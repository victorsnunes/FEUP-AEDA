#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <fstream>
#include "bakery.h"
#include "client.h"
#include "employee.h"
#include "order.h"
#include "product.h"
#include "date.h"
#include "menu.h"

using testing::Eq;

//THESE TESTS ARE MEANT TO BE TESTED INDIVIDUALLY

/*
TEST(test, BST_ProductFrequency) {

    Company* AnthonyCenter = new Company();

    Product* cocaCola = new Beverage("Coca-Cola", 300, 4);
    Product* paoDeForma = new Bread("Pão de Forma", "pequeno", 3);
    Product* boloPaoDeLo = new Cake("Pão de Ló", 5, "massa de pão de ló");
    Product* paozinho = new Bread("Pãozinho", "pequeno", 1);

    Package* p1 = new Package(cocaCola, 5);     //Costs 20 euros
    Package* p2 = new Package(paoDeForma, 9);   //Costs 27 euros
    Package* p3 = new Package(boloPaoDeLo, 2);  //Costs 62 euros
    Package* p4 = new Package(paozinho, 3);     //Costs 3 euros

    //ORDER 1: Packages of Coca Cola and Pao de Forma
    Order* order = new Order();
    order->addPackage(p1);
    order->addPackage(p2);

    //ORDER 2: Packages of Pao de Forma e Bolo Pao de Lo
    Order* order2 = new Order();
    order2->addPackage(p2);
    order2->addPackage(p3);

    //ORDER 3: Packages of Coca Cola e Bolo Pao de Lo
    Order* order3 = new Order();
    order3->addPackage(p1);
    order3->addPackage(p3);

    //ORDER 4: Packages of Paozinho and Coca Cola
    Order* order4 = new Order();
    order4->addPackage(p4);
    order4->addPackage(p1);


    Client* victor = new Client("Victor", 25416);
    Client* manuel = new Client("Manuel", 5966);
    Bakery* padaria1 = new Bakery("Rua dos padeiros, 80", AnthonyCenter);
    Bakery* padaria2 = new Bakery("Rua das maravilhas, 60", AnthonyCenter);
    Employee* guilherme = new Employee("Guilherme", 779566);
    Employee* alexandre = new Employee("Alexandre", 964423);
    Employee* jose = new Employee("José", 1215469);

    padaria1->addEmployee(guilherme, 700, "deliveryman");
    padaria1->addEmployee(alexandre, 750, "cooker");
    padaria2->addEmployee(jose, 900, "cooker");

    //victor->makeNewOrder(order, padaria1);
    victor->makeNewOrder(order, padaria1, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one
    //victor->makeNewOrder(order2, padaria1);
    victor->makeNewOrder(order2, padaria1, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one
    //manuel->makeNewOrder(order3, padaria1);
    manuel->makeNewOrder(order3, padaria1, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one
    //victor->makeNewOrder(order4, padaria1);
    victor->makeNewOrder(order4, padaria2, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one


    EXPECT_EQ(3, AnthonyCenter->frequencyOfProduct(cocaCola));
    EXPECT_EQ(1, AnthonyCenter->frequencyOfProduct(paozinho));

    EXPECT_EQ(3, AnthonyCenter->frequencyOfCategory("bread"));

    EXPECT_EQ(cocaCola, AnthonyCenter->mostRequestedProduct());
    EXPECT_EQ(paozinho, AnthonyCenter->leastRequestedProduct());

}
*/


/*
TEST(test, HashTable_Employees) {

    Company* AnthonyCenter = new Company();


    Bakery* padaria1 = new Bakery("Rua dos padeiros, 80", AnthonyCenter);
    Bakery* padaria2 = new Bakery("Rua das maravilhas, 60", AnthonyCenter);
    Employee* guilherme = new Employee("Guilherme", 779566);
    Employee* alexandre = new Employee("Alexandre", 964423);
    Employee* filipe = new Employee("Filipe", 451206);
    Employee* lucas = new Employee("Lucas", 84561230);
    Employee* jose = new Employee("José", 1215469);
    Employee* joao = new Employee("João", 485162);
    Employee* ana = new Employee("Ana", 4561205);

    padaria1->addEmployee(guilherme, 700, "deliveryman");
    padaria1->addEmployee(alexandre, 750, "cooker");
    padaria1->addEmployee(filipe, 750, "cooker");
    padaria1->addEmployee(lucas, 650, "cleaner");

    padaria2->addEmployee(jose, 900, "cooker");
    padaria2->addEmployee(joao, 800, "deliveryman");
    padaria2->addEmployee(ana, 850, "deliveryman");

    vector<Employee*> deliverymen = {ana, guilherme, joao};
    vector<Employee*> cookers = {alexandre, filipe, jose};
    vector<Employee*> cleaners = {lucas};

    EXPECT_EQ(deliverymen, AnthonyCenter->searchEmployeesByJob("deliveryman"));
    EXPECT_EQ(cookers, AnthonyCenter->searchEmployeesByJob("cooker"));
    EXPECT_EQ(cleaners, AnthonyCenter->searchEmployeesByJob("cleaner"));


    int anaSalary = ana->getSalary();
    int joaoSalary = joao->getSalary();
    int guilhermeSalary = guilherme->getSalary();

    //Increasing 2% for all deliverymen that works in the company.
    AnthonyCenter->increaseEmployeesSalaryByJob(2, "deliveryman");

    anaSalary *= 1.02;
    joaoSalary *= 1.02;
    guilhermeSalary *= 1.02;

    EXPECT_EQ(anaSalary, ana->getSalary());
    EXPECT_EQ(joaoSalary, joao->getSalary());
    EXPECT_EQ(guilhermeSalary, guilherme->getSalary());

}
*/


