#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <thread>
#include <cctype>
#include <algorithm>
#include <limits>
#include <ctime>

using namespace std;

struct Product
{
    string productID;
    string name;
    string type;
    string field;
    string keyword;
    int quantity;
    float price;
    float discount;
    Product *next;
};

struct Customer {
	string keyword;
	string field;
    string date;
    string billID;
    int serial;
    string productname;
    int productquantity;
    int total;
    Customer *next;
};

struct TreeNode
{
    Product data;
    TreeNode *left;
    TreeNode *right;
};

Customer *headC = nullptr;
Product *head = nullptr;
enum SortField { NAME, PRODUCT_ID, TYPE, PRICE, QUANTITY, DISCOUNT };
Product *tail = nullptr;

string removeSpaces(string str)
{
    str.erase(0, str.find_first_not_of(' ')); 
    str.erase(str.find_last_not_of(' ') + 1);
    return str;
}

void displaySortedProduct(string sortBy)
{
	if (head == nullptr)
	{
		cout << "  The information system is empty." << endl;
		return;
	}
	int listSize = 0;
	Product *temp = head;
	while (temp != nullptr)
	{
		listSize++;
		temp = temp->next;
	}
	Product *productArray = new Product[listSize];
	temp = head;
	for (int i = 0; i < listSize; i++)
	{
		productArray[i] = *temp;
		temp = temp->next;
	}
	for (int i = 1; i < listSize; i++)
	{
		Product key = productArray[i];
		int j = i - 1;
		while (j >= 0 && ((sortBy == "productID" && productArray[j].productID > key.productID) ||
						  (sortBy == "name" && productArray[j].name > key.name) ||
						  (sortBy == "type" && productArray[j].type > key.type) ||
						  (sortBy == "price" && productArray[j].price > key.price)))
		{
			productArray[j + 1] = productArray[j];
			j--;
		}
		productArray[j + 1] = key;
	}
	cout << "-----------------------------------" << endl;
	cout << "  List of products sorted by " << sortBy << ":" << endl;
	cout << "O===============o============================================================o====================o===============o===============o===============O" << endl;
    cout << "|   ProductID   |                           Product Name                     |         Type       |     Price     |    Quantity   |    Discount   |" << endl;
    cout << "o===============o============================================================o====================o===============o===============o===============o" << endl;
	for (int i = 0; i < listSize; i++)
	{
		cout << "|" << setw(15) << left << productArray[i].productID 
			 << "|" << setw(60) << left << productArray[i].name
			 << "|" << setw(20) << left << productArray[i].type 
			 << "|" << setw(15) << left << productArray[i].price 
			 << "|" << setw(15) << left << productArray[i].quantity 
			 << "|" << setw(15) << left << productArray[i].discount << "|" << endl;
	    cout << "|---------------|------------------------------------------------------------|--------------------|---------------|---------------|---------------|" << endl;
	}
	delete[] productArray;
}

void displaySortedBill(string sortBy)
{
    if (headC == nullptr)
    {
        cout << "  The information system is empty." << endl;
        return;
    }
    int listSize = 0;
    Customer *temp = headC;
    while (temp != nullptr)
    {
        listSize++;
        temp = temp->next;
    }
    Customer *billArray = new Customer[listSize];
    temp = headC;
    for (int i = 0; i < listSize; i++)
    {
        billArray[i] = *temp;
        temp = temp->next;
    }
    for (int i = 1; i < listSize; i++)
    {
        Customer key = billArray[i];
        int j = i - 1;
        while (j >= 0 && (
            (sortBy == "date" && billArray[j].date > key.date) ||
            (sortBy == "billID" && billArray[j].billID > key.billID)))
        {
            billArray[j + 1] = billArray[j];
            j--;
        }
        billArray[j + 1] = key;
    }
    cout << "-----------------------------------" << endl;
    cout << "  List of product sorted by " << sortBy << ":" << endl;
    cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
    cout << "| Date          | BillID   | Serial                 | Product           | Quantity                                   | Total       |" << endl;
    cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
    for (int i = 0; i < listSize; i++)
    {
        cout << "| " << setw(10) << left << billArray[i].date << " | " << setw(53) << left << billArray[i].billID << " | " << setw(22) << left << billArray[i].serial << " | " << setw(23) 
        << left << billArray[i].productname << " | " << setw(40) << left << billArray[i].productquantity << " | " << setw(11) << left << billArray[i].total << " |" << endl;
    	cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
    }
    delete[] billArray;
}

void returnToPreviousFunction() {
    int input;
    do {
        std::cout << "  Enter 0 to return to the previous function: ";
        std::cin >> input;
    } while (input != 0);
    system("cls");
    cin.ignore();
}

void addProduct(string productID, string name, string type, int price, int quantity, int discount)
{
    Product *newProduct = new Product;
    newProduct->productID = productID;
    newProduct->name = name;
    newProduct->type = type;
    newProduct->price = price;
    newProduct->quantity = quantity;
    newProduct->discount = discount;
    newProduct->next = head;
    head = newProduct;
}

