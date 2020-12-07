// ShopManager 1.0 - Program.cpp
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

void Program::start(){
    // Try to load userdata.
    if(this->loadUserData()){
        // If userdata was loaded correctly print the welcome message with the user's name.
        this->msg.alertWelcome(this->userName);
    } else {
        // If userdata was loaded incorrectly/did not exist, print a welcome message for new user.
        this->msg.alertWelcome("");
        // Inform the user that a new profile is being created.
        this->msg.alertNewProfile();
        // Execute function to create new user.
        this->newUserData();

    }
    // Remind the user of a command that shows all of the available commands.
    this->msg.alertHelp();
    // Start reading the commands from the user.
    this->readCommands();
}

void Program::readCommands(){
    // Make temporary string used in getline for the user input.
    std::string line;
    // While loop until the user wants to close the program.
    while(1){
        // Print '> ' to make the program look nicer.
        this->msg.alertEnterCommand();
        // Get the users command.
        // I don't think checking boundaries here is necessary.
        std::getline(std::cin, line);
        // Turn the user input to lowercase.
        for(auto& c : line) c = std::tolower(c);
        if(line == "stop" || line == "exit"){   // Stop the program.
            this->list.saveFile(this->fstoreName);
            this->msg.alertStop(this->userName);
            exit(0);
        } else if(line == "help"){              // Print all available commands.
            this->msg.alertCommands();
        } else if(line == "itemprint"){         // Print all of the items.
            this->list.printAll();
        } else if(line == "itemmanage"){        // Manage item.
            this->list.manageItem();
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } else if(line == "itemnew"){           // Create new item.
            this->list.newItem();
        } else if(line == "itemdelete"){        // Delete item.
            this->list.deleteItem();
        } else if(line == "fileload"){          // Load items from a file.
            this->list.readFileInput();
        } else if(line == "filesave"){          // Save to the store's file.
            this->list.saveFile(this->fstoreName);
        } else if(line == "filedelete"){        // Delete the store's file.
            this->list.deleteFile(this->fstoreName);
        } else if(line == "nameuser"){          // Change username.
            this->changeUserName();
        } else if(line == "namestore"){         // Change storename.
            this->changeStoreName();
        } else if(line == "deletedata"){        // Delete all data.
            this->deleteUserData();
            this->list.deleteFile(this->fstoreName);
            this->msg.alertDelete();
            exit(0);
        } else if(line == "formatinfo"){        // Show formatting info.
            this->msg.alertFormatInfo();
        } else if(line == "programinfo"){       // Show program info.
            this->msg.alertProgramInfo(this->userName, this->storeName, this->fstoreName);
        } else {                                // Unknown command.
            this->msg.alertUnknown();
            this->msg.alertHelp();
        }
    }
}

void Program::newUserData(){
    // Make temporary string used in getline.
    std::string line;
    // While-loop until user sets an acceptable name.
    while(1){
        // Ask the user for a username.
        this->msg.alertEnterUserName();
        // Get input from the user.
        std::getline(std::cin, line);
        // Check for boundaries.
        if(line.size() <= NAME_MAX && line.size() >= NAME_MIN){
            // If the username was acceptable save it and break the while-loop.
            this->userName = line;
            break;
        } else {
            // Restart the while loop and print error about the username length.
            this->msg.errorUserNameLength();
        }
    }

    // Make temporary string used in getline.
    std::string lain;
    // Make temporary string to test if the storename is userdata.
    std::string test;
    while(1){
        // Ask the user for a storename.
        this->msg.alertEnterStoreName();
        // Get input from the user.
        std::getline(std::cin, lain);
        // Put the input to the test string.
        test = lain;
        // Convert the test string to lowercase.
        for(auto& c : test) c = std::tolower(c);
        // Check for boundaries and if the storename is 'userdata'.
        if(lain.size() <= NAME_MAX && lain.size() >= NAME_MIN && test != "userdata"){
            // If the storename was acceptable save it.
            this->storeName = lain;
            // Create the filename.
            this->makeFStoreName();
            // Create the store file.
            this->list.initFile(this->fstoreName);
            // Save the userdata.
            this->saveUserData();
            // Break the while-loop.
            break;
        } else {
            if(test == "userdata"){
                // Restart the while-loop and print error if the storename was 'userdata'.
                this->msg.errorStoreNameUserData();
            } else {
                // Restart the while-loop and print error about the storename length.
                this->msg.errorStoreNameLength();
            }
        }
    }
}

void Program::changeUserName(){
    // Make temporary string used in getline.
    std::string line;
    // Ask the user to enter new username.
    this->msg.alertEnterUserName();
    // Get input from the user.
    std::getline(std::cin, line);
    // Check for name boundaries.
    if(line.size() <= NAME_MAX && line.size() >= NAME_MIN){
        // If the boundaries are correct, remember the username and save it to userdata.txt.
        this->userName = line;
        this->saveUserData();
    } else {
        // Close the function and print error about the username length.
        this->msg.errorUserNameLength();
    }
}

