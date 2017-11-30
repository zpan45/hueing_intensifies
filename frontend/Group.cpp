/**
 * @class Group
 * Group Class.
 *
 * @brief Group Class
 * @author Jacob Fryer (jfryer6), Anthony Tran (atran94), Omar Abdel-Qader (oabdelqa), Usant Kajendirarajah (ukajendi), Zhengyang Pan (zpan45)
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
Group::Group(): name(""), act(NULL), groupState(NULL), type("LightGroup"), groupClass("Other") {

}

/**
 * Overload constructor for Group class.
 * @param n for name.
 * @param a pointer for act.
 * @param s pointer for state.
 * @param t for type.
 * @param c for groupClass.
 */
Group::Group(string n, Action* a, State* s, string t, string c): name(n), act(a), groupState(s), type(t), groupClass(c) {

}

// --------------------------------------
// PUBLIC METHODS
// --------------------------------------


/**
 * Getter for the Action of the Group.
 * Takes no parameters.
 * @return pointer to act object.
 */
Action* Group::getAction() {
    return act;
}


/**
 * Getter for the name of the Group.
 * Takes no parameters.
 * @return name as a string.
 */
string Group::getName() {
    return name;
}


/**
 * Getter for the state of the Group.
 * Takes no parameters.
 * @return pointer to groupState object.
 */
State* Group::getState() {
    return groupState;
}


/**
 * Getter for the type of the Group.
 * Takes no parameters.
 * @return type as a string.
 */
string Group::getType() {
    return type;
}


/**
 * Getter for the class of the Group.
 * Takes no parameters.
 * @return class as a string.
 */
string Group::getClass() {
    return groupClass;
}


/**
 * Accessor method for a specific Light in the Group.
 * Throws an out_of_range if attempting to access an element outside of the vector's bounds.
 * @param element The integer position of the desired Light object in the lights vector.
 * @return the desired Light object.
 */
Light* Group::getLight(int element) {
    try {
        Light *l = &lights.at(element);
        return l;
    }
    catch(const out_of_range& oor) {
        cerr << element << " is out of range for this Group" << endl;
    }
    return 0;
}

/**
* Accessor method that returns the number of Lights associated with the Group, which is the length of the vector.
* @return the number of Lights as an integer.
*/
int Group::getNumberOfLights() {
    return lights.size();
}


/**
 * Setter for the name field.
 * @param n A string of the group name.
 */
void Group::setName(string n) {
    name = n;
}


/**
 * Setter for the state field.
 * @param s A string of the group state.
 */
void Group::setState(State* s) {
    groupState = s;
}


/**
 * Setter for the type field.
 * @param t A string of the group type.
 * Can be "LightGroup", "Room", "Luminaire" or "LightSource"
 */
void Group::setType(string t) {
    type = t;
}


/**
 * Setter for the class field.
 * @param c A string of the group class.
 */
void Group::setClass(string c) {
    groupClass = c;
}


// --------------------------------------
// Not so PRIVATE METHODS
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
