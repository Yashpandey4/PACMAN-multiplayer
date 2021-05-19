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
#include "AudioManager.h"
#include "network.h"
#include <SFML/Network.hpp>

struct sprites{
    PacMan* pacMan;
    Ghost* redGhost;
    Ghost* pinkGhost;
    Ghost* blueGhost;
    Ghost* orangeGhost;
    Maze* maze;
    int score = 0;
    bool win = false;
};

struct ClientInput {
    int32_t up;
    int32_t down;
    int32_t left;
    int32_t right;
};

class GamePlay : public State {
private:
    Logger* logger;
    
    AudioManager* audioManager;
    
    unsigned m_connectedClients = 0;
    std::array<sprites, 2> m_peers;
    std::array<bool, 2> m_connects;
    
    sf::UdpSocket m_socket;
    
    sf::IpAddress m_remoteAddress;
    Port_t m_remotePort;
    
    Client_t m_clientId;
    bool m_isConnected = false;

    int waitTime;
    bool gameOver = false;
    int time = 0;
    //bool isPacManMovementAllowed();

    //void handleGhostMovement(Ghost* ghost);

    //bool isGhostMovementAllowed(Ghost* ghost);

    //float calculateGhostDistance(Ghost* ghost, int x, int y);

    //void teleportTunnels(Character* character);

    //void handleGhostFrightening(Ghost* ghost);
    
    void connect(sf::Packet &packet);
    
    void handlePacManPosition(sf::Packet &packet);
    
    void handleRedGhostPosition(sf::Packet &packet);
    
    void handlePinkGhostPosition(sf::Packet &packet);
    
    void handleBlueGhostPosition(sf::Packet &packet);
    
    void handleOrangeGhostPosition(sf::Packet &packet);
    
    void handleMaze(sf::Packet &packet);
    
    void handleResult(sf::Packet &packet);
    
    void handleScores(sf::Packet &packet);
    
    std::array<ClientInput, 2> m_clientInputs;
    
    void send(sf::Packet &packet);

public:
    void init();

    void loop();

    void render(sf::RenderWindow* window, unsigned id);

    void keyPressed(int code);

    void keyReleased(int code);

    //void removePellets();

    //void setChaseBehaviour();

    void stopSirenAndLoop(Sounds sound, bool isLoop, int volume);
};


#endif //PACMAN_2PLAYER_GAMEPLAY_H
