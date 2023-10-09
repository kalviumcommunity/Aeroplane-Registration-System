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
       
        return 0; 
    }
};

void addTicket() {
    string passengerName, source, destination, flightNumber, date;
    int paymentChoice;

    cin.ignore(); 

    cout << "Enter passenger name: ";
    getline(cin, passengerName);

    cout << "Enter source: ";
    getline(cin, source);

    cout << "Enter destination: ";
    getline(cin, destination);

    cout << "Enter flight number: ";
    getline(cin, flightNumber);

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

    Ticket newTicket(passengerName, source, destination, flightNumber, date, paymentMethod);
    newTicket.saveTicket();

    cout << "Ticket saved successfully!" << endl;
}

void fetchAllTickets() {
    
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
