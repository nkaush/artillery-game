//
// Created by Neil Kaushikkar on 4/18/21.
//

#ifndef ARTILLERY_BULLET_H
#define ARTILLERY_BULLET_H

#include "cinder/gl/gl.h"

namespace artillery {

/**
 * This class is used to represent bullets shot from Tanks.
 */
class Bullet {
  public:
    /**
     * Default constructor used when creating temporary bullets at game start.
     */
    Bullet();

    /**
     * Creates a new Bullet with specified initial position and velocity.
     * @param initial_position - a vec2 indicating the initial position
     * @param initial_velocity - a vec2 indicating the initial velocity
     * @param color - a ColorA8u object indicating the color of the bullet
     * @param radius - a float indicating the radius of the bullet
     */
    Bullet(const glm::vec2& initial_position, const glm::vec2& initial_velocity,
           const ci::ColorA8u& color, float radius);

    /**
     * Updates the bullet's position and velocity.
     */
    void AdvanceToNextFrame();

    /**
     * Updates the bullet's position with its velocity.
     */
    void UpdatePosition();

    /**
     * Updates the bullet's velocity with the constant acceleration of gravity.
     */
    void UpdateVelocity();

    /**
     * Stops the bullet's motion and stops the bullet from being drawn.
     */
    void Stop();

    /**
     * Draws this bullet in the window if the bullet is active.
     */
    void Draw() const;

    /**
     * Gets the position of the bullet.
     * @return a vec2 indicating the position of the bullet
     */
    const glm::vec2& GetPosition() const;

    /**
     * Gets the velocity of the bullet.
     * @return a vec2 indicating the velocity of the bullet
     */
    const glm::vec2& GetVelocity() const;

    /**
     * Gets the radius of the bullet.
     * @return a float indicating the radius of the bullet
     */
    float GetRadius() const;

    /**
     * Gets status of the bullet.
     * @return a bool indicating if the bullet is active (true) or not (false)
     */
    bool IsActive() const;

  private:
    // The constant acceleration of gravity as a vector with x-component = 0
    static const glm::vec2 kGravityAcceleration;

    // Vectors representing the 2D position and velocity of the bullet
    glm::vec2 position_;
    glm::vec2 velocity_;

    float radius_;

    // Indicates whether the bullet is mid-flight
    bool is_active_;

    // The color to draw the bullet with
    ci::Color8u color_;
};

} // namespace artillery

#endif //ARTILLERY_BULLET_H
