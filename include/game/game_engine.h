//
// Created by Neil Kaushikkar on 4/23/21.
//

#ifndef ARTILLERY_GAME_ENGINE_H
#define ARTILLERY_GAME_ENGINE_H

#include "utilities/json_manager.h"

#include "core/terrain.h"
#include "core/bullet.h"
#include "core/tank.h"

#include <nlohmann/json.hpp>
#include "cinder/gl/gl.h"
#include <vector>
#include <string>

namespace artillery {

/**
 * This struct contains information on how to render the bars that indicate
 * the number of hitpoints each player has.
 */
struct HitpointsRenderingSettings {
  glm::vec2 vertical_padding_;
  glm::vec2 horizontal_padding_;
  glm::vec2 label_padding_;

  size_t bar_height_;
  float bar_length_scalar_;

  std::string label_prefix_;
  std::string label_suffix_;

  ci::ColorA8u total_hitpoints_color_;
  ci::ColorA8u label_color_;
};

enum class GameState {
  kGameStart,
  kInProgress,
  kGameOver
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    HitpointsRenderingSettings, vertical_padding_, horizontal_padding_,
    bar_height_, bar_length_scalar_, total_hitpoints_color_, label_prefix_,
    label_suffix_, label_color_, label_padding_)

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
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(
      GameEngine, tanks_, tank_config_, terrain_, blast_size_scalar_,
      min_blast_size_, max_blast_size_, max_hitpoints_,
      hp_render_settings_, tank_speed_on_move_)

  /**
   * Default constructor that initializes a default bullet.
   */
  GameEngine();

  /**
   * Pass the deserialized TankConfiguration object to each player's tank.
   */
  void ConfigureTanks();

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
   * Move the tank representing the current player to the left or right, as
   * indicated, at the speed determined from the game settings.
   * @param should_move_left - a bool indicating whether the tank should move
   *                           left (true) or right (false)
   */
  void MoveCurrentTank(bool should_move_left);

  /**
   * Get the background color of the terrain.
   * @return a ColorA8u indicating the background color
   */
  const ci::ColorA8u& GetBackgroundColor() const;

  const GameState& GetGameState() const;

  void Reload();

 private:
  Bullet bullet_;
  Terrain terrain_;

  float blast_size_scalar_;
  size_t min_blast_size_;
  size_t max_blast_size_;
  float max_hitpoints_;

  std::vector<Tank> tanks_;
  size_t current_tank_idx_;

  glm::vec2 tank_speed_on_move_;

  GameState game_state_;

  TankConfiguration tank_config_;
  HitpointsRenderingSettings hp_render_settings_;

  /**
   * Moves to the next player's turn.
   */
  void AdvanceToNextPlayerTurn();

  /**
   * Checks whether the active bullet is colliding with the terrain.
   * @return a bool indicating whether the bullet is colliding with the terrain
   */
  bool IsBulletCollidingWithTerrain() const;

  bool IsBulletOutOfBounds() const;

  /**
   * Calculates the radius of the blast caused by a bullet using the bullet
   * speed, the blast radius scalar, and the max and min radius sizes.
   */
  size_t CalculateBulletImpactSize() const;

  /**
   * Update the y-coordinate of the given tank using the height of the terrain
   * at the tank's current x-coordinates. This method is required since tanks
   * do not have access to information about the terrain.
   * @param tank - the tank to update y-coordinates for
   */
  void UpdateTankYCoordinate(Tank& tank);

  /**
   * Draw a bar indicating the number of hitpoints the given tank has remaining.
   * @param tank - the tank to draw the hitpoints bar for
   * @param index - the index of the tank in the vector 'tanks_'
   */
  void DrawHitpointsBar(const Tank& tank, size_t index) const;
};

} // namespace artillery

#endif  // ARTILLERY_GAME_ENGINE_H
