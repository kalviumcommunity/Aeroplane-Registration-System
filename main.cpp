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
    }

    static int getTotalTickets() {
    }
};

void addTicket() {
	string passengerName, source, destination, flightNumber, date;
    int paymentMethod;

    Ticket newTicket(passengerName, source, destination, flightNumber, date, paymentMethod);
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