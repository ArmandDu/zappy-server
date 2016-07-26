//
// Created by armanddu on 02/07/16.
//

#include "Square.h"
#include "World.h"

namespace zappy {

    Square::Square() {

        for (int i = 0; i < World::Resources::resources.size(); ++i) {
            stocks.emplace(World::Resources::getById(i), 0);
        }
    }

    void Square::addResource(const Resource &resource, int quantity) {
        stocks[resource] += quantity;
    }

    int Square::getQuantity(const Resource &resource) {
        return stocks[resource];
    }

    void Square::setResource(const Resource &resource, int quantity) {
        stocks[resource] = quantity;
    }


}

