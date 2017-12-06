#include "Ia_Heuristic.h"
#include "Engine/CommandUntap.h"
#include "Engine/CommandDraw.h"
#include "Engine/CommandPhase.h"
#include "Engine/CommandAttack.h"
#include "Engine/CommandSolveCombat.h"
#include "Engine/CommandPaye.h"
#include "Engine/CommandDie.h"
#include "Engine/CommandDiscard.h"
#include "Engine/CommandResolveCard.h"
#include "Engine/CommandResolveCapa.h"
#include "Engine/CommandCast.h"
#include "Engine/CommandActive.h"
#include "Engine/CommandTour.h"
#include "Engine/CommandClean.h"
#include "Engine/CommandPriority.h"
#include "Engine/CommandBlock.h"
#include "Engine/CommandVideMp.h"
#include <iostream>
#include <algorithm>
#include <ctime> 

static bool InvCompareCreaAtt(std::shared_ptr<Etat::Creature> a, std::shared_ptr<Etat::Creature> b) {
    return a->GetForce() > b->GetForce();
}

namespace Ai {

    Ia_Heuristic::Ia_Heuristic(std::shared_ptr<Etat::State> state, std::shared_ptr<Engine::Moteur> moteur) :
    Ia_Base(state, moteur) {

    }

    void Ia_Heuristic::Think() {
        // si c'est le debut du tour
        if (currentState->GetPhase() == 0) {
            // on simplifie : on lance un terrain si on peux en lancer un
            std::cout << "\trecherche terrain" << std::endl;
            // on cherche un terrain dans notre main
            for (unsigned int i = 0; i < currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand().size(); i++)
                if (currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand()[i]->GetIsLand()) {
                    // un terrain n'ayant pas de cout, on cast le terrain
                    engine->AddCommand(std::shared_ptr<Engine::CommandCast>(new Engine::CommandCast(currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand()[i])));
                    // techniquement, un terrain ne passe pas par la pile donc on resout le terrain
                    engine->AddCommand(std::shared_ptr<Engine::CommandResolveCard>(new Engine::CommandResolveCard(currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand()[i], std::weak_ptr<Engine::Moteur>(engine))));
                    // on a jouer un terrain on devrait s'occuper du a jouer un terrain mais vue l'utilité ici on s'abstient
                    break;
                }
            std::cout << "\ton passe" << std::endl;
            // on passe a la phase suivante
            engine->AddCommand(std::shared_ptr<Engine::CommandPhase>(new Engine::CommandPhase(1)));
            engine->Update();
        }// si c'est la phase de declaration des attaquants
        else if (currentState->GetPhase() == 1) {
            // on fait la liste des créatures avec lesquels c'est bien d'attaquer et on attaque
            Attaque();
            engine->Update();
            engine->AddCommand(std::shared_ptr<Engine::CommandPhase>(new Engine::CommandPhase(2)));
            engine->Update();
        } else if (currentState->GetPhase() == 2) {
            // priorite on combat
            DoBestAction();
        } else if (currentState->GetPhase() == 3) {
            // on fait la liste des créatures avec lesquels c'est bien d'attaquer
            Bloque();
            engine->Update();
            engine->AddCommand(std::shared_ptr<Engine::CommandSolveCombat>(new Engine::CommandSolveCombat()));
            engine->Update();
            engine->AddCommand(std::shared_ptr<Engine::CommandPhase>(new Engine::CommandPhase(4)));
            engine->Update();
        } else if (currentState->GetPhase() == 4) {
            // on tente de faire un coup
            DoBestAction();
        }
    }

