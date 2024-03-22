#ifndef TOWER_H
#define TOWER_H

#include "cub.h"

struct tower {
    int sz;
    Cub<int> bd;
    Mat<int> top;
    tower(int n)
        : sz(n) 
    {
        bd = Cub<int>(n, Mat<int>(n, Vec<int>(n)));
        top = Mat<int>(n, Vec<int>(n));
    }
};

#endif