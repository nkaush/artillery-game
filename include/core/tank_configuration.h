//
// Created by Neil Kaushikkar on 4/25/21.
//

#ifndef ARTILLERY_TANK_CONFIGURATION_H
#define ARTILLERY_TANK_CONFIGURATION_H

#include <nlohmann/json.hpp>
#include "cinder/gl/gl.h"

namespace artillery {

struct TankConfiguration {
  float chassis_rounding_;
  float chassis_length_;
  float chassis_height_;

  nlohmann::json turret_offset_;
  float turret_padding_;
  float turret_radius_;

  float barrel_length_;
  float barrel_radius_;

  nlohmann::json tread_color_;
  float tread_wheel_padding_;
  float tread_wheel_radius_;

  glm::vec2 GetTurretOffset() const;

  ci::ColorA8u GetTreadColor() const;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    TankConfiguration, chassis_rounding_, chassis_length_, chassis_height_,
    turret_offset_, turret_padding_, turret_radius_, barrel_length_,
    barrel_radius_, tread_wheel_padding_, tread_wheel_radius_, tread_color_)

} // namespace artillery

#endif  // ARTILLERY_TANK_CONFIGURATION_H
