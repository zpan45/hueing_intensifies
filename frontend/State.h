/**
 * @file State.h
 * State Class head file.
 * @brief State Class head file.
 * @author Anthony Tran (atran94)
 * @date November 28, 2017
 */

#ifndef _state_h_included
#define _state_h_included

#include <string>
#include <iostream>
#include <vector>


class State {
    public:
      State();
      State(bool any, bool all);

      bool getAny_On();
      bool getAll_On();
      void setAny_On();
      void setAll_On();

    private:
      bool any_on;
      bool all_on;
};

#endif
