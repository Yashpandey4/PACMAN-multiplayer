//
// Created by prats on 27/4/21.
//

#ifndef PACMAN_2PLAYER_GAMEPLAY_H
#define PACMAN_2PLAYER_GAMEPLAY_H

#include "State.h"
#include "Logger.h"
#include "Maze.h"
#include "PacMan.h"
#include "Character.h"

class GamePlay : public State {
private:
    Logger* logger;
    Maze* maze;
    PacMan* pacMan;
    Character* redGhost;
    Character* pinkGhost;
    Character* blueGhost;
    Character* orangeGhost;

    bool isPacManMovementAllowed();

public:
    void init();
    void loop();
    void render(sf::RenderWindow* window);
    void keyPressed(int code);
    void keyReleased(int code);
};


#endif //PACMAN_2PLAYER_GAMEPLAY_H
