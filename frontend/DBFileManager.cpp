/**
 * @file DBFileManager.cpp
 * Database file manager.
 *
 * @brief Database file manager
 * @author Team 24
 * @date November 09, 2017
 */

#include <cstddef>
#include <sstream>

#include "DBFileManager.h"

/* CONSTRUCTORS */

/**
 * Default constructor. Creates a HUE_USERS/ directory if none already exist.
 */
DBFileManager::DBFileManager()
{
    if(!boost::filesystem::exists("./HUE_USERS"))
    {
        boost::filesystem::create_directory("./HUE_USERS");
    }
}

/* PUBLIC METHODS */



/**
 * Creates a new directory for a newly-registered user. NOTE: actual user info file created here
 * @param newUser a new user object
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
        dirPath = DBFileManager::createUserFilePath(username);
        std::ofstream userWriteStream(dirPath);

        if(!userWriteStream.std::ofstream::is_open()) //check that file is open
        {
            std::cout << "File failed to open." << std::endl;
        }
        else
        {
            userWriteStream << newUser.User::infoToString() << std::endl;

            userWriteStream.std::ofstream::close();
            userWriteStream.std::ofstream::clear();
        }
        return 0;
    }
}

/**
 * Creates a new user info file within the user's directory, and can be used to save a user's info
 * at the end of the session, since the output file stream overwrites the file contents.
 * @param newUser a new user object
 *
bool DBFileManager::saveUser(User* currentUser)
{
    std::string dirPath = DBFileManager::createDirPath(currentUser->User::getUsername());
    std::string filepath = DBFileManager::createFilePath(currentUser->User::getUsername());

    if(!boost::filesystem::exists(dirPath))
    {
        std::cout << "Error: could not find user." << std::endl;
        return 1;
    }
    else
    {
        DBFileManager::writeToFile(*currentUser, filepath);
        return 0;
    }
}*/

bool DBFileManager::saveBridges(User* currentUser)
{
    std::string dirPath = DBFileManager::createDirPath(currentUser->User::getUsername());
    std::string filepath = DBFileManager::createBridgeFilePath(currentUser->User::getUsername());

    if(!boost::filesystem::exists(dirPath))
    {
        std::cout << "Error: could not find user." << std::endl;
        return 1;
    }
    else
    {
        DBFileManager::writeToFile(*currentUser, filepath);
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
    User currentUser;
    std::string userFile = DBFileManager::createUserFilePath(username);
    std::string bridgeFile = DBFileManager::createBridgeFilePath(username);

    if(!boost::filesystem::exists(userFile))
    {
        currentUser.setUsername("");
    }
    else
    {
        currentUser = DBFileManager::readFromFile(userFile, bridgeFile);
    }

    return currentUser;
}

std::string DBFileManager::createDirPath(std::string username)
{
    std::hash<std::string> usr_hash;
    std::stringstream ss;
    ss << usr_hash(username);
    std::string newusername = ss.str();

    std::string dirPath = "HUE_USERS";
    dirPath.std::string::append("/");
    dirPath.std::string::append(newusername);

    return dirPath;
}

std::string DBFileManager::createUserFilePath(std::string username)
{
    std::hash<std::string> usr_hash;
    std::stringstream ss;
    ss << usr_hash(username);
    std::string newusername = ss.str();

    std::string filepath = "HUE_USERS";
    filepath.std::string::append("/");
    filepath.std::string::append(newusername);
    filepath.std::string::append("/");
    filepath.std::string::append(newusername);
    filepath.std::string::append("_info.txt");

    return filepath;
}

std::string DBFileManager::createBridgeFilePath(std::string username)
{
    std::hash<std::string> usr_hash;
    std::stringstream ss;
    ss << usr_hash(username);
    std::string newusername = ss.str();

    std::string filepath = "HUE_USERS";
    filepath.std::string::append("/");
    filepath.std::string::append(newusername);
    filepath.std::string::append("/");
    filepath.std::string::append(newusername);
    filepath.std::string::append("_bridges.txt");

    return filepath;
}

/**
 * Write bridge data to file.
 */
void DBFileManager::writeToFile(User newUser, std::string bridgePath)
{
    std::ofstream bridgesWriteStream(bridgePath);

    if(!bridgesWriteStream.std::ofstream::is_open()) //check that file is open
    {
        std::cout << "File failed to open." << std::endl;
    }
    else
    {

        bridgesWriteStream << newUser.User::bridgesToString();

        bridgesWriteStream.std::ofstream::close();
        bridgesWriteStream.std::ofstream::clear();
    }
}

User DBFileManager::readFromFile(std::string userPath, std::string bridgePath)
{
    User currentUser;
    std::string currentLine;

    std::ifstream userReadStream(userPath);

    if(!userReadStream.std::ifstream::is_open()) //check that file is open
    {
        std::cout << "User file failed to open." << std::endl;
    }
    else
    {
        std::cout << "Reading useer info" << std::endl;
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

        userReadStream.std::ifstream::close();
        userReadStream.std::ifstream::clear();
    }

    std::ifstream bridgeReadStream(bridgePath);

    if(!bridgeReadStream.std::ifstream::is_open()) //check that file is open
    {
        std::cout << "Bridge file failed to open." << std::endl;
    }
    else
    {
        while(!bridgeReadStream.std::ifstream::eof())
        {
            Bridge tempBridge;

            std::getline(bridgeReadStream, currentLine);
            tempBridge.Bridge::setName(currentLine);

            std::getline(bridgeReadStream, currentLine);
            tempBridge.Bridge::setLocation(currentLine);

            std::getline(bridgeReadStream, currentLine);
            tempBridge.Bridge::setHostName(currentLine);

            std::getline(bridgeReadStream, currentLine);
            tempBridge.Bridge::setPort(currentLine);

            currentUser.User::addBridge(tempBridge);
        }

        bridgeReadStream.std::ifstream::close();
        bridgeReadStream.std::ifstream::clear();
    }

    return currentUser;
}


