#include "Cout.h"
#include <algorithm>
namespace Etat {

    Cout::Cout(int L, int I, int B, int U, int G) {
        inc = std::max(I, 0);
        blue = std::max(U, 0);
        black = std::max(B, 0);
        green = std::max(G, 0);
        life = std::max(L, 0);
    }

    int Cout::GetBlack() const {
        return black;
    }

    int Cout::GetLife() const {
        return life;
    }

    int Cout::GetBlue() const {
        return blue;
    }

    int Cout::GetGreen() const {
        return green;
    }


    int Cout::GetInc() const {
        return inc;
    }
};