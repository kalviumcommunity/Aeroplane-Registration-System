#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Abstract class for PaymentMethod
class PaymentMethod {
public:
    virtual void makePayment() = 0; // Pure virtual function for making payment
    virtual ~PaymentMethod() {} // Virtual destructor for polymorphic behavior
};

// Concrete class for Credit Card Payment
class CreditCardPayment : public PaymentMethod {
public:
    void makePayment() override {
        cout << "Payment made using credit card." << endl;
    }
};

// Concrete class for Cash Payment
class CashPayment : public PaymentMethod {
public:
    void makePayment() override {
        cout << "Payment made using cash." << endl;
    }
};

// Interface for Ticket Management
class TicketManagement {
public:
    virtual void addTicket() = 0; // Pure virtual function for adding a ticket
    virtual void fetchAllTickets() = 0; // Pure virtual function for fetching all tickets
    virtual void searchTicket() = 0; // Pure virtual function for searching a ticket
    virtual ~TicketManagement() {} // Virtual destructor for polymorphic behavior
};

// Class for Ticket
class Ticket {
private:
    string passengerName;
    string source;
    string destination;
    string flightNumber;
    string date;
    PaymentMethod* payment;

public:
    // Constructor for Ticket
    Ticket(string passengerName, string source, string destination, string flightNumber, string date, PaymentMethod* payment) {
        this->passengerName = passengerName;
        this->source = source;
        this->destination = destination;
        this->flightNumber = flightNumber;
        this->date = date;
        this->payment = payment;
    }

    // Destructor for Ticket
    ~Ticket() {
        delete payment;
    }

    // Function to save ticket details to a file
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

    // Function to display ticket details
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

    // Function to get passenger name
    string getPassengerName() {
        return passengerName;
    }
};

// Class implementing TicketManagement interface
class TicketManager : public TicketManagement {
private:
    Ticket ticketDatabase[100];
    int numTickets;
    const int maxTickets;

public:
    // Constructor for TicketManager
    TicketManager() : numTickets(0), maxTickets(100) {} // Initialize numTickets and maxTickets

    // Function to add a ticket
    void addTicket() override {
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

    // Function to fetch all tickets
    void fetchAllTickets() override {
        if (numTickets == 0) {
            cout << "No tickets available." << endl;
            return;
        }

        for (int i = 0; i < numTickets; ++i) {
            ticketDatabase[i].displayTicket();
            cout << endl;
        }
    }

    // Function to search for a ticket
    void searchTicket() override {
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
};

int main() {
    TicketManager manager;
    int choice;

    while (true) {
        cout << "\n1. Add Ticket\n2. Fetch All Tickets\n3. Search Ticket\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addTicket();
                break;
            case 2:
                manager.fetchAllTickets();
                break;
            case 3:
                manager.searchTicket();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
