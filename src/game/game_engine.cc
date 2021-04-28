//
// Created by Neil Kaushikkar on 4/23/21.
//

#include "game/game_engine.h"

#include "utilities/json_manager.h"

namespace artillery {

using nlohmann::json;
using glm::length;
using std::vector;
using ci::Rectf;
using glm::vec2;

GameEngine::GameEngine()
    : bullet_(), blast_radius_scalar_(0), min_blast_radius_(0),
      max_blast_radius_(0), current_tank_idx_(0) {}

void GameEngine::ConfigureTanks() {
  for (Tank& tank : tanks_) {
    tank.Configure(tank_config_);

    UpdateTankYCoordinate(tank);
  }
}

void GameEngine::UpdateTankYCoordinate(Tank& tank) {
  std::pair<float, float> treads = tank.GetTreadsXCoordinates();

  size_t y1 = terrain_.GetStartingHeight(static_cast<size_t>(treads.first));
  size_t y2 = terrain_.GetStartingHeight(static_cast<size_t>(treads.second));

  auto y1_coord = static_cast<float>(y1);
  auto y2_coord = static_cast<float>(y2);

  tank.SetYCoordinate(y1_coord, y2_coord);
}

const ci::ColorA8u& GameEngine::GetBackgroundColor() const {
  return terrain_.GetBackgroundColor();
}

void GameEngine::Draw(const glm::vec2& mouse_location) const {
  terrain_.Draw();
  bullet_.Draw();

  for (size_t idx = 0; idx < tanks_.size(); idx++) {
    tanks_.at(idx).Draw(mouse_location, idx == current_tank_idx_);
  }
}

void GameEngine::AdvanceToNextFrame() {
  bullet_.AdvanceToNextFrame();

  vec2 bullet_position = bullet_.GetPosition();
  float radius = bullet_.GetRadius();

  bool is_bullet_past_map_bound =
      bullet_position.x - radius > static_cast<float>(terrain_.GetMaxWidth());
  is_bullet_past_map_bound |= bullet_position.x + radius < 0;
  is_bullet_past_map_bound |=
      bullet_position.y - radius > static_cast<float>(terrain_.GetMaxHeight());

  bool did_bullet_hit_terrain = IsBulletCollidingWithTerrain();
  bool should_bullet_stop = is_bullet_past_map_bound || did_bullet_hit_terrain;

  // If the bullet leaves the map bounds, make it inactive
  if (bullet_.IsActive() && should_bullet_stop) {
    bullet_.Stop();
    AdvanceToNextPlayerTurn();
  }

  // If the bullet is active and collides with some terrain, destroy the terrain
  if (did_bullet_hit_terrain) {
    terrain_.DestroyTerrainInRadius(bullet_.GetPosition(),
                                    CalculateBulletImpactRadius());
  }

  for (const Tank& tank : tanks_) {
    if (bullet_.IsActive() && tank.WasTankHit(bullet_position, radius)) {
    }
  }
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

void GameEngine::PointActiveTankBarrel(const vec2& mouse_location) {
  tanks_.at(current_tank_idx_).PointBarrel(mouse_location);
}

void GameEngine::ShootBulletFromActiveTank() {
  if (!bullet_.IsActive()) { // prevent tank from removing bullet if in action
    bullet_ = tanks_.at(current_tank_idx_).ShootBullet();
  }
}

void GameEngine::AdvanceToNextPlayerTurn() {
  current_tank_idx_++;

  if (current_tank_idx_ == tanks_.size()) {
    current_tank_idx_ = 0;
  }
}

void GameEngine::MoveActiveTank(const vec2& velocity) {
  Tank& current_tank = tanks_.at(current_tank_idx_);
  current_tank.UpdatePosition(velocity);

  std::pair<float, float> tank_position = current_tank.GetTreadsXCoordinates();
  auto max_width = static_cast<float>(terrain_.GetMaxWidth());

  // If the tank has not reached the bounds of the map, update it's y-coords
  if (tank_position.first > 0 && tank_position.second < max_width) {
    UpdateTankYCoordinate(current_tank);
  } else { // otherwise, undo advancing via velocity
    current_tank.UpdatePosition(velocity * vec2(-1, -1));
  }
}

} // namespace artillery
