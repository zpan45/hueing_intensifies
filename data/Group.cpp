/*
Group.cpp

Group.cpp [...]

@author - Jacob Fryer (jfryer6)
@date - November 04, 2017
*/

#include "Group.h"

using namespace std;

// --------------------------------------
// CONSTRUCTORS
// --------------------------------------

/*
Group()

Default constructor for Group class. Initializes all fields to have no values.
Takes no parameters.
*/
Group() {
    name = "";
}

// ! TODO: Add overloaded constructor for creating a Group with fields

// --------------------------------------
// PUBLIC METHODS
// --------------------------------------

/*
getName()

Getter for the name of the Group.

Takes no parameters.

Returns name as a string.
*/
string getName() {
    return name;
}

/*
getLight()

Accessor method for a specific Light in the Group. Throws an out_of_range if attempting to access an element outside of the vector's bounds.

Parameters:
- int element: The integer position of the desired Light object in the lights vector.

Returns the desired Light object.
*/
Light getLight(int element) {
    try {
        return lights.at(element);
    }
    catch(const out_of_range& oor) {
        cerr << element << " is out of range for this Group" << endl;
    }
}

// --------------------------------------
// PRIVATE METHODS
// --------------------------------------

/*
addLight()

Method that adds a Light to the Group by adding the Light to the lights vector.

Parameters:
- Light l: A Light object to be added to the Group.
*/
void addLight(Light l) {
    lights.push_back(l);
}

/*
removeLight()

Method to remove a Light at the given position from the Group.

Parameters:
- int element: The integer position of the desired Light object in the lights vector.

Returns whether the removal was successful as a boolean.
*/
bool removeLight(int element) {
    // if the target Light is outside of the bounds of the lights vector, return false
    if( (element > lights.size() ) || (element < 0) ) {
        return false;
    }
    // else, remove the Light at the specified location
    else {
        lights.erase(element);
        return true;
    }
}
