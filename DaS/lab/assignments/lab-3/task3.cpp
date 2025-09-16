/*

Task 3:
write a simple airline ticket reservation program. The program should display a menu with the following options:
reserve a ticket, 
cancel a reservation, 
check whether a ticket is reserved for particular person, and 
display the passengers. 

the information is maintained on a alphabetized linked list of names. in simple version of the
program, assume that tickets are reserved for only one flight. In a fuller version, place no limit on the number of
flights. create a linked list of flights with each node including a pointer to a linked list of passengers

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

// Node for the passenger linked list
class PassengerNode {
public:
    std::string name;
    PassengerNode* next;

    PassengerNode(const std::string& passengerName) : name(passengerName), next(nullptr) {}
};

// Class to manage the passenger list
class ReservationSystem {
private:
    PassengerNode* head;

public:
    ReservationSystem() : head(nullptr) {}

    ~ReservationSystem() {
        while (head != nullptr) {
            PassengerNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Function to reserve a ticket (insert in alphabetical order)
    void reserveTicket(const std::string& passengerName) {
        PassengerNode* newNode = new PassengerNode(passengerName);
        if (head == nullptr || head->name > passengerName) {
            newNode->next = head;
            head = newNode;
            std::cout << "Ticket reserved for " << passengerName << "." << std::endl;
            return;
        }

        PassengerNode* current = head;
        while (current->next != nullptr && current->next->name < passengerName) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
        std::cout << "Ticket reserved for " << passengerName << "." << std::endl;
    }

    // Function to cancel a reservation
    void cancelReservation(const std::string& passengerName) {
        if (head == nullptr) {
            std::cout << "No reservations to cancel." << std::endl;
            return;
        }

        if (head->name == passengerName) {
            PassengerNode* temp = head;
            head = head->next;
            delete temp;
            std::cout << "Reservation for " << passengerName << " canceled." << std::endl;
            return;
        }

        PassengerNode* current = head;
        while (current->next != nullptr && current->next->name != passengerName) {
            current = current->next;
        }

        if (current->next == nullptr) {
            std::cout << "Passenger " << passengerName << " not found." << std::endl;
        } else {
            PassengerNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
            std::cout << "Reservation for " << passengerName << " canceled." << std::endl;
        }
    }

    // Function to check if a ticket is reserved
    void checkReservation(const std::string& passengerName) {
        PassengerNode* current = head;
        while (current != nullptr) {
            if (current->name == passengerName) {
                std::cout << "A ticket is reserved for " << passengerName << "." << std::endl;
                return;
            }
            current = current->next;
        }
        std::cout << "No ticket found for " << passengerName << "." << std::endl;
    }

    // Function to display all passengers
    void displayPassengers() {
        if (head == nullptr) {
            std::cout << "No passengers currently reserved." << std::endl;
            return;
        }
        
        std::cout << "Current Passengers:" << std::endl;
        PassengerNode* current = head;
        while (current != nullptr) {
            std::cout << "- " << current->name << std::endl;
            current = current->next;
        }
    }
};

// Main function to display menu and handle user input
int main() {
    ReservationSystem airline;
    int choice;
    std::string name;

    do {
        std::cout << "\n--- Airline Reservation Menu ---" << std::endl;
        std::cout << "1. Reserve a ticket" << std::endl;
        std::cout << "2. Cancel a reservation" << std::endl;
        std::cout << "3. Check reservation status" << std::endl;
        std::cout << "4. Display all passengers" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1:
                std::cout << "Enter passenger name to reserve: ";
                std::cin>> name;
                airline.reserveTicket(name);
                break;
            case 2:
                std::cout << "Enter passenger name to cancel: ";
                std::cin>> name;
                airline.cancelReservation(name);
                break;
            case 3:
                std::cout << "Enter passenger name to check: ";
                std::cin>> name;
                airline.checkReservation(name);
                break;
            case 4:
                airline.displayPassengers();
                break;
            case 5:
                std::cout << "Exiting program. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);

    return 0;
}