/**
 * @file Light.cpp
 * Light Class.
 *
 * @brief Light Class
 * @author Jacob Fryer (jfryer6)
 * @date November 05, 2017
 */

#include "Light.h"

using namespace std;

// --------------------------------------
// CONSTRUCTORS
// --------------------------------------


/**
 * Default constructor for Light class. Initializes all fields to have no values.
 */
Light::Light(): name(""), isActive(false),  brightness(0), hue(0), sat(0), id("") {
    // name = "";
    // isActive = false; //on
    // brightness = 0;   //bri
    // hue = 0;          //hue
    // sat = 0;          //sat
    // id = "";
}

/**
 * Overload constructor for Light class.
 * @param n for name.
 * @param i for isActive.
 * @param b for brightness.
 * @param h for hue.
 * @param s for sat.
 * @param id for id.
 */
Light::Light(string n, bool i, int b, int h, int s, string id): name(n), isActive(i),  brightness(b), hue(h), sat(s), id(id) {
    // name = "";
    // isActive = false; //on
    // brightness = 0;   //bri
    // hue = 0;          //hue
    // sat = 0;          //sat
    // id = "";
}

// --------------------------------------
// PUBLIC METHODS
// --------------------------------------


/**
 * Getter for the name of the Light object.
 * @return the name field, a string.
 */
string Light::getName() {
    return name;
}


/**
 * Getter for the isActive field, determining whether the light is on or off (True for "On", False for "Off".
 * @return the current state of the Light as a boolean.
 */
bool Light::getIsActive() {
    return isActive;
}


/**
 * Getter for the brightness level of the Light object.
 * @return the brightness level, an int.
 */
int Light::getBrightness() {
    return brightness;
}


/**
 * Getter for the hue of the Light.
 * @return the hue of the Light as an int.
 */
int Light::getHue() {
    return hue;
}


/**
 * Getter for the sat of the Light.
 * @return the sat of the Light as an int.
 */
int Light::getSat() {
    return sat;
}

/**
 * Getter for the ID field.
 * @return Light ID in string.
 */
string Light::getID() {
    return id;
}


/**
 * Setter for the name field.
 * @param n A string for the name of the Light object.
 */
void Light::setName(string n) {
    name = n;
}


/**
 * Setter for the isActive field.
 * @param onOrOff A boolean representation of whether the Light should be on (true) or off (false).
 */
void Light::setIsActive(bool onOrOff) {
    isActive = onOrOff;
}


/**
 * Setter for the brightness field.
 * @param b An integer representation of the brightness level.
 */
void Light::setBrightness(int b) {
    brightness = b;
}


/**
 * Setter for the hue field.
 * @param h An integer representation of the light's hue.
 */
void Light::setHue(int h) {
    hue = h;
}

/**
 * Setter for the sat field.
 * @param s An integer representation of the light's sat.
 */
void Light::setSat(int s) {
    sat = s;
}

/**
 * Setter for the ID field.
 * @param i An integer representation of Light ID.
 */
void Light::setID(string i) {
    id = i;
}

