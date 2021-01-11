#ifndef BAKERY_H_
#define BAKERY_H_

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include "client.h"
#include "order.h"
#include "product.h"
#include "employee.h"
#include "bst.h"

using namespace std;

class Product;
class Order;
class Client;
class Employee;
struct EmployeeHash;
class Company;
class NoRepeating;

/**
 * Bakery Class
 * This class represents a bakery object. It stores its name, address, employees that work there and
 * clients who once bought something there
 */
class Bakery{
    string address;
    vector<Client *> clients;
    vector<Employee *> employees;
    Company* company;
public:

    /**
     * Bakery Constructor
     * @param address The address of the bakery
     * @param company The company of Anthony
     */
    Bakery(string address, Company* company);
    ~Bakery();

    string getAddress() const;
    vector<Client *> getClients() const;
    vector<Employee *> getEmployees();
    Company* getCompany();
    /**
     * This method returns all the incompleted orders of this bakery
     * @return The incompleted orders of this bakery
     */
    vector<Order*> getOrders() const;
    /**
     * Basic information method
     * @return Returns some basic information about the bakery
     */
    string getInfo() const;

    void addClient(Client * client);
    void addEmployee(Employee * employee, int salary, string job);
    void fireEmployee(Employee * employee);

    /**
     * Searches for a certain employee that works in this bakery
     * @param employee The employee we're looking for
     * @return The employee we've found. If we couldn't find the employee, it throws an exception of NonExistingEmployee
     */
    Employee* searchEmployee(Employee * employee);

    /**
     * This method finds the less busy employee in this bakery. In case of multiple employees being equally
     * less busy, it returns the first it finds in the list of employees
     * @return The less busy employee
     */
    Employee* lessBusyEmployee();
    /**
     * Sorts the vector of employees (by their names)
     */
    void sortEmployees();
	void setAddress(string address);
	void setCompany(Company* company);
	/**
	 * This method indicates that this bakery has just received a new Order, from a certain client
	 * @param order The order the bakery has just received
	 * @param client The client that has just made this order
	 */
    void receivedNewOrder(Order* order, Client* client);
    /**
    * The employee must be a deliveryman, and with this method he will delivery all the completed orders
    * (max of 5) to the clients, begining with the clients with more negative opinions
    * @param mode For testing, this argument accepts "fastfoward30min" mode, which increases 30 minutes of the current time, so that we can see the new orders being concluded by the employee
    * @param mode2 For testing, this argument accepts "alwaysOpen" mode, which set the time and date to a regular working time of the bakery
    */
    void deliverOrders(Employee* deliveryman, string mode, string mode2);
    /**
     * Prints in the screen information about all the clients that have bought something from this bakery
     */
    void showClients() const;
    /**
     * Two bakerys are the same if they have the same id
     * @param b2 The second bakery
     * @return True if they are thhe same bakery, false otherwise
     */
    bool operator == (const Bakery& b2) const;
};

struct EmployeeHash {
    bool operator() (const Employee* e1, const Employee* e2) const;
    int operator() (const Employee* e) const;
};

typedef unordered_set<Employee*, EmployeeHash, EmployeeHash> HtableEmp;

class Company {
    string name = "Anthony's Bakeries Center";
    string owner = "Anthony";
	vector<Bakery *> bakeries;
	vector<Client *> clients;
    vector<Employee*> employees;
	vector<Order *> deliveredOrders;
	vector<Order *> completedOrders;
    vector<Order *> incompletedOrders;
	vector<Product *> products;

    HtableEmp tableEmployees;

    BST<ProductFrequency> productsFrequency;

public:
    Company() : productsFrequency(ProductFrequency()) {}
	~Company() {}

	vector<Product *> getProducts() const;
	vector<Bakery *> getBakeries() const;
	vector<Employee *> getEmployees() const;
	vector<Client *> getClients() const;
	vector<Client *> getClientsPremium() const;
	vector<Order *> getDeliveredOrders() const;
	vector<Order *> getIncompletedOrders() const;
    vector<Order *> getCompletedOrders() const;
    BST<ProductFrequency> getProductsFrequency() const;

