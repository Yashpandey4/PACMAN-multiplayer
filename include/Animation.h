//
// Created by prats on 30/4/21.
//

#ifndef PACMAN_2PLAYER_ANIMATION_H
#define PACMAN_2PLAYER_ANIMATION_H

#include "SFML/Graphics.hpp"

class Animation {
private:
    sf::IntRect* boundaries;
    int frames;
    sf::Clock clock;
    int resetValue;

public:
    Animation(sf::IntRect* rect, int framesNumber);

    void changeFrame();

    sf::IntRect getBoundaries() const;
};


#endif //PACMAN_2PLAYER_ANIMATION_H
