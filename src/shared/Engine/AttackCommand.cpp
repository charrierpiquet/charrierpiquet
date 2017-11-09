#include "AttackCommand.h"
#include "Etat/Carte.h"
#include <iostream>

namespace Engine
{
    void AttackCommand::AddAttaquant (std::shared_ptr<Etat::Creature> crea)
    {
        if (!crea->GetIsTap() && !crea->GetMalInvoc())
            attaquant.push_back(crea);
    }
    
    void AttackCommand::SupprAttaquant (std::shared_ptr<Etat::Creature> crea)
    {
        int ind=-1;
        for ( int i = 0 ; i < (int)attaquant.size() ; i++ )
            if ( crea == attaquant[i] )
                ind = i;
        if (ind != -1)
            attaquant.erase(attaquant.begin()+ind);
    }
    
    void AttackCommand::Execute (std::shared_ptr<Etat::State> state)
    {
        //std::cout<<attaquant.size()<<std::endl;
        //on engage les creatures attaquantes
        for ( int i = 0 ; i < (int)attaquant.size() ; i++ )
            attaquant[i]->SetIsTap(true);
    }
}