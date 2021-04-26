//
// Created by Neil Kaushikkar on 4/25/21.
//

#ifndef ARTILLERY_TANK_CONFIGURATION_H
#define ARTILLERY_TANK_CONFIGURATION_H

#include "core/json_manager.h"

#include <nlohmann/json.hpp>
#include "cinder/gl/gl.h"

namespace artillery {

/**
 * This struct is used to deserialize details for configuring tank objects.
 * This abstraction allows for json to NOT be repetitive while allowing
 * tank objects to have the same configuration (except colors).
 */
struct TankConfiguration {
  float chassis_rounding_;
  float chassis_length_;
  float chassis_height_;

  glm::vec2 turret_offset_;
  float turret_padding_;
  float turret_radius_;

  float barrel_length_;
  float barrel_radius_;

  ci::ColorA8u tread_color_;
  float tread_wheel_padding_;
  float tread_wheel_radius_;

  glm::vec2 bullet_velocity_damping_;
};

// macro from JSON parsing library that automatically (de)serializes this struct
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    TankConfiguration, chassis_rounding_, chassis_length_, chassis_height_,
    turret_offset_, turret_padding_, turret_radius_, barrel_length_,
    barrel_radius_, tread_wheel_padding_, tread_wheel_radius_, tread_color_,
    bullet_velocity_damping_)

} // namespace artillery

#endif  // ARTILLERY_TANK_CONFIGURATION_H
