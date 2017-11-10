/**
 * @file Bridge.cpp
 * Bridge Class.
 *
 * @brief Bridge Class
 * @author Jacob Fryer (jfryer6)
 * @date November 04, 2017
 */

#include "Bridge.h"

using namespace std;

// --------------------------------------
// CONSTRUCTORS
// --------------------------------------


/**
 * Default constructor for Bridge class. Initializes all fields to have no values.
 */
Bridge::Bridge() {
    name = "";
    location = "";
    hostName = "";
    port = "";
}

// ! TODO: Add overloaded constructor for creating a Bridge with fields


// --------------------------------------
// PUBLIC METHODS
// --------------------------------------


/**
 * Getter for the name of the Bridge object.
 * @return the name field, a string.
 */
string Bridge::getName() {
    return name;
}


/**
 * Getter for the location of the Bridge object.
 * @return the location field, a string.
 */
string Bridge::getLocation() {
    return location;
}


/**
 * Getter for the host name of the Bridge object.
 * @return the host name field, a string.
 */
string Bridge::getHostName() {
    return hostName;
}


/**
 * Getter for the port of the Bridge object.
 * @return the port field, a string.
 */
string Bridge::getPort() {
    return port;
}


/**
 * Accessor method for a specific Group in this Bridge. Throws an out_of_range if attempting to access an element outside of the vector's bounds.
 * @param element The integer position of the desired Group object in the groups vector.
 * @return the desired Group object.
 */
Group Bridge::getGroup(int element) {
    try {
        return groups.at(element);
    }
    catch(const out_of_range& oor) {
        cerr << element << " is out of range for this Bridge" << endl;
    }
}


/**
 * Setter for the name field.
 * @param n A string for the name of the Bridge.
 */
void Bridge::setName(string n) {
    name = n;
}

/*
setLocation()

Setter for the location field.

Parameters:
- string l: A string providing the location of the Bridge.
*/
/**
 * Setter for the location field.
 * @param l A string for the location of the Bridge.
 */
void Bridge::setLocation(string l) {
    location = l;
}


/**
 * Setter for the hostName field.
 * @param hn A string representation of the host name for the Bridge.
 */
void Bridge::setHostName(string hn) {
    hostName = hn;
}


/**
 * Setter for the port field.
 * @param p A string representation of the Port for the Bridge.
 */
void Bridge::setPort(string p) {
    port = p;
}

// --------------------------------------
// PRIVATE METHODS
// --------------------------------------


/**
 * Method that adds a Group to the Bridge by adding the Group object to the Bridge class's groups vector.
 * @param g A Group object to be added to the Bridge.
 */
void Bridge::addGroup(Group g) {
    groups.push_back(g);
}


/**
 * Method to remove a Group at the given position from the Bridge.
 * @param element The integer position of the desired Group object in the groups vector.
 * @return whether the removal was successful as a boolean.
 */
bool Bridge::removeGroup(int element) {
    // if the target Group is outside of the bounds of the groups vector, return false
    if( (element > groups.size() ) || (element < 0) ) {
        return false;
    }
    // else, remove the Group at the specified location
    else {
        groups.erase(groups.begin() + element);
        return true;
    }
}