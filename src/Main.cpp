/**
 * Entry point for the game
 */

#include "GameWindow.h"

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
