#include "order.h"

int Order::nextId = 1;

Order::Order() {

    id = nextId;
    nextId++;
}

Order::Order(const Order &o){
    vector<Package *> newPurchase(o.getPurchase());
    purchase = newPurchase;
    price = o.getPrice();
    rating = o.getRating();
    dateToPickUp = o.getDateToPickUp();
    timeToPickUp = o.getTimeToPickUp();
}

vector <Package *> Order::getPurchase() const {
    return purchase;
}

int Order::getId() const {
    return id;
}

double Order::getPrice() const {
    return price;
}

int Order::getHadDiscount() const {
    return hadDiscount;
}

int Order::getRating() const {
    return rating;
}

string Order::getPickUpAddress() const {
    return pickUpAddress;
}

Date Order::getDateToPickUp() const {
    return dateToPickUp;
}
Time Order::getTimeToPickUp() const {
    return timeToPickUp;
}

Client* Order::getClient() const {
    return client;
}

string Order::getInfo() const {

    stringstream os;
    os << "Order " << id << ":\n";
    for(unsigned i = 0; i < purchase.size(); i++){
        os << purchase[i]->getInfo();
    }
    os << "Price: " << price << endl;

    if (pickUpAddress == "")
        os << "This order wasn't sent to the bakery yet\n";
    else{
        os << "Date to pick up: " << dateToPickUp.getInfo() << endl
           << "Time to pick up: " << timeToPickUp.getInfo() << endl;
    }


    return os.str();
}

void Order::addPackage(Package* purchase) {
    (this->purchase).push_back(purchase);
    price += purchase->getPrice();
}

void Order::setRating(int rating) {
    this->rating = rating;
}

void Order::setHadDiscount(int discount) {
    this->hadDiscount = discount;
}

void Order::setPickUpAddress(string address) {
    pickUpAddress = address;
}


void Order::setPrice(double price) {
    this->price = price;
}

void Order::setClient(Client* c) {
    this->client = c;
}

void Order::setDateToPickUp(Date date) {
    dateToPickUp = date;
}

void Order::setTimeToPickUp(Time time) {
    timeToPickUp = time;
}

void Order::sendOrderToBakery(string mode) {
    Date date;
    Time time;

    if (mode == "alwaysOpen"){
        date.setWeekday("Monday");
        time = Time(15, 0);
    }

    Time::pickUpTimeDate(date, time);

    dateToPickUp = date;
    timeToPickUp = time;
}

void Order::productMoneyEarned(int discount) {

    vector<Package *>::iterator it = purchase.begin();
    while(it != purchase.end()){
        double money = (*it)->getPrice();
        money = money * ((100 - (double)discount) / 100);
        ((*it)->getProduct())->moneyEarned(money); //This increases the right category of product because the method moneyEarned is virtual
        int quantity = (*it)->getQuantity();
        ((*it)->getProduct())->productSold(quantity);
        it++;
    }
}

bool Order::operator<(const Order& order) const {
    if(this->dateToPickUp < order.dateToPickUp){
        return true;
    }
    else if(this->dateToPickUp == order.dateToPickUp && this->timeToPickUp == order.timeToPickUp){
        return true;
    }
    else return false;
}

bool Order::operator==(const Order& order) const {
    if(id == order.id)
        return true;
    else
        return false;
}

bool DeliveryOrder::operator<(const DeliveryOrder& do2) const {

    Client* c1 = order->getClient();
    Client* c2 = (do2.getOrder())->getClient();

    if (c1->getOpinionValue() == c2->getOpinionValue()) {
        return c1->getPastDiscounts() > c2->getPastDiscounts();
    }

    return c1->getOpinionValue() > c2->getOpinionValue();
}

OrderNotFound::OrderNotFound(Order* order) : order(order), id(order->getId()) {
    cout << "\nSorry, we couldn't find the order with id " << order->getId()
         << " that was made by a client whose nif is " << order->getClient()->getNif() << endl;
}