    Product* chooseProduct(string name) const;
	Bakery* chooseBakery(string address) const;
    Client* chooseClient(int nif) const;
    Employee* chooseEmployee(int nif) const;
    Order* chooseOrder(int id) const;

    /**
     * Adds a new bakery to the company
     * @param bakery Bakery being added
     */
	void addBakery(Bakery * bakery);
    void addClient(Client* client);
    void addEmployee(Employee* employee);
    void addDeliveredOrder(Order* order);
    void addCompletedOrder(Order* order);
    void addIncompletedOrder(Order* order);
    void addProduct(Product* product);

    void addProductFrequency(ProductFrequency productFrequency);
    void addToEmployeeTable(Employee* employee);


    void removeEmployee(Employee* employee);
    void removeCompletedOrder(Order* order);
    void removeIncompletedOrder(Order* order);
    void removeProductFrequency(ProductFrequency productFrequency);
    void removeFromEmployeeTable(Employee* employee);

    //BST<ProductFrequency> Methods
    int frequencyOfProduct(Product* product);
    int frequencyOfCategory(string category);
    Product* mostRequestedProduct();
    Product* leastRequestedProduct();

    //Hash Table
    void increaseEmployeesSalaryByJob(int percentageIncreased, string job);
    vector<Employee*> searchEmployeesByJob(string job) const;

    /**
     * Returns the total money earned by a certain bakery
     * @param bakery The bakery we want to analise
     * @return The total money earned by a certain bakery
     */
    int totalMoneyEarnedFromBakery(Bakery* bakery);
    /**
     * This method will calculate how many orders a certain bakery has delivered
     * @param bakery The bakery we want to analise
     * @return How many orders this bakery has delivered
     */
    int totalOrdersDeliveredFromBakery(Bakery* bakery);
    /**
     * Gives the total money earned from a certain product category
     * @param category The category of the product (only accpets "Beverage", "Bread" or "Cake")
     * @return The total money earned from that product category
     */
    double totalMoneyEarnedByCategory(string category);
    /**
     * Returns the total quantity sold of a certain product category
     * @param category The category of the product (only accpets "Beverage", "Bread" or "Cake")
     * @return The total quantity sold of that product category
     */
    int totalQuantitySoldByCategory(string category);

    int totalNumberOfClients();
    int totalNumberOfPremiumClients();
    int totalNumberOfNormalClients();

    /**
     * This will print the full history of the client
     * @param client The client we're analising
     */
    void printClientHistory(Client* client);

};



/***************** BAKERY EXCEPTIONS ****************/

/**
 * Exception when a certain bakery isn't found
 */
class BakeryNotFound {
	string address;
public:
	BakeryNotFound(string address): address(address){
	    cout << "\nSorry, but we couldn't find the bakery with address: " << address;
	}
    BakeryNotFound(Bakery* bakery): address(bakery->getAddress()){
        cout << "\nSorry, but we couldn't find the bakery with address: " << address;
	}
};

/**
 * Exception when a bakery already exists
 */
class AlreadyExistingBakery {
	string address;
public:
    AlreadyExistingBakery(Bakery* bakery): address(bakery->getAddress()){
	    cout << "\nSorry, looks like the bakery from the address " << bakery->getAddress() << " already exists\n";
	}
};

class ThisBakeryDoesntHaveAnyCooker {
    string bakery_address;
public:
    ThisBakeryDoesntHaveAnyCooker(Bakery* bakery) : bakery_address(bakery->getAddress()) {
        cout << "\nOh, we couldn't receive your order, the bakery with address " << bakery_address <<
        " has no cookers to prepare it\n";
    }
};

class InvalidCategory {
    string category;
public:
    InvalidCategory(string category) : category(category) {
        cout << "\nThe category " << category << " is invalid!\n";
    }
};

#endif /* BAKERY_H_ */