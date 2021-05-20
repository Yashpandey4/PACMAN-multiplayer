//
// Created by prats on 27/4/21.
//

#ifndef PACMAN_2PLAYER_GAMEPLAY_H
#define PACMAN_2PLAYER_GAMEPLAY_H

#include "State.h"
#include "Logger.h"
#include "Maze.h"
#include "PacMan.h"
#include "Ghost.h"
#include "Character.h"

class GamePlay : public State {
private:
    Logger* logger;
    Maze* maze;
    PacMan* pacMan;
    Ghost* redGhost;
    Ghost* pinkGhost;
    Ghost* blueGhost;
    Ghost* orangeGhost;

    int waitTime;

    bool isPacManMovementAllowed();

    void handleGhostMovement(Ghost* ghost);

    bool isGhostMovementAllowed(Ghost* ghost);

    float calculateGhostDistance(Ghost* ghost, int x, int y);

    void teleportTunnels(Character* character);

    void handleGhostFrightening(Ghost* ghost);

public:
    void init();

    void loop();

    void render(sf::RenderWindow* window);

    void keyPressed(int code);

    void keyReleased(int code);

    void setChaseBehaviour();
};


#endif //PACMAN_2PLAYER_GAMEPLAY_H
