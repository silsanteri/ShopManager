// ShopManager 1.0 - List.cpp
// Author - @silsanteri

#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <ios>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <cstring>
#include "List.h"
#include "Item.h"
#include "Program.h"
#include "Message.h"

void List::printAll(){
    // Print through the item vector with the report function from Item class.
    for(auto i : this->items){
        i.report();
        std::cout << "< " << std::endl;
    }
}

bool List::boundaryCheck(std::string name, double price, int stock, int sold){
    // Initiate the check boolean.
    bool checc = false;
    // Nest the boundary checks for all types
    // and change the check boolean to true at the last step.
    if(name.size() <= NAME_MAX && name.size() >= NAME_MIN){
        if(price <= MAX && price >= MIN){
            if(stock <= MAX && stock >= MIN){
                if(sold <= MAX && sold >= MIN){
                    checc = true;
                } else {
                    this->msg.errorBoundary("Sold");
                }
            } else {
                this->msg.errorBoundary("Stock");
            }
        } else {
            this->msg.errorBoundary("Price");
        }
    } else {
        this->msg.errorNameBoundary();
    }
    return checc;
}

void List::manageItem(){
    // Make temporary string used in getline.
    std::string line;
    // Type - 1 = Sell, 2 = Add stock, 3 = Remove stock.
    int type = 0;
    // Amount to sell, add or remove.
    int amount = 0;
    // Ask the user for item to manage.
    this->msg.alertManageItem(1);
    // Get the item name.
    std::getline(std::cin, line);
    // Check for the name boundary.
    if(line.size() <= NAME_MAX && line.size() >= NAME_MIN){
        // Find the item.
        auto res = std::find_if(items.begin(), items.end(), [line](Item i) { return i.getName() == line; });
        // Check if the item exists.
        if(res != std::end(items)){
            // Turn the position into integer.
            int index = distance(items.begin(), res);
            // Ask the user for manage type.
            this->msg.alertManageItem(2);
            // Get the type.
            std::cin >> type;
            // Check if cin is good and check type.
            if(std::cin && type == 1){
                // Ask the user for an amount.
                this->msg.alertManageItem(3);
                // Check if cin is good and get amount.
                std::cin >> amount;
                if(std::cin){
                    // Execute sell function with the amount.
                    // Boundary check is done within the function.
                    items[index].sell(amount);
                } else {
                    // Cin error.
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    this->msg.errorUnknown();
                }
            // Check if cin is good and check type.
            } else if(std::cin && type == 2){
                // Ask the user for an amount.
                this->msg.alertManageItem(4);
                // Check if cin is good and get amount.
                std::cin >> amount;
                if(std::cin){
                    // Execute add function with the amount.
                    // Boundary check is done within the function.
                    items[index].add(amount);
                } else {
                    // Cin error.
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    this->msg.errorUnknown();
                }
            // If cin is bad and/or type is incorrect (not 1 or 2).
            // Check if cin is good and check type.
            } else if(std::cin && type == 3){
                // Ask the user for an amount.
                this->msg.alertManageItem(5);
                // Check if cin is good and get amount.
                std::cin >> amount;
                if(std::cin){
                    // Execute remove function with the amount.
                    // Boundary check is done within the function.
                    items[index].remove(amount);
                } else {
                    // Cin error.
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    this->msg.errorUnknown();
                }
            // If cin is bad and/or type is incorrect (not 1 or 2).
            } else {
                // Clear and ignore cin until newline incase of cin error.
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                this->msg.errorUnknown();
            }
        } else {
            // Error finding the specified item.
            this->msg.errorFindFail(line);
        }
    } else {
        // Error item name boundary.
        this->msg.errorNameBoundary();
    }
}

void List::newItem(){
    // Make temporary string used in getline.
    std::string line;
    // Boolean for checking if the name exists already.
    bool nameChecc = false;
    std::string name;   // Item object name
    double price;       // Item object price.
    int stock, sold;    // Item object stock and sold.
    // Ask values from the user and briefly explain formatting rules
    this->msg.alertNew();
    // Read the line
    std::getline(std::cin, line);
    // Initiate namecheck as false.
    nameChecc = false;
    // Turn the temporary string into stringstream.
    std::stringstream ss(line);
    // Read the values from stringstream.
    if(ss >> name >> price >> stock >> sold){
        // Check for the name boundary.
        if(this->boundaryCheck(name, price, stock, sold)){
            // For loop to check if item with the same name exists.
            for(auto i : this->items) if(i.getName() == name) nameChecc = true;
            if(nameChecc){
                // Print errors if item with the same name exists.
                this->msg.errorAddItemDuplicateName();
            } else {
                // If everything is in boundaries and no duplicate names
                // Make the Item object and push back.
                Item item(name, price, stock, sold);
                this->items.push_back(item);
            }
        }
    } else {
        // Print error and remind of the formatting rules
        this->msg.errorReadFail();
    }
}

