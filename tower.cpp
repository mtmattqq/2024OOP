#include "tower.h"
#include "position.h"
#include <iostream>

int tower::size() {
    return sz;
}

int& tower::operator[](position pos) {
    return bd[top(pos)][pos.row][pos.col];
}

pair tower::input_insert() {
    pair ret{0, {0, 0}, {0, 0}};
    for(size_t i{0}; i < size(); ++i) {
        for(size_t j{0}; j <= i; ++j) {
            for(size_t k{0}; k <= i; ++k) {
                std::cin >> bd[i][j][k];
                if(j == i || k == i) {
                    ht.find_erase(bd[i][j][k], {int(j), int(k)}, ret);
                }
                tp[j][k] = std::max(j, k);
            }
        }
    }
    return ret;
}

void tower::find_pair(pair first_pair, Vec<int> &ans) {
    while(true) {
        ans.push_back(first_pair.val);

        // problematic
        top(first_pair.first_pos)++;
        top(first_pair.second_pos)++;

        bool find_new = false;
        if(top(first_pair.first_pos) < size()) {
            if(ht.find_erase(operator[](first_pair.first_pos), first_pair.first_pos, 
                first_pair))
                continue;
        }

        if(top(first_pair.second_pos) < size()) {
            if(ht.find_erase(operator[](first_pair.second_pos), first_pair.second_pos, 
                first_pair))
                continue;
        }

        if(!find_new) {
            break;
        }
    }
}