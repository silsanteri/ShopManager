// ShopManager 1.0 - List.h
// Author - @silsanteri

#pragma once
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "Message.h"

// Class for holding, storing and displaying the store information.
class List {
    public:
        List(){}

        // TODO: Overloaded >> operator for file reading.

        void printAll();                        // Prints all of the item(s).
        /* TODO: void printAllOrder(int type)*/ // Prints all of the items with order. (type - 1 = Name, 2 = Price, 3 = Stock)
        /* TODO: void orderItems(int type);*/   // Orders items. (type - 1 = Name, 2 = Price, 3 = Stock)

        // Checks for the Item variable boundaries.
        bool boundaryCheck(std::string name, double price, int stock, int sold);

        void manageItem();                      // Add stock or document sold item(s).
        void newItem();                         // Add item.
        void deleteItem();                      // Delete item.

        // File formatting: name price stock sold
        void initFile(std::string fileName);    // Initiate file.
        void readFile(std::string fileName);    // Read from file.
        void readFileInput();                   // Read from file with input.
        void saveFile(std::string fileName);    // Save file.
        void deleteFile(std::string fileName);  // Delete file.
    private:
        std::vector<Item> items;                // Vector of the item(s).
        Message msg;                            // Messages.
};
#endif