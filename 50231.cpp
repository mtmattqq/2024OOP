#include <iostream>
#include <vector>
#include <utility>
#include "cub.h"
#include "cube.h"
#include "hash-table.h"
#include "tower.h"
#include "pair.h"
#include "position.h"

pair input_insert(hash_table &ht, tower &tow) {
    pair ret;
    for(int i{0}; i < tow.bd.size(); ++i) {
        for(int j{0}; j <= i; ++j) {
            for(int k{0}; k <= i; ++k) {
                std::cin >> tow.bd[i][j][k];
                if(j == i || k == i) {
                    int pos = insert(ht, tow.bd[i][j][k], (j << 8) + k);
                    if(pos) {
                        ret.val = tow.bd[i][j][k];
                        ret.first_pos = (j << 8) + k;
                        int p = f(ret.val, ht.s);
                        ret.second_pos = ht.data[p][pos ^ (1 << 20)].idx;
                        ht.data[p][pos ^ (1 << 20)].val = 0;
                        ht.data[p][pos ^ (1 << 20)].idx = 0;
                    }
                }
                
                tow.top[j][k] = std::max(j, k);
            }
        }
    }
    return ret;
}

void find_pair(pair first_pair, hash_table &ht, tower &tow, Vec<int> &ans) {
    while(true) {
        ans.push_back(first_pair.val);
        int fr = first_pair.first_pos >> 8, fc = first_pair.first_pos & ((1 << 8) - 1);
        int sr = first_pair.second_pos >> 8, sc = first_pair.second_pos & ((1 << 8) - 1);

        tow.top[fr][fc]++;
        tow.top[sr][sc]++;

        bool find_new = false;
        if(tow.top[fr][fc] < tow.bd.size()) {
            if(erase(ht, tow.bd[tow.top[fr][fc]][fr][fc], (fr << 8) + fc, 
                first_pair))
                continue;
        }

        if(tow.top[sr][sc] < tow.bd.size()) {
            if(erase(ht, tow.bd[tow.top[sr][sc]][sr][sc], (sr << 8) + sc, 
                first_pair))
                continue;
        }

        if(!find_new) {
            break;
        }
    }
}

void print_answer(Vec<int> &ans) {
    for(int i{0}; i < ans.size(); ++i) {
        std::cout << ans[i] << " \n"[i == ans.size() - 1];
    }
}

int main(void) {
    int n, s, c;
    std::cin >> n >> s >> c;

    hash_table ht(s, c);
    tower tow(n);
    Vec<int> ans;

    pair first_pair{input_insert(ht, tow)};

    find_pair(first_pair, ht, tow, ans);
    print_answer(ans);
}