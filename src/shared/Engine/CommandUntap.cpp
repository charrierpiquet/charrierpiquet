#include "CommandUntap.h"
#include <iostream>

namespace Engine {
    
    CommandUntap::CommandUntap(std::shared_ptr<Etat::Carte> carte)
    {
        //std::cout<<"\t\tinit untap"<<std::endl;
        idCarte = carte->GetIdObj();
        wasTaped = carte->GetIsTap();
        if (carte->GetIsCreature())
            hadMalInvoc = std::static_pointer_cast<Etat::Creature>(carte)->GetMalInvoc();
        else
            hadMalInvoc = -1;
    }
    
    void CommandUntap::Execute(std::shared_ptr<Etat::State> state)
    {
        //std::cout<<"\t\texec untap"<<std::endl;
        for (unsigned int i = 0 ; i < state->GetBattlefield().size() ; i++ )
            if (state->GetBattlefield()[i]->GetIdObj() == idCarte)
            {
                state->GetBattlefield()[i]->SetIsTap(false);
                if (state->GetBattlefield()[i]->GetIsCreature())
                    std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i])->SetMalInvoc(false);
            }
    }
    
    void CommandUntap::Undo(std::shared_ptr<Etat::State> state)
    {
        //std::cout<<"\t\tundo untap"<<std::endl;
        for (unsigned int i = 0 ; i < state->GetBattlefield().size() ; i++ )
            if (state->GetBattlefield()[i]->GetIdObj() == idCarte)
            {
                state->GetBattlefield()[i]->SetIsTap(wasTaped);
                if (state->GetBattlefield()[i]->GetIsCreature())
                    std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i])->SetMalInvoc(hadMalInvoc);
            }
    }
    
}
