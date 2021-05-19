/**
 * First State in the game, demonstrates start of the game play
 */

#include "client/PacMan.h"
#include "client/Ghost.h"
#include "client/GamePlay.h"
#include "client/Direction.h"
#include "client/LoadSprites.h"
#include "client/Maze.h"
#include "client/Audio.h"
#include <iostream>
#include <bits/stdc++.h>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include<unistd.h>

#include <cmath>
#include <client/Entity.h>

using namespace sf;
using namespace std;

/**
 * Initialises the play state of the game
 */
void GamePlay::init()
{
    sf::IpAddress serverAddress, myAddress;
    std::cout << "Enter Server IP address: ";
    std::cin >> serverAddress;
    logger = new Logger("GamePlay");
    audioManager = new AudioManager();
    stopSirenAndLoop(Sounds::GameStart, false, VOLUME);
    while(audioManager->isPlayingAudio(Sounds::GameStart) || audioManager->isPlayingAudio(Sounds::Death)) {
        continue;
    }
    myAddress = sf::IpAddress::getPublicAddress();
    if(serverAddress == myAddress){
        m_remoteAddress = sf::IpAddress::LocalHost;
    }
    else{
        m_remoteAddress = serverAddress;
    }
    m_remotePort = 54321;
    logger->log(m_remoteAddress.toString());
    m_connects.fill(false);
    sf::Packet packet;
    packet << CommandsToServer::Connect;
    send(packet);
    {
        sf::Packet packet;
        sf::IpAddress address;
        Port_t port;
        if (m_socket.receive(packet, address, port) == sf::Socket::Done) {
            CommandsToClient command;
            uint8_t result;
            packet >> command >> result;
            if (result) {
                connect(packet);
            }
        }
    }
    
    if(!m_isConnected){
        return;
    }
    Maze* temp_maze = new Maze();
    for(int k = 0; k < 2; k++){
        int i;
        int threshold = 0;
        do{
            i = rand()%25 + 1;
            threshold++;
        }
        while(temp_maze->isCellBlockingCharacter(i, 29) && threshold < 50);
        if(threshold == 50){
            do{
                i = rand()%25 + 1;
                threshold++;
            }
            while(temp_maze->isCellBlockingCharacter(i, 4) && threshold < 100);
            if(threshold == 100){
               m_peers[k].pacMan = new PacMan(10, 30);
            }
            else{
                m_peers[k].pacMan = new PacMan(i, 3);
            }
        }
        else{
            m_peers[k].pacMan = new PacMan(i, 30);
        }
        m_peers[k].maze = new Maze();
        m_peers[k].redGhost = new Ghost(14,14,1, 3);
        m_peers[k].pinkGhost = new Ghost(14,18,26,3);
        m_peers[k].blueGhost = new Ghost(12,18,1,30);
        m_peers[k].orangeGhost = new Ghost(16,18,26,30);

        m_peers[k].redGhost->teleport(13, 14);
    }
    
    {
        sf::Packet packet;
        sf::IpAddress address;
        Port_t port;
        while (m_socket.receive(packet, address, port) == sf::Socket::Done) {
            CommandsToClient command;
            packet >> command;
            switch (command) {
                case CommandsToClient::ConnectRequestResult:
                    break;

                case CommandsToClient::PacManPosition:
                    handlePacManPosition(packet);
                    break;

                case CommandsToClient::RedGhostPosition:
                    handleRedGhostPosition(packet);
                    break;
                case CommandsToClient::PinkGhostPosition:
                    handlePinkGhostPosition(packet);
                    break;
                case CommandsToClient::BlueGhostPosition:
                    handleBlueGhostPosition(packet);
                    break;
                case CommandsToClient::OrangeGhostPosition:
                    handleOrangeGhostPosition(packet);
                    break;
                case CommandsToClient::Maze:
                    handleMaze(packet);
                    break;
                case CommandsToClient::Result:
                    handleResult(packet);
                    break;
                case CommandsToClient::Scores:
                    handleScores(packet);
                    break;
            }
        }
    }

    waitTime = 0;
}

