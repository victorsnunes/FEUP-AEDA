#include "bakery.h"

vector<string> NoRepeating::AllBakeryAddresses;

using namespace std;

Bakery::Bakery(string address, Company* company) {
    this->address = address;
    this->company = company;

    for (string ad : NoRepeating::AllBakeryAddresses) {
        if(ad == address)
            throw BakeryAddressAlreadyUsed(address);
    }

    company->addBakery(this); //Adds the new created bakery to the company's bakeries vector
}

Bakery::~Bakery() {}

string Bakery::getAddress() const {
    return this->address;
}

vector<Client *> Bakery::getClients() const {
    return this->clients;
}

vector<Employee *> Bakery::getEmployees() {
    return this->employees;
}

Company* Bakery::getCompany() {
    return this->company;
}

vector<Order*> Bakery::getOrders() const{
	vector<Order*> orders_out;
	for (unsigned i = 0; i < employees.size(); i++) {
		vector<Order*> orders = employees[i]->getIncompletedOrders();
		for (unsigned j = 0; j < orders.size(); i++) {
			orders_out.push_back(orders[j]);
		}
	}
	return orders_out;
}

string Bakery::getInfo() const{
	stringstream ss;

    string ad = this->address;
    size_t pos;
    while ((pos = ad.find(" ")) != std::string::npos) {
        ad.replace(pos, 1, "_");
    }
	ss << "Address: " << ad << endl 
	   << "Number of employees: " << this->employees.size() << endl 
	   << "Number of clients: " << this->clients.size() << endl 
	   << "Number of orders: " << this->getOrders().size() << endl << endl;
	return ss.str();
}

void Bakery::addClient(Client *client) {
    this->clients.push_back(client);    //adds client to the bakery

    //Adding client to the company vector, if he's not already there
    if ( (company->getClients()).size() == 0 || sequencialSearch(company->getClients(), client) == -1)
        company->addClient(client);

}

void Bakery::addEmployee(Employee *employee, int salary, string job) {

    //Checking if this employee doesn't already work in another bakery
    if (employee->getWorkingAddress() != "none")
        throw EmployeeAlreadyWorks(employee);

    employee->setWorkingAddress(this->address);   //Now his working address is the bakery address
    employee->setSalary(salary);                         //And he got a salary
    employee->setJob(job);                               //And he got a job

    this->employees.push_back(employee);     //Adds employee to the bakery's employee vector
    company->addEmployee(employee);          //Adds employee to the company's employee vector
    company->addToEmployeeTable(employee);  //Adds employee to the company's employee hash table

}

void Bakery::fireEmployee(Employee * employee) {

    //Searches for the employee
    int indexBakery = sequencialSearch(employees, employee);

    //If employee doesn't exist
    if (indexBakery == -1)
        throw(EmployeeNotFound(employee->getNif()));
    else {
        employee->setSalary(0);                                   //No more salary
        employee->setWorkingAddress("none");                    //No more working address
        employee->setJob("none");                                 //No more job
        employees.erase( employees.begin() + indexBakery );   //Removing him from the the list of employees of the bakery
        company->removeEmployee(employee);                          //Removing him from the the list and table of employees of the company
    }

}

Employee* Bakery::searchEmployee(Employee * employee){
	vector<Employee *> ::iterator it = employees.begin();
	while (it != employees.end()) {
		if ((*it)->getNif() == employee->getNif()) {
			return (*it);
		}
		it++;
	}
	throw(EmployeeNotFound(employee->getNif()));
}

Employee* Bakery::lessBusyEmployee() {

    int minimum = 999;
    vector<Employee*> cookers = company->searchEmployeesByJob("cooker");

    for (auto it = cookers.begin(); it != cookers.end(); it++){

        //Cooker from another bakery, we have to remove him from our vector of cookers from this bakery
        if ( (*it)->getWorkingAddress() != address ) {
            cookers.erase(it);
            it--;
            continue;
        }

        //Checking if the cooker has less orders than the minimum yet found
        if ( ((*it)->getIncompletedOrders()).size() < minimum )
            minimum =  ((*it)->getIncompletedOrders()).size();
    }

    for (Employee* employee : cookers){
        if ((employee->getIncompletedOrders()).size() == minimum )
            return employee;
    }

    //This exception is thrown we the bakery has no cooker
    throw ThisBakeryDoesntHaveAnyCooker(this);
}

