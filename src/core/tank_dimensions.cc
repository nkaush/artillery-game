//
// Created by Neil Kaushikkar on 4/25/21.
//

#include "core/tank_dimensions.h"

#include "core/json_manager.h"

namespace artillery {

glm::vec2 TankDimensions::GetTurretOffset() const {
  return turret_offset_.get<glm::vec2>();
}

ci::ColorA8u TankDimensions::GetTreadColor() const {
  return tread_color_.get<ci::ColorA8u>();
}

} // namespace artillery
