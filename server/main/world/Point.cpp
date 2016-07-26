//
// Created by armanddu on 30/06/16.
//

#include "Point.h"

namespace  zappy {

    Point::Point() : x(0), y(0)  {}

    Point::Point(int x, int y): x(x), y(y) { }

    bool zappy::Point::operator<(const Point &b) const {
        return (x < b.x) ||  (x == b.x &&  y < b.y);
    }

    bool Point::operator==(const Point &point) const {
        return x == point.x && y == point.y;
    }

}

