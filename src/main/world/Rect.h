//
// Created by armanddu on 26/06/16.
//

#ifndef ZAPPY_RECT_H
#define ZAPPY_RECT_H

namespace zappy {
    class Rect {

    public:
        Rect();

        Rect(int width, int height, int x, int y);

        int width;
        int height;
        int x;
        int y;

    };
}

#endif //ZAPPY_RECT_H
