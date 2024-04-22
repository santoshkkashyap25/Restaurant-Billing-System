#include "Admin.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream> // Include the necessary header file for file operations

void RestAdmin::addProduct(string productCode, string product, float price) {
    // Add product to internal data structures
    productCodes[productCount] = productCode;
    productList[productCount] = product;
    priceList[productCount] = price;
    productCount++;

    // Open the file in append mode
    ofstream outputFile("products.txt", ios::app);
    if (outputFile.is_open()) {
        // Write the product information to the file
        outputFile << productCode << "," << product << "," << price << endl;
        // Close the file
        outputFile.close();
    } else {
        // Display an error message if the file cannot be opened
        cout << "Unable to open file!" << endl;
    }
}


void RestAdmin::deleteProduct(string productCode) {
    vector<string> updatedProductCodes;
    vector<string> updatedProductList;
    vector<float> updatedPriceList;
    string line;
    bool found = false;

    ifstream inputFile("products.txt");
    ofstream outputFile("temp.txt"); // Create a temporary file to store updated products

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Unable to open file!" << endl;
        return;
    }

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string code, product;
        float price;

        getline(ss, code, ',');
        getline(ss, product, ',');
        ss >> price;

        if (code == productCode) {
            found = true;
            cout << "\tProduct " << productCode << " deleted!" << endl;
        } else {
            // Store products other than the one to be deleted in the updated vectors
            updatedProductCodes.push_back(code);
            updatedProductList.push_back(product);
            updatedPriceList.push_back(price);
        }
    }

    inputFile.close();
    outputFile.close();

    if (!found) {
        cout << "Product with code " << productCode << " not found." << endl;
        return;
    }

    // Rewrite the remaining products to the file
    ofstream rewriteFile("products.txt");
    if (!rewriteFile.is_open()) {
        cout << "Unable to open file!" << endl;
        return;
    }

    for (int i = 0; i < updatedProductCodes.size(); i++) {
        rewriteFile << updatedProductCodes[i] << "," << updatedProductList[i] << "," << updatedPriceList[i] << endl;
    }

    rewriteFile.close();
}


void RestAdmin::updateProduct(string productCode, string product, float price) {
    ifstream inputFile("products.txt");
    ofstream tempFile("temp.txt"); // Temporary file

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cout << "Unable to open file!" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string code, oldProduct;
        float oldPrice;

        getline(ss, code, ',');
        getline(ss, oldProduct, ',');
        ss >> oldPrice;

        if (code == productCode) {
            found = true;
            tempFile << code << "," << product << "," << price << endl; // Update the line
            cout << "\tProduct " << productCode << " updated!" << endl;
        } else {
            tempFile << line << endl; // Copy the original line to the temporary file
        }
    }

    inputFile.close();
    tempFile.close();

    if (!found) {
        cout << "Product with code " << productCode << " not found." << endl;
        return;
    }

    // Remove the original file
    remove("products.txt");

    // Rename the temporary file to the original file name
    rename("temp.txt", "products.txt");
}
