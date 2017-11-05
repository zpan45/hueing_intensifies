/*
Light.h

The Light class [...]

@author - Jacob Fryer (jfryer6)
@date - November 04, 2017
*/

#ifndef _light_h_included
#define _light_h_included

#include <string>
#include <iostream>

class Light {
    public:
        Light();
        
        std::string getName();
        bool getIsActive();
        int getBrightness();
        std::string getColour();
        int getSchedule();
        void setName(std::string n);
        void setIsActive(bool onOff);
        void setBrightness(int b);
        void setColour(std::string hexcode);
        void setSchedule(int sched);
    private:
        void convertHexcodeToCoords(std::string col);
        
        std::string name;
        bool isActive;
        int brightness;
        std::string colour;
        int schedule;
};

#endif