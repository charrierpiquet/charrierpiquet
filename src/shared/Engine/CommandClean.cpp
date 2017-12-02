#include "CommandClean.h"

namespace Engine
{
    CommandClean::CommandClean(std::shared_ptr<Etat::Creature> crea)
    {
        idCrea = crea->GetIdObj();
        bonusEOT = crea->GetBonusEOT();
        blessure = crea->GetBlessure();
    }
    void CommandClean::Execute(std::shared_ptr<Etat::State> state)
    {
        for (unsigned int i = 0 ; i < state->GetBattlefield().size() ; i++)
            if (idCrea == state->GetBattlefield()[i]->GetIdObj())
            {
                std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i])->SetBonusEOT(0);
                std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i])->SetBlessure(0);
            }
    }
    void CommandClean::Undo(std::shared_ptr<Etat::State> state)
    {
        for (unsigned int i = 0 ; i < state->GetBattlefield().size() ; i++)
            if (idCrea == state->GetBattlefield()[i]->GetIdObj())
            {
                std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i])->SetBonusEOT(bonusEOT);
                std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i])->SetBlessure(blessure);
            }
    }
}