// NOTES
// File Manager needs to:
//        1. Create a usable database at runtime (load users)
//        2. Manipulate database during runtime (add, remove, update a user)
//        3. Convert the runtime database to a text file for persistence (save users)
//        4. clear the file after loading so as to write to blank file

// Methods to implement:

//    1. Write to file     saveUsers()
//    2. Clear file

//    3. Read from file --> to where?     loadUsers()
//        - how do you know when a line is done?
//    4. Search file!!!! some sort of tree implementation

//    5. Add user
//    6. Remove user

/**
 * @file DBFileManager.cpp
 * Database file manager.
 *
 * @brief Database file manager
 * @author Team 24
 * @date November 09, 2017
 */


#include "DBFileManager.h"

/* CONSTRUCTORS */


/**
 * Default constructor. Initializes output stream to database file.
 */
DBFileManager::DBFileManager()
{
    DBFileManager::userFileStream.std::ofstream::open("UserDatabase.txt"); //open output stream to database file
}

/* PUBLIC METHODS */

//std::set<User> loadUsers(std::string fileName)
//{

//}


/**
 * Save the vector of User objects to file.
 * @param users a vector containing User objects.
 */
void saveUsers(std::vector<User> users)
{
    if (!DBFileManager::userFileStream.std::ofstream::is_open()) //check that file is open
    {
        std::cout << "File failed to open." << std::endl;
        return 1;
    }
    else
    {
        writeToFile();
    }
}


/**
 * Write data to file.
 */
void writeToFile()
{
    if (!userFile.std::ofstream::is_open()) //check that file is open
    {
        std::cout << "File failed to open." << std::endl;
        return 1;
    }
    else
    {
        for (std::vector<User>::iterator it = DBFileManager::listOfUsers.begin() ; it != DBFileManager::listOfUsers.end(); ++it)
        {
            randomUser = *it;
            DBFileManager::userFileStream << randomUser.User::toString() << std::endl; //write info to a single line
        }
    }
}


