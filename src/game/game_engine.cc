//
// Created by Neil Kaushikkar on 4/23/21.
//

#include "game/game_engine.h"

namespace artillery {

using glm::vec2;

GameEngine::GameEngine()
    : tank_(vec2(50, 400), Tank::kDefaultTurretOffset,
            40, 15, 10, 30, 3, 106, 113, 82),
      bullet_(vec2(-10, -10), vec2(0, 0), 1) {

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
}

void GameEngine::PointActiveTankBarrel(const vec2& mouse_location) {
  tank_.PointBarrel(mouse_location);
}

void GameEngine::ShootBulletFromActiveTank() {
  bullet_ = tank_.ShootBullet();
}

} // namespace artillery
