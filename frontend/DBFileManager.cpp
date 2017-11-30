/**
 * @class DBFileManager
 * Database is implemented as a filesystem using Boost's filesystem library. Each user has a their own directory
 * containing two files, one for user info and one for bridge info. Both files are read to create a User object.
 * A user directory and info file are created on registration and never modified. Bridge files are created on
 * adding a new bridge and are modified whenever a bridge is updated or added.
 *
 * @brief Database file manager
 * @author Jacob Fryer (jfryer6), Anthony Tran (atran94), Omar Abdel-Qader (oabdelqa), Usant Kajendirarajah (ukajendi), Zhengyang Pan (zpan45)
 */

#include <cstddef>
#include <sstream>

#include "DBFileManager.h"

// --------------------------------------
// CONSTRUCTOR
// --------------------------------------

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

// --------------------------------------
// PUBLIC METHODS
// --------------------------------------

/**
 * Creates a new directory for a newly registered user.
 * @param newUser a new user object
 */
bool DBFileManager::addNewUser(User newUser)
{
    std::string username = newUser.User::getUsername();
    std::string dirPath = DBFileManager::createDirPath(username); //creates a path to the directory using the username

    if(boost::filesystem::exists(dirPath))
    {
        std::cout << "Error: user already exists." << std::endl;
        return 1;
    }
    else
    {
        boost::filesystem::create_directory(dirPath); //create a directory for specified user
        dirPath = DBFileManager::createUserFilePath(username); //create a path to the user info file
        std::ofstream userWriteStream(dirPath); //open a write stream to user info file

        if(!userWriteStream.std::ofstream::is_open()) //check that file is open
        {
            std::cout << "File failed to open." << std::endl;
        }
        else
        {
            userWriteStream << newUser.User::infoToString() << std::endl; //write user's info to file; this is only done once

            userWriteStream.std::ofstream::close();//close and clear file stream
            userWriteStream.std::ofstream::clear();
        }
        return 0;
    }
}

/**
 * Creates a new bridge info file within the user's directory, and can be used to save a user's info
 * bridge info during or at the end of the session.
 * @param newUser a new user object
 * @return a boolean indicating whether the operation was successful
 */
bool DBFileManager::saveBridges(User* currentUser)
{
    std::string dirPath = DBFileManager::createDirPath(currentUser->User::getUsername()); //creates a path to the directory using the username
    std::string filepath = DBFileManager::createBridgeFilePath(currentUser->User::getUsername()); //creates a path to the user's bridge file

    if(!boost::filesystem::exists(dirPath))
    {
        std::cout << "Error: could not find user." << std::endl;
        return 1;
    }
    else
    {
        DBFileManager::writeToFile(*currentUser, filepath); //call on writeToFile method to write bridges to file
        return 0;
    }
}

/**
 * Removes a user from the database by removing all associated directories and files
 * @param newUser a user object to be removed
 * @return a boolean indicating whether the operation was successful
 */
bool DBFileManager::removeUser(User currentUser)
{
    std::string filepath = DBFileManager::createDirPath(currentUser.User::getUsername()); //creates a path to the directory using the username

    if(!boost::filesystem::exists(filepath))
    {
        std::cout << "Error: could not find user." << std::endl;
        return 1;
    }
    else
    {
        boost::filesystem::remove_all(filepath); //remove all directories associated with the user
        return 0;
    }
}

/**
 * Creates a user object by calling readFromFile() method in User class
 * @param username a username identifying the user in the DB
 * @return a User object containing user info and bridges from file
 */
User DBFileManager::getUser(std::string username)
{
    User currentUser;
    std::string userFile = DBFileManager::createUserFilePath(username); //creates a path to the user's info file
    std::string bridgeFile = DBFileManager::createBridgeFilePath(username); //creates a path to the user's bridge file


    if(!boost::filesystem::exists(userFile))
    {
        currentUser.setUsername(""); //returns a user with empty name if user doesn't exist
    }
    else
    {
        currentUser = DBFileManager::readFromFile(userFile, bridgeFile); //call to readFromFile to build a user
    }

    return currentUser;
}

