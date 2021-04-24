//
// Created by Neil Kaushikkar on 4/20/21.
//

#include "core/terrain.h"

#include "glm/vec2.hpp"

namespace artillery {

using ci::ColorA8u;
using std::vector;
using std::array;
using glm::vec2;

const ColorA8u Terrain::kRemovedTerrainColor = ColorA8u(119, 78, 36, 255); // 106, 56, 31, 255
const ColorA8u Terrain::kVisibleTerrainColor = ColorA8u(228, 187, 151, 255);
const ColorA8u Terrain::kBackgroundColor = ci::ColorA8u(0, 0, 0, 0); // 98, 187, 193

constexpr TerrainVisibility Terrain::kDefaultVisibility;

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
        pixels_.setPixel(point, kRemovedTerrainColor);
        landscape_.at(y_coord).at(x_coord) = TerrainVisibility::kRemoved;
      }
    }
  }

  display_->update(pixels_);
}

Terrain::Terrain() : landscape_(),
                     pixels_(kWindowWidth, kWindowHeight, true),
                     display_() {
  std::vector<size_t> terr = std::vector<size_t>(kWindowWidth, 0);

  for (size_t i = 0; i < terr.size(); i++) {
    terr.at(i) = i;
  }

  pixels_.setPremultiplied(false);

  LoadSurfaceFromHeights(terr);
  display_ = ci::gl::Texture::create(pixels_);
}

void Terrain::LoadSurfaceFromHeights(const vector<size_t>& column_heights) {
  for (size_t col = 0; col < kWindowWidth; col++) {
    size_t limit = kWindowHeight - column_heights.at(col);

    for (size_t row = landscape_.size(); row > 0; row--) {
      try {
        if (row - 1 >= limit) {
          landscape_.at(row - 1).at(col) = TerrainVisibility::kVisible;
          pixels_.setPixel(vec2(col, row - 1), kVisibleTerrainColor);
        } else {
          landscape_.at(row - 1).at(col) = TerrainVisibility::kNone;
//          pixels_.setPixel(vec2(col, row - 1), kBackgroundColor);
        }
      } catch (std::out_of_range& e) {
        std::cout << row << " " << col << std::endl;
      }
    }
  }
}

}
