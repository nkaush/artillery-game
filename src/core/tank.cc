//
// Created by Neil Kaushikkar on 4/18/21.
//

#include "core/tank.h"

namespace artillery {

using ci::Rectf;
using glm::vec2;

const vec2 Tank::kDefaultTurretOffset = vec2(22, 0);
const vec2 Tank::kBulletVelocityDamping = vec2(0.05, 0.05);
const ci::Color8u Tank::kDefaultTreadColor = ci::Color8u(0, 0, 0);

Tank::Tank(const vec2& chassis_position, const vec2& turret_offset,
           float chassis_length, float chassis_height, float turret_radius,
           float barrel_length, float barrel_radius, uint8_t red_intensity,
           uint8_t green_intensity, uint8_t blue_intensity)
    : chassis_position_(chassis_position),
      turret_offset_(turret_offset),
      chassis_offset_(vec2(-chassis_length / 2, -chassis_height / 2)),
      barrel_pivot_position_(turret_offset + chassis_offset_),
      /*chassis_length_(chassis_length), */
      barrel_length_(barrel_length),
      barrel_radius_(barrel_radius),
      turret_radius_(turret_radius),
//      chassis_rect_(chassis_position,
//                    chassis_position + vec2(chassis_length, chassis_height)),
      chassis_rect_(vec2(-chassis_length / 2, -chassis_height / 2),
                    vec2(chassis_length / 2, chassis_height / 2)),
      barrel_rect_(vec2(turret_radius + kTurretPadding, -barrel_radius),
                   vec2(turret_radius + barrel_length, barrel_radius)),
      chassis_color_(red_intensity, green_intensity, blue_intensity),
      tread_color_(kDefaultTreadColor) {
  vec2 upper_pt = vec2((-chassis_length / 2) + kTreadWheelPadding,
                       (chassis_height / 2) - kTreadWheelRadius);
  vec2 lower_pt = vec2((chassis_length / 2) - kTreadWheelPadding,
                       (chassis_height / 2) + kTreadWheelRadius);

  treads_rect_ = Rectf(upper_pt, lower_pt);
}

void Tank::Draw() {
  ci::gl::color(chassis_color_);

  ci::gl::pushMatrices(); ///
  // Move the origin to the pivot point at the barrel
  ci::gl::translate(chassis_position_);


  ci::gl::drawSolidRoundedRect(chassis_rect_, kChassisRounding); // chassis

  ci::gl::color(tread_color_);
  ci::gl::drawSolidRoundedRect(treads_rect_, kTreadWheelRadius); // treads

  barrel_pivot_position_ = (turret_offset_ + chassis_offset_);

  DrawBarrel();

  ci::gl::color(ci::Color("blue"));
  ci::gl::drawSolidCircle(vec2(), 2); // turret

  ci::gl::popMatrices(); ///
}

void Tank::DrawBarrel() const {
  // Adapted from: https://discourse.libcinder.org/t/what-is-the-best-way-to-rotate-rectangles-images/410/4
//  ci::gl::pushMatrices();
  // Move the origin to the pivot point at the barrel
  ci::gl::translate(barrel_pivot_position_);

  // Pivot the reference grid
  ci::gl::rotate(barrel_rotation_);

  ci::gl::drawSolidCircle(vec2(), turret_radius_); // turret
  // Draw draw the barrel at the origin of the pivoted reference grid
  ci::gl::drawSolidRect(barrel_rect_);
//  ci::gl::popMatrices();
}

Bullet Tank::ShootBullet() const {
  // subtract the barrel radius so the bullet starts completely inside barrel
  float barrel_span = barrel_length_ + turret_radius_ - barrel_radius_;
  vec2 barrel_extension(glm::cos(barrel_rotation_) * barrel_span,
                        glm::sin(barrel_rotation_) * barrel_span);
  vec2 initial_position = barrel_pivot_position_ + chassis_position_ + barrel_extension;

  return Bullet(initial_position, loaded_bullet_velocity_, 100, 100, 100, barrel_radius_);
}

void Tank::PointBarrel(const vec2& position_pointed_at) {
  loaded_bullet_velocity_ =
      (position_pointed_at - barrel_pivot_position_ - chassis_position_) * kBulletVelocityDamping;

  barrel_rotation_ = glm::atan(loaded_bullet_velocity_.y,
                               loaded_bullet_velocity_.x);
}

glm::vec2 Tank::GetBarrelPivotPosition() const {
  return barrel_pivot_position_ + chassis_position_;
}

} // namespace artillery
