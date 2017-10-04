#include "Cout.h"
#include <math>
namespace Etat
{
    int Cout::GetBlack()
    {
        return black;
    }
    int Cout::GetLife()
    {
        return life;
    }
    int Cout::GetBlue()
    {
        return blue;
    }
    int Cout::GetGreen()
    {
        return green;
    }
    int Cout::GetDiscard()
    {
        return discard;
    }
    int Cout::GetMeule()
    {
        return meule;
    }
    int Cout::GetExile()
    {
        return exile;
    }
    int Cout::GetInc()
    {
        return inc;
    }
    int Cout::GetPermanent()
    {
        return permanent;
    }
    void Cout::SetCost(int Inc = 0, int Blue = 0, int Black = 0, int Green = 0, 
            int Discard = 0, int Life = 0, int Permanent = 0, int Exile = 0, int Meule = 0)
    {
        inc = std::max(Inc,0);
        blue = std::max(Blue,0);
        black = std::max(Black,0);
        green = std::max(Green,0);
        discard = std::max(Discard,0);
        life = std::max(Life,0);
        permanent = std::max(Permanent,0);
        exile = std::max(Exile,0);
        meule = std::max(Meule,0);
    }
    
};