//
// Created by Neil Kaushikkar on 4/23/21.
//

#include "game/game_engine.h"

#include "core/json_manager.h"

namespace artillery {

using nlohmann::json;
using glm::length;
using std::vector;
using glm::vec2;

GameEngine::GameEngine()
    : bullet_(),
      current_player_idx_(0) {}

void GameEngine::ConfigurePlayerTanks() {
  for (Player& player : players_) {
    player.ConfigureTank(tank_config_, 360); // TODO fix this + Get height at index
  }
}

const ci::ColorA8u& GameEngine::GetBackgroundColor() const {
  return terrain_.GetBackgroundColor();
}

void GameEngine::Draw(const glm::vec2& mouse_location) const {
  terrain_.Draw();
  bullet_.Draw();

  for (size_t idx = 0; idx < players_.size(); idx++) {
    players_.at(idx).Draw(mouse_location, idx == current_player_idx_);
  }
}

void GameEngine::AdvanceToNextFrame() {
  float x_coord = bullet_.GetPosition().x;
  float radius = bullet_.GetRadius();

  bool is_bullet_past_map_bound =
      x_coord - radius > static_cast<float>(terrain_.GetMaxWidth());
  is_bullet_past_map_bound |= x_coord + radius < 0;

  // If the bullet leaves the map bounds, make it inactive
  if (is_bullet_past_map_bound) {
    bullet_.Stop();
  }

  bullet_.AdvanceToNextFrame();

  // If the bullet is active and collides with some terrain, destroy the terrain
  if (IsBulletCollidingWithTerrain() && bullet_.IsActive()) {
    bullet_.Stop();
    terrain_.DestroyTerrainInRadius(bullet_.GetPosition(),
                                    CalculateBulletImpactRadius());
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
  players_.at(current_player_idx_).PointTankBarrel(mouse_location);
}

void GameEngine::ShootBulletFromActiveTank() {
  if (!bullet_.IsActive()) { // prevent player from removing bullet if in action
    bullet_ = players_.at(current_player_idx_).ShootBullet();
  }
}

void GameEngine::AdvanceToNextPlayerTurn() {
  current_player_idx_++;

  if (current_player_idx_ == players_.size()) {
    current_player_idx_ = 0;
  }
}

} // namespace artillery
