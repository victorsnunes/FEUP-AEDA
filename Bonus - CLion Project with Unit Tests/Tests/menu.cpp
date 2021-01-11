#include "menu.h"

void clearBuffer() {
	cin.clear();
	cin.ignore(1000, '\n');
}

/********** File Managing **********/

void fileManager(Company* c) {

	ifstream file("register.txt");
	
	if (file.fail())
		return;

	string l;
	while (getline(file, l)) {

		stringstream line(l);
		string mode;
		line >> mode;


		if (mode == "addBakery") {
			string address;
			line >> address;

			addBakery(c, address);
		}
		if (mode == "changeBakeryAddress") {
			string oldAddress;
			line >> oldAddress;
			string newAddress;
			line >> newAddress;

			changeBakeryAddress(c, oldAddress, newAddress);
		}
		if (mode == "addEmployee") {
			string address;
			line >> address;
			string name;
			line >> name;
			string nifString;
			line >> nifString;
			int nif = stoi(nifString);
			string salaryString;
			line >> salaryString;
			int salary = stoi(salaryString);
            string job;
            line >> job;

			addEmployee(c, address, name, nif, salary, job);
		}
		if (mode == "removeEmployee") {
			string address;
			line >> address;
			string nifString;
			line >> nifString;
			int nif = stoi(nifString);

			removeEmployee(c, address, nif);
		}
		if (mode == "addClient") {
			string nifString;
			line >> nifString;
			int nif = stoi(nifString);
			string name;
			line >> name;
			string premium;
			line >> premium;

			addClient(c, nif, name, premium);
		}
		if (mode == "togglePremiumClient") {
			string nifString;
			line >> nifString;
			int nif = stoi(nifString);

			togglePremiumClient(c, nif);
		}
		if (mode == "makeOrder") {
			string nifString;
			line >> nifString;
			int nifClient = stoi(nifString);
			string address;
			line >> address;
			string productName1;
			line >> productName1;
			string qquantity1;
			line >> qquantity1;
			int quantity1 = stoi(qquantity1);

			string productName2 = "none";
			string qquantity2;
			int quantity2 = 0;
			string productName3 = "none";
			string qquantity3;
			int quantity3 = 0;

			int tmp = 0;
			string tmp2;
			while (line >> tmp2) {

				if (tmp == 0)
					productName2 = tmp2;

				if (tmp == 1) {
					qquantity2 = tmp2;
					quantity2 = stoi(qquantity2);
				}

				if (tmp == 2)
					productName3 = tmp2;

				if (tmp == 3) {
					qquantity3 = tmp2;
					quantity3 = stoi(qquantity3);
				}

				tmp++;
			}

			makeOrder(c, nifClient, address, productName1, quantity1, productName2, quantity2, productName3, quantity3);
		}
		if (mode == "goToBakery") {
			string nifString;
			line >> nifString;
			int nifClient = stoi(nifString);
			string address;
			line >> address;

			goToBakery(c, nifClient, address);
		}
		if (mode == "changeSalary") {
			string salaryString;
			line >> salaryString;
			int salary = stoi(salaryString);
			string nifString;
			line >> nifString;
			int nifEmployee = stoi(nifString);

			changeSalary(c, salary, nifEmployee);
		}
		if (mode == "addProduct") {
			string type;
			line >> type;
			string name;
			line >> name;
			string priceString;
			line >> priceString;
			double price = stod(priceString);
			string sizeBeverageString;
			line >> sizeBeverageString;
			int sizeBeverage = stoi(sizeBeverageString);
			string sizeBread;
			line >> sizeBread;

			addProduct(c, type, name, price, sizeBeverage, sizeBread);
		}
			

	}

	file.close();
}

/********** Company Information **********/

void menu(Company* c) {

    Date date;
	int menuOption;

	cout << date.getExtendedDate() << endl;

	do {
		menuOption = showMenu();
		switch (menuOption){
			case 1:
				companyMenu(c);
				break;
			case 2:
				bakeryMenu(c);
				break;
			case 3:
				clientMenu(c);
				break;
			case 4:
				orderMenu(c);
				break;
			case 5:
				employeesMenu(c);
				break;
			case 6:
				productsMenu(c);
				break;
			case 0:
				return;
			default:
				cout << "ERROR: Not a valid Operation! Please try again..." << endl << endl;
		}

	} while (menuOption != 0);
}

