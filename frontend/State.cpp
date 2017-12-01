/**
 * @class State
 * State Class.
 *
 * @brief State Class
 * @author Jacob Fryer (jfryer6), Anthony Tran (atran94), Omar Abdel-Qader (oabdelqa), Usant Kajendirarajah (ukajendi), Zhengyang Pan (zpan45)
 * @date November 28, 2017
 */

#include "State.h"

using namespace std;

// --------------------------------------
// CONSTRUCTORS
// --------------------------------------


/**
 * Default constructor for State class. Initializes all fields to be false.
 * any_on "false" if all lamps are on, "true" if at least one lamp is on
 * all_on "false" if all lamps ore off, "true" if all amps are on
 */
State::State(): any_on(false), all_on(false) {
}

/**
 * Overload constructor for State class.
 * @param any for any_on.
 * @param all for all_on.
 */
State::State(bool any, bool all): any_on(any), all_on(all) {
}


// --------------------------------------
// PUBLIC METHODS
// --------------------------------------


/**
 * Getter for the any_on field
 * @return any_on
 */
bool State::getAny_On() {
    return any_on;
}


/**
 * Getter for the all_on field
 * @return all_on
 */
bool State::getAll_On() {
    return any_on;
}


/**
 * Setter for the any_on field.
 * @param x should be "true" or "false"
 */
void State::setAny_On(bool x) {
    any_on = x;
}


/**
 * Setter for the aall_on field.
 * @param x should be "true" or "false"
 */
void State::setAll_On(bool x) {
    ally_on = x;
}
