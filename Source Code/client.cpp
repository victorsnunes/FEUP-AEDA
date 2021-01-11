#include "client.h"

using namespace std;

vector<int> NoRepeating::AllNifs;

Client::Client(string name, int nif, string type) : nif(nif){
    this->name = name;

    if (type == "premium")
        this->premium = true;

    for (int n : NoRepeating::AllNifs) {
        if (nif == n)
            throw NifAlreadyUsed(nif);
    }
    NoRepeating::AllNifs.push_back(nif);
}

int Client::getNif() const {
    return nif;
}

string Client::getName() const {
    return name;
}

bool Client::getOpinion() const {
    return opinion;
}

double Client::getOpinionValue() const {
    return opinionValue;
}

bool Client::getPremium() const {
    return premium;
}

int Client::getPastDiscounts() const {
    return pastDiscounts;
}

int Client::getPoints() const {
    return points;
}

vector<Order *> Client::getReceivedOrders() const {
    return receivedOrders;
}

vector<Order *> Client::getCurrentOrders() const {
    return currentOrders;
}

string Client::getInfo() const{
    stringstream ss;
    string opiniao = "Negatif";
    if(this->opinion){
        opiniao = "Positive";
    }

    ss << "Nif: " << nif << endl 
       << "Name: " << name << endl
       << "Opinion: " << opiniao << endl 
       << "Points: " << points << endl << endl;
    return ss.str();
}

int Client::hasDiscount(){
    if(this->premium && this->points >= 100) return 5;
    if(this->points >= 200) return 2;
    return 0;
}

void Client::addReceivedOrder(Order* order) {

    int myRating = clientFeedback();
    order->setRating(myRating);
    checkOpinion();

    receivedOrders.push_back(order);
    eraseCurrentOrder(order);
}

void Client::setName(string name) {
    this->name = name;
}

void Client::setPremium(bool premium) {
    this->premium = premium;
}

void Client::setPastDiscounts(int pd) {
    this->pastDiscounts = pd;
}

void Client::setPoints(int points) {
    this->points = points;
}

void Client::setOpinionValue(double value) {
    this->opinionValue = value;
}

void Client::makeNewOrder(Order* order, Bakery* bakery, string mode) {

    Date date;
    Time time;

    if (mode == "alwaysOpen"){
        date.setWeekday("Monday");
        time = Time(15, 0);
    }

    if ( time < Time(7, 0) || Time(20, 0)< time || date.getWeekday() == "Saturday" || date.getWeekday() == "Sunday") {
        throw BakeryClosed(date, time);
    }

    if (order->getPickUpAddress() != "")
        throw OrderBeingResent(order);

    int discount = hasDiscount();
    if (discount != 0){

        double newPrice = order->getPrice() * ((100.0 - (double)hasDiscount()) / 100.0);
        order->setPrice(newPrice);
        order->setHadDiscount(discount);

        if (premium)
            points -= 100;
        else
            points -= 200;

        pastDiscounts++;
    }
    else {
        points += static_cast<int>(order->getPrice()) * 10;
    }

    order->productMoneyEarned(discount);

    order->setPickUpAddress(bakery->getAddress());
    order->setClient(this);
    order->sendOrderToBakery(mode);
    bakery->receivedNewOrder(order, this);

    currentOrders.push_back(order);
}

void Client::goToTheBakeryToPickUpOrder(Bakery* bakery, string mode, string mode2) {

    cout << "Client " << name << " goes to the bakery in " << bakery->getAddress() << " to pick up his order..\n\n";

    Date date;
    Time time;

    if (mode2 == "alwaysOpen"){
        date.setWeekday("Monday");
        time = Time(15, 0);
    }

    if (mode == "fastfoward30min")
        ++time;

    if (date.getWeekday() == "Saturday" || date.getWeekday() == "Sunday") {
        cout << name << ": Oh, they're closed, I forgot it's " << date.getWeekday() << ".\n";
        return;
    }
    if (time < Time(7,0) || Time(20,0) < time){
        cout << name << ": Oh, they're closed. It's " << time.getInfo() <<", I should have expected it." << endl;
        return;
    }


    if (time < Time(12, 0))
        cout << name << ": Good morning, I came here to pick my order.\n";
    else if (time < Time(18, 0))
        cout << name << ": Good afternoon, I came here to pick my order.\n";
    else
        cout << name << ": Good evening, I came here to pick my order.\n";

    cout << "Manager: Alright, wait a second please\n\n";
    cout << "A few moments later... \n\n";

    int tmp = 0;
    for (auto employee : bakery->getEmployees()) {
        employee->refresh(bakery->getCompany(), mode, mode2);
        int numOrders = employee->giveOrder(bakery->getCompany(), this);
        if (numOrders != 0) {
            cout << employee->getName() <<": Here you have, " << numOrders << " order";
            if(numOrders != 1)
                cout << "s";
            cout << " for you\n";
            tmp++;
        }
    }

    if (tmp == 0) {
        cout << "Manager: I'm sorry, but there's nothing for you by now.\n";
    }

}

void Client::eraseCurrentOrder(Order* order){
    currentOrders.erase(currentOrders.begin() + sequencialSearch(currentOrders, order));
}

bool Client::searchOrder(Order* order){
    if(sequencialSearch(currentOrders, order) != -1){
        return true;
    }
    else if(sequencialSearch(receivedOrders, order) != -1){
        return true;
    }
    else return false;
}

int Client::clientFeedback(){
    int feedback = (rand() % 10);
    return (feedback > 5) ? 5 : feedback;  //50% chance of giving 5 stars
}

void Client::checkOpinion() {

    vector<Order *>::iterator it = receivedOrders.begin();
    double sum = 0;
    while (it != receivedOrders.end()){
        sum += (*it)->getRating();
        it++;
    }
    opinionValue = sum / receivedOrders.size();
    
    if(opinionValue >= 2.5)
        this->opinion = true;
    else
        this->opinion = false;
}

bool Client::operator==(Client client) const {
    if(this->nif == client.nif){
        return true;
    }
    else return false;
}
