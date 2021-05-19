//
// Created by prats on 1/5/21.
//

#ifndef PACMAN_2PLAYER_AUDIO_H
#define PACMAN_2PLAYER_AUDIO_H

#define AUDIO_GAME_START "assets/Sound/game_start.wav"
#define AUDIO_EAT_GHOST "assets/Sound/eat_ghost.wav"
#define AUDIO_DEATH_1 "assets/Sound/death_1.wav"
#define AUDIO_POWER_SNACK "assets/Sound/power_pellet.wav"
#define AUDIO_MUNCH "assets/Sound/munch.wav"
#define AUDIO_SIREN "assets/Sound/siren_1.wav"
#define AUDIO_RETREATING "assets/Sound/retreating.wav"
#define AUDIO_VICTORY "assets/Sound/win.wav"
#define AUDIO_DEFEAT "assets/Sound/defeat.wav"

#define VOLUME 50
#define VOLUME_MUNCH 10
#define VOLUME_SIREN 60

enum class Sounds {
    None,
    PowerSnack,
    EatGhost,
    Death,
    Munch,
    GameStart,
    Siren,
    Retreating,
    Victory,
    Defeat
};

#endif //PACMAN_2PLAYER_AUDIO_H
