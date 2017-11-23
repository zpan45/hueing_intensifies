/**
 * @file User.h
 * User Class head file.
 *
 * @brief User Class head file.
 * @author Jacob Fryer (jfryer6)
 * @date November 03, 2017
 */

#ifndef _user_h_included
#define _user_h_included

#include <string>
#include <iostream>
#include <vector>
#include "Bridge.h"

class User {
    public:
        User();
        User& operator=(const User&);
        User(std::string un, std::string pw, std::string first, std::string last);

        std::string getUsername();
        std::string getFirstName();
        std::string getLastName();
        std::string getPassword();
        Bridge getBridge(int element);
        std::vector<Bridge> getAllBridges();
        void setUsername(std::string u);
        void setFirstName(std::string first);
        void setLastName(std::string last);
        void setPassword(std::string pass);
        std::string constructGreetingString();
        std::string toString();
        std::string hashPassword(std::string pass);
    private:
        void addBridge(Bridge b);
        bool removeBridge(int element);

        std::string username;
        std::string firstName;
        std::string lastName;
        std::string password;
        std::vector<Bridge> bridges;
};

#endif
