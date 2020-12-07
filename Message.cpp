// ShopManager 1.0 - Message.cpp
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
#include "Message.h"


void Message::alertEnterUserName(){
    std::cout << "< Enter username(3-64 Characters)\n< ";
}

void Message::alertEnterStoreName(){
    std::cout << "< Enter storename(3-64 Characters)\n< ";
}

void Message::alertWelcome(std::string name){
    if(name == ""){
        std::cout << "< Welcome new user!" << std::endl;
    } else {
        std::cout << "< Welcome " << name << "!" << std::endl;
    }
}

void Message::alertEnterCommand(){
    std::cout << "> ";
}

void Message::alertCommands(){
    std::cout << "< -- List of Available Commands --" << std::endl;
    std::cout << "< NOTE: The commands are NOT case sensitive." << std::endl;
    std::cout << "< help          - Lists all available commands." << std::endl;
    std::cout << "< itemprint     - Print all items." << std::endl;
    std::cout << "< itemmanage    - Add stock or document sold item(s)." << std::endl;
    std::cout << "< itemnew       - Create new item." << std::endl;
    std::cout << "< itemdelete    - Delete item." << std::endl;
    std::cout << "< fileload      - Load items from text file of your choice and adds them to your store." << std::endl;
    std::cout << "< filesave      - Save items to text file. (storename.txt)" << std::endl;
    std::cout << "< filedelete    - Delete store data text file. (storename.txt)" << std::endl;
    std::cout << "< nameuser      - Change username." << std::endl;
    std::cout << "< namestore     - Change storename." << std::endl;
    std::cout << "< deletedata    - Deletes all data including userdata." << std::endl;
    std::cout << "< formatinfo    - Info about formatting rules in user created files." << std::endl;
    std::cout << "< programinfo   - Info about the program." << std::endl;
    std::cout << "< stop          - Saves the data and closes the program." << std::endl;
    std::cout << "< exit          - Saves the data and closes the program." << std::endl;
}

void Message::alertStop(std::string name){
    std::cout << "< Exiting program..." << std::endl;
    std::cout << "< Bye bye " << name << "!" << std::endl;
}

void Message::alertDelete(){
    std::cout << "< All data deleted." << std::endl;
    std::cout << "< Exiting program...." << std::endl;
}

void Message::alertFormatInfo(){
    std::cout << "< --- Format Info ---" << std::endl;
    std::cout << "< -- Userdata Formatting --" << std::endl;
    std::cout << "< Stored in userdata.txt.\n< " << std::endl;
    std::cout << "< Format:\n< username\n< storename\n< " << std::endl;
    std::cout << "< Example:\n< Warren Buffett\n< Berkshire Hathaway\n< \n< " << std::endl;
    std::cout << "< -- Storedata Formatting --" << std::endl;
    std::cout << "< These formatting rules are used when using 'itemnew' command." << std::endl;
    std::cout << "< Stored in storename.txt." << std::endl;
    std::cout << "< File is named after storename that is set by the user." << std::endl;
    std::cout << "< Storename whitespaces are converted to underscores and all of the letters to lowercase." << std::endl;
    std::cout << "< Filename example: Berkshire Hathaway -> berkshire_hathaway.txt" << std::endl;
    std::cout << "< Tip: It is highly recommended to use different filenames than your storename when loading store items via files to not run into any issues.\n< " << std::endl;
    std::cout << "< Format:\n< name price stock sold\n< " << std::endl;
    std::cout << "< Name    -   string    -     3-64 characters, no whitespaces allowed." << std::endl;
    std::cout << "< Price   -   double    -     Has to be between 0 and 99999." << std::endl;
    std::cout << "< Stock   -   integer   -     Has to be between 0 and 99999." << std::endl;
    std::cout << "< Sold    -   integer   -     Has to be between 0 and 99999.\n< " << std::endl;
    std::cout << "< Example:\n< Item1 666 72 18\n< Item2 420 69 13" << std::endl;
}

void Message::alertProgramInfo(std::string uname, std::string sname, std::string sfname){
    std::cout << "< -- Program Info --" << std::endl;
    std::cout << "< Username: " << uname << std::endl;
    std::cout << "< Storename: " << sname << std::endl;
    std::cout << "< Store's filename: " << sfname << std::endl;
    std::cout << "< Program made by @silsanteri" << std::endl;
}

void Message::alertUnknown(){
    std::cout << "< Unknown command!" << std::endl;
}

void Message::alertHelp(){
    std::cout << "< Enter 'help' for a list of available commands." << std::endl;
}

