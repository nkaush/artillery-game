//
// Created by Neil Kaushikkar on 4/23/21.
//

#ifndef ARTILLERY_GAME_ENGINE_H
#define ARTILLERY_GAME_ENGINE_H

#include "core/terrain.h"
#include "core/bullet.h"
#include "core/tank.h"

#include "nlohmann/json.hpp"
#include "Cinder/gl/gl.h"

#include <string>

namespace artillery {

class GameEngine {
  // TODO documentation
  // TODO convert fields to players
  // TODO finish serialization
  // TODO default constructor
 public:
  static const std::string kJsonTerrainKey;

  GameEngine();

  /**
   * Used by the nlohmann::json library to serialize GameEngine objects.
   * @param json_object - the json object to serialize into
   * @param game_engine - the GameEngine object to serialize
   */
  friend void to_json(nlohmann::json& json_object, const GameEngine& game_engine);

  /**
   * Used by the nlohmann::json library to deserialize GameEngine objects.
   * @param json_object - the json object to serialize from
   * @param game_engine - the GameEngine object to deserialize into
   */
  friend void from_json(const nlohmann::json& json_object, GameEngine& game_engine);

  void Draw(const glm::vec2& mouse_location) const;

  void AdvanceToNextFrame();

  void PointActiveTankBarrel(const glm::vec2& mouse_location);

  void ShootBulletFromActiveTank();

  bool IsBulletCollidingWithTerrain() const;

  const ci::ColorA8u& GetBackgroundColor() const;

 private:
  Tank tank_;
  Bullet bullet_;

  Terrain terrain_;
};

} // namespace artillery

#endif  // ARTILLERY_GAME_ENGINE_H
