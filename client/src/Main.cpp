#include <SFML/Graphics.hpp>
#include <iostream>

#include "client/Client.h"
#include <server/Server.h>

void printOptions()
{
    std::cout << "Please enter options. Usage:\n";
    std::cout << "./pacman client\n";
    std::cout << "./pacman server\n";
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "Please enter options. Usage:\n";
        std::cout << "./pacman client\n";
        std::cout << "./pacman server\n";
        return EXIT_SUCCESS;
    }
    std::vector<std::string> options;
    for (int i = 0; i < argc; i++) {
        options.push_back(argv[i]);
    }

    if (options[1] == "client") {
        Client client;
        client.run();
    }
    else if (options[1] == "server") {
        Server *server = new Server();
        //std::cout << "here1";
        server->init();

        server->loop();
    }
    else {
        printOptions();
    }
}