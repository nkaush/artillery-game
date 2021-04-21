//
// Created by Neil Kaushikkar on 4/20/21.
//

#ifndef ARTILLERY_TERRAIN_H
#define ARTILLERY_TERRAIN_H

#include <cstdlib>
#include <array>

#include "cinder/gl/gl.h"
#include "cinder/Surface.h"

namespace artillery {

enum class TerrainVisibility {
  kVisible = 0,
  kRemoved = 1,
  kNone = 2
};

class Terrain {
 public:
  Terrain();

  void Draw() const;

  static constexpr int kWindowWidth = 750;
  static constexpr int kWindowHeight = 500;

 private:
  static const ci::ColorA8u kVisibleTerrainColor;
  static const ci::ColorA8u kRemovedTerrainColor;
  static const ci::ColorA8u kBackgroundColor;

  std::array<std::array<TerrainVisibility, kWindowWidth>, kWindowHeight>
      landscape_;

  ci::Surface8u pixels_;

  ci::gl::Texture2dRef display_;

};
} // namespace artillery

#endif  // ARTILLERY_TERRAIN_H
