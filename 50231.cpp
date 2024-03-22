#include <iostream>
#include <vector>
#include <utility>

template<typename T> using Vec = std::vector<T>;
template<typename T> using Mat = Vec<Vec<T>>;
template<typename T> using Cub = Vec<Mat<T>>;

struct cube {
    int val, idx;
};

struct hash_table {
    Mat<cube> data;
    int s, c;
    hash_table(int seed, int cap)
        : s(seed), c(cap) 
    {
        data = Mat<cube>(20010, Vec<cube>(c, {0, 0}));
    }
};

struct tower {
    int sz;
    Cub<int> bd;
    Mat<int> top;
    tower(int n)
        : sz(n) 
    {
        bd = Cub<int>(n, Mat<int>(n, Vec<int>(n)));
        top = Mat<int>(n, Vec<int>(n));
    }
};

struct pair {
    int val;
    int first_pos, second_pos;
};

struct position {
    int row, col;
    position(int r, int c)
        : row(r), col(c) {}
};

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
    int idx = 0;
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
    for(int i = 0; i < ans.size(); ++i) {
        std::cout << ans[i] << " \n"[i == ans.size() - 1];
    }
}

int main(void) {
    int n, s, c;
    std::cin >> n >> s >> c;

    hash_table ht(s, c);
    tower tow(n);
    Vec<int> ans(10000010);

    int first{0};
    pair first_pair{input_insert(ht, tow)};

    find_pair(first_pair, ht, tow, ans);
    print_answer(ans);
}