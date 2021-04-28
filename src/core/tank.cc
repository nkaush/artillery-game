//
// Created by Neil Kaushikkar on 4/18/21.
//

#include "core/tank.h"

#include "core/terrain.h"

namespace artillery {

using nlohmann::json;
using ci::ColorA8u;
using ci::Rectf;
using glm::vec2;

Tank::Tank()
    : chassis_rounding_(0), chassis_rotation_(0), tread_wheel_radius_(0),
      tread_wheel_padding_(0), barrel_length_(0), barrel_radius_(0),
      barrel_rotation_(0), barrel_span_(0), turret_radius_(0),
      aim_assistance_(0) {}

Tank::Tank(const vec2& chassis_position, const ColorA8u& chassis_color,
           const ci::ColorA8u& bullet_color)
    : chassis_position_(chassis_position), chassis_rounding_(0),
      chassis_rotation_(0), tread_wheel_radius_(0), tread_wheel_padding_(0),
      barrel_length_(0), barrel_radius_(0), barrel_rotation_(0),
      barrel_span_(0), turret_radius_(0), aim_assistance_(0),
      chassis_color_(chassis_color), bullet_color_(bullet_color) {}

void Tank::Configure(const TankConfiguration& config) {
  ConfigureChassis(config);
  ConfigureTreads(config);
  ConfigureTurretAndBarrel(config);
}

void Tank::ConfigureChassis(const TankConfiguration& config) {
  float half_chassis_length = config.chassis_length_ / 2;
  float half_chassis_height = config.chassis_height_ / 2;

  // Set up the fields defining the chassis appearance
  chassis_offset_ = vec2(-1 * half_chassis_length, -1 * half_chassis_height);

  chassis_rect_ = Rectf(vec2(-1 * half_chassis_length, -1 * half_chassis_height),
                        vec2(half_chassis_length, half_chassis_height));
  chassis_rounding_ = config.chassis_rounding_;
}

void Tank::ConfigureTreads(const TankConfiguration& config) {
  float half_chassis_length = config.chassis_length_ / 2;
  float half_chassis_height = config.chassis_height_ / 2;

  // Set up the fields defining the tank treads appearance
  tread_color_ = config.tread_color_;
  tread_wheel_radius_ = config.tread_wheel_radius_;
  tread_wheel_padding_ = config.tread_wheel_padding_;

  vec2 tread_upper_pt(-1 * half_chassis_length + config.tread_wheel_padding_,
                      half_chassis_height - config.tread_wheel_radius_);
  vec2 tread_lower_pt(half_chassis_length - config.tread_wheel_padding_,
                      half_chassis_height + config.tread_wheel_radius_);
  treads_rect_ = Rectf(tread_upper_pt, tread_lower_pt);
}

void Tank::ConfigureTurretAndBarrel(const TankConfiguration& config) {
  // Set up the fields defining the turret appearance
  turret_radius_ = config.turret_radius_;
  turret_offset_ = config.turret_offset_;

  // Set up the fields defining the barrel appearance
  barrel_pivot_position_ =
      chassis_position_ + turret_offset_ + chassis_offset_;
  barrel_length_ = config.barrel_length_;
  barrel_radius_ = config.barrel_radius_;

  // subtract the barrel radius so the bullet starts completely inside barrel
  barrel_span_ = barrel_length_ + turret_radius_ - barrel_radius_;

  // Set the bounding dimensions of the barrel
  vec2 barrel_upper_pt(turret_radius_ + config.turret_padding_,
                       -1 * barrel_radius_);
  vec2 barrel_lower_pt(turret_radius_ + barrel_length_, barrel_radius_);
  barrel_rect_ = Rectf(barrel_upper_pt, barrel_lower_pt);

  // Set the damping multiplier of bullet velocity
  bullet_velocity_damping_ = config.bullet_velocity_damping_;
}

void Tank::SetYCoordinate(float treads_y1, float treads_y2) {
  std::pair<float, float> x_coords = GetTreadsXCoordinates();
  chassis_rotation_ =
      glm::atan(treads_y2 - treads_y1, x_coords.second - x_coords.first);

  float y_coordinate =
      (treads_y1 + treads_y2) / 2 - treads_rect_.y2 + tread_wheel_padding_;

  chassis_position_.y += (y_coordinate - chassis_position_.y);
  barrel_pivot_position_ = chassis_position_ + turret_offset_ + chassis_offset_;

}

void Tank::Draw(const vec2& mouse_location, bool is_current_player) const {
  DrawLaser(mouse_location, is_current_player);

  ci::gl::pushMatrices();
  DrawChassis();
  DrawBarrel();

  ci::gl::popMatrices();

  ci::gl::color(ci::Color(1, 1, 1));
}

void Tank::DrawChassis() const {
  // Move the origin to the pivot point at the barrel
  ci::gl::translate(chassis_position_);
  ci::gl::rotate(chassis_rotation_);

  ci::gl::color(chassis_color_);
  ci::gl::drawSolidRoundedRect(chassis_rect_, chassis_rounding_); // chassis

  ci::gl::color(tread_color_);
  ci::gl::drawSolidRoundedRect(treads_rect_, tread_wheel_radius_); // treads
  ci::gl::drawStrokedRoundedRect(chassis_rect_, chassis_rounding_); // chassis
}

void Tank::DrawBarrel() const {
  // Adapted from: https://discourse.libcinder.org/t/what-is-the-best-way-to-rotate-rectangles-images/410/4
  // Move the origin to the pivot point at the barrel
  ci::gl::translate(barrel_pivot_position_ - chassis_position_);

  // Pivot the reference grid
  ci::gl::rotate(barrel_rotation_ - chassis_rotation_);

  // Draw draw the barrel at the origin of the pivoted reference grid
  ci::gl::color(chassis_color_);
  ci::gl::drawSolidRect(barrel_rect_);

  ci::gl::color(tread_color_);
  ci::gl::drawStrokedRect(barrel_rect_); // turret

  ci::gl::color(chassis_color_);
  ci::gl::drawSolidCircle(vec2(), turret_radius_); // turret

  ci::gl::color(tread_color_);
  ci::gl::drawStrokedCircle(vec2(), turret_radius_); // turret
}

void Tank::DrawLaser(const vec2& mouse_location, bool is_current_player) const {
  if (is_current_player) {
    ci::gl::color(laser_color_);

    if (aim_assistance_ > 0) {
      for (const vec2& point : PredictBulletPath(aim_assistance_)) {
        ci::gl::drawSolidCircle(point, 2);
      }
    } else {
      ci::gl::drawLine(barrel_pivot_position_, mouse_location);
    }
  }
}

std::vector<vec2> Tank::PredictBulletPath(size_t aim_assistance) const {
  std::vector<vec2> points;

  vec2 working_velocity(loaded_bullet_velocity_);
  vec2 barrel_extension(glm::cos(barrel_rotation_) * barrel_span_,
                        glm::sin(barrel_rotation_) * barrel_span_);
  vec2 working_position = barrel_pivot_position_ + barrel_extension;

  for (size_t i = 0; i < aim_assistance; i++) {
    working_position += working_velocity;
    working_velocity += Bullet::kGravityAcceleration;

    if (i % 3 == 0) {
      points.push_back(working_position);
    }

    if (working_position.y > Terrain::kWindowHeight) {
      break;
    }
  }

  return points;
}

Bullet Tank::ShootBullet() const {
  // Find the change in coords after the barrel rotation
  vec2 barrel_extension(glm::cos(barrel_rotation_) * barrel_span_,
                        glm::sin(barrel_rotation_) * barrel_span_);
  vec2 initial_position = barrel_pivot_position_ + barrel_extension;

  return Bullet(initial_position, loaded_bullet_velocity_,
                bullet_color_, barrel_radius_);
}

void Tank::PointBarrel(const vec2& position_pointed_at) {
  // The velocity is the dampened magnitude of the vector to the mouse location
  loaded_bullet_velocity_ =
      (position_pointed_at - barrel_pivot_position_) * bullet_velocity_damping_;

  barrel_rotation_ = glm::atan(loaded_bullet_velocity_.y,
                               loaded_bullet_velocity_.x);
}

float Tank::GetBarrelRotation() const {
  return barrel_rotation_;
}

std::pair<float, float> Tank::GetTreadsXCoordinates() const {
  float x1 = treads_rect_.x1 + chassis_position_.x;
  float x2 = treads_rect_.x2 + chassis_position_.x;
  return {x1, x2};
}

void Tank::UpdatePosition(const glm::vec2& velocity) {
  barrel_pivot_position_ += velocity;
  chassis_position_ += velocity;
}

bool Tank::WasTankHit(const vec2& point, float radius) const {
  bool was_chassis_hit =
      chassis_rect_.getOffset(chassis_position_).contains(point);
  bool were_treads_hit =
      treads_rect_.getOffset(chassis_position_).contains(point);
  bool was_turret_hit =
      glm::distance(point, barrel_pivot_position_) < radius + turret_radius_;

  return was_chassis_hit || were_treads_hit || was_turret_hit;
}

} // namespace artillery
