#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class PaymentMethod {
public:
    virtual void makePayment() = 0;
};

class CreditCardPayment : public PaymentMethod {
public:
    void makePayment() override {
        cout << "Payment made using credit card." << endl;
    }
};

class CashPayment : public PaymentMethod {
public:
    void makePayment() override {
        cout << "Payment made using cash." << endl;
    }
};

class Ticket {
private:
    string passengerName;
    string source;
    string destination;
    string flightNumber;
    string date;
    PaymentMethod* payment;
     static int totalTickets;//creating an static variable 

public:

    Ticket() : payment(nullptr) {}

   
    Ticket(string passengerName, string source, string destination, string flightNumber, string date, PaymentMethod* payment) {
        this->passengerName = passengerName;
        this->source = source;
        this->destination = destination;
        this->flightNumber = flightNumber;
        this->date = date;
        this->payment = payment;
    }


    ~Ticket() {
        delete payment; 
    }

    void saveTicket() {
        
    }

    void displayTicket() {
        cout << "Passenger Name: " << this->passengerName << endl;
        cout << "Source: " << this->source << endl;
        cout << "Destination: " << this->destination << endl;
        cout << "Flight Number: " << this->flightNumber << endl;
        cout << "Date: " << this->date << endl;

        if (payment) {
            cout << "Payment Method: ";
            payment->makePayment();
        }
    }

    string getPassengerName() {
        return passengerName;
    }

    static int getTotalTickets() {
        return totalTickets;
        return 0; 
    }
};
int Ticket::totalTickets = 0;//initilizing total ticket as 0

int numTickets = 0;
const int maxTickets = 100;//fixing the size of total ticet to b 100

void addTicket() {
    if (numTickets >= maxTickets) {
        cout << "Maximum number of tickets reached. Cannot add more tickets." << endl;
        return;
    }

    string name, src, dest, flight, date;
    int paymentChoice;

    cin.ignore(); 

    cout << "Enter passenger name: ";
    getline(cin, name);

    cout << "Enter source: ";
    getline(cin, src);

    cout << "Enter destination: ";
    getline(cin, dest);

    cout << "Enter flight number: ";
    getline(cin, flight);

    cout << "Enter date: ";
    getline(cin, date);

    cout << "Select Payment Method:" << endl;
    cout << "1. Credit Card" << endl;
    cout << "2. Cash" << endl;
    cout << "Enter your choice: ";
    cin >> paymentChoice;

    PaymentMethod* paymentMethod = nullptr;

    switch (paymentChoice) {
        case 1:
            paymentMethod = new CreditCardPayment();
            break;
        case 2:
            paymentMethod = new CashPayment();
            break;
        default:
            cout << "Invalid payment method choice." << endl;
            return;
    }

    Ticket newTicket(name, src, dest, flight, date, paymentMethod);
    newTicket.saveTicket();


    cout << "Ticket saved successfully!" << endl;
}

void fetchAllTickets() {
    if (numTickets == 0) {
        cout << "No tickets available." << endl;
        return;
    }

    
}

void searchTicket() {  
    
}

int main() {
    int choice;

    while (true) {
        cout << "\n1. Add Ticket\n2. Fetch All Tickets\n3. Search Ticket\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTicket();
                break;
            case 2:
                fetchAllTickets();
                break;
            case 3:
                searchTicket();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
