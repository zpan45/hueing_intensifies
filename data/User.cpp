/*
User.cpp

User.cpp [...]

@author - Jacob Fryer (jfryer6)
@date - November 03, 2017
*/

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

// ! TODO: Add overloaded constructor for creating a user with fields

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

string User::constructGreetingString() {
    return "Hello, \t" + username + " (" + firstName + " " + lastName + ")";
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
string User::hashPassword(string pass) {
    // ! TODO: Add method for hashing a user's password and returning the hashed string
    
    return pass;
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

int main(int argc, char **argv) {
    User u;
    u.setUsername("jfryer6");
    
    u.setFirstName("Jake");
    u.setLastName("Fryer");
    
    //cout << "Hello,\t" << u.getUsername() << " (" << u.getFirstName() << " " << u.getLastName() << ")" << endl;
    
    cout << u.constructGreetingString() << endl;
    
    return 0;
}
