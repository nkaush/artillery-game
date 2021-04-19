//
// Created by Neil Kaushikkar on 4/18/21.
//

#include "core/bullet.h"
#include "cinder/gl/gl.h"

namespace artillery {

using glm::vec2;

const glm::vec2 Bullet::kGravityAcceleration = vec2(0, 0.2);

Bullet::Bullet(const vec2& initial_position, const vec2& initial_velocity,
               uint8_t red_intensity, uint8_t green_intensity,
               uint8_t blue_intensity, float radius)
    : position_(initial_position), velocity_(initial_velocity), radius_(radius),
      color_(ci::Color8u(red_intensity, blue_intensity, green_intensity)) {}

void Bullet::UpdatePosition() {
    position_ += velocity_;
    velocity_ += kGravityAcceleration;
}

void Bullet::Draw() const {
  ci::gl::color(color_);
  ci::gl::drawSolidCircle(position_, radius_);
}

} // namespace artillery
