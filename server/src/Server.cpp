/**
 * First State in the game, demonstrates start of the game play
 */

#include <server/PacManServer.h>
#include <server/GhostServer.h>
#include <server/Server.h>
#include <server/DirectionServer.h>
#include <server/MazeServer.h>
#include <iostream>
#include <bits/stdc++.h>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include<unistd.h>
#include <SFML/Network.hpp>
#include <bitset>
#include <thread>

#include <cmath>
#include <server/EntityServer.h>

using namespace sf;
using namespace std;
int maxClients = 2;
int startTime = 0;
int elapsedTime = 0;
/**
 * Initialises the play state of the game
 */
void Server::init() {
    m_socket.setBlocking(false);
    m_socket.bind(54321);
    m_connects.fill(false);
    std::cout << "Server IP Address: " << sf::IpAddress::getPublicAddress().toString() << endl;
    MazeServer* temp_maze = new MazeServer();
    for(int k = 0; k < maxClients; k++){
        int i;
        int threshold = 0;
        m_peers[k].maze = new MazeServer();
        for(int X = 0; X < 30; X++){
            for(int Y = 0; Y < 34; Y++){
                m_peers[k].maze->cells[X][Y] = temp_maze->cells[X][Y];
            }
        }
        do{
            i = rand()%25 + 1;
            threshold++;
        }
        while(!temp_maze->isCellBlockingCharacter(i, 29) && threshold < 50);
        if(threshold == 50){
            do{
                i = rand()%25 + 1;
                threshold++;
            }
            while(!temp_maze->isCellBlockingCharacter(i, 4) && threshold < 100);
            if(threshold == 100){
                m_peers[k].pacMan = new PacManServer(10, 30);
            }
            else{
                m_peers[k].pacMan = new PacManServer(i, 3);
            }
        }
        else{
            m_peers[k].pacMan = new PacManServer(i, 30);
        }
        m_peers[k].pacMan->queueDirection(Direction::RIGHT);
        m_peers[k].redGhost = new GhostServer(14,14,1, 3);
        m_peers[k].pinkGhost = new GhostServer(14,18,26,3);
        m_peers[k].blueGhost = new GhostServer(12,18,1,30);
        m_peers[k].orangeGhost = new GhostServer(16,18,26,30);
        m_peers[k].redGhost->teleport(12, 15);
        waitTime = 0;
    }
    
}

/**
 * Specifies actions which keep the play state of the game running in a loop
 */
