//
// Created by Neil Kaushikkar on 4/24/21.
//

#include "game/player.h"

#include "utilities/json_manager.h"

namespace artillery {

using ci::ColorA8u;
using glm::vec2;

void Player::ConfigureTank(const TankConfiguration& config) {
  tank_.ConfigureTank(config);
}

void Player::SetTankYCoordinate(float treads_y1, float treads_y2) {
  tank_.SetYCoordinate(treads_y1, treads_y2);
}

void Player::Draw(const vec2& mouse_location, bool is_current_player) const {
  if (is_current_player) {
    ci::gl::color(laser_color_);

    if (aim_assistance_ > 0) {
      for (const vec2& point : tank_.PredictBulletPath(aim_assistance_)) {
        ci::gl::drawSolidCircle(point, 2);
      }
    } else {
      ci::gl::drawLine(tank_.GetBarrelPivotPosition(), mouse_location);
    }
  }

  tank_.Draw();
}

Bullet Player::ShootBullet() const {
  return tank_.ShootBullet();
}

void Player::PointTankBarrel(const vec2& mouse_location) {
  tank_.PointBarrel(mouse_location);
}

std::pair<float, float> Player::GetTankTreadsXCoordinates() const {
  return tank_.GetTreadsXCoordinates();
}

} // namespace artillery
