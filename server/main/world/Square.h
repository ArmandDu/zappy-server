//
// Created by armanddu on 02/07/16.
//

#ifndef ZAPPY_CLIENT_SQUARE_H
#define ZAPPY_CLIENT_SQUARE_H


#include <map>
#include "Resource.h"

namespace zappy {
    class Square {

    private:
        std::map<Resource , int > stocks;

    public:
        Square();

    public:
        void addResource(const Resource &resource, int quantity);
        void setResource(const Resource &resource, int quantity);

        int getQuantity(const Resource &resource);
    };
}


#endif //ZAPPY_CLIENT_SQUARE_H