void Server::loop() {
    int dead[2] = {0, 0};
    auto t1 = chrono::high_resolution_clock::now();
    while(true){
        if(rand()%3 != 0){
            continue;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(100));
        int x;
        //if(rand()%2 == 0){
            x = receiveData();
        //}
        //else{
            //sendState();
           // continue;
        //}
        if(m_connectedClients == 0){
            continue;
        }
        if(x == 2 || m_connectedClients == 1){
            sendState();
            continue;
        }
        if(startTime == 0){
            t1 = chrono::high_resolution_clock::now();
            startTime++;
        }
        for(int k = 0; k < maxClients; k++){
            cur_id = k;
            if(isPacManMovementAllowed() && !m_peers[cur_id].pacMan->isPacmanDead()){
                m_peers[cur_id].pacMan->movePacman();
            }
            else{
                m_peers[cur_id].pacMan->stopPacman();
            }

            if (m_peers[cur_id].maze->isMazeIntersection(m_peers[cur_id].pacMan->getCellX(), m_peers[cur_id].pacMan->getCellY())){
                m_peers[cur_id].pacMan->stopPacman();
            }

            removePellets();
            m_peers[cur_id].redGhost->setScatterGhosts(false);
            m_peers[cur_id].pinkGhost->setScatterGhosts(false);
            m_peers[cur_id].blueGhost->setScatterGhosts(false);
            m_peers[cur_id].orangeGhost->setScatterGhosts(false);
            setChaseBehaviour();

            handleGhostMovement(m_peers[cur_id].redGhost);
            handleGhostMovement(m_peers[cur_id].pinkGhost);
            handleGhostMovement(m_peers[cur_id].blueGhost);
            handleGhostMovement(m_peers[cur_id].orangeGhost);
            if(m_peers[cur_id].pacMan->getPelletsEaten() == 5)
                m_peers[cur_id].pinkGhost->teleport(13, 14);
            if(m_peers[cur_id].pacMan->getPelletsEaten() == 50)
                m_peers[cur_id].blueGhost->teleport(13, 14);
            if(m_peers[cur_id].pacMan->getPelletsEaten() == 100)
                m_peers[cur_id].orangeGhost->teleport(13, 14);
            teleportTunnels(m_peers[cur_id].pacMan);
            teleportTunnels(m_peers[cur_id].redGhost);
            teleportTunnels(m_peers[cur_id].pinkGhost);
            teleportTunnels(m_peers[cur_id].blueGhost);
            teleportTunnels(m_peers[cur_id].orangeGhost);
            handleGhostFrightening(m_peers[cur_id].redGhost);
            handleGhostFrightening(m_peers[cur_id].pinkGhost);
            handleGhostFrightening(m_peers[cur_id].blueGhost);
            handleGhostFrightening(m_peers[cur_id].orangeGhost);
            if (m_peers[cur_id].pacMan->getPelletsEaten() == 240) {
                m_peers[cur_id].redGhost->teleport(13, 14);
                m_peers[cur_id].pinkGhost->teleport(13, 14);
                m_peers[cur_id].blueGhost->teleport(13, 14);
                m_peers[cur_id].orangeGhost->teleport(13, 14);
                waitTime++;
            }

            if (m_peers[cur_id].pacMan->isPacmanDead() && dead[k] < 5){
                dead[k]++;
                waitTime++;
            }

            if (m_peers[cur_id].pacMan->isPacmanDead() && dead[k] == 5) {
                m_peers[cur_id].score = m_peers[cur_id].score - 100;
                if (m_peers[cur_id].redGhost->isGhostOutOfCage())
                    m_peers[cur_id].redGhost->teleport(13, 14);
                if (m_peers[cur_id].pinkGhost->isGhostOutOfCage())
                    m_peers[cur_id].pinkGhost->teleport(13,14);
                if (m_peers[cur_id].blueGhost->isGhostOutOfCage())
                    m_peers[cur_id].blueGhost->teleport(13,14);
                if (m_peers[cur_id].orangeGhost->isGhostOutOfCage())
                    m_peers[cur_id].orangeGhost->teleport(13,14);
                int i;
                int threshold = 0;
                do{
                    i = rand()%25 + 1;
                    threshold++;
                }
                while(!m_peers[cur_id].maze->isCellBlockingCharacter(i, 29) && threshold < 50);
                if(threshold == 50){
                    do{
                        i = rand()%25 + 1;
                        threshold++;
                    }
                    while(!m_peers[cur_id].maze->isCellBlockingCharacter(i, 4) && threshold < 100);
                    if(threshold == 100){
                        m_peers[k].pacMan = new PacManServer(10, 30);
                    }
                    else{
                        m_peers[k].pacMan = new PacManServer(i, 3);
                    }
                }
                else{
                    m_peers[k].pacMan = new PacManServer(i, 30);
                }
                m_peers[k].pacMan->queueDirection(Direction::RIGHT);
                m_peers[cur_id].pacMan->setPacmanDead(false);
                waitTime = 0;
                dead[k] = 0;
            }
            sendState();
            
        } 
        auto t2 = chrono::high_resolution_clock::now();
        if(chrono::duration_cast<chrono::seconds>( t2 - t1 ).count() > 30){
            for(int l = 0; l < 5000; l++){
                sendResult();
            }
            
            m_connects.fill(false);
            m_connectedClients = 0;
            init();
        }
        elapsedTime = chrono::duration_cast<chrono::seconds>( t2 - t1 ).count();
    }
}

int Server::receiveData(){
    sf::Packet packet;
    sf::IpAddress address;
    Port_t port;
    int flag = 0;
    while (m_socket.receive(packet, address, port) == sf::Socket::Done) {
        CommandsToServer command;
        packet >> command;
        switch (command) {
            case CommandsToServer::Connect:
                handleConnect(address, port);
                flag = 2;
                break;

            case CommandsToServer::Disconnect:
                break;

            case CommandsToServer::Input:
                handleInput(packet);
                flag = 1;
                break;
        }
    }
    return flag;
}

