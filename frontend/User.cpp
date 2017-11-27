/**
 * @file User.cpp
 * User Class.
 *
 * @brief User Class
 * @author Jacob Fryer (jfryer6)
 * @date November 03, 2017
 */


#include <functional>
#include <cstddef>
#include <sstream>
#include "User.h"

using namespace std;

// --------------------------------------
// CONSTRUCTORS
// --------------------------------------


/**
 * Default constructor for User class. Initializes all fields to have no values.
 * Takes no parameters.
 */
User::User() {
    username = "";
    password = "";
    firstName = "";
    lastName = "";
}


/**
 * Copy assignment for User class.
 * This method allows the copying of one User object to another by overloading the assignment operator (=).
 * @param otherUser the user object being copied
 * @return the copied new user object
 */
User& User::operator=(const User& otherUser)
{
    User::username = otherUser.username;
    User::firstName = otherUser.firstName;
    User::lastName = otherUser.lastName;
    User::password = otherUser.password;
    //User::bridges = otherUser.bridges;

    return *this;
}


/** Overloaded constructor for the User class. Initializes all fields to have specified values.
 * 
 * @param un The User's associated username, a string
 * @param pw The User's associated password, a string
 * @param first The User's first name, a string
 * @param last The User's last name, a string
 */
User::User(string un, string pw, string first, string last) {
    username = un;
    password = pw;
    firstName = first;
    lastName = last;
}

// --------------------------------------
// PUBLIC METHODS
// --------------------------------------


/**
 * Getter for the username field.
 * @return the username associated with this user, a string.
 */
string User::getUsername() {
    return username;
}


/**
 * Getter for the first name field.
 * @return the first name associated with this user, a string.
 */
string User::getFirstName() {
    return firstName;
}


/**
 * Getter for the last name field.
 * @return the last name associated with this user, a string.
 */
string User::getLastName() {
    return lastName;
}


/**
 * Getter for the password field.
 * @return the password associated with this user, a string.
 */
string User::getPassword() {
    return password;
}


/**
 * Accessor method for a specific Bridge for this User. Throws an out_of_range if attempting to access an element outside of the vector's bounds.
 * @param element The integer position of the desired Bridge object in the bridges vector.
 * @return the desired Bridge object.
 */
Bridge* User::getBridge(int element) {
    try {
        Bridge *b = &bridges.at(element);
        return b;
    }
    catch(const out_of_range& oor) {
        cerr << element << " is out of range for this User" << endl;
    }
}

/**
* Accessor method that returns the number of Bridges associated with the User, which is the length of the vector.
* @return the number of Bridges as an integer.
*/
int User::getNumberOfBridges() {
    return bridges.size();
}

/**
 * Setter for the username field.
 * @param u A well-formed string as username.
 */
void User::setUsername(string u) {
    username = u;
}


/**
 * Setter for the first name field.
 * @param u A well-formed string as first name.
 */
void User::setFirstName(string first) {
    firstName = first;
}


/**
 * Setter for the last name field.
 * @param u A well-formed string as last name.
 */
void User::setLastName(string last) {
    lastName = last;
}


/**
 * Setter for the password field.
 * @param u A well-formed string as password.
 */
void User::setPassword(string pass) {
    password = pass;
}


/**
 * Method that constructs a string to greet the User in the form of "Hello, <username> (<first> <last>)".

 * @return a greeting in the specified form.
 */
string User::constructGreetingString() {
    return "Hello, \t" + username + " (" + firstName + " " + lastName + ")";
}


/**
 * Returns user info in a singe string.
 * @return user as string
 */
string User::toString()  {
    string temp = "";

    temp.std::string::append(username);
    temp.std::string::append("\t");

    temp.std::string::append(User::hashPassword(password));
    temp.std::string::append("\t");

    temp.std::string::append(firstName);
    temp.std::string::append("\t");

    temp.std::string::append(lastName);
    temp.std::string::append("\t");

    return temp;
    //Add something for bridges when it's all worked out
}

// --------------------------------------
// PRIVATE METHODS
// --------------------------------------


/**
 * Takes the user's password as a parameter and generates a "hashed" version of that password.
 * @param pass A well-formed string as password.
 * @return the hashed version of the password.
 */
string User::hashPassword(string pass) {

    std::hash<std::string> str_hash;

    std::stringstream ss;

    ss << str_hash(pass);

    return ss.str();
}


/**
 * Method that assigns a given Bridge to the User by adding the Bridge object to the User class's bridges vector.
 * @param b A Bridge object to be assigned to the User.
 */
void User::addBridge(Bridge b) {
    bridges.push_back(b);
}


/**
 * Method to remove a Bridge at the given position from the User.
 * @param element The integer position of the desired Bridge object in the bridges vector.
 * @return whether the removal was successful as a boolean.
 */
bool User::removeBridge(int element) {
    // if the target Bridge is outside of the bounds of the bridges vector, return false
    if( (element > bridges.size() ) || (element < 0) ) {
        return false;
    }
    // else, remove the Bridge at the specified location
    else {
        bridges.erase(bridges.begin() + element);
        return true;
    }
}

/*int main(int argc, char **argv) {
    User u;
    u.setUsername("jfryer6");

    u.setFirstName("Jake");
    u.setLastName("Fryer");

    //cout << "Hello,\t" << u.getUsername() << " (" << u.getFirstName() << " " << u.getLastName() << ")" << endl;

    User u2("Username", "password123", "Some", "Body");

    cout << u.constructGreetingString() << endl;
    cout << u2.constructGreetingString() << endl;

    return 0;
}*/
