/*
Group.h

The Group class [...]

@author - Jacob Fryer (jfryer6)
@date - November 04, 2017
*/

#ifndef _group_h_included
#define _group_h_included

#include <string>
#include <iostream>
#include <vector>
#include "Light.h"

class Group {
    public:
        Group();
        
        std::string getName();
        Light getLight(int element);
    private:
        void addLight(Light l);
        bool removeLight(int element);
        
        std::string name;
        std::vector<Light> lights;
};

#endif