void readFromFile(string filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cout << "  Can't open file" << endl;
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ';'))
        {
            fields.push_back(field);
        }

        if (fields.size() != 6)
        {
            cout << "  Invalid data format" << endl;
            continue;
        }

        string productID = fields[0];
        string name = fields[1];
        string type = fields[2];
        int price = stoi(fields[3]);
        int quantity = stoi(fields[4]);
        int discount = stoi(fields[5]);

        addProduct(productID, name, type, price, quantity, discount);
    }

    inFile.close();
}

void displayProduct()
{
    Product *temp = head;
    cout << "O===============o============================================================o====================o===============o===============o===============O" << endl;
    cout << "|   ProductID   |                           Product Name                     |         Type       |     Price     |    Quantity   |    Discount   |" << endl;
    cout << "o===============o============================================================o====================o===============o===============o===============o" << endl;
    while (temp != nullptr)
	{
	    cout << "|" << setw(15) << left << temp->productID 
			 << "|" << setw(60) << left << temp->name 
			 << "|" << setw(20) << left << temp->type 
			 << "|" << setw(15) << left << temp->price 
			 << "|" << setw(15) << left << temp->quantity 
			 << "|" << setw(15) << left << temp->discount << "|" << endl;
	    cout << "|---------------|------------------------------------------------------------|--------------------|---------------|---------------|---------------|" << endl;
	    temp = temp->next;
	}
}

void displaynewProduct(string productID, string name, string type, int price, int quantity, int discount)
{
    cout << "O---------------o---------------------------------o---------------o---------------o---------------o---------------O" << endl;
    cout << "|   ProductID   |               Name              |      Type     |     Price     |    Quantity   |    Discount   |" << endl;
    cout << "o---------------o---------------------------------o---------------o---------------o---------------o---------------o" << endl;
	cout << "|" << setw(15) << left << productID 
		 << "|" << setw(33) << left << name 
		 << "|" << setw(15) << left << type 
		 << "|" << setw(15) << left << price 
		 << "|" << setw(15) << left << quantity 
		 << "|" << setw(15) << left << discount << " |" << endl;
	cout << "o---------------o---------------------------------o---------------o---------------o---------------o---------------o" << endl;
}

void displaynewadjustProduct(string newID, string newname_product, string newtype, int newprice, int newquantity, int newdiscount)
{
	cout << "O---------------o---------------------------------o---------------o---------------o---------------o---------------O" << endl;
	cout << "|   ProductID   |               Name              |      Type     |     Price     |    Quantity   |    Discount   |" << endl;
	cout << "o---------------o---------------------------------o---------------o---------------o---------------o---------------o" << endl;
	cout << "|" << setw(13) << left << newID 
		 << "|" << setw(33) << left << newname_product 
		 << "|" << setw(15) << left << newtype 
		 << "|" << setw(15) << left << newprice 
		 << "|" << setw(15) << left << newquantity 
		 << "|" << setw(14) << left << newdiscount << "|" << endl;
	cout << "o---------------o---------------------------------o---------------o---------------o---------------o---------------o" << endl;
}

vector<Product*> searchProduct(string keyword, string field)
{
    vector<Product*> result;
    Product *temp = head;
    while (temp != nullptr)
    {
        if (field == "productID") 
        {
            temp->productID.erase(0, temp->productID.find_first_not_of(' ')); 
    		temp->productID.erase(temp->productID.find_last_not_of(' ') + 1);
            if (temp->productID == removeSpaces(keyword))
            {
                result.push_back(temp);
            }
        }
        else if (field == "name")
        {
        	temp->name.erase(0, temp->name.find_first_not_of(' ')); 
    		temp->name.erase(temp->name.find_last_not_of(' ') + 1);
            if (temp->name == removeSpaces(keyword))
            {
                result.push_back(temp);
            }
		}
        else if (field == "type")
        {
            temp->type.erase(0, temp->type.find_first_not_of(' ')); 
    		temp->type.erase(temp->type.find_last_not_of(' ') + 1);
            if (temp->type == removeSpaces(keyword))
            {
                result.push_back(temp);
            }
        }
        temp = temp->next;
    }
    return result; 
}

void findProduct(string keyword, string field)
{
    vector<Product*> productsToFind = searchProduct(keyword, field);
    if (productsToFind.empty())
    {
        cout << "  No product found in the store." << endl;
        return;
    }
    else {
    cout << "O---------------o---------------------------------o---------------o---------------o---------------o---------------O" << endl;
    cout << "|   ProductID   |               Name              |      Type     |     Price     |    Quantity   |    Discount   |" << endl;
    cout << "o---------------o---------------------------------o---------------o---------------o---------------o---------------o" << endl;
        for (Product* product : productsToFind)
        {
            cout << "|" << setw(15) << left << product->productID 
			     << "|" << setw(33) << left << product->name 
				 << "|" << setw(15) << left << product->type 
            	 << "|" << setw(15) << left << product->price 
				 << "|" << setw(15) << left << product->quantity 
				 << "|" << setw(15) << left << product->discount << "|" << endl;
        cout << "o---------------o---------------------------------o---------------o---------------o---------------o---------------o" << endl;
		}
    }
}

