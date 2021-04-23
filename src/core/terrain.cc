//
// Created by Neil Kaushikkar on 4/20/21.
//

#include "core/terrain.h"

#include "glm/vec2.hpp"

namespace artillery {

using ci::ColorA8u;
using std::array;
using glm::vec2;

const ColorA8u Terrain::kRemovedTerrainColor = ColorA8u(106, 56, 31, 255);
const ColorA8u Terrain::kVisibleTerrainColor = ColorA8u(119, 78, 36, 255);
const ColorA8u Terrain::kBackgroundColor = ci::ColorA8u(0, 0, 0, 0); // 98, 187, 193

void Terrain::Draw() const {
  ci::gl::draw(display_);
}

Terrain::Terrain() : landscape_(),
                     pixels_(kWindowWidth, kWindowHeight, true),
                     display_() {
  std::vector<size_t> terr = std::vector<size_t>(kWindowWidth, 0);

  for (size_t i = 0; i < terr.size(); i++) {
    terr.at(i) = i;
  }

  pixels_.setPremultiplied(false);

  for (size_t col = 0; col < kWindowWidth; col++) {
    size_t limit = kWindowHeight - terr.at(col);
    for (size_t row = landscape_.size() - 1; row > 0; row--) {
      try {
        if (row > limit) {
          landscape_.at(row).at(col) = TerrainVisibility::kVisible;
          pixels_.setPixel(vec2(col, row), kVisibleTerrainColor);
        }
        else {
          landscape_.at(row).at(col) = TerrainVisibility::kNone;
          pixels_.setPixel(vec2(col, row), kBackgroundColor);
        }
      } catch (std::out_of_range& e) {
        std::cout << row << " " << col << std::endl;
      }
    }

    display_ = ci::gl::Texture::create(pixels_);
  }
}

}
