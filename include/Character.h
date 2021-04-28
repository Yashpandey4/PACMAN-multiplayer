//
// Created by prats on 28/4/21.
//

#ifndef PACMAN_2PLAYER_CHARACTER_H
#define PACMAN_2PLAYER_CHARACTER_H


class Character {
private:
    float screenPositionX;
public:
    float getScreenPositionX() const;

    float getScreenPositionY() const;

    int getCellX() const;

    int getCellY() const;

private:
    float screenPositionY;
    int cellX;
    int cellY;

public:
    Character(int cellPositionX, int cellPositionY);

};

#endif //PACMAN_2PLAYER_CHARACTER_H
