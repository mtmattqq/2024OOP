#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "cub.h"
#include "cube.h"
#include "pair.h"
#include "position.h"
#include "result.h"


class hash_table {
private:
    Mat<cube> data;
    int s, c;
    int hash_function(const int k, const int s) const;
public:
    hash_table(const int seed, const int cap)
        : s(seed), c(cap) 
    {
        data = Mat<cube>(20010, Vec<cube>(c, {0, {0, 0}}));
    };
    Result insert(const int k, const position idx);
    bool find_erase(const int val, const position idx, pair &this_pair);
};

#endif