void GamePlay::connect(sf::Packet &packet)
{
    logger->log("Connection request accepted!");
    packet >> m_clientId;
    m_isConnected = true;

    auto slot = static_cast<std::size_t>(m_clientId);
    m_connects[slot] = true;
    logger->log("Connection is able to be made!");

    m_socket.setBlocking(false);
}

void GamePlay::send(sf::Packet &packet)
{
    m_socket.send(packet, m_remoteAddress, m_remotePort);
}
/**
 * Specifies actions which keep the play state of the game running in a loop
 */
void GamePlay::loop() {
    if(!m_isConnected){
        return;
    }
    // a hacky way to freeze game when intro music is playing - give player some time to prepare.
    while(audioManager->isPlayingAudio(Sounds::GameStart) || audioManager->isPlayingAudio(Sounds::Death)) {
        continue;
    }

    Input_t input = 0;
    int x = static_cast<int>(m_clientId);
    if (!m_peers[x].pacMan->getDirections().empty()) {
        switch (m_peers[x].pacMan->getDirections().front()) {
            case Direction::UP:{
                input = Input::UP1;
                break;
            }
            case Direction::DOWN:{
                input = Input::DOWN1;
                break;
            }
            case Direction::LEFT:{
                input = Input::LEFT1;
                break;
            }
            case Direction::RIGHT:{
                input = Input::RIGHT1;
                break;
            }
        }
        m_peers[x].pacMan->directions.pop();
        sf::Packet clientInput;
        clientInput << CommandsToServer::Input << m_clientId << input;
        send(clientInput);  
    }
    
    {
        sf::Packet packet;
        sf::IpAddress address;
        Port_t port;
        while (m_socket.receive(packet, address, port) == sf::Socket::Done) {
            CommandsToClient command;
            packet >> command;
            switch (command) {
                case CommandsToClient::ConnectRequestResult:
                    break;

                case CommandsToClient::PacManPosition:
                    handlePacManPosition(packet);
                    break;

                case CommandsToClient::RedGhostPosition:
                    handleRedGhostPosition(packet);
                    break;
                case CommandsToClient::PinkGhostPosition:
                    handlePinkGhostPosition(packet);
                    break;
                case CommandsToClient::BlueGhostPosition:
                    handleBlueGhostPosition(packet);
                    break;
                case CommandsToClient::OrangeGhostPosition:
                    handleOrangeGhostPosition(packet);
                    break;
                case CommandsToClient::Maze:
                    handleMaze(packet);
                    break;
                case CommandsToClient::Result:
                    handleResult(packet);
                    break;
                case CommandsToClient::Scores:
                    handleScores(packet);
                    break;
            }
            
        }
        if(m_peers[x].pacMan->isPacmanDead()){
            m_peers[x].pacMan->setPacmanDead(false);
            logger->log("PacMan Dead. Resetting Game.");
            stopSirenAndLoop(Sounds::Death, false, VOLUME);   
        }
    }

    
}

void GamePlay::handleResult(sf::Packet &packet){
    Client_t clientid;
    int result;
    float x;
    while (packet >> clientid) {
        int id = static_cast<int>(clientid);
        packet >> x;
        result = (int)x;
        if(result == 1 ){
            m_peers[id].win = true;
        }
    }
    gameOver = true;
}

void GamePlay::handleScores(sf::Packet &packet){
    Client_t clientid;
    float x, y;
    while (packet >> clientid) {
        int id = static_cast<int>(clientid);
        packet >> x >> y;
        m_peers[id].score = (int)x;
        time = (int)y;
    }
}

