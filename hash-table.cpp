#include "pair.h"
#include "hash-table.h"
#include <cstdlib>

int f(int k, int s) {
    return (k % s * 77 + 2222) % s;
}

int insert(hash_table &ht, int k, int idx) {
    int p = f(k, ht.s);
    for(int i{0}; i <= ht.c; ++i) {
        if(ht.data[p][i].val == k) {
            return (1 << 20) + i;
        }
    }

    for(int i{0}; i <= ht.c; ++i) {
        if(ht.data[p][i].val == 0) {
            ht.data[p][i].val = k;
            ht.data[p][i].idx = idx;
            return 0;
        }
    }
    exit(-1);
}

bool erase(hash_table &ht, int val, int idx, pair &this_pair) {
    int ret{insert(ht, val, idx)};
    if(!ret) return false;
    this_pair.val = val;
    this_pair.first_pos = idx;
    int p = f(this_pair.val, ht.s);
    this_pair.second_pos = ht.data[f(this_pair.val, ht.s)][ret ^ (1 << 20)].idx;
    ht.data[p][ret ^ (1 << 20)].val = 0;
    ht.data[p][ret ^ (1 << 20)].idx = 0;
    return true;
}