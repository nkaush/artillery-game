//
// Created by Neil Kaushikkar on 4/23/21.
//

#include "game/game_engine.h"

#include "core/json_manager.h"

namespace artillery {

using nlohmann::json;
using glm::length;
using glm::vec2;

GameEngine::GameEngine()
    : tank_(vec2(50, 200), Tank::kDefaultTurretOffset,
            40, 15, 10, 30, 3, 106, 113, 82),
      bullet_(tank_.ShootBullet()) {
  bullet_.Stop();
}

void to_json(json& json_object, const GameEngine& game_engine) {}

void from_json(const json& json_object, GameEngine& game_engine) {
  json_object.at(JsonManager::kJsonTerrainKey).get_to(game_engine.terrain_);

  json radius_scalar = json_object.at(JsonManager::kJsonBlastRadiusScalar);
  radius_scalar.get_to(game_engine.blast_radius_scalar_);

  json min_radius = json_object.at(JsonManager::kJsonMinBlastRadiusKey);
  min_radius.get_to(game_engine.min_blast_radius_);

  json max_radius = json_object.at(JsonManager::kJsonMaxBlastRadiusKey);
  max_radius.get_to(game_engine.max_blast_radius_);
}

const ci::ColorA8u& GameEngine::GetBackgroundColor() const {
  return terrain_.GetBackgroundColor();
}

void GameEngine::Draw(const glm::vec2& mouse_location) const {
  terrain_.Draw();

  ci::gl::color(ci::Color("red"));
  ci::gl::drawLine(tank_.GetBarrelPivotPosition(), mouse_location);

  bullet_.Draw();
  tank_.Draw();
}

void GameEngine::AdvanceToNextFrame() {
  bullet_.AdvanceToNextFrame();

  if (IsBulletCollidingWithTerrain()) {
    bullet_.Stop();
    terrain_.DestroyTerrainInRadius(bullet_.GetPosition(),
                                    CalculateBulletImpactRadius());
  }

  float bullet_x_coord = bullet_.GetPosition().x;
  float bullet_radius = bullet_.GetRadius();

  bool is_bullet_past_map_bound =
      bullet_x_coord - bullet_radius > terrain_.GetMaxWidth();
  is_bullet_past_map_bound |= bullet_x_coord + bullet_radius < 0;

  if (is_bullet_past_map_bound) {
    bullet_.Stop();
  }
}

void GameEngine::PointActiveTankBarrel(const vec2& mouse_location) {
  tank_.PointBarrel(mouse_location);
}

void GameEngine::ShootBulletFromActiveTank() {
  bullet_ = tank_.ShootBullet();
}

bool GameEngine::IsBulletCollidingWithTerrain() const {
  const vec2& bullet_position = bullet_.GetPosition();
  auto x_coord = static_cast<size_t>(bullet_position.x);
  auto y_coord = static_cast<size_t>(bullet_position.y);

  return terrain_.GetTerrainVisibility(x_coord, y_coord)
         == TerrainVisibility::kVisible;
}

size_t GameEngine::CalculateBulletImpactRadius() const {
  float scaled_radius = length(bullet_.GetVelocity()) * blast_radius_scalar_;
  return glm::clamp(static_cast<size_t>(scaled_radius),
                    min_blast_radius_, max_blast_radius_);
}

} // namespace artillery
