/**
 * @file Group.cpp
 * Group Class.
 *
 * @brief Group Class
 * @author Jacob Fryer (jfryer6)
 * @date November 04, 2017
 */


#include "Group.h"

using namespace std;

// --------------------------------------
// CONSTRUCTORS
// --------------------------------------


/**
 * Default constructor for Group class. Initializes all fields to have no values.
 * Takes no parameters.
 */
Group::Group() {
    name = "";
}

// ! TODO: Add overloaded constructor for creating a Group with fields

// --------------------------------------
// PUBLIC METHODS
// --------------------------------------


/**
 * Getter for the name of the Group.
 * Takes no parameters.
 * @return name as a string.
 */
string Group::getName() {
    return name;
}


/**
 * Accessor method for a specific Light in the Group.
 * Throws an out_of_range if attempting to access an element outside of the vector's bounds.
 * @param element The integer position of the desired Light object in the lights vector.
 * @return the desired Light object.
 */
Light Group::getLight(int element) {
    try {
        return lights.at(element);
    }
    catch(const out_of_range& oor) {
        cerr << element << " is out of range for this Group" << endl;
    }
}

/**
* Accessor method that returns the number of Lights associated with the Group, which is the length of the vector.
* @return the number of Lights as an integer.
*/
int Group::getNumberOfLights() {
    return lights.size();
}

void Group::setName(string n) {
    name = n;
}

// --------------------------------------
// PRIVATE METHODS
// --------------------------------------


/**
 * Method that adds a Light to the Group by adding the Light to the lights vector.
 * @param l A Light object to be added to the Group.
 */
void Group::addLight(Light l) {
    lights.push_back(l);
}


/**
 * Method to remove a Light at the given position from the Group.
 * @param element The integer position of the desired Light object in the lights vector.
 * @return whether the removal was successful as a boolean.
 */
bool Group::removeLight(int element) {
    // if the target Light is outside of the bounds of the lights vector, return false
    if( (element > lights.size() ) || (element < 0) ) {
        return false;
    }
    // else, remove the Light at the specified location
    else {
        lights.erase(lights.begin() + element);
        return true;
    }
}
