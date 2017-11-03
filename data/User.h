/*
User.h

The User class [...]

@author - Jacob Fryer (jfryer6)
@date - November 03, 2017
*/

#ifndef _user_h_included
#define _user_h_included

#include <string>
#include <iostream>

class User {
    public:
        User();
        
        std::string getUsername();
        std::string getFirstName();
        std::string getLastName();
        void setUsername(std::string u);
        void setFirstName(std::string first);
        void setLastName(std::string last);
        void setPassword(std::string pass);
    private:
        std::string hashPassword(std::string pass); 
        
        std::string username;
        std::string firstName;
        std::string lastName;
        std::string password;
};

#endif