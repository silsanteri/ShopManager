// ShopManager 1.0 - main.cpp
// Author - @silsanteri

// Class hierarchy: Main -> Program -> List -> Item.

// Program manages an object of List and storage of userdata.
// List class manages a vector of Item objects and storage of the store's data.
// Item class manages individual Item objects.
// Message class is used by every class. It is used for text printing and #define variables storage.

// Future improvements/TODOs:
// More stores and/or profiles. (maybe password protected profile with encryption?)
// Localization.
// GUI.
// Better formatting for the items or database storage. (maybe XML or JSON?)
// More types of information to store about the items.
// Overall efficiency of existing functions. (Overloading operators for file reading, remove unecessary includes etc.)

#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator> 
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <ios>
#include <limits>
#include <iomanip>
#include <sstream>
#include <memory>
#include "List.h"
#include "Item.h"
#include "Program.h"
#include "Message.h"

int main(){
    // Start the program.
    Program program;
    program.start();
    return 0;
}