/**
* Creates a string indicating the path of the user's directory within the filesystem
* @param username the username of the user to be found
* @return a string indicating the path to the directory in the filesystem
*/
std::string DBFileManager::createDirPath(std::string username)
{
<<<<<<< HEAD
    std::hash<std::string> usr_hash;
    std::stringstream ss;
    ss << usr_hash(username);
    std::string newusername = ss.str(); //username is hashed for security purposes
=======
    std::hash<std::string> usr_hash;
    std::stringstream ss;
    ss << usr_hash(username);
    std::string newusername = ss.str();
>>>>>>> 0f4de2afb4aaaf99a2dcd97d77dcda43db5f47ac

    std::string dirPath = "HUE_USERS";
    dirPath.std::string::append("/");
    dirPath.std::string::append(newusername);

    return dirPath;
}

/**
* Creates a string indicating the path of the user's information file within the filesystem
* @param username the username of the user to be found
* @return a string indicating the path to the user info file in the filesystem
*/
std::string DBFileManager::createUserFilePath(std::string username)
{
<<<<<<< HEAD
    std::hash<std::string> usr_hash;
    std::stringstream ss;
    ss << usr_hash(username);
    std::string newusername = ss.str(); //username is hashed for security purposes
=======
    std::hash<std::string> usr_hash;
    std::stringstream ss;
    ss << usr_hash(username);
    std::string newusername = ss.str();
>>>>>>> 0f4de2afb4aaaf99a2dcd97d77dcda43db5f47ac

    std::string filepath = "HUE_USERS";
    filepath.std::string::append("/");
    filepath.std::string::append(newusername);
    filepath.std::string::append("/");
    filepath.std::string::append(newusername);
    filepath.std::string::append("_info.txt");

    return filepath;
}

/**
* Creates a string indicating the path of the user's bridge information file within the filesystem
* @param username the username of the user to be found
* @return a string indicating the path to the user's bridge info file in the filesystem
*/
std::string DBFileManager::createBridgeFilePath(std::string username)
{
    std::hash<std::string> usr_hash;
    std::stringstream ss;
    ss << usr_hash(username);
    std::string newusername = ss.str(); //username is hashed for security purposes

    std::string filepath = "HUE_USERS";
    filepath.std::string::append("/");
    filepath.std::string::append(newusername);
    filepath.std::string::append("/");
    filepath.std::string::append(newusername);
    filepath.std::string::append("_bridges.txt");

    return filepath;
}

/**
 * Write the user's bridge data to file on bridge update or app termination.
 * @param newUser user who's bridge info is being saved
 * @param bridgePath the path to the user's bridge file in the DB filesystem
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

        bridgesWriteStream << newUser.User::bridgesToString(); //loop through user's bridges and write to file

        bridgesWriteStream.std::ofstream::close(); //close and clear file stream
        bridgesWriteStream.std::ofstream::clear();
    }
}

/**
 * Reads the user's bridge and info from files and create a user object.
 * @param userPath path to user's information file
 * @param bridgePath the path to the user's bridge file in the DB filesystem
 */
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
        //set username, password, first and last names from info file
        std::getline(userReadStream, currentLine);
        currentUser.User::setUsername(currentLine);

        std::getline(userReadStream, currentLine);
        currentUser.User::setPassword(currentLine);

        std::getline(userReadStream, currentLine);
        currentUser.User::setFirstName(currentLine);

        std::getline(userReadStream, currentLine);
        currentUser.User::setLastName(currentLine);

        userReadStream.std::ifstream::close(); //close and clear file stream
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

            //set bridge name, location, hostname, and port from bridge file
            std::getline(bridgeReadStream, currentLine);
            tempBridge.Bridge::setName(currentLine);

            std::getline(bridgeReadStream, currentLine);
            tempBridge.Bridge::setLocation(currentLine);

            std::getline(bridgeReadStream, currentLine);
            tempBridge.Bridge::setHostName(currentLine);

            std::getline(bridgeReadStream, currentLine);
            tempBridge.Bridge::setPort(currentLine);

            currentUser.User::addBridge(tempBridge); //add the bridge to the user
        }

        bridgeReadStream.std::ifstream::close(); //close and clear file stream
        bridgeReadStream.std::ifstream::clear();
    }

    return currentUser;
}