int showMenu() {
	int menuOption;

	cout << " ____________________________________ " << endl;
	cout << "| --- What would you like to do? --- |" << endl;
	cout << "| 1 - Company Informations           |" << endl;
	cout << "| 2 - Bakery Menu                    |" << endl;
	cout << "| 3 - Clients Menu                   |" << endl;
	cout << "| 4 - Orders Menu                    |" << endl;
	cout << "| 5 - Employees Menu                 |" << endl;
	cout << "| 6 - Products Menu                  |" << endl;
	cout << "| 0 - Exit                           |" << endl;
	cout << "|____________________________________|" << endl;
	cout << "Option: ";
	cin >> menuOption;
	clearBuffer();

	return menuOption;
}

void companyMenu(Company *c) {
	int menuOption;

	do {
		menuOption = showCompanyInformationOptions(c);
		switch (menuOption) {
		case 0:
			break;
		default:
			cout << "ERROR: Not a valid Operation! Please try again..." << endl;
		}
	} while (menuOption != 0);

    cout << "\n\n";
	return;
}

int showCompanyInformationOptions(Company *c) {
	int menuOption;

	cout << "_____________________________________" << endl;
	cout << " ------- COMPANY INFORMATION ------- " << endl << endl;
	cout << "Total Bakeries: " << c->getBakeries().size() << endl;
	cout << "Total Employees: " << c->getEmployees().size() << endl;
	cout << "Total Clients: " << c->getClients().size() << endl;
	cout << "Premium Clients: " << c->getClientsPremium().size() << endl;
	cout << "Total Orders Delivered: " << c->getDeliveredOrders().size() << endl;
    cout << "Total Orders Completed but Not Delivered: " << c->getCompletedOrders().size() << endl;
    cout << "Total Orders Incompleted: " << c->getIncompletedOrders().size() << endl;
	cout << "Total Products: " << c->getProducts().size() << endl;
	cout << "_____________________________________" << endl;
	cout << " 0 - Back" << endl << endl;
	cout << "Option: ";
	cin >> menuOption;

	return menuOption;
}

/********** Bakery Information **********/

void bakeryMenu(Company *c) {
	int menuOption;

	do {
		menuOption = showBakeryOptions(c);
		switch (menuOption) {
		case 0:
			break;
		case 1:
			chooseBakery(c);
			break;
		case 2:
			addBakery(c);
			break;
		default:
			cout << "ERROR: Not a valid Operation! Please try again..." << endl;
		}
	} while (menuOption != 0);

	cout << "\n\n";
	return;
}

int showBakeryOptions(Company *c) {
	int menuOption;
	vector<Bakery *> bakeries = c->getBakeries();

	cout << " _____________________________________ " << endl;
	cout << " ----------- BAKERIES MENU ----------- " << endl;
	cout << " Total Bakeries: " << bakeries.size() << endl;
	for (unsigned i = 0; i < bakeries.size(); i++) {
		cout << " - " << bakeries[i]->getAddress() << endl;
	}
	cout << " _____________________________________" << endl;
	cout << " ----- What would you like to do? ---- " << endl;
	cout << " 1 - Choose a bakery" << endl;
	cout << " 2 - Add Bakery" << endl;
	cout << " 0 - Back" << endl << endl;
	cout << " Option: ";
	cin >> menuOption;

	return menuOption;
}

void addBakery(Company *c) {
    string address;

    clearBuffer();
    cout << "Enter address: ";
    getline(cin, address);
    try{

		Bakery* newBakery = new Bakery(address, c);
        cout << "Bakery added!" << endl << endl;

		fstream file;
		file.open("register.txt", fstream::app);

		size_t pos;
		while ((pos = address.find(" ")) != std::string::npos) {
			address.replace(pos, 1, "_");
		}

		file << "addBakery " << address << endl;
		
		file.close();
    }
    catch (...) {  }

    cout << "\n\n";
	return;
}

void chooseBakery(Company *c) {
	string address;

	clearBuffer();
	cout << "Enter address of the bakery: ";
	getline(cin, address);

	try {
        Bakery *b = c->chooseBakery(address);
        chooseBakeryMenu(c, b);
	}
	catch(...){ }
}

void chooseBakeryMenu(Company *c, Bakery *b) {
	int menuOption;

	do {
		menuOption = showChooseBakeryOptions(b);
		switch (menuOption) {
		case 0:
			break;
		case 1:
			changeBakeryAddress(c, b);
			break;
		case 2:
            addEmployee(c, b);
			break;
		case 3:
            removeEmployee(c, b);
			break;
		default:
			cout << "ERROR: Not a valid Operation! Please try again..." << endl;
		}
	} while (menuOption != 0);

	cout << "\n\n";
	return;
}