void GamePlay::handlePacManPosition(sf::Packet &packet)
{
    Client_t clientid;
    Input_t input1;
    int a, b, p;
    float x, y, dead;
    while (packet >> clientid) {
        int id = static_cast<int>(clientid);
        int pacmanX = m_peers[id].pacMan->screenPositionX;
        int pacmanY = m_peers[id].pacMan->screenPositionY;
        packet >> x >> y >> dead >> input1;
        a = (int)x; b = (int)y; p = (int)dead;
        if(p == 1){
            m_peers[id].pacMan->setPacmanDead(true);
        }
        else{
            m_peers[id].pacMan->setPacmanDead(false);
        }
        auto &inputState = m_clientInputs[id];
        inputState.up = input1 == Input::UP1;
        inputState.down = input1 == Input::DOWN1;
        inputState.right = input1 == Input::RIGHT1;
        inputState.left = input1 == Input::LEFT1;
        auto &input = m_clientInputs[id];
        if(input.left){
            m_peers[id].pacMan->setDirection(Direction::LEFT);
        }
        else if(input.down){
            m_peers[id].pacMan->setDirection(Direction::DOWN);
        }
        else if(input.right){
            m_peers[id].pacMan->setDirection(Direction::RIGHT);
        }
        else{
            m_peers[id].pacMan->setDirection(Direction::UP);
        }
        m_connects[id] = true;
        m_peers[id].pacMan->move(a - pacmanX, b - pacmanY);
    }
    
}

void GamePlay::handleRedGhostPosition(sf::Packet &packet)
{
    Client_t clientid;
    int a, b, p, q;
    float x, y, frighten, outOfCage;
    Input_t input1;
    while (packet >> clientid) {
        int id = static_cast<int>(clientid);
        int redGhostX = m_peers[id].redGhost->screenPositionX;
        int redGhostY = m_peers[id].redGhost->screenPositionY;
        packet >> x >> y >> frighten >> outOfCage >> input1;;
        a = x; b = y; p = frighten; q = outOfCage;
        if(p == 1){
            m_peers[id].redGhost->setGhostFrightened(true);
        }
        else{
            m_peers[id].redGhost->setGhostFrightened(false);
        }
        if(q == 1){
            m_peers[id].redGhost->move(a - redGhostX, b - redGhostY);
        }
        auto &inputState = m_clientInputs[id];
        inputState.up = input1 & Input::UP1;
        inputState.down = input1 & Input::DOWN1;
        inputState.right = input1 & Input::RIGHT1;
        inputState.left = input1 & Input::LEFT1;
        auto &input = m_clientInputs[id];
        if(input.up){
            m_peers[id].redGhost->setDirection(Direction::UP);
        }
        else if(input.down){
            m_peers[id].redGhost->setDirection(Direction::DOWN);
        }
        else if(input.right){
            m_peers[id].redGhost->setDirection(Direction::RIGHT);
        }
        else{
            m_peers[id].redGhost->setDirection(Direction::LEFT);
        }
    }
}

void GamePlay::handlePinkGhostPosition(sf::Packet &packet)
{
    Client_t clientid;
    int a, b, p, q;
    float x, y, frighten, outOfCage;
    Input_t input1;
    while (packet >> clientid) {
        int id = static_cast<int>(clientid);
        int pinkGhostX = m_peers[id].pinkGhost->screenPositionX;
        int pinkGhostY = m_peers[id].pinkGhost->screenPositionY;
        packet >> x >> y >> frighten >> outOfCage >> input1;;
        a = x; b = y; p = frighten; q = outOfCage;
        if(p == 1){
            m_peers[id].pinkGhost->setGhostFrightened(true);
        }
        else{
            m_peers[id].pinkGhost->setGhostFrightened(false);
        }
        if(q == 1){
            m_peers[id].pinkGhost->move(a - pinkGhostX, b - pinkGhostY);
        }
        auto &inputState = m_clientInputs[id];
        inputState.up = input1 & Input::UP1;
        inputState.down = input1 & Input::DOWN1;
        inputState.right = input1 & Input::RIGHT1;
        inputState.left = input1 & Input::LEFT1;
        auto &input = m_clientInputs[id];
        if(input.up){
            m_peers[id].pinkGhost->setDirection(Direction::UP);
        }
        else if(input.down){
            m_peers[id].pinkGhost->setDirection(Direction::DOWN);
        }
        else if(input.right){
            m_peers[id].pinkGhost->setDirection(Direction::RIGHT);
        }
        else{
            m_peers[id].pinkGhost->setDirection(Direction::LEFT);
        }
    }
}