void adjustProduct(string keyword, string field, string newID, string newname_product, string newtype, int newprice, int newquantity, int newdiscount)
{
    vector<Product*> productsToAdjust = searchProduct(keyword, field);
    if (productsToAdjust.empty()) {
        cout << "  No products found to adjust." << endl;
        return;
    }
    for (Product* product : productsToAdjust) {
    	product->productID = newID;
        product->name = newname_product;
        product->type = newtype;
        product->price = newprice;
        product->quantity = newquantity;
        product->discount = newdiscount;
    }
    cout << "  Product information updated successfully." << endl;
}

void deleteProduct(string productID)
{
    if (head == nullptr)
    {
        cout << "  The list is empty." << endl;
        return;
    }
    Product *temp = head;
    Product *prev = nullptr;
    while (temp != nullptr && temp->productID != productID)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr)
    {
        cout << "  Product not found in the library." << endl;
        return;
    }
    if (prev == nullptr)
    {
        head = head->next;
    }
    else
    {
        prev->next = temp->next;
    }
    delete temp;
    cout << "  Product deleted successfully." << endl;
}

void exportData(string filename)
{
    ofstream outputFile(filename);
    Product *temp = head;

    while (temp != nullptr)
    {
        outputFile << removeSpaces(temp->productID) << "; " << removeSpaces(temp->name) << "; " << removeSpaces(temp->type) << "; " << temp->price << "; " << temp->quantity << "; " << temp->discount << endl;
        temp = temp->next;
    }

    outputFile.close();
}

void addCustomer(string billID, string date, int serial, string productname, int productquantity, int total) {
    Customer *newCustomer = new Customer;
    newCustomer->billID = billID;
    newCustomer->date = date;
    newCustomer->serial = serial;
    newCustomer->productname = productname;
    newCustomer->productquantity = productquantity;
    newCustomer->total = total;
    newCustomer->next = headC;
    headC = newCustomer;
}

vector<Customer *> searchBill(string keyword, string field)
{
	vector<Customer *> show;
    Customer *temp = headC;
    while (temp != nullptr)
    {
        if (field == "date")
        {
            temp->date.erase(0, temp->date.find_first_not_of(' ')); 
    		temp->date.erase(temp->date.find_last_not_of(' ') + 1);
            if (temp->date == removeSpaces(keyword))
            {
                show.push_back(temp);
            }
        }
        else if (field == "month")
        {
        	size_t pos = temp->date.find_first_of("/");
            size_t pos2 = temp->date.find_last_not_of(' ') + 1;
            string month = temp->date.substr(pos, pos2-pos);
            if(month == "/"+removeSpaces(keyword))
            {
                show.push_back(temp);
            }
        }
        else if (field == "year")
        {
        	size_t pos = temp->date.find_first_of("/");
            size_t pos2 = temp->date.find_first_of("/", pos+1);
            size_t pos3 = temp->date.find_last_not_of(' ') + 1;
            string year = temp->date.substr(pos2, pos3-pos2);
            if(year == "/"+removeSpaces(keyword))
            {
                show.push_back(temp);
            }
        }
        else if (field == "billID")
        {
            temp->billID.erase(0, temp->billID.find_first_not_of(' ')); 
    		temp->billID.erase(temp->billID.find_last_not_of(' ') + 1);
            if (temp->billID == removeSpaces(keyword))
            {
                show.push_back(temp);
            }
        }
        temp = temp->next;
    }
    return show; 
}

void findBill(string keyword, string field)
{
    vector<Customer *> billsToFind = searchBill(keyword, field);
    if (billsToFind.empty())
    {
        cout << "  Not found in the system." << endl;
        return;
    }
    else{
    cout << "O--------------o--------------o-----------o------------------------------------------------------------o---------------o---------------O" << endl;
    cout << "|      Date    |    BillID    |   Serial  |                          Product Name                      |   Quantity    |      Total    |" << endl;
    cout << "o--------------o--------------o-----------o------------------------------------------------------------o---------------o---------------o" << endl;
    for (Customer *customer : billsToFind) 
	{
        cout << "|" << setw(14) << left << customer->date 
		     << "|" << setw(14) << left << customer->billID 
			 << "|" << setw(11)  << left << customer->serial 
			 << "|" << setw(60) << left << customer->productname 
			 << "|" << setw(15) << left << customer->productquantity 
			 << "|" << setw(15) << left << customer->total << "|" << endl;
    	cout << "o--------------o--------------o-----------o------------------------------------------------------------o---------------o---------------o" << endl;
	}
	}
}

void DisplayBill() {
    Customer *temp = headC;
    cout << "O--------------o--------------o-----------o------------------------------------------------------------o---------------o---------------O" << endl;
    cout << "|      Date    |    BillID    |   Serial  |                          Product Name                      |   Quantity    |      Total    |" << endl;
    cout << "o--------------o--------------o-----------o------------------------------------------------------------o---------------o---------------o" << endl;
    while (temp != nullptr) {
        cout << "|"  << setw(14) << left << temp->date 
			 << "|" << setw(14) << left << temp->billID 
			 << "|" << setw(11)  << left << temp->serial 
			 << "|" << setw(60) << left << temp->productname 
			 << "|" << setw(15) << left << temp->productquantity 
			 << "|" << setw(15) << left << temp->total << "|" << endl;
    	cout << "o--------------o--------------o-----------o------------------------------------------------------------o---------------o---------------" << endl;
        temp = temp->next;
    }
}

