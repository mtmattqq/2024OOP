#ifndef POSITION_H
#define POSITION_H

struct position {
    int row, col;
    position(int r, int c)
        : row(r), col(c) {}
};

#endif