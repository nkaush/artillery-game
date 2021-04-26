//
// Created by Neil Kaushikkar on 4/18/21.
//

#ifndef ARTILLERY_TANK_H
#define ARTILLERY_TANK_H

#include <nlohmann/json.hpp>

#include "cinder/gl/gl.h"
#include "core/bullet.h"
#include "core/tank_configuration.h"

namespace artillery {

class Tank {
 public:
  static const glm::vec2 kDefaultTurretOffset;

  Tank() = default;

  Tank(const glm::vec2& chassis_position, const ci::ColorA8u& chassis_color,
       const ci::ColorA8u& bullet_color);

  void ConfigureTank(const TankConfiguration& dimensions, float y_coordinate);

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
  static const glm::vec2 kBulletVelocityDamping;

  // TODO replace
  static constexpr float kChassisRounding = 5;

  static constexpr float kTreadWheelRadius = 5;

  glm::vec2 chassis_position_;
  glm::vec2 chassis_offset_;

  glm::vec2 turret_offset_;

  glm::vec2 barrel_pivot_position_;
  glm::vec2 loaded_bullet_velocity_;

  float chassis_rounding_;
  float tread_wheel_radius_;

  float barrel_length_;
  float barrel_radius_;
  float barrel_rotation_;
  float turret_radius_;

  ci::Rectf chassis_rect_;
  ci::Rectf barrel_rect_;
  ci::Rectf treads_rect_;

  ci::Color8u chassis_color_;
  ci::ColorA8u bullet_color_;
  ci::Color8u tread_color_;

  void DrawBarrel() const;

  void SetYCoordinate(float y_coordinate);

  void ConfigureChassis(const TankConfiguration& config);

  void ConfigureTurretAndBarrel(const TankConfiguration& config);

  void ConfigureTreads(const TankConfiguration& config);
};

} // namespace artillery

#endif  // ARTILLERY_TANK_H
