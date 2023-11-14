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

    // Static variable to keep track of the total number of tickets created.
    static int totalTickets;

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
        ofstream file((passengerName + "_ticket.txt").c_str());

        if (!file.is_open()) {
            cout << "Error: Unable to create the ticket file!" << endl;
            return;
        }

        file << "Passenger Name: " << passengerName << endl;
        file << "Source: " << source << endl;
        file << "Destination: " << destination << endl;
        file << "Flight Number: " << flightNumber << endl;
        file << "Date: " << date << endl;

        if (payment) {
            file << "Payment Method: ";
            payment->makePayment();
        }

        file.close();
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

    // Static function to get the total number of tickets.
    static int getTotalTickets() {
        return totalTickets;
    }
};

// Initialize the static variable.
int Ticket::totalTickets = 0;

Ticket ticketDatabase[100];
int numTickets = 0;
const int maxTickets = 100;

void addTicket() {
    if (numTickets >= maxTickets) {
        cout << "Maximum number of tickets reached. Cannot add more tickets." << endl;
        return;
    }

    string name, src, dest, flight, date;
    int paymentChoice;

    cin.ignore(); // Clear the newline character left in the buffer

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

    ticketDatabase[numTickets++] = newTicket;

    cout << "Ticket saved successfully!" << endl;
}

void fetchAllTickets() {
    if (numTickets == 0) {
        cout << "No tickets available." << endl;
        return;
    }

    for (int i = 0; i < numTickets; ++i) {
        ticketDatabase[i].displayTicket();
        cout << endl;
    }
}

void searchTicket() {
    cin.ignore(); // Clear the newline character left in the buffer
    string name;
    cout << "Enter passenger name to search: ";
    getline(cin, name);

    bool found = false;

    for (int i = 0; i < numTickets; ++i) {
        if (ticketDatabase[i].getPassengerName() == name) {
            ticketDatabase[i].displayTicket();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Ticket not found for passenger: " << name << endl;
    }
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
