//
// Created by Neil Kaushikkar on 4/23/21.
//

#include "game/game_engine.h"

#include "cinder/Rand.h"

namespace artillery {

using nlohmann::json;

using glm::length;
using glm::vec2;

using ci::Rectf;

using std::transform;
using std::vector;

GameEngine::GameEngine()
    : bullet_(), blast_size_scalar_(0), min_blast_size_(0),
      max_blast_size_(0), max_hitpoints_(0), default_aim_assistance_(0),
      current_tank_idx_(0), game_state_(GameActivityState::kGameStart),
      hitpoints_update_status_(HitpointsUpdateStatus::kForcedUpdate) {}

void GameEngine::ConfigureTanks() {
  for (Tank& tank : tanks_) {
    tank.Configure(tank_config_);
    UpdateTankYCoordinate(tank);
  }
}

void GameEngine::UpdateTankYCoordinate(Tank& tank) {
  std::pair<float, float> treads = tank.GetTreadsXCoordinates();

  // get the height of the terrain at the location of the tank's treads
  size_t y1 = terrain_.GetStartingHeight(static_cast<size_t>(treads.first));
  size_t y2 = terrain_.GetStartingHeight(static_cast<size_t>(treads.second));

  auto y1_coord = static_cast<float>(y1);
  auto y2_coord = static_cast<float>(y2);

  tank.SetYCoordinate(y1_coord, y2_coord);
}

void GameEngine::SetPlayerAimAssistance(const vector<bool>& has_aim_assistance) {
  for (size_t idx = 0; idx < has_aim_assistance.size(); idx++) {
    if (has_aim_assistance.at(idx)) {
      tanks_.at(idx).SetAimAssistance(default_aim_assistance_);
    } else {
      tanks_.at(idx).SetAimAssistance(0);
    }
  }
}

HitpointsUpdateStatus GameEngine::RetrieveHitpointsUpdateStatus() {
  HitpointsUpdateStatus status = hitpoints_update_status_;

  if (status != HitpointsUpdateStatus::kNoTanksHit) {
    hitpoints_update_status_ = HitpointsUpdateStatus::kNoTanksHit;
  }

  return status;
}

const ci::ColorA8u& GameEngine::GetBackgroundColor() const {
  return terrain_.GetBackgroundColor();
}

const GameActivityState& GameEngine::GetGameActivityState() const {
  return game_state_;
}

vector<size_t> GameEngine::GetPlayerHitpoints() const {
  vector<size_t> hitpoints(tanks_.size());
  auto getter = [] (const Tank& tank) { return tank.GetHitpoints(); };
  transform(tanks_.begin(), tanks_.end(), hitpoints.begin(), getter);

  return hitpoints;
}

std::vector<bool> GameEngine::GetPlayerAimAssistanceStatus() const {
  vector<bool> status(tanks_.size());
  auto checker = [] (const Tank& tank) { return tank.GetAimAssistance() > 0; };
  transform(tanks_.begin(), tanks_.end(), status.begin(), checker);

  return status;
}

vector<ci::ColorA8u> GameEngine::GetTankColors() const {
  vector<ci::ColorA8u> colors(tanks_.size());

  for (size_t idx = 0; idx < tanks_.size(); idx++) {
    colors.at(idx) = tanks_.at(idx).GetChassisColor();
  }

  return colors;
}

float GameEngine::GetMaxHitpoints() const {
  return max_hitpoints_;
}

void GameEngine::Draw(const glm::vec2& mouse_location) const {
  terrain_.Draw();

  for (size_t idx = 0; idx < tanks_.size(); idx++) {
    tanks_.at(idx).Draw(mouse_location, idx == current_tank_idx_);
  }

  bullet_.Draw();

  ci::gl::color(ci::Color(1, 1, 1));
}

void GameEngine::AdvanceToNextFrame() {
  bullet_.AdvanceToNextFrame();

  HandleBulletTerrainCollisions();
  HandleBulletTankCollisions();
}

void GameEngine::HandleBulletTerrainCollisions() {
  bool did_bullet_hit_terrain = IsBulletCollidingWithTerrain();
  bool should_bullet_stop = IsBulletOutOfBounds() || did_bullet_hit_terrain;

  // If the bullet leaves the map bounds, make it inactive
  if (bullet_.IsActive() && should_bullet_stop) {
    bullet_.Stop();
    AdvanceToNextPlayerTurn();

    // If the bullet is active and collides with terrain, destroy the terrain
    if (did_bullet_hit_terrain) {
      terrain_.DestroyTerrainInRadius(
          bullet_.GetPosition(), CalculateBulletImpactSize());
    }
  }
}

bool GameEngine::IsBulletOutOfBounds() const {
  vec2 bullet_position = bullet_.GetPosition();
  float radius = bullet_.GetRadius();

  // Check all bounds EXCEPT the top bound since a bullet can come back down
  bool is_bullet_past_map_bound =
      bullet_position.x - radius > static_cast<float>(terrain_.GetMaxWidth());

  is_bullet_past_map_bound |= bullet_position.x + radius < 0;

  is_bullet_past_map_bound |=
      bullet_position.y - radius > static_cast<float>(terrain_.GetMaxHeight());

  return is_bullet_past_map_bound;
}

bool GameEngine::IsBulletCollidingWithTerrain() const {
  const vec2& bullet_position = bullet_.GetPosition();
  auto x_coord = static_cast<size_t>(bullet_position.x);
  auto y_coord = static_cast<size_t>(bullet_position.y);

  return terrain_.GetTerrainVisibility(x_coord, y_coord)
         == TerrainVisibility::kVisible;
}

void GameEngine::HandleBulletTankCollisions() {
  bool were_tanks_hit = false;
  for (Tank& tank : tanks_) {
    if (bullet_.IsActive() && tank.WasTankHit(bullet_)) {
      were_tanks_hit = true;
      tank.SubtractHitpoints(CalculateBulletImpactSize());
    }
  }

  if (were_tanks_hit) {
    bullet_.Stop();
    AdvanceToNextPlayerTurn();
    hitpoints_update_status_ = HitpointsUpdateStatus::kTanksHit;
  }
}

void GameEngine::AdvanceToNextPlayerTurn() {
  if (game_state_ == GameActivityState::kGameStart) {
    game_state_ = GameActivityState::kInProgress;
  }

  if (WasGameWon()) {
    game_state_ = GameActivityState::kGameOver;
    return;
  }

  FindNextSurvivingTank();
}

bool GameEngine::WasGameWon() const {
  size_t tanks_alive = 0;
  for (const Tank& tank : tanks_) {
    if (tank.GetHitpoints() > 0) {
      tanks_alive++;
    }
  }

  // If there are 1 or fewer tanks alive, the game is finished
  return tanks_alive <= 1;
}

void GameEngine::FindNextSurvivingTank() {
  size_t starting_idx = current_tank_idx_;
  bool is_first_iteration = true;

  while(tanks_.at(current_tank_idx_).GetHitpoints() == 0 || is_first_iteration) {
    is_first_iteration = false;

    current_tank_idx_++;

    // if we have gone through each player's turn, go back to the 1st player
    if (current_tank_idx_ == tanks_.size()) {
      current_tank_idx_ = 0;
    }

    if (starting_idx == current_tank_idx_) {
      break;
    }
  }
}

size_t GameEngine::CalculateBulletImpactSize() const {
  float scaled_size = length(bullet_.GetVelocity()) * blast_size_scalar_;
  return glm::clamp(static_cast<size_t>(scaled_size),
                    min_blast_size_, max_blast_size_);
}

void GameEngine::PointActiveTankBarrel(const vec2& mouse_location) {
  tanks_.at(current_tank_idx_).PointBarrel(mouse_location);
}

void GameEngine::ShootBulletFromActiveTank() {
  if (!bullet_.IsActive()) { // prevent tank from removing bullet if in action
    bullet_ = tanks_.at(current_tank_idx_).ShootBullet();
  }
}

void GameEngine::MoveCurrentTank(bool should_move_left) {
  vec2 speed = tank_speed_on_move_;

  if (should_move_left) { // invert the velocity to move left
    speed *= vec2(-1, -1);
  }

  Tank& current_tank = tanks_.at(current_tank_idx_);
  current_tank.UpdatePosition(speed);

  std::pair<float, float> tank_position = current_tank.GetTreadsXCoordinates();
  auto max_width = static_cast<float>(terrain_.GetMaxWidth());

  // If the tank has not reached the bounds of the map, update it's y-coord
  if (tank_position.first > 0 && tank_position.second < max_width) {
    UpdateTankYCoordinate(current_tank);
  } else { // otherwise, undo advancing via velocity by negating the change
    current_tank.UpdatePosition(speed * vec2(-1, -1));
  }
}

void GameEngine::Restart() {
  terrain_.Reload();

  current_tank_idx_ = static_cast<size_t>(
      ci::randInt(0, static_cast<int>(tanks_.size() - 1)));
  game_state_ = GameActivityState::kInProgress;
  hitpoints_update_status_ = HitpointsUpdateStatus::kForcedUpdate;

  for (Tank& tank : tanks_) {
    tank.ResetHitpoints(static_cast<size_t>(max_hitpoints_));

    std::pair<float, float> x_bounds = tank.GetXBounds();
    float min_bound = glm::max(-1 * x_bounds.first, 0.0f);
    float max_bound =
        static_cast<float>(terrain_.GetMaxWidth()) - x_bounds.second - 1;

    tank.SetXCoordinate(ci::randFloat(min_bound, max_bound));
    UpdateTankYCoordinate(tank);
  }
}

} // namespace artillery
