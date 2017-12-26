/** 
 * @file UserService.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "UserService.hpp"
<<<<<<< HEAD
#include "Game.h"
=======
>>>>>>> 89fd093ffbb508ed24727a92ec930da23f19dd05
namespace server
{
UserService::UserService (Game& gm) : AbstractService("/user"),
    game(gm) {
    
}

HttpStatus UserService::get (Json::Value& out, int id) const {
<<<<<<< HEAD
	if (id>=0)
	{
    		const Joueur* user = game.getUser(id);
		if (!user)
        		throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    		out["name"] = user->name;
    		out["free"] = user->free;
	}
	else
	{
		for (auto it=game.getUsers().begin(); it!=game.getUsers().end(); ++it)
		{
			Json::Value val;
			val["name"] = it->second->name;
			val["free"] = it->second->free;
			out.append(val);
		}
    	}
=======
    const Joueur* user = game.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    out["name"] = user->name;
    out["free"] = user->free;
>>>>>>> 89fd093ffbb508ed24727a92ec930da23f19dd05
    return HttpStatus::OK;
}

HttpStatus UserService::post (const Json::Value& in, int id) {
    const Joueur* user = game.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    unique_ptr<Joueur> usermod (new Joueur(*user));
<<<<<<< HEAD
    if (in.isMember("name"))
        usermod->name = in["name"].asString();
    if (in.isMember("free"))
        usermod->free = in["free"].asBool();
=======
    if (in.isMember("name")) {
        usermod->name = in["name"].asString();
    }
    if (in.isMember("free")) {
        usermod->free = in["free"].asBool();
    }
>>>>>>> 89fd093ffbb508ed24727a92ec930da23f19dd05
    game.setUser(id,std::move(usermod));
    return HttpStatus::NO_CONTENT;
}

HttpStatus UserService::put (Json::Value& out,const Json::Value& in) {
<<<<<<< HEAD
	// tester le nombre de joueurs et les parties en court
	if (game.getUsers().size()<2)
	{
	    std::string name = in["name"].asString();
	    bool age = false;
		if (in.isMember("free"))
			age = in["free"].asBool();
	    out["id"] = game.addUser(make_unique<Joueur>(name,age));
	    return HttpStatus::CREATED;
	}
	else
		throw ServiceException(HttpStatus::OK,"Nombre de joueur maximum deja atteint");
=======
    std::string name = in["name"].asString();
    bool age = in["free"].asBool();
    out["id"] = game.addUser(make_unique<Joueur>(name,age));
    return HttpStatus::CREATED;
>>>>>>> 89fd093ffbb508ed24727a92ec930da23f19dd05
}

HttpStatus UserService::remove (int id) {
    const Joueur* user = game.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    game.removeUser(id);
    return HttpStatus::NO_CONTENT;
}

<<<<<<< HEAD
}
=======
}
>>>>>>> 89fd093ffbb508ed24727a92ec930da23f19dd05
