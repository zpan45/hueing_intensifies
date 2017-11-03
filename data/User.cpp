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

int main(int argc, char **argv) {
    User u;
    u.setUsername("jfryer6");
    
    u.setFirstName("Jake");
    u.setLastName("Fryer");
    
    cout << "Hello,\t" << u.getUsername() << " (" << u.getFirstName() << " " << u.getLastName() << ")" << endl;
    
    return 0;
}