void GamePlay::handleBlueGhostPosition(sf::Packet &packet)
{
    Client_t clientid;
    int a, b, p, q;
    float x, y, frighten, outOfCage;
    Input_t input1;
    while (packet >> clientid) {
        int id = static_cast<int>(clientid);
        int blueGhostX = m_peers[id].blueGhost->screenPositionX;
        int blueGhostY = m_peers[id].blueGhost->screenPositionY;
        packet >> x >> y >> frighten >> outOfCage >> input1;;
        a = x; b = y; p = frighten; q = outOfCage;
        if(p == 1){
            m_peers[id].blueGhost->setGhostFrightened(true);
        }
        else{
            m_peers[id].blueGhost->setGhostFrightened(false);
        }
        if(q == 1){
            m_peers[id].blueGhost->move(a - blueGhostX, b - blueGhostY);
        }
        auto &inputState = m_clientInputs[id];
        inputState.up = input1 & Input::UP1;
        inputState.down = input1 & Input::DOWN1;
        inputState.right = input1 & Input::RIGHT1;
        inputState.left = input1 & Input::LEFT1;
        auto &input = m_clientInputs[id];
        if(input.up){
            m_peers[id].blueGhost->setDirection(Direction::UP);
        }
        else if(input.down){
            m_peers[id].blueGhost->setDirection(Direction::DOWN);
        }
        else if(input.right){
            m_peers[id].blueGhost->setDirection(Direction::RIGHT);
        }
        else{
            m_peers[id].blueGhost->setDirection(Direction::LEFT);
        }
    }
}

void GamePlay::handleOrangeGhostPosition(sf::Packet &packet)
{
    Client_t clientid;
    float x, y, frighten, outOfCage;
    int a, b, p, q;
    Input_t input1;
    while (packet >> clientid) {
        int id = static_cast<int>(clientid);
        int orangeGhostX = m_peers[id].orangeGhost->screenPositionX;
        int orangeGhostY = m_peers[id].orangeGhost->screenPositionY;
        packet >> x >> y >> frighten >> outOfCage >> input1;
        a = x; b = y; p = frighten; q = outOfCage;
        if(p == 1){
            m_peers[id].orangeGhost->setGhostFrightened(true);
        }
        else{
            m_peers[id].orangeGhost->setGhostFrightened(false);
        }
        if(q == 1){
            m_peers[id].orangeGhost->move(a - orangeGhostX, b - orangeGhostY);
        }
        auto &inputState = m_clientInputs[id];
        inputState.up = input1 & Input::UP1;
        inputState.down = input1 & Input::DOWN1;
        inputState.right = input1 & Input::RIGHT1;
        inputState.left = input1 & Input::LEFT1;
        auto &input = m_clientInputs[id];
        if(input.up){
            m_peers[id].orangeGhost->setDirection(Direction::UP);
        }
        else if(input.down){
            m_peers[id].orangeGhost->setDirection(Direction::DOWN);
        }
        else if(input.right){
            m_peers[id].orangeGhost->setDirection(Direction::RIGHT);
        }
        else{
            m_peers[id].orangeGhost->setDirection(Direction::LEFT);
        }
    }
}

void GamePlay::handleMaze(sf::Packet &packet)
{
    
    Client_t clientid;
    int x[30][34];
    float y;
    while(packet >> clientid){
        int id = static_cast<int>(clientid);
        if(id > 1){
        }
        for(int i = 0; i < 30; i++){
            for(int j = 0; j < 34; j++){
                packet >> y;
                int z = static_cast<int>(y);
                m_peers[id].maze->cells[i][j] = z;
            }
        }
    }
}