void Server::handleConnect(const sf::IpAddress &address, Port_t port)
{
    std::cout << "Client requesting connection\n"
              << "From IP: " << address.toString() << '\n'
              << "From port: " << (int)port << std::endl;

    if (m_connectedClients < maxClients) {
        std::cout << "Connection is able to be made!" << std::endl;

        auto slot = emptySlot();
        auto &client = getClientEndPoint(slot);
        client.address = address;
        client.port = port;

        sf::Packet packet;
        packet << CommandsToClient::ConnectRequestResult << (uint8_t)1
               << static_cast<Client_t>(slot);
        sendTo(packet, static_cast<Client_t>(slot));

        m_connects[slot] = true;
        m_connectedClients++;
    }
    std::cout << "--\n\n";
}

void Server::sendTo(sf::Packet &packet, Client_t clientId)
{
    auto &client = getClientEndPoint(clientId);
    m_socket.send(packet, client.address, client.port);
}

void Server::handleInput(sf::Packet &packet)
{
    Client_t x;
    Input_t input1;
    packet >> x >> input1;
    cur_id = static_cast<int>(x);
    auto &inputState = m_clientInputs[cur_id];
    inputState.up = input1 == Input::UP1;
    inputState.down = input1 == Input::DOWN1;
    inputState.right = input1 == Input::RIGHT1;
    auto &input = m_clientInputs[cur_id];
    if(input.up){
        m_peers[cur_id].pacMan->queueDirection(Direction::UP);
    }
    else if(input.down){
        m_peers[cur_id].pacMan->queueDirection(Direction::DOWN);
    }
    else if(input.right){
        m_peers[cur_id].pacMan->queueDirection(Direction::RIGHT);
    }
    else{
        m_peers[cur_id].pacMan->queueDirection(Direction::LEFT);
    }
    
}

