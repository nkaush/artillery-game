//
// Created by Neil Kaushikkar on 4/25/21.
//

#include "utilities/quadratic_model.h"

#include <numeric>

namespace artillery {

using std::vector;
using glm::dmat3;
using glm::mat3;
using glm::dvec3;
using glm::vec3;
using glm::vec2;

QuadraticModel::QuadraticModel(
    const vec2& point_a, const vec2& point_b, const vec2& point_c) {
  dvec3 second_column = vec3(point_a.x, point_b.x, point_c.x);
  dvec3 third_column = second_column * second_column;

  // Make design matrix with the form a polynomial takes with given x-values
  mat3 design_matrix = dmat3(dvec3(1), second_column, third_column);
  dvec3 observation_vector = dvec3(point_a.y, point_b.y, point_c.y);

  quadratic_constants_ = Solve(design_matrix, observation_vector);
}

const dvec3 QuadraticModel::Solve(
    const dmat3& design_matrix, const dvec3& observation_vector) {
  // Solve the linear system A.T * A * x = A.T * b
  dmat3 design_matrix_transpose = glm::transpose(design_matrix);

  dmat3 equation_system = design_matrix_transpose * design_matrix;
  dvec3 equation_targets = design_matrix_transpose * observation_vector;

  return glm::inverse(equation_system) * equation_targets;
}

float QuadraticModel::ComputePoint(float x_coord) const {
  return glm::dot(quadratic_constants_, vec3(1, x_coord, x_coord * x_coord));
}

std::vector<float> QuadraticModel::ComputePointsInRange(
    float start_x, float end_x) const {
  vector<float> x_values = CreateRange(start_x, end_x);
  std::vector<float> y_values = vector<float>(x_values.size());

  // Compute each the y-value for each x-value in the range
  for (size_t idx = 0; idx < x_values.size(); idx++) {
    y_values.at(idx) = ComputePoint(x_values.at(idx));
  }

  return y_values;
}

std::vector<float> QuadraticModel::CreateRange(float start, float end) {
  vector<float> range = vector<float>(static_cast<size_t>(end - start));
  std::iota(range.begin(), range.end(), start); // Fill with increments of 1

  return range;
}

const glm::vec3& QuadraticModel::GetQuadraticConstants() const {
  return quadratic_constants_;
}

} // namespace artillery