TEST(test, Priority_queue) {

    Company* AnthonyCenter = new Company();

    Product* cocaCola = new Beverage("Coca-Cola", 300, 4);
    Product* paoDeForma = new Bread("Pão de Forma", "pequeno", 3);
    Product* boloPaoDeLo = new Cake("Pão de Ló", 5, "massa de pão de ló");
    Product* paozinho = new Bread("Pãozinho", "pequeno", 1);

    Package* p1 = new Package(cocaCola, 5);     //Costs 20 euros
    Package* p2 = new Package(paoDeForma, 9);   //Costs 27 euros
    Package* p3 = new Package(boloPaoDeLo, 2);  //Costs 62 euros
    Package* p4 = new Package(paozinho, 3);     //Costs 3 euros


    Order* order = new Order();      //Costs 47 euros
    order->addPackage(p1);
    order->addPackage(p2);

    Order* order2 = new Order();    //Costs 89 euros
    order2->addPackage(p2);
    order2->addPackage(p3);

    Order* order3 = new Order();    //Costs 82 euros
    order3->addPackage(p1);
    order3->addPackage(p3);

    Order* order4 = new Order();    //Costs 23 euros
    order4->addPackage(p4);
    order4->addPackage(p1);

    Order* order5 = new Order();    //Costs 40 euros
    order5->addPackage(p1);
    order5->addPackage(p1);

    Order* order6 = new Order();    //Costs 65 euros
    order6->addPackage(p4);
    order6->addPackage(p3);


    Client* victor = new Client("Victor", 25415216);
    Client* pedro = new Client("Pedro", 78946127);
    Client* rui = new Client("Rui", 135426710);
    Client* henrique = new Client("Henrique", 1380561);
    Client* manuel = new Client("Manuel", 5966);

    Bakery* padaria1 = new Bakery("Rua dos padeiros, 80", AnthonyCenter);
    Bakery* padaria2 = new Bakery("Rua das maravilhas, 60", AnthonyCenter);

    Employee* guilherme = new Employee("Guilherme", 779566);
    Employee* alexandre = new Employee("Alexandre", 964423);
    Employee* filipe = new Employee("Filipe", 451206);
    Employee* lucas = new Employee("Lucas", 84561230);
    Employee* jose = new Employee("José", 1215469);
    Employee* joao = new Employee("João", 485162);
    Employee* ana = new Employee("Ana", 4561205);

    padaria1->addEmployee(guilherme, 700, "deliveryman");
    padaria1->addEmployee(alexandre, 750, "cooker");
    padaria1->addEmployee(filipe, 750, "cooker");
    padaria1->addEmployee(lucas, 650, "cleaner");

    padaria2->addEmployee(jose, 900, "cooker");
    padaria2->addEmployee(joao, 800, "deliveryman");
    padaria2->addEmployee(ana, 850, "deliveryman");


    //victor->makeNewOrder(order, padaria1);
    victor->makeNewOrder(order, padaria1, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one
    //manuel->makeNewOrder(order2, padaria1);
    manuel->makeNewOrder(order2, padaria1, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one
    //victor->makeNewOrder(order3, padaria1);
    victor->makeNewOrder(order3, padaria1, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one
    //pedro->makeNewOrder(order4, padaria1);
    pedro->makeNewOrder(order4, padaria1, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one
    //rui->makeNewOrder(order5, padaria1);
    rui->makeNewOrder(order5, padaria1, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one
    //henrique->makeNewOrder(order6, padaria1);
    henrique->makeNewOrder(order6, padaria1, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one
    //henrique->makeNewOrder(order6, padaria1);

    victor->setOpinionValue(5);
    pedro->setOpinionValue(5);
    manuel->setOpinionValue(4);
    rui->setOpinionValue(3);
    henrique->setOpinionValue(2);


    //padaria1->deliverOrders(guilherme);
    padaria1->deliverOrders(guilherme, "fastfoward30min", "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one

    //padaria1->deliverOrders(guilherme);
    padaria1->deliverOrders(guilherme, "fastfoward30min", "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one



    Client* maria = new Client("Maria", 48513571);
    Client* joana = new Client("Joana", 123051);

    Order* order7 = new Order();    //Costs 30 euros
    order7->addPackage(p2);
    order7->addPackage(p4);

    Order* order8 = new Order();    //Costs 23 euros
    order8->addPackage(p1);
    order8->addPackage(p4);

    Order* order9 = new Order();    //Costs 3 euros
    order9->addPackage(p4);

    Order* order10 = new Order();    //Costs 6 euros
    order10->addPackage(p4);
    order10->addPackage(p4);

    Order* order11 = new Order();    //Costs 3 euros
    order11->addPackage(p4);

    //victor->makeNewOrder(order7, padaria2);
    victor->makeNewOrder(order7, padaria2, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one
    //maria->makeNewOrder(order8, padaria2);
    maria->makeNewOrder(order8, padaria2, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one
    //maria->makeNewOrder(order9, padaria2);
    maria->makeNewOrder(order9, padaria2, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one
    //joana->makeNewOrder(order10, padaria2);
    joana->makeNewOrder(order10, padaria2, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one
    //joana->makeNewOrder(order11, padaria2);
    joana->makeNewOrder(order11, padaria2, "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one


    //padaria2->deliverOrders(ana);
    padaria2->deliverOrders(ana, "fastfoward30min", "alwaysOpen"); //If bakery is closed, comment the line above and uncomment this one

}

