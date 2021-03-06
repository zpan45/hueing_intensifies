/**
 * @file Light.h
 * Light Class head file.
 *
 * @brief Light Class head file
 * @author Jacob Fryer (jfryer6), Anthony Tran (atran94), Omar Abdel-Qader (oabdelqa), Usant Kajendirarajah (ukajendi), Zhengyang Pan (zpan45)
 * @date November 05, 2017
 */

#ifndef _light_h_included
#define _light_h_included

#include <string>
#include <iostream>

class Light {
    public:
        Light();
        Light(std::string n, bool i, int b, int h, int s, std::string id);

        std::string getName();
        bool getIsActive();
        int getBrightness();
        int getHue();
        int getSat();
        std::string getID();
        void setName(std::string n);
        void setIsActive(bool onOff);
        void setBrightness(int b);
        void setHue(int h);
        void setSat(int s);
        void setID(std::string i);
    private:
        std::string name;
        bool isActive;
        int brightness;
        int hue;
        int sat;
        std::string id;
};

#endif
