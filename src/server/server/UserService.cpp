/** 
 * @file UserService.cpp
 * @author Philippe-Henri Gosselin
 * @date 9 décembre 2015
 * @copyright CNRS
 */

#include "UserService.hpp"
namespace server
{
UserService::UserService (Game& gm) : AbstractService("/user"),
    game(gm) {
    
}

HttpStatus UserService::get (Json::Value& out, int id) const {
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
    return HttpStatus::OK;
}

HttpStatus UserService::post (const Json::Value& in, int id) {
    const Joueur* user = game.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    unique_ptr<Joueur> usermod (new Joueur(*user));

    if (in.isMember("name"))
        usermod->name = in["name"].asString();
    if (in.isMember("free"))
        usermod->free = in["free"].asBool();

    game.setUser(id,std::move(usermod));
    return HttpStatus::NO_CONTENT;
}

HttpStatus UserService::put (Json::Value& out,const Json::Value& in) {
	// tester le nombre de joueurs et les parties en court
	if (game.getUsers().size()<2)
	{
	    std::string name = in["name"].asString();
	    bool age = false;
		if (in.isMember("free"))
			age = in["free"].asBool();
	    out["id"] = game.addUser(make_unique<Joueur>(name,age))-1;
	    return HttpStatus::CREATED;
	}
	else
		throw ServiceException(HttpStatus::OK,"Nombre de joueur maximum deja atteint");
}

HttpStatus UserService::remove (int id) {
    const Joueur* user = game.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    game.removeUser(id);
    return HttpStatus::NO_CONTENT;
}

}
