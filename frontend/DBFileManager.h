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
        bool saveBridges(User* newUser); //check for existence in filesystem, build path and write info to file
        bool removeUser(User currentUser); //check for existence in filesystem and delete directory associated with user
        User getUser(std::string username); //check for existence in filesystem

        std::string createDirPath(std::string username);
        std::string createUserFilePath(std::string username);
        std::string createBridgeFilePath(std::string username);
        void writeToFile(User newUser, std::string userPath);
        User readFromFile(std::string userPath, std::string bridgePath);
};
#endif // DBFILEMANAGER_H
