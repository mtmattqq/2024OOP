#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "cub.h"
#include "cube.h"
#include "pair.h"
#include "result.h"


class hash_table {
private:
    Mat<cube> data;
    int s, c;
    int hash_function(int k, int s);
public:
    hash_table(int seed, int cap)
        : s(seed), c(cap) 
    {
        data = Mat<cube>(20010, Vec<cube>(c, {0, 0}));
    };
    Result insert(int k, int idx);
    bool find_erase(int val, int idx, pair &this_pair);
};

#endif