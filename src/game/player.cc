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

  player.active_bullet_ = player.tank_.ShootBullet();
  player.active_bullet_.Stop();

  json_object.at(JsonManager::kJsonLaserColorKey).get_to(player.laser_color_);
}

void Player::ConfigureTank(const TankDimensions& dimensions, float initial_y) {
  tank_.ConfigureTankDimensions(dimensions);
}

} // namespace artillery
