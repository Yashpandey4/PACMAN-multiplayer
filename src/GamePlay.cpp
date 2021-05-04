/**
 * First State in the game, demonstrates start of the gameplay
 */

#include "GamePlay.h"
#include "SFML/Graphics.hpp"

using namespace sf;

void GamePlay::init() {
    logger = new Logger("GamePlay");
    logger->log("Playing State Initialised");
}

void GamePlay::loop() {}

void GamePlay::render(RenderWindow *window) {
    CircleShape circle(200);
    circle.setFillColor(Color::Blue);
    window->draw(circle);
}

void GamePlay::keyPressed(int code) {
    logger->log("Key Pressed: "+to_string(code));
}

void GamePlay::keyReleased(int code) {}