void Bakery::sortEmployees(){
	insertionSort(employees);
}

void Bakery::setAddress(string address){
	this->address = address;
}

void Bakery::setCompany(Company* company){
    this->company = company;
}

void Bakery::receivedNewOrder(Order* order, Client* client) {

    //If this client isn't registered yet, register him
    if (clients.size() == 0 || sequencialSearch(this->clients, client) == -1) {
        addClient(client);
    }

    //If some product isn't registered yet, register it
    for (Package* pack : order->getPurchase()) {
        Product* product = pack->getProduct();
        if ((company->getProducts()).size() == 0 || sequencialSearch(company->getProducts(), product) == -1)
            company->addProduct(product);

    }

    //Increases the frequency of the products
    vector<Package*> packages = order->getPurchase();
    for (int i = 0; i < packages.size(); i++) {

        Product* product = packages[i]->getProduct();
        int freq = company->frequencyOfProduct(product);

        ProductFrequency pf(product, freq);
        company->removeProductFrequency(pf);
        ++pf;
        company->addProductFrequency(pf);
    }

    //Finds the less busy employee, and give this new order to him
    Employee* employee = lessBusyEmployee();
    employee->newOrder(company, order);

}

void Bakery::deliverOrders(Employee* deliveryman, string mode, string mode2) {

    if (deliveryman->getJob() != "deliveryman")
        throw IAmNotADeliveryman(deliveryman);

    Date date;
    Time time;

    if (mode2 == "alwaysOpen"){
        date.setWeekday("Monday");
        time = Time(15, 0);
    }

    if (mode == "fastfoward30min")
        ++time;

    if (date.getWeekday() == "Saturday" || date.getWeekday() == "Sunday") {
        throw BakeryClosed(date, time);
    }
    if (time < Time(7,0) || Time(20,0) < time){
        throw BakeryClosed(date, time);
    }

    priority_queue<DeliveryOrder> totalOrdersToDeliver;

    for (Employee* cooker : employees) {
        //Updating the completed orders from the cookers
        //Refreshing a non cooker employee doesn't do nothing
        cooker->refresh(company, mode, mode2);
        for (Order* order : cooker->getCompletedOrders()) {
            totalOrdersToDeliver.push(DeliveryOrder(order, cooker));
        }
    }

    if (totalOrdersToDeliver.empty()) {
        cout << "\n" << deliveryman->getName() << ": Hey, there're no orders for me to deliver!\n";
        return;
    }

    //Filling the priority queue of the deliveryman with orders (max 5)
    while(!totalOrdersToDeliver.empty() && (deliveryman->getOrdersToDeliver().size() < 5)) {

        DeliveryOrder delOrder = totalOrdersToDeliver.top();
        totalOrdersToDeliver.pop();

        //Removing this order from the completed orders vector of the cooker
        Employee* cooker = delOrder.getCookerWhoMadeIt();
        cooker->eraseCompletedOrder(delOrder.getOrder());

        deliveryman->addOrderToDeliver(delOrder);
    }

    int num = (deliveryman->getOrdersToDeliver()).size();

    cout << "\n" << deliveryman->getName() << ": Alright, I'm going to deliver " <<
    num << " order"; if (num != 1) cout << "s"; cout << "\n\n";

    //Deliverying the orders
    while ( !(deliveryman->getOrdersToDeliver()).empty() ) {

        cout << "Driving to the client's house...\n";

        Client* clientToDeliver = (deliveryman->getOrdersToDeliver()).top().getOrder()->getClient();

        int numOrdersDelivered = deliveryman->giveDeliveredOrder(company, clientToDeliver);

        cout << deliveryman->getName() << ": Hello, here you have your " << numOrdersDelivered <<
        " order"; if(numOrdersDelivered != 1) cout << "s";

        cout << endl << clientToDeliver->getName() << ": Oh, thank you very much.\n\n";

    }

}

void Bakery::showClients() const{
	vector<Client *> ::const_iterator it = clients.begin();
	cout << "These are the clients of the bakery:\n ";
	while (it != clients.end()) {
		cout << (*it)->getInfo() << endl;
		it++;
	}
}

