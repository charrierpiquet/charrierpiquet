#include "Etat.h"
#include "TestEtat.h"
#include <iostream>


namespace Test
{
    int TestEtat()
    {
            int ret = -1;

            Etat::State* state = new Etat::State();

            if(2!=state->GetNbJoueur())
                    return 1;
            else
                    ret = 0;
            std::cout<<"Etat creer"<<std::endl;
            if(20!=state->JoueurActif()->GetPv())
                    return 2;
            else
                    ret = 0;
            std::cout<<"Nombre de point de vie Ok"<<std::endl;                
    
            state->JoueurActif()->SetPv(state->JoueurActif()->GetPv()+2);

            if (22!=state->JoueurActif()->GetPv())
                    return 3;
            else
                    ret = 0;
            std::cout<<"Modification PV Ok"<<std::endl;
            state->JoueurActif()->SetPv(-8);

            if (0!=state->JoueurActif()->GetPv())
                    return 4;
            else
                    ret = 0;
            std::cout<<"Les Pv ne peuvent pas être negatif Ok"<<std::endl;
            
            if (0!=state->JoueurActif()->GetManaPool()->GetInc())
                    return 5;
            else
                    ret = 0;
            
            std::cout<<"La ManaPool est vide Ok"<<std::endl;

            state->JoueurActif()->GetManaPool()->AddInc();
            state->JoueurActif()->GetManaPool()->AddInc();
            state->JoueurActif()->GetManaPool()->AddInc();
            state->JoueurActif()->GetManaPool()->AddInc();
            if (4!=state->JoueurActif()->GetManaPool()->GetInc())
                return 6;
            else
                ret = 0;

            std::cout<<"Ajout a la manapool Ok"<<std::endl;

            
            state->IncrPhase();
            if (state->GetPhase() != 1 && state->JoueurActif()->GetManaPool()->GetInc() != 0)
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
            
            state->JoueurActif()->GetManaPool()->AddInc();
            state->JoueurActif()->GetManaPool()->AddInc();
            state->JoueurActif()->GetManaPool()->AddInc();
            state->JoueurActif()->GetManaPool()->AddInc();
            state->JoueurActif()->GetManaPool()->Payer(*cost);
            if (state->JoueurActif()->GetManaPool()->GetInc() != 1)
                return 10;
            else
                ret = 0;
            std::cout<<"payer cout Ok"<<std::endl; 
            
            std::string nom = "foret";
            std::vector<std::shared_ptr<Etat::Capacite> > capa;
            Etat::Carte* card = new Etat::Carte(true,true,false,false,nom,*cost,capa,1,0);
            state->AddCardBattlefield(*card);
            if (state->GetBattlefield().size() != 1)
                return 11;
            else
                ret = 0;
            std::cout<<"creation carte Ok"<<std::endl;     

            return ret;
    }
};