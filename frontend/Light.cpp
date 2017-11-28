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
Light::Light() {
    name = "";
    isActive = false; //on
    brightness = 0;   //bri
    hue = 0;          //hue
    sat = 0;          //sat
    schedule = 0;
    id = "";
}

// ! TODO: Add overloaded constructor for creating a Light with fields

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

// TODO: Should this be returning an integer? Perhaps look into a different way of implementing the schedules.
/**
 * Getter for the scheduled time for the Light to be turned on.
 * @return a schedule for when the Light should be turned on, an int.
 */
int Light::getSchedule() {
    return schedule;
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
 * @param h An integer representation of the light's sat.
 */
void Light::setSat(int s) {
    sat = s;
}

// TODO: Determine how to represent the schedule properly. See "getSchedule()"

/**
 * Setter for the schedule field.
 * @param sched An integer representation of when the Light should turn on.
 */
void Light::setSchedule(int sched) {
    schedule = sched;
}

/**
 * Setter for the ID field.
 * @param id An integer representation of Light ID.
 */
void Light::setID(string i) {
    id = i;
}

// --------------------------------------
// PRIVATE METHODS
// --------------------------------------


/**
 * WILL BE REMOVED: Method that converts a given, well-formed string representing a colour's hexcode into the associated colour space coordinates to be used with the Hue API.
 * @param col A well-formed hexcode string that represents a colour
 */
void Light::convertHexcodeToCoords(string col) {
    // TODO: Write method to convert a hexcode into valid colour coordinates for the Hue API to process if needed
    // TODO: Return Type?
}