bool Bakery::operator == (const Bakery& b2) const {
    return address == b2.getAddress();
}


////////////////////// EMPLOYEE HASH FUNCTION //////////////////////////

bool EmployeeHash::operator() (const Employee* e1, const Employee* e2) const {
    return e1->getNif() == e2->getNif();
}

int EmployeeHash::operator() (const Employee* e) const {

    int v = 0;
    for (char letter : e->getJob()) {
        v = 37 * v + letter;
    }
    return v;
}


/////////////////// COMPANY ///////////////////

vector<Product *> Company::getProducts() const{
	return products;
}

vector<Bakery *> Company::getBakeries() const{
    return bakeries;
}

vector<Employee *> Company::getEmployees() const{
	return employees;
}

vector<Client *> Company::getClients() const {
    return clients;
}

vector<Client *> Company::getClientsPremium() const {

	vector<Client *> ret;
	for (Client* client : clients) {
	    if (client->getPremium())
	        ret.push_back(client);
	}

	return ret;
}

vector<Order *> Company::getDeliveredOrders() const {
    return deliveredOrders;
}
vector<Order *> Company::getIncompletedOrders() const {
    return incompletedOrders;
}
vector<Order *> Company::getCompletedOrders() const {
    return completedOrders;
}

BST<ProductFrequency> Company::getProductsFrequency() const {
    return productsFrequency;
}


vector<Employee*> Company::searchEmployeesByJob(string job) const {
    
    vector<Employee*> res;
    for (auto it = tableEmployees.begin(); it != tableEmployees.end(); it++) {
        if ((*it)->getJob() == job)
            res.push_back(*it);
    }
    return res;
}



Product* Company::chooseProduct(string name) const{

    for (Product* product : products) {
        if (product->getName() == name)
            return product;
    }

    throw ProductNotFound(name);

}

Bakery * Company::chooseBakery(string address) const{

    for (Bakery* bakery : bakeries) {
        if (bakery->getAddress() == address)
            return bakery;
    }
    
    throw BakeryNotFound(address);
    
}

Client* Company::chooseClient(int nif) const{

    for (Client* client : clients) {
        if (client->getNif() == nif)
            return client;
    }

	throw ClientNotFound(nif);

}

Employee* Company::chooseEmployee(int nif) const{

    for (Employee* employee : employees) {
        if (employee->getNif() == nif)
            return employee;
    }

	throw(EmployeeNotFound(nif));

}

Order* Company::chooseOrder(int id) const{

    for (Order* order : deliveredOrders){
        if (order->getId() == id)
            return order;
    }

    for (Order* order : completedOrders){
        if (order->getId() == id)
            return order;
    }

    for (Order* order : incompletedOrders){
        if (order->getId() == id)
            return order;
    }

    throw OrderNotFound(id);

}

void Company::addBakery(Bakery* bakery){
	if(bakeries.size() == 0 || sequencialSearch(this->bakeries, bakery) == -1){
	    bakery->setCompany(this);
		this->bakeries.push_back(bakery);
	}
	else throw(AlreadyExistingBakery(bakery));
}


void Company::addClient(Client* client) {
    clients.push_back(client);
}
void Company::addEmployee(Employee* employee) {
    employees.push_back(employee);
}
void Company::addDeliveredOrder(Order* order) {
    deliveredOrders.push_back(order);
}
void Company::addCompletedOrder(Order* order) {
    completedOrders.push_back(order);
}
void Company::addIncompletedOrder(Order* order) {
    incompletedOrders.push_back(order);
}
void Company::addProduct(Product * product){
    products.push_back(product);
    productsFrequency.insert(ProductFrequency(product));
}
void Company::addProductFrequency(ProductFrequency productFrequency) {

    ProductFrequency pf = productsFrequency.find(productFrequency);
    if (pf.getProduct()->getName() == "")
        productsFrequency.insert(productFrequency);
    else
        throw AlreadyExistingProductFrequency(pf);
}
void Company::addToEmployeeTable(Employee* employee) {

    auto tmp = tableEmployees.insert(employee);

    if (!tmp.second) throw EmployeeAlreadyWorks(employee);
}


