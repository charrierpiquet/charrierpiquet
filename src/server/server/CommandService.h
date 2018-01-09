// Generated by dia2code
#ifndef SERVER__COMMANDSERVICE__H
#define SERVER__COMMANDSERVICE__H

#include <vector>
#include <json/json.h>

namespace server {
  class AbstractService;
}

#include "HttpStatus.h"
#include "AbstractService.h"

namespace server {

  /// class CommandService - 
  class CommandService : public server::AbstractService {
    // Attributes
  private:
    std::vector<Json::Value>& listCommands;
    // Operations
  public:
    CommandService (std::vector<Json::Value>& val);
    HttpStatus get (Json::Value& out, int id) const;
    HttpStatus post (const Json::Value& in, int id);
    HttpStatus put (Json::Value& out, const Json::Value& in);
    HttpStatus remove (int id);
    // Setters and Getters
  };

};

#endif
