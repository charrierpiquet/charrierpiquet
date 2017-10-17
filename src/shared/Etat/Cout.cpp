#include "Cout.h"
#include <algorithm>
namespace Etat
{
    int Cout::GetBlack() const
    {
        return black;
    }
    int Cout::GetLife() const
    {
        return life;
    }
    int Cout::GetBlue() const
    {
        return blue;
    }
    int Cout::GetGreen() const
    {
        return green;
    }
    int Cout::GetDiscard() const
    {
        return discard;
    }
    int Cout::GetMeule() const
    {
        return meule;
    }
    int Cout::GetExile() const
    {
        return exile;
    }
    int Cout::GetInc() const
    {
        return inc;
    }
    int Cout::GetPermanent() const
    {
        return permanent;
    }
    void Cout::SetCost(int Inc , int Blue , int Black , int Green , 
            int Discard , int Life , int Permanent , int Exile , int Meule)
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