/**
 * Render sprites and stuff on the game window
 * @param window - Game Window
 */
void GamePlay::render(RenderWindow *window, unsigned i) {
    int id, id2;
    id = static_cast<int>(m_clientId);
    if(static_cast<int>(m_clientId) == 0){
        id2 = 1;
    }
    else{
        id2 = 0;
    }

    if(!m_isConnected){
        return;
    }
    

    // Load Maze
    for (int i = 0; i < Maze::SIZE_X; i++)
    {
        for (int j = 0; j < Maze::SIZE_Y; j++)
        {
            LoadSprites::mazePieces[m_peers[id].maze->getCellCode(i, j)]->setPosition(i * 16.0f, j * 16.0f);
            window->draw(*LoadSprites::mazePieces[m_peers[id].maze->getCellCode(i, j)]);
        }
    }
    // Load Character Sprites and animate it
    Sprite pacManSprite;
    Sprite redGhostSprite;
    Sprite pinkGhostSprite;
    Sprite blueGhostSprite;
    Sprite orangeGhostSprite;

    if (m_peers[id].pacMan->getDirections().empty())
        pacManSprite = *LoadSprites::get(Entity::PAC_MAN, true, m_peers[id].pacMan->direction);
    else
        pacManSprite = *LoadSprites::get(Entity::PAC_MAN, true, m_peers[id].pacMan->getDirections().front());

    if (m_peers[id].pacMan->isPacmanDead())
        pacManSprite = *LoadSprites::get(Entity::DEAD_PAC_MAN, true, Direction::UNSET);

    if (!m_peers[id].redGhost->isGhostFrightened())
        redGhostSprite = *LoadSprites::get(Entity::RED_GHOST, m_peers[id].redGhost->isGhostOutOfCage(), m_peers[id].redGhost->getDirection());
    else
        redGhostSprite = *LoadSprites::get(Entity::FRIGHTENED_GHOST, m_peers[id].redGhost->isGhostOutOfCage(), m_peers[id].redGhost->getDirection());

    if (!m_peers[id].pinkGhost->isGhostFrightened())
        pinkGhostSprite = *LoadSprites::get(Entity::PINK_GHOST, m_peers[id].pinkGhost->isGhostOutOfCage(), m_peers[id].pinkGhost->getDirection());
    else
        pinkGhostSprite = *LoadSprites::get(Entity::FRIGHTENED_GHOST, m_peers[id].pinkGhost->isGhostOutOfCage(), m_peers[id].pinkGhost->getDirection());

    if (!m_peers[id].blueGhost->isGhostFrightened())
        blueGhostSprite = *LoadSprites::get(Entity::BLUE_GHOST, m_peers[id].blueGhost->isGhostOutOfCage(), m_peers[id].blueGhost->getDirection());
    else
        blueGhostSprite = *LoadSprites::get(Entity::FRIGHTENED_GHOST, m_peers[id].blueGhost->isGhostOutOfCage(), m_peers[id].blueGhost->getDirection());

    if (!m_peers[id].orangeGhost->isGhostFrightened())
        orangeGhostSprite = *LoadSprites::get(Entity::ORANGE_GHOST, m_peers[id].orangeGhost->isGhostOutOfCage(), m_peers[id].orangeGhost->getDirection());
    else
        orangeGhostSprite = *LoadSprites::get(Entity::FRIGHTENED_GHOST, m_peers[id].orangeGhost->isGhostOutOfCage(), m_peers[id].orangeGhost->getDirection());

    pacManSprite.setPosition(m_peers[id].pacMan->getScreenPositionX(),m_peers[id].pacMan->getScreenPositionY());
    redGhostSprite.setPosition(m_peers[id].redGhost->getScreenPositionX(), m_peers[id].redGhost->getScreenPositionY());
    pinkGhostSprite.setPosition(m_peers[id].pinkGhost->getScreenPositionX(),m_peers[id].pinkGhost->getScreenPositionY());
    blueGhostSprite.setPosition(m_peers[id].blueGhost->getScreenPositionX(),m_peers[id].blueGhost->getScreenPositionY());
    orangeGhostSprite.setPosition(m_peers[id].orangeGhost->getScreenPositionX(),m_peers[id].orangeGhost->getScreenPositionY());

    window->draw(pacManSprite);
    window->draw(redGhostSprite);
    window->draw(pinkGhostSprite);
    window->draw(blueGhostSprite);
    window->draw(orangeGhostSprite);



    // Opponent
    for (int i = 0; i < Maze::SIZE_X; i++)
    {
        for (int j = 0; j < Maze::SIZE_Y; j++)
        {

            LoadSprites::mazePieces[m_peers[id2].maze->getCellCode(i, j)]->setPosition(i * 16.0f + 486, j * 16.0f);            
            window->draw(*LoadSprites::mazePieces[m_peers[id2].maze->getCellCode(i, j)]);
        }
    }

    if (m_peers[id2].pacMan->getDirections().empty())
        pacManSprite = *LoadSprites::get(Entity::PAC_MAN, true, m_peers[id2].pacMan->direction);
    else
        pacManSprite = *LoadSprites::get(Entity::PAC_MAN, true, m_peers[id2].pacMan->getDirections().front());

    if (m_peers[id2].pacMan->isPacmanDead())
        pacManSprite = *LoadSprites::get(Entity::DEAD_PAC_MAN, true, Direction::UNSET);

    if (!m_peers[id2].redGhost->isGhostFrightened())
        redGhostSprite = *LoadSprites::get(Entity::RED_GHOST, m_peers[id2].redGhost->isGhostOutOfCage(), m_peers[id2].redGhost->getDirection());
    else
        redGhostSprite = *LoadSprites::get(Entity::FRIGHTENED_GHOST, m_peers[id2].redGhost->isGhostOutOfCage(), m_peers[id2].redGhost->getDirection());

    if (!m_peers[id2].pinkGhost->isGhostFrightened())
        pinkGhostSprite = *LoadSprites::get(Entity::PINK_GHOST, m_peers[id2].pinkGhost->isGhostOutOfCage(), m_peers[id2].pinkGhost->getDirection());
    else
        pinkGhostSprite = *LoadSprites::get(Entity::FRIGHTENED_GHOST, m_peers[id2].pinkGhost->isGhostOutOfCage(), m_peers[id2].pinkGhost->getDirection());

    if (!m_peers[id2].blueGhost->isGhostFrightened())
        blueGhostSprite = *LoadSprites::get(Entity::BLUE_GHOST, m_peers[id2].blueGhost->isGhostOutOfCage(), m_peers[id2].blueGhost->getDirection());
    else
        blueGhostSprite = *LoadSprites::get(Entity::FRIGHTENED_GHOST, m_peers[id2].blueGhost->isGhostOutOfCage(), m_peers[id2].blueGhost->getDirection());

    if (!m_peers[id2].orangeGhost->isGhostFrightened())
        orangeGhostSprite = *LoadSprites::get(Entity::ORANGE_GHOST, m_peers[id2].orangeGhost->isGhostOutOfCage(), m_peers[id2].orangeGhost->getDirection());
    else
        orangeGhostSprite = *LoadSprites::get(Entity::FRIGHTENED_GHOST, m_peers[id2].orangeGhost->isGhostOutOfCage(), m_peers[id2].orangeGhost->getDirection());

    pacManSprite.setPosition(m_peers[id2].pacMan->getScreenPositionX() + 486,m_peers[id2].pacMan->getScreenPositionY());
    redGhostSprite.setPosition(m_peers[id2].redGhost->getScreenPositionX() + 486, m_peers[id2].redGhost->getScreenPositionY());
    pinkGhostSprite.setPosition(m_peers[id2].pinkGhost->getScreenPositionX() + 486,m_peers[id2].pinkGhost->getScreenPositionY());
    blueGhostSprite.setPosition(m_peers[id2].blueGhost->getScreenPositionX() + 486,m_peers[id2].blueGhost->getScreenPositionY());
    orangeGhostSprite.setPosition(m_peers[id2].orangeGhost->getScreenPositionX() + 486,m_peers[id2].orangeGhost->getScreenPositionY());

    window->draw(pacManSprite);
    window->draw(redGhostSprite);
    window->draw(pinkGhostSprite);
    window->draw(blueGhostSprite);
    window->draw(orangeGhostSprite);

    sf::Font font;
    if (!font.loadFromFile("assets/open-sans/OpenSans-Light.ttf"))
    {
        std::cout << "Error loading font\n" ;
    }
    std::ostringstream ss;
    ss << "You";
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::Blue);
    text.setPosition(215.f, 510.f);
    text.setString(ss.str());
    window->draw(text);

    // Opponent
    std::ostringstream ss1;
    ss1 << "Opponent";
    text.setFont(font);
    text.setCharacterSize(24);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::Blue);
    text.setPosition(675.f, 510.f);
    text.setString(ss1.str());
    window->draw(text);

    // Score - 1
    std::ostringstream ss2;
    ss2 << "" << m_peers[id].score;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::White);
    text.setPosition(20.f, 8.f);
    text.setString(ss2.str());
    window->draw(text);

    // Score - 2
    std::ostringstream ss3;
    ss3 << "" << m_peers[id2].score;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::White);
    text.setPosition(900.f, 8.f);
    text.setString(ss3.str());
    window->draw(text);

    // Time
    std::ostringstream ss4;
    ss4 << time << "s";
    text.setFont(font);
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::White);
    text.setPosition(470.f, 8.f);
    text.setString(ss4.str());
    window->draw(text);

    // GameOver
    if(gameOver){
        int myId = static_cast<int>(m_clientId);
        std::ostringstream ss0;
        if(m_peers[myId].win){
            ss0 << "YOU WON";
        }
        else{
            ss0 << "YOU LOST";
        }
        text.setFont(font);
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Bold);
        text.setColor(sf::Color::Yellow);
        text.setPosition(430.f, 250.f);
        text.setString(ss0.str());
        window->draw(text);
    }
}

