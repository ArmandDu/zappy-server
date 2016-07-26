//
// Created by armanddu on 28/06/16.
//

#ifndef ZAPPY_CLIENT_INVENTORY_H
#define ZAPPY_CLIENT_INVENTORY_H

#include <string>
#include <set>
#include "../../World.h"

namespace zappy {
    class Inventory {

    private:
        std::map<Resource, int> stocks;

    public:
        Inventory();

    public:
        int getStock(const Resource &resource)const;
        void addStock(const Resource &resource, int i);

    public:
        friend std::string &operator<<(std::string &str, const Inventory &i);
        friend std::ostream &operator<<(std::ostream &os, const Inventory &i);

        bool consume(Resource resource);
    };
}

#endif //ZAPPY_CLIENT_INVENTORY_H
