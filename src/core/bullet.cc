//
// Created by Neil Kaushikkar on 4/18/21.
//

#include "core/bullet.h"
#include "cinder/gl/gl.h"

namespace artillery {

using glm::vec2;

const vec2 Bullet::kGravityAcceleration = vec2(0, 0.2);

const ci::Color8u Bullet::kDefaultColor = ci::Color8u(100, 100, 100);

Bullet::Bullet(const vec2& initial_position, const vec2& initial_velocity,
               float radius)
    : position_(initial_position), velocity_(initial_velocity), radius_(radius),
      color_(kDefaultColor) {}

void Bullet::UpdatePosition() {
    position_ += velocity_;
    velocity_ += kGravityAcceleration;
}

void Bullet::Draw() const {
  ci::gl::color(color_);
  ci::gl::drawSolidCircle(position_, radius_);
}

const glm::vec2& Bullet::GetVelocity() const {
  return velocity_;
}

const glm::vec2& Bullet::GetPosition() const{
  return position_;
}

} // namespace artillery
