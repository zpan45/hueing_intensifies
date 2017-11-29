/**
 * @file Bridge.h
 * Bridge Class head file.
 *
 * @brief Bridge Class head file.
 * @author Jacob Fryer (jfryer6)
 * @date November 04, 2017
 */

#ifndef _bridge_h_included
#define _bridge_h_included

#include <string>
#include <iostream>
#include <vector>
#include "Group.h"
#include "Light.h"

class Bridge {
    public:
        Bridge();
        Bridge(std::string n, std::string l, std::string h, std::string p, std::string u, std::string s);

        std::string getName();
        std::string getLocation();
        std::string getHostName();
        std::string getPort();
        std::string getUsername();
        std::string getStatus();
        Group* getGroup(int element);
        Light* getLight(int element);
        int getNumberOfGroups();

        void setName(std::string n);
        void setLocation(std::string l);
        void setHostName(std::string hn);
        void setPort(std::string p);
        void setUsername(std::string u);
        void setStatus(std::string s);
        std::string toString();

        void addGroup(Group g);
        void addLight(Light l);
        void clearGroups();
        void clearLights();
        bool removeGroup(int element);
        bool removeLight(int element);
    private:
        std::string name;
        std::string location;
        std::string hostName;
        std::string port;
        std::string username;
        //status is used to store API response from bridge
        std::string status;
        std::vector<Group> groups;
        std::vector<Light> lights;
};

#endif
