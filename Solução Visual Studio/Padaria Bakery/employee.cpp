#include "employee.h"

Employee::Employee(string name, int nif) : nif(nif) {
    this->name = name;

    for (int n : NoRepeating::AllNifs) {
        if (nif == n)
            throw NifAlreadyUsed(nif);
    }
    NoRepeating::AllNifs.push_back(nif);
}

int Employee::getNif() const {
    return nif;
}

string Employee::getName() const {
    return name;
}

int Employee::getSalary() const {
    return salary;
}

string Employee::getWorkingAddress() const {
    return workingAddress;
}

string Employee::getJob() const {
    return job;
}

vector<Order*> Employee::getIncompletedOrders() const {
    return incompletedOrders;
}

vector<Order*> Employee::getCompletedOrders() const {
    return completedOrders;
}

priority_queue<DeliveryOrder> Employee::getOrdersToDeliver() const {
    return ordersToDeliver;
}

string Employee::getInfo() const {

    stringstream ss;
    ss << "Nif: " << this->nif << endl
       << "Name: " << name << endl
       << "Salary: " << this->salary << endl;
    return ss.str();
}

void Employee::setName(string name) {
    this->name = name;
}

void Employee::setSalary(int salary) {
    this->salary = salary;
}

void Employee::setWorkingAddress(string address) {
    this->workingAddress = address;
}

void Employee::setJob(string job) {
    this->job = job;
}


void Employee::addOrderToDeliver(DeliveryOrder deliveryOrder) {
    ordersToDeliver.push(deliveryOrder);
}

DeliveryOrder Employee::popOrderToDeliver() {
    DeliveryOrder delOrder = ordersToDeliver.top();
    ordersToDeliver.pop();
    return delOrder;
}


void Employee::newOrder(Company* company, Order *order) {
    incompletedOrders.push_back(order);
    company->addIncompletedOrder(order);

}

void Employee::refresh(Company* company, string mode, string mode2) {
    Date date;
    Time time;

    if (mode2 == "alwaysOpen"){
        date.setWeekday("Monday");
        time = Time(15, 0);
    }

    if (mode == "fastfoward30min")
        ++time;

    //Let's check all incompleted orders from this employee
    auto it = incompletedOrders.begin();
    for ( it ; it != incompletedOrders.end() ; it++) {
        //Same day
        if ((*it)->getDateToPickUp() == date) {
            //Cheking time to pick up this order
            if ((*it)->getTimeToPickUp() < time || (*it)->getTimeToPickUp() == time){
                completedOrders.push_back(*it);         //Added to completed orders from the employee
                company->addCompletedOrder(*it);        //Added to completed orders from the company
                company->removeIncompletedOrder(*it);   //Removed from the incompleted orders from the company
                incompletedOrders.erase(it);            //Removed from the incompleted orders from the employee
                it--;
            }
        }
        //The following days
        else {
            if ((*it)->getDateToPickUp() < date) {
                completedOrders.push_back(*it);         //Added to completed orders from the employee
                company->addCompletedOrder(*it);        //Added to completed orders from the company
                company->removeIncompletedOrder(*it);   //Removed from the incompleted orders from the company
                incompletedOrders.erase(it);            //Removed from the incompleted orders from the employee
                it--;
            }
        }
    }

}

int Employee::giveOrder(Company* company, Client* client) {

    Date date;
    Time time;

    auto it = completedOrders.begin();
    int count = 0;  //This will count how many orders the client received

    for (it; it != completedOrders.end(); it++){
        //Checking if the nif registered in the order is the same nif of the client requesting it
        if ((*it)->getClient() == client){

            (*it)->setDateToPickUp(date);   //After giving the order to the client, the variable dateToPickUp now represents the date the client has picked up the order
            (*it)->setTimeToPickUp(time);   //After giving the order to the client, the variable timeToPickUp now represents the time the client has picked up the order

            client->addReceivedOrder(*it);          //Client register received order
            company->addDeliveredOrder(*it);       //Company register delivered order

            company->removeCompletedOrder(*it);   //Order is erased from the completed but not delivered vector of the company
            completedOrders.erase(it);           //Order is erased from the completed but not delivered vector of the employee
            it--;

            count++;
        }
    }
    return count;
}

int Employee::giveDeliveredOrder(Company* company, Client* client) {

    Date date;
    Time time;

    int count = 0;  //This will count how many orders the client received

    while ( !ordersToDeliver.empty() && (ordersToDeliver.top().getOrder())->getClient() == client ) {

        Order* order = ordersToDeliver.top().getOrder();
        ordersToDeliver.pop();
        order->setDateToPickUp(date);   //After giving the order to the client, the variable dateToPickUp now represents the date the client has picked up the order
        order->setTimeToPickUp(time);   //After giving the order to the client, the variable timeToPickUp now represents the time the client has picked up the order

        client->addReceivedOrder(order);          //Client register received order
        company->addDeliveredOrder(order);       //Company register delivered order

        company->removeCompletedOrder(order);   //Order is erased from the completed but not delivered vector of the company

        count++;
    }

    return count;
}

void Employee::eraseIncompletedOrder(Order* order) {

    auto it = incompletedOrders.begin();
    while (it != incompletedOrders.end()) {
        if (*it == order){
            incompletedOrders.erase(it);
            return;
        }
        it++;
    }
}

void Employee::eraseCompletedOrder(Order* order) {

    auto it = completedOrders.begin();
    while (it != completedOrders.end()) {
        if (*it == order){
            completedOrders.erase(it);
            return;
        }
        it++;
    }
}

bool Employee::operator==(int nif) const{
    if(this->nif == nif)
        return true;
    else
        return false;
}

bool Employee::operator<(Employee &e) const{
    if (this->name < e.getName())
        return true;
    else
        return false;
}

bool Employee::operator ==(const Employee& employee) const{
    if(this->nif == employee.getNif())
        return true;
    else
        return false;
}