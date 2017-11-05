/*
Bridge.h

The Bridge class [...]

@author - Jacob Fryer (jfryer6)
@date - November 04, 2017
*/

#ifndef _bridge_h_included
#define _bridge_h_included

#include <string>
#include <iostream>
#include <vector>
#include "Group.h"

class Bridge {
    public:
        Bridge();
        
        std::string getName();
        std::string getLocation();
        std::string getHostName();
        std::string getPort();
        Group getGroup(int element);
        
        void setName(std::string n);
        void setLocation(std::string l);
        void setHostName(std::string hn);
        void setPort(std::string p);
    private:
        void addGroup(Group g);
        bool removeGroup(int element);
        
        std::string name;
        std::string location;
        std::string hostName;
        std::string port;
        std::vector<Group> groups;
};

#endif