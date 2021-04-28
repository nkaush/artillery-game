//
// Created by Neil Kaushikkar on 4/20/21.
//

#ifndef ARTILLERY_TERRAIN_H
#define ARTILLERY_TERRAIN_H

#include <nlohmann/json.hpp>
#include "cinder/Surface.h"
#include "cinder/gl/gl.h"
#include <vector>
#include <array>

namespace artillery {

/**
 * This enum encodes the different types of Terrain shadings.
 */
enum class TerrainVisibility {
  kNone = 0,
  kVisible = 1,
  kRemoved = 2,
};

/**
 * This abstraction represents the landscape drawn on the window. It provides
 * functionality to interact with Bullet objects and Tank objects.
 */
class Terrain {
 public:
  // These constants define the size of the app window
  static constexpr int kWindowWidth = 750;
  static constexpr int kWindowHeight = 500;

  /**
   * Default constructor. Initializes the array of pixels and states using the
   * constant window height and window width.
   */
  Terrain();

  /**
   * Get the max height of the terrain as a size_t.
   * @return a size_t indicating the max possible height of the terrain
   */
  size_t GetMaxHeight() const;

  /**
   * Get the max width of the terrain as a size_t.
   * @return a size_t indicating the max possible width of the terrain
   */
  size_t GetMaxWidth() const;

  /**
   * Get the type of terrain shading at the specified coordinates. Returns
   * TerrainVisibility::kNone if the indices are out of bounds.
   * @param x_coord - the x_coordinate of the terrain visibility requested
   * @param y_coord the y_coordinate of the terrain visibility requested
   * @return a TerrainVisibility enum indicating the type of terrain shading
   */
  const TerrainVisibility& GetTerrainVisibility(
      size_t x_coord, size_t y_coord) const;

  /**
   * Get the background color for this terrain.
   * @return a ColorA8u object containing the r, g, b, and a color values
   */
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
   * Get the height of the terrain as it was at the start of the game.
   * @param x_coordinate - the x_coordinate to get the height at
   * @return a size_t indicating the height of the terrain
   */
  size_t GetStartingHeight(size_t x_coordinate) const;

  /**
   * Used by the nlohmann::json library to serialize Terrain objects.
   * @param json_object - the json object to populate
   * @param terrain - the Terrain object to serialize
   */
  friend void to_json(nlohmann::json& json_object, const Terrain& terrain);

  /**
   * Used by the nlohmann::json library to deserialize Terrain objects.
   * @param json_object - the json object to deserialize
   * @param terrain - the Terrain object to populate
   */
  friend void from_json(const nlohmann::json& json_object, Terrain& terrain);

 private:
  static constexpr TerrainVisibility kDefaultVisibility =
      TerrainVisibility::kNone;

  // The pixel grid that contains the state of each pixel in the window
  std::array<std::array<TerrainVisibility, kWindowWidth>, kWindowHeight>
      landscape_;

  std::vector<size_t> starting_heights_;

  // The pixel grid containing the color information of each pixel
  ci::Surface8u pixels_;

  // The texture formed by the pixel grid that is drawn on the window
  ci::gl::Texture2dRef display_;

  // The colors to shade each type of terrain
  ci::ColorA8u visible_terrain_color_;
  ci::ColorA8u removed_terrain_color_;
  ci::ColorA8u background_color_;

  /**
   * Set the color and state of each pixel according to the number of pixels in
   * each column of the frame given by each entry in the vector of heights.
   * @param heights - a vector of size_t indicating the number of shaded pixels
   */
  void LoadSurfaceFromHeights(const std::vector<size_t>& heights);

  /**
   * Compute the heights of all x-coordinates in the range of the window by
   * fitting a quadratic curve to each vector of 3 points in the vector passed.
   * @param points - a vector containing groups of 3 points to fit a curve to
   * @return a vector of size_t heights resulting from the curves fit to the
   * groups of points passed in the vector of vector of vec2 points.
   */
  std::vector<size_t> ComputerSurfaceHeights(
      const std::vector<std::vector<glm::vec2>>& points) const;

  static ci::ColorA8u RandomizeColor(const ci::ColorA8u& original_color);
};

} // namespace artillery

#endif  // ARTILLERY_TERRAIN_H