    int Ia_Heuristic::EvalState() {
        int status = engine->HistoricSize();
        int sortie = 0;
        // on vide la pile
        while (!currentState->GetPile().empty()) {
            if (currentState->GetPile()[currentState->GetPile().size() - 1]->GetIsCapacite())
                engine->AddCommand(std::shared_ptr<Engine::CommandResolveCapa>(new Engine::CommandResolveCapa(std::static_pointer_cast<Etat::Capacite>(currentState->GetPile()[currentState->GetPile().size() - 1]), std::weak_ptr<Engine::Moteur>(engine))));
            else
                engine->AddCommand(std::shared_ptr<Engine::CommandResolveCard>(new Engine::CommandResolveCard(std::static_pointer_cast<Etat::Carte>(currentState->GetPile()[currentState->GetPile().size() - 1]), std::weak_ptr<Engine::Moteur>(engine))));
            engine->Update();
        }
        // on note
        int nb_crea = 0, offense = 0, defense = 0, carte_main = 0, nb_land = 0, nb_pv = 0, nb_autre = 0;
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++) {
            if (currentState->GetBattlefield()[i]->GetIsCreature()) {
                // si c'est toi qui est en train de regarder
                // on ne prend en compte que les creatures degages
                if (std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetIsTap()) {
                    if (currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetPriority()) {
                        nb_crea++;
                        offense += std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetForce();
                        defense += std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetEndurance();
                    } else {
                        nb_crea--;
                        offense -= std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetEndurance();
                        defense -= std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetForce();
                    }
                } else {
                    if (currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetPriority())
                        nb_autre++;
                    else
                        nb_autre--;
                }
            } else if (currentState->GetBattlefield()[i]->GetIsLand()) {
                if (currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetPriority())
                    nb_land++;
                else
                    nb_land--;
            }
        }
        carte_main = currentState->GetJoueurs()[currentState->GetPriority()]->GetHand().size() - currentState->GetJoueurs()[1 - currentState->GetPriority()]->GetHand().size();
        nb_pv = currentState->GetJoueurs()[currentState->GetPriority()]->GetPv() - currentState->GetJoueurs()[1 - currentState->GetPriority()]->GetPv();
        //prise en compte des manapool pour la qtt de terrain
        nb_land += currentState->GetJoueurs()[currentState->GetPriority()]->GetManaPool()->GetBlack();
        nb_land += currentState->GetJoueurs()[currentState->GetPriority()]->GetManaPool()->GetBlue();
        nb_land += currentState->GetJoueurs()[currentState->GetPriority()]->GetManaPool()->GetGreen();
        nb_land += currentState->GetJoueurs()[currentState->GetPriority()]->GetManaPool()->GetMulti();
        nb_land += currentState->GetJoueurs()[currentState->GetPriority()]->GetManaPool()->GetInc();

        nb_land -= currentState->GetJoueurs()[1 - currentState->GetPriority()]->GetManaPool()->GetBlack();
        nb_land -= currentState->GetJoueurs()[1 - currentState->GetPriority()]->GetManaPool()->GetBlue();
        nb_land -= currentState->GetJoueurs()[1 - currentState->GetPriority()]->GetManaPool()->GetGreen();
        nb_land -= currentState->GetJoueurs()[1 - currentState->GetPriority()]->GetManaPool()->GetMulti();
        nb_land -= currentState->GetJoueurs()[1 - currentState->GetPriority()]->GetManaPool()->GetInc();

