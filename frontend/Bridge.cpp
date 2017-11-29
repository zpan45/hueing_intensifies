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
Bridge::Bridge(): name(""), location(""), hostName(""), port(""), username(""), status("") {
    // name = "";
    // location = "";
    // hostName = "";
    // port = "";
    // username = "";
    // status = "";
}


/**
 * Overload constructor for Bridge class.
 * @param n for name.
 * @param l for location.
 * @param h for hostName.
 * @param p for port.
 * @param u for username.
 * @param s for status.
 */
Bridge::Bridge(string n, string l, string h, string p, string u, string s): name(n), location(l), hostName(h), port(p), username(u), status(s) {
    // name = "";
    // location = "";
    // hostName = "";
    // port = "";
    // username = "";
    // status = "";
}

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
 * Getter for the username of the Bridge object.
 * @return the username field, a string.
 */
string Bridge::getUsername() {
    return username;
}


/**
 * Getter for the status of the Bridge object.
 * @return the status field, a string.
 */
string Bridge::getStatus() {
    return status;
}


/**
 * Accessor method for a specific Group in this Bridge. Throws an out_of_range if attempting to access an element outside of the vector's bounds.
 * @param element The integer position of the desired Group object in the groups vector.
 * @return the desired Group object.
 */
Group* Bridge::getGroup(int element) {
    try {
        Group *g = &groups.at(element);
        return g;
    }
    catch(const out_of_range& oor) {
        cerr << element << " is out of range for this Bridge" << endl;
    }
    return 0;
}


/**
 * Accessor method for a specific Light in this Bridge. Throws an out_of_range if attempting to access an element outside of the vector's bounds.
 * @param element The integer position of the desired Light object in the groups vector.
 * @return the desired Light object.
 */
Light* Bridge::getLight(int element) {
    try {
        Light *l = &lights.at(element);
        return l;
    }
    catch(const out_of_range& oor) {
        cerr << element << " is out of range for this Bridge" << endl;
    }
    return 0;
}

/**
* Accessor method that returns the number of Lights associated with the Group, which is the length of the vector.
* @return the number of Lights as an integer.
*/
int Bridge::getNumberOfGroups() {
    return groups.size();
}

/**
 * Setter for the name field.
 * @param n A string for the name of the Bridge.
 */
void Bridge::setName(string n) {
    name = n;
}


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

/**
 * Setter for the username field.
 * @param p A string representation of the username for the Bridge.
 */
void Bridge::setUsername(string u) {
    username = u;
}

/**
 * Setter for the status field.
 * @param p A string representation of the status for the Bridge.
 */
void Bridge::setStatus(string s) {
    status = s;
}

std::string Bridge::toString()
{
    string temp = "";

    temp.std::string::append(Bridge::name);
    temp.std::string::append("\n");

    temp.std::string::append(Bridge::location);
    temp.std::string::append("\n");

    temp.std::string::append(Bridge::hostName);
    temp.std::string::append("\n");

    temp.std::string::append(Bridge::port);
    temp.std::string::append("\n");

    return temp;
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
 * Method that adds a Light to the Bridge by adding the Light object to the Bridge class's lights vector.
 * @param l A Light object to be added to the Bridge.
 */
void Bridge::addLight(Light l) {
    lights.push_back(l);
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


/**
 * Method to remove a Light at the given lightID from the Bridge.
 * @param element The integer position of the desired Light object in the lights vector.
 * @return whether the removal was successful as a boolean.
 */
bool Bridge::removeLight(int element) {
    // if the target Light is outside of the bounds of the groups vector, return false
    if( (element > lights.size() ) || (element < 0) ) {
        return false;
    }
        // else, remove the Light at the specified location
    else {
        lights.erase(lights.begin() + element);
        return true;
    }
}

/**
 * Method to drop all stored lights in the bridge.
 */
void Bridge::clearLights() {
    lights.clear();
}

/**
 * Method to drop all stored groups in the bridge.
 */
void Bridge::clearGroups() {
    groups.clear();
}