void Server::sendResult(){
    sf::Packet resultPacket;
    resultPacket << CommandsToClient::Result;
    for (unsigned i = 0; i < maxClients; i++) {
        Client_t id = static_cast<Client_t>(i);
        resultPacket << id;
        if(m_peers[i].score > m_peers[(i + 1)%2].score){
            resultPacket << (float)1;
        }
        else{
            resultPacket << (float)0;
        }
    }
    for (unsigned i = 0; i < maxClients; i++) {
        if (m_connects[i]) {
            sendTo(resultPacket, static_cast<Client_t>(i));
        }
    }

}
void Server::sendState()
{
    sf::Packet packet;
    sf::Packet RedGhostPacket;
    sf::Packet PinkGhostPacket;
    sf::Packet BlueGhostPacket;
    sf::Packet OrangeGhostPacket;
    sf::Packet MazePacket;
    sf::Packet ScoresPacket;
    packet << CommandsToClient::PacManPosition;
    RedGhostPacket << CommandsToClient::RedGhostPosition;
    PinkGhostPacket << CommandsToClient::PinkGhostPosition;
    BlueGhostPacket << CommandsToClient::BlueGhostPosition;
    OrangeGhostPacket << CommandsToClient::OrangeGhostPosition;
    MazePacket << CommandsToClient::Maze;
    ScoresPacket << CommandsToClient::Scores;
    for (unsigned i = 0; i < maxClients; i++) {
        //if (m_connects[i]) {

            
            Client_t id = static_cast<Client_t>(i);

            // Scores Packet
            ScoresPacket << id << (float)m_peers[i].score << (float)elapsedTime;
            // Pacman Packet
            packet <<  id << (float)m_peers[i].pacMan->screenPositionX << (float)m_peers[i].pacMan->screenPositionY;
            if(m_peers[i].pacMan->isPacmanDead()){
                packet << (float)1;
            }
            else{
                packet << (float)0;
            }
            Input_t input = 0;
            if(m_peers[i].pacMan->directions.front() == Direction::UP){
                input = Input::UP1;
            }
            if(m_peers[i].pacMan->directions.front() == Direction::DOWN){
                input = Input::DOWN1;
            }
            if(m_peers[i].pacMan->directions.front() == Direction::LEFT){
                input = Input::LEFT1;
            }
            if(m_peers[i].pacMan->directions.front() == Direction::RIGHT){
                input = Input::RIGHT1;
            }
            packet << input;

            // RedGhost Packet
            Input_t input1 = 0;
            RedGhostPacket << id << (float)m_peers[i].redGhost->screenPositionX << (float)m_peers[i].redGhost->screenPositionY;
            if(m_peers[i].redGhost->isGhostFrightened()){
                RedGhostPacket << (float)1;
            }
            else{
                RedGhostPacket << (float)0;
            }
            if(m_peers[i].redGhost->isGhostOutOfCage()){
                RedGhostPacket << (float)1;
            }
            else{
                RedGhostPacket << (float)0;
            }
            if(m_peers[i].redGhost->getDirection() == Direction::UP){
                input1 |= Input::UP1;
            }
            if(m_peers[i].redGhost->getDirection() == Direction::DOWN){
                input1 |= Input::DOWN1;
            }
            if(m_peers[i].redGhost->getDirection() == Direction::LEFT){
                input1 |= Input::LEFT1;
            }
            if(m_peers[i].redGhost->getDirection() == Direction::RIGHT){
                input1 |= Input::RIGHT1;
            }
            RedGhostPacket << input1;

            // PinkGhost Packet
            Input_t input2 = 0;
            PinkGhostPacket << id << (float)m_peers[i].pinkGhost->screenPositionX << (float)m_peers[i].pinkGhost->screenPositionY;
            if(m_peers[i].pinkGhost->isGhostFrightened()){
                PinkGhostPacket << (float)1;
            }
            else{
                PinkGhostPacket << (float)0;
            }
            if(m_peers[i].pinkGhost->isGhostOutOfCage()){
                PinkGhostPacket << (float)1;
            }
            else{
                PinkGhostPacket << (float)0;
            }
            if(m_peers[i].pinkGhost->getDirection() == Direction::UP){
                input2 |= Input::UP1;
            }
            if(m_peers[i].pinkGhost->getDirection() == Direction::DOWN){
                input2 |= Input::DOWN1;
            }
            if(m_peers[i].pinkGhost->getDirection() == Direction::LEFT){
                input2 |= Input::LEFT1;
            }
            if(m_peers[i].pinkGhost->getDirection() == Direction::RIGHT){
                input2 |= Input::RIGHT1;
            }
            PinkGhostPacket << input2;

            // BlueGhost Packet
            Input_t input3 = 0;
            BlueGhostPacket << id << (float)m_peers[i].blueGhost->screenPositionX << (float)m_peers[i].blueGhost->screenPositionY;
            if(m_peers[i].blueGhost->isGhostFrightened()){
                BlueGhostPacket << (float)1;
            }
            else{
                BlueGhostPacket << (float)0;
            }
            if(m_peers[i].blueGhost->isGhostOutOfCage()){
                BlueGhostPacket << (float)1;
            }
            else{
                BlueGhostPacket << (float)0;
            }
            if(m_peers[i].blueGhost->getDirection() == Direction::UP){
                input3 |= Input::UP1;
            }
            if(m_peers[i].blueGhost->getDirection() == Direction::DOWN){
                input3 |= Input::DOWN1;
            }
            if(m_peers[i].blueGhost->getDirection() == Direction::LEFT){
                input3 |= Input::LEFT1;
            }
            if(m_peers[i].blueGhost->getDirection() == Direction::RIGHT){
                input3 |= Input::RIGHT1;
            }
            BlueGhostPacket << input3;

            // OrangeGhost Packet
            Input_t input4 = 0;
            OrangeGhostPacket << id << (float)m_peers[i].orangeGhost->screenPositionX << (float)m_peers[i].orangeGhost->screenPositionY;
            if(m_peers[i].orangeGhost->isGhostFrightened()){
                OrangeGhostPacket << (float)1;
            }
            else{
                OrangeGhostPacket << (float)0;
            }
            if(m_peers[i].orangeGhost->isGhostOutOfCage()){
                OrangeGhostPacket << (float)1;
            }
            else{
                OrangeGhostPacket << (float)0;
            }
            if(m_peers[i].orangeGhost->getDirection() == Direction::UP){
                input4 |= Input::UP1;
            }
            if(m_peers[i].orangeGhost->getDirection() == Direction::DOWN){
                input4 |= Input::DOWN1;
            }
            if(m_peers[i].orangeGhost->getDirection() == Direction::LEFT){
                input4 |= Input::LEFT1;
            }
            if(m_peers[i].orangeGhost->getDirection() == Direction::RIGHT){
                input4 |= Input::RIGHT1;
            }
            OrangeGhostPacket << input4;

            // Maze Packet
            MazePacket << id;
            for(int p = 0; p < 30; p++){
                for(int q = 0; q < 34; q++){
                    MazePacket << static_cast<float> (m_peers[i].maze->cells[p][q]);
                }
            }

        //}
    }

    for (unsigned i = 0; i < maxClients; i++) {
        if (m_connects[i]) {
            sendTo(packet, static_cast<Client_t>(i));
            sendTo(RedGhostPacket, static_cast<Client_t>(i));
            sendTo(PinkGhostPacket, static_cast<Client_t>(i));
            sendTo(BlueGhostPacket, static_cast<Client_t>(i));
            sendTo(OrangeGhostPacket, static_cast<Client_t>(i));
            sendTo(MazePacket, static_cast<Client_t>(i));
            sendTo(ScoresPacket, static_cast<Client_t>(i));
        }
    }
}

