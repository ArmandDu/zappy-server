//
// Created by armanddu on 26/06/16.
//

#include "Parser.h"

namespace  zappy {
    Parser::Parser(int ac, char **av): port(""), size(10, 10, 0, 0), teamCount(0), deltaTime(100), teams() {

        if (ac < 0 || av  == NULL) return ;
        int opt;
        this->path = av[0];
        while ((opt  = getopt(ac, av, "p:P:x:y:c:t:n:") ) != -1) {
            switch (opt) {
                case 'p':
                    this->port = optarg;
                    break;
                case 'P':
                    this->spectatorPort = optarg;
                    break;
                case 'x':
                    this->size.width = atoi(optarg);
                    break;
                case 'y':
                    this->size.height = atoi(optarg);
                    break;
                case 'c':
                    this->teamCount = atoi(optarg);
                    break;
                case 't':
                    this->deltaTime = atoi(optarg);
                    break;
                case 'n':
                    optind--;
                    for( ;optind < ac && *av[optind] != '-'; optind++){
                        teams.push_back( av[optind] );
                    }
                    break;
                default:break;
            }
        }
    }

    const std::string & Parser::getPort()const {
        return this->port;
    }

    const std::string &Parser::getSpectatorPort() const {
        return spectatorPort;
    }

    const Rect & Parser::getSize()const {
        return this->size;
    }

    const std::vector<std::string> & Parser::getTeams()const {
        return this->teams;
    }

    int Parser::getTeamCount()const {
        return teamCount;
    }

    int Parser::getDeltaTime()const {
        return deltaTime;
    }

    bool Parser::isValid()const {
        return !port.empty() && size.height > 0 && size.width > 0 && !teams.empty() && teamCount > 0;
    }

    std::ostream& operator<<(std::ostream& os, const Parser& obj)
    {
        os << "{\"port\": \"" << obj.getPort() << "\", \"width\": " << obj.getSize().width << ", \"height\": " << obj.getSize().height;
        os << ", \"teams\": [";
        for (int i = 0; i < obj.getTeams().size(); ++i) {
            os << "\"" << obj.teams[i] << "\"";
            if (i + 1 < obj.teams.size()) {
                os << ", ";
            }
        }
        os << "], \"teamCount\": " << obj.getTeamCount() << ", \"deltaTime\": " << obj.getDeltaTime();
        os << ", \"valid\": " << obj.isValid() << "}";
        return os;
    }

    std::string Parser::usage() {
        std::string usage;

        usage = "Usage: " + path.substr(path.rfind('/') + 1)
                + " -p port [-P spectatorPort] -x width -y height -n team1 [team 2 [...]] -c clientPerTeam -t deltaTime";
        return usage;
    }


}