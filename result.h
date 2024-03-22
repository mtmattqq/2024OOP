#ifndef RESULT_H
#define RESULT_H

#include <string>

enum Type {
    OK,
    ERR
};

using T = int;
class Result {
private:
    Type type;
    T val;
    std::string err_msg;
public:
    Result(T _val)
        : val(_val), type(OK) {}
    Result(const std::string &_err_msg = "")
        : type(ERR), err_msg(_err_msg) {}
    T unwrap();
    std::string repr();
    bool ok();
    bool err();
};

#endif