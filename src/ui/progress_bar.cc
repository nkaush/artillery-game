//
// Created by Neil Kaushikkar on 4/30/21.
//

#include "ui/progress_bar.h"

namespace artillery {

using ci::ColorA8u;
using ci::Rectf;

using glm::vec2;

using std::string;

ProgressBar::ProgressBar(const ProgressBarRenderSettings& settings,
                         const ColorA8u& progress_color,
                         float max_progress, size_t index)
    : background_color_(settings.background_color_),
      progress_color_(progress_color),
      label_color_(settings.label_color_),
      bar_length_scalar_(settings.bar_width_ / max_progress),
      progress_(max_progress) {
  vec2 upper_pt = settings.horizontal_padding_
                  + vec2(0, settings.bar_height_ * index)
                  + (settings.vertical_padding_ * vec2(0, index + 1));
  vec2 offset = vec2(bar_length_scalar_ * max_progress, settings.bar_height_);

  background_rect_ = Rectf(upper_pt, upper_pt + offset);
  progress_rect_ = Rectf(upper_pt, upper_pt + offset);

  label_position_ = upper_pt + settings.label_padding_;

  label_ = settings.label_prefix_
           + std::to_string(index + 1)
           + settings.label_suffix_;
}

void ProgressBar::Draw() const {
  ci::gl::color(background_color_);
  ci::gl::drawSolidRect(background_rect_);

  ci::gl::color(progress_color_);
  ci::gl::drawSolidRect(progress_rect_);

  ci::gl::drawString(label_ + std::to_string(static_cast<int>(progress_)),
                     label_position_, label_color_);
}

void ProgressBar::UpdateProgress(float updated_progress) {
  progress_rect_.x2 += (updated_progress - progress_)
                       * bar_length_scalar_;
  progress_ = updated_progress;
}

} // namespace artillery
