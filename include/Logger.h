#ifndef PACMAN_2PLAYER_LOGGER_H
#define PACMAN_2PLAYER_LOGGER_H

#include <string>
using namespace std;

class Logger
{
private:
    string location;

public:
    Logger(string loc);
    void log(string msg);
};

#endif //PACMAN_2PLAYER_LOGGER_H
