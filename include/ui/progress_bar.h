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
 *
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
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    ProgressBarRenderSettings, vertical_padding_, horizontal_padding_,
    bar_height_, bar_width_, background_color_, label_prefix_,
    label_suffix_, label_color_, label_padding_)

/**
 *
 */
class ProgressBar {
 public:
  ProgressBar(const ProgressBarRenderSettings& settings,
              const ci::ColorA8u& progress_color,
              float max_progress, size_t index);

  void Draw() const;

  void UpdateProgress(float updated_progress);

 private:
  ci::ColorA8u background_color_;
  ci::ColorA8u progress_color_;
  ci::ColorA8u label_color_;

  ci::Rectf background_rect_;
  ci::Rectf progress_rect_;

  glm::vec2 label_position_;
  std::string label_;

  float bar_length_scalar_;
  float progress_;
};

} // namespace artillery

#endif  // ARTILLERY_PROGRESS_BAR_H