int showChooseBakeryOptions(Bakery *b){
	int menuOption;

	cout << " _____________________________________ " << endl;
	cout << " --------- CHOOSE BAKERY MENU -------- " << endl;
	cout << b->getInfo();
	cout << " _____________________________________" << endl;
	cout << " ----- What would you like to do? ---- " << endl;
	cout << " 1 - Change Bakery address" << endl;
	cout << " 2 - Add employee" << endl;
	cout << " 3 - Remove employee" << endl;
	cout << " 0 - Back" << endl << endl;
	cout << " Option: ";
	cin >> menuOption;

	return menuOption;
}

void changeBakeryAddress(Company *c, Bakery *b){
	string newAddress;

	clearBuffer();
	cout << "Enter new address: ";
	getline(cin, newAddress);
	string oldAddress = b->getAddress();

	b->setAddress(newAddress);
	cout << "Address updated!" << endl << endl;

	fstream file;
	file.open("register.txt", fstream::app);

	size_t pos;
	while ((pos = oldAddress.find(" ")) != std::string::npos) {
		oldAddress.replace(pos, 1, "_");
	}
	while ((pos = newAddress.find(" ")) != std::string::npos) {
		newAddress.replace(pos, 1, "_");
	}

	file << "changeBakeryAddress " << oldAddress << " " << newAddress << endl;
	file.close();

	cout << "\n\n";
	return;
}

void addEmployee(Company *c, Bakery * b) {
	int nif, salary;
    string name;
    string job;

	clearBuffer();
	cout << "Nif: ";
	cin >> nif;

    clearBuffer();
	cout << "Name: ";
	getline(cin, name);

    clearBuffer();
	cout << "Salary: ";
	cin >> salary;

    clearBuffer();
    cout << "Job: ";
    getline(cin, job);

    transform(job.begin(), job.end(), job.begin(), ::tolower);

    try{
        Employee *e = new Employee(name, nif);
        b->addEmployee(e, salary, job);
	    cout << e->getInfo() <<"Employee added successfully!" << endl;

		fstream file;
		file.open("register.txt", fstream::app);

		string address = b->getAddress();
		size_t pos;
		while ((pos = address.find(" ")) != std::string::npos) {
			address.replace(pos, 1, "_");
		}
		while ((pos = name.find(" ")) != std::string::npos) {
			name.replace(pos, 1, "_");
		}
        while ((pos = job.find(" ")) != std::string::npos) {
            job.replace(pos, 1, "_");
        }

		file << "addEmployee " << address << " " << name << " " << nif << " " << salary << " " << job << endl;
		file.close();
		//void addEmployee(Company* c, string address, string name, int nif, int salary);

    }
    catch (...){}

    cout << "\n\n";
	return;
}

void removeEmployee(Company *c, Bakery *b) {
	int nif;

	clearBuffer();
	cout << "Nif: ";
	cin >> nif;

	try {
        Employee *e = c->chooseEmployee(nif);
        b->fireEmployee(e);
        cout << "Employee fired with success!\n";

		fstream file;
		file.open("register.txt", fstream::app);
		string address = b->getAddress();
		size_t pos;
		while ((pos = address.find(" ")) != std::string::npos) {
			address.replace(pos, 1, "_");
		}
		file << "removeEmployee " << address << " " << e->getNif() << endl;
		file.close();
		//void removeEmployee(Company * c, string address, int nif);

	}
	catch (...) { }

    cout << "\n\n";
	return;;
}

/********** Client Information **********/

void clientMenu(Company *c) {
	int menuOption;

	do {
		menuOption = showClientOptions(c);
		switch (menuOption) {
		case 0:
			break;
		case 1:
			chooseClient(c);
			break;
		case 2:
			addClient(c);
			break;
		default:
			cout << "ERROR: Not a valid Operation! Please try again..." << endl;
		}
	} while (menuOption != 0);

    cout << "\n\n";
	return;
}

