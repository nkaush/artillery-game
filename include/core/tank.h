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
  Tank(const glm::vec2& chassis_position, const glm::vec2& turret_offset,
       float chassis_length, float chassis_height, float turret_radius,
       float barrel_length, float barrel_radius, uint8_t red_intensity,
       uint8_t green_intensity, uint8_t blue_intensity);

  void Draw();

  void Update();

  Bullet ShootBullet() const;

  void PointBarrel(const glm::vec2& position_pointed_at);

  void UpdatePosition(const glm::vec2& velocity);

  const glm::vec2& GetBarrelPivotPosition() const;

  float GetBarrelRotation() const;

  static const glm::vec2 kDefaultTurretOffset;

 private:
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

  static const ci::Color8u kDefaultTreadColor;

  static const glm::vec2 kBulletVelocityDamping;

  static constexpr float kTurretPadding = -2;
  static constexpr float kChassisRounding = 5;

  static constexpr float kTreadWheelRadius = 5;
  static constexpr float kTreadWheelPadding = 2;

  void DrawBarrel() const;
};

} // namespace artillery

#endif  // ARTILLERY_TANK_H
