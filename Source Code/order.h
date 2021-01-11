#ifndef ORDER_H_
#define ORDER_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "client.h"
#include "employee.h"
#include "product.h"
#include "date.h"
#include "AuxFunctions.h"

using namespace std;

class Client;
class Employee;

/**
 * Order Class
 * An order is a group of package, that a certain client requests for the bakery, and will be done by an employee
 */
class Order {
    int id;
    Date dateToPickUp;
    Time timeToPickUp;
    vector<Package *> purchase;
    int hadDiscount = 0;
    double price = 0.0;
    int rating;
    string pickUpAddress = "";
    Client* client;
    static int nextId;

public:
    /**
     * Order Constructor.
     * This will create an empty order object, that we are going to add the packages the client wants later on
     */
    Order();
    Order(const Order &o);


    /**
     * Vector of the packages of the order
     * @return Vector of the packages of the order
     */
    vector<Package *> getPurchase() const;
    int getId() const;
    double getPrice() const;
    /**
     * Returns how much discount this order had, including zero for no discount
     * @return The discount
     */
    int getHadDiscount() const;
    /**
     * Returns the rating that the client gave in this order
     * @return The rating that the client gave in this order
     */
    int getRating() const;
    /**
     * Returns the address which this order will be picked up
     * @return The address which this order will be picked up
     */
    string getPickUpAddress() const;
    /**
     * Returns the date when the order is ready to be picked up by the client
     * @return The date when the order is ready to be picked up by the client
     */
    Date getDateToPickUp() const;
    /**
     * Returns the time when the order is ready to be picked up by the client
     * @return The time when the order is ready to be picked up by the client
     */
    Time getTimeToPickUp() const;
    /**
     * Returns the  client who ordered it
     * @return The  client who ordered it
     */
    Client* getClient() const;
    /**
     * Returns basic Information about the order
     * @return Basic Information about the order
     */
    string getInfo() const;


    void setRating(int rating);
    void setHadDiscount(int discount);
    void setPickUpAddress(string address);
    void setPrice(double price);
    void setClient(Client* c);
    void setDateToPickUp(Date date);
    void setTimeToPickUp(Time time);

    /**
     * Adds a new package to the order, and also increses its price
     * @param purchase the package being added
     */
    void addPackage(Package* purchase);
    /**
     * This method sees the date and time now, that the order is being requested to the bakery, and calculates the date and time to pick it up
     * And stores then in their right attributes of the order object
     * @param mode For debugging and testing purposes, the mode can accept "alwaysOpen", so that it will calculate the date and time based in the "alwaysOpen" default value
     */
    void sendOrderToBakery(string mode = "normal");
    /**
     * This method increases the money earned by a certain product, now that we now if the client had a discount of not, and stores it in the static variable of the category product class.
     * It also increases the quantity of the category!
     * @param discount
     */
    void productMoneyEarned(int discount);
    bool operator < (const Order& order) const;
    bool operator == (const Order& order) const;

};

/**
 * Delivery Order Class
 * This class is for the orders that are going to be delivered by the deliverymen.
 * It also has the operator< implemented for the use of the priority queue
 */
class DeliveryOrder {
    Order* order;
    Employee* cookerWhoMadeIt;
public:
    DeliveryOrder(Order* o, Employee* cooker) : order(o), cookerWhoMadeIt(cooker) {}
    bool operator<(const DeliveryOrder& do2) const;
    Order* getOrder() const { return order; }
    Employee* getCookerWhoMadeIt() const { return cookerWhoMadeIt; }
};

/***************** ORDERS EXCEPTIONS ****************/

/**
 * Exception when a order doesn't exist
 */
class OrderNotFound {
    Order* order;
    int id;
public:
    OrderNotFound(Order* order);
    OrderNotFound(int id) : id(id) {
        cout << "\nSorry, we couldn't find the order with id " << id << endl;
    }
};

class OrderBeingResent {
    Order* order;
public:
    OrderBeingResent(Order* order) : order(order) {
        cout << "\nSorry, you can't resend the same order. Create another one.\n";
    }
};

/**
 * Exception when a order is being made in a moment where the bakery is closed
 */
class BakeryClosed {
    Date date;
    Time time;
public:
    BakeryClosed(Date date, Time time) : date(date), time(time) {
        cout << "\nSorry, we're closed. We only work from 7:00 to 20:00, from Monday to Friday\n";
    }
    Date getDate() {return date;}
    Time getTime() {return time;}
};


#endif /* ORDER_H_ */