void List::deleteItem(){
    // Make temporary string used in getline.
    std::string line;
    // Save the original size of the item vector.
    const auto original = this->items.size();
    // Ask the user to enter the item he/she wants to remove.
    this->msg.alertDeleteItem();
    // Get the item name.
    std::getline(std::cin, line);
    // Check for the name boundary.
    if(line.size() <= NAME_MAX && line.size() >= NAME_MIN){
        // If in vector, use erase–remove idiom to remove the wanted item.
        this->items.erase(std::remove_if(this->items.begin(), this->items.end(), [line](Item i) { return i.getName() == line; }), items.end());
        // Check if the original vector size is the same as the new size and print according message.
        if(this->items.size() == original){
            // Error finding the item.
            this->msg.errorFindFail(line);
        } else {
            // Deleted successfully.
            this->msg.alertDeleteSucc(line);
        }
    } else {
        // Name boundary error.
        this->msg.errorNameBoundary();
    }
}

void List::initFile(std::string fileName){
    // Open the infilestream to check if the file exists already..
    std::fstream infile(fileName, std::fstream::in);
    // If the file does not exist, create the file.
    if(!infile.good()){
        // Open outfilestream.
        std::fstream outFile (fileName, std::fstream::out);
        // Check if the outfilestream is good.
        if(!outFile.good()){
            // Error reading the file.
            this->msg.errorFileRead();
        } else {
            // Create empty file.
            outFile << "";
            outFile.close();
        }
    } else {
        // If file exists, loads the contents to the item vector.
        this->readFile(fileName);
    }
}

void List::readFile(std::string fileName){
    // Make temporary string used in getline.
    std::string line;
    // Open infilestream.
    // Filename boundary is checked elsewhere.
    std::ifstream inFile (fileName);
    // Boolean for checking if the name exists already.
    bool nameChecc = false;
    std::string name;   // Item object name
    double price;       // Item object price.
    int stock, sold;    // Item object stock and sold.
    // Counter to keep track of the read lines for error messages.
    int counter = 1;

    // Check if infilestream is open.
    if (inFile.is_open()){
        // While loop through the lines.
        while (std::getline(inFile,line)){
            // Initiate namecheck as false.
            nameChecc = false;
            // Turn the temporary string into stringstream.
            std::stringstream ss(line);
            // Read the values from stringstream.
            if(ss >> name >> price >> stock >> sold){
                // Check for the name boundary.
                if(this->boundaryCheck(name, price, stock, sold)){
                    // For loop to check if item with the same name exists.
                    for(auto i : this->items) if(i.getName() == name) nameChecc = true;
                    if(nameChecc){
                        // Print errors if item with the same name exists.
                        this->msg.errorAddItemDuplicateName();
                        this->msg.errorFileLine(fileName, counter);
                    } else {
                        // If everything is in boundaries and no duplicate names
                        // Make the Item object and push back.
                        Item item(name, price, stock, sold);
                        this->items.push_back(item);
                    }
                } else {
                    this->msg.errorFileLine(fileName, counter);
                }
            } else {
                // Print an error reading the current line of the file.
                this->msg.errorFileLine(fileName, counter);
            }
            // Increment the line counter.
            counter++;
        }
        // Close the filestream.
        inFile.close();
    } else {
        // File read error.
        this->msg.errorFileRead();
    }
}

void List::readFileInput(){
    // Make temporary string used in getline.
    std::string line;
    // Ask the user to enter the filename.
    this->msg.alertFileLoad();
    // Get the filename.
    std::getline(std::cin, line);
    // Check for the filename boundary.
    if(line.size() <= NAME_MAX && line.size() >= NAME_MIN){
        // Execute the readFile function with the filename given by user.
        this->readFile(line);
    } else {
        // Name boundary error.
        this->msg.errorNameBoundary();
    }
}

void List::saveFile(std::string fileName){
    // Open outfilestream.
    std::fstream outFile (fileName, std::fstream::out);
    // Check if outfilestream is good.
    if(!outFile.good()){
        // File read error.
        this->msg.errorFileRead();
    } else {
        // For loop through the item vector
        // and print them to the file following to the formatting rules.
        for(auto i : this->items){
            outFile << i << std::endl;
        }
        // Close the filestream.
        outFile.close();
        // Alert of success.
        this->msg.alertFileSaveSucc();
    }
}

void List::deleteFile(std::string fileName){
    // Copy the filename to the char array.
    // Filename boundary is checked elsewhere.
    char name[FILE_MAX];
    std::strcpy(name, fileName.c_str());
    // Remove the file and check for success.
    if(remove(name) == 0){
        // Alert of success.
        this->msg.alertDeleteFileSucc();
    } else {
        // Alert of failure.
        this->msg.errorDeleteFileFail();
    }
}