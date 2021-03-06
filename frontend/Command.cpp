/**
 * @class Command
 * Command Class.
 *
 * @brief Command Class
 * @author Jacob Fryer (jfryer6), Anthony Tran (atran94), Omar Abdel-Qader (oabdelqa), Usant Kajendirarajah (ukajendi), Zhengyang Pan (zpan45)
 * @date November 28, 2017
 */

 #include "Command.h"

 using namespace std;

 // --------------------------------------
 // CONSTRUCTORS
 // --------------------------------------

 /**
  * Default constructor for Command class. Initializes all fields to have no values.
  */
 Command::Command(): address(""), method(""), body("") {
     // address = "";
     // method = "";
     // body = "";
 }

 /**
  * Overload constructor for Command class.
  * @param a for address.
  * @param m for method.
  * @param b for body.
  */
 Command::Command(string a, string m, string b): address(a), method(m), body(b) {
     // address = "";
     // method = "";
     // body = "";
 }

 // --------------------------------------
 // PUBLIC METHODS
 // --------------------------------------

 /**
  * Getter for the address of the Command object.
  * @return the address field, a string.
  */
 string Command::getAddress() {
     return address;
 }

 /**
  * Getter for the method of the Command object.
  * @return the method field, a string - "POST", "PUT", or "DELETE".
  */
 string Command::getMethod() {
     return method;
 }

 /**
  * Getter for the body of the Command object.
  * @return the body field, a string.
  */
 string Command::getBody() {
     return body;
 }

 /**
  * Setter for the address field.
  * @param a A string for the address of the Command object
  * address is the path to a light, group, or bridge resource.
  */
 void Command::setAddress(string a) {
     address = a;
 }

 /**
  * Setter for the method field.
  * @param m A string for the method of the Command object.
  * method is an HTTP method - "POST", "PUT", or "DELETE".
  */
 void Command::setMethod(string m) {
     method = m;
 }

 /**
  * Setter for the body field.
  * @param b A Json string for the body of the Command object.
  */
 void Command::setBody(string b) {
     body = b;
 }
