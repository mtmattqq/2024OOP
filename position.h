#ifndef POSITION_H
#define POSITION_H

class position {
private:
    int row, col;
public:
    position(const int r, const int c)
        : row(r), col(c) {}
    position(const position &pos) { position(pos.row, pos.col);}
    int get_row() const { return row;}
    int get_col() const { return col;}
};

#endif