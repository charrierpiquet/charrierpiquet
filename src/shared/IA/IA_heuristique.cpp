#include "IA_heuristique.h"
#include "Engine/BlockCommand.h"
#include "Etat/Active.h"
#include <iostream>
#include <ctime>
#include <Engine/CastCommand.h>
#include <Engine/LetPriorityCommand.h>
#include <Engine/AttackCommand.h>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static bool InvCompareCreaAtt(std::shared_ptr<Etat::Creature> a, std::shared_ptr<Etat::Creature> b) {
    return a->GetForce() > b->GetForce();
}


namespace IA {

    IA_heuristique::IA_heuristique(std::shared_ptr<Etat::State> state, std::shared_ptr<Engine::Moteur> moteur) {
        currentState = state;
        engine = moteur;
    }

    void IA_heuristique::Think() {
        std::vector<std::shared_ptr<Etat::Carte> > MainJoueur;
        std::vector<std::shared_ptr<Etat::Carte> > NonLandMainJoueur;
        std::vector<std::shared_ptr<Etat::Carte> > Board;
        std::vector<std::shared_ptr<Etat::Creature> > CreaturesJoueur;

        MainJoueur = currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetHand();
        Board = currentState->GetBattlefield();
        unsigned int i = 0;

        for (i = 0; i < Board.size(); i++) //Récupération des listes de créatures et terrians controlés par le joueur
            if ((Board[i]->GetIndJoueur() == currentState->GetJoueurTour()) && (Board[i]->GetIsCreature()))
                CreaturesJoueur.push_back(std::static_pointer_cast<Etat::Creature>(Board[i]));

        for (i = 0; i < MainJoueur.size(); i++)
            if (!MainJoueur[i]->GetIsLand())
                NonLandMainJoueur.push_back(MainJoueur[i]);

        std::shared_ptr<Engine::LetPriorityCommand> Past(std::shared_ptr<Engine::LetPriorityCommand>(new Engine::LetPriorityCommand()));
        // si on est dans la pre-combat main phase
        if (currentState->GetPhase() == 0) {
            // si c'est joueur dont c'est le tour qui a la priorite
            if (currentState->GetJoueurTour() == currentState->GetPriority()) {
                // si on peux jouer un terrain
                if (!currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetAJoueTerrain()) {
                    //std::cout<<"on est la"<<currentState->GetJoueurTour()<<" "<< currentState->GetPriority()<<" "<<currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetAJoueTerrain()<<std::endl;
                    bool passe = true;
                    for (i = 0; i < MainJoueur.size(); i++)
                        if (MainJoueur[i]->GetIsLand()) {
                            std::shared_ptr<Engine::CastCommand> Cast(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(MainJoueur[i], nullptr, nullptr)));
                            engine->AddCommand(Cast);
                            passe = false;
                            break;
                        }
                    if (passe) {
                        engine->AddCommand(Past);
                    }
                } else {
                    engine->AddCommand(Past);
                }
            } else {
                engine->AddCommand(Past);
            }
        }// si on est dans la post-combat main phase
        else if (currentState->GetPhase() == 4) {
            Penser();
        }// si on est durant la phase de combat
        else if (currentState->GetPhase() == 1) {
            if (currentState->GetPriority() == currentState->GetJoueurTour()) {
                engine->AddCommand(PhaseAttaque());
            }
            engine->AddCommand(Past);
            engine->AddCommand(Past);
        } else if (currentState->GetPhase() == 2) {
            Penser();
        } else if (currentState->GetPhase() == 3) {
            engine->AddCommand(PhaseBloqueur());
            engine->AddCommand(Past);
            engine->AddCommand(Past);
        } else {
            engine->AddCommand(Past);
        }
    }

    std::vector<std::shared_ptr<Engine::CastCommand> > IA_heuristique::GetListCommand() {
        unsigned int i = 0;
        unsigned int j = 0;
        unsigned int n = 0;
        std::vector<std::shared_ptr<Engine::CastCommand> > ListeCommandes;
        std::vector<std::shared_ptr<Etat::Carte> > MainJoueur = currentState->GetJoueurs()[currentState->GetPriority()]->GetHand();
        std::vector<std::shared_ptr<Etat::Carte> > BoardJoueur;
        std::vector<std::shared_ptr<Etat::Objet> > Cibles;

        for (i = 0; i < currentState->GetBattlefield().size(); i++)
            Cibles.push_back(std::static_pointer_cast<Etat::Objet>(currentState->GetBattlefield()[i]));

        for (j = 0; j < currentState->GetPile().size(); j++)
            Cibles.push_back(currentState->GetPile()[j]);

        for (n = 0; n < currentState->GetBattlefield().size(); n++)
            if ((currentState->GetBattlefield()[n]->GetIndJoueur() == currentState->GetPriority())&&(!currentState->GetBattlefield()[n]->GetIsLand()))
                BoardJoueur.push_back(currentState->GetBattlefield()[n]);

        for (i = 0; i < MainJoueur.size(); i++) {
            if (((currentState->GetPriority() == currentState->GetJoueurTour()) && ((currentState->GetPhaseName() == "Pre-Combat Main") || (currentState->GetPhaseName() == "Post-Combat Main")))&&((MainJoueur[i]->GetIsPermanent()) && currentState->GetPile().empty())) {
                if ((MainJoueur[i]->GetIsLand()&&!(currentState->GetJoueurs()[currentState->GetJoueurTour()]->GetAJoueTerrain())) || (!MainJoueur[i]->GetIsLand())) {
                    ListeCommandes.push_back(std::shared_ptr<Engine::CastCommand>(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(MainJoueur[i], nullptr, nullptr))));
                }
            } else if (!MainJoueur[i]->GetIsPermanent())
                for (unsigned int k = 0; k < MainJoueur[i]->GetAbility().size(); k++) {
                    if (!MainJoueur[i]->GetAbility()[k]->GetNeedTarget())
                        ListeCommandes.push_back(std::shared_ptr<Engine::CastCommand>(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(MainJoueur[i], nullptr, nullptr))));
                    else
                        for (j = 0; j < Cibles.size(); j++)
                            ListeCommandes.push_back(std::shared_ptr<Engine::CastCommand>(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(MainJoueur[i], nullptr, Cibles[j]))));

                }
        }

        for (i = 0; i < BoardJoueur.size(); i++)
            for (n = 0; n < BoardJoueur[i]->GetAbility().size(); n++) {
                if (BoardJoueur[i]->GetAbility()[n]->GetNeedTarget())
                    for (j = 0; j < Cibles.size(); j++)
                        ListeCommandes.push_back(std::shared_ptr<Engine::CastCommand>(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(BoardJoueur[i]->GetAbility()[n], BoardJoueur[i], Cibles[j]))));
                else
                    ListeCommandes.push_back(std::shared_ptr<Engine::CastCommand>(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(BoardJoueur[i]->GetAbility()[n], BoardJoueur[i], nullptr))));
            }
        return ListeCommandes;
    }

    int IA_heuristique::EvalCmd(std::shared_ptr<Engine::CastCommand> cmd) {
        std::shared_ptr<Engine::LetPriorityCommand> passe(new Engine::LetPriorityCommand());
        int joueur = currentState->GetPriority();
        int compteur = 0;
        //creation de la commande "alternative"
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIsLand()) {
                engine->AddCommand(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(currentState->GetBattlefield()[i]->GetAbility()[0], currentState->GetBattlefield()[i], nullptr)));
                engine->Update();
                compteur++;
            }

        // on ajoute la commande et on l'execute
        if (cmd != nullptr)
        {
            engine->AddCommand(cmd);
            engine->Update();
        }
        compteur++;
        // on déroule jusqu'a ce que la pile soit vide pour pouvoir "noter" l'etat;
        while (!currentState->GetPile().empty()) {
            engine->AddCommand(passe);
            engine->Update();
            compteur++;
        }

        // on evalue l'etat
        int nb_crea = 0, offense = 0, defense = 0, carte_main = 0, nb_land = 0, nb_pv = 0, nb_autre = 0;
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++) {
            if (currentState->GetBattlefield()[i]->GetIsCreature()) {
                // si c'est toi qui est en train de regarder
                // on ne prend en compte que les creatures degages
                if (std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetIsTap()) {
                    if (currentState->GetBattlefield()[i]->GetIndJoueur() == joueur) {
                        nb_crea++;
                        offense += std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetForce();
                        defense += std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetEndurance();
                        //} else {
                        //    nb_crea--;
                        //    offense -= std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetEndurance();
                        //    defense -= std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetForce();
                    }
                } else {
                    if (currentState->GetBattlefield()[i]->GetIndJoueur() == joueur)
                        nb_autre++;
                    //else
                    //    nb_autre--;
                }
            } else if (currentState->GetBattlefield()[i]->GetIsLand()) {
                if (currentState->GetBattlefield()[i]->GetIndJoueur() == joueur)
                    nb_land++;
                //else
                //    nb_land--;
            }
        }
        carte_main = currentState->GetJoueurs()[joueur]->GetHand().size(); // - currentState->GetJoueurs()[1 - joueur]->GetHand().size();
        nb_pv = currentState->GetJoueurs()[joueur]->GetPv(); // - currentState->GetJoueurs()[1 - joueur]->GetPv();
        //prise en compte des manapool pour la qtt de terrain
        nb_land += currentState->GetJoueurs()[joueur]->GetManaPool()->GetBlack();
        nb_land += currentState->GetJoueurs()[joueur]->GetManaPool()->GetBlue();
        nb_land += currentState->GetJoueurs()[joueur]->GetManaPool()->GetGreen();
        nb_land += currentState->GetJoueurs()[joueur]->GetManaPool()->GetMulti();
        nb_land += currentState->GetJoueurs()[joueur]->GetManaPool()->GetInc();

        //nb_land -= currentState->GetJoueurs()[1 - joueur]->GetManaPool()->GetBlack();
        //nb_land -= currentState->GetJoueurs()[1 - joueur]->GetManaPool()->GetBlue();
        //nb_land -= currentState->GetJoueurs()[1 - joueur]->GetManaPool()->GetGreen();
        //nb_land -= currentState->GetJoueurs()[1 - joueur]->GetManaPool()->GetMulti();
        //nb_land -= currentState->GetJoueurs()[1 - joueur]->GetManaPool()->GetInc();

        int k1 = 5, k2 = 3, k3 = 3, k4 = 1, k5 = 1, k6 = 1, k7 = 3; // voir pour changer les coefficients plus tard
        int score = nb_crea * k1 + offense * k2 + defense * k3 + carte_main * k4 + nb_land * k5 + nb_pv * k6 + nb_autre*k7;
        std::cout << "\t\t nbCrea " << nb_crea << " offensif " << offense << " defensif " << defense << " mana " << nb_land << " pv " << nb_pv << " main " << carte_main << " permanent " << nb_autre << std::endl;
        
        for (int i = 0; i < compteur; i++)
            engine->RollBack();

        return score;
    }

    std::shared_ptr<Engine::Command> IA_heuristique::PhaseAttaque() {
        std::shared_ptr<Engine::AttackCommand> attaque(new Engine::AttackCommand());
        // si ta creature meurs pas et tue quelqu'un si elle est bloquee et que sa capacite n'est pas rentable
        for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++)
            if (currentState->GetBattlefield()[i]->GetIsCreature() && currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetJoueurTour()) {
                int survie = std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetEndurance();
                bool tue = true;

                for (unsigned int j = 0; j < currentState->GetBattlefield().size(); j++)
                    if (currentState->GetBattlefield()[j]->GetIsCreature() && currentState->GetBattlefield()[j]->GetIndJoueur() == 1 - currentState->GetJoueurTour()) {
                        survie -= std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[j])->GetForce();
                        if (std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i])->GetForce() < std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[j])->GetEndurance())
                            tue = false;
                    }

                bool bonne_capa = false;
                if (!currentState->GetBattlefield()[i]->GetAbility().empty()) {
                    int actustate = EvalCmd(nullptr);
                    for (unsigned int j = 0; j < currentState->GetBattlefield()[i]->GetAbility().size(); j++)
                        if (!currentState->GetBattlefield()[i]->GetAbility()[i]->GetNeedTarget()) {
                            std::shared_ptr<Engine::CastCommand> cmd(new Engine::CastCommand(currentState->GetBattlefield()[i]->GetAbility()[j], currentState->GetBattlefield()[i], nullptr));
                            if (EvalCmd(cmd) > actustate)
                                bonne_capa = true;
                        } else {
                            // si la capa a besoin d'une cible, on teste toute les cibles envisageable, que ce soit sur la pile ou en jeu.
                            for (unsigned int k = 0; k < currentState->GetBattlefield().size(); k++)
                                if (!bonne_capa) {
                                    std::shared_ptr<Engine::CastCommand> cmd(new Engine::CastCommand(currentState->GetBattlefield()[i]->GetAbility()[j], currentState->GetBattlefield()[i], currentState->GetBattlefield()[k]));
                                    if (EvalCmd(cmd) > actustate)
                                        bonne_capa = true;
                                }
                            for (unsigned int k = 0; k < currentState->GetPile().size(); k++)
                                if (!bonne_capa) {
                                    std::shared_ptr<Engine::CastCommand> cmd(new Engine::CastCommand(currentState->GetBattlefield()[i]->GetAbility()[j], currentState->GetBattlefield()[i], currentState->GetPile()[k]));
                                    if (EvalCmd(cmd) > actustate)
                                        bonne_capa = true;
                                }
                        }

                    if (tue && (!bonne_capa || survie))
                        attaque->AddAttaquant(std::static_pointer_cast<Etat::Creature>(currentState->GetBattlefield()[i]));
                }
            }
        return attaque;
    }

    std::shared_ptr<Engine::Command> IA_heuristique::PhaseBloqueur() {
        // bloquage extremement simplifie
        // theoriquement, on pourrait aussi bloquer avec une creature "inutile",
        // bloquer avec plusieurs creature sur une même creature, chercher a tuer a tout prix etc.

        std::shared_ptr<Engine::BlockCommand> bloqueur(new Engine::BlockCommand());
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
                    bloqueur->AddBloqueur(creaJDef[j], attaquant[i]);
                    creaJDef.erase(creaJDef.begin() + j);
                    break;
                }

        return bloqueur;
    }

    void IA_heuristique::Penser() {
        std::shared_ptr<Engine::LetPriorityCommand> Past(std::shared_ptr<Engine::LetPriorityCommand>(new Engine::LetPriorityCommand()));
        int passer = EvalCmd(nullptr);

        std::vector<int> list_val_cmd;
        std::vector<std::shared_ptr<Engine::CastCommand> > list_cmd = GetListCommand();
        if (!list_cmd.empty()) {

            int indmax = 0, max = EvalCmd(list_cmd[0]);
            list_val_cmd.push_back(max);
            for (unsigned int i = 1; i < list_cmd.size(); i++) {
                list_val_cmd.push_back(EvalCmd(list_cmd[i]));
                if (list_val_cmd[i] > max) {
                    max = list_val_cmd[i];
                    indmax = i;
                }
            }

            std::vector<std::shared_ptr<Etat::Carte> > TerrainsJoueur;
            for (unsigned int i = 0; i < currentState->GetBattlefield().size(); i++) //Récupération des listes de terrians controlés par le joueur
                if ((currentState->GetBattlefield()[i]->GetIndJoueur() == currentState->GetJoueurTour()) && (currentState->GetBattlefield()[i]->GetIsLand()))
                    TerrainsJoueur.push_back(currentState->GetBattlefield()[i]);

            if (max > passer) {
                // on depense le mana (on admet que ça passe pas par la pile)
                auto obj = list_cmd[indmax]->GetObj();
                Etat::Cout cost;
                if (obj->GetIsCapacite()) {
                    if (std::static_pointer_cast<Etat::Capacite>(obj)->GetCategorie() == 2)
                        cost = std::static_pointer_cast<Etat::Active>(obj)->GetCost();
                } else
                    cost = std::static_pointer_cast<Etat::Carte>(obj)->GetCost();

                int b = 0, u = 0, g = 0, i = 0;
                for (unsigned int j = 0; j < TerrainsJoueur.size(); j++)
                    if (TerrainsJoueur[j]->GetName() == "Marais" && b < cost.GetBlack() && !TerrainsJoueur[j]->GetIsTap()) {
                        engine->AddCommand(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(TerrainsJoueur[i]->GetAbility()[0], TerrainsJoueur[i], nullptr)));
                        engine->AddCommand(Past);
                        engine->AddCommand(Past);
                        b++;
                    }
                for (unsigned int j = 0; j < TerrainsJoueur.size(); j++)
                    if (TerrainsJoueur[j]->GetName() == "Ile" && u < cost.GetBlue() && !TerrainsJoueur[j]->GetIsTap()) {
                        engine->AddCommand(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(TerrainsJoueur[i]->GetAbility()[0], TerrainsJoueur[i], nullptr)));
                        engine->AddCommand(Past);
                        engine->AddCommand(Past);
                        u++;
                    }
                for (unsigned int j = 0; j < TerrainsJoueur.size(); j++)
                    if (TerrainsJoueur[j]->GetName() == "Foret" && g < cost.GetGreen() && !TerrainsJoueur[j]->GetIsTap()) {
                        engine->AddCommand(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(TerrainsJoueur[i]->GetAbility()[0], TerrainsJoueur[i], nullptr)));
                        engine->AddCommand(Past);
                        engine->AddCommand(Past);
                        g++;
                    }
                for (unsigned int j = 0; j < TerrainsJoueur.size(); j++)
                    if (i < cost.GetInc() && !TerrainsJoueur[j]->GetIsTap()) {
                        engine->AddCommand(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(TerrainsJoueur[i]->GetAbility()[0], TerrainsJoueur[i], nullptr)));
                        engine->AddCommand(Past);
                        engine->AddCommand(Past);
                        i++;
                    }
            }
            if (max > passer) {
                // on depense le mana (on admet que ça passe pas par la pile)
                auto obj = list_cmd[indmax]->GetObj();
                Etat::Cout cost;
                if (obj->GetIsCapacite()) {
                    if (std::static_pointer_cast<Etat::Capacite>(obj)->GetCategorie() == 2)
                        cost = std::static_pointer_cast<Etat::Active>(obj)->GetCost();
                } else
                    cost = std::static_pointer_cast<Etat::Carte>(obj)->GetCost();

                int b = 0, u = 0, g = 0, i = 0;
                for (unsigned int j = 0; j < TerrainsJoueur.size(); j++)
                    if (TerrainsJoueur[j]->GetName() == "Marais" && b < cost.GetBlack() && !TerrainsJoueur[j]->GetIsTap()) {
                        engine->AddCommand(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(TerrainsJoueur[i]->GetAbility()[0], TerrainsJoueur[i], nullptr)));
                        engine->AddCommand(Past);
                        engine->AddCommand(Past);
                        b++;
                    }
                for (unsigned int j = 0; j < TerrainsJoueur.size(); j++)
                    if (TerrainsJoueur[j]->GetName() == "Ile" && u < cost.GetBlue() && !TerrainsJoueur[j]->GetIsTap()) {
                        engine->AddCommand(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(TerrainsJoueur[i]->GetAbility()[0], TerrainsJoueur[i], nullptr)));
                        engine->AddCommand(Past);
                        engine->AddCommand(Past);
                        u++;
                    }
                for (unsigned int j = 0; j < TerrainsJoueur.size(); j++)
                    if (TerrainsJoueur[j]->GetName() == "Foret" && g < cost.GetGreen() && !TerrainsJoueur[j]->GetIsTap()) {
                        engine->AddCommand(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(TerrainsJoueur[i]->GetAbility()[0], TerrainsJoueur[i], nullptr)));
                        engine->AddCommand(Past);
                        engine->AddCommand(Past);
                        g++;
                    }
                for (unsigned int j = 0; j < TerrainsJoueur.size(); j++)
                    if (i < cost.GetInc() && !TerrainsJoueur[j]->GetIsTap()) {
                        engine->AddCommand(std::shared_ptr<Engine::CastCommand>(new Engine::CastCommand(TerrainsJoueur[i]->GetAbility()[0], TerrainsJoueur[i], nullptr)));
                        engine->AddCommand(Past);
                        engine->AddCommand(Past);
                        i++;
                    }
                engine->Update();

                engine->AddCommand(list_cmd[indmax]);
            } else
                engine->AddCommand(Past);
        } else
            engine->AddCommand(Past);
    }
}