int showClientOptions(Company *c) {
	int menuOption;

	cout << "_____________________________________" << endl;
	cout << " ----------- CLIENT MENU ----------- " << endl;
	cout << "Total Clients - " << c->getClients().size() << endl;
	cout << "Premium Clients - " << c->getClientsPremium().size() << endl;
	cout << "_____________________________________" << endl;
	cout << "What would you like to do?" << endl;
	cout << "1 - Choose client" << endl;
	cout << "2 - Add client" << endl;
	cout << "0 - Back" << endl << endl;
	cout << "Option: ";
	cin >> menuOption;

	return menuOption;
}

void chooseClient(Company *c){
	int nif;

	clearBuffer();
	cout << "Nif: ";
	cin >> nif;

	try {
        Client * cli = c->chooseClient(nif);
        chooseClientMenu(c, cli);
	}
    catch (...) {  }

}

void addClient(Company *c){
	int nif;
    string name, premium;

	clearBuffer();
	cout << "Nif: ";
	cin >> nif;

    clearBuffer();
	cout << "Name: ";
    getline(cin, name);

    clearBuffer();
    cout << "Type of client (premium/normal): ";
    getline(cin, premium);

    try{
        Client* cli = new Client(name, nif, premium);
        c->addClient(cli);

		fstream file;
		file.open("register.txt", fstream::app);

		size_t pos;
		while ((pos = name.find(" ")) != std::string::npos) {
			name.replace(pos, 1, "_");
		}

		file << "addClient " << nif << " " << name << " " << premium << endl;
		file.close();
		//void addClient(Company* c, int nif, string name, string premium);
    }
    catch(...){ }

    cout << "\n\n";
	return;
}

void chooseClientMenu(Company *c, Client *cli) {
	int menuOption;

	do {
		menuOption = showChooseClientOptions(c, cli);
		switch (menuOption) {
		case 0:
			break;
		case 1:
			togglePremiumClient(c, cli);
			break;
		case 2:
			makeOrder(c, cli);
			break;
		case 3:
            goToBakery(c, cli);
			break;
		default:
			cout << "ERROR: Not a valid Operation! Please try again..." << endl;
		}
	} while (menuOption != 0);

    cout << "\n\n";
	return;
}

int showChooseClientOptions(Company *c, Client *cli) {
	int menuOption;

	cout << "_____________________________________" << endl;
	cout << " -------- CHOOSE CLIENT MENU -------- " << endl;
	cout << cli->getInfo();
	cout << "_____________________________________" << endl;
	cout << "What would you like to do?" << endl;
	cout << "1 - Change premium" << endl;
	cout << "2 - Make order" << endl;
	cout << "3 - Go to Bakery" << endl;
	cout << "0 - Back" << endl << endl;
	cout << "Option: ";
	cin >> menuOption;

	return menuOption;
}

void togglePremiumClient(Company *c, Client *cli) {

    if(cli->getPremium()) {
        cli->setPremium(false);
        cout << "\nNow the client is no longer premium!\n\n";
    }
    else {
        cli->setPremium(true);
        cout << "\nNow the client premium!\n\n";
    }

	fstream file;
	file.open("register.txt", fstream::app);
	file << "togglePremiumClient " << cli->getNif() << endl;
	file.close();
	//void togglePremiumClient(Company* c, int nif);

    cout << "\n\n";
	return;
}

