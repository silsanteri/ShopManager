// ShopManager 1.0 - Message.h
// Author - @silsanteri

#pragma once
#ifndef LANGUAGES_H_INCLUDED
#define LANGUAGES_H_INCLUDED
#include <iostream>
#include <string>

#define NAME_MIN 3
#define NAME_MAX 64
#define MIN 0
#define MAX 99999
// Filename max = 64 (+4 for '.txt').
#define FILE_MAX 68

// Class to store messages and define numbers, used by every other class.
class Message {
    public:
        Message(){}

        // TODO: Add more languages.

        void alertEnterUserName();
        void alertEnterStoreName();
        void alertWelcome(std::string name);
        void alertCommands();
        void alertEnterCommand();
        void alertStop(std::string name);
        void alertDelete();
        void alertFormatInfo();
        void alertProgramInfo(std::string uname, std::string sname, std::string sfname);
        void alertUnknown();
        void alertHelp();
        void alertNew();
        void alertAdd(std::string name, int count);
        void alertSell(std::string name, int count);
        void alertRemove(std::string name, int count);
        void alertPrintStock(std::string name, int stock);
        void alertManageItem(int index);
        void alertDeleteItem();
        void alertDeleteSucc(std::string name);
        void alertDeleteFileSucc();
        void alertFileSaveSucc();
        void alertFileLoad();
        void alertNewProfile();

        void errorUserNameLength();
        void errorStoreNameLength();
        void errorStoreNameUserData();
        void errorCountRemove();
        void errorCountAdd();
        void errorReadFail();
        void errorNameBoundary();
        void errorBoundary(std::string name);
        void errorFileRead();
        void errorDeleteFileFail();
        void errorFileLine(std::string fileName, int line);
        void errorAddItem(int index);
        void errorAddItemDuplicateName();
        void errorFindFail(std::string name);
        void errorUnknown();
};
#endif