/**
 * @file Action.cpp
 * Action Class.
 *
 * @brief Action Class
 * @author Anthony Tran (atran94)
 * @date November 28, 2017
 */

#include "Action.h"

using namespace std;

// --------------------------------------
// CONSTRUCTORS
// --------------------------------------


/**
 * Default constructor for Action class. Initializes all fields to have no values.
 */
Action::Action(): isActive(false), brightness(0), hue(0), sat(0) {
    // isActive = false; //on
    // brightness = 0;   //bri
    // hue = 0;          //hue
    // sat = 0;          //sat
}

/**
 * Overload constructor for Action class.
 * @param i for isActive.
 * @param b for brightness.
 * @param h for hue.
 * @param s for sat.
 */
Action::Action(bool i, int b, int h, int s): isActive(i), brightness(b), hue(h), sat(s) {
    // isActive = false; //on
    // brightness = 0;   //bri
    // hue = 0;          //hue
    // sat = 0;          //sat
}

// --------------------------------------
// PUBLIC METHODS
// --------------------------------------


/**
 * Getter for the isActive field, determining whether the light is on or off (True for "On", False for "Off".
 * @return the current state of the Action as a boolean.
 */
bool Action::getIsActive() {
    return isActive;
}


/**
 * Getter for the brightness level of the Action object.
 * @return the brightness level, an int.
 */
int Action::getBrightness() {
    return brightness;
}


/**
 * Getter for the hue of the Action.
 * @return the hue of the Action as an int.
 */
int Action::getHue() {
    return hue;
}

/**
 * Getter for the sat of the Action.
 * @return the sat of the Action as an int.
 */
int Action::getSat() {
    return sat;
}

/**
 * Setter for the name field.
 * @param n A string for the name of the Action object.
 */
void Action::setName(string n) {
    name = n;
}


/**
 * Setter for the isActive field.
 * @param onOrOff A boolean representation of whether the Light should be on (true) or off (false).
 */
void Action::setIsActive(bool onOrOff) {
    isActive = onOrOff;
}


/**
 * Setter for the brightness field.
 * @param b An integer representation of the brightness level.
 */
void Action::setBrightness(int b) {
    brightness = b;
}


/**
 * Setter for the hue field.
 * @param h An integer representation of the Action's hue.
 */
void Action::setHue(int h) {
    hue = h;
}

/**
 * Setter for the sat field.
 * @param h An integer representation of the Action's sat.
 */
void Action::setSat(int s) {
    sat = s;
}
