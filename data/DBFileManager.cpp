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
    DBFileManager::mainPath = "USERS";
}

/* PUBLIC METHODS */



/**
 * Save the vector of User objects to file.
 * @param users a vector containing User objects.
 */
bool addNewUser(User newUser)
{
    std::string filepath = createPath(newUser.User::getUsername());

    if(boost::filesystem::exists(filepath))
    {
        std::cout << "Error: user already exists." << std::endl;
        return 1;
    }
    else
    {
        boost::filesystem::create_directory(filepath);
        writeToFile(newUser, filepath);
        return 0;
    }
}

bool saveUser(User currentUser)
{
    std::string filepath = createPath(currentUser).User::getUsername());

    if(!boost::filesystem::exists(filepath))
    {
        std::cout << "Error: could not find user." << std::endl;
        return 1;
    }
    else
    {
        writeToFile(currentUser, filepath);
        return 0;
    }
}

bool removeUser(User currentUser)
{
    std::string filepath = createPath(currentUser).User::getUsername());

    if(!boost::filesystem::exists(filepath))
    {
        std::cout << "Error: could not find user." << std::endl;
        return 1;
    }
    else
    {
        boost::filesystem::remove_all(filepath);
        return 0;
    }
}

User getUser(std::string username) //this depends on the toString() of user being updated with newline chars
{
    std::string filepath = createPath(currentUser).User::getUsername());

    if(!boost::filesystem::exists(filepath))
    {
        std::cout << "Error: could not find user." << std::endl;
        return 1;
    }
    else
    {
        User currentUser = readFromFile(filepath);
        return currentUser;
    }

}

std::string createPath(std::string username)
{
    string filepath = DBFileManager::mainPath;
    filepath.std::string::append("/");
    filepath.std::string::append(username);
    filepath.std::string::append("/");
    filepath.std::string::append(username);
    filepath.std::string::append("_info.txt");
}

/**
 * Write data to file.
 */
void writeToFile(User newUser, std::string userPath))
{
    DBFileManager::userWriteStream.std::ofstream.open(userPath);

    if(!DBFileManager::userWriteStream.std::ofstream::is_open()) //check that file is open
    {
        std::cout << "File failed to open." << std::endl;
        return 1;
    }
    else
    {
        DBFileManager::userWriteStream << newUser.User::toString();
        DBFileManager::userWriteStream.std::ofstream::close();
        DBFileManager::userWriteStream.std::ofstream::clear();
        return 0;
    }
}

User readFromFile(std::string userPath)
{
    DBFileManager::userReadStream.std::ifstream::open(userPath);

    if(!DBFileManager::userReadStream.std::ifstream::is_open()) //check that file is open
    {
        std::cout << "File failed to open." << std::endl;
        return 1;
    }
    else
    {
        User currentUser;
        std::string currentLine;

        //this will follow the exact format of the toString method to ensure
            //the right values are stored in the right places
        std::getline(DBFileManager::userReadStream, currentLine);
        currentUser.User::setUsername(currentLine);

        std::getline(DBFileManager::userReadStream, currentLine);
        currentUser.User::setPassword(currentLine);

        std::getline(DBFileManager::userReadStream, currentLine);
        currentUser.User::setFirstName(currentLine);

        std::getline(DBFileManager::userReadStream, currentLine);
        currentUser.User::setLastName(currentLine);

        //will add something here to deal with bridges as well

        DBFileManager::userReadStream.std::ifstream::close();
        DBFileManager::userReadStream.std::ifstream::clear();

        return currentUser;
    }

}


