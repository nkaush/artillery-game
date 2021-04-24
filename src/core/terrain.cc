//
// Created by Neil Kaushikkar on 4/20/21.
//

#include "core/terrain.h"

#include "glm/vec2.hpp"

namespace artillery {

using nlohmann::json;
using ci::ColorA8u;
using std::vector;
using std::string;
using std::array;
using glm::vec2;

const string Terrain::kJsonRedColorKey = "red";
const string Terrain::kJsonGreenColorKey = "green";
const string Terrain::kJsonBlueColorKey = "blue";
const string Terrain::kJsonAlphaChannelKey = "alpha";

const string Terrain::kJsonStartingHeightsKey = "starting_pixel_heights";
const string Terrain::kJsonBackgroundColorKey = "background_color";
const string Terrain::kJsonVisibleTerrainColorKey = "visible_terrain_color";
const string Terrain::kJsonRemovedTerrainColorKey = "removed_terrain_color";

constexpr TerrainVisibility Terrain::kDefaultVisibility;

Terrain::Terrain() : landscape_(),
                     pixels_(kWindowWidth, kWindowHeight, true),
                     display_() {}

void to_json(nlohmann::json& json_object, const Terrain& terrain) {}

void from_json(const nlohmann::json& json_object, Terrain& terrain) {
  if (!json_object.at(Terrain::kJsonStartingHeightsKey).is_array()) {
    throw std::invalid_argument("Must construct a Terrain object with an array");
  }

  terrain.pixels_.setPremultiplied(false);

  Terrain::DeserializeColorA8u(
      json_object.at(Terrain::kJsonBackgroundColorKey),
      terrain.background_color_);
  Terrain::DeserializeColorA8u(
      json_object.at(Terrain::kJsonVisibleTerrainColorKey),
      terrain.visible_terrain_color_);
  Terrain::DeserializeColorA8u(
      json_object.at(Terrain::kJsonRemovedTerrainColorKey),
      terrain.removed_terrain_color_);

  json heights_array = json_object.at(Terrain::kJsonStartingHeightsKey);
  terrain.LoadSurfaceFromHeights(heights_array.get<vector<size_t>>());

  terrain.display_ = ci::gl::Texture::create(terrain.pixels_);
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
//          pixels_.setPixel(vec2(col, row - 1), kBackgroundColor);
        }
      } catch (std::out_of_range& e) {
        std::cout << row << " " << col << std::endl;
      }
    }
  }
}

void Terrain::DeserializeColorA8u(const json& json_object, ColorA8u& color) {
  json_object.at(Terrain::kJsonRedColorKey).get_to(color.r);
  json_object.at(Terrain::kJsonGreenColorKey).get_to(color.g);
  json_object.at(Terrain::kJsonBlueColorKey).get_to(color.b);
  json_object.at(Terrain::kJsonAlphaChannelKey).get_to(color.a);
}

void Terrain::SerializeColorA8u(json& json_object, const ColorA8u& color) {
  json_object = json {
      {Terrain::kJsonRedColorKey, color.r},
      {Terrain::kJsonGreenColorKey, color.g},
      {Terrain::kJsonBlueColorKey, color.b},
      {Terrain::kJsonAlphaChannelKey, color.a}
  };
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
