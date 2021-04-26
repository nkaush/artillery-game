//
// Created by Neil Kaushikkar on 4/24/21.
//

#ifndef ARTILLERY_PLAYER_H
#define ARTILLERY_PLAYER_H

#include "core/bullet.h"
#include "core/tank.h"

#include <nlohmann/json.hpp>
#include "cinder/gl/gl.h"

namespace artillery {

class Player {
 public:
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

  void ConfigureTank(const TankConfiguration& dimensions, float initial_y);

  void Draw(const glm::vec2& mouse_location, bool is_current_player) const;

  void PointTankBarrel(const glm::vec2& mouse_location);

  Bullet ShootBullet() const;

 private:
  Tank tank_;

  ci::ColorA8u laser_color_;
};

} // namespace artillery

#endif  // ARTILLERY_PLAYER_H
