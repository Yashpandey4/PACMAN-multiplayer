/**
 * This file contains the main framework or the game engine. The class manages the Render Window.
 */

#include <StateMachine.h>
#include "GameWindow.h"
#include "GamePlay.h"
#include "LoadSprites.h"

using namespace sf;

RenderWindow GameWindow::window;
Logger GameWindow::logger("GameWindow");
StateMachine GameWindow::stateMachine;

/**
 * Initialise Game window with desired in-game resolution
 * @TODO: Take the resolution as a constructor (command line) parameter
 */
void GameWindow::init() {
    logger.log("Game Started");
    LoadSprites::load();
    window.create(VideoMode(448, 596), "Namco PacMan");
    stateMachine.addState(new GamePlay);
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
                logger.log("Game Ended. Exiting.");
                window.close();
                break;
            case Event::KeyPressed:
                stateMachine.keyPressed(event.key.code);
                break;
            case Event::KeyReleased:
                stateMachine.keyReleased(event.key.code);
                break;
        }
    }
    stateMachine.loop();
}

/**
 * Renders and displaying the game-window
 */
void GameWindow::render() {
    window.clear(Color::Black);
    stateMachine.render(& window);
    window.display();
}
