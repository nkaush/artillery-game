//
// Created by Neil Kaushikkar on 4/18/21.
//

#ifndef ARTILLERY_TANK_H
#define ARTILLERY_TANK_H

#include "core/tank_configuration.h"
#include "core/bullet.h"

#include "utilities/json_manager.h"

#include <nlohmann/json.hpp>
#include "cinder/gl/gl.h"

namespace artillery {

/**
 * This class is an abstraction to represent a player's tank.
 */
class Tank {
 public:
  /**
   * This macro from from the nlohmann::json parsing library will generate the
   * boilerplate code required to construct a Tank object with the default
   * constructor and populate it with fields from the json. The macro also
   * generates boilerplate code to serialize this object.
   */
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(
      Tank, chassis_position_, chassis_color_, bullet_color_)

  /**
   * Default constructor used by nlohmann::json to deserialize Player objects.
   */
  Tank();

  /**
   * Creates a new tank object with the specified position and color.
   * Also loads the color of the bullets this tank shoots.
   * @param chassis_position - a vec2 indicating the position of the tank
   * @param chassis_color - a ColorA8u indicating the color of the tank
   * @param bullet_color - a ColorA8u indicating the color of the tank's bullets
   */
  Tank(const glm::vec2& chassis_position, const ci::ColorA8u& chassis_color,
       const ci::ColorA8u& bullet_color);

  /**
   * Sets up the tank's treads, chassis, and turret according to the config
   * specified in the passed TankConfiguration struct. To avoid repetitive
   * json, this method was created to initialize all tanks with 1 struct.
   * @param config - a TankConfiguration struct with information on the
   *                 dimensions of all of the tank's components listed above
   */
  void ConfigureTank(const TankConfiguration& config);

  /**
   * Sets the height of the tank in the frame. Used when configuring the tank
   * after creating it with deserialized json.
   * @param treads_y1 - a float indicating the 1st y-coordinate of the treads
   * @param treads_y2 - a float indicating the 2nd y-coordinate of the treads
   */
  void SetYCoordinate(float treads_y1, float treads_y2);

  /**
   * Draws this tank object in the window.
   */
  void Draw() const;

  /**
   * Creates a Bullet object with initial position and velocity dependent
   * on the direction and magnitude of the tank's barrel.
   * @return a Bullet with initial speed and direction set by the user's mouse
   */
  Bullet ShootBullet() const;

  /**
   * Sets the barrel angle according to the tank's relative position and
   * the position being pointed at. Also sets the potential velocity of a
   * bullet, if a bullet were to be fired at that instant.
   * @param position_pointed_at - a vec2 indicating the point the barrel is
   * being pointed at.
   */
  void PointBarrel(const glm::vec2& position_pointed_at);

  void UpdatePosition(const glm::vec2& velocity);

  /**
   * Getter for the pivot position of the tank's barrel.
   * @return a vec2 indicating where the point the barrel pivots
   */
  const glm::vec2& GetBarrelPivotPosition() const;

  /**
   * Getter for the angle the barrel is rotated between -1 * PI and PI.
   * @return a float indicating the barrel's angle of rotation
   */
  float GetBarrelRotation() const;

  std::pair<float, float> GetTreadsXCoordinates() const;

  std::vector<glm::vec2> PredictBulletPath(size_t aim_assistance) const;

 private:
  // Tracks the position of the tank's chassis
  glm::vec2 chassis_position_;
  glm::vec2 chassis_offset_;

  // Used when the user requests to shoot a bullet
  glm::vec2 barrel_pivot_position_;
  glm::vec2 loaded_bullet_velocity_;
  glm::vec2 bullet_velocity_damping_;

  // Used in drawing the tank chassis
  float chassis_rounding_;
  float chassis_rotation_;
  float tread_wheel_radius_;
  float tread_wheel_padding_;

  // Used when drawing the tank turret
  float barrel_length_;
  float barrel_radius_;
  float barrel_rotation_;
  float turret_radius_;
  float barrel_span_;

  // Used when drawing the tank's components
  ci::Rectf chassis_rect_;
  ci::Rectf barrel_rect_;
  ci::Rectf treads_rect_;

  // Used when drawing the tank's components
  ci::ColorA8u chassis_color_;
  ci::ColorA8u bullet_color_;
  ci::ColorA8u tread_color_;

  /**
   * Draws the tank's barrel; transforms a reference frame to pivot position.
   */
  void DrawBarrel() const;

  /**
   * Sets the tank's chassis dimensions. Used when configuring the tank
   * after creating it with deserialized json.
   * @param config - a TankConfiguration struct with information on the
   *                 dimensions of all of the tank's components
   */
  void ConfigureChassis(const TankConfiguration& config);

  /**
   * Sets the tank's turret and barrel dimensions. Used when configuring
   * the tank after creating it with deserialized json.
   * @param config - a TankConfiguration struct with information on the
   *                 dimensions of all of the tank's components
   */
  void ConfigureTurretAndBarrel(const TankConfiguration& config);

  /**
   * Sets the tank's tread dimensions. Used when configuring the tank
   * after creating it with deserialized json.
   * @param config - a TankConfiguration struct with information on the
   *                 dimensions of all of the tank's components
   */
  void ConfigureTreads(const TankConfiguration& config);
};

} // namespace artillery

#endif  // ARTILLERY_TANK_H
