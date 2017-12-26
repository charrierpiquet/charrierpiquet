#include "ManaPool.h"
#include <iostream>
#include <algorithm>

namespace Etat {

    void ManaPool::SetInc(int value) {
        inc = std::max(value, 0);;
    }

    void ManaPool::SetBlue(int value) {
        blue= std::max(value, 0);
    }

    void ManaPool::SetBlack(int value) {
        black= std::max(value, 0);
    }

    void ManaPool::SetGreen(int value) {
        green= std::max(value, 0);
    }

    void ManaPool::SetMulti(int value) {
        multi= std::max(value, 0);
    }

    int ManaPool::GetInc() const {
        return inc;
    }

    int ManaPool::GetBlack() const {
        return black;
    }

    int ManaPool::GetBlue() const {
        return blue;
    }

    int ManaPool::GetGreen() const {
        return green;
    }

    int ManaPool::GetMulti() const {
        return multi;
    }
};