void makeOrder(Company *c, Client *cli) {

    vector<Product *> products = c->getProducts();
    vector<Product *>::iterator itp = products.begin();

    Order* order = new Order();

    cout << "____________________________________________" << endl;
    cout << " -------- CLIENT MAKING A NEW ORDER -------- " << endl;
    cout << "____________________________________________" << endl;
    cout << "____________________________________________" << endl;
    cout << "            PRODUCTS AVAILABLE" << endl;
    cout << " Total Products: " << products.size() << endl << endl;
    cout << "____________________________________________" << endl;
    while(itp != products.end()){
		cout << endl;
        cout << (*itp)->getInfo();
        itp++;
    }
    cout << "____________________________________________" << endl;

	int t = 0;
	string name1;
	int quantity1;
	string name2 = "none";
	int quantity2 = 0;
	string name3 = "none";
	int quantity3 = 0;

    string answer;
    do {

        string name;
        int quantity;

		clearBuffer();
        cout << "Choose the name of the product you want: ";
        getline(cin, name);

		clearBuffer();
        cout << "Now choose the quantity: ";
        cin >> quantity;

        try {
            order->addPackage( new Package(c->chooseProduct(name), quantity) );

			size_t pos;
			while ((pos = name.find(" ")) != std::string::npos) {
				name.replace(pos, 1, "_");
			}

			t++;
			if (t == 1) {
				name1 = name;
				quantity1 = quantity;
			}
			if (t == 2) {
				name2 = name;
				quantity2 = quantity;
			}
			if (t == 3) {
				name3 = name;
				quantity3 = quantity;
			}
        }
        catch (...) { }

		clearBuffer();
        cout << "\nWould you like to add another product (yes/no)? ";
        getline(cin, answer);
    } while (answer != "no" && answer != "No");

    string address;
	clearBuffer();
    cout << "\nAnd what's the address of the bakery you want to request this order? ";
    getline(cin, address);

    try {
        Bakery* b = c->chooseBakery(address);
        cli->makeNewOrder(order, b);
        cout << "\nOrder requested with success!\n";

		fstream file;
		file.open("register.txt", fstream::app);

		size_t pos;
		while ((pos = address.find(" ")) != std::string::npos) {
			address.replace(pos, 1, "_");
		}

		file << "makeOrder " << cli->getNif() << " " << address;
		int i = 0;
		while (i != t) {

			if (i == 0)
				file << " " << name1 << " " << quantity1;
			if (i == 1)
				file << " " << name2 << " " << quantity2;
			if (i == 2)
				file << " " << name3 << " " << quantity3;

			i++;
		}
		file << endl;
		file.close();
		//void makeOrder(Company* c, int nifClient, string address, string productName1, int quantity1, string productName2="", int quantity2=0, string productName3="", int quantity3=0);

    }
    catch (...) { }

    cout << "\n\n";
	return;

}

void goToBakery(Company *c, Client *cli) {
    string address;

    clearBuffer();
    cout << "What's the address of the bakery you want to go? ";
    getline(cin, address);

    try{
        Bakery* b = c->chooseBakery(address);
        cout << "\n\n";
        cli->goToTheBakeryToPickUpOrder(b);

		fstream file;
		file.open("register.txt", fstream::app);

		size_t pos;
		while ((pos = address.find(" ")) != std::string::npos) {
			address.replace(pos, 1, "_");
		}

		file << "goToBakery " << cli->getNif() << " " << address << endl;
		file.close();
		//void goToBakery(Company * c, int nifClient, string address);

    }
    catch (...) { }

    cout << "\n\n";
	return;
}

/********** Order Information **********/

void orderMenu(Company *c) {
	int menuOption;

	do {
		menuOption = showOrderOptions(c);
		switch (menuOption) {
		case 0:
			break;
		case 1:
			chooseOrder(c);
			break;
		default:
			cout << "ERROR: Not a valid Operation! Please try again..." << endl;
		}
	} while (menuOption != 0);

    cout << "\n\n";
	return;
}

int showOrderOptions(Company *c) {
	int menuOption;

	cout << " _____________________________________ " << endl;
	cout << " ------------- ORDER MENU ------------ " << endl;
	cout << "Total Orders Delivered: " << c->getDeliveredOrders().size() << endl;
	cout << "Total Orders Completed but Not Delivered: " << c->getCompletedOrders().size() << endl;
    cout << "Total Orders Incompleted: " << c->getIncompletedOrders().size() << endl;
	cout << " _____________________________________" << endl;
	cout << " ----- What would you like to do? ---- " << endl;
	cout << " 1 - Get Order Info by Id" << endl;
	cout << " 0 - Back" << endl << endl;
	cout << " Option: ";
	cin >> menuOption;

	return menuOption;
}

void chooseOrder(Company *c){

    int id;

    clearBuffer();
    cout << "What's the id of the order?";
    cin >> id;

    cout << endl << endl;

    (c->chooseOrder(id))->getInfo();

    cout << "\n\n";
	return;
}

/********** Employee Information **********/

void employeesMenu(Company *c) {
	int menuOption;

	do {
		menuOption = showEmployeeOptions(c);
		switch (menuOption) {
            case 0:
                break;
            case 1:
                chooseEmployee(c);
                break;
		    case 2:
                addEmployee(c);
                break;
            default:
                cout << "ERROR: Not a valid Operation! Please try again..." << endl;
		}
	} while (menuOption != 0);

    cout << "\n\n";
	return;
}

