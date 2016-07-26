//
// Created by armanddu on 29/06/16.
//

#ifndef ZAPPY_CLIENT_PLAYER_H
#define ZAPPY_CLIENT_PLAYER_H

#include <map>
#include "../../../tcp/Client.h"
#include "Inventory.h"
#include "../Actor.h"
#include "../../../tcp/Request.h"

namespace zappy {
    class Player : public Actor{

    public:
        class Command {
        public:
            enum Priority {
                Low,
                High,
                Absolute
            };

            class Duration {
            public:
                static const double Move;
                static const double TurnLeft;
                static const double TurnRight;
                static const double See;
                static const double Inventory;
                static const double Take;
                static const double Put;
                static const double Broadcast;
                static const double Incantation;
                static const double Fork;
                static const double ConnectNbr;
                static const double eatDuration;
                static const double Expel;
            private:
                static const double Default;

            };
        public:
            static const std::string Move;
            static const std::string TurnLeft;
            static const std::string TurnRight;
            static const std::string See;
            static const std::string Inventory;
            static const std::string Take;
            static const std::string Put;
            static const std::string Expel;
            static const std::string Broadcast;
            static const std::string Incantation;
            static const std::string Fork;
            static const std::string ConnectNbr;

        private:
            const std::string message_;
            const double timeout_;
            const std::function<void()> callback_;

        public:
            Command(const std::string &message, double timeout, const std::function<void()> &cb);

        public:
            const std::string getMessage() const;
            const double getTimeout() const;
            const std::function<void()> &getCallback() const;

        };

        class Message : public Actor::Message {
        public:
            static const std::string deadMessage;
        };

        enum Orientation {
            North,
            East,
            South,
            West,
            __COUNT
        };

    private:
        static const long maxCommandSize = 10;
    private:
        static const std::map<Player::Orientation, std::pair<int, int>> forwardMatrix;
        static const std::map<Player::Orientation, Player::Orientation> leftMatrix;
        static const std::map<Player::Orientation, Player::Orientation> rightMatrix;
        static const std::map<Player::Orientation, int> angleMatrix;

        static const double zappyAngle;

    private:
        Inventory inventory_;
        Timeout hunger_;
        Timeout commandTimeout_;
        Point position_;
        Rect size_;
        Orientation orientation_;
        int level_;
        bool dead_;
        std::string teamName_;
        std::list<Command> commands_;
        bool incanting_;

    public:
        Player(my_tcp::Client::Session session, const Rect &size, const Point &position,
               Player::Orientation orientation);

    public:
        void disconnect();
        bool startCmdTimeout(const std::string &message, double timeout, const std::function<void()> &cb, Command::Priority priority);
        bool startCmdTimeout(const std::string &message, double timeout, const std::function<void()> &cb);
        bool startCmdTimeout(const Command &command);
        void updateCmdTimeout(double deltaTime);
        bool isBusy();
        void addCommand(Player::Command command, Player::Command::Priority priority);

    public:
        Inventory & getInventory();
        void updateAppetite(double deltaTime);

        bool isDead(double deltaTime);

        Point getPosition()const;
        const Orientation & getOrientation()const;
        const int getLevel() const;
        const std::string getTeamName() const;
        void setTeamName(const std::string &teamName);

    public:
        void forward();
        void left();
        void right();
        void levelUp();

        bool hasCommand() const;
        Command popCommand();

        void setIncanting(bool incanting);
        bool isIncanting() const;

        int getAngle(Player &source);

        void forward(const Orientation &orientation);
    };
}


#endif //ZAPPY_CLIENT_PLAYER_H
