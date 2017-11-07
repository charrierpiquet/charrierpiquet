#include "Etat.h"
#include "TestEtat.h"
#include <iostream>

namespace Test
{
    int TestEtat()
    {
            int ret = -1;

            Etat::State* state = new Etat::State();

            if(20!=state->GetJoueurs()[state->GetPriority()]->GetPv())
                    return 2;
            else
                    ret = 0;
            std::cout<<"Nombre de point de vie Ok"<<std::endl;                
    
            state->GetJoueurs()[state->GetPriority()]->SetPv(state->GetJoueurs()[state->GetPriority()]->GetPv()+2);

            if (22!=state->GetJoueurs()[state->GetPriority()]->GetPv())
                    return 3;
            else
                    ret = 0;
            std::cout<<"Modification PV Ok"<<std::endl;
            state->GetJoueurs()[state->GetPriority()]->SetPv(-8);

            if (0!=state->GetJoueurs()[state->GetPriority()]->GetPv())
                    return 4;
            else
                    ret = 0;
            std::cout<<"Les Pv ne peuvent pas être negatif Ok"<<std::endl;
            
            if (0!=state->GetJoueurs()[state->GetPriority()]->GetManaPool()->GetInc())
                    return 5;
            else
                    ret = 0;
            
            std::cout<<"La ManaPool est vide Ok"<<std::endl;

            state->GetJoueurs()[state->GetPriority()]->GetManaPool()->AddInc();
            state->GetJoueurs()[state->GetPriority()]->GetManaPool()->AddInc();
            state->GetJoueurs()[state->GetPriority()]->GetManaPool()->AddInc();
            state->GetJoueurs()[state->GetPriority()]->GetManaPool()->AddInc();
            if (4!=state->GetJoueurs()[state->GetPriority()]->GetManaPool()->GetInc())
                return 6;
            else
                ret = 0;

            std::cout<<"Ajout a la manapool Ok"<<std::endl;

            
            state->IncrPhase();
            if (state->GetPhase() != 1 && state->GetJoueurs()[state->GetPriority()]->GetManaPool()->GetInc() != 0)
                return 7;
            else
                ret = 0;
            
            std::cout<<"passage de phase Ok"<<std::endl;
            
            Etat::Cout* cost = new Etat::Cout();
            cost->SetCost(-1,0,0,0,0,0,0,0,0);
            if (cost->GetInc() != 0)
                return 8;
            else
                ret = 0;
            std::cout<<"cout positifs Ok"<<std::endl;
            
            cost->SetCost(3,0,0,0,0,0,0,0,0);
            if (cost->GetInc() != 3)
                return 9;
            else
                ret = 0;
            std::cout<<"modification cout Ok"<<std::endl;
            
            state->GetJoueurs()[state->GetPriority()]->GetManaPool()->AddInc();
            state->GetJoueurs()[state->GetPriority()]->GetManaPool()->AddInc();
            state->GetJoueurs()[state->GetPriority()]->GetManaPool()->AddInc();
            state->GetJoueurs()[state->GetPriority()]->GetManaPool()->AddInc();
            state->GetJoueurs()[state->GetPriority()]->GetManaPool()->Payer(*cost);
            if (state->GetJoueurs()[state->GetPriority()]->GetManaPool()->GetInc() != 1)
                return 10;
            else
                ret = 0;
            std::cout<<"payer cout Ok"<<std::endl; 
            
            std::string nom = "foret";
            std::vector<std::shared_ptr<Etat::Capacite> > capa;
            std::shared_ptr<Etat::Carte> card (new Etat::Carte(true,true,false,false,nom,*cost,capa,1,0));
            state->AddCardBattlefield(card);
            if (state->GetBattlefield().size() != 1)
                return 11;
            else
                ret = 0;
            std::cout<<"creation carte Ok"<<std::endl;     

            return ret;
    }
};