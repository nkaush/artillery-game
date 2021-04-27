//
// Created by Neil Kaushikkar on 4/24/21.
//

#ifndef ARTILLERY_PLAYER_H
#define ARTILLERY_PLAYER_H

#include "utilities/json_manager.h"

#include "core/bullet.h"
#include "core/tank.h"

#include <nlohmann/json.hpp>
#include "cinder/gl/gl.h"

namespace artillery {

class Player {
 public:
  /**
   * This macro from from the nlohmann::json parsing library will generate the
   * boilerplate code required to construct a Player object with the default
   * constructor and populate it with fields from the json. The macro also
   * generates boilerplate code to serialize this object.
   */
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(Player, tank_, laser_color_)

  /**
   * Default constructor.
   */
  Player() = default;

  /**
   * Pass the given TankConfiguration struct to this player's tank to initialize
   * the tank's dimensions. Also, set the tank's y-coordinate.
   * @param config - a TankConfiguration struct with information on the
   *                 dimensions of all of the tank's components
   */
  void ConfigureTank(const TankConfiguration& config);

  /**
   * Position the tank on the map so it is just above the terrain
   * @param treads_y1 - a float indicating the 1st y-coordinate of the treads
   * @param treads_y2 - a float indicating the 2nd y-coordinate of the treads
   */
  void SetTankYCoordinate(float treads_y1, float treads_y2);

  /**
   * Draws this player's tank in the window. Also draws the laser aim if this
   * player is the current player with an active turn.
   * @param mouse_location - a vec2 indicating the position of the user's mouse
   * @param is_current_player - a bool indicating if it is this player's turn
   */
  void Draw(const glm::vec2& mouse_location, bool is_current_player) const;

  /**
   * Point this player's tank's barrel at the location given by the passed vec2.
   * @param mouse_location - a vec2 indicating the position of the user's mouse
   */
  void PointTankBarrel(const glm::vec2& mouse_location);

  /**
   * Shoot a bullet from this player's tank.
   * @return the Bullet object created when the player's tank shot a bullet
   */
  Bullet ShootBullet() const;

  std::pair<float, float> GetTankTreadsXCoordinates() const;

 private:
  Tank tank_;
  ci::ColorA8u laser_color_;
};

} // namespace artillery

#endif  // ARTILLERY_PLAYER_H
