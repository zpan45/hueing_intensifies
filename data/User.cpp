/*
User.cpp

User.cpp [...]

@author - Jacob Fryer (jfryer6)
@date - November 03, 2017
*/

#include <functional>
#include <cstddef>
#include "User.h"

using namespace std;

// --------------------------------------
// CONSTRUCTORS
// --------------------------------------

/*
User()

Default constructor for User class. Initializes all fields to have no values.
Takes no parameters.
*/
User::User() {
    username = "";
    password = "";
    firstName = "";
    lastName = "";
}

/*
Copy assignment for User class

This method allows the copying of one User object to another
by overloading the assignment operator (=)

Takes one User object pointer as a parameter
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

/*
User()

Overloaded constructor for the User class. Initializes all fields to have specified values.

Parameters
- string un: The User's associated username, a string
- string pw: The User's associated password, a string
- string first: The User's first name, a string
- string last: The User's last name, a string
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

/*
getUsername()

Getter for the username field.

Takes no parameters.

Returns the username associated with this user, a string.
*/
string User::getUsername() {
    return username;
}

/*
getFirstName()

Getter for the first name field.

Takes no parameters.

Returns the first name associated with this user, a string.
*/
string User::getFirstName() {
    return firstName;
}

/*
getLastName()

Getter for the last name field.

Takes no parameters.

Returns the last name associated with this user, a string.
*/
string User::getLastName() {
    return lastName;
}

/*
getPassword()

Getter for the password field.

Takes no parameters.

Returns the password associated with this user, a string.
*/
string User::getPassword() {
    return password;
}

/*
getBridge()

Accessor method for a specific Bridge for this User. Throws an out_of_range if attempting to access an element outside of the vector's bounds.

Parameters:
- int element: The integer position of the desired Bridge object in the bridges vector.

Returns the desired Bridge object.
*/
Bridge User::getBridge(int element) {
    try {
        return bridges.at(element);
    }
    catch(const out_of_range& oor) {
        cerr << element << " is out of range for this User" << endl;
    }
}

/*
setUsername()

Setter for the username field.

Parameters:
- string u : A well-formed string.
*/
void User::setUsername(string u) {
    username = u;
}

/*
setFirstName()

Setter for the user's first name field.

Parameters:
- string first : A well-formed string.
*/
void User::setFirstName(string first) {
    firstName = first;
}

/*
setLastName()

Setter for the user's last name field.

Parameters:
- string last : A well-formed string.
*/
void User::setLastName(string last) {
    lastName = last;
}

/*
setPassword()

Setter for the user's password field.

Parameters:
- string pass : A well-formed string.
*/
void User::setPassword(string pass) {
    password = pass;
}

/*
constructGreetingString()

Method that constructs a string to greet the User in the form of "Hello, <username> (<first> <last>)".

Returns a greeting in the specified form.
*/
string User::constructGreetingString() {
    return "Hello, \t" + username + " (" + firstName + " " + lastName + ")";
}

/*
toString()

Returns user info in a singe string.

Takes no parameters.
*/
string User::toString()  {
    string temp = "";

    temp.std::string::append(username);
    temp.std::string::append("\t");

    temp.std::string::append(password);
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

/*
hashPassword()

Takes the user's password as a parameter and generates a "hashed" version of that password.

Parameters:
- string pass : A well-formed string.

Returns the hashed version of the password.
*/
size_t User::hashPassword(string pass) {

    std::hash<std::string> str_hash;

    return str_hash(pass);
}

/*
addBridge()

Method that assigns a given Bridge to the User by adding the Bridge object to the User class's bridges vector.

Parameters:
- Bridge b: A Bridge object to be assigned to the User.
*/
void User::addBridge(Bridge b) {
    bridges.push_back(b);
}

/*
removeBridge()

Method to remove a Bridge at the given position from the User.

Parameters:
- int element: The integer position of the desired Bridge object in the bridges vector.

Returns whether the removal was successful as a boolean.
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