void Company::removeEmployee(Employee* employee) {
    int index = sequencialSearch(employees, employee);

    if (index == -1)
        throw EmployeeNotFound(employee);
    else {
        employees.erase( employees.begin() + index );
        tableEmployees.erase(employee);
    }

}
void Company::removeCompletedOrder(Order* order) {
    int index = sequencialSearch(completedOrders, order);

    if (index == -1)
        throw OrderNotFound(order);
    else
        completedOrders.erase( completedOrders.begin() + index );
}
void Company::removeIncompletedOrder(Order* order) {

    int index = sequencialSearch(incompletedOrders, order);

    if (index == -1)
        throw OrderNotFound(order);
    else
        incompletedOrders.erase( incompletedOrders.begin() + index );
}
void Company::removeProductFrequency(ProductFrequency productFrequency) {

    ProductFrequency pf = productsFrequency.find(productFrequency);
    if (pf.getProduct()->getName() == "")
        throw ProductFrequencyNotFound(pf);
    else
        productsFrequency.remove(productFrequency);
}
void Company::removeFromEmployeeTable(Employee* employee) {
    tableEmployees.erase(employee);
}



int Company::frequencyOfProduct(Product* product) {

    for (BSTItrIn<ProductFrequency> it(productsFrequency); !it.isAtEnd(); it.advance()) {

        ProductFrequency pf = it.retrieve();
        if (pf.getProduct() == product)
            return pf.getFrequency();
    }

    throw ProductFrequencyNotFound();
}

int Company::frequencyOfCategory(string category) {

    int result = 0;

    for (BSTItrIn<ProductFrequency> it(productsFrequency); !it.isAtEnd(); it.advance()) {
        
        ProductFrequency pf = it.retrieve();
        if (pf.getProduct()->getCategory() == category)
            result += pf.getFrequency();
    }

    return result;

}

Product* Company::mostRequestedProduct() {

    if (productsFrequency.isEmpty())
        throw ProductFrequencyNotFound();

    ProductFrequency pf;
    for (BSTItrIn<ProductFrequency> it(productsFrequency); !it.isAtEnd(); it.advance()) {
        pf = it.retrieve();
    }

    return pf.getProduct();

}

Product* Company::leastRequestedProduct() {

    if (productsFrequency.isEmpty())
        throw ProductFrequencyNotFound();

    BSTItrIn<ProductFrequency> it(productsFrequency);
    ProductFrequency pf = it.retrieve();

    return pf.getProduct();
}



int Company::totalMoneyEarnedFromBakery(Bakery* bakery) {
    int money = 0;
    for (Order* order : deliveredOrders) {
        if (order->getPickUpAddress() == bakery->getAddress())
            money += order->getPrice();
    }
    return money;
}
int Company::totalOrdersDeliveredFromBakery(Bakery* bakery) {
    int quantity = 0;
    for (Order* order : deliveredOrders) {
        if (order->getPickUpAddress() == bakery->getAddress())
            quantity++;
    }
    return quantity;
}
double Company::totalMoneyEarnedByCategory(string category) {

    if (category == "beverage" || category == "Beverage") {
        return Beverage::getTotalMoneyBeverage();
    }
    if (category == "bread" || category == "Bread") {
        return Bread::getTotalMoneyBread();
    }
    if (category == "cake" || category == "Cake") {
        return Cake::getTotalMoneyCake();
    }

    throw InvalidCategory(category);
}
int Company::totalQuantitySoldByCategory(string category) {

    if (category == "beverage" || category == "Beverage") {
        return Beverage::getTotalBeverageSold();
    }
    if (category == "bread" || category == "Bread") {
        return Bread::getTotalBreadSold();
    }
    if (category == "cake" || category == "Cake") {
        return Cake::getTotalCakeSold();
    }

    throw InvalidCategory(category);
}

int Company::totalNumberOfClients() {
    return clients.size();
}
int Company::totalNumberOfPremiumClients() {
    return getClientsPremium().size();
}
int Company::totalNumberOfNormalClients() {
    return clients.size() - getClientsPremium().size();
}


