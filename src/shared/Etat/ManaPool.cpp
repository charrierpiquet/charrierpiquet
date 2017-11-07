#include "ManaPool.h"
#include <iostream>

namespace Etat
{
    void ManaPool::AddInc()
    {
        inc ++;
    }
    void ManaPool::AddBlue()
    {
        blue ++;
    }
    void ManaPool::AddBlack()
    {
        black ++;
    }
    void ManaPool::AddGreen()
    {
        green ++;
    }
    void ManaPool::AddMulti()
    {
        multi ++;
    }
    void ManaPool::Vider()
    {
        inc =0;
        blue =0;
        black =0;
        green =0;
        multi =0;
    }
    
    bool ManaPool::Payer(Cout cost)
    {
        int I=cost.GetInc(),B=cost.GetBlack(),U=cost.GetBlue(),G=cost.GetGreen();
        int tamponI = inc, tamponB = black, tamponU = blue, tamponG = green, tamponM = multi;
        if (I>=inc)
        {
            I -= inc;
            inc = 0;
        }
        else
        {
            inc -= I;
            I = 0;
        }
        
        if (B>=black)
        {
            B -= black;
            black = 0;
        }
        else
        {
            black -= B;
            B = 0;
        }
        
        if (U>=blue)
        {
            U -= blue;
            blue = 0;
        }
        else
        {
            blue -= U;
            U = 0;
        }
        
        if (G>=green)
        {
            G -= green;
            green = 0;
        }
        else
        {
            green -= G;
            G = 0;
        }
        
        if (G > 0 && multi > 0)
            if (G <=  multi)
            {
                multi -= G;
                G = 0;
            }

        
        if (B > 0 && multi > 0)
            if (B <=  multi)
            {
                multi -= B;
                B = 0;
            }
        
        if (U > 0 && multi > 0)
            if (U <=  multi)
            {
                multi -= U;
                U = 0;
            }

        
        if (I > 0 && (black > 0 || blue > 0 || green > 0 || multi >0 ))
        {
            if (I <=  black)
            {
                black -= I;
                I = 0;
            }
            else
            {
                I -= black;
                black = 0;
                if (I <=  blue)
                {
                    blue -= I;
                    I = 0;
                }
                else
                {
                    I -= blue;
                    blue = 0;
                    if (I <=  green)
                    {
                        green -= I;
                        I = 0;
                    }
                    else
                    {
                        I -= green;
                        green = 0;
                    }
                }
            }
        }

        if (I>0 || B >0 || U >0 || G>0)
        {
            inc = tamponI;
            black = tamponB;
            blue = tamponU;
            green = tamponG;
            multi = tamponM;
            return false;
        }
        return true;
    }
    
    int ManaPool::GetInc() const
    {
        return inc;
    }
    int ManaPool::GetBlack() const
    {
        return black;
    }
    int ManaPool::GetBlue() const
    {
        return blue;
    }
    int ManaPool::GetGreen() const
    {
        return green;
    }
    int ManaPool::GetMulti() const
    {
        return multi;
    }
};

