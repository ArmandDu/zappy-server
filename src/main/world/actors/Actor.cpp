//
// Created by armanddu on 07/07/16.
//

#include "Actor.h"

namespace zappy {

    const std::string Actor::Message::Ko = "ko";
    const std::string Actor::Message::OK = "ok";

    const std::string Actor::Message::MSG_WELCOME = "BIENVENUE";


    Actor::Actor(my_tcp::Client::Session session) : session(session), exited(false) { }

    std::string Actor::getId() const {
        return session.getClient().getId();
    }

    bool Actor::operator==(const Actor &p) {
        return getId() == p.getId();
    }


    my_tcp::Client::Session & Actor::getSession() {
        return session;
    }



}