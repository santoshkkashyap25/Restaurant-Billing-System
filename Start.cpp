#include <iostream>

#include "Bill.h"
#include "Admin.h"
using namespace std;

RestAdmin Admin;
BillDesk Desk;

string query = "stay";

void welcomeMessage() {
    cout << "\n";
    cout << "*******************************************" << endl;
    cout << "*                                         *" << endl;
    cout << "*   Welcome to the Restaurant Booking     *" << endl;
    cout << "*             System                      *" << endl;
    cout << "*                                         *" << endl;
    cout << "*******************************************" << endl;
    cout << "\n";
    cout << "Press Enter to continue..." << endl;
    
    // Ignore any input until Enter is pressed
    while (cin.get() != '\n') {}

    cout << "\n";
    cout << "Please enter 'admin' for Administration Access or 'desk' for Billing Access" << endl;
}

void headerAdminMessage() {
    cout << "\n";
    cout << "*********************************************************" << endl;
    cout << "*                                                       *" << endl;
    cout << "*          Welcome to the Admin Panel                   *" << endl;
    cout << "*          Restaurant Booking System                    *" << endl;
    cout << "*                                                       *" << endl;
    cout << "*********************************************************" << endl;
    cout << "\n";
    cout << "                      ---Commands---                     " << endl;
    cout << "1. 'add'    - Add a new product " << endl;
    cout << "2. 'update' - Update a product " << endl;
    cout << "3. 'show'   - Show all products" << endl;
    cout << "4. 'delete' - Delete a product" << endl;
    cout << "5. 'search' - Search for a product" << endl;
    cout << "6. 'exit'   - Exit the Admin Panel" << endl;
    cout << "\n";
}

void headerBillMessage() {
    cout << "\n";
    cout << "*********************************************************" << endl;
    cout << "*                                                       *" << endl;
    cout << "*       Restaurant Booking System                       *" << endl;
    cout << "*                                                       *" << endl;
    cout << "*********************************************************" << endl;
    cout << "\n";
    cout << "                      --- Commands ---                  " << endl;
    cout << "1. 'add'    - Add a new product " << endl;
    cout << "2. 'bill'   - Generate bill" << endl;
    cout << "3. 'show'   - Show all products" << endl;
    cout << "4. 'check' - Show bill " << endl;
    cout << "5. 'delete' - Delete a product " << endl;
    cout << "6. 'search' - Search for a product " << endl;
    cout << "7. 'exit'   - Exit the window" << endl;
    cout << "\n";
}

void runAdminCommands(string query) {
    // Display the header for the Admin Panel
    headerAdminMessage();

    // Continue running commands until 'exit' is entered
    while (query != "exit") {
        if (query == "admin") {
            cout << "\n\t\tWelcome to Admin Panel" << endl;
        }
        else if (query == "show") {
            // Show all products
            Admin.readProductsFromFile();
        }
        else if (query == "add") {
            // Add a new product
            string productCode, productName;
            float price;

            cout << "\nEnter the Product Code: ";
            cin >> productCode;

            cout << "Enter the Product Name: ";
            cin.ignore(); // Ignore any previous input
            getline(cin, productName);

            cout << "Enter the Price: ";
            cin >> price;

            Admin.addProduct(productCode, productName, price);
            cout << "\nProduct Added successfully!" << endl;
        }
        else if (query == "delete") {
            // Delete a product
            string productCode;
            cout << "\nEnter the Product Code to delete: ";
            cin >> productCode;

            Admin.deleteProduct(productCode);
        }
        else if (query == "update") {
            // Update a product
            string productCode, productName;
            float price;

            cout << "\nEnter the Product Code to update: ";
            cin >> productCode;

            // Check if the product exists
            if (Admin.searchOne(productCode)) {
                cout << "Product with code " << productCode << " found." << endl;

                // Prompt for updated product name
                cout << "Enter the updated Product Name: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, productName);

                // Prompt for updated price
                cout << "Enter the updated Price: ";
                cin >> price;

                // Update the product
                Admin.updateProduct(productCode, productName, price);
                cout << "Product updated successfully!" << endl;
            } else {
                cout << "Product with code " << productCode << " not found." << endl;
            }
        }
        else if (query == "search") {
            // Search for a product
            string productCode;

            cout << "\nEnter the Product Code to search: ";
            cin >> productCode;

            Admin.searchOne(productCode);
        }
        else {
            cout << "Invalid command! Please try again." << endl;
        }

        // Prompt for the next command
        cout << "\n\nEnter a command (or 'exit' to quit): ";
        cin >> query;
        system("CLS"); // Clear the screen for clarity
        headerAdminMessage(); // Redisplay the header for clarity
    }

    // Display exit message when loop exits
    cout << "\n\nThank you for using the Admin Panel. See you again!" << endl;
}

void runBillCommands(string query) {
    headerBillMessage();

    if (query != "exit") {
        if (query == "desk") {
            cout << "\tWelcome to the Bill Desk" << endl;
        }
        else if (query == "show") {
            cout << "Displaying all available products:" << endl;
            Admin.readProductsFromFile();
        }
        else if (query == "search") {
            cout << "Please enter the product code to search:" << endl;
            string productCode;
            cin >> productCode;
            Admin.searchOne(productCode);
        }
        else if (query == "add") {
            cout << "Please enter the product code to add:" << endl;
            string productCode;
            cin >> productCode;

            // Check if the product exists
            if (Admin.searchOne(productCode)) {
                Desk.billAddProduct(productCode);
            } else {
                cout << "Product with code " << productCode << " not found." << endl;
            }
        }
        else if (query == "delete") {
            cout << "Please enter the product code to delete:" << endl;
            string productCode;
            cin >> productCode;
            Desk.billDeleteProduct(productCode);
        }
        else if (query == "check") {
            cout << "Checking your bill..." << endl;
            Desk.checkBill();
        }
        else if (query == "bill") {
            cout << "Generating bill..." << endl;
            Desk.generateBill();
        }
        else {
            cout << "\tInvalid command! Please enter a valid command." << endl;
        }

        // Prompt for the next query
        cout << "\n\nEnter your query or type 'exit' to close the window: ";
        cin >> query;
        system("CLS"); // Clear the screen for better readability
        runBillCommands(query);
    }
    else {
        remove("customer.txt");
        system("CLS");
        cout << "\nThank you for using the Bill Desk. Have a great day!\n" << endl;
    }
}


int main() {
    welcomeMessage();

    cin >> query;
    system("CLS");

    if (query == "admin") {
        runAdminCommands(query);
    }
    else if (query == "desk") {
        runBillCommands(query);
    }
}