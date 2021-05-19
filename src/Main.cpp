/**
 * Entry point for the game
 */

#include "GameWindow.h"

/**
 * Serves as the entry point of the game
 * @return return 0 in the main function means that the program executed successfully. return 1 in the main function means that the program does not execute successfully and there is some error.
 */
int main()
{
    GameWindow::init();

    while(GameWindow::isRunning())
    {
        GameWindow::handleEvents();
        GameWindow::render();
    }

    // For windows Systems, uncomment the next line to avoid exiting during gameplay
    // system("pause");

    return 0;
}
