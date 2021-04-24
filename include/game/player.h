//
// Created by Neil Kaushikkar on 4/24/21.
//

#ifndef ARTILLERY_PLAYER_H
#define ARTILLERY_PLAYER_H

#include "nlohmann/json.hpp"

#include "core/bullet.h"
#include "core/tank.h"

namespace artillery {

class Player {
 public:
  Player() = default;

  /**
   * Used by the nlohmann::json library to serialize Player objects.
   * @param json_object - the json object to serialize into
   * @param player - the Player object to serialize
   */
  void to_json(nlohmann::json& json_object, const Player& player);

  /**
   * Used by the nlohmann::json library to deserialize Player objects.
   * @param json_object - the json object to serialize from
   * @param player - the Player object to deserialize into
   */
  void from_json(const nlohmann::json& json_object, Player& player);
 private:
  Tank tank_;
  Bullet active_bullet_;
};

} // namespace artillery

#endif  // ARTILLERY_PLAYER_H
