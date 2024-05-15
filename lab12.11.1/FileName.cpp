#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Subscriber {
    std::string phoneNumber;
    int callDuration; 
};

struct Node {
    Subscriber data;
    Node* next;
};

class TelephoneDirectory {
private:
    Node* head;

public:
    TelephoneDirectory() : head(nullptr) {}

    Node* getHead() const {
        return head;
    }

    void addSubscriber(const std::string& phoneNumber, int callDuration) {
        Node* newNode = new Node;
        newNode->data.phoneNumber = phoneNumber;
        newNode->data.callDuration = callDuration;
        newNode->next = nullptr;

        if (!head) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void removeSubscriber(const std::string& phoneNumber) {
        if (!head)
            return;

        Node* temp = head;
        Node* prev = nullptr;

        while (temp && temp->data.phoneNumber != phoneNumber) {
            prev = temp;
            temp = temp->next;
        }

        if (temp) {
            if (prev)
                prev->next = temp->next;
            else
                head = temp->next;
            delete temp;
        }
    }

    void sortDirectory() {
        if (!head)
            return;

        Node* current = head;
        Node* index = nullptr;
        Subscriber temp;

        while (current) {
            index = current->next;

            while (index) {
                if (current->data.phoneNumber > index->data.phoneNumber) {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }

    void viewDirectory() {
        Node* temp = head;
        while (temp) {
            std::cout << "Phone number: " << temp->data.phoneNumber << ", Call duration: " << temp->data.callDuration << " minutes\n";
            temp = temp->next;
        }
    }

    void printPaymentMessage(const std::string& phoneNumber) {
        Node* temp = head;
        while (temp) {
            if (temp->data.phoneNumber == phoneNumber) {
                std::cout << "Payment message for phone number " << phoneNumber << ": Please pay " << temp->data.callDuration * 0.1 << " USD\n";
                return;
            }
            temp = temp->next;
        }
        std::cout << "Phone number " << phoneNumber << " not found in the directory.\n";
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            return;
        }

        Node* temp = head;
        while (temp) {
            file << temp->data.phoneNumber << " " << temp->data.callDuration << "\n";
            temp = temp->next;
        }

        file.close();
        std::cout << "Data saved to file: " << filename << std::endl;
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            return;
        }

        clear();

        std::string phoneNumber;
        int callDuration;
        while (file >> phoneNumber >> callDuration) {
            addSubscriber(phoneNumber, callDuration);
        }

        file.close();
        std::cout << "Data loaded from file: " << filename << std::endl;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    ~TelephoneDirectory() {
        clear();
    }
};

int main() {
    TelephoneDirectory directory;

    int choice;
    std::string filename;
    bool running = true;
    while (running) {
        std::cout << "\nTelephone Directory Menu:\n";
        std::cout << "1. Add Subscriber\n";
        std::cout << "2. Remove Subscriber\n";
        std::cout << "3. Sort Directory\n";
        std::cout << "4. View Directory\n";
        std::cout << "5. Print Payment Message\n";
        std::cout << "6. Save Directory to File\n";
        std::cout << "7. Load Directory from File\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string phoneNumber;
            int callDuration;
            std::cout << "Enter phone number: ";
            std::cin >> phoneNumber;
            std::cout << "Enter call duration (in minutes): ";
            std::cin >> callDuration;
            directory.addSubscriber(phoneNumber, callDuration);
            break;
        }
        case 2: {
            std::string phoneNumber;
            std::cout << "Enter phone number to remove: ";
            std::cin >> phoneNumber;
            directory.removeSubscriber(phoneNumber);
            break;
        }
        case 3:
            directory.sortDirectory();
            std::cout << "Directory sorted.\n";
            break;
        case 4:
            std::cout << "Telephone Directory:\n";
            directory.viewDirectory();
            break;
        case 5: {
            std::string phoneNumber;
            std::cout << "Enter phone number: ";
            std::cin >> phoneNumber;
            directory.printPaymentMessage(phoneNumber);
            break;
        }
        case 6: {
            std::cout << "Enter filename to save: ";
            std::cin >> filename;
            directory.saveToFile(filename);
            break;
        }
        case 7: {
            std::cout << "Enter filename to load: ";
            std::cin >> filename;
            directory.loadFromFile(filename);
            break;
        }
        case 8:
            running = false;
            break;
        default:
            std::cout << "Invalid choice! Please enter a number between 1 and 8.\n";
        }
    }

    return 0;
}
