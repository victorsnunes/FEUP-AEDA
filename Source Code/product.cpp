#include "product.h"

int Product::quantitySold = 0;
int Beverage::quantitySold = 0;
int Bread::quantitySold = 0;
int Cake::quantitySold = 0;

double Product::moneyEarnedProduct = 0;
double Beverage::moneyEarnedBeverage = 0;
double Bread::moneyEarnedBread = 0;
double Cake::moneyEarnedCake = 0;

double Cake::pricePerKg = 6.0;

Product::Product(string name, double price) {
    this->name = name;
    this->price = price;
}

string Product::getName() const {
    return name;
}

string Product::getCategory() const {
    return category;
}

void Product::setName(string name) {
    this->name = name;
}

void Product::setCategory(string category) {
    this->category = category;
}

double Product::getPrice() const {
    return price;
}

string Product::getInfo() const {

    stringstream os;
    os << "Name: " << name
       << "\nPrice: " << price << " euros\n";
    return os.str();
}

void Product::setPrice(double price) {
    this->price = price;
}

void Product::productSold(int quantity) {
    quantitySold += quantity;
}

void Product::moneyEarned(double money) {
    moneyEarnedProduct += money;
}

Beverage::Beverage(string name, int size, double price): Product(name, price) {
    this->size = size;
    this->setCategory("beverage");
}

int Beverage::getSize() const {
    return size;
}

string Beverage::getInfo() const {
    stringstream os;
    os << Product::getInfo();
    os << "Size: " << size << " ml\n";
    return os.str();
}

int Beverage::getTotalBeverageSold() {
    return quantitySold;
}

double Beverage::getTotalMoneyBeverage() {
    return moneyEarnedBeverage;
}

void Beverage::setSize(int size) {
    this->size = size;
}

void Beverage::productSold(int quantity) {
    quantitySold += quantity;
}

void Beverage::moneyEarned(double money) {
    moneyEarnedBeverage += money;
}

Bread::Bread(string name, string size, double price): Product(name, price) {
    this->size = size;
    this->setCategory("bread");
}

string Bread::getSize() const {
    return size;
}

int Bread::getTotalBreadSold() {
    return quantitySold;
}

double Bread::getTotalMoneyBread() {
    return moneyEarnedBread;
}

string Bread::getInfo() const {
    stringstream os;
    os << Product::getInfo();
    os << "Size: " << size << endl;
    return os.str();
}

void Bread::setSize(string size) {
    this->size = size;;
}

void Bread::productSold(int quantity) {
    quantitySold += quantity;
}

void Bread::moneyEarned(double money) {
    moneyEarnedBread += money;
}

Cake::Cake(string name, double weight, string nameBirthday, int years, string layer1, string layer2) : Product(name) {
	this->layers.push_back(layer1);
	this->layers.push_back(layer2);
	this->weight = weight;
    this->nameBirthday = nameBirthday;
    this->years = years;
    this->setPrice(calculatePrice(weight, this->layers));
    this->isBirthday = true;
    this->setCategory("cake");
}

Cake::Cake(string name, double weight, string layer1, string layer2) : Product(name) {
    this->weight = weight;
    (this->layers).push_back(layer1);
    if (layer2 == "")
        (this->layers).push_back(layer2);
    this->setPrice(calculatePrice(weight, this->layers));
    this->setCategory("cake");
}

vector<string> Cake::getLayers() const {
    return layers;
}

string Cake::getNameBirthday() const {
    return nameBirthday;
}

int Cake::getYears() const {
    return years;
}

double Cake::getPricePerKg() const {
    return pricePerKg;
}

double Cake::getWeight() const {
    return weight;
}

int Cake::getTotalCakeSold() {
    return quantitySold;
}

string Cake::getInfo() const {

    stringstream os;
    os << Product::getInfo();

    os << "Weight: " << this->getWeight() << " kg\n";

    os << "Layer 1: " << layers[0] << endl;
    if (layers[1] != "")
        os << "Layer 2: " << layers[1] << endl;
        
    if (isBirthday)
        os << "This cake is for the birthday of " << this->nameBirthday << ", making " << this->years << " years today!" << endl << endl;
    return os.str();
}

void Cake::setLayers(vector<string> layers) {
    this->layers = layers;
    this->setPrice(calculatePrice(this->weight, layers));
}

void Cake::setNameBirthday(string name) {
    this->nameBirthday = name;
}

void Cake::setYears(int years) {
    this->years = years;
}

void Cake::setPricePerKG(double price) {
    this->pricePerKg = price;
}

void Cake::setWeight(double weight) {
    this->weight = weight;
    this->setPrice(calculatePrice(weight, this->layers));
}

double Cake::calculatePrice(double weight, vector<string> layers) {

    double layers_cost = 0;     //Extra cost for special layers
    for(unsigned i = 0; i < layers.size(); i++){
        if(layers[i] == "crocante")
            layers_cost += 2.0;
        else if(layers[i] == "massa folhada")
            layers_cost += 1.0;
        else if(layers[i] == "massa de pão de ló")
            layers_cost += 1.0;
        else if (layers[i] == "")
            continue;
        else
            throw CakeLayerDoesntExist(layers[i]);
    }
    int price = weight *(pricePerKg) + layers_cost;     //pricePerKg is set to 6 by default
    return price;
}

void Cake::productSold(int quantity) {
    quantitySold += quantity;
}

double Cake::getTotalMoneyCake() {
    return moneyEarnedCake;
}

void Cake::moneyEarned(double money) {
    moneyEarnedCake += money;
}

Package::Package(Product* p, int q) {
    this->product = p;
    this->quantity = q;
    this->price = (product->getPrice() * this->quantity);
}

Package::Package(Beverage* p, int q) {
    this->product = p;
    this->quantity = q;
    p->productSold(q);
    this->price = (product->getPrice() * this->quantity);
}

Package::Package(Bread* p, int q) {
    this->product = p;
    this->quantity = q;
    p->productSold(q);
    this->price = (product->getPrice() * this->quantity);
}

int Package::getQuantity() const {
    return quantity;
}

Product* Package::getProduct() const {
    return product;
}

double Package::getPrice() const {
    return price;
}

string Package::getInfo() const {

    stringstream os;
    os << quantity << " units of " << (*product).getName() << endl;
    return os.str();
}

void Package::setQuantity(int quantity) {
    this->quantity = quantity;
}

void Package::setProduct(Product* product) {
    this->product = product;
}


bool ProductFrequency::operator==(const ProductFrequency& pf) const {
    return product->getName() == (pf.getProduct())->getName();
}

bool ProductFrequency::operator<(const ProductFrequency& pf) const {
    
    if (frequency == pf.getFrequency()) {

        if (product->getCategory() == pf.getProduct()->getCategory())
            return product->getName() < (pf.getProduct())->getName();

        return product->getCategory() < pf.getProduct()->getCategory();
    }   

    return frequency < pf.getFrequency();
}