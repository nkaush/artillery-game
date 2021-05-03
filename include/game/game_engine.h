//
// Created by Neil Kaushikkar on 4/23/21.
//

#ifndef ARTILLERY_GAME_ENGINE_H
#define ARTILLERY_GAME_ENGINE_H

#include "game_status.h"

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
      min_blast_size_, max_blast_size_, max_hitpoints_, tank_speed_on_move_,
      default_aim_assistance_)

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
   * Sets the aim assistance for each player depending on the value of the
   * bool in the corresponding index in the passed array. If the bool is true,
   * set the player aim assistance to the default aim assistance value, else
   * set the player aim assistance to zero.
   * @param has_aim_assistance - a vector of bool indicating the aim assistance
   *                             status to set for each corresponding player
   */
  void SetPlayerAimAssistance(const std::vector<bool>& has_aim_assistance);

  /**
   * Get the background color of the terrain.
   * @return a ColorA8u indicating the background color
   */
  const ci::ColorA8u& GetBackgroundColor() const;

  /**
   * Get the current game activity state - InProgress, GameStart, or GameOver.
   * @return a GameActivityState enum indicating the state of the game
   */
  const GameActivityState& GetGameActivityState() const;

  HitpointsUpdateStatus RetrieveHitpointsUpdateStatus();

  /**
   * Get the number of hitpoints each player has.
   * @return a vector of the hitpoints of each player, indexed by player number
   */
  std::vector<size_t> GetPlayerHitpoints() const;

  /**
   * Get whether each player has aim assistance enabled.
   * @return a vector of the aim assist status of each player,
   * indexed by player number
   */
  std::vector<bool> GetPlayerAimAssistanceStatus() const;

  /**
   * Get the color of each tank.
   * @return a vector of the color of each tank,
   * indexed by the corresponding player number
   */
  std::vector<ci::ColorA8u> GetTankColors() const;

  /**
   * Get the max number of hitpoints a player can have.
   * @return a float indicating the max number of hitpoints a player can have
   */
  float GetMaxHitpoints() const;

  /**
   * Restarts the game. Reloads the terrain. Reloads all player hitpoints.
   */
  void Restart();

 private:
  Bullet bullet_;
  Terrain terrain_;

  // Constants pertaining to calculating a bullet's impact size
  float blast_size_scalar_;
  size_t min_blast_size_;
  size_t max_blast_size_;

  // Constants pertaining to default in-game tank settings
  float max_hitpoints_;
  size_t default_aim_assistance_;
  glm::vec2 tank_speed_on_move_;

  // Stores information on the dimensions of tanks
  TankConfiguration tank_config_;

  // Stores each tank in the game with each tank representing a player
  std::vector<Tank> tanks_;

  // The index of the tank belonging to the player whose turn it is
  size_t current_tank_idx_;

  // The status of the game used to convey how to render UI elements
  GameActivityState game_state_;

  //
  HitpointsUpdateStatus hitpoints_update_status_;

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
   * Checks whether the bullet has left the game window bounds.
   * @return a bool indicating whether the bullet has left the window bounds
   */
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
   *
   * @return
   */
  bool WasGameWon() const;

  /**
   *
   */
  void FindNextSurvivingTank();

  void HandleBulletTerrainCollisions();

  void HandleBulletTankCollisions();
};

} // namespace artillery

#endif  // ARTILLERY_GAME_ENGINE_H
