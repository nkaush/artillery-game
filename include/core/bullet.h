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

    /**
     * Creates a new Bullet with specified initial position and velocity.
     * @param initial_position - a vec2 indicating the initial position
     * @param initial_velocity - a vec2 indicating the initial velocity
     * @param radius - a float indicating the radius of the bullet
     */
    Bullet(const glm::vec2& initial_position, const glm::vec2& initial_velocity,
           float radius);

    void AdvanceToNextFrame();

    /**
     * Updates the bullet's position with its velocity and updates the bullet's
     * velocity with the constant acceleration of gravity.
     */
    void UpdatePosition();

    void UpdateVelocity();

    /**
     * Draws this bullet in the window.
     */
    void Draw() const;

    const glm::vec2& GetPosition() const;

    const glm::vec2& GetVelocity() const;

  private:
    static const glm::vec2 kGravityAcceleration;

    static const ci::Color8u kDefaultColor;

    glm::vec2 position_;
    glm::vec2 velocity_;

    float radius_;

    ci::Color8u color_;
};

} // namespace artillery

#endif //ARTILLERY_BULLET_H
