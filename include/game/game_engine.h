//
// Created by Neil Kaushikkar on 4/23/21.
//

#ifndef ARTILLERY_GAME_ENGINE_H
#define ARTILLERY_GAME_ENGINE_H

#include "core/json_manager.h"
#include "core/terrain.h"
#include "core/bullet.h"

#include "game/player.h"

#include <nlohmann/json.hpp>
#include "Cinder/gl/gl.h"
#include <vector>

namespace artillery {

/**
 * This class contains and executes all the logic involved in this game.
 */
class GameEngine {
 public:
  /**
   * This macro from from the nlohmann::json parsing library will generate the
   * boilerplate code required to construct a GameEngine object with the
   * default constructor and populate it with fields from the json. The macro
   * also generates boilerplate code to serialize this object.
   */
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(GameEngine, players_, tank_config_, terrain_,
                                 blast_radius_scalar_, min_blast_radius_,
                                 max_blast_radius_)

  /**
   * Default constructor that initializes a default bullet.
   */
  GameEngine();

  /**
   * Pass the deserialized TankConfiguration object to each player's tank.
   */
  void ConfigurePlayerTanks();

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
  Bullet bullet_;

  Terrain terrain_;

  float blast_radius_scalar_;
  size_t min_blast_radius_;
  size_t max_blast_radius_;

  std::vector<Player> players_;
  size_t current_player_idx_;

  TankConfiguration tank_config_;

  /**
   * Moves to the next player's turn.
   */
  void AdvanceToNextPlayerTurn();

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
