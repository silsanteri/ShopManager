// ShopManager 1.0 - Item.cpp
// Author - @silsanteri

#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <ios>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "Item.h"
#include "Message.h"


Item::Item(std::string name_, double price_, int stock_, int sold_){
    // Check for boundaries here, just in case they are not checked elsewhere.
    // The boundaries should be primarily checked elsewhere, so there can be an appropriate error message printed for the user.
    if(name_.size() <= NAME_MAX && name_.size() >= NAME_MIN){
        this->name = name_;
    } else {
        this->name = "xxx";
    }
    if(price_ >= MIN && price_ <= MAX){
        this->price = price_;
    } else {
        this->price = 0;
    }
    if(stock_ >= MIN && stock_ <= MAX){
        this->stock = stock_;
    } else {
        this->stock = 0;
    }
    if(sold_ >= MIN && sold_ <= MAX) {
        this->sold = sold_;
    } else {
        this->sold = 0;
    }
}

std::ostream &operator<<(std::ostream &out, const Item &notThis){
    out << notThis.name << ' ' << notThis.price << ' ' << notThis.stock << ' ' << notThis.sold;
    return out;
}

std::string Item::getName(){
    // Basic getter.
    return this->name;
}

double Item::getPrice(){
    // Basic getter.
    return this->price;
}

int Item::getStock(){
    // Basic getter.
    return this->stock;
}

int Item::getSold(){
    // Basic getter.
    return this->sold;
}

double Item::getProfit(){
    // Calculate price * sold, for the profit.
    return this->price * this->sold;
}

void Item::report(){ // TODO: Print through Message for possible future localization.
    // Prints the Item info in a tidy formatted list.
    std::cout << std::setw(11) << std::left << "< " << this->name << std::endl;
    std::cout << std::setw(10) << std::left << "< Price:";
    std::cout << std::setw(15) << std::right << std::fixed << std::setprecision(2) << this->price << std::endl;
    std::cout << std::setw(10) << std::left << "< Stock:";
    std::cout << std::setw(15) << std::right << this->stock << std::endl;
    std::cout << std::setw(10) << std::left << "< Sold:";
    std::cout << std::setw(15) << std::right << this->sold << std::endl;
    std::cout << std::setw(10) << std::left << "< Profit:";
    std::cout << std::setw(15) << std::right << std::fixed << std::setprecision(2) << this->getProfit() << std::endl;
}

void Item::sell(int count){
    // Boundary checks.
    if(count >= MIN && this->stock >= count && count + this->sold <= MAX){
        // Add the count to sold and remove stock.
        this->sold += count;
        this->stock -= count;
        // Alert the successful sale and print new stock.
        this->msg.alertSell(this->name, count);
        this->msg.alertPrintStock(this->name, this->stock);
    } else {
        // Error message and print the current stock.
        this->msg.errorCountRemove();
        this->msg.alertPrintStock(this->name, this->stock);
    }
}

void Item::add(int count){
    // Boundary checks.
    if(count >= MIN && count + this->stock <= MAX){
        // Add stock.
        this->stock += count;
        // Alert the successful addition and print new stock.
        this->msg.alertAdd(this->name, count);
        this->msg.alertPrintStock(this->name, this->stock);
    } else {
        // Error message.
        this->msg.errorCountAdd();
    }
}

void Item::remove(int count){
    // Boundary checks.
    if(count >= MIN && this->stock >= count){
        // Remove stock.
        this->stock -= count;
        // Alert the successful removal and print new stock.
        this->msg.alertRemove(this->name, count);
        this->msg.alertPrintStock(this->name, this->stock);
    } else {
        // Error message and print the current stock.
        this->msg.errorCountRemove();
        this->msg.alertPrintStock(this->name, this->stock);
    }
}