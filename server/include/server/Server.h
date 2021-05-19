//
// Created by prats on 27/4/21.
//

#ifndef PACMAN_2PLAYER_GAMEPLAY_H
#define PACMAN_2PLAYER_GAMEPLAY_H

#include "StateServer.h"
#include "MazeServer.h"
#include "PacManServer.h"
#include "GhostServer.h"
#include "CharacterServer.h"
#include "networkServer.h"
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <array>
#include <queue>
struct ClientEndPoint {
    sf::Time lastHeard;
    sf::IpAddress address;
    Port_t port;
};

struct sprites{
    PacManServer* pacMan;
    GhostServer* redGhost;
    GhostServer* pinkGhost;
    GhostServer* blueGhost;
    GhostServer* orangeGhost;
    MazeServer* maze;
    int score = 0;
};

struct ClientInput {
    int32_t up;
    int32_t down;
    int32_t right;
    int32_t left;
};
//
class Server: public StateServer{
private:
    int cur_id;
    int receiveData();
    void sendState();
    void sendTo(sf::Packet &packet, Client_t client);
    int emptySlot();

    void handleConnect(const sf::IpAddress &address, Port_t port);
    void handleInput(sf::Packet &packet);
    void sendResult();
    std::array<sprites, 2> m_peers;

    template <typename T>
    ClientEndPoint &getClientEndPoint(T slot);

    sf::UdpSocket m_socket;
    sf::Clock m_clock;
    unsigned m_connectedClients = 0;
    std::array<ClientEndPoint, 2> m_clientEndPoints;
    std::array<ClientInput, 2> m_clientInputs;
    std::array<uint8_t, 2> m_connects;

    int waitTime;
    
    void move(PacManServer *pacMan, float x, float y);

    bool isPacManMovementAllowed();

    void handleGhostMovement(GhostServer* ghost);

    bool isGhostMovementAllowed(GhostServer* ghost);

    float calculateGhostDistance(GhostServer* ghost, int x, int y);

    void teleportTunnels(CharacterServer* character);

    void handleGhostFrightening(GhostServer* ghost);
    
    

public:

    void init();

    void loop();

    void removePellets();

    void setChaseBehaviour();
};

template <typename T>
ClientEndPoint &Server::getClientEndPoint(T slot)
{
    return m_clientEndPoints[static_cast<size_t>(slot)];
}

#endif //PACMAN_2PLAYER_GAMEPLAY_H
