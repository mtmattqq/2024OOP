#include "pair.h"
#include "position.h"
#include "hash-table.h"
#include <cstdlib>

int hash_table::hash_function(int k, int s) {
    return (k % s * 77 + 2222) % s;
}

Result hash_table::insert(int k, position idx) {
    int p = hash_function(k, s);
    for(int i{0}; i <= c; ++i) {
        if(data[p][i].val == k) {
            return Result(i);
        }
    }

    for(int i{0}; i <= c; ++i) {
        if(data[p][i].val == 0) {
            data[p][i].val = k;
            data[p][i].idx = idx;
            return Result("Not found");
        }
    }
    exit(-1);
}

bool hash_table::find_erase(int val, position idx, pair &this_pair) {
    Result ret{insert(val, idx)};
    if(ret.err()) {
        return false;
    }
    this_pair.val = val;
    this_pair.first_pos = idx;
    int p = hash_function(this_pair.val, s);
    this_pair.second_pos = data[p][ret.unwrap()].idx;
    data[p][ret.unwrap()].val = 0;
    data[p][ret.unwrap()].idx = position{0, 0};
    return true;
}