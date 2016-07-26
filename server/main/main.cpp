#include <iostream>
#include "parser/Parser.h"
#include "tcp/Server.h"
#include "Game.h"
#include "world/endpoint/AbstractRequestHandler.h"
#include "world/endpoint/PlayerRequestHandler.h"
#include "world/endpoint/SpectatorRequestHandler.h"


int main(int ac, char **av) {
    srand((unsigned int) (time(NULL) ^ getpid()));
    zappy::Parser parser(ac, av);

    if (!parser.isValid()) {
        std::cerr << parser.usage() << std::endl;
        return (EXIT_FAILURE);
    }
    zappy::Game game(parser.getDeltaTime(), parser.getSize(), parser.getTeams(), parser.getTeamCount());
    zappy::PlayerRequestHandler playerRoute(game);
    zappy::SpectatorRequestHandler spectatorRoute(game);
    my_tcp::Server playerServer(playerRoute);
    my_tcp::Server spectatorServer(spectatorRoute);

    bool createdPlayerServer = playerServer.listen(parser.getPort(), "0.0.0.0");
    bool createdSpectatorServer = parser.getSpectatorPort().empty() ? false : spectatorServer.listen(parser.getSpectatorPort(), "0.0.0.0");

    if (!createdPlayerServer || (!parser.getSpectatorPort().empty() && !createdSpectatorServer)) {
        std::cerr << "failed to start zappy: " << playerServer.getStatus() << std::endl;
        std::cerr << "failed to start zappy: " << spectatorServer.getStatus() << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Player Server Listening at: 127.0.0.1:" << parser.getPort() << std::endl;
    if (!parser.getSpectatorPort().empty()) std::cout << "Spectator Server Listening at: 127.0.0.1:" << parser.getSpectatorPort() << std::endl;

    playerServer.start();
    spectatorServer.start();
    while (playerServer.isRunning() || spectatorServer.isRunning()) {
        if (playerServer.isRunning()) playerServer.update();
        if (spectatorServer.isRunning()) spectatorServer.update();
        game.update();
    }
    return (EXIT_SUCCESS);
}