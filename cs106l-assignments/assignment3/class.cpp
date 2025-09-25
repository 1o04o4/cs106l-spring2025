#include "class.h"

TwoNum::TwoNum(int a, int b) {
    _a = a;
    _b = b;
}

TwoNum::TwoNum() {
    _a = 0;
    _b = 0;
}

int TwoNum::get_a() const {
    return _a;
}

int TwoNum::get_b() const {
    return _b;
}

void TwoNum::set_a(int value) {
    _a = value;
}

void TwoNum::set_b(int value) {
    _b = value;
}

bool TwoNum::is_equal() const {
    return _a == _b;
}