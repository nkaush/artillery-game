//
// Created by Neil Kaushikkar on 4/23/21.
//

#include "game/game_engine.h"

namespace artillery {

using glm::vec2;

GameEngine::GameEngine()
    : tank_(vec2(50, 400), Tank::kDefaultTurretOffset,
            40, 15, 10, 30, 3, 106, 113, 82),
      bullet_(tank_.ShootBullet()) {
  bullet_.Stop();
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
    terrain_.DestroyTerrainInRadius(bullet_.GetPosition(), Bullet::kBlastRadius);
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

} // namespace artillery
