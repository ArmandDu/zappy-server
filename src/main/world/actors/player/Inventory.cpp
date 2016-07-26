//
// Created by armanddu on 28/06/16.
//

#include <sstream>
#include <iostream>

#include "Inventory.h"

namespace zappy {

    Inventory::Inventory() {
        stocks[World::Resources::Food] = 10;
        stocks[World::Resources::Deraumere] = 0;
        stocks[World::Resources::Linemate] = 0;
        stocks[World::Resources::Mendiane] = 0;
        stocks[World::Resources::Phiras] = 0;
        stocks[World::Resources::Sibur] = 0;
        stocks[World::Resources::Thystame] = 0;
    }

    int Inventory::getStock(const Resource &resource)const {
        return stocks.at(resource);
    }


    std::string &operator<<(std::string &str, const zappy::Inventory &i) {
        std::stringstream os;

        os << "{" << World::Resources::Food.getName() << " " << i.getStock(World::Resources::Food);
        os << ", "<< World::Resources::Linemate.getName() << " " << i.getStock(World::Resources::Linemate);
        os << ", "<< World::Resources::Deraumere.getName() << " " << i.getStock(World::Resources::Deraumere);
        os << ", "<< World::Resources::Sibur.getName() << " " << i.getStock(World::Resources::Sibur);
        os << ", "<< World::Resources::Mendiane.getName() << " " << i.getStock(World::Resources::Mendiane);
        os << ", "<< World::Resources::Phiras.getName() << " " << i.getStock(World::Resources::Phiras);
        os << ", "<< World::Resources::Thystame.getName() << " " << i.getStock(World::Resources::Thystame);
        os << "}";
        str += os.str();
        return str;
    }

    std::ostream &operator<<(std::ostream &os, const Inventory &i) {
        os << i;
        return os;
    }

    bool Inventory::consume(Resource resource) {
        if (stocks[resource] > 0) {
            stocks[resource] -= 1;
            return true;
        }
        return false;
    }

    void Inventory::addStock(const Resource &resource, int i) {
        stocks[resource] += i;
    }


}


