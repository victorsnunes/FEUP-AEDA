#ifndef PRODUCT_H_
#define PRODUCT_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

/**
 * Product Class
 * This class represents a generic product class, which will be the parent of all the other specific products
 */
class Product{
    string name;
    string category = "generic";
    double price;
    /**
     * The global quantity sold by generic products
     */
    static int quantitySold;
    /**
     * The global money earned by generic products
     */
    static double moneyEarnedProduct;
public:
    /**
     * Basic Constructor
     * @param name The name of the product
     * @param price The price of the product
     */
    Product(string name, double price = 0);
    Product(){this->name = ""; this->price = 0;};   //never used

    string getName() const;
    string getCategory() const;
    double getPrice() const;
    /**
     * Information (All child classes will have to redefine this)
     * @return Outputs a string with basic informations of the product
     */
    virtual string getInfo() const;
    void setName(string name);
    void setCategory(string category);
    void setPrice(double price);
    /**
     * This method increases the quantity sold of a certain product
     * @param quantity Value that will increase the previous one
     */
    virtual void productSold(int quantity);
    /**
     * This method increases the money earned by a certain product
     * @param money Value that will increase the previous one
     */
    virtual void moneyEarned(double money);
};

/**
 * Beverage Class
 * A child class of Product
 */
class Beverage: public Product{
    int size;
    /**
     * The global quantity sold by this category of product
     */
    static int quantitySold;
    /**
     * The global money earned by this category of product
     */
    static double moneyEarnedBeverage;
public:
    /**
     * Beverage Constructor
     * @param name Name of the beverage
     * @param size The size of the beverage (in mililiters)
     * @param price The price of the beverage
     */
    Beverage(string name, int size, double price = 0);
    int getSize() const;
    string getInfo() const;
    static int getTotalBeverageSold();
    static double getTotalMoneyBeverage();
    void setSize(int size);
    /**
     * This method increases the quantity sold of this category of product
     * @param quantity Value that will increase the previous one
     */
    void productSold(int quantity) override;
    /**
     * This method increases the money earned by this category of product
     * @param money Value that will increase the previous one
     */
    void moneyEarned(double money) override;
};

/**
 * Bread Class
 * A child class of Product
 */
class Bread: public Product{
    string size;
    /**
     * The global quantity sold by this category of product
     */

    static int quantitySold;
    /**
     * The global money earned by this category of product
     */
    static double moneyEarnedBread;
public:
    Bread(string name, string size, double price = 0);
    string getSize() const;
    static int getTotalBreadSold();
    static double getTotalMoneyBread();
    string getInfo() const override;
    void setSize(string size);
    /**
     * This method increases the quantity sold of this category of product
     * @param quantity Value that will increase the previous one
     */
    void productSold(int quantity) override;
    /**
     * This method increases the money earned by this category of product
     * @param money Value that will increase the previous one
     */
    void moneyEarned(double money) override;
};

/**
 * Cake Class
 * A child class of Product
 */
class Cake: public Product{
    vector<string> layers;
    double weight;
    string nameBirthday;
    int years;
    bool isBirthday = false;
    static double pricePerKg;
    /**
     * The global quantity sold by this category of product
     */
    static int quantitySold;
    /**
     * The global money earned by this category of product
     */
    static double moneyEarnedCake;
public:
    Cake(string name, double weight, string nameBirthday, int years, string layer1, string layer2 = "");
    Cake(string name, double weight, string layer1, string layer2 = "");
    vector<string> getLayers() const;
    string getNameBirthday() const;
    int getYears() const;
    double getPricePerKg() const;
    double getWeight() const;
    static int getTotalCakeSold();
    static double getTotalMoneyCake();
    string getInfo() const override;
    void setLayers(vector<string> layers);
    void setNameBirthday(string name);
    void setYears(int years);
    void setPricePerKG(double price);
    void setWeight(double weight);
    /**
     * This is an auxiliar function, to calculate the price of the cake, based on the layers chosen
     * @param weight The weight of the cake
     * @param layers The layers of the cake
     * @return The price of the cake
     */
    double calculatePrice(double weight,vector<string> layers);       //price per kg, layers extra
    /**
     * This method increases the quantity sold of this category of product
     * @param quantity Value that will increase the previous one
     */
    void productSold(int quantity) override;
    /**
     * This method increases the money earned by this category of product
     * @param money Value that will increase the previous one
     */
    void moneyEarned(double money) override;
};

