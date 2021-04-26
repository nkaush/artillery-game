//
// Created by Neil Kaushikkar on 4/24/21.
//

#include "game/player.h"

#include "core/json_manager.h"

namespace artillery {

using ci::ColorA8u;
using glm::vec2;

void to_json(nlohmann::json& json_object, const Player& player) {}

void from_json(const nlohmann::json& json_object, Player& player) {
  player.tank_ =
      Tank(vec2(json_object.at(JsonManager::kJsonStartingXKey).get<float>(), 0),
           json_object.at(JsonManager::kJsonTankColorKey).get<ColorA8u>(),
           json_object.at(JsonManager::kJsonBulletColorKey).get<ColorA8u>());

  json_object.at(JsonManager::kJsonLaserColorKey).get_to(player.laser_color_);
}

void Player::ConfigureTank(const TankConfiguration& config, float initial_y) {
  tank_.ConfigureTank(config, initial_y);
}

void Player::Draw(const vec2& mouse_location, bool is_current_player) const {
  if (is_current_player) {
    ci::gl::color(laser_color_);
    ci::gl::drawLine(tank_.GetBarrelPivotPosition(), mouse_location);
  }

  tank_.Draw();
}

Bullet Player::ShootBullet() const {
  return tank_.ShootBullet();
}

void Player::PointTankBarrel(const vec2& mouse_location) {
  tank_.PointBarrel(mouse_location);
}

} // namespace artillery
