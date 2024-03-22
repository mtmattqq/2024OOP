#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "cub.h"
#include "cube.h"
#include "pair.h"

struct hash_table {
    Mat<cube> data;
    int s, c;
    hash_table(int seed, int cap)
        : s(seed), c(cap) 
    {
        data = Mat<cube>(20010, Vec<cube>(c, {0, 0}));
    }
};

int f(int k, int s);
int insert(hash_table &ht, int k, int idx);
bool erase(hash_table &ht, int val, int idx, pair &this_pair);

#endif