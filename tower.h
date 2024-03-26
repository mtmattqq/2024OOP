#ifndef TOWER_H
#define TOWER_H

#include "cub.h"
#include "position.h"
#include "pair.h"
#include "hash-table.h"

class tower {
private:
    int sz;
    Cub<int> bd;
    Mat<int> tp;
public:
    tower(int n)
        : sz(n) 
    {
        bd = Cub<int>(n, Mat<int>(n, Vec<int>(n)));
        tp = Mat<int>(n, Vec<int>(n));
    }
    int size();
    int& operator[](position pos);
    int& top(position pos);
    pair input_insert(hash_table &ht);
    void find_pair(pair first_pair, hash_table &ht, Vec<int> &ans);
};

#endif