void readFromFilebill(string filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cout << "  Can't open file" << endl;
        return;
    }
    string line;
    while (getline(inFile, line))
    {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ';'))
        {
            fields.push_back(field);
        }

        if (fields.size() != 6)
        {
            cout << "  Invalid data format" << endl;
            continue;
        }
        
        string billID = fields[0];
        string date = fields[1];
        int serial = stoi(fields[2]);
        string productname = fields[3];
        int productquantity = stoi(fields[4]);
        int total = stoi(fields[5]);
        
        addCustomer(billID, date, serial, productname, productquantity, total);
        }
    
    inFile.close();
}

void exportDatabill(string filename)
{
    ofstream outputFile(filename);
    Customer *temp = headC;
    while (temp != nullptr)
    {
        outputFile << removeSpaces(temp->billID) << "; " << removeSpaces(temp->date) << "; " << temp->serial << "; " << removeSpaces(temp->productname) << "; " << temp->productquantity << "; " << temp->total << endl;
        temp = temp->next;
    }
    outputFile.close();
}

bool editdate(string date)
{
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    int currentYear = 1900 + timePtr->tm_year;
    int day, month, year;
    sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 2020 || year > currentYear) {
        cout << "  Invalid date!";
        return false;
    }
    bool is_valid_date = true;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            is_valid_date = false;
        }
    } else if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            if (day > 29) {
                is_valid_date = false;
            }
        } else {
            if (day > 28) {
                is_valid_date = false;
            }
        }
    }
    if (!is_valid_date) {
        cout << "  Invalid date! ";
        return false;
    }
    return true;
}

bool editmonth(string month1)
{
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    int currentYear = 1900 + timePtr->tm_year;
    int month, year;
    sscanf(month1.c_str(), "%d/%d", &month, &year);
    if (month < 1 || month > 12 || year < 2000 || year > currentYear) {
        cout << "  Invalid date!";
        return false;
    }
    return true;
}

bool edityear(string year1)
{
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    int currentYear = 1900 + timePtr->tm_year;
    int year;
    sscanf(year1.c_str(), "%d", &year);
    if (year < 2000 || year > currentYear) {
        cout << "  Invalid date!";
        return false;
    }
    return true;
}

void editproduct(string &product) {
    int i;
    while (!all_of(product.begin(), product.end(), [](unsigned char c) { return isalnum(c) || isspace(c) || c == ',' || c == '-'; })) {
        cout << "  Wrong enter! Product/type contains only numbers, characters, spaces, ',', '-': ";
        getline(cin, product);
    }
    product[0] = toupper(product[0]);
    for (i=0; i < product.length(); i++){
        if (isspace(product[i-1])){
            product[i] = toupper(product[i]);
        }
    }
}

bool isInteger(string str)
{
    if (str.empty()) return false;
    for (int i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]) && str[i] != '-') return false;
    }
    return true;
}