int Server::emptySlot()
{
    for (unsigned i = 0; i < maxClients; i++) {
        if (!m_connects[i]) {
            return i;
        }
    }
    return -1;
}
/**
 * In “Chase” mode, the ghosts are trying to find and capture Pac-Man.
 * Each of the four ghosts has a unique behaviour while chasing Pac-Man.
 * This function defines this behaviour
 */
void Server::setChaseBehaviour() {
    if (!m_peers[cur_id].pacMan->getDirections().empty()) {
        // Red Ghost Directly Chases Pacman
        // Blinky the red ghost is very aggressive in its approach while chasing Pac-Man and will follow Pac-Man once located.
        if (!m_peers[cur_id].redGhost->isScatterGhosts()) {
            m_peers[cur_id].redGhost->setGhostDestination(m_peers[cur_id].pacMan->getCellX(), m_peers[cur_id].pacMan->getCellY());
        }

        // Pink Ghost is off from PacMan's location by 4 cells (lurks around PacMan)
        // Pinky the pink ghost will attempt to ambush Pac-Man by trying to get in front of him and cut him off.
        if (!m_peers[cur_id].pinkGhost->isScatterGhosts()) {
            switch (m_peers[cur_id].pacMan->getDirections().front()) {
                case Direction::UP:
                    m_peers[cur_id].pinkGhost->setGhostDestination(m_peers[cur_id].pacMan->getCellX(), m_peers[cur_id].pacMan->getCellY() - 4);
                    break;
                case Direction::DOWN:
                    m_peers[cur_id].pinkGhost->setGhostDestination(m_peers[cur_id].pacMan->getCellX(), m_peers[cur_id].pacMan->getCellY() + 4);
                    break;
                case Direction::LEFT:
                    m_peers[cur_id].pinkGhost->setGhostDestination(m_peers[cur_id].pacMan->getCellX() - 4, m_peers[cur_id].pacMan->getCellY());
                    break;
                case Direction::RIGHT:
                    m_peers[cur_id].pinkGhost->setGhostDestination(m_peers[cur_id].pacMan->getCellX() + 4, m_peers[cur_id].pacMan->getCellY());
                    break;
            }
        }

        // Blue Ghost Patrols with direction close to Pacman decided by distance between the two
        // Inky the cyan ghost will patrol an area and is not very predictable in this mode.
        if (!m_peers[cur_id].blueGhost->isScatterGhosts()) {
            m_peers[cur_id].blueGhost->setGhostDestination(m_peers[cur_id].pacMan->getCellX() + (m_peers[cur_id].redGhost->getCellX() - m_peers[cur_id].pacMan->getCellX()), m_peers[cur_id].pacMan->getCellY() + (
                    m_peers[cur_id].redGhost->getCellY() - m_peers[cur_id].pacMan->getCellY()));
        }

        // Orange Ghost chases Pacman if it is close to clyde else it minds its own business.
        // Clyde the orange ghost is moving in a random fashion and seems to stay out of the way of Pac-Man.
        if (!m_peers[cur_id].orangeGhost->isScatterGhosts()) {
            if (sqrt(pow((m_peers[cur_id].orangeGhost->getCellX() - (m_peers[cur_id].pacMan->getCellX())), 2) + pow((m_peers[cur_id].orangeGhost->getCellY() - (m_peers[cur_id].pacMan->getCellY())), 2)) < 9) {
                m_peers[cur_id].orangeGhost->setGhostDestination(m_peers[cur_id].pacMan->getCellX(), m_peers[cur_id].pacMan->getCellY());
            }
            else {
                m_peers[cur_id].orangeGhost->setGhostDestination(1, 30);
            }
        }
    }
}

