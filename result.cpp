#include "result.h"
#include <string>

T Result::unwrap() {
    return val;
}

std::string Result::repr() {
    return err_msg;
}

bool Result::ok() {
    return type == OK;
}

bool Result::err() {
    return type == ERR;
}