void Program::changeStoreName(){
    // Make temporary string used in getline.
    std::string line;
    // Make temporary string to test if the storename is userdata.
    std::string test;
    // Ask the user to enter new storename.
    this->msg.alertEnterStoreName();
    // Get input from the user.
    std::getline(std::cin, line);
    // Put the input to the test string.
    test = line;
    // Convert the test string to lowercase.
    for(auto& c : test) c = std::tolower(c);
    // Check for boundaries and if the storename is 'userdata'.
    if(line.size() <= NAME_MAX && line.size() >= NAME_MIN && test != "userdata"){
        // If the storename was acceptable save it.
        this->storeName = line;
        // Create the filename.
        this->makeFStoreName();
        // Save the store data to a new file named after the new store.
        this->list.saveFile(this->fstoreName);
        // Save the userdata.
        this->saveUserData();
    } else {
        if(test == "userdata"){
            // Close the function and print error if the storename was 'userdata'.
            this->msg.errorStoreNameUserData();
        } else {
            // Close the function and print error about the storename length.
            this->msg.errorStoreNameLength();
        }
    }
}

void Program::makeFStoreName(){
    // Get the original storename to temporary string.
    std::string temp = this->storeName;
    // For loop through the temporary string.
    for(auto& c : temp){
        // Convert all characters to lowercase.
        c = std::tolower(c);
        // Check if character is space, and convert it to underscore if yes.
        if(std::isspace(c)){
            c = '_';
        }
    }
    // Finally add '.txt' to the temporary string and replace fstoreName with it.
    this->fstoreName = temp + ".txt";
}

bool Program::loadUserData(){
    // Make temporary string used in getline.
    std::string line;
    // Open infilestream.
    std::ifstream inFile(userData);
    // Return boolean.
    bool checc = false;
    // Line counter
    int counter = 1;
    // Make temporary strings for the username, storename and storename userdata test.
    std::string uname, sname, test;
    // Check if infilestream is good and open.
    if (inFile.is_open() && inFile.good()){
        // While-loop through the userdata file.
        while(std::getline(inFile, line)){
            // First line = username.
            if(counter == 1){
                // Put line in uname string.
                uname = line;
                // Check for boundaries.
                if(uname.length() <= NAME_MAX && uname.length() >= NAME_MIN){
                    // Increment the counter to move to storename.
                    counter++;
                } else {
                    // Close the function and print error about the storename length.
                    this->msg.errorFileLine(this->userData, counter);
                    this->msg.errorUserNameLength();
                    // Break while-loop on error.
                    break;
                }
            // Second line = storename.
            } else if(counter == 2){
                sname = line;
                // Put the input to the test string.
                test = sname;
                // Convert the test string to lowercase.
                for(auto& c : test) c = std::tolower(c);
                // Check for boundaries and if the storename is 'userdata'.
                if(sname.length() <= NAME_MAX && sname.length() >= NAME_MIN && test != "userdata"){
                    // If the storename and username both were acceptable store them.
                    this->storeName = sname;
                    this->userName = uname;
                    // Create the filename.
                    this->makeFStoreName();
                     // Initiate the store data or alternatively do nothing if the file already exists.
                    this->list.initFile(this->fstoreName);
                    // Return checc at the end.
                    checc = true;
                    // Break while-loop on success.
                    break;
                } else {
                    if(test == "userdata"){
                        // Close the function and print error if the storename was 'userdata'.
                        this->msg.errorFileLine(this->userData, counter);
                        this->msg.errorStoreNameUserData();
                    } else {
                        // Close the function and print error about the storename length.
                        this->msg.errorFileLine(this->userData, counter);
                        this->msg.errorStoreNameLength();
                    }
                    // Break while-loop on error.
                    break;
                }
            }
        }
    }
    // Close infilestream.
    inFile.close();
    // Return true if storename and username both were acceptable.
    return checc;
}

bool Program::saveUserData(){
    // Open outfilestream.
    std::fstream outFile (userData, std::fstream::out);
    // Check if outfilestream is good.
    if(!outFile.good()){
        // Return false and show file read error if outfilestream is bad.
        this->msg.errorFileRead();
        return false;
    } else {
        // If outfilestream is good.
        // Print userdata according to the formatting rules.
        outFile << this->userName << std::endl;
        outFile << this->storeName;
        // Close filestream
        outFile.close();
        // Return true.
        return true;
    }
}

bool Program::deleteUserData(){
    // Copy the filename to the char array.
    char ud[FILE_MAX];
    // Remove the file and check for success.
    strcpy(ud, this->userData.c_str());
    // Remove the file and check for success.
    if(remove(ud) != 0){
        // Return true for success.
        return true;
    } else {
        // Return false for failure.
        return false;
    }
}