        int k1 = 5, k2 = 3, k3 = 3, k4 = 1, k5 = 1, k6 = 1, k7 = 3; // voir pour changer les coefficients plus tard
        sortie = nb_crea * k1 + offense * k2 + defense * k3 + carte_main * k4 + nb_land * k5 + nb_pv * k6 + nb_autre*k7;
        // on reviens en arriere
        Retour(status);
        // end
        //std::cout << "\t" << sortie << std::endl;
        return sortie;
    }

    std::vector<std::shared_ptr<Etat::Objet> > Ia_Heuristic::ListObjet() {
        std::vector<std::shared_ptr<Etat::Objet> > sortie;
        int hist = engine->HistoricSize();
        // recherche dans la main
        for (unsigned int i = 0; i < currentState->GetJoueurs()[currentState->GetPriority()]->GetHand().size(); i++) {
            if (!currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i]->GetIsLand()) {
                if (currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i]->GetIsPermanent()) {
                    if (currentState->GetPhase() == 0 || currentState->GetPhase() == 4)
                        if (currentState->GetPile().empty())
                            if (TryCast(currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i]->GetCost()))
                                sortie.push_back(currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i]);
                } else {
                    if (TryCast(currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i]->GetCost()))
                        sortie.push_back(currentState->GetJoueurs()[currentState->GetPriority()]->GetHand()[i]);
                }
            }
            Retour(hist);
        }
        // recherche sur le champ de bataille
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (!currentState->GetBattlefield()[i]->GetIsLand())
                if (currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetPriority())
                    if (!currentState->GetBattlefield()[i]->GetIsTap())
                        if (!currentState->GetBattlefield()[i]->GetAbility().empty())
                            for (unsigned int j = 0; j < currentState->GetBattlefield()[i]->GetAbility().size(); j++) {
                                if (TryCast(currentState->GetBattlefield()[i]->GetAbility()[j]->GetCost()))
                                    sortie.push_back(currentState->GetBattlefield()[i]->GetAbility()[j]);
                                Retour(hist);
                            }
        return sortie;
    }

    std::vector<std::shared_ptr<Etat::Objet> > Ia_Heuristic::ListCible() {
        std::vector<std::shared_ptr<Etat::Objet> > sortie;
        for (unsigned int i = 0 ; i < currentState->GetBattlefield().size() ; i++)
            sortie.push_back(currentState->GetBattlefield()[i]);
        for (unsigned int i = 0 ; i < currentState->GetPile().size() ; i++)
            sortie.push_back(currentState->GetPile()[i]);
        return sortie;
    }

    void Ia_Heuristic::DoBestAction() {

        // on a besoin du max, de l'objet, de la cible, de la source
        int max = EvalState();
        //std::cout<<"\t\t"<<max<<std::endl;
        int def = max;
        std::shared_ptr<Etat::Objet> obj;
        std::weak_ptr<Etat::Objet> cible;
        std::shared_ptr<Etat::Carte> src;
        int status = engine->HistoricSize();

        // creer liste objet activable
        std::vector<std::shared_ptr<Etat::Objet> > objs = ListObjet();
        // creer liste cible legale
        std::vector<std::shared_ptr<Etat::Objet> > cibles = ListCible();
        // pour chaque combinaison possible 
        for (unsigned int i = 0; i < objs.size(); i++)
            for (unsigned int j = 0; j < cibles.size(); j++) {
                if (TryCast(objs[i]->GetCost())) {
                    objs[i]->SetTarget(std::weak_ptr<Etat::Objet>(cibles[j]));
                    //std::shared_ptr<Etat::Carte> source_tamporaire();
                    if (objs[i]->GetIsCapacite()) {
                        // on cherche la source
                        //for (unsigned int k = 0; k < currentState->GetBattlefield().size(); k++)
                        //    for (unsigned int l = 0; l < currentState->GetBattlefield()[i]->GetAbility().size(); l++)
                        //        if (currentState->GetBattlefield()[i]->GetAbility()[j]->GetIdObj() == objs[i]->GetIdObj())
                        //            source_tamporaire = currentState->GetBattlefield()[i];

                        engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(std::static_pointer_cast<Etat::Capacite>(objs[i])->GetSource().lock(), std::static_pointer_cast<Etat::Capacite>(objs[i]), cibles[j])));
                    } else
                        engine->AddCommand(std::shared_ptr<Engine::CommandCast>(new Engine::CommandCast(std::static_pointer_cast<Etat::Carte>(objs[i]))));

                    engine->Update();

                    int val = EvalState();
                    if (val > max) {
                        max = val;
                        obj = objs[i];
                        src = std::static_pointer_cast<Etat::Capacite>(objs[i])->GetSource().lock();
                        cible = cibles[j];
                    }
                }
                Retour(status);
            }
        Retour(status);
        if (max > def) {
            std::cout << "\t\t" << obj->GetName() << std::endl;
            // on fait l'action correspondant au max
            if (TryCast(obj->GetCost())) {
                if (obj->GetIsCapacite())
                    engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(src, std::static_pointer_cast<Etat::Capacite>(obj), cible)));
                else {
                    obj->SetTarget(cible);
                    engine->AddCommand(std::shared_ptr<Engine::CommandCast>(new Engine::CommandCast(std::static_pointer_cast<Etat::Carte>(obj))));
                }
                engine->Update();
            }

        }// gestion priorite
        else {
            // si aucune action n'est rentable
            // on passe la priorite
            engine->AddCommand(std::shared_ptr<Engine::CommandPriority>(new Engine::CommandPriority(1 - currentState->GetPriority())));
            engine->Update();
            // si la pile est vide
            if (currentState->GetPile().empty()) {
                // si la priorite est egal au joueur dont c'est le tour
                if (currentState->GetPriority() == currentState->GetJoueurTour()) {
                    // si on est a la phase 4
                    if (currentState->GetPhase() == 4)
                        // fin tour
                        FinTour();
                        //sinon
                    else {
                        // on passe a la phase suivante
                        KillAll();
                        engine->AddCommand(std::shared_ptr<Engine::CommandPhase>(new Engine::CommandPhase((currentState->GetPhase() + 1) % 5)));
                    }
                    engine->Update();
                }
            }// sinon si le dernier objet lance a ete lance par le joueur qui a la priorite
            else if (currentState->GetPile()[currentState->GetPile().size() - 1]->GetIndJoueur() == currentState->GetPriority()) {
                // on resout l'objet
                if (currentState->GetPile()[currentState->GetPile().size() - 1]->GetIsCapacite())
                    engine->AddCommand(std::shared_ptr<Engine::CommandResolveCapa>(new Engine::CommandResolveCapa(std::static_pointer_cast<Etat::Capacite>(currentState->GetPile()[currentState->GetPile().size() - 1]), std::weak_ptr<Engine::Moteur>(engine))));
                else
                    engine->AddCommand(std::shared_ptr<Engine::CommandResolveCard>(new Engine::CommandResolveCard(std::static_pointer_cast<Etat::Carte>(currentState->GetPile()[currentState->GetPile().size() - 1]), std::weak_ptr<Engine::Moteur>(engine))));
                engine->Update();
            }
        }
    }

    void Ia_Heuristic::Retour(int val) {
        //std::cout<<"\t\t"<<val<<"\t"<<engine->HistoricSize()<<std::endl;
        int k = engine->HistoricSize() - val;
        while (engine->HistoricSize() != val) {
            engine->RollBack();
            k--;
        }
        if (k != 0)
            std::cout << "\t\tWut ?!" << std::endl;

    }

    // override TryCast pour qu'il engage aussi la mana

    bool Ia_Heuristic::TryCast(std::shared_ptr<Etat::Cout> cost) {
        // on admet qu'il n'existe que trois type de terrain (les terrains de base)
        // on admet que l'on commence avec la manapool vide
        std::cout<<"\tTryCast"<<std::endl;
        bool canCast = (0 == cost->GetInc() && 0 == cost->GetBlack() && 0 == cost->GetBlue()&& 0 == cost->GetGreen());
        if (!canCast) {
            int hist = engine->HistoricSize();
            int inc = cost->GetInc(), b = cost->GetBlack(), u = cost->GetBlue(), g = cost->GetGreen(), k = 0;
            //std::cout<<"\t"<<inc<<"\t"<<b<<"\t"<<u<<"\t"<<g<<std::endl;
            for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
                if (currentState->GetBattlefield()[i]->GetIsLand() && !currentState->GetBattlefield()[i]->GetIsTap() && currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetPriority()) {
                    if (b > 0 && currentState->GetBattlefield()[i]->GetName() == "Marais") {
                        engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(currentState->GetBattlefield()[i], currentState->GetBattlefield()[i]->GetAbility()[0], std::weak_ptr<Etat::Objet>())));
                        b--;
                        k++;
                    }
                    if (u > 0 && currentState->GetBattlefield()[i]->GetName() == "Ile") {
                        engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(currentState->GetBattlefield()[i], currentState->GetBattlefield()[i]->GetAbility()[0], std::weak_ptr<Etat::Objet>())));
                        u--;
                        k++;
                    }
                    if (g > 0 && currentState->GetBattlefield()[i]->GetName() == "Foret") {
                        engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(currentState->GetBattlefield()[i], currentState->GetBattlefield()[i]->GetAbility()[0], std::weak_ptr<Etat::Objet>())));
                        g--;
                        k++;
                    }
                }
            engine->Update();
            for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
                if (currentState->GetBattlefield()[i]->GetIsLand() && !currentState->GetBattlefield()[i]->GetIsTap() && currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetPriority())
                    if (i > 0) {
                        engine->AddCommand(std::shared_ptr<Engine::CommandActive>(new Engine::CommandActive(currentState->GetBattlefield()[i], currentState->GetBattlefield()[i]->GetAbility()[0], std::weak_ptr<Etat::Objet>())));
                        inc--;
                        k++;
                    }
            engine->Update();
            while (k--) {
                engine->AddCommand(std::shared_ptr<Engine::CommandResolveCapa>(new Engine::CommandResolveCapa(std::static_pointer_cast<Etat::Capacite>(currentState->GetPile()[currentState->GetPile().size() - 1]), std::weak_ptr<Engine::Moteur>(engine))));
                engine->Update();
            }

            int m1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetMulti();
            int i1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetInc();
            int b1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetBlack();
            int u1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetBlue();
            int g1 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetGreen();

            engine->AddCommand(std::shared_ptr<Engine::CommandPaye>(new Engine::CommandPaye(cost)));
            engine->Update();

            int m2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetMulti();
            int i2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetInc();
            int b2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetBlack();
            int u2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetBlue();
            int g2 = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetManaPool()->GetGreen();
            //std::cout <<"\t\t"<<m1<<" "<<m2<<" "<<i1<<" "<<i2<<" "<<b1<<" "<<b2<<" "<<u1<<" "<<u2<<" "<<g1<<" "<<g2<<" ";

            canCast = (m1 != m2 || i1 != i2 || b1 != b2 || u1 != u2 || g1 != g2);
            //std::cout<<"\t"<<canCast<<std::endl;
            if (!canCast)
                Retour(hist);

        }
        return canCast;
    }

    void Ia_Heuristic::FinTour() {
        engine->AddCommand(std::shared_ptr<Engine::CommandVideMp>(new Engine::CommandVideMp()));
        engine->Update();
        KillAll();
        // on clean le reste
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIsCreature())
                engine->AddCommand(std::shared_ptr<Engine::CommandClean>(new Engine::CommandClean(std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i]))));
        // on se defausse des cartes que l'on a en trop
        int nb = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand().size();
        for (int i = 6; i < nb; i++) // oblige de faire comme ça sinon ça merde
            engine->AddCommand(std::shared_ptr<Engine::CommandDiscard>(new Engine::CommandDiscard(currentState->GetJoueurTour())));

        engine->AddCommand(std::shared_ptr<Engine::CommandPhase>(new Engine::CommandPhase(0)));
        engine->AddCommand(std::shared_ptr<Engine::CommandTour>(new Engine::CommandTour(1 - currentState->GetJoueurTour())));
        engine->Update();

        // c'est le debut du tour
        // on degage tout
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetJoueurTour())
                engine->AddCommand(std::shared_ptr<Engine::CommandUntap>(new Engine::CommandUntap(currentState->GetBattlefield()[i])));
        // on pioche
        engine->AddCommand(std::shared_ptr<Engine::CommandPriority>(new Engine::CommandPriority(currentState->GetJoueurTour())));
        engine->Update();
        engine->AddCommand(std::shared_ptr<Engine::CommandDraw>(new Engine::CommandDraw(currentState->GetJoueurTour())));
        engine->Update();
    }

    void Ia_Heuristic::Attaque() {

        // si ta creature meurs pas et tue quelqu'un si elle est bloquee et que sa capacite n'est pas rentable
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIsCreature() && currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetJoueurTour())
                if (!std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetMalInvoc()) {
                    int survie = std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetEndurance();
                    bool tue = true;

                    for (unsigned int j = 0; j < currentState->GetBattlefield().size(); j++)
                        if (currentState->GetBattlefield()[j]->GetIsCreature() && currentState->GetBattlefield()[j]->GetIndJoueur() == 1 - currentState->GetJoueurTour()) {
                            survie -= std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[j])->GetForce();
                            if (std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetForce() < std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[j])->GetEndurance())
                                tue = false;
                        }

                    if (tue && (!currentState->GetBattlefield()[i]->GetAbility().empty() || survie > 0))
                        engine->AddCommand(std::shared_ptr<Engine::CommandAttack>(new Engine::CommandAttack(std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i]))));
                }
    }

    void Ia_Heuristic::Bloque() {
        // bloquage extremement simplifie
        // theoriquement, on pourrait aussi bloquer avec une creature "inutile",
        // bloquer avec plusieurs creature sur une même creature, chercher a tuer a tout prix etc.
        int jDef = 1 - currentState->GetJoueurTour();

        std::vector<std::shared_ptr<Etat::Creature> > creaJDef;
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIsCreature() && currentState->GetBattlefield()[i]->GetIndJoueur() == jDef)
                creaJDef.push_back(std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i]));

        std::vector<std::shared_ptr<Etat::Creature> > attaquant = currentState->GetAttaquants();
        std::sort(attaquant.begin(), attaquant.end(), InvCompareCreaAtt); // ordonne selon attaque décroissante.
        // pour chaque crea attaquante
        for (unsigned int i = 0; i < attaquant.size(); i++)
            // si on peux la bloquer sans mourir
            for (unsigned int j = 0; j < creaJDef.size(); j++)
                if (creaJDef[j]->GetEndurance() > attaquant[i]->GetForce()) {
                    engine->AddCommand(std::shared_ptr<Engine::CommandBlock>(new Engine::CommandBlock(creaJDef[j], attaquant[i])));
                    creaJDef.erase(creaJDef.begin() + j);
                    break;
                }
    }

    void Ia_Heuristic::KillAll() {
        // on tue les trucs qui doivent mourir
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIsCreature())
                if (std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetEndurance() <= 0)
                    engine->AddCommand(std::shared_ptr<Engine::CommandDie>(new Engine::CommandDie(currentState->GetBattlefield()[i])));
        engine->Update();
    }
}

