//
// Created by Neil Kaushikkar on 4/24/21.
//

#include "core/json_helper.h"
#include "game/player.h"

namespace artillery {

using ci::ColorA8u;
using std::string;
using glm::vec2;

const string Player::kJsonBulletColorKey = "bullet_color";
const string Player::kJsonLaserColorKey = "laser_color";
const string Player::kJsonTankColorKey = "chassis_color";
const string Player::kJsonStartingXKey = "starting_x";

void to_json(nlohmann::json& json_object, const Player& player) {}

void from_json(const nlohmann::json& json_object, Player& player) {
  player.tank_ =
      Tank(vec2(json_object.at(Player::kJsonStartingXKey).get<float>(), 0),
           json_object.at(Player::kJsonTankColorKey).get<ColorA8u>(),
           json_object.at(Player::kJsonBulletColorKey).get<ColorA8u>());

  player.active_bullet_ = player.tank_.ShootBullet();
  player.active_bullet_.Stop();

  json_object.at(Player::kJsonLaserColorKey).get_to(player.laser_color_);
}

void Player::ConfigureTank(const TankDimensions& dimensions, float initial_y) {
  tank_.ConfigureTankDimensions(dimensions);
}

} // namespace artillery
