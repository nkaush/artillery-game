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
      current_player_idx_(0) {
  bullet_.Stop();
}

void to_json(json& json_object, const GameEngine& game_engine) {}

void from_json(const json& json_object, GameEngine& game_engine) {
  json_object.at(JsonManager::kJsonTerrainKey).get_to(game_engine.terrain_); // TODO Get height at index

  json radius_scalar = json_object.at(JsonManager::kJsonBlastRadiusScalarKey);
  radius_scalar.get_to(game_engine.blast_radius_scalar_);

  json min_radius = json_object.at(JsonManager::kJsonMinBlastRadiusKey);
  min_radius.get_to(game_engine.min_blast_radius_);

  json max_radius = json_object.at(JsonManager::kJsonMaxBlastRadiusKey);
  max_radius.get_to(game_engine.max_blast_radius_);

  json configuration = json_object.at(JsonManager::kJsonTankConfigurationKey);
  auto dimensions = configuration.get<TankConfiguration>();

  json_object.at(JsonManager::kJsonPlayersKey).get_to(game_engine.players_);

  for (Player& player : game_engine.players_) {
    player.ConfigureTank(dimensions, 360); // TODO set this
  }

  Player first_player = game_engine.players_.at(game_engine.current_player_idx_);
  game_engine.bullet_ = first_player.ShootBullet();
  game_engine.bullet_.Stop();
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

  if (IsBulletCollidingWithTerrain() && bullet_.IsActive()) {
    bullet_.Stop();
    terrain_.DestroyTerrainInRadius(bullet_.GetPosition(),
                                    CalculateBulletImpactRadius());
  }

  float x_coord = bullet_.GetPosition().x;
  float radius = bullet_.GetRadius();

  bool is_bullet_past_map_bound =
      x_coord - radius > static_cast<float>(terrain_.GetMaxWidth());
  is_bullet_past_map_bound |= x_coord + radius < 0;

  if (is_bullet_past_map_bound) {
    bullet_.Stop();
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