/**
 * Determines if the PacMan character is free to move
 * @return True if pacman can move, false otherwise
 */
bool Server::isPacManMovementAllowed() {
    if (!m_peers[cur_id].pacMan->getDirections().empty()) {
        switch (m_peers[cur_id].pacMan->directions.front()) {
            case Direction::UP:
                return !m_peers[cur_id].maze->isCellBlockingCharacter(m_peers[cur_id].pacMan->getCellX(), m_peers[cur_id].pacMan->getCellY() - 1);
                break;
            case Direction::DOWN:
                return !m_peers[cur_id].maze->isCellBlockingCharacter(m_peers[cur_id].pacMan->getCellX(), m_peers[cur_id].pacMan->getCellY() + 1);
                break;
            case Direction::LEFT:
                return !m_peers[cur_id].maze->isCellBlockingCharacter(m_peers[cur_id].pacMan->getCellX() - 1, m_peers[cur_id].pacMan->getCellY());
                break;
            case Direction::RIGHT:
                return !m_peers[cur_id].maze->isCellBlockingCharacter(m_peers[cur_id].pacMan->getCellX() + 1, m_peers[cur_id].pacMan->getCellY());
                break;
        }
    }
    return true;
}

/**
 * Calculates the distance between ghost position and the x,y coordinates supplied to it
 * @param ghost - Ghost for which distance is being calculated
 * @param x - target X
 * @param y - target Y
 * @return distance
 */
float Server::calculateGhostDistance(GhostServer *ghost, int x, int y) {
    float distance = 1000000.0f;
    if (!m_peers[cur_id].maze->isCellBlockingCharacter(ghost->getCellX() + x, ghost->getCellY() + y)) {
        // ((x2-x1)^2 - (Y2-Y1)^2)^(1/2)
        distance = (float) sqrt(pow((ghost->getDestinationX() - (ghost->getCellX() + x)), 2) + pow((ghost->getDestinationY() - (ghost->getCellY() + y)), 2));
    }
    return distance;
}

/**
 * This function determines the movement behaviour of the ghosts
 * @param ghost
 */
void Server::handleGhostMovement(GhostServer *ghost) {
    // Set Scattering to false if target tile reached
    if(ghost->isScatterGhosts()) {
        if(ghost->getCellX() == ghost->getDestinationX() && ghost->getCellY() == ghost->getDestinationY()) {
            ghost->setScatterGhosts(false);
        }
    }

    if(m_peers[cur_id].maze->isMazeIntersection(ghost->getCellX(), ghost->getCellY())) {
        if (ghost->isGhostDecision()) {
            float distanceRight = calculateGhostDistance(ghost, 1, 0);
            float distanceLeft = calculateGhostDistance(ghost, -1, 0);
            float distanceUp = calculateGhostDistance(ghost, 0, -1);
            float distanceDown = calculateGhostDistance(ghost, 0, 1);
            if (distanceRight < distanceLeft && distanceRight < distanceUp && distanceRight < distanceDown)
                ghost->setDirection(Direction::RIGHT);
            else if (distanceLeft < distanceRight && distanceLeft < distanceUp && distanceLeft < distanceDown)
                ghost->setDirection(Direction::LEFT);
            else if (distanceUp < distanceLeft && distanceUp < distanceRight && distanceUp < distanceDown)
                ghost->setDirection(Direction::UP);
            else if (distanceDown < distanceLeft && distanceDown < distanceUp && distanceDown < distanceRight)
                ghost->setDirection(Direction::DOWN);
        }
        ghost->setGhostDecision(false);
    }
    else {
        ghost->setGhostDecision(true);
    }

    if (isGhostMovementAllowed(ghost) && ghost->isGhostOutOfCage())
        ghost->moveGhost();
    else
        ghost->setGhostDecision(true);
}

