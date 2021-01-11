#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "order.h"
#include "product.h"
#include "client.h"

using namespace std;

class Order;
class DeliveryOrder;
class Product;
class Company;
class Client;
class NoRepeating;

/**
 * This class represents an employee object. It stores the name, nif, salary, address of the bakery he works
 * and the incompleted and completed (but not yet delivered) orders of this employee
 */
class Employee {

protected:
	const int nif;
	string name;
    int salary = 0;
    string workingAddress = "none";
    string job = "none";
    vector<Order*> incompletedOrders;           //Orders that the cooker is still preparing
    vector<Order*> completedOrders;             //Orders that the cooker has already prepared
    priority_queue<DeliveryOrder> ordersToDeliver;     //Orders for the deliveryman to deliver

public:
    /**
     * Employee basic constructor
     * @param name Name of the employee
     * @param nif Nif of the employee
     */
	Employee(string name, int nif);

	int getNif() const;
	string getName() const;
	int getSalary() const;
	string getWorkingAddress() const;
    string getJob() const;
	/**
	 * Vector of Incompleted Orders
	 * @return Returns the vector of the Orders that the employee is still working on
	 */
	vector<Order*> getIncompletedOrders() const;
    /**
     * Vector of Completed Orders (Concluded but not delivered)
     * @return Returns the vector of the Orders that the employee has already concluded
     */
    vector<Order*> getCompletedOrders() const;
    /**
     * Priority queue of orders to deliver (for deliverymen)
     * @return Returns a priority queue of the order that are going to be deliver by this employee
     */
    priority_queue<DeliveryOrder> getOrdersToDeliver() const;
    /**
     * Basic Information
     * @return String with basic informations about the employee
     */
	string getInfo() const;

	void setName(string name);
	void setSalary(int salary);
	void setWorkingAddress(string address);
    void setJob(string job);

    /**
     * Adds a new delivery order to be delivered
     * @param deliveryOrder The new delivery order to be delivered
     */
    void addOrderToDeliver(DeliveryOrder deliveryOrder);
    /**
     * Pops a deliver order from the priority queue and returns it
     * @return The deliver order just popped out
     */
    DeliveryOrder popOrderToDeliver();


	/**
	 * New order is added to the vector of incompleted orders of the employee
	 * @param order The new order added
	 */
	void newOrder(Company* company, Order *order);
	/**
	 * Refreshs the incompleted orders of the employee, based on the current time, and move the concluded order (those whose reached or passed the pick up time expected) to the completed orders vector
	 * @param company The company of Anthony
	 * @param mode For testing, this argument accepts "fastfoward30min" mode, which increases 30 minutes of the current time, so that we can see the new orders being concluded by the employee
     * @param mode2 For testing, this argument accepts "alwaysOpen" mode, which set the time and date to a regular working time of the bakery
	 */
	void refresh(Company* company, string mode = "normal", string mode2 = "normal");
	/**
	 * The employee gives the concluded order(s) of the current client, adding it to the client's received orders vector
	 * @param company The company of Anthony
	 * @param client The client asking for his order(s)
	 * @return How many orders the client has received, including zero for nothing received
	 */
    int giveOrder(Company* company, Client* client);
    /**
     * The deliveryman deliver the order(s) for this client, adding it to the client's received orders vector
     * @param company The company of Anthony
     * @param client The client asking for his order(s)
     * @return How many orders the client has received, including zero for nothing received
     */
    int giveDeliveredOrder(Company* company, Client* client);
    /**
     * Erases an order from the incompleted order vector of this employee
     * @param order Order we want to erase
     */
    void eraseIncompletedOrder(Order* order);
    /**
     * Erases an order from the completed order vector of this employee
     * @param order Order we want to erase
     */
    void eraseCompletedOrder(Order* order);
    /**
     * An employee is equal to a integer if that integer is his nif
     * @param nif Integer we want to compare
     * @return True if the integer is equal to the employee's nif, false otherwise
     */
	bool operator == (int nif) const;
	/**
	 * An employee is less than another one when his name is less than the other one's name
	 * @param e The second employee
	 * @return True if his name is less than the second employee's name, false otherwise
	 */
	bool operator < (Employee & e) const;
    /**
     * Checks if two employees are the same person
     * @param employee Second employee
     * @return true if the are the same, false otherwise
     */
    bool operator ==(const Employee& employee) const;
};


/***************** EXCEPTIONS ****************/

/**
 * Exception throw when a employee tries to work in more than one bakery
 */
class EmployeeAlreadyWorks {
    Employee* employee;
public:
    EmployeeAlreadyWorks(Employee* employee) : employee(employee) {
        cout << "\nHey, hold on " << employee->getName() << "!\n";
        cout << "You already work at " << employee->getWorkingAddress() << ", remember ?\n";
        cout << "You can't work in two bakeries at the same time.\n";
    }
};

/**
 * Exception when a employee is not found
 */
class EmployeeNotFound {
	int nif;
	string name;
public:
    /**
     * Constructor that receives the nif of the employee that wasn't found
     * @param nif The nif of the employee that wasn't found
     */
	EmployeeNotFound(int nif) : nif(nif) {
	    cout << "\nSorry, we didn't find any employee with Nif " << this->nif << endl;
	}
    EmployeeNotFound(Employee* employee) : name(employee->getName()), nif(employee->getNif()) {
        cout << "\nSorry, we didn't find any employee with Nif " << this->nif
                << " and called " << this->name << endl;
	}
};

/**
 * Exception when a employee already exists
 */
class AlreadyExistingEmployee{
    int nif;    
    string name;
public:
    /**
     * Constructor that receives the nif of the employee that already exists
     * @param nif The nif of the employee that already exists
     */
    AlreadyExistingEmployee(int nif) : nif(nif) {
        cout << "\nSorry, looks like there's already a employee with Nif " << this->nif << endl;
    }
    AlreadyExistingEmployee(Employee* employee) : name(employee->getName()), nif(employee->getNif()) {
        cout << "\nSorry, looks like there's already a employee with Nif " << this->nif
                << " and called " << this->name << endl;
    }
};

/**
 * Exception when a employee is asked to deliver orders but he's not a deliveryman
 */
class IAmNotADeliveryman {
    int nif;
    string name;
public:
    IAmNotADeliveryman(Employee* e) : nif(e->getNif()), name(e->getName()) {
        cout << "\nThe employee " << name << ", with nif " << nif << ", is not a deliveryman!\n";
    }
};
#endif /* EMPLOYEE_H_ */