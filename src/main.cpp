#include <iostream>
#include <string>
#include <cstdlib> // Include the header for system()
#include <fstream> // Include the header for ifstream and ofstream
using namespace std;

// ...

// Function to clear the screen
void clearScreen() {
#ifdef _WIN32 // For Windows
    system("cls");
#else // For other systems (Linux, macOS)
    system("clear");
#endif
}

// Global variables
double totalBill = 0;

class Pizza {
private:
    int orderQty, getPizzaType, getPizzaSize, pizzaPrice[3];
    string pizzaType[5], pizzaSize[3], customerName, customerContact;

public:
    Pizza();
    void getCustomerInfo(void);
    void displayPizzaMenu(void);
    void getPizzaSizeFunc(void);
    void getPizzaTypeFunc(void);
    void getOrderQuantity(void);
    void saveOrder(void);
    void displayTotalBill(void);
    void getPizzaOrder(void);
};

// Constructor
Pizza::Pizza() {
    orderQty = 0;
    getPizzaSize = 0;
    getPizzaType = 0;

    // Initialize pizzaPrice array
    pizzaPrice[0] = 500;
    pizzaPrice[1] = 1000;
    pizzaPrice[2] = 1500;

    // Initialize pizzaType array
    pizzaType[0] = "Fajita";
    pizzaType[1] = "Crown-Crust";
    pizzaType[2] = "Kabab";
    pizzaType[3] = "Vegetable";
    pizzaType[4] = "Meat";

    // Initialize pizzaSize array
    pizzaSize[0] = "Small";
    pizzaSize[1] = "Medium";
    pizzaSize[2] = "Large";
}

// Getting information of the customer
void Pizza::getCustomerInfo(void) {
    cout << "Enter your good name: ";
    cin >> customerName;
    cout << "Enter your contact no: ";
    cin >> customerContact;
    ofstream out(customerName + ".txt", ios::app);
    if (!out.is_open()) {
        cerr << "Error opening a file\n";
        return;
    }
    out << "[SIZE]   [QTY]    [ITEM]        [PRICE]\n\n";
    out.close();
}

// Display menu for pizza
void Pizza::displayPizzaMenu() {
    int exit = 0;

    cout << "\n------------------------------------------------------------------\n";
    for (auto type = 0; type < 5; ++type) {
        cout << "\t" << type << ": " << pizzaType[type] << endl;
    }
    getPizzaTypeFunc();
    cout << "\n------------------------------------------------------------------\n";
    for (auto size = 0; size < 3; ++size) {
        cout << "\t" << size << ": " << pizzaSize[size] << "    Rs." << pizzaPrice[size] << endl;
    }
    getPizzaSizeFunc();
    getOrderQuantity();
    cout << "\n------------------------------------------------------------------\n";

    cout << "\n\tWant to order more!\n\t(-1 for exit): ";
    cin >> exit;
    if (exit != -1) {
        saveOrder();
        displayPizzaMenu();
    }
    else {
        cout << "\n---------------------------------------------------------------\n";
        displayTotalBill();
    }
}

void Pizza::getPizzaTypeFunc(void) {
    cout << "\t(Pizza Type): ";
    cin >> this->getPizzaType;
    while (!(this->getPizzaType >= 0 && this->getPizzaType <= 4)) {
        cout << "\tInvalid Choice!" << endl;
        cout << "\t(Try again): " << endl;
        cin >> this->getPizzaType;
    }
}

void Pizza::getPizzaSizeFunc(void) {
    cout << "\t(Pizza Size):    ";
    cin >> this->getPizzaSize;
    while (!(this->getPizzaSize >= 0 && this->getPizzaSize <= 2)) {
        cout << "\nInvalid Choice!" << endl;
        cout << "\t(Try again): " << endl;
        cin >> this->getPizzaSize;
    }
}

void Pizza::getOrderQuantity(void) {
    cout << "\t(Pizza Quantity): ";
    cin >> orderQty;
    while (!(this->orderQty >= 0 && this->orderQty <= 30)) {
        cout << "\t(Try again): ";
        cin >> orderQty;
    }
}

void Pizza::saveOrder(void) {
    ofstream out(customerName + ".txt", ios::app);
    if (!out.is_open()) {
        cerr << "Error opening a file!\n";
        return;
    }
    out << pizzaSize[getPizzaSize] << "      " << orderQty << "      " << pizzaType[getPizzaType] << "            " << pizzaPrice[getPizzaSize] << '\n';
    totalBill = orderQty * pizzaPrice[getPizzaSize];
    out.close();
}

void Pizza::displayTotalBill(void) {
    ifstream in(customerName + ".txt");
    if (!in.is_open()) {
        cerr << "Error opening a file!\n";
        return;
    }

    string line;
    while (getline(in, line)) {
        cout << line << '\n';
    }

    in.close();
}

void Pizza::getPizzaOrder(void) {
    getCustomerInfo();
    displayPizzaMenu();
}

int main() {
    Pizza pizzaOrder;
    pizzaOrder.getPizzaOrder();
    return 0;
}
