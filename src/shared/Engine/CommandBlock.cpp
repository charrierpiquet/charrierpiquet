#include "CommandBlock.h"
#include "Etat/Objet.h"
#include "Etat/State.h"
#include <iostream>

namespace Engine
{
    CommandBlock::CommandBlock(std::shared_ptr<Etat::Creature> bloqueur, std::shared_ptr<Etat::Creature> bloque)
    {
        //std::cout<<"\t\tinit bloque"<<std::endl;
        idBloqueur = bloqueur->GetIdObj();
        idBloque = bloque->GetIdObj();
    }
    void CommandBlock::Execute(std::shared_ptr<Etat::State> state)
    {
        //std::cout<<"\t\texec bloque"<<std::endl;
        for (unsigned int i = 0 ; i < state->GetBattlefield().size() ; i++)
        {
            if (state->GetBattlefield()[i]->GetIdObj() == idBloqueur)
                state->AddListBloqueur(std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i]));
            if (state->GetBattlefield()[i]->GetIdObj() == idBloque)
                state->AddListBloque(std::static_pointer_cast<Etat::Creature>(state->GetBattlefield()[i]));
        }
    }
    void CommandBlock::Undo(std::shared_ptr<Etat::State> state)
    {
        //std::cout<<"\t\tundo bloque"<<std::endl;
        state->DelListBloque(state->GetListBloque().size()-1);
        state->DelListBloqueur(state->GetBloqueur().size()-1);
    }
    
    
}
