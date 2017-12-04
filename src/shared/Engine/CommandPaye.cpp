
#include "CommandPaye.h"
#include <iostream>
namespace Engine {

    CommandPaye::CommandPaye(std::shared_ptr<Etat::Cout> cout) {
        coutB = cout->GetBlack();
        coutU = cout->GetBlue();
        coutG = cout->GetGreen();
        coutI = cout->GetInc();
        coutPv = cout->GetLife();
    }

    void CommandPaye::Execute(std::shared_ptr<Etat::State> state) {
        mB = state->GetJoueurs()[state->GetPriority()]->GetManaPool()->GetBlack();
        mU = state->GetJoueurs()[state->GetPriority()]->GetManaPool()->GetBlue();
        mG = state->GetJoueurs()[state->GetPriority()]->GetManaPool()->GetGreen();
        mI = state->GetJoueurs()[state->GetPriority()]->GetManaPool()->GetInc();
        mM = state->GetJoueurs()[state->GetPriority()]->GetManaPool()->GetMulti();


        // on paye les PV
        state->GetJoueurs()[state->GetPriority()]->SetPv(state->GetJoueurs()[state->GetPriority()]->GetPv() - coutPv);

        int I = coutI, B = coutB, U = coutU, G = coutG;
        int tamponI = mI, tamponB = mB, tamponU = mU, tamponG = mG, tamponM = mM;
        //std::cout<<"\tinitialisation Ok ...";

        if (I >= tamponI) {
            I -= tamponI;
            tamponI = 0;
        } else {
            tamponI -= I;
            I = 0;
        }

        if (B >= tamponB) {
            B -= tamponB;
            tamponB = 0;
        } else {
            tamponB -= B;
            B = 0;
        }

        if (U >= tamponU) {
            U -= tamponU;
            tamponU = 0;
        } else {
            tamponU -= U;
            U = 0;
        }

        if (G >= tamponG) {
            G -= tamponG;
            tamponG = 0;
        } else {
            tamponG -= G;
            G = 0;
        }

        if (G > 0 && tamponM > 0)
            if (G <= tamponM) {
                tamponM -= G;
                G = 0;
            }


        if (B > 0 && tamponM > 0)
            if (B <= tamponM) {
                tamponM -= B;
                B = 0;
            }

        if (U > 0 && tamponM > 0)
            if (U <= tamponM) {
                tamponM -= U;
                U = 0;
            }


        if (I > 0 && (tamponB > 0 || tamponU > 0 || tamponG > 0 || tamponM > 0)) {
            if (I <= tamponB) {
                tamponB -= I;
                I = 0;
            } else {
                I -= tamponB;
                tamponB = 0;
                if (I <= tamponU) {
                    tamponU -= I;
                    I = 0;
                } else {
                    I -= tamponU;
                    tamponU = 0;
                    if (I <= tamponG) {
                        tamponG -= I;
                        I = 0;
                    } else {
                        I -= tamponG;
                        tamponG = 0;
                    }
                }
            }
        }

        if (I > 0 || B > 0 || U > 0 || G > 0) {
            Undo(state);
        } else {
            state->GetJoueurs()[state->GetPriority()]->GetManaPool()->SetBlack(tamponB);
            state->GetJoueurs()[state->GetPriority()]->GetManaPool()->SetBlue(tamponU);
            state->GetJoueurs()[state->GetPriority()]->GetManaPool()->SetGreen(tamponG);
            state->GetJoueurs()[state->GetPriority()]->GetManaPool()->SetInc(tamponI);
            state->GetJoueurs()[state->GetPriority()]->GetManaPool()->SetMulti(tamponM);
        }
    }

    void CommandPaye::Undo(std::shared_ptr<Etat::State> state) {
        state->GetJoueurs()[state->GetPriority()]->GetManaPool()->SetBlack(mB);
        state->GetJoueurs()[state->GetPriority()]->GetManaPool()->SetBlue(mU);
        state->GetJoueurs()[state->GetPriority()]->GetManaPool()->SetGreen(mG);
        state->GetJoueurs()[state->GetPriority()]->GetManaPool()->SetInc(mI);
        state->GetJoueurs()[state->GetPriority()]->GetManaPool()->SetMulti(mM);
        state->GetJoueurs()[state->GetPriority()]->SetPv(state->GetJoueurs()[state->GetPriority()]->GetPv() + coutPv);
    }

}