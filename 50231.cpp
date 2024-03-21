#include <iostream>
#include <vector>
#include <utility>

template<typename T> using Vec = std::vector<T>;
template<typename T> using Mat = Vec<Vec<T>>;
template<typename T> using Cub = Vec<Mat<T>>;

int f(int k, int s) {
    return (k % s * 77 + 2222) % s;
}

int insert(
    Cub<int> &ht, 
    int k, int s, int c, 
    int idx
) {
    int p = f(k, s);
    for(int i{0}; i <= c; ++i) {
        if(ht[p][i][0] == k) {
            return (1 << 20) + i;
        }
    }

    for(int i{0}; i <= c; ++i) {
        if(ht[p][i][0] == 0) {
            ht[p][i][0] = k;
            ht[p][i][1] = idx;
            return 0;
        }
    }
}

std::pair<int, int> input_insert(
    Cub<int> &ht, const int &s, const int &c, Cub<int> &bd, Mat<int> &top, int &first
) {
    int first_pos, second_pos, ret;
    for(int i{0}; i < bd.size(); ++i) {
        for(int j{0}; j <= i; ++j) {
            for(int k{0}; k <= i; ++k) {
                std::cin >> bd[i][j][k];
                if(j == i || k == i) {
                    ret = insert(ht, bd[i][j][k], s, c, (j << 8) + k);
                    if(ret) {
                        first = bd[i][j][k];
                        first_pos = (j << 8) + k;
                        int p = f(first, s);
                        second_pos = ht[p][ret ^ (1 << 20)][1];
                        ht[p][ret ^ (1 << 20)][0] = 0;
                        ht[p][ret ^ (1 << 20)][1] = 0;
                    }
                }
                
                top[j][k] = j > k  ?  j  :  k;
            }
        }
    }
    return {first_pos, second_pos};
}

int find_pair(
    int &first, int &first_pos, int &second_pos, 
    Cub<int> &ht, const int &s, const int &c, Cub<int> &bd, Mat<int> &top,
    Vec<int> &ans
) {
    int idx = 0;
    while(true) {
        ans[idx++] = first;
        int fr = first_pos >> 8, fc = first_pos & ((1 << 8) - 1);
        int sr = second_pos >> 8, sc = second_pos & ((1 << 8) - 1);

        top[fr][fc]++;
        top[sr][sc]++;

        bool find_new = false;
        if(top[fr][fc] < bd.size()) {
            int ret{insert(ht, bd[top[fr][fc]][fr][fc], s, c, (fr << 8) + fc)};
            if(ret) {
                find_new = true;
                first = bd[top[fr][fc]][fr][fc];
                first_pos = (fr << 8) + fc;
                int p = f(first, s);
                second_pos = ht[f(first, s)][ret ^ (1 << 20)][1];
                ht[p][ret ^ (1 << 20)][0] = 0;
                ht[p][ret ^ (1 << 20)][1] = 0;
                continue;
            }
        }

        if(top[sr][sc] < bd.size()) {
            int ret{insert(ht, bd[top[sr][sc]][sr][sc], s, c, (sr << 8) + sc)};
            if(ret) {
                find_new = true;
                first = bd[top[sr][sc]][sr][sc];
                first_pos = (sr << 8) + sc;
                int p = f(first, s);
                second_pos = ht[p][ret ^ (1 << 20)][1];
                ht[p][ret ^ (1 << 20)][0] = 0;
                ht[p][ret ^ (1 << 20)][1] = 0;
                continue;
            }
        }

        if(!find_new) {
            break;
        }
    }
    return idx;
}

int main(void) {
    int n, s, c;
    std::cin >> n >> s >> c;

    Cub<int> ht(20010, Mat<int>(c, Vec<int>(2)));
    Cub<int> bd(n, Mat<int>(n, Vec<int>(n)));
    Mat<int> top(n, Vec<int>(n));
    Vec<int> ans(10000010);

    int first{0}, ret{0};
    std::pair<int, int> pos{input_insert(ht, s, c, bd, top, first)};
    int &first_pos{pos.first};
    int &second_pos{pos.second};

    int ans_num{find_pair(first, first_pos, second_pos, ht, s, c, bd, top, ans)};

    for(int i = 0; i < ans_num; ++i) {
        std::cout << ans[i] << " \n"[i == ans_num - 1];
    }
}