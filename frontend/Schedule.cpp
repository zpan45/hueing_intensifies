/**
 * @class Schedule
 * Schedule Class.
 *
 * @brief Schedule Class
 * @author Jacob Fryer (jfryer6), Anthony Tran (atran94), Omar Abdel-Qader (oabdelqa), Usant Kajendirarajah (ukajendi), Zhengyang Pan (zpan45)
 * @date November 28, 2017
 */

 #include "Schedule.h"

 using namespace std;

 // --------------------------------------
 // CONSTRUCTORS
 // --------------------------------------


 /**
  * Default constructor for Schedule class. Initializes all fields to have no values.
  */
 Schedule::Schedule(): name(""), description(""), command(NULL), stime(""), localTime(""), status("") {
     // name = "";
     // description = "";
     // command = NULL;
     // stime = "";
     // localTime = "";
     // status = "";
 }

 /**
  * Overload constructor for Schedule class.
  * @param n for name.
  * @param d for description.
  * @param pointer c for command.
  * @param st for stime.
  * @param l for localTime.
  * @param s for status.
  */
 Schedule::Schedule(string n, string d, Command* c, string st, string l, string s): name(n), description(d), command(c), stime(st), localTime(l), status(s) {
     // name = "";
     // description = "";
     // command = NULL;
     // stime = "";
     // localTime = "";
     // status = "";
 }

 // --------------------------------------
 // PUBLIC METHODS
 // --------------------------------------


 /**
  * Getter for the name of the Schedule object.
  * @return the name field, a string.
  */
 string Schedule::getName() {
     return name;
 }

 /**
  * Getter for the description of the Schedule object.
  * @return the description field, a string.
  */
 string Schedule::getDescription() {
     return description;
 }

 /**
  * Getter for the command of the Schedule object.
  * @return pointer to command, an object containing "address", "method", and "body".
  */
 Command* Schedule::getCommand() {
     return command;

}

 /**
  * Getter for the time of the Schedule object.
  * @return the time field, a string.
  */
 string Schedule::getTime() {
     return stime;
 }

 /**
  * Getter for the localTime of the Schedule object.
  * @return the localTime field, a string.
  */
 string Schedule::getLocalTime() {
     return localTime;
 }

 /**
  * Getter for the status of the Schedule object.
  * @return the status field, a string either "enabled" or "disabled".
  */
 string Schedule::getStatus() {
     return status;
 }

 /**
  * Setter for the name field.
  * @param n A string for the name of the Schedule object.
  */
 void Schedule::setName(string n) {
     name = n;
 }

 /**
  * Setter for the description field.
  * @param d A string for the description of the Schedule object.
  */
 void Schedule::setDescription(string d) {
     description = d;
 }

 /**
  * Setter for the command field.
  * @param c a Command object for the command of the Schedule object.
  */
 void Schedule::setCommand(Command c) {
     command = c;
 }

 /**
  * Setter for the stime field.
  * @param t A string for the stime of the Schedule object.
  */
 void Schedule::setTime(string t) {
     stime = t;
 }

 /**
  * Setter for the localTime field.
  * @param lt A string for the localTime of the Schedule object.
  */
 void Schedule::setLocalTime(string lt) {
     localTime = lt;
 }

 /**
  * Setter for the status field.
  * @param s A string for the status of the Schedule object.
  */
 void Schedule::setStatus(string s) {
     status = s;
 }