bool isIDExist(string ID)
{
    ifstream file("Product.txt");
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string productID;
        getline(iss, productID, ';');
        if (productID == ID)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool isbillIDExist(string ID)
{
    ifstream file("bill.txt");
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string billID;
        getline(iss, billID, ';');
        if (billID == ID)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void editID(string &ID)
{
    while (true)
    {
        getline(cin, ID);
        if (!isInteger(ID))
        {
            cout << "  Wrong enter! ID contains numbers only: ";
            continue;
        }
        if (isIDExist(ID))
        {
            cout << "  Wrong enter! ID have already exist: ";
            continue;
        }
        break;
    }
}

void editbillID(string &ID)
{
    while (true)
    {
        getline(cin, ID);
        if (!isInteger(ID))
        {
            cout << "  Wrong enter! ID contains numbers only: ";
            continue;
        }
        if (isbillIDExist(ID))
        {
            cout << "  Wrong enter! ID have already exist: ";
            continue;
        }
        break;
    }
}

void editnumber (string &number){
	string input;
	bool isNum;
	do {
		getline(cin, input);
		isNum = true;
		for (char const &c : input) {
			if (isdigit(c) == false) {
				isNum = false;
			    break;
			}
		}
		if (isNum == false) {
			cout << "  Wrong enter! Contains numbers only : ";
		}
	} while (isNum == false);
	stringstream num(input);
	num >> number;
}

void editnumberint (int &number){
	string input;
	bool isNum;
	do {
		getline(cin, input);
		isNum = true;
		for (char const &c : input) {
			if (isdigit(c) == false) {
				isNum = false;
			    break;
			}
		}
		if (isNum == false) {
			cout << "  Wrong enter! Contains numbers only : ";
		}
	} while (isNum == false);
	stringstream num(input);
	num >> number;
}

void editchoice(int &choice) {
    string enter;
    bool validChoice = false;
    while (!validChoice) {
        getline(cin, enter);
        if (isInteger(enter) && enter.length() == 1) {
            choice = stoi(enter);
            validChoice = true;
        }
        else {
            cout << "  Invalid input! Please enter a single integer: ";
        }
    }
}

void InterfaceProduct()
{
    SortField field;
	int choice, adjust, find, arrange;	
	system("cls");
	while (true) {
		cout << "\n\n\n\n\t\t\t\tNHOM 4\n";
		cout << "\t\t\t\tNGUYEN TRAN THANH TRUNG\n";
		cout << "\t\t\t\tLAM TAN PHAT\n";
		cout << "\t\t\t\tLE PHU CUONG\n";
	    cout << "               *=================================================* \n";
	    cout << "               | STT  |      SELECT FUNCTION YOU WANT TO DO      | \n";
	    cout << "               |------|------------------------------------------| \n";
	    cout << "               |  1.  |  Show product list                       | \n";
	    cout << "               |------|------------------------------------------| \n";
	    cout << "               |  2.  |  Add new product                         | \n";
	    cout << "               |------|------------------------------------------| \n";
	    cout << "               |  3.  |  Adjust product list                     | \n";
	    cout << "               |------|------------------------------------------| \n";
	    cout << "               |  4.  |  Delete product                          | \n";
	    cout << "               |------|------------------------------------------| \n";
	    cout << "               |  5.  |  Finding product                         | \n";
	    cout << "               |------|------------------------------------------| \n";
//		cout << "               |  6.  |  Arrange product                         | \n";
//	    cout << "               |------|------------------------------------------| \n";
	    cout << "               |  0.  |  Exit                                    | \n";
	    cout << "               *=================================================* \n";
	    cout << "              	         Select fuction: ";  
		editchoice(choice); 
		switch(choice){
//        case 1:
//		{
//        	system("cls");
//            displayProduct();
//            returnToPreviousFunction();
//            break;
//		}
		case 2:
        {
        	system("cls");
            string productID, name, type;
            int price, quantity, discount;
            cout << "  Enter product ID: ";
            editID(productID);
            cout << "  Enter product name: ";
            getline(cin, name);
            editproduct(name);
            cout << "  Enter product type: ";
            getline(cin, type);
            editproduct(type);
            cout << "  Enter protudct price: ";
            editnumberint(price);
            cout << "  Enter quantity: ";
            editnumberint(quantity);
            cout << "  Enter discount: "; 
			editnumberint(discount);
			cout << "  Please check your enter again \n";
			displaynewProduct(productID, name, type, price, quantity, discount);
			cout << "  If it true, enter 1; false, enter 0: ";
			editchoice(choice);
			switch (choice){
				case 0:
				{
    				system("cls");
                    break;
				}
				case 1:
				{
            		addProduct(productID, name, type, price, quantity, discount);
            		exportData("Product.txt");
            		break;
            	}
            }
            returnToPreviousFunction();
            break;
        }
        
		case 3:
        {
        	system("cls");
        	string newID;
            string newname_product;
            string newtype;
            int newprice;
            int newquantity;
            int newdiscount;
            do{
		        cout << "\n\n\n\n\t\t\t\tNHOM 4\n";
				cout << "\t\t\t\tNGUYEN TRAN THANH TRUNG\n";
				cout << "\t\t\t\tLAM TAN PHAT\n";
				cout << "\t\t\t\tLE PHU CUONG\n";
			    cout << "               *=================================================* \n";
			    cout << "               | STT  |       SELECT ADJUST FUNCTION             | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  1.  |  Adjust by ID                            | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  2.  |  Adjust by product name                  | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  0.  |  Exit                                    | \n";
			    cout << "               *=================================================* \n";
			    cout << "               	      Select function: ";
				editchoice(adjust);
				switch(adjust){ 
				case 1:
				{
					system("cls");
					string ID;
					string productID = "productID"; 
					cout << "  Find by ID: ";      	
					editnumber(ID);
		    		findProduct(ID,productID);
		    		vector<Product*> productsToFind = searchProduct(ID, productID);
    				if (productsToFind.empty())
    				{
						break;
    				}
    				cout << "  Enter new ID: ";
    				editnumber(newID);
		            cout << "  Enter new product name: ";
		            getline(cin, newname_product);
		            editproduct(newname_product);
		            cout << "  Enter new type: ";
		            getline(cin, newtype);
		            editproduct(newtype);
		            cout << "  Enter new price: ";
		            editnumberint(newprice);
		            cout << "  Enter new quantity: ";
		            editnumberint(newquantity);
		            cout << "  Enter new discount: ";
					editnumberint(newdiscount);
					cout << "  Please check your enter again \n";
					displaynewadjustProduct(newID, newname_product, newtype, newprice, newquantity, newdiscount);
					cout << "  If it true, enter 1; false, enter 0: ";
					editchoice(choice);                       
 					switch (choice){
						case 0:
						{
		    				system("cls");
		                    break;
						}
						case 1:
						{
		            		adjustProduct(ID, productID, newID, newname_product, newtype, newprice, newquantity, newdiscount);
		            		exportData("Product.txt");
		            		break;
		            	}
		            }
		            returnToPreviousFunction();		    		
		            break;
				}
				
				case 2:
				{
				    system("cls"); 
					string findname;
					string name = "name";       	
		        	cout << "  Find by name: ";	
		    		getline(cin, findname);
		    		editproduct(findname);
		    		findProduct(findname,name);
					vector<Product*> productsToFind = searchProduct(findname, name);
    				if (productsToFind.empty())
    				{
						break;
    				}
    				cout << "  Enter new ID: ";
    				editnumber(newID);
		            cout << "  Enter new name: ";
		            getline(cin, newname_product);
		            editproduct(newname_product);
		            cout << "  Enter new type: ";
		            getline(cin, newtype);
		            editproduct(newtype);
		            cout << "  Enter new price: ";
					editnumberint(newprice);
		            cout << "  Enter new quantity: ";
					editnumberint(newquantity);
					cout << "  Enter new discount: ";
					editnumberint(newdiscount);
		            cout << "  Please check your enter again \n";
					displaynewadjustProduct(newID, newname_product, newtype, newprice, newquantity, newdiscount);
					cout << "  If it true, enter 1; false, enter 0: ";
					cin >> choice;
					switch (choice){
						case 0:
						{
		    				system("cls");
		                    break;
						}
						case 1:
						{
		            		adjustProduct(findname, name, newID, newname_product, newtype, newprice, newquantity, newdiscount);
		            		exportData("Product.txt");
		            		break;
		            	}
		            }
		            returnToPreviousFunction();		    		
		            break;
				} 
				
				default:
				{
    				system("cls");
				    break;
				} 
				               
                case 0:
                {
    				system("cls");
                    break;
                }
                  			
				}
			}while (find != 0);
            break;
        }
        
        case 4:
        {
            system("cls");
			string productID;            
			cout << "  Enter the productID to be deleted: ";
			editnumber(productID);
            deleteProduct(productID);
			exportData("Product.txt");
			returnToPreviousFunction();
            break;
        }
        
         case 5:
        {
        	system("cls");
			do{
				cout << "\n\n\n\n\t\t\t\tNHOM 4\n";
				cout << "\t\t\t\tNGUYEN TRAN THANH TRUNG\n";
				cout << "\t\t\t\tLAM TAN PHAT\n";
				cout << "\t\t\t\tLE PHU CUONG\n";
			    cout << "               *=================================================* \n";
			    cout << "               | STT  |          SELECT SEARCH FUNCTION          | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  1.  |  Find by ID                              | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  2.  |  Find by name                            | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  3.  |  Find by type                            | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  0.  |  Exit                                    | \n";
			    cout << "               *=================================================* \n";
			    cout << "                	      Select function: ";
				editchoice(find);   
				switch (find){ 
				case 1:
				{ 
					system("cls");
					string ID;
					string productID = "productID"; 
					cout << "  Find by ID: ";      	
		    		editnumber(ID);
		    		findProduct(ID,productID);
		    		returnToPreviousFunction();
		            break;
				} 
				
				case 2:
				{ 
					system("cls");
					string findname;
					string name = "name";       	
		        	cout << "  Find by name: ";
		    		getline(cin, findname);
		    		editproduct(findname);
		    		findProduct(findname,name);
		    		returnToPreviousFunction();
		            break;
				}
				
				case 3:
				{ 
					system("cls");
					string findtype; 
					string type = "type";       	
		        	cout << "  Find by type:";
		    		getline(cin, findtype);
		    		editproduct(findtype);
		    		findProduct(findtype,type);
		    		returnToPreviousFunction();
		            break;
				}
				
				default:
				{
    				system("cls");
    				break;
				} 
				               
                case 0:
                {
    				system("cls");
                    break;
                }
                 			
				}
			}while (find != 0);
            break;
        }
        
        case 1:
        {
        	system("cls");
            do
            {
				cout << "\n\n\n\n\t\t\t\tNHOM 4\n";
				cout << "\t\t\t\tNGUYEN TRAN THANH TRUNG\n";
				cout << "\t\t\t\tLAM TAN PHAT\n";
				cout << "\t\t\t\tLE PHU CUONG\n";
			    cout << "               *=================================================* \n";
			    cout << "               | STT  |     	 SELECT ARRANGE FUNCTION         | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  1.  |  Arrange by ID                           | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  2.  |  Arrange by name                         | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  3.  |  Arrange by type                         | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  4.  |  Arrange by price                        | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  0.  |  Exit                                    | \n";
			    cout << "               *=================================================* \n";
			    cout << "                	      Select function: ";
                editchoice(arrange);     
				switch (arrange)
                {
				case 1:
                {
                    system("cls");
					cout << "  Arrange by ID:\n";
                    displaySortedProduct("productID");
                    exportData("Product.txt");
                    returnToPreviousFunction();
                    break;
                }                
                
                case 2:
                {
                    system("cls");
					cout << "  Arrange by name:\n";
                    displaySortedProduct("name");
                    exportData("Product.txt");
                    returnToPreviousFunction();
                    break;
                }
                
                case 3:
                {
                    system("cls");
					cout << "  Arrange by type:\n";
                    displaySortedProduct("type");
                    exportData("Product.txt");
                    returnToPreviousFunction();
                    break;
                }
                
                case 4:
                {
                    system("cls");
					cout << "  Arrange by price:\n";
                    displaySortedProduct("price");
                    exportData("Product.txt");
                    returnToPreviousFunction();
                    break;
                }
                
                default:
				{
    				system("cls");
    				break;
				} 
				               
                case 0:
                {
    				system("cls");
                    break;
                }
                }
            } while (arrange != 0);
            break;
        }
        
        default:
			{
    			system("cls");
				break;
			}
			
	    	case 0:
	        	system("cls");
	            return;
	        }
	    cout << endl;
	    system("cls");
	}
    return;	
}

//------------------------------------------------------------------------------------------------------------------------------
void InterfaceBill() {
	system("cls");
	int choice;
	string YN;
	int serial;
	while (true) {
		cout << "\n\n\n\n\t\t\t\tNHOM 4\n";
		cout << "\t\t\t\tNGUYEN TRAN THANH TRUNG\n";
		cout << "\t\t\t\tLAM TAN PHAT\n";
		cout << "\t\t\t\tLE PHU CUONG\n";
	    cout << "               *=================================================* \n";
	    cout << "               | STT  |      SELECT FUNCTION YOU WANT TO DO      | \n";
	    cout << "               |------|------------------------------------------| \n";
	    cout << "               |  1.  |  Show all bill                           | \n";
	    cout << "               |------|------------------------------------------| \n";
	    cout << "               |  2.  |  Add new bill                            | \n";
	    cout << "               |------|------------------------------------------| \n";
	    cout << "               |  3.  |  Find bill ID                            | \n";
	    cout << "               |------|------------------------------------------| \n";
	    cout << "               |  4.  |  Revenue                                 | \n";
	    cout << "               |------|------------------------------------------| \n";
	    cout << "               |  0.  |  Exit                                    | \n";
	    cout << "               *=================================================* \n";
		cout << "                  	   Select function: ";
		editchoice (choice);     
		switch (choice) {
			case 1:
			{
				system("cls");
            	DisplayBill();
            	returnToPreviousFunction();
                break;
			}
			
			case 2:
			{
				system("cls");
            	displayProduct();
				string billID;
	            cout << "\tEnter date: ";
	            string date;
                bool valid_date = false;
                do {
                    cin >> date;
                    valid_date = editdate(date);
                } while (!valid_date);
                cin.ignore();
                cout << "\tEnter Bill ID: ";
                editbillID(billID);
                do {
                	serial++;
                    string productID = "productID";
                    string ProductID;
                    cout << "\tEnter product ID: ";
                    cin >> ProductID;
                    int quantitybuy;
                    cout << "\tHow many do you want to buy: ";
                    cin >> quantitybuy;
                    vector<Product*> BuyProduct = searchProduct(ProductID, productID);
                    if (BuyProduct.empty())
                    {
                        cout << "\tProduct not found." << endl;
                        system("cls");
                        return;
                    }
                    if (BuyProduct[0]->quantity == 0)
                    {
                        cout << "\tWe currently don't have this product'." << endl;
                        return;
                    }
	                int total;
	                int remain;
	                float dis;
	                remain = BuyProduct[0]->quantity - quantitybuy;
	                if(BuyProduct[0]->discount == 0)
	                {
	                     total = quantitybuy * BuyProduct[0]->price;
	                }
	                else {
	                	dis = BuyProduct[0]->discount / 100;
	                	total = quantitybuy * (BuyProduct[0]->price - BuyProduct[0]->price * dis);
						}
	                if (remain < 0)
	                {
		                cout << "\tSorry we don't have enough" << endl;
		                remain = BuyProduct[0]->quantity;
		                cout << "\tChange a mount of quantity product: ";
		                cin >> quantitybuy;
	                }
                    BuyProduct[0]->quantity=remain;
                    exportData("Product.txt");
                    addCustomer(billID, date, serial, BuyProduct[0]->name, quantitybuy, total);
                    exportDatabill("bill.txt");
                    cout << "\tPress 'Y' or 'y' to countinue to buy another product ?: " << endl;
          			cin >> YN;
                    } while(YN=="y" || YN=="Y");
                    serial = 0;
                    cin.ignore();
				    break;
				}
			
			case 3:
				{
					system("cls");
					string billID;
					cout << "  Enter the Bill ID to find: ";
					editnumber(billID);
					findBill(billID,"billID");
			        returnToPreviousFunction();
			        break;
				}
				
			case 4:
				{
					system("cls"); 
					int sum;
					int revenue;
					do
            		{
						cout << "\n\n\n\n\t\t\t\tNHOM 4\n";
						cout << "\t\t\t\tNGUYEN TRAN THANH TRUNG\n";
						cout << "\t\t\t\tLAM TAN PHAT\n";
						cout << "\t\t\t\tLE PHU CUONG\n";
			    		cout << "               *=================================================* \n";
	    				cout << "               | STT  |      SELECT FUNCTION YOU WANT TO DO      | \n";
	    				cout << "               |------|------------------------------------------| \n";
	    				cout << "               |  1.  |  Revenue by day                          | \n";
	    				cout << "               |------|------------------------------------------| \n";
	    				cout << "               |  2.  |  Revenue by month                        | \n";
	    				cout << "               |------|------------------------------------------| \n";
	    				cout << "               |  3.  |  Revenue by year                         | \n";
	    				cout << "               |------|------------------------------------------| \n";
	    				cout << "               |  0.  |  Exit                                    | \n";
	    				cout << "               *=================================================* \n";
						cout << "                  	   Select function: ";
                		editchoice(revenue);
                		switch(revenue)
                		{
                			case 1:
                			{
                				system("cls");
                				string date;
                				cout << "  Type date you want to see revenue (dd/mm/yyyy): ";
                				bool valid_date = false;
                				do {
                    			cin >> date;
                    			valid_date = editdate(date);
                				} while (!valid_date);
                				cin.ignore();
                				findBill(date,"date");
                				ifstream revenue("bill.txt"); 
                                string line;
               					while (getline(revenue, line)) {           
                              	size_t pos = line.find_first_of(";");
                              	size_t pos2 = line.find_first_of(";",pos+1);
                               	string date2 = line.substr(pos, pos2 - pos);
                            	removeSpaces(date2);
                            	if(date2 == "; "+date)
                             	{
                                    size_t pos1 = line.find_last_of(';');    
                                    string last_value_str = line.substr(pos1 + 1);   
                                    int total = stoi(last_value_str);
                                    sum = sum + total;
                                }
                                else
                                {
                                    sum = sum + 0;
                                }
                            }
                				cout << "                    Revenue: " << sum << endl;
                				sum = 0;
                				returnToPreviousFunction();
                				break;
                			}
                			
                			case 2:
                			{
                				system("cls");
                				string month;
                				cout << "  Type month you want to see revenue (mm/yyyy): ";
                				bool valid_month = false;
                				do {
                    			cin >> month;
                    			valid_month = editmonth(month);
                				} while (!valid_month);
                				cin.ignore();
                				findBill(month,"month");
                				ifstream revenue("bill.txt"); 
                                string line;
               					while (getline(revenue, line)) {           
                              	size_t pos = line.find_first_of(";");
                              	size_t pos2 = line.find_first_of(";",pos+1);
                              	size_t pos3 = line.find_first_of("/");
                               	string month2 = line.substr(pos3, pos2 - pos3);
                            	removeSpaces(month2);
                            	if(month2 == "/"+month)
                             	{
                                    size_t pos1 = line.find_last_of(';');    
                                    string last_value_str = line.substr(pos1 + 1);   
                                    int total = stoi(last_value_str);
                                    sum = sum + total;
                                }
                                else
                                {
                                    sum = sum + 0;
                                }
                            }
                				cout << "                    Revenue: " << sum << endl;
                				sum = 0;
                				returnToPreviousFunction();
                				break;
                			}
                			
                			case 3:
                			{
                				system("cls");
                				string year;
                				cout << "  Type year you want to see revenue (yyyy): ";
                				bool valid_year = false;
                				do {
                    			cin >> year;
                    			valid_year = edityear(year);
                				} while (!valid_year);
                				cin.ignore();
                				findBill(year,"year");
                				ifstream revenue("bill.txt"); 
                                string line;
               					while (getline(revenue, line)) {           
                              	size_t pos = line.find_first_of(";");
                              	size_t pos2 = line.find_first_of(";",pos+1);
                              	size_t pos3 = line.find_first_of("/");
                              	size_t pos4 = line.find_first_of("/",pos3+1);
                               	string year2 = line.substr(pos4, pos2 - pos4);
                            	removeSpaces(year2);
                            	if(year2 == "/"+year)
                             	{
                                    size_t pos1 = line.find_last_of(';');    
                                    string last_value_str = line.substr(pos1 + 1);   
                                    int total = stoi(last_value_str);
                                    sum = sum + total;
                                }
                                else
                                {
                                    sum = sum + 0;
                                }
                            }
                				cout << "                    Revenue: " << sum << endl;
                				sum = 0;
                				returnToPreviousFunction();
                				break;
                			}
                			
                			default:
							{
    							system("cls");
    							break;
							} 
				               
                			case 0:
                			{
    							system("cls");
                    			break;
                			}
                
                		}
                	} while (revenue != 0);
			    }
				
			default:
				{
    				system("cls");
    				break;
				} 
				               
                case 0:
                {
    				system("cls");
                    return;
                }
            }
			cout << endl;
	        system("cls");
	}
    return;	
} 

void begin ()
{
	int choice;
	while (true)
	{
				cout << "\n\n\n\n\t\t\t\tNHOM 4\n";
				cout << "\t\t\t\tNGUYEN TRAN THANH TRUNG\n";
				cout << "\t\t\t\tLAM TAN PHAT\n";
				cout << "\t\t\t\tLE PHU CUONG\n\n";
			    cout << "               *=================================================* \n";
			    cout << "               | STT  |     	      CHOOSE ROLE                | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  1.  |  Admin                                   | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  2.  |  Bill                                    | \n";
			    cout << "               |------|------------------------------------------| \n";
			    cout << "               |  0.  |  Exit the program                        | \n";
			    cout << "               *=================================================* \n";
				cout << "                         Select: ";
		editchoice(choice);
        switch (choice)
        {
    		case 1:
    		{
    			system("cls");
				InterfaceProduct();
				break;
			}
			case 2:
    		{
    			system("cls");
				InterfaceBill();
				break;
			}
			default:
			{
    			system("cls");
				break;
			}
       	 	case 0:
        	{
        		cout << "  Exiting...." << endl;
        		system("cls");
            	return;
        	}
        	cout << endl;
        	system("cls");
    	}
    }
}

int main(){
	system("cls");
	readFromFile("Product.txt");
	readFromFilebill("bill.txt");
	begin();
}
