//
// Created by Neil Kaushikkar on 4/20/21.
//

#include "core/terrain.h"

#include "core/quadratic_solver.h"
#include "core/json_manager.h"
#include "glm/vec2.hpp"

namespace artillery {

using nlohmann::json;
using ci::ColorA8u;
using std::vector;
using glm::vec2;

constexpr TerrainVisibility Terrain::kDefaultVisibility;

Terrain::Terrain() : landscape_(),
                     pixels_(kWindowWidth, kWindowHeight, true),
                     display_() {}

void to_json(json& json_object, const Terrain& terrain) {}

void from_json(const json& json_object, Terrain& terrain) { // TODO documentation
  terrain.pixels_.setPremultiplied(true);

  json_object.at(JsonManager::kJsonBackgroundColorKey)
      .get_to(terrain.background_color_);

  json_object.at(JsonManager::kJsonVisibleTerrainColorKey)
      .get_to(terrain.visible_terrain_color_);

  json_object.at(JsonManager::kJsonRemovedTerrainColorKey)
      .get_to(terrain.removed_terrain_color_);

  json ridge_extrema = json_object.at(JsonManager::kJsonRidgeExtremaKey);
  auto points_matrix = ridge_extrema.get<vector<vector<vec2>>>();
  vector<size_t> heights = terrain.ComputerSurfaceHeights(points_matrix);
  terrain.LoadSurfaceFromHeights(heights);

  terrain.display_ = ci::gl::Texture::create(terrain.pixels_);
}

vector<size_t> Terrain::ComputerSurfaceHeights(
    const vector<vector<vec2>>& points_matrix) const {
  // TODO check if window size == last point x value
  vector<float> curve_fits = vector<float>();
  curve_fits.reserve(sizeof(float) * kWindowWidth);

  for (const vector<vec2>& points : points_matrix) {
    vec2 start = points.at(0);
    vec2 end = points.at(2);

    QuadraticSolver quad_solver(start, points.at(1), end);
    std::vector<float> y_values =
        quad_solver.ComputePointsInRange(start.x, end.x);

    curve_fits.insert(curve_fits.end(), y_values.begin(), y_values.end());
  }

  vector<size_t> heights = vector<size_t>(curve_fits.size());

  for (size_t idx = 0; idx < curve_fits.size(); idx++) {
    heights.at(idx) = static_cast<size_t>(glm::max(0.f, curve_fits.at(idx)));
  }

  return heights;
}

void Terrain::LoadSurfaceFromHeights(const vector<size_t>& column_heights) {
  for (size_t col = 0; col < kWindowWidth; col++) {
    size_t limit = kWindowHeight - column_heights.at(col);

    for (size_t row = landscape_.size(); row > 0; row--) {
      try {
        if (row - 1 >= limit) {
          landscape_.at(row - 1).at(col) = TerrainVisibility::kVisible;
          pixels_.setPixel(vec2(col, row - 1), visible_terrain_color_);
        } else {
          landscape_.at(row - 1).at(col) = TerrainVisibility::kNone;
        }
      } catch (std::out_of_range& e) {
        std::cout << row << " " << col << std::endl;
      }
    }
  }
}

void Terrain::Draw() const {
  ci::gl::draw(display_);
}

const TerrainVisibility& Terrain::GetTerrainVisibility(
    size_t x_coord, size_t y_coord) const {
  try {
    return landscape_.at(y_coord).at(x_coord);
  } catch (std::out_of_range& exception) {
    return kDefaultVisibility;
  }
}

size_t Terrain::GetMaxHeight() const {
  return landscape_.size();
}

size_t Terrain::GetMaxWidth() const {
  return kWindowWidth;
}

const ci::ColorA8u& Terrain::GetBackgroundColor() const {
  return background_color_;
}

void Terrain::DestroyTerrainInRadius(
    const glm::vec2& center_point, size_t radius) {
  auto unsigned_radius = static_cast<float>(radius);

  auto center_x = static_cast<size_t>(center_point.x);
  auto center_y = static_cast<size_t>(center_point.y);

  size_t right_bound = center_x + radius;
  size_t lower_bound = center_y + radius;

  // Go through all points in the square formed by the radius of impact
  for (size_t x_coord = center_x - radius; x_coord < right_bound; x_coord++) {
    for (size_t y_coord = center_y - radius; y_coord < lower_bound; y_coord++) {
      // We only need to change the shade of a point if it is visible
      bool is_terrain_in_background =
          GetTerrainVisibility(x_coord, y_coord) != TerrainVisibility::kVisible;

      bool is_point_out_of_bounds = x_coord < 0 || x_coord >= GetMaxWidth();
      is_point_out_of_bounds |= y_coord < 0 || y_coord >= GetMaxHeight();

      if (is_terrain_in_background || is_point_out_of_bounds) {
        continue;
      }

      vec2 point(x_coord, y_coord);

      // Check if point is inside blast radius circle
      if (glm::distance(point, center_point) <= unsigned_radius) {
        pixels_.setPixel(point, removed_terrain_color_);
        landscape_.at(y_coord).at(x_coord) = TerrainVisibility::kRemoved;
      }
    }
  }

  display_->update(pixels_);
}

}
