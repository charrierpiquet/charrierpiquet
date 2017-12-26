/** 
 * @file UserDB.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "Game.hpp"
namespace server
{
Game::Game() : idseq(1) {
    
}

const Joueur* Game::getUser (int id) const {
    auto ite = users.find(id);
    if (ite == users.cend())
        return nullptr;
    return ite->second.get();
}

int Game::getNbUser() const
{
	return users.size();
}

int Game::addUser (unique_ptr<Joueur> user) {
    int id = idseq++;
    users.insert(std::make_pair(id,std::move(user)));
    return id;
}

void Game::setUser (int id, unique_ptr<Joueur> user) {
    users[id] = std::move(user);
    if (id > idseq) {
        idseq = id;
    }
}

void Game::removeUser (int id) {
    auto ite = users.find(id);
    if (ite == users.end())
        return;
    users.erase(ite);
}

const std::map<int,std::unique_ptr<Joueur> >& Game::getUsers() const{
	return users;
}

}
