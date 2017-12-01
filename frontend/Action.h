/**
 * @file Action.h
 * gAction Class head file.
 * @brief Action Class head file.
 * @author Jacob Fryer (jfryer6), Anthony Tran (atran94), Omar Abdel-Qader (oabdelqa), Usant Kajendirarajah (ukajendi), Zhengyang Pan (zpan45)
 * @date November 28, 2017
 */

#ifndef _action_h_included
#define _action_h_included

#include <string>
#include <iostream>


class Action {
    public:
      Action();
      Action(bool i, int b, int h, int s);

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
