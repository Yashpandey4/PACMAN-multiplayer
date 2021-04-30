//
// Created by prats on 30/4/21.
//

#ifndef PACMAN_2PLAYER_ENTITY_H
#define PACMAN_2PLAYER_ENTITY_H

enum Entity {
    // PacMan Movements
    PAC_MAN = 0,
    PAC_MAN_DOWN = 1,
    PAC_MAN_LEFT = 2,
    PAC_MAN_RIGHT = 3,

    // Blinky Movements
    RED_GHOST = 4,
    RED_GHOST_DOWN = 5,
    RED_GHOST_LEFT = 6,
    RED_GHOST_RIGHT = 7,

    // Pinky Movements
    PINK_GHOST = 8,
    PINK_GHOST_DOWN = 9,
    PINK_GHOST_LEFT = 10,
    PINK_GHOST_RIGHT = 11,

    // Inky Movements
    BLUE_GHOST = 12,
    BLUE_GHOST_DOWN = 13,
    BLUE_GHOST_LEFT = 14,
    BLUE_GHOST_RIGHT = 15,

    // Clyde Movements
    ORANGE_GHOST = 16,
    ORANGE_GHOST_DOWN = 17,
    ORANGE_GHOST_LEFT = 18,
    ORANGE_GHOST_RIGHT = 19,

    // Misc
    FRIGHTENED_GHOST = 20,
    DEAD_PAC_MAN = 21
};

#endif //PACMAN_2PLAYER_ENTITY_H
