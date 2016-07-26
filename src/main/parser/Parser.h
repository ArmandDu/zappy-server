//
// Created by armanddu on 26/06/16.
//

#ifndef ZAPPY_PARSER_H
#define ZAPPY_PARSER_H


#include <vector>
#include <string>
#include <sstream>
#include <getopt.h>

#include "../world/Rect.h"

namespace zappy {
    class Parser {

    private:
        std::string path;
        std::string port;
        std::string spectatorPort;
        Rect size;
        std::vector<std::string> teams;
        int teamCount;
        int deltaTime;

    public:
        Parser(int ac, char **av);

    public:
        const std::string & getPort()const;
        const std::string & getSpectatorPort()const;

        const Rect & getSize()const;

        const std::vector<std::string> & getTeams()const;
        int getTeamCount()const;

        int getDeltaTime()const;

        bool isValid()const;

        std::string usage();

    public:

        friend std::ostream& operator<<(std::ostream& os, const Parser& obj);



    };
}

#endif //ZAPPY_PARSER_H
