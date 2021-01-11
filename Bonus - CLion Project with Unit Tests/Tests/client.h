#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include "bakery.h"
#include "order.h"

using namespace std;

class Bakery;
class NoRepeating;

/**
 * Client Class
 * This class represents a client object
 */
class Client {

    const int nif;
    /**
     * Points of the client
     */
    int points = 0;
    string name;
    /**
     * True if he's opinion is positive or false if it's negative
     */
    bool opinion;
    double opinionValue;
    /**
     * True if he's a premium client or false if he's a normal one
     */
    bool premium = false;
    int pastDiscounts = 0;
    /**
     * The orders which the client hasn't received yet
     */
    vector<Order *> currentOrders;
    /**
     * The orders which the client has already received
     */
    vector<Order *> receivedOrders;

public:

    Client(string name, int nif, string type = "normal");


    int getNif() const;
    string getName() const;
    bool getOpinion() const;
    double getOpinionValue() const;
    bool getPremium() const;
    int getPastDiscounts() const;
    int getPoints() const;
    vector<Order *> getReceivedOrders() const;
    vector<Order *> getCurrentOrders() const;
    string getInfo() const;

    void setName(string name);
    void setPremium(bool premium);
    void setPastDiscounts(int pd);
    void setPoints(int points);
    void setOpinionValue(double value);

    /**
     * The client makes an order and send it to the bakery that he chooses
     * @param order The client's order
     * @param bakery The bakery which the client has chosen
     * @param mode For debugging and testing purposes, this method accepts the mode "alwaysOpen", that allowes the client to request an order to a bakery any time
     */
    void makeNewOrder(Order* order, Bakery* bakery, string mode = "normal");

    /**
     * The client decides to go to the bakery to pick up his order(s).
     * But if he goes in a time when the bakery is closed, or his order isn't ready yet, or he didn't even order anyting, he won't get nothing
     * @param bakery The bakery which the client is going to
     * @param mode For testing, this argument accepts "fastfoward30min" mode, which increases 30 minutes of the current time, so that we can see if the client is able to pick up his order
     * @param mode2 For testing, this argument accepts "alwaysOpen" mode, which set the time and date to a relugar working time of the bakery
     */
    void goToTheBakeryToPickUpOrder(Bakery* bakery, string mode = "normal", string mode2 = "normal");

    /**
     * Checks if the client has discounts and how much
     * @return How much discount the client has, including 0 for no discount
     */
    int hasDiscount();
    /**
     * Client receives his order from the bakery
     * In this method, the client also gives his rating to the order he's just received
     * @param order Order he's just received
     */
    void addReceivedOrder(Order* order);
    /**
     * This method recalculates the opinion of a client, based in the rating of his received order.
     * This method is always called when the client receives a new order ( void addReceivedOrder(Order* order) ).
     */
    void checkOpinion();
    /**
     * Erases a certain order from the currentOrder vector
     * @param order The order to be removed
     */
    void eraseCurrentOrder(Order* order);
    /**
     * Checks if a certain order exists in the current or received orders by the client
     * @param order The order we're searching for
     * @return true if we've found it, or false otherwise
     */
    bool searchOrder(Order* order);
    /**
     * Static method for all clients
     * This method generates a random number from 0 to 5, which will be the clients rating in a specific order
     * @return The random number generated
     */
    static int clientFeedback();
    /**
     * Operator to check if two clients are the same
     * @param client The second client
     * @return true if they are the same, false otherwise
     */
    bool operator ==(Client client) const;
};

/***************** CLIENTS EXCEPTIONS ****************/

/**
 * Expection when a client doesn't exist
 */
class ClientNotFound {
	int nif;
	string name;
public:
	ClientNotFound(int nif) : nif(nif) {
        cout << "\nSorry, but we couldn't find the client whose nif is " << nif;
	}
    ClientNotFound(Client* client) : nif(client->getNif()), name(client->getName()) {
        cout << "\nSorry, we didn't find any client with Nif " << this->nif
             << " and called " << this->name << endl;
    }
};

/**
 * Expection when a client already exists
 */
class AlreadyExistingClient{
    int nif;
public:
    AlreadyExistingClient(int nif) : nif(nif) {
        cout << "There's already a client here with nif " << nif << endl;
    }
};

#endif /* CLIENT_H_ */