int showEmployeeOptions(Company *c) {
	int menuOption;

	cout << endl << endl << endl;
	cout << "_____________________________________" << endl;
	cout << "----------- EMPLOYEE MENU -----------" << endl;
	cout << "No. of Employees: " << c->getEmployees().size() << endl;
	cout << "Salary total: " << getSalary(c->getEmployees()) << endl;
	cout << "_____________________________________" << endl;
	cout << " ---- What would you like to do? ---- " << endl;
	cout << "1 - Choose Employee" << endl;
    cout << "2 - Hire employee" << endl;
	cout << "0 - Back" << endl << endl;
	cout << "Option: ";
	cin >> menuOption;

	return menuOption;
}

void chooseEmployee(Company *c){
	int nif;

	clearBuffer();
	cout << "Nif: ";
	cin >> nif;

	try{
        Employee *e = c->chooseEmployee(nif);
        chooseEmployeeMenu(c, e);
	} catch (...) {  }

}

void chooseEmployeeMenu(Company *c, Employee *e) {
	int menuOption;

	do {
		menuOption = showChooseEmployeeOptions(c, e);
		switch (menuOption) {
		case 0:
			break;
		case 1:
			changeSalary(c, e);
			break;
		default:
			cout << "ERROR: Not a valid Operation! Please try again..." << endl;
		}
	} while (menuOption != 0);

    cout << "\n\n";
	return;
}

int showChooseEmployeeOptions(Company *c, Employee *e) {
	int menuOption;

	cout << "_____________________________________" << endl;
	cout << " ------- CHOOSE EMPLOYEE MENU ------- " << endl;
	cout << e->getInfo();
	cout << "_____________________________________" << endl;
	cout << "What would you like to do?" << endl;
	cout << "1 - Change salary" << endl;
	cout << "0 - Back" << endl << endl;
	cout << "Option: ";
	cin >> menuOption;

	return menuOption;
}

void changeSalary(Company *c, Employee *e){
	int salary;

	clearBuffer();
	cout << "New salary: ";
	cin >> salary;

	e->setSalary(salary);
	cout << "Salary updated!" << endl;

    cout << "\n\n";

	
	fstream file;
	file.open("register.txt", fstream::app);
	file << "changeSalary " << salary << " " << e->getNif() << endl;
	file.close();
	//void changeSalary(Company* c, int salary, int nifEmployee);

	return;

}

int getSalary(vector<Employee *> employees){
	vector<Employee *>::iterator it = employees.begin();
	int price = 0;

	while(it != employees.end()){
		price += (*it)->getSalary();
		it++;
	}

	return price;
}

void addEmployee(Company *c) {
    int nif;
    string name;

    clearBuffer();
    cout << "Nif: ";
    cin >> nif;

    clearBuffer();
    cout << "Name: ";
    getline(cin, name);

    try{

        int salary;
        string address;
        string job;

        clearBuffer();
        cout << "Salary: ";
        cin >> salary;

        clearBuffer();
        cout << "Address of the Bakery he wants to work: ";
        getline(cin, address);

        clearBuffer();
        cout << "What would be his job in the bakery? ";
        getline(cin, job);

        transform(job.begin(), job.end(), job.begin(), ::tolower);

        Bakery* b = c->chooseBakery(address);

		Employee* e = new Employee(name, nif);
        b->addEmployee(e, salary, job);

		cout << "Employee added with success!\n\n";

		fstream file;
		file.open("register.txt", fstream::app);

		size_t pos;
		while ((pos = address.find(" ")) != std::string::npos) {
			address.replace(pos, 1, "_");
		}
		while ((pos = name.find(" ")) != std::string::npos) {
			name.replace(pos, 1, "_");
		}
        while ((pos = job.find(" ")) != std::string::npos) {
            job.replace(pos, 1, "_");
        }

		file << "addEmployee " << address << " " << name << " " << nif << " " << salary << " " << job << endl;
		file.close();
		//void addEmployee(Company* c, string address, string name, int nif, int salary);

    }
    catch (...) {   }

    cout << "\n\n";
	return;
}

/********** Product Information **********/

void productsMenu(Company *c) {
	int menuOption;

	do {
		menuOption = showProductOptions(c);
		switch (menuOption) {
		case 0:
			break;
		case 1:
			addProduct(c);
			break;
		default:
			cout << "ERROR: Not a valid Operation! Please try again..." << endl;
		}
	} while (menuOption != 0);

    cout << "\n\n";
	return;
}

