/*
Bridge.cpp

Bridge.cpp [...]

@author - Jacob Fryer (jfryer6)
@date - November 04, 2017
*/

#include "Bridge.h"

using namespace std;

// --------------------------------------
// CONSTRUCTORS
// --------------------------------------

/*
Bridge()

Default constructor for Bridge class. Initializes all fields to have no values.
Takes no parameters.
*/
Bridge() {
    name = "";
    location = "";
    hostName = "";
    port = "";
}

// ! TODO: Add overloaded constructor for creating a Bridge with fields


// --------------------------------------
// PUBLIC METHODS
// --------------------------------------

/*
getName()

Getter for the name of the Bridge.

Takes no parameters.

Returns name as a string.
*/
string getName() {
    return name;
}

/*
getLocation()

Getter for the location of the Bridge.

Takes no parameters.

Returns location as a string.
*/
string getLocation() {
    return location;
}

/*
getHostName()

Getter for the host name of the Bridge.

Takes no parameters.

Returns hostName as a string.
*/
string getHostName() {
    return hostName;
}

/*
getPort()

Getter for the port of the Bridge.

Takes no parameters.

Returns port as a string.
*/
string getPort() {
    return port;
}

/*
getGroup()

Accessor method for a specific Group in this Bridge. Throws an out_of_range if attempting to access an element outside of the vector's bounds.

Parameters:
- int element: The integer position of the desired Group object in the groups vector.

Returns the desired Group object.
*/
Group getGroup(int element) {
    try {
        return groups.at(element);
    }
    catch(const out_of_range& oor) {
        cerr << element << " is out of range for this Bridge" << endl;
    }
}

/*
setName()

Setter for the name field.

Parameters:
- string n: The name of the Bridge.
*/
void setName(string n) {
    name = n;
}

/*
setLocation()

Setter for the location field.

Parameters:
- string l: A string providing the location of the Bridge.
*/
void setLocation(string l) {
    location = l;
}

/*
setHostName()

Setter for the hostName field.

Parameters:
- string hn: A string representation of the host name for the Bridge.
*/
void setHostName(string hn) {
    hostName = hn;
}

/*
setPort()

Setter for the port field.

Parameters:
- string p: A string representation of the Port for the Bridge.
*/
void setPort(string p) {
    port = p;
}

// --------------------------------------
// PRIVATE METHODS
// --------------------------------------

/*
addGroup()

Method that adds a Group to the Bridge by adding the Group object to the Bridge class's groups vector.

Parameters:
- Group g: A Group object to be added to the Bridge.
*/
void addGroup(Group g) {
    groups.push_back(g);
}

/*
removeGroup()

Method to remove a Group at the given position from the Bridge.

Parameters:
- int element: The integer position of the desired Group object in the groups vector.

Returns whether the removal was successful as a boolean.
*/
bool removeGroup(int element) {
    // if the target Group is outside of the bounds of the groups vector, return false
    if( (element > groups.size() ) || (element < 0) ) {
        return false;
    }
    // else, remove the Group at the specified location
    else {
        groups.erase(element);
        return true;
    }
}
