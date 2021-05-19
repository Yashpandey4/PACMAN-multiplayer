/**
 * Entry point for the game
 */
#include <iostream>
#include "client/GameWindow.h"
#include "client/Client.h"
//int run();
/**
 * Serves as the entry point of the game
 * @return return 0 in the main function means that the program executed successfully. return 1 in the main function means that the program does not execute successfully and there is some error.
 */
int Client::run()
{
    GameWindow *window1 = new GameWindow();
    window1->init(0);

    while(window1->isRunning())
    {
        window1->render(0);
        window1->handleEvents(0);
   }

    // For windows Systems, uncomment the next line to avoid exiting during gameplay
    // system("pause");

    return 0;
}
