#include "BlockCommand.h"
#include "Etat/Creature.h"
#include "Etat/State.h"

namespace Engine
{
    BlockCommand::BlockCommand (std::vector<std::shared_ptr<Etat::Creature> > attaq)
    {
        attaquant = attaq;
    }
    void BlockCommand::SupprBloqueur (std::shared_ptr<Etat::Creature> crea)
    {
        int ind=-1;
        for ( int i = 0 ; i < (int)bloqueur.size() ; i++ )
            if ( crea == bloqueur[i] )
                ind = i;
        if (ind != -1)
        {
            bloqueur.erase(bloqueur.begin()+ind);
            bloque.erase(bloque.begin()+ind);
        }
            
    }
    void BlockCommand::AddBloqueur (std::shared_ptr<Etat::Creature> crea_bloqueur, std::shared_ptr<Etat::Creature> crea_bloque)
    {
        bloqueur.push_back(crea_bloqueur);
        bloque.push_back(crea_bloque);
    }
    void BlockCommand::Execute (std::shared_ptr<Etat::State> state)
    {
        // les creatures bloqueuse inflige leur blessure aux creatures bloques
        for( int i = 0 ; i < (int)bloqueur.size() ; i++ )
            bloque[i]->SetBlessure(bloque[i]->GetBlessure() + bloqueur[i]->GetForce());   
         
        // les creatures bloques infliges leurs blessures aux creature bloqueuses
        // dans l'ordre des creatures qui bloque et si ça depasse aux creatures suivantes
        for( int i = 0 ; i < (int)attaquant.size() ; i++ )
        {
            bool isBlocked = false;
            
            for ( int j = 0 ; j < (int)bloque.size() ; j++ )
                if ( attaquant[i] == bloque[j] )
                    isBlocked = true;
            
            int dmgToDeal = attaquant[i]->GetForce();    
            
            if ( isBlocked )
            {
                for ( int j = 0 ; j < (int)bloque.size() ; j++ )
                    if ( attaquant[i] == bloque[j] && dmgToDeal > 0 )
                    {
                        if ( dmgToDeal >= bloqueur[j]->GetEndurance() )
                        {
                            dmgToDeal -=  bloqueur[j]->GetEndurance();
                            bloqueur[j]->SetBlessure(bloqueur[j]->GetBlessure() + bloqueur[j]->GetEndurance());
                        }
                        else 
                        {
                            bloqueur[j]->SetBlessure(bloqueur[j]->GetBlessure() + dmgToDeal);
                            dmgToDeal = 0;
                        }
                    }
            }
            else
                state->GetJoueurs()[1-state->GetJoueurTour()]->SetPv(state->GetJoueurs()[1-state->GetJoueurTour()]->GetPv() - dmgToDeal);
         
        }       
    }
}