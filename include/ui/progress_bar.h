//
// Created by Neil Kaushikkar on 4/30/21.
//

#ifndef ARTILLERY_PROGRESS_BAR_H
#define ARTILLERY_PROGRESS_BAR_H

#include "utilities/json_manager.h"

#include <nlohmann/json.hpp>
#include "cinder/gl/gl.h"
#include <string>

namespace artillery {

/**
 * This struct contains settings about how to render ProgressBar objects.
 * It is used to configure uniform progress bars from deserialized JSON.
 */
struct ProgressBarRenderSettings {
  glm::vec2 vertical_padding_;
  glm::vec2 horizontal_padding_;
  glm::vec2 label_padding_;

  size_t bar_height_;
  float bar_width_;

  std::string label_prefix_;
  std::string label_suffix_;

  ci::ColorA8u background_color_;
  ci::ColorA8u label_color_;
};

/**
 * This macro from from the nlohmann::json parsing library will generate the
 * boilerplate code required to create a ProgressBarRenderSettings struct and
 * populate it with fields from passed JSON data. The macro also generates
 * boilerplate code to serialize ProgressBarRenderSettings structs.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    ProgressBarRenderSettings, vertical_padding_, horizontal_padding_,
    bar_height_, bar_width_, background_color_, label_prefix_,
    label_suffix_, label_color_, label_padding_)

/**
 * This class is used to render a progress bar with text indicating progress.
 */
class ProgressBar {
 public:
  /**
   * Creates a progress bar with the rendering settings passed from the given
   * ProgressBarRenderSettings struct. Colors the current progress in the given
   * color. Labels the progress bar with the provided index.
   * @param settings - the ProgressBarRenderSettings containing information
   *                   about how to render this progress bar
   * @param progress_color - a ColorA8u indicating the color with which to
   *                         render the current progress represented by this bar
   * @param max_progress - a float indicating the max progress this bar can hold
   * @param index - a size_t indicating the index used to label this bar
   */
  ProgressBar(const ProgressBarRenderSettings& settings,
              const ci::ColorA8u& progress_color,
              float max_progress, size_t index);

  /**
   * Renders the progress bar and the background bar showing the max progress.
   */
  void Draw() const;

  /**
   * Updates the progress with the updated value.
   * @param updated_progress - a float indicating the updated progress
   */
  void UpdateProgress(float updated_progress);

 private:
  // Used to render the progress bar components
  ci::ColorA8u background_color_;
  ci::ColorA8u progress_color_;
  ci::ColorA8u label_color_;

  // Used to show the max progress represented by the bar
  ci::Rectf background_rect_;

  // Used to show the current progress
  ci::Rectf progress_rect_;

  // Used to render the label of the progress bar
  glm::vec2 label_position_;
  std::string label_;

  // Used to scale the progress level to the rendering width of the progress bar
  float bar_length_scalar_;

  // Stores the internal progress state of this progress bar
  float progress_;
};

} // namespace artillery

#endif  // ARTILLERY_PROGRESS_BAR_H
