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
#ifndef DBFILEMANAGER_H
#define DBFILEMANAGER_H

#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <vector>

#include "User.h"

class DBFileManager
{
    public:
        DBFileManager();

        void loadUsers();//coded, needs testing
        void saveUsers(); //coded, needs testing
        User getUser(std::string userName);

        bool addUser(User newUser);
        bool removeUser(User currentUser);

    private:
        std::ofstream userFileStream;
        std::vector<User> listOfUsers;

        void clearFile();
        void writeToFile(); //coded needs testing
        void buildActiveDB(); //coded needs testing
};
#endif // DBFILEMANAGER_H
