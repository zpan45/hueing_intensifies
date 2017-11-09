/*
Light.cpp

Light.cpp [...]

@author - Jacob Fryer (jfryer6)
@date - November 05, 2017
*/

#include "Light.h"

using namespace std;

// --------------------------------------
// CONSTRUCTORS
// --------------------------------------

/*
Light()

Default constructor for Light class. Initializes all fields to have no values.
Takes no parameters.
*/
Light::Light() {
    name = "";
    isActive = false;
    brightness = 0;
    colour = "#FFFFFF";
    schedule = 0;
}

// ! TODO: Add overloaded constructor for creating a Light with fields

// --------------------------------------
// PUBLIC METHODS
// --------------------------------------

/*
getName()

Getter for the name of the Light object.

Takes no parameters.

Returns the name field, a string.
*/
string Light::getName() {
    return name;
}

/*
getIsActive()

Getter for the isActive field, determining whether the light is on or off (True for "On", False for "Off".

Takes no parameters.

Returns the current state of the Light as a boolean.
*/
bool Light::getIsActive() {
    return isActive;
}

/*
getBrightness()

Getter for the brightness level of the Light object.

Takes no parameters.

Returns the brightness level, an int.
*/
int Light::getBrightness() {
    return brightness;
}

/*
getColour()

Getter for the colour of the Light.

Takes no parameters.

Returns the colour of the Light (in hexcode form) as a string.
*/
string Light::getColour() {
    return colour;
}

/*
! TODO: Should this be returning an integer? Perhaps look into a different way of implementing the schedules.

getSchedule()

Getter for the scheduled time for the Light to be turned on.

Takes no parameters.

Returns a schedule for when the Light should be turned on, an int.
*/
int Light::getSchedule() {
    return schedule;
}

/*
setName()

Setter for the name field.

Parameters:
- string n: A string for the name of the Light object.
*/
void Light::setName(string n) {
    name = n;
}

/*
setIsActive()

Setter for the isActive field.

Parameters:
- bool onOrOff: A boolean representation of whether the Light should be on (true) or off (false).
*/
void Light::setIsActive(bool onOrOff) {
    isActive = onOrOff;
}

/*
setBrightness()

Setter for the brightness field.

Parameters:
- int b: An integer representation of the brightness level.
*/
void Light::setBrightness(int b) {
    brightness = b;
}

/*
setColour()

Setter for the colour field.

Parameters:
- string hexcode: A well-formed hexcode string that represents the colour that the Light should be emitting.
*/
void Light::setColour(string hexcode) {
    colour = hexcode;
}

/*
! TODO: Determine how to represent the schedule properly. See "getSchedule()"

setSchedule()

Setter for the schedule field.

Parameters:
- int sched: An integer representation of when the Light should turn on
*/
void Light::setSchedule(int sched) {
    schedule = sched;
}

// --------------------------------------
// PRIVATE METHODS
// --------------------------------------

/*
convertHexcodeToCoords()

Method that converts a given, well-formed string representing a colour's hexcode into the associated colour space coordinates to be used with the Hue API.

Returns ??? (** NOTE: Return type???)
*/
void Light::convertHexcodeToCoords(string col) {
    // ! TODO: Write method to convert a hexcode into valid colour coordinates for the Hue API to process if needed
}
