//
// Created by armanddu on 30/06/16.
//

#ifndef ZAPPY_CLIENT_VECTOR2_H
#define ZAPPY_CLIENT_VECTOR2_H


namespace zappy {

    class Point {

    public:
        int x;
        int y;

    public:
        Point();
        Point(int x, int y);

    public:
        bool operator<(const Point &b) const ;
        bool operator==(const Point &point) const;
    };

}

#endif //ZAPPY_CLIENT_VECTOR2_H
