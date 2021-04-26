//
// Created by Neil Kaushikkar on 4/18/21.
//

#include "core/bullet.h"

namespace artillery {

using glm::vec2;

const vec2 Bullet::kGravityAcceleration = vec2(0, 0.2);
const ci::Color8u Bullet::kDefaultColor = ci::Color8u(100, 100, 100);

Bullet::Bullet(
    const vec2& initial_position, const vec2& initial_velocity, float radius)
    : position_(initial_position),
      velocity_(initial_velocity),
      radius_(radius),
      is_active_(true),
      color_(kDefaultColor) {}

void Bullet::AdvanceToNextFrame() {
  if (is_active_) {
    UpdatePosition();
    UpdateVelocity();
  }
}

void Bullet::UpdateVelocity() {
  velocity_ += kGravityAcceleration;
}

void Bullet::UpdatePosition() {
  position_ += velocity_;
}

void Bullet::Stop() {
  is_active_ = false;
}

void Bullet::Draw() const {
  if (is_active_) {
    ci::gl::color(color_);
    ci::gl::drawSolidCircle(position_, radius_);
  }
}

const glm::vec2& Bullet::GetVelocity() const {
  return velocity_;
}

const glm::vec2& Bullet::GetPosition() const {
  return position_;
}

float Bullet::GetRadius() const {
  return radius_;
}

bool Bullet::IsActive() const {
  return is_active_;
}

} // namespace artillery
