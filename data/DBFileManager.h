// NOTES
// File Manager needs to:
//        1. Create a usable database at runtime (load users)
//        2. Manipulate database during runtime (add, remove, update a user)
//        3. Convert the runtime database to a text file for persistence (save users)
//        4. clear the file after loading so as to write to blank file

// Methods to implement:

//    1. Write to file     saveUsers()    (in progress)
//    2. Clear file

//    3. Read from file --> to where?     loadUsers()
//        - how do you know when a line is done?
//    4. Search file!!!! some sort of tree implementation

//    5. Add user
//    6. Remove user

/**
 * @file DBFileManager.h
 * Database file manager head file.
 *
 * @brief Database file manager head file.
 * @author Team 24
 * @date November 09, 2017
 */

#ifndef DBFILEMANAGER_H
#define DBFILEMANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <boost/filesystem.hpp>

#include "User.h"

class DBFileManager
{
    public:
        DBFileManager();

        bool addNewUser(User newUser);
        bool saveUser(User newUser); //check for existence in filesystem, build path and write info to file
        bool removeUser(User currentUser); //check for existence in filesystem and delete directory associated with user
        User getUser(std::string username); //check for existence in filesystem

    private:
        std::string mainPath;
        std::ifstream userReadStream; //remember to close() and clear() between operations
        std::ofstream userWriteStream; //remember to close() and clear() between operations

        void createPath(std::string username);
        void writeToFile(User newUser, std::string userPath);
        User readFromFile(std::string userPath);
};
#endif // DBFILEMANAGER_H
