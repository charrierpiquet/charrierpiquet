#include "IA_heuristique.h"
#include "Engine/BlockCommand.h"
#include <iostream>
#include <ctime>
#include <Engine/CastCommand.h>
#include <Engine/LetPriorityCommand.h>
#include <Engine/AttackCommand.h>
#include <cstdlib>
#include <ctime>




namespace IA {

    IA_heuristique::IA_heuristique(std::shared_ptr<Etat::State> state, std::shared_ptr<Engine::Moteur> moteur)
    {
        currentState = state;
        engine = moteur;

    }

    void IA_heuristique::Think()
    {
        std::vector<int> list_val_cmd;
        std::vector<std::shared_ptr<Engine::Command> > list_cmd;
    }
    
    std::vector<std::shared_ptr<Engine::Command> > IA_heuristique::GetListCommand()
    {
       std::vector<std::shared_ptr<Engine::Command> > sortie;
       
       return sortie;
    }
    
    int IA_heuristique::EvalCmd(std::shared_ptr<Engine::Command> cmd)
    {
        // on copie l'etat;
        std::shared_ptr<Etat::State> tampon = currentState->Clone();
        std::shared_ptr<Engine::Moteur> m = std::shared_ptr<Engine::Moteur>(new Engine::Moteur(tampon));
        int joueur = currentState->GetPriority();
        
        std::shared_ptr<Engine::LetPriorityCommand> passe = std::shared_ptr<Engine::LetPriorityCommand>(new Engine::LetPriorityCommand());
        // on ajoute la commande et on l'execute
        m->AddCommand(cmd);
        m->Update();
        // on déroule jusqu'a ce que la pile soit vide pour pouvoir "noter" l'etat;
        while (!tampon->GetPile().empty())
        {
            m->AddCommand(passe);
            m->Update();
        }
        
        // on evalue l'etat
        int nb_crea = 0, offense = 0, defense = 0 , carte_main = 0, nb_land = 0, nb_pv = 0;
        for ( int i = 0; i < tampon->GetBattlefield().size() ; i++ )
        {
            if (tampon->GetBattlefield()[i]->GetIsCreature())
            {
                // si c'est toi qui est en train de regarder
                // on ne prend en compte que les creatures degages
                if (std::static_pointer_cast<Etat::Creature>(tampon->GetBattlefield()[i])->GetIsTap())
                {
                    if (tampon->GetBattlefield()[i]->GetIndJoueur() == joueur)
                    {
                        nb_crea ++;
                        offense +=  std::static_pointer_cast<Etat::Creature>(tampon->GetBattlefield()[i])->GetForce();
                        defense +=  std::static_pointer_cast<Etat::Creature>(tampon->GetBattlefield()[i])->GetEndurance();
                    }
                    else
                    {
                        nb_crea --;
                        offense -=  std::static_pointer_cast<Etat::Creature>(tampon->GetBattlefield()[i])->GetEndurance();
                        defense -=  std::static_pointer_cast<Etat::Creature>(tampon->GetBattlefield()[i])->GetForce();
                    }
                }
            }
            else if (tampon->GetBattlefield()[i]->GetIsLand())
            {
                if (tampon->GetBattlefield()[i]->GetIndJoueur() == joueur)
                    nb_land ++;
                else
                    nb_land --;
            }     
        }
        carte_main = tampon->GetJoueurs()[joueur]->GetHand().size() - tampon->GetJoueurs()[1-joueur]->GetHand().size();
        nb_pv = tampon->GetJoueurs()[joueur]->GetPv() - tampon->GetJoueurs()[1-joueur]->GetPv();
        //prise en compte des manapool pour la qtt de terrain
        nb_land += tampon->GetJoueurs()[joueur]->GetManaPool()->GetBlack();
        nb_land += tampon->GetJoueurs()[joueur]->GetManaPool()->GetBlue();
        nb_land += tampon->GetJoueurs()[joueur]->GetManaPool()->GetGreen();
        nb_land += tampon->GetJoueurs()[joueur]->GetManaPool()->GetMulti();
        nb_land += tampon->GetJoueurs()[joueur]->GetManaPool()->GetInc();
        
        nb_land -= tampon->GetJoueurs()[1-joueur]->GetManaPool()->GetBlack();
        nb_land -= tampon->GetJoueurs()[1-joueur]->GetManaPool()->GetBlue();
        nb_land -= tampon->GetJoueurs()[1-joueur]->GetManaPool()->GetGreen();
        nb_land -= tampon->GetJoueurs()[1-joueur]->GetManaPool()->GetMulti();
        nb_land -= tampon->GetJoueurs()[1-joueur]->GetManaPool()->GetInc();
        

        int k1=1,k2=1,k3=1,k4=1,k5=1,k6=1; // voir pour changer les coefficients plus tard
        
        return nb_crea*k1 +  offense*k2 + defense*k3 +  carte_main*k4 + nb_land*k5 + nb_pv*k6;
    }
    
    std::shared_ptr<Engine::Command> IA_heuristique::PhaseAttaque()
    {
        std::shared_ptr<Engine::AttackCommand> attaque (new Engine::AttackCommand());
        // si ta creature meurs pas et tue quelqu'un si elle est bloquee et que sa capacite n'est pas rentable
        for ( int i = 0 ; i < currentState->GetBattlefield().size() ; i++ )
            if (currentState->GetBattlefield()[i]->GetIsCreature() && currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetJoueurTour())
            {
                int survie = std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetEndurance();
                bool tue = true;
                 
                for ( int j = 0 ; j < currentState->GetBattlefield().size() ; j++ )
                    if (currentState->GetBattlefield()[j]->GetIsCreature() && currentState->GetBattlefield()[j]->GetIndJoueur() == 1-currentState->GetJoueurTour())
                    {
                        survie -= std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[j])->GetForce();
                        if (std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetForce() < std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[j])->GetEndurance())
                            tue = false;
                    }
                 
                bool bonne_capa = false;
                if (!currentState->GetBattlefield()[i]->GetAbility().empty())
                {
                    int actustate = EvalCmd(nullptr);
                    for ( int j = 0 ; j < currentState->GetBattlefield()[i]->GetAbility().size() ; j++)
                        if (!currentState->GetBattlefield()[i]->GetAbility()[i]->GetNeedTarget())
                        {
                            std::shared_ptr<Engine::CastCommand> cmd(new Engine::CastCommand(currentState->GetBattlefield()[i]->GetAbility()[j],currentState->GetBattlefield()[i],nullptr));
                            if (EvalCmd(cmd) > actustate)
                                bonne_capa = true;
                        }
                }
            }
        return attaque;
    }
    
    std::shared_ptr<Engine::Command> IA_heuristique::PhaseBloqueur()
    {
        return std::shared_ptr<Engine::BlockCommand>(new Engine::BlockCommand());
    }

}


