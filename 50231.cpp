#include <iostream>
#include <vector>

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
    for(int i = 0; i <= c; ++i) {
        if(ht[p][i][0] == k) {
            return (1 << 20) + i;
        }
    }

    for(int i = 0; i <= c; ++i) {
        if(ht[p][i][0] == 0) {
            ht[p][i][0] = k;
            ht[p][i][1] = idx;
            return 0;
        }
    }
}

int main(void) {
    int n, s, c;
    std::cin >> n >> s >> c;

    Cub<int> ht(20010, Mat<int>(10, Vec<int>(2)));
    Cub<int> bd(110, Mat<int>(110, Vec<int>(110)));
    Mat<int> top(110, Vec<int>(110));
    Vec<int> ans(10000010);

    int first = 0, first_pos, second_pos, ret;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= i; ++j) {
            for(int k = 0; k <= i; ++k) {
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

    int idx = 0;
    while(true) {
        ans[idx++] = first;
        int fr = first_pos >> 8, fc = first_pos & ((1 << 8) - 1);
        int sr = second_pos >> 8, sc = second_pos & ((1 << 8) - 1);

        top[fr][fc]++;
        top[sr][sc]++;

        ret = 0;
        bool find_new = false;
        if(top[fr][fc] < n) {
            ret = insert(ht, bd[top[fr][fc]][fr][fc], s, c, (fr << 8) + fc);
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

        if(top[sr][sc] < n) {
            ret = insert(ht, bd[top[sr][sc]][sr][sc], s, c, (sr << 8) + sc);
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

    for(int i = 0; i < idx; ++i) {
        std::cout << ans[i] << " \n"[i == idx - 1];
    }
}