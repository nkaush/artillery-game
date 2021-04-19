//
// Created by Neil Kaushikkar on 4/18/21.
//

#ifndef ARTILLERY_BULLET_H
#define ARTILLERY_BULLET_H

#include "cinder/gl/gl.h"
#include "glm/vec2.hpp"

namespace artillery {

class Bullet {
  public:
    Bullet() = default;

    Bullet(const glm::vec2& initial_position, const glm::vec2& initial_velocity,
           uint8_t red_intensity, uint8_t green_intensity,
           uint8_t blue_intensity, float radius);

    void UpdatePosition();

    void Draw() const;

  private:
    glm::vec2 position_;
    glm::vec2 velocity_;

    float radius_;

    ci::Color8u color_;

    static const glm::vec2 kGravityAcceleration;
};

} // namespace artillery

#endif //ARTILLERY_BULLET_H
