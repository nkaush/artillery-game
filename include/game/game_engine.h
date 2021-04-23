//
// Created by Neil Kaushikkar on 4/23/21.
//

#ifndef ARTILLERY_GAME_ENGINE_H
#define ARTILLERY_GAME_ENGINE_H

#include "core/terrain.h"
#include "core/bullet.h"
#include "core/tank.h"

#include "Cinder/gl/gl.h"

namespace artillery {

class GameEngine {
 public:
  GameEngine();

  void Draw(const glm::vec2& mouse_location) const;

  void AdvanceToNextFrame();

  void PointActiveTankBarrel(const glm::vec2& mouse_location);

  void ShootBulletFromActiveTank();

  bool IsBulletCollidingWithTerrain() const;

 private:
  Tank tank_;
  Bullet bullet_;

  Terrain terrain_;
};

} // namespace artillery

#endif  // ARTILLERY_GAME_ENGINE_H
