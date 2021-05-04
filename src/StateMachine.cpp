/**
 * This file has a collection of objects which tell the game what to show in a specific moment
 */

#include "StateMachine.h"

/**
 * Add new states to the game state machine
 * @param state - game state to be added
 */
void StateMachine::addState(State *state) {
    states.push(state);
    states.top()->init();
}

/**
 * Loops wrt the latest state
 */
void StateMachine::loop() {
    states.top()->loop();
}

/**
 * Renders the latest state in the supplied window]
 * @param window
 */
void StateMachine::render(sf::RenderWindow *window) {
    states.top()->render(window);
}

/**
 * Handles key pressed wrt the latest state
 * @param code - key code pressed
 */
void StateMachine::keyPressed(int code) {
    states.top()->keyPressed(code);
}

/**
 * Handles key released wrt the latest state
 * @param code - key code released
 */
void StateMachine::keyReleased(int code) {
    states.top()->keyReleased(code);
}
