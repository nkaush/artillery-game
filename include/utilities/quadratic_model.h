//
// Created by Neil Kaushikkar on 4/25/21.
//

#ifndef ARTILLERY_QUADRATIC_MODEL_H
#define ARTILLERY_QUADRATIC_MODEL_H

#include "cinder/gl/gl.h"
#include <vector>

namespace artillery {

class QuadraticModel {
 public:
   /**
    * Creates a quadratic model by fitting a polynomial with degree 2 to the
    * curve that passes through all 3 points. The constructor must take 3
    * points (as opposed to a vector) since matrix and vec3 constructors are
    * NOT range based.
    * @param point_a - a vec2 indicating the a point this model passes through
    * @param point_b - a vec2 indicating the a point this model passes through
    * @param point_c - a vec2 indicating the a point this model passes through
    */
   QuadraticModel(const glm::vec2& point_a, const glm::vec2& point_b,
                  const glm::vec2& point_c);

  /**
   * Gets the constants that describe this quadratic model.
   * @return a vec3 of the constants that represent this model
   */
  const glm::vec3& GetQuadraticConstants() const;

  /**
   * Compute the y_value corresponding to the passed x_coordinate using the
   * constants of this quadratic model.
   * @param x_coordinate - a float indicating the x-coordinate to use
   * @return a float indicating the corresponding y-coordinate
   */
  float ComputePoint(float x_coordinate) const;

  /**
   * Returns a vector of all the corresponding y-values for each x value in the
   * range between start_x (inclusive) and end_x (exclusive).
   * @param start_x - a float to start the range at (inclusive)
   * @param end_x - a float to end the range at (exclusive)
   * @return a vector of floats computed by fitting each x_value in the range
   * to the quadratic modeled by this class.
   */
  const std::vector<float> ComputePointsInRange(float start_x, float end_x) const;

  /**
   * Create a range of floats from start to end, incremented by 1.
   * @param start - a float to start the range at (inclusive)
   * @param end - a float to end the range at (exclusive)
   * @return a range of floats from start to end
   */
  static const std::vector<float> CreateRange(float start, float end);

 private:
  // constants at each index correspond to terms with power equal to that index
  glm::vec3 quadratic_constants_;

  /**
   * Solves the system of equations given by the equation matrix and solutions.
   * @param design_matrix - a mat3 of constants in a linear system of equations
   * @param observation_vector - a vec3 of the solutions to the system
   * @return a vec3 of the solution to the system of equations
   */
  static const glm::vec3 Solve(
      const glm::mat3& design_matrix, const glm::vec3& observation_vector);
};

}

#endif  // ARTILLERY_QUADRATIC_MODEL_H
