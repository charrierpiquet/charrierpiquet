// Generated by dia2code
#ifndef SERVER__USERSERVICE__H
#define SERVER__USERSERVICE__H

#include <json/json.h>

namespace server {
  class Game;
  class AbstractService;
}

#include "HttpStatus.h"
#include "AbstractService.h"
#include "Game.h"

namespace server {

  /// class UserService - 
  class UserService : public server::AbstractService {
    // Associations
    // Attributes
  protected:
    Game& game;
    // Operations
  public:
    UserService (Game& gm);
    HttpStatus get (Json::Value& out, int id) const;
    HttpStatus post (const Json::Value& in, int id);
    HttpStatus put (Json::Value& out, const Json::Value& in);
    HttpStatus remove (int id);
    // Setters and Getters
    Game& getGame() const;
    void setGame(const Game&& game);
  };

};

#endif
