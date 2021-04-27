/**
 * This file contains the main framework or the game engine. The class manages the Render Window.
 */

#include "GameWindow.h"

using namespace sf;

RenderWindow GameWindow::window;

/**
 * Initialise Game window with desired in-game resolution
 * @TODO: Take the resolution as a constructor (command line) parameter
 */
void GameWindow::init() {
    window.create(VideoMode(1280, 720), "Namco PacMan");
}

/**
 * Tells us if the gamewindow is open and active
 * @return True if window exists, even if hidden
 */
bool GameWindow::isRunning() {
    return window.isOpen();
}

/**
 * Basic EventHandler for gameWindow
 */
void GameWindow::handleEvents() {
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type) {
            case Event::Closed:
                window.close();
                break;
        }
    }

}

/**
 * Renders and displaying the game-window
 */
void GameWindow::render() {
    window.clear(Color::White);
    window.display();
}
