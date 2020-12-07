// ShopManager 1.0 - Program.h
// Author - @silsanteri

#pragma once
#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include "List.h"
#include "Message.h"

// Class to manage userdata and the list.
class Program {
    public:
        Program(){};

        void start();                           // Starts the program.
    private:
        std::string userName;                   // Username.
        std::string storeName;                  // Name of the store.
        /* TODO: std::string locale; */         // Language.
        List list;                              // List of the items.
        Message msg;                            // Messages.

        std::string fstoreName;                 // Filename for the storename. (ex: "Hello World" = "hello_world.txt")
        std::string userData = "userdata.txt";  // Userdata.txt file.

        void readCommands();                    // Waits for commands and executes them.

        void newUserData();                     // Create new user.
        void changeUserName();                  // Change username.
        void changeStoreName();                 // Change storename.
        void makeFStoreName();                  // Makes the fStoreName.

        // File formatting:
        // username 
        // storename
        bool loadUserData();                    // Load userdata.
        bool saveUserData();                    // Save userdata.
        bool deleteUserData();                  // Delete userdata.
};
#endif