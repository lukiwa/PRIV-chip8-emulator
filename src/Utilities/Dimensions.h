#pragma once

struct Dimensions {
    Dimensions()
        : x(0)
        , y(0)
        , z(0)
    {
    }
    Dimensions(int x, int y, int z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    int x;
    int y;
    int z;
};