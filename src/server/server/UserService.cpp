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
    const Joueur* user = game.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    out["name"] = user->name;
    out["free"] = user->free;
    return HttpStatus::OK;
}

HttpStatus UserService::post (const Json::Value& in, int id) {
    const Joueur* user = game.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    unique_ptr<Joueur> usermod (new Joueur(*user));
    if (in.isMember("name")) {
        usermod->name = in["name"].asString();
    }
    if (in.isMember("free")) {
        usermod->free = in["free"].asBool();
    }
    game.setUser(id,std::move(usermod));
    return HttpStatus::NO_CONTENT;
}

HttpStatus UserService::put (Json::Value& out,const Json::Value& in) {
    std::string name = in["name"].asString();
    bool age = in["free"].asBool();
    out["id"] = game.addUser(make_unique<Joueur>(name,age));
    return HttpStatus::CREATED;
}

HttpStatus UserService::remove (int id) {
    const Joueur* user = game.getUser(id);
    if (!user)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
    game.removeUser(id);
    return HttpStatus::NO_CONTENT;
}

}