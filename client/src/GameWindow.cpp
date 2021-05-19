/**
 * This file contains the main framework or the game engine. The class manages the Render Window.
 */

#include "client/StateMachine.h"
#include "client/GameWindow.h"
#include "client/GamePlay.h"
#include "client/LoadSprites.h"

using namespace sf;

RenderWindow GameWindow::window;
Logger GameWindow::logger("GameWindow");
StateMachine GameWindow::stateMachine;

/**
 * Initialise Game window with desired in-game resolution
 * @TODO: Take the resolution as a constructor (command line) parameter
 */
void GameWindow::init(int i) {
    logger.log("Game Started");
    LoadSprites::load();
    stateMachine.addState(new GamePlay);
    window.create(VideoMode(966, 550), "Namco PacMan");
    
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
void GameWindow::handleEvents(int i) {
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
void GameWindow::render(unsigned id) {
    window.clear(Color::Black);
    stateMachine.render(& window, id);
    window.display();
}
