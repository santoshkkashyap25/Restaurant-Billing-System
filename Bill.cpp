#include "Bill.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

BillDesk::BillDesk() {
    billAmount = 0;
    billProdCount = 0;
}

// Function to generate a unique ID for the bill directory
string generateUniqueID() {
    time_t now = time(0);
    char* dt = ctime(&now);
    string uniqueID = string(dt);

    // Convert characters to be removed into a character array
    const char charsToRemove[] = {' ', ':', '\n'};

    // Iterate through the character array and erase each character from the uniqueID string
    for (char c : charsToRemove) {
        uniqueID.erase(remove(uniqueID.begin(), uniqueID.end(), c), uniqueID.end());
    }

    return uniqueID;
}


void BillDesk::billAddProduct(string productCode) {
    ifstream inputFile("products.txt"); // Open the products file for reading
    ofstream outputFile("customer.txt", ios::app); // Open the customer file in append mode

    if (inputFile.is_open() && outputFile.is_open()) {
        string line;
        bool found = false;

        // Iterate through each line in the products.txt file
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string code, product;
            float price;

            // Extract product information from the line
            getline(ss, code, ',');
            getline(ss, product, ',');
            ss >> price;

            // Check if the code matches the desired product code
            if (code == productCode) {
                // Write the details of the product to the customer.txt file
                outputFile << line << endl;
                cout << "\tProduct added to the bill!" << endl;
                found = true;
                break; // Stop searching once the product is found
            }
        }

        // If the product code is not found, display an error message
        if (!found) {
            cout << "Product with code " << productCode << " not found." << endl;
        }

        // Close the files
        inputFile.close();
        outputFile.close();
    } else {
        cout << "Unable to open file!" << endl;
    }
}


void BillDesk::billDeleteProduct(string productCode) {
    ifstream inputFile("customer.txt");
    ofstream tempFile("temp.txt"); // Temporary file to store modified contents

    if (inputFile.is_open() && tempFile.is_open()) {
        string line;
        bool found = false;

        // Iterate through each line in the customer.txt file
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string code, product;
            float price;

            // Extract product information from the line
            getline(ss, code, ',');
            getline(ss, product, ',');
            ss >> price;

            // Check if the code matches the desired product code
            if (code == productCode) {
                found = true;
                continue; // Skip writing this line to temp file
            }

            // Write the line to the temporary file
            tempFile << line << endl;
        }

        // Close the files
        inputFile.close();
        tempFile.close();

        if (found) {
            // Replace the original file with the modified contents
            if (remove("customer.txt") != 0) {
                perror("Error deleting customer.txt");
            }
            if (rename("temp.txt", "customer.txt") != 0) {
                perror("Error renaming temp.txt");
            } else {
                cout << "\tProduct removed from the bill!" << endl;
            }
        } else {
            cout << "Product with code " << productCode << " not found in the bill." << endl;
        }
    } else {
        cout << "Unable to open files!" << endl;
    }
}


void BillDesk::checkBill() {
    ifstream customerFile("customer.txt");

    if (customerFile.is_open()) {
        string line;
        int itemCount = 0;

        cout << "\n\t\t\tYour Product Bill" << endl;
        cout << "\t\t\t_________________\n\n" << endl;

        cout << "\t\tSl\tProduct\t\tPrice" << endl;
        cout << "\t\t----|---------------|--------" << endl;

        // Iterate through each line in the customer.txt file
        while (getline(customerFile, line)) {
            stringstream ss(line);
            string code, product;
            float price;

            // Extract product information from the line
            getline(ss, code, ',');
            getline(ss, product, ',');
            ss >> price;

            // Display product details
            cout << "\t\t" << ++itemCount << ".\t" << product << "\t" << price << endl;
        }

        cout << "\t\t______________________________" << endl;
        cout << "\n\t\t\t\t\tTHANKS" << endl;

        // Close the file
        customerFile.close();
    } else {
        cout << "Unable to open customer file!" << endl;
    }
}

void BillDesk::generateBill() {
    ifstream inputFile("customer.txt");
    ofstream billFile("bill.txt");

    if (inputFile.is_open() && billFile.is_open()) {
        string line;
        float totalAmount = 0.0f;
        int itemCount = 0;

        // Write bill header
        billFile << "\t\t\tYour Product Bill" << endl;
        billFile << "\t\t\t_________________\n\n" << endl;

        billFile << "\t\tSl\tProduct\t\tPrice" << endl;
        billFile << "\t\t----|---------------|--------" << endl;

        // Iterate through each line in the customer.txt file
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string code, product;
            float price;

            // Extract product information from the line
            getline(ss, code, ',');
            getline(ss, product, ',');
            ss >> price;

            // Write product details to bill file
            billFile << "\t\t" << ++itemCount << ".\t" << product << "\t" << price << endl;

            // Update total amount
            totalAmount += price;
        }

        // Write total amount to bill file
        billFile << "\t\t______________________________" << endl;
        billFile << "\t\t\t\tTotal:\t" << totalAmount << endl;
        billFile << "\n\t\t\t\t\tTHANKS" << endl;

        cout << "Bill generated successfully. Check bill.txt file." << endl;

        // Close the files
        inputFile.close();
        billFile.close();

        // Generate a unique ID for the bill directory
        string uniqueID = generateUniqueID();

        // Create a directory with the unique ID
        string command = "mkdir " + uniqueID;
        system(command.c_str());

        // Move the bill file to the directory
        string moveCommand = "move bill.txt " + uniqueID;
        system(moveCommand.c_str());

        // Remove the customer.txt file
        remove("customer.txt");
    } else {
        cout << "Unable to open files!" << endl;
    }
}