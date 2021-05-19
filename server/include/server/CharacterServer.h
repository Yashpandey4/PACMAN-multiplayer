//
// Created by prats on 28/4/21.
//

#ifndef PACMAN_2PLAYER_CHARACTER_H
#define PACMAN_2PLAYER_CHARACTER_H

//#include <SFML\Network.hpp>
class CharacterServer {
protected:
    

    

public:
    CharacterServer(int cellPositionX, int cellPositionY);
    
    float screenPositionX;

    float screenPositionY;

    float getScreenPositionX() const;

    float getScreenPositionY() const;

    int getCellX() const;

    int getCellY() const;

    void move(float x, float y);

    void teleport(int x, int y);
    
    int cellX;

    int cellY;
};

#endif //PACMAN_2PLAYER_CHARACTER_H