/**
 * This function determines if ghost movement is allowed from a target to destination cell
 * @param ghost - Ghost in question (who we want to move)
 * @return Boolean, True if Movement is allowed
 */
bool Server::isGhostMovementAllowed(GhostServer *ghost) {
    switch (ghost->getDirection()) {
        case Direction::UP:
            return !m_peers[cur_id].maze->isCellBlockingCharacter(ghost->getCellX(), ghost->getCellY() - 1);
            break;
        case Direction::DOWN:
            return !m_peers[cur_id].maze->isCellBlockingCharacter(ghost->getCellX(), ghost->getCellY() + 1);
            break;
        case Direction::LEFT:
            return !m_peers[cur_id].maze->isCellBlockingCharacter(ghost->getCellX() - 1, ghost->getCellY());
            break;
        case Direction::RIGHT:
            return !m_peers[cur_id].maze->isCellBlockingCharacter(ghost->getCellX() + 1, ghost->getCellY());
            break;
        default:
            return false;
    }
}

/**
 * @TODO: Automate tunnel locations in a random maze instead of hardcoding
 * This function helps the characters teleport from one end of the tunnel to the other
 * @param character
 */
void Server::teleportTunnels(CharacterServer *character) {
    if (character->getCellX() == 0 && character->getCellY() == 17)
        character->teleport(27, 17);
    else if (character->getCellX() == 28 && character->getCellY() == 17)
        character->teleport(1, 17);
}

/**
 * Handles the frightened state of ghosts, when pacman eats power pellets
 * @param ghost - The frightened ghost in question
 */
void Server::handleGhostFrightening(GhostServer *ghost) {
     if (m_peers[cur_id].pacMan->getCellX() == ghost->getCellX() && m_peers[cur_id].pacMan->getCellY() == ghost->getCellY()) {
         if (ghost->isGhostFrightened()) {
             ghost->teleport(13, 14);
             ghost->setGhostFrightened(false);
             m_peers[cur_id].score = m_peers[cur_id].score + 50;
         }
         else {
             m_peers[cur_id].pacMan->setPacmanDead(true);
             m_peers[cur_id].redGhost->teleport(-2, -2);
             m_peers[cur_id].pinkGhost->teleport(-2,-2);
             m_peers[cur_id].blueGhost->teleport(-2,-2);
             m_peers[cur_id].orangeGhost->teleport(-2,-2);
         }
     }
}


/**
 * Removes the pellets from the game screen when PacMan eats them
 */
void Server::removePellets() {
    // Pellet Tile -> Blank Tile
    if(m_peers[cur_id].maze->cells[m_peers[cur_id].pacMan->getCellX()][m_peers[cur_id].pacMan->getCellY()] == 0) {
        m_peers[cur_id].maze->cells[m_peers[cur_id].pacMan->getCellX()][m_peers[cur_id].pacMan->getCellY()] = 4;
        m_peers[cur_id].pacMan->eatPellets();
        m_peers[cur_id].score++;
    }
    // Power Pellet Tile -> Blank Tile
    else if(m_peers[cur_id].maze->cells[m_peers[cur_id].pacMan->getCellX()][m_peers[cur_id].pacMan->getCellY()] == 3) {
        m_peers[cur_id].maze->cells[m_peers[cur_id].pacMan->getCellX()][m_peers[cur_id].pacMan->getCellY()] = 4;
        m_peers[cur_id].redGhost->setGhostFrightened(true);
        m_peers[cur_id].pinkGhost->setGhostFrightened(true);
        m_peers[cur_id].blueGhost->setGhostFrightened(true);
        m_peers[cur_id].orangeGhost->setGhostFrightened(true);
        m_peers[cur_id].score = m_peers[cur_id].score + 5;

    }
}
