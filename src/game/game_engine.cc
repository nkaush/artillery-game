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
    : bullet_(),
      current_player_idx_(0) {}

void GameEngine::ConfigurePlayerTanks() {
  for (Player& player : players_) {
    player.ConfigureTank(tank_config_);

    std::pair<float, float> treads = player.GetTankTreadsXCoordinates();
    size_t y1 = terrain_.GetStartingHeight(static_cast<size_t>(treads.first));
    size_t y2 = terrain_.GetStartingHeight(static_cast<size_t>(treads.second));

    auto y1_coord = static_cast<float>(y1);
    auto y2_coord = static_cast<float>(y2);

    player.SetTankYCoordinate(y1_coord, y2_coord);
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
