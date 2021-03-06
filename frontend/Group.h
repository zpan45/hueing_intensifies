/**
 * @file Group.h
 * Group Class head file.
 * @brief Group Class head file.
 * @author Jacob Fryer (jfryer6), Anthony Tran (atran94), Omar Abdel-Qader (oabdelqa), Usant Kajendirarajah (ukajendi), Zhengyang Pan (zpan45)
 * @date November 04, 2017
 */

#ifndef _group_h_included
#define _group_h_included

#include <string>
#include <iostream>
#include <vector>
#include "Light.h"
#include "Action.h"
#include "State.h"

class Group {
    public:
        Group();
        Group(std::string n, std::string i, Action* a, State* s, std::string t, std::string c);

        Action* getAction();
        std::string getID();
        std::string getName();
        State* getState();
        std::string getType();
        std::string getClass();

        Light* getLight(int element);

        int getNumberOfLights();
        void setName(std::string n);
        void setID(std::string i);
        void setState(State* s);
        void setType(std::string t);
        void setClass(std::string c);

        void addLight(Light l);
        bool removeLight(int element);
    private:
        std::string name;
        std::string id;
        Action* act;
        std::vector<Light> lights;
        State* groupState;
        std::string type;
        std::string groupClass;

};

#endif
