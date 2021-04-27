//
// Created by prats on 27/4/21.
//

#ifndef PACMAN_2PLAYER_STATEMACHINE_H
#define PACMAN_2PLAYER_STATEMACHINE_H

#include <stack>
#include "SFML/Graphics.hpp"
#include "State.h"

using namespace std;

class StateMachine {
private:
    stack<State*> states;

public:
    void addState(State* state);
    void loop();
    void render(sf::RenderWindow* window);
    void keyPressed(int code);
    void keyReleased(int code);
};


#endif //PACMAN_2PLAYER_STATEMACHINE_H