void Message::alertNew(){
    std::cout << "< Enter new item according to the following formatting rules." << std::endl;
    std::cout << "< name price stock sold" << std::endl;
    this->alertEnterCommand();
}

void Message::alertAdd(std::string name, int count){
    std::cout << "< Added " << count << " stock of " << name << std::endl;
}

void Message::alertSell(std::string name, int count){
    std::cout << "< Sold " << count << " of " << name << std::endl;
}

void Message::alertRemove(std::string name, int count){
    std::cout << "< Removed " << count << " of " << name << std::endl;
}

void Message::alertPrintStock(std::string name, int stock){
    std::cout << "< " << name << " in stock: " << stock << std::endl;
}

void Message::alertManageItem(int index){
    switch(index){
        case 1: std::cout << "< Name of the item you want to manage (case sensitive, 3-64 letters)\n> "; break;
        case 2: std::cout << "< Select Option:\n< 1: Document sale.\n< 2: Add stock.\n< 3: Remove stock.\n> "; break;
        case 3: std::cout << "< Amount of items sold (integer, 0 <= sold <= 99999)\n> "; break;
        case 4: std::cout << "< Amount of stock to add (integer, 0 <= stock <= 99999)\n> "; break;
        case 5: std::cout << "< Amount of stock to remove (integer, 0 <= sold <= 99999)\n> "; break;
        default: this->errorUnknown();
    }
}

void Message::alertDeleteItem(){
    std::cout << "< Name of the item you want to delete (case sensitive, 3-64 letters)" << std::endl;
    this->alertEnterCommand();
}

void Message::alertDeleteSucc(std::string name){
    std::cout << "< Item '" << name << "' successfully removed!" << std::endl;
}

void Message::alertDeleteFileSucc(){
    std::cout << "< File successfully removed!" << std::endl;
}

void Message::alertFileSaveSucc(){
    std::cout << "< File successfully saved!" << std::endl;
}

void Message::alertFileLoad(){
    std::cout << "< Enter name of file to load" << std::endl;
    this->alertEnterCommand();
}

void Message::alertNewProfile(){
    std::cout << "< Creating new profile!" << std::endl;
}


void Message::errorUserNameLength(){
    std::cout << "< Error: Username must be 3-64 characters long." << std::endl;
}

void Message::errorStoreNameLength(){
    std::cout << "< Error: Storename must be 3-64 characters long." << std::endl;
}

void Message::errorStoreNameUserData(){
    std::cout << "< Error: Storename can not be any variation of 'userdata'." << std::endl;
}

void Message::errorCountRemove(){
    std::cout << "< Error: Amount needs to be minimum 0 and smaller or equal to current stock size!" << std::endl;
}

void Message::errorCountAdd(){
    std::cout << "< Error: Amount needs to be minimum 0 and cannot change stock to over 99999!" << std::endl;
}

void Message::errorReadFail(){
    std::cout << "< Error: Formatting error!" << std::endl;
    std::cout << "< Enter 'formatinfo' for a comprehensive explanation of the formatting rules." << std::endl;
}

void Message::errorNameBoundary(){
    std::cout << "< Error: Item name must be 3-64 characters long." << std::endl;
}

void Message::errorBoundary(std::string name){
    std::cout << "< Error: " << name << " needs to be 0-99999!" << std::endl;
}

void Message::errorFileRead(){
    std::cout << "< Error: Reading file has failed!" << std::endl;
}

void Message::errorDeleteFileFail(){
    std::cout << "< Error: Deleting file has failed!" << std::endl;
}

void Message::errorFileLine(std::string fileName, int line){
    std::cout << "< Error: Formatting error in " << fileName << " on line " << line << "!" << std::endl;
}

void Message::errorAddItem(int index){
    switch(index){
        case 1: std::cout << "< Error: Setting the name." << std::endl; break;
        case 2: std::cout << "< Error: Setting the price." << std::endl; break;
        case 3: std::cout << "< Error: Setting the stock." << std::endl; break;
        case 4: std::cout << "< Error: Setting the sold." << std::endl; break;
        default: this->errorUnknown();
    }
}

void Message::errorAddItemDuplicateName(){
    std::cout << "< Error: Duplicate item names are not allowed!" << std::endl;
    std::cout << "< Proceeding with ignoring the duplicate." << std::endl;
}

void Message::errorFindFail(std::string name){
    std::cout << "< Error: Could not find item '" << name << "'!" << std::endl;
}

void Message::errorUnknown(){
    std::cout << "< Error: Unknown error." << std::endl;
}