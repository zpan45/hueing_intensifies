
/**
 * @file Command.h
 * Command Class head file.
 *
 * @brief Command Class head file
 * @author Jacob Fryer (jfryer6), Anthony Tran (atran94), Omar Abdel-Qader (oabdelqa), Usant Kajendirarajah (ukajendi), Zhengyang Pan (zpan45)
 * @date November 28, 2017
 */

#ifndef _command_h_included
#define _command_h_included

#include <string>
#include <iostream>

class Command {
    public:
        Command();
        Command(std::string a, std::string m, std::string b);

        std::string getAddress();
        std::string getMethod();
        std::string getBody();
        void setAddress(std::string a);
        void setMethod(std::string m);
        void setBody(std::string b);

    private:

        std::string address;
        std::string method;
        std::string body;
};

#endif