/**
 * Package Class
 * A package is a pack with a certain Quantity of a certain Product
 */
class Package{
    Product* product;
    int quantity;
    double price;
public:
    /**
     * Package Constructor
     * @param product Product inside the package
     * @param quantity Quantity of this product
     */
    Package(Product* product, int quantity);
    Package(Beverage* beverage, int quantity);
    Package(Bread* bread, int quantity);
    int getQuantity() const;
    Product* getProduct() const;
    double getPrice() const;
    string getInfo() const;
    void setQuantity(int quantity);
    void setProduct(Product* product);
};

/**
 * ProductFrequency Class
 * This class stores the frenquency with which each product is ordered by the clients
 */
class ProductFrequency {
    Product* product;
    int frequency;
public:
    ProductFrequency() : frequency(0) { product = new Product(""); }
    ProductFrequency(Product* p) : product(p) { frequency = 0; }
    ProductFrequency(Product* p, int f) : product(p), frequency(f) {}
    Product* getProduct() const { return product; }
    int getFrequency() const { return frequency; }
    ProductFrequency& operator++() { frequency++; return *this; }
    bool operator==(const ProductFrequency& pf) const;
    bool operator<(const ProductFrequency& pf) const;
};

/***************** EXCEPTIONS ****************/


/**
 * This exception is throw when a layer doesn't exist
 */
class CakeLayerDoesntExist {
    string layer;
public:
    CakeLayerDoesntExist(string layer) : layer(layer) {
        cout << "\nSorry, we don't have cake layer of '" << this->layer
             << "'.\nHere, we only sell: 'crocante', 'massa folhada' and 'massa de pão de ló'\n";
    }
};

/**
 * Exception when a Product isn't found
 */
class ProductNotFound {
	string name;
public:
	ProductNotFound(string name): name(name){
	    cout << "\nSorry, but we couldn't find a product called " << this->name << ".\n";
	}
    ProductNotFound(Product* product): name(product->getName()){
        cout << "\nSorry, but we couldn't find a product called " << this->name << ".\n";
	}
};

/**
 * Exception when a Product already exists
 */
class AlreadyExistingProduct{
    string name;
public:
    AlreadyExistingProduct(string name) : name(name) {
        cout << "Hey, the product " << name << " already exists!\n";
    }
    AlreadyExistingProduct(Product* product) : name(product->getName()) {
        cout << "Hey, the product " << name << " already exists!\n";
    }
};



/**
 * Exception when a ProductFrequency isn't found
 */
class ProductFrequencyNotFound {
    string name;
public:
    ProductFrequencyNotFound() {
        cout << "\nSorry, but we couldn't find this product frequency.\n";
    }
    ProductFrequencyNotFound(string name) : name(name) {
        cout << "\nSorry, but we couldn't find a product frequency called " << this->name << ".\n";
    }
    ProductFrequencyNotFound(ProductFrequency pf) : name(pf.getProduct()->getName()) {
        cout << "\nSorry, but we couldn't find a product called " << this->name << ".\n";
    }
};

/**
 * Exception when a ProductFrequency already exists
 */
class AlreadyExistingProductFrequency {
    string name;
public:
    AlreadyExistingProductFrequency(string name) : name(name) {
        cout << "Hey, the product frequency " << name << " already exists!\n";
    }
    AlreadyExistingProductFrequency(ProductFrequency pf) : name(pf.getProduct()->getName()) {
        cout << "Hey, the product frequency " << name << " already exists!\n";
    }
};


#endif /* PRODUCT_H_ */