#include <iostream>
#include "cub.h"
#include "hash-table.h"
#include "tower.h"
#include "pair.h"

void print_answer(Vec<int> &ans) {
    for(size_t i{0}; i < ans.size(); ++i) {
        std::cout << ans[i] << " \n"[i == ans.size() - 1];
    }
}

int main(void) {
    int n, s, c;
    std::cin >> n >> s >> c;

    tower tow(n, s, c);
    Vec<int> ans;

    pair first_pair{tow.input_insert()};
    tow.find_pair(first_pair, ans);
    print_answer(ans);
}