//
// Created by armanddu on 28/06/16.
//

#ifndef ZAPPY_CLIENT_WORLD_H
#define ZAPPY_CLIENT_WORLD_H


#include <vector>
#include <string>
#include <map>
#include "Rect.h"
#include "Point.h"
#include "Square.h"

namespace zappy {
    class World {


    public:
        class Resources {
        public:
            static const zappy::Resource Food;
            static const zappy::Resource Linemate;
            static const zappy::Resource Deraumere;
            static const zappy::Resource Sibur;
            static const zappy::Resource Mendiane;
            static const zappy::Resource Phiras;
            static const zappy::Resource Thystame;
        public:
            static const std::vector<zappy::Resource> resources;
        public:
            static const zappy::Resource &getById(int i);
        };

    public:
        enum Fertility {
            Infertile,
            Moderate,
            Abundant
        };
    private:
        int width;
        int height;
        std::map<Point, Square> map;

    public:
        World(const Rect &size);

    public:
        Rect getSize() const;
        Square & getSquare(int x, int y);

        template<Fertility B>
        void generateResources();

    };
}

#endif //ZAPPY_CLIENT_WORLD_H
