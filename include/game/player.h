//
// Created by Neil Kaushikkar on 4/24/21.
//

#ifndef ARTILLERY_PLAYER_H
#define ARTILLERY_PLAYER_H

#include "core/bullet.h"
#include "core/tank.h"

#include "nlohmann/json.hpp"
#include "cinder/gl/gl.h"
#include <string>

namespace artillery {

class Player {
 public:
  static const std::string kJsonBulletColorKey;
  static const std::string kJsonLaserColorKey;
  static const std::string kJsonTankColorKey;
  static const std::string kJsonStartingXKey;

  Player() = default;

  /**
   * Used by the nlohmann::json library to serialize Player objects.
   * @param json_object - the json object to serialize into
   * @param player - the Player object to serialize
   */
  friend void to_json(nlohmann::json& json_object, const Player& player);

  /**
   * Used by the nlohmann::json library to deserialize Player objects.
   * @param json_object - the json object to serialize from
   * @param player - the Player object to deserialize into
   */
  friend void from_json(const nlohmann::json& json_object, Player& player);

  void ConfigureTank(const TankDimensions& dimensions, float initial_y);

 private:
  Tank tank_;
  Bullet active_bullet_;

  ci::ColorA8u laser_color_;
};

} // namespace artillery

#endif  // ARTILLERY_PLAYER_H
