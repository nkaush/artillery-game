//
// Created by Neil Kaushikkar on 4/25/21.
//

#ifndef ARTILLERY_QUADRATIC_SOLVER_H
#define ARTILLERY_QUADRATIC_SOLVER_H

#include "cinder/gl/gl.h"
#include <vector>

namespace artillery {

class QuadraticSolver {
 public:
  QuadraticSolver(const glm::vec2& point_a, const glm::vec2& point_b,
                  const glm::vec2& point_c);

  const glm::vec3& GetQuadraticConstants() const;

  float ComputePoint(float x_coordinate) const;

  std::vector<float> ComputePointsInRange(float start_x, float end_x) const;

  static std::vector<float> CreateRange(float start, float end);

 private:
  static constexpr float kSquarePower = 2.f;

  glm::vec3 quadratic_constants_;

  glm::mat3 design_matrix_;
  glm::vec3 observation_vector_;

  glm::vec3 Solve() const;
};

}


#endif  // ARTILLERY_QUADRATIC_SOLVER_H