/**
 * Set action for key presses during gameplay
 * @param code - key code
 */
void GamePlay::keyPressed(int code) {
    // logger->log("Key Pressed: "+to_string(code));
    int x = static_cast<int>(m_clientId);
    switch (code) {
        case Keyboard::Up:
            m_peers[x].pacMan->queueDirection(Direction::UP);
            break;
        case Keyboard::Down:
            m_peers[x].pacMan->queueDirection(Direction::DOWN);
            break;
        case Keyboard::Left:
            m_peers[x].pacMan->queueDirection(Direction::LEFT);
            break;
        case Keyboard::Right:
            m_peers[x].pacMan->queueDirection(Direction::RIGHT);
            break;
    }
}

/**
 * Set action for key release during gameplay
 * @param code - key code
 */
void GamePlay::keyReleased(int code) {}


/**
 * replace siren audio with another sound
 * @param sound - to be played
 * @param isLoop - whether to play on a loop or no
 * @param volume - volume to be played in
 */
void GamePlay::stopSirenAndLoop(Sounds sound, bool isLoop, int volume) {
    if(audioManager->isPlayingAudio(Sounds::Siren))
        audioManager->stopSound(Sounds::Siren);
    if(audioManager->isPlayingAudio(Sounds::Munch))
        audioManager->stopSound(Sounds::Munch);
    audioManager->playSound(sound, isLoop, volume);
    while(audioManager->isPlayingAudio(sound))
        continue;
    audioManager->playSound(Sounds::Siren, true, VOLUME_SIREN);
}