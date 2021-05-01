//
// Created by prats on 1/5/21.
//

#ifndef PACMAN_2PLAYER_AUDIOMANAGER_H
#define PACMAN_2PLAYER_AUDIOMANAGER_H

#include "Audio.h"
#include "SFML/Audio.hpp"

class AudioManager {
public:
    AudioManager();

    void PlaySound(Sounds soundType, bool loop, int volume);

    void StopSound(Sounds soundType = Sounds::None);

    bool IsPlayingAudio(Sounds soundType);

private:

    sf::SoundBuffer gameStartBuffer;
    sf::Sound gameStartSound;

    sf::SoundBuffer munchSoundBuffer;
    sf::Sound munchSound;

    sf::SoundBuffer powerSnackBuffer;
    sf::Sound powerSnackSound;

    sf::SoundBuffer eatGhostBuffer;
    sf::Sound eatGhostSound;

    sf::SoundBuffer deathBuffer;
    sf::Sound deathSound;

    sf::SoundBuffer sirenBuffer;
    sf::Sound sirenSound;

    sf::SoundBuffer retreatingBuffer;
    sf::Sound retreatingSound;
};


#endif //PACMAN_2PLAYER_AUDIOMANAGER_H
