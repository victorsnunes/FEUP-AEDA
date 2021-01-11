#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "bakery.h"
#include "AuxFunctions.h"

using namespace std;

void clearBuffer();
void menu(Company* c);
int showMenu();

/********** File Managing **********/

void fileManager(Company* c);

/********** Company Information **********/

void companyMenu(Company *c);
int showCompanyInformationOptions(Company *c);

/********** Bakery Information **********/

void bakeryMenu(Company *c);
int showBakeryOptions(Company *c);
void chooseBakery(Company *c);
void addBakery(Company *c);
void chooseBakeryMenu(Company *c, Bakery *b);
int showChooseBakeryOptions(Bakery *b);
void changeBakeryAddress(Company *c, Bakery *b);
void addEmployee(Company *c, Bakery *b);
void removeEmployee(Company *c, Bakery *b);
void deliverOrders(Company* c, Bakery* b);

//For file to use
void addBakery(Company* c, string address);
void changeBakeryAddress(Company* c, string oldAddress, string newAddress);
void addEmployee(Company* c, string address, string name, int nif, int salary, string job);
void removeEmployee(Company* c, string address, int nif);

/********** Client Information **********/

void clientMenu(Company *c);
int showClientOptions(Company *c);
void chooseClient(Company *c);
void addClient(Company *c);
void chooseClientMenu(Company *c, Client *cli);
int showChooseClientOptions(Company *c, Client *cli);
void togglePremiumClient(Company *c, Client *cli);
void makeOrder(Company *c, Client *cli);
void goToBakery(Company *c, Client *cli);

//For file to use
void addClient(Company* c, int nif, string name, string premium);
void togglePremiumClient(Company* c, int nif);
void makeOrder(Company* c, int nifClient, string address, string productName1, int quantity1, string productName2="", int quantity2=0, string productName3="", int quantity3=0);
void goToBakery(Company* c, int nifClient, string address);


/********** Order Information **********/

void orderMenu(Company *c);
int showOrderOptions(Company *c);
void chooseOrder(Company *c);

/********** Employee Information **********/

void employeesMenu(Company *c);
int showEmployeeOptions(Company *c);
void chooseEmployee(Company *c);
void addEmployee(Company *c);
void chooseEmployeeMenu(Company *c, Employee *e);
int showChooseEmployeeOptions(Company *c, Employee *e);
void changeSalary(Company *c, Employee *e);
int getSalary(vector<Employee *> employees);
void increaseEmployeeByJob(Company* c);
void showEmployeesByJob(Company* c);

//For file to use
void changeSalary(Company* c, int salary, int nifEmployee);

/********** Product Information **********/

void productsMenu(Company *c);
int showProductOptions(Company *c);
void addProduct(Company *c);

//For file to use
void addProduct(Company* c, string type, string name, double price, int sizeBeverage, string sizeBread);

#endif /* MENU_H_ */