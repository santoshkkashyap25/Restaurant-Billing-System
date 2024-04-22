#include "products.h"
#include <fstream> // Include the necessary header file for file operations
#include <sstream> // Include the necessary header file for std::stringstream
#include <iostream>



int Restaurant::findIndex(string productCode) {
    readProductsFromFile(); // Ensure products are read from the file before searching

    for (int i = 0; i < productCount; i++) {
        if (productCodes[i] == productCode) {
            return i;
        }
    }

    return -1; // Return -1 if productCode is not found
}



void Restaurant::readProductsFromFile() {
    ifstream inputFile("products.txt"); // Open the file for reading
    string line;

    if (inputFile.is_open()) {
        // Display header
        cout << "\t\tCode\tProduct\t\tPrice" << endl;
        cout << "\t\t------|---------------|------" << endl;

        // Read each line from the file and display product information
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string productCode, product;
            float price;

            // Extract product information from the line
            getline(ss, productCode, ',');
            getline(ss, product, ',');
            ss >> price;

            // Display product information
            cout << "\t\t" << productCode << "\t" << product << "\t" << price << endl;
        }

        // Close the file
        inputFile.close();
    } else {
        // Display an error message if the file cannot be opened
        cout << "Unable to open file!" << endl;
    }
}


void Restaurant::showProducts() {
    ifstream inputFile("products.txt"); // Open the products file for reading
    string line;

    if (inputFile.is_open()) {
        // Display header
        cout << "\t\tCode\tProduct\t\tPrice" << endl;
        cout << "\t\t------|---------------|------" << endl;

        // Read each line from the file and display product information
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string productCode, product;
            float price;

            // Extract product information from the line
            getline(ss, productCode, ',');
            getline(ss, product, ',');
            ss >> price;

            // Display product information
            cout << "\t\t" << productCode << "\t" << product << "\t" << price << endl;
        }

        // Close the file
        inputFile.close();
    } else {
        // Display an error message if the file cannot be opened
        cout << "Unable to open file!" << endl;
    }
}

bool Restaurant::searchOne(string productCode) {
    ifstream inputFile("products.txt");
    string line;
    bool found = false;

    if (inputFile.is_open()) {
        cout << "\t\tCode\tProduct\t\tPrice" << endl;
        cout << "\t\t------|---------------|------" << endl;

        while (getline(inputFile, line)) {
            stringstream ss(line);
            string code, product;
            float price;

            getline(ss, code, ',');
            getline(ss, product, ',');
            ss >> price;

            if (code == productCode) {
                found = true;
                cout << "\t\t" << code << "\t" << product << "\t" << price << endl;
                break; // Stop searching once the product is found
            }
        }

        inputFile.close();
    } else {
        cout << "Unable to open file!" << endl;
        return false; // Return false if unable to open the file
    }

    if (!found) {
        cout << "Product with code " << productCode << " not found." << endl;
    }

    return found; // Return whether the product was found or not
}