int showProductOptions(Company *c) {
	int menuOption;
	vector<Product *> products = c->getProducts();
	vector<Product *>::iterator itp = products.begin();

	cout << " _____________________________________ " << endl;
	cout << " ----------- PRODUCTS MENU ----------- " << endl;
	cout << " Total Products: " << products.size() << endl << endl;
	cout << "|||PRODUCTS|||" << endl;
	while(itp != products.end()){
	    cout << endl;
		cout << (*itp)->getInfo();
		itp++;
	}

	cout << " _____________________________________" << endl;
	cout << " ----- What would you like to do? ---- " << endl;
	cout << " 1 - Add a new Product" << endl;
	cout << " 0 - Back" << endl << endl;
	cout << " Option: ";
	cin >> menuOption;

	return menuOption;
}

void addProduct(Company *c) {
	string type, name;
	double price;

	clearBuffer();
	cout << "Enter type (only 'beverage' or 'bread'): ";
	getline(cin, type);

	clearBuffer();
	cout << "Enter name: ";
	getline(cin, name);


	if (type == "product" || type == "Product") {
		clearBuffer();
		cout << "Enter price: ";
		cin >> price;

		try {
            Product *product = new Product(name, price);
			c->addProduct(product);
			cout << "\nProduct added with success!";

			fstream file;
			file.open("register.txt", fstream::app);

			size_t pos;
			while ((pos = name.find(" ")) != std::string::npos) {
				name.replace(pos, 1, "_");
			}

			file << "addProduct " << type << " " << name << " " << price << " " << 0 << " " << "none" << endl;
			file.close();
			//void addProduct(Company* c, string type, string name, double price, int sizeBeverage, string sizeBread);
		}
		catch (...) { }
	}
	else if (type == "beverage" || type == "Beverage") {
		int size;

		clearBuffer();
		std::cout << "Enter size (ml): ";
		cin >> size;

		clearBuffer();
		cout << "Enter price: ";
		cin >> price;

		try {

            Product* beverage = new Beverage(name, size, price);
			c->addProduct(beverage);
            cout << "\nProduct added with success!";

			fstream file;
			file.open("register.txt", fstream::app);

			size_t pos;
			while ((pos = name.find(" ")) != std::string::npos) {
				name.replace(pos, 1, "_");
			}

			file << "addProduct " << type << " " << name << " " << price << " " << size << " " << "none" << endl;
			file.close();
			//void addProduct(Company* c, string type, string name, double price, int sizeBeverage, string sizeBread);
		}
		catch (...) { }
	}
	else if (type == "bread" || type == "Bread") {
		string size;

		clearBuffer();
		std::cout << "Enter size: ";
		getline(cin, size);

		clearBuffer();
		cout << "Enter price: ";
		cin >> price;

		try {

            Product* bread = new Bread(name, size, price);
			c->addProduct(bread);
            cout << "\nProduct added with success!";

			fstream file;
			file.open("register.txt", fstream::app);

			size_t pos;
			while ((pos = name.find(" ")) != std::string::npos) {
				name.replace(pos, 1, "_");
			}

			file << "addProduct " << type << " " << name << " " << price << " " << 0 << " " << size << endl;
			file.close();
			//void addProduct(Company* c, string type, string name, double price, int sizeBeverage, string sizeBread);
		}
		catch (...) { }
	}
	else if (type == "cake" || type == "Cake") {
        double weight;
        int lay;

        clearBuffer();
        std::cout << "Enter weight of the cake: ";
        cin >> weight;

        do {
            clearBuffer();
            cout << "You want 1 or 2 layers? ";
            cin >> lay;
            if (lay != 1 && lay != 2)
                cout << "Invalid answer! Try Again.\n\n";
        } while (lay != 1 && lay != 2);

        string layer1 = "";
        string layer2 = "";
        for (int i = 1; i <= lay; i++){
            cout << "Choose layer " << i << "(only 'crocante', 'massa folhada', 'massa de pão de ló'): ";
            if (i == 1)
                getline(cin, layer1);
            if (i == 2)
                getline(cin, layer2);
        }
        try {
            Product* cake = new Cake(name, weight, layer1, layer2);
            c->addProduct(cake);

			size_t pos;
			while ((pos = name.find(" ")) != std::string::npos) {
				name.replace(pos, 1, "_");
			}

            cout << "\nProduct added with success!";
        }
        catch (...) { }
    }
	else {
		cout << "\nERROR: That product type doesn't exist" << endl;
	}

	cout << "\n\n";
	return;
}


////////////////////////////////////////// FILE MANAGER /////////////////////////////////

void addProduct(Company* c, string type, string name, double price, int sizeBeverage, string sizeBread) {
	
	size_t pos;
	while ((pos = name.find("_")) != std::string::npos) {
		name.replace(pos, 1, " ");
	}
	while ((pos = sizeBread.find(" ")) != std::string::npos) {
		sizeBread.replace(pos, 1, "_");
	}

	if (type == "product" || type == "Product") {

		Product* product = new Product(name, price);
		c->addProduct(product);

	}
	else if (type == "beverage" || type == "Beverage") {

		Product* beverage = new Beverage(name, sizeBeverage, price);
		c->addProduct(beverage);

	}
	else if (type == "bread" || type == "Bread") {
		
		Product* bread = new Bread(name, sizeBread, price);
		c->addProduct(bread);
	}
}


void changeSalary(Company* c, int salary, int nifEmployee) {
	
	(c->chooseEmployee(nifEmployee))->setSalary(salary);

}

void addClient(Company* c, int nif, string name, string premium) {
	
	size_t pos;
	while ((pos = name.find("_")) != std::string::npos) {
		name.replace(pos, 1, " ");
	}

	Client* cli = new Client(name, nif, premium);
	c->addClient(cli);

}

void togglePremiumClient(Company* c, int nif) {

	Client* cli = c->chooseClient(nif);

	if (cli->getPremium()) {
		cli->setPremium(false);
	}
	else {
		cli->setPremium(true);
	}

}

void makeOrder(Company* c, int nifClient, string address, string productName1, int quantity1, string productName2, int quantity2, string productName3, int quantity3) {

	size_t pos;
	while ((pos = address.find("_")) != std::string::npos) {
		address.replace(pos, 1, " ");
	}
	while ((pos = productName1.find("_")) != std::string::npos) {
		productName1.replace(pos, 1, " ");
	}
	while ((pos = productName2.find("_")) != std::string::npos) {
		productName2.replace(pos, 1, " ");
	}
	while ((pos = productName3.find("_")) != std::string::npos) {
		productName3.replace(pos, 1, " ");
	}

	Client* cli = c->chooseClient(nifClient);
	Order* order = new Order();

	order->addPackage(new Package(c->chooseProduct(productName1), quantity1));
	
	if (productName2 != "none")
		order->addPackage(new Package(c->chooseProduct(productName2), quantity2));
	if (productName3 != "none")
		order->addPackage(new Package(c->chooseProduct(productName3), quantity3));

	Bakery* b = c->chooseBakery(address);
	cli->makeNewOrder(order, b);
	
}

void goToBakery(Company* c, int nifClient, string address) {
	
	size_t pos;
	while ((pos = address.find("_")) != std::string::npos) {
		address.replace(pos, 1, " ");
	}

	Client* cli = c->chooseClient(nifClient);
	Bakery* b = c->chooseBakery(address);
	cli->goToTheBakeryToPickUpOrder(b);
	cout << "\n\n";
}

void addBakery(Company* c, string address) {

	size_t pos;
	while ((pos = address.find("_")) != std::string::npos) {
		address.replace(pos, 1, " ");
	}

	Bakery* newBakery = new Bakery(address, c);
}

void changeBakeryAddress(Company* c, string oldAddress, string newAddress) {

	size_t pos;
	while ((pos = oldAddress.find("_")) != std::string::npos) {
		oldAddress.replace(pos, 1, " ");
	}
	while ((pos = newAddress.find("_")) != std::string::npos) {
		newAddress.replace(pos, 1, " ");
	}

	Bakery* b = c->chooseBakery(oldAddress);
	b->setAddress(newAddress);
}

void addEmployee(Company* c, string address, string name, int nif, int salary, string job) {

	size_t pos;
	while ((pos = address.find("_")) != std::string::npos) {
		address.replace(pos, 1, " ");
	}
	while ((pos = name.find("_")) != std::string::npos) {
		name.replace(pos, 1, " ");
	}
    while ((pos = job.find("_")) != std::string::npos) {
        job.replace(pos, 1, " ");
    }
	
	Bakery* b = c->chooseBakery(address);
	Employee* e = new Employee(name, nif);
	b->addEmployee(e, salary, job);

}

void removeEmployee(Company* c, string address, int nif) {

	size_t pos;
	while ((pos = address.find("_")) != std::string::npos) {
		address.replace(pos, 1, " ");
	}

	Bakery* b = c->chooseBakery(address);
	Employee* e = c->chooseEmployee(nif);
	b->fireEmployee(e);

}