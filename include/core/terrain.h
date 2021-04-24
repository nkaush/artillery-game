//
// Created by Neil Kaushikkar on 4/20/21.
//

#ifndef ARTILLERY_TERRAIN_H
#define ARTILLERY_TERRAIN_H

#include <vector>
#include <array>

#include "cinder/gl/gl.h"
#include "cinder/Surface.h"

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

  Terrain();

  size_t GetMaxHeight() const;

  size_t GetMaxWidth() const;

  const TerrainVisibility& GetTerrainVisibility(
      size_t x_coord, size_t y_coord) const;

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

 private:
  static const ci::ColorA8u kVisibleTerrainColor;
  static const ci::ColorA8u kRemovedTerrainColor;
  static const ci::ColorA8u kBackgroundColor;

  static constexpr TerrainVisibility kDefaultVisibility =
      TerrainVisibility::kNone;

  std::array<std::array<TerrainVisibility, kWindowWidth>, kWindowHeight>
      landscape_;

  ci::Surface8u pixels_;

  ci::gl::Texture2dRef display_;

  void LoadSurfaceFromHeights(const std::vector<size_t>& heights);
};
} // namespace artillery

#endif  // ARTILLERY_TERRAIN_H
