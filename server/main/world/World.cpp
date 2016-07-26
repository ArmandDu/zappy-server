//
// Created by armanddu on 28/06/16.
//

#include <iostream>
#include "World.h"

namespace  zappy {

    const Resource World::Resources::Food = zappy::Resource(0, "nourriture");
    const Resource World::Resources::Linemate = zappy::Resource(1, "linemate");
    const Resource World::Resources::Deraumere = zappy::Resource(2, "deraumere");
    const Resource World::Resources::Sibur = zappy::Resource(3, "sibur");
    const Resource World::Resources::Mendiane = zappy::Resource(4, "mendiane");
    const Resource World::Resources::Phiras = zappy::Resource(5, "phiras");
    const Resource World::Resources::Thystame = zappy::Resource(6, "thystame");

    const std::vector<Resource> World::Resources::resources = { World::Resources::Food,
                                                                World::Resources::Linemate,
                                                                World::Resources::Deraumere,
                                                                World::Resources::Sibur,
                                                                World::Resources::Mendiane,
                                                                World::Resources::Phiras,
                                                                World::Resources::Thystame };

    World::World(const Rect &size): width(size.width),
                                    height(size.height){
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                Square square;
                map.emplace(Point(x, y), square);
            }
        }
    }

    template <>
    void World::generateResources<World::Fertility::Abundant>() {

        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                Square &square = getSquare(x, y);
                square.setResource(World::Resources::Food, 10);
                square.setResource(World::Resources::Linemate, 10);
                square.setResource(World::Resources::Deraumere, 10);
                square.setResource(World::Resources::Sibur, 10);
                square.setResource(World::Resources::Mendiane, 10);
                square.setResource(World::Resources::Thystame, 10);
                square.setResource(World::Resources::Phiras, 10);
            }
        }
    }

    template <>
    void World::generateResources<World::Fertility::Moderate>() {
        int iterations = 15 + (int) (1.50 * (rand() % (width * height) / 2));
        unsigned long size = World::Resources::resources.size();
        for (int i = 0; i < iterations; ++i) {
            auto x = rand() % width;
            auto y = rand() % height;
            int resource = (int) (rand() % size);
            map[Point(x, y)].addResource(World::Resources::getById(resource), 1);
        }
    }

    template <>
    void World::generateResources<World::Fertility::Infertile>() {

        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                Square &square = getSquare(x, y);
                square.setResource(World::Resources::Food, 0);
                square.setResource(World::Resources::Linemate, 0);
                square.setResource(World::Resources::Deraumere, 0);
                square.setResource(World::Resources::Sibur, 0);
                square.setResource(World::Resources::Mendiane, 0);
                square.setResource(World::Resources::Thystame, 0);
                square.setResource(World::Resources::Phiras, 0);
            }
        }
    }

    Rect World::getSize() const { return Rect(width, height, 0, 0); }

    Square &World::getSquare(int x, int y) { return map[Point(x, y)]; }

    const zappy::Resource &World::Resources::getById(int i) {
        for (auto &r: resources) {
            if (r.getId() == i) return r;
        }
        return resources[-1];
    }

}

