#include "AttackCommand.h"
#include "Etat/Carte.h"

namespace Engine
{
    void AttackCommand::AddAttaquant (std::shared_ptr<Etat::Creature> crea)
    {
        if (!crea->GetIsTap())
            attaquant.push_back(crea);
    }
    
    void AttackCommand::SupprAttaquant (std::shared_ptr<Etat::Creature> crea)
    {
        int ind=-1;
        for ( int i = 0 ; i < attaquant.size() ; i++ )
            if ( crea == attaquant[i] )
                ind = i;
        if (ind != -1)
            attaquant.erase(attaquant.begin()+ind);
    }
    
    void AttackCommand::Execute (Etat::State& state)
    {
        //on engage les creatures attaquantes
        for ( int i = 0 ; i < attaquant.size() ; i++ )
            attaquant[i]->SetIsTap(true);
    }
}