//
// Created by prats on 28/4/21.
//

#ifndef PACMAN_2PLAYER_CHARACTER_H
#define PACMAN_2PLAYER_CHARACTER_H


class Character {
protected:
    float screenPositionX;

    float screenPositionY;

    int cellX;

    int cellY;

public:
    Character(int cellPositionX, int cellPositionY);

    float getScreenPositionX() const;

    float getScreenPositionY() const;

    int getCellX() const;

    int getCellY() const;

    void move(float x, float y);
};

#endif //PACMAN_2PLAYER_CHARACTER_H
