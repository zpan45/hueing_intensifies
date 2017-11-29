
/**
 * @file Schedule.h
 * schedule Class head file.
 *
 * @brief Schedule Class head file
 * @author Anthony Tran (Atran94)
 * @date November 28, 2017
 */

#ifndef _schedule_h_included
#define _schedule_h_included

#include <string>
#include <iostream>
#include "Command.h"

class Schedule {
    public:
        Schedule();
        Schedule(std::string n, std::string d, Command c, std::string st, std::string l, std::string s)

        std::string getName();
        std::string getDescription();
        Command getCommand();
        std::string getTime();
        std::string getLocalTime();
        std::string getStatus();
        void setName(std::string n);
        void setDescription(std::string d);
        void setCommand(Object c);
        void setTime(std::string t);
        void setLocalTime(std::string lt);
        void setStatus(std::string s);

    private:

        std::string name;
        std::string description;
        Command command;
        std::string stime;
        std::string localTime;
        std::string status;
};

#endif
