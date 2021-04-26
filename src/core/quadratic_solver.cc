//
// Created by Neil Kaushikkar on 4/25/21.
//

#include "core/quadratic_solver.h"

#include <numeric>

namespace artillery {

using std::vector;
using glm::mat3;
using glm::vec3;
using glm::vec2;

QuadraticSolver::QuadraticSolver(
    const vec2& point_a, const vec2& point_b, const vec2& point_c) {
  vec3 second_column = vec3(point_a.x, point_b.x, point_c.x);

  vec3 third_column = vec3(glm::pow(point_a.x, kSquarePower),
                           glm::pow(point_b.x, kSquarePower),
                           glm::pow(point_c.x, kSquarePower));

  design_matrix_ = mat3(vec3(1), second_column, third_column);
  observation_vector_ = vec3(point_a.y, point_b.y, point_c.y);

  quadratic_constants_ = Solve();
}

vec3 QuadraticSolver::Solve() const {
  mat3 design_matrix_transpose = glm::transpose(design_matrix_);

  mat3 equation_system = design_matrix_transpose * design_matrix_;
  vec3 equation_targets = design_matrix_transpose * observation_vector_;

  return glm::inverse(equation_system) * equation_targets;
}

float QuadraticSolver::ComputePoint(float x_coord) const {
  return glm::dot(quadratic_constants_, vec3(1, x_coord, x_coord * x_coord));
}

std::vector<float> QuadraticSolver::ComputePointsInRange(
    float start_x, float end_x) const {
  vector<float> x_values = CreateRange(start_x, end_x);
  std::vector<float> y_values = vector<float>(x_values.size());

  std::iota(x_values.begin(), x_values.end(), start_x);

  for (size_t idx = 0; idx < x_values.size(); idx++) {
    y_values.at(idx) = ComputePoint(x_values.at(idx));
  }

  return y_values;
}

std::vector<float> QuadraticSolver::CreateRange(float start, float end) {
  vector<float> range = vector<float>(static_cast<size_t>(end - start));
  std::iota(range.begin(), range.end(), start);

  return range;
}

const glm::vec3& QuadraticSolver::GetQuadraticConstants() const {
  return quadratic_constants_;
}

} // namespace artillery
