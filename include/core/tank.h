//
// Created by Neil Kaushikkar on 4/18/21.
//

#ifndef ARTILLERY_TANK_H
#define ARTILLERY_TANK_H

#include "bullet.h"

#include "cinder/gl/gl.h"
#include "glm/vec2.hpp"

namespace artillery {

class Tank {
 public:
  static const glm::vec2 kDefaultTurretOffset;

  /**
   * Creates a Tank object.
   * @param chassis_position - a vec2 of the initial position of the tank
   * @param turret_offset - a vec2 of the location of the turret in
   *                        relation to the tank body
   * @param chassis_length - a float indicating the length of the tank
   * @param chassis_height - a float indicating the height of the tank
   * @param turret_radius - a float indicating the radius of the tank turret
   * @param barrel_length - a float indicating the length of the tank barrel
   * @param barrel_radius - a float indicating the radius of the tank barrel
   * @param red_intensity - a float indicating the intensity of red to color
   * @param green_intensity -  a float indicating the intensity of green to color
   * @param blue_intensity - a float indicating the intensity of blue to color
   */
  Tank(const glm::vec2& chassis_position, const glm::vec2& turret_offset,
       float chassis_length, float chassis_height, float turret_radius,
       float barrel_length, float barrel_radius, uint8_t red_intensity,
       uint8_t green_intensity, uint8_t blue_intensity);

  /**
   * Draws this tank object in the window.
   */
  void Draw() const;

  /**
   * Creates a Bullet object with initial position and velocity dependent on the
   * direction and magnitude of the tank's barrel.
   * @return
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

  const glm::vec2& GetBarrelPivotPosition() const;

  float GetBarrelRotation() const;

 private:
  static const ci::Color8u kDefaultTreadColor;

  static const glm::vec2 kBulletVelocityDamping;

  static constexpr float kTurretPadding = -2;
  static constexpr float kChassisRounding = 5;

  static constexpr float kTreadWheelRadius = 5;
  static constexpr float kTreadWheelPadding = 2;

  glm::vec2 chassis_position_;

  glm::vec2 turret_offset_;
  glm::vec2 chassis_offset_;

  glm::vec2 barrel_pivot_position_;
  glm::vec2 loaded_bullet_velocity_;

//  float chassis_length_;

  float barrel_length_;
  float barrel_radius_;
  float barrel_rotation_;

  float turret_radius_;

  ci::Rectf chassis_rect_;
  ci::Rectf barrel_rect_;
  ci::Rectf treads_rect_;

  ci::Color8u chassis_color_;
  ci::Color8u tread_color_;

  void DrawBarrel() const;
};

} // namespace artillery

#endif  // ARTILLERY_TANK_H
