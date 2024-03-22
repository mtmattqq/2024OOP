#ifndef CUB_H
#define CUB_H

#include <vector>

template<typename T> using Vec = std::vector<T>;
template<typename T> using Mat = Vec<Vec<T>>;
template<typename T> using Cub = Vec<Mat<T>>;

#endif