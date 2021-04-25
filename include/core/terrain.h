//
// Created by Neil Kaushikkar on 4/20/21.
//

#ifndef ARTILLERY_TERRAIN_H
#define ARTILLERY_TERRAIN_H

#include <vector>
#include <array>

#include "nlohmann/json.hpp"
#include "cinder/Surface.h"
#include "cinder/gl/gl.h"

namespace artillery {

enum class TerrainVisibility {
  kNone = 0,
  kVisible = 1,
  kRemoved = 2,
};

class Terrain {
 public:
  static constexpr int kWindowWidth = 750;
  static constexpr int kWindowHeight = 500;

  static const std::string kJsonStartingHeightsKey;
  static const std::string kJsonBackgroundColorKey;
  static const std::string kJsonVisibleTerrainColorKey;
  static const std::string kJsonRemovedTerrainColorKey;

  Terrain();

  size_t GetMaxHeight() const;

  size_t GetMaxWidth() const;

  const TerrainVisibility& GetTerrainVisibility(
      size_t x_coord, size_t y_coord) const;

  const ci::ColorA8u& GetBackgroundColor() const;

  /**
   * Re-shades all the 'kVisible' terrain blocks in the radius with a darker
   * color to indicate removal and changes status of those blocks to 'kRemoved'.
   * @param center_point - a vec2 indicating the center of the blast
   * @param radius - a size_t indicating the radius of the blast
   */
  void DestroyTerrainInRadius(const glm::vec2& center_point, size_t radius);

  /**
   * Draws the terrain on the window.
   */
  void Draw() const;

  /**
   * Used by the nlohmann::json library to serialize Terrain objects.
   * @param json_object - the json object to serialize into
   * @param terrain - the Terrain object to serialize
   */
  friend void to_json(nlohmann::json& json_object, const Terrain& terrain);

  /**
   * Used by the nlohmann::json library to deserialize Terrain objects.
   * @param json_object - the json object to serialize from
   * @param terrain - the Terrain object to deserialize into
   */
  friend void from_json(const nlohmann::json& json_object, Terrain& terrain);

 private:
  static constexpr TerrainVisibility kDefaultVisibility =
      TerrainVisibility::kNone;

  std::array<std::array<TerrainVisibility, kWindowWidth>, kWindowHeight>
      landscape_;

  ci::Surface8u pixels_;

  ci::gl::Texture2dRef display_;

  ci::ColorA8u visible_terrain_color_;
  ci::ColorA8u removed_terrain_color_;
  ci::ColorA8u background_color_;

  void LoadSurfaceFromHeights(const std::vector<size_t>& heights);
};
} // namespace artillery

#endif  // ARTILLERY_TERRAIN_H
