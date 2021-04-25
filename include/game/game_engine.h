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
  // TODO convert fields to players
  // TODO finish serialization
  // TODO default constructor
 public:
  // These constants are used in deserializing the game settings json
  static const std::string kJsonTerrainKey;
  static const std::string kJsonMaxBlastRadiusKey;
  static const std::string kJsonMinBlastRadiusKey;
  static const std::string kJsonBlastRadiusScalar;

  GameEngine();

  /**
   * Used by the nlohmann::json library to serialize GameEngine objects.
   * @param json_object - the json object to serialize into
   * @param game_engine - the GameEngine object to serialize
   */
  friend void to_json(nlohmann::json& json_object,
                      const GameEngine& game_engine);

  /**
   * Used by the nlohmann::json library to deserialize GameEngine objects.
   * @param json_object - the json object to serialize from
   * @param game_engine - the GameEngine object to deserialize into
   */
  friend void from_json(const nlohmann::json& json_object,
                        GameEngine& game_engine);

  /**
   * Draws all the components of the game: tanks, bullets, terrain, lasers.
   * @param mouse_location - a vec2 indicating the location of the user's mouse
   *                         with respect to the app window.
   */
  void Draw(const glm::vec2& mouse_location) const;

  /**
   * Advances the game one frame. Updates the state of all components of the
   * game: tanks, bullets, terrain, lasers.
   */
  void AdvanceToNextFrame();

  /**
   * Points the barrel of the tank belonging to the player with an active turn
   * at the location where the user's mouse pointer is located.
   * @param mouse_location - a vec2 indicating the location of the user's mouse
   *                         with respect to the app window.
   */
  void PointActiveTankBarrel(const glm::vec2& mouse_location);

  /**
   * Shoots a bullet from the tank belonging to the player with an active turn.
   */
  void ShootBulletFromActiveTank();

  /**
   * Get the background color of the terrain.
   * @return a ColorA8u indicating the background color
   */
  const ci::ColorA8u& GetBackgroundColor() const;

 private:
  Tank tank_;
  Bullet bullet_;

  Terrain terrain_;

  float blast_radius_scalar_;
  size_t min_blast_radius_;
  size_t max_blast_radius_;

  /**
   * Checks whether the active bullet is colliding with the terrain.
   * @return a bool indicating whether the bullet is colliding with the terrain
   */
  bool IsBulletCollidingWithTerrain() const;

  /**
   * Calculates the radius of the blast caused by a bullet using the bullet
   * speed, the blast radius scalar, and the max and min radius sizes.
   */
  size_t CalculateBulletImpactRadius() const;
};

} // namespace artillery

#endif  // ARTILLERY_GAME_ENGINE_H
