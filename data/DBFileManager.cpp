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
    //std::ifstream userReadStream;
    //std::ofstream userWriteStream;

    if(!boost::filesystem::exists("./USERS"))
    {
        boost::filesystem::create_directory("./USERS");
    }
}

/* PUBLIC METHODS */



/**
 * Save the vector of User objects to file.
 * @param users a vector containing User objects.
 */
bool DBFileManager::addNewUser(User newUser)
{
    std::string username = newUser.User::getUsername();
    std::string dirPath = DBFileManager::createDirPath(username);

    if(boost::filesystem::exists(dirPath))
    {
        std::cout << "Error: user already exists." << std::endl;
        return 1;
    }
    else
    {
        boost::filesystem::create_directory(dirPath);
        dirPath = DBFileManager::createFilePath(username);
        DBFileManager::writeToFile(newUser, dirPath);
        return 0;
    }
}

bool DBFileManager::saveUser(User currentUser)
{
    std::string filepath = DBFileManager::createFilePath(currentUser.User::getUsername());

    if(!boost::filesystem::exists(filepath))
    {
        std::cout << "Error: could not find user." << std::endl;
        return 1;
    }
    else
    {
        DBFileManager::writeToFile(currentUser, filepath);
        return 0;
    }
}

bool DBFileManager::removeUser(User currentUser)
{
    std::string filepath = DBFileManager::createDirPath(currentUser.User::getUsername());

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

User DBFileManager::getUser(std::string username) //this depends on the toString() of user being updated with newline chars
{
    std::string filepath = DBFileManager::createFilePath(username);

    if(!boost::filesystem::exists(filepath))
    {
        std::cout << "Error: could not find user." << std::endl;
    }
    else
    {
        User currentUser = DBFileManager::readFromFile(filepath);
        return currentUser;
    }

}

std::string DBFileManager::createDirPath(std::string username)
{
    std::string dirPath = "USERS";
    dirPath.std::string::append("/");
    dirPath.std::string::append(username);

    return dirPath;
}

std::string DBFileManager::createFilePath(std::string username)
{
    std::string filepath = "USERS";
    filepath.std::string::append("/");
    filepath.std::string::append(username);
    filepath.std::string::append("/");
    filepath.std::string::append(username);
    filepath.std::string::append("_info.txt");

    return filepath;
}

/**
 * Write data to file.
 */
void DBFileManager::writeToFile(User newUser, std::string userPath)
{
    std::ofstream userWriteStream(userPath);

    if(!userWriteStream.std::ofstream::is_open()) //check that file is open
    {
        std::cout << "File failed to open." << std::endl;
    }
    else
    {
        userWriteStream << newUser.User::toString();
        userWriteStream.std::ofstream::close();
        userWriteStream.std::ofstream::clear();
    }
}

User DBFileManager::readFromFile(std::string userPath)
{
    std::ifstream userReadStream(userPath);

    if(!userReadStream.std::ifstream::is_open()) //check that file is open
    {
        std::cout << "File failed to open." << std::endl;
    }
    else
    {
        User currentUser;
        std::string currentLine;

        //this will follow the exact format of the toString method to ensure
            //the right values are stored in the right places
        std::getline(userReadStream, currentLine);
        currentUser.User::setUsername(currentLine);

        std::getline(userReadStream, currentLine);
        currentUser.User::setPassword(currentLine);

        std::getline(userReadStream, currentLine);
        currentUser.User::setFirstName(currentLine);

        std::getline(userReadStream, currentLine);
        currentUser.User::setLastName(currentLine);

        //will add something here to deal with bridges as well

        userReadStream.std::ifstream::close();
        userReadStream.std::ifstream::clear();

        return currentUser;
    }

}


