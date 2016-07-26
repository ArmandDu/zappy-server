//
// Created by armanddu on 29/06/16.
//

#include <iostream>
#include <cmath>
#include "Player.h"

namespace zappy {


    const std::string Player::Message::deadMessage = "mort";

    const double Player::Command::Duration::Default = 7.0;
    const double Player::Command::Duration::eatDuration = 126.0;

    const double Player::Command::Duration::Move = Player::Command::Duration::Default;
    const double Player::Command::Duration::TurnLeft = Player::Command::Duration::Default;
    const double Player::Command::Duration::TurnRight = Player::Command::Duration::Default;
    const double Player::Command::Duration::See = Player::Command::Duration::Default;
    const double Player::Command::Duration::Inventory = Player::Command::Duration::Default;
    const double Player::Command::Duration::Take = Player::Command::Duration::Default;
    const double Player::Command::Duration::Put = Player::Command::Duration::Default;
    const double Player::Command::Duration::Broadcast = Player::Command::Duration::Default;
    const double Player::Command::Duration::Expel = Player::Command::Duration::Default;
    const double Player::Command::Duration::Incantation = 300.0;
    const double Player::Command::Duration::Fork = 42.0;
    const double Player::Command::Duration::ConnectNbr = 0;

    const std::string Player::Command::Move = "avance";
    const std::string Player::Command::TurnLeft = "gauche";
    const std::string Player::Command::TurnRight = "droite";
    const std::string Player::Command::See = "voir";
    const std::string Player::Command::Inventory = "inventaire";
    const std::string Player::Command::Take = "prend";
    const std::string Player::Command::Put = "pose";
    const std::string Player::Command::Expel = "expulse";
    const std::string Player::Command::Broadcast = "broadcast";
    const std::string Player::Command::Incantation = "incantation";
    const std::string Player::Command::Fork = "fork";
    const std::string Player::Command::ConnectNbr = "connect_nbr";

    Player::Command::Command(const std::string &message,
                             double timeout,
                             const std::function<void()> &cb): message_(message),
                                                               timeout_(timeout),
                                                               callback_(cb){

    }

    const std::string Player::Command::getMessage() const {
        return message_;
    }

    const double Player::Command::getTimeout() const {
        return timeout_;
    }

    const std::function<void()> &Player::Command::getCallback() const {
        return callback_;
    }


    const std::map<Player::Orientation, std::pair<int, int>> Player::forwardMatrix =
            {{North, {0, -1}},
             {East, {1, 0}},
             {South, {0, 1}},
             {West, {-1, 0}}
            };
    const std::map<Player::Orientation, Player::Orientation> Player::leftMatrix = {{North, West},
                                                                                   {West, South},
                                                                                   {South, East},
                                                                                   {East, North}};

    const std::map<Player::Orientation, Player::Orientation> Player::rightMatrix = {{North, East},
                                                                                    {East, South},
                                                                                    {South, West},
                                                                                    {West, North}};


    Player::Player(my_tcp::Client::Session session, const Rect &size,
                   const Point &position, Player::Orientation orientation) : Actor(session),
                                                                             size_(size),
                                                                             position_(position),
                                                                             orientation_(orientation),
                                                                             level_(1),
                                                                             dead_(false) {
    }

    Inventory &Player::getInventory() {
        return inventory_;
    }

    bool Player::isDead(double deltaTime) {
        if (deltaTime <= 0) return dead_;
        return (dead_ = inventory_.getStock(World::Resources::Food) == 0 &&
                        hunger_.ready(deltaTime));
    }

    void Player::updateAppetite(double deltaTime) {
        if ((hunger_.empty() || hunger_.ready(deltaTime)) && inventory_.consume(World::Resources::Food)) {
            hunger_.reset();
            auto message = "Consuming food (left: " +
                           std::to_string(inventory_.getStock(World::Resources::Food)) +
                           ")";
            hunger_.start(Player::Command::Duration::eatDuration, message, [](){});
        }
    }

    void  Player::disconnect() {
        if (!exited) {
            commandTimeout_.reset();
            hunger_.reset();
            session.disconnect();
            exited = true;
        }
    }

    Point Player::getPosition()const {
        return position_;
    }

    const Player::Orientation & Player::getOrientation()const {
        return orientation_;
    }

    void Player::forward() {
        forward(getOrientation());
    }

    void Player::forward(const Player::Orientation &orientation) {
        position_.x = (size_.width + position_.x + Player::forwardMatrix.at(orientation).first) % size_.width;
        position_.y = (size_.height + position_.y + Player::forwardMatrix.at(orientation).second) % size_.height;
    }


    void Player::left() {
        orientation_ = leftMatrix.at(orientation_);
    }

    void Player::right() {
        orientation_ = rightMatrix.at(orientation_);
    }

    const int Player::getLevel() const {
        return level_;
    }

    bool Player::startCmdTimeout(const std::string &message, double timeout, const std::function<void()> &cb,
                                 Player::Command::Priority priority) {
        if (isBusy() && priority != Player::Command::Priority::Absolute) {
            Command command = Command(message, timeout, cb);
            addCommand(command, priority);
            return false;
        }
        commandTimeout_.reset();
        return commandTimeout_.start(timeout, message, cb);    }

    bool Player::startCmdTimeout(const std::string &message, double timeout, const std::function<void()> &cb){
        return startCmdTimeout(message, timeout, cb, Player::Command::Priority::Low);
    }

    bool Player::startCmdTimeout(const Command &command){
        return startCmdTimeout(command.getMessage(), command.getTimeout(), command.getCallback());
    }

    void Player::updateCmdTimeout(double deltaTime) {
        if (!commandTimeout_.empty() && commandTimeout_.ready(deltaTime)) {
            auto function = commandTimeout_.getCallback();
            function();
            commandTimeout_.reset();
        }

    }


    const std::string Player::getTeamName() const {
        return teamName_;
    }

    void Player::setTeamName(const std::string &teamName) {
        this->teamName_ = teamName;
    }

    void Player::levelUp() {
        level_ += 1;
    }

    bool Player::isBusy() {
        return !commandTimeout_.empty();
    }

    void Player::addCommand(Player::Command command, Player::Command::Priority priority) {
        if (commands_.size() < maxCommandSize) {
            if (priority == Player::Command::Priority::Low) commands_.push_back(command);
            else if (priority == Player::Command::Priority::High) commands_.push_front(command);
        }
    }

    Player::Command Player::popCommand() {
        Player::Command command = commands_.front();
        commands_.pop_front();
        return command;
    }

    bool Player::hasCommand() const {
        return !commands_.empty();
    }

    void Player::setIncanting(bool incanting) {
        incanting_ = incanting;
    }

    bool Player::isIncanting() const {
        return incanting_;
    }

    const std::map<Player::Orientation, int> Player::angleMatrix = {{Player::Orientation::North, 6},
                                                                    {Player::Orientation::West, 4},
                                                                    {Player::Orientation::South, 2},
                                                                    {Player::Orientation::East, 8}};

    const double Player::zappyAngle = 57.2958 / 45; // 180 / PI

    int Player::getAngle(Player &source) {
        if (source.getPosition() == getPosition()) return 0;
        int x0 = (source.getPosition().x - getPosition().x);
        int y0 = (source.getPosition().y - getPosition().y);
        int dx = std::min(x0, size_.width - x0);
        int dy = std::min(y0, size_.height - y0);
        int angle = (std::atan2(dy, dx)) * zappyAngle;
        return 1 + (std::abs(angle - angleMatrix.at(getOrientation()))) % 8;
    }



}