void Company::printClientHistory(Client* client) {

    if (clients.size() == 0 || sequencialSearch(clients, client) == -1)
        throw ClientNotFound(client);

    int NumClientsOrders = 0;
    int ClientsPoints = 0;

    cout << "\nThis is the full history of the client " << client->getName();
    if (client->getPremium())
        cout << " (premium client)";
    else
        cout << " (normal client)";
    cout << ":\n\n";

    //Looks for all the delivered orders from this client
    for (Order* order : deliveredOrders) {
        if (order->getClient() == client) {

            NumClientsOrders++;
            int discount = order->getHadDiscount();

            cout << "Order " << NumClientsOrders << endl;

            cout << "Id: " << order->getId() << endl;
            if (discount != 0)
                cout << "Discount: " << discount << "%\n";
            else
                cout << "Discount: No discount\n";

            cout << "Price: " << order->getPrice() << endl;
            cout << "This order was picked up at " << (order->getDateToPickUp()).getInfo()
                 << ", " << (order->getTimeToPickUp()).getInfo()
                 << ",\nin a bakery with address " << order->getPickUpAddress() << endl;

            if (discount == 0) {
                int gainedPoints = order->getPrice() * 10;
                ClientsPoints += gainedPoints;
                cout << "The client gained +" << gainedPoints << " with this order.\n"
                     << "Now the client has " << ClientsPoints << " points\n\n";
            }
            else {
                if (discount == 2)
                    ClientsPoints -= 200;
                else
                    ClientsPoints -= 100;
                cout << "Now the client's points return to " << ClientsPoints << "\n\n";
            }
        }
    }

    //Looks for all the completed orders from this client
    for (Order* order : completedOrders) {
        if (order->getClient() == client) {

            NumClientsOrders++;
            int discount = order->getHadDiscount();

            cout << "Order " << NumClientsOrders << endl;

            cout << "Id: " << order->getId() << endl;
            if (discount != 0)
                cout << "Discount: " << discount << "%\n";
            else
                cout << "Discount: No discount\n";

            cout << "Price: " << order->getPrice() << endl;
            cout << "This order wasn't picked up yet, but it can be from the " << (order->getDateToPickUp()).getInfo()
                 << ", " << (order->getTimeToPickUp()).getInfo()
                 << ",\nat the bakery with address " << order->getPickUpAddress() << endl;

            if (discount == 0) {
                int gainedPoints = order->getPrice() * 10;
                ClientsPoints += gainedPoints;
                cout << "The client gained +" << gainedPoints << " with this order.\n"
                     << "Now the client has " << ClientsPoints << " points\n\n";
            }
            else {
                if (discount == 2)
                    ClientsPoints -= 200;
                else
                    ClientsPoints -= 100;
                cout << "Now the client's points return to " << ClientsPoints << "\n\n";
            }
        }
    }

    //Looks for all the incompleted orders from this client (The same structure as the previous one)
    for (Order* order : incompletedOrders) {
        if (order->getClient() == client) {

            NumClientsOrders++;
            int discount = order->getHadDiscount();

            cout << "Order " << NumClientsOrders << endl;

            cout << "Id: " << order->getId() << endl;
            if (discount != 0)
                cout << "Discount: " << discount << "%\n";
            else
                cout << "Discount: No discount\n";

            cout << "Price: " << order->getPrice() << endl;
            cout << "This order wasn't picked up yet, but it can be from the " << (order->getDateToPickUp()).getInfo()
                 << ", " << (order->getTimeToPickUp()).getInfo()
                 << ",\nat the bakery with address " << order->getPickUpAddress() << endl;

            if (discount == 0) {
                int gainedPoints = order->getPrice() * 10;
                ClientsPoints += gainedPoints;
                cout << "The client gained +" << gainedPoints << " with this order.\n"
                     << "Now the client has " << ClientsPoints << " points\n\n";
            }
            else {
                if (discount == 2)
                    ClientsPoints -= 200;
                else
                    ClientsPoints -= 100;
                cout << "Now the client's points return to " << ClientsPoints << "\n\n";
            }
        }
    }

}

void Company::increaseEmployeesSalaryByJob(int percentageIncreased, string job) {

    vector<Employee*> employeesOfThatJob = searchEmployeesByJob(job);
    for (auto it = employeesOfThatJob.begin(); it != employeesOfThatJob.end(); it++) {

        int salary = (*it)->getSalary();
        salary *= (1 + (double)(percentageIncreased) / 100);
        (*it)->setSalary(salary);
    }
}