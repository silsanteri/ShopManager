// ShopManager 1.0 - Item.h
// Author - @silsanteri

#pragma once
#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include "Message.h"

// Class for the individual store items.
class Item {
    private:
        // Profit is not saved, because it is only needed in report function, so it would require unnecessary calculations.
        // TODO: More things to save, such as purchase price, product rating etc.

        std::string name;                   // Name of the product.
        double price;                       // Price of the product.
        int stock;                          // Amount of product currently available.
        int sold;                           // Amount of product sold.
        Message msg;                        // Messages.
    public:
        Item(std::string name_ = "xxx", double price_ = 0.0, int stock_ = 0, int sold_ = 0);

        // Overloaded out operator for easier Item storing.
        friend std::ostream &operator<<(std::ostream &out, const Item &notThis);

        std::string getName();              // Gets the name of the product.
        double getPrice();                  // Gets the price of the product.
        int getStock();                     // Gets the stock of the product.
        int getSold();                      // Gets the sold of the product.
        double getProfit();                 // Gets the profit of the product.

        void report();                      // Prints out all information of the item.
        void sell(int count);               // Sells "count" amount of item(s) if there is/are enough in stock.
        void add(int count);                // Adds "count" amount of item(s) to the stock.
        void remove(int count);             // Removes "count" amount of item(s) from the stock.
};
#endif