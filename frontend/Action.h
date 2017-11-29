/**
 * @file Action.h
 * gAction Class head file.
 * @brief Action Class head file.
 * @author Anthony Tran (atran94)
 * @date November 28, 2017
 */

#ifndef _action_h_included
#define _action_h_included

#include <string>
#include <iostream>


class Action {
    public:
      Action();

      bool getIsActive();
      int getBrightness();
      int getHue();
      int getSat();
      void setIsActive(bool onOff);
      void setBrightness(int b);
      void setHue(int h);
      void setSat(int s);
    private:
      bool isActive;
      // std::string effect; Could implement this
      int brightness;
      int hue;
      int sat;
};

#endif
