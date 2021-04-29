//
// Created by Neil Kaushikkar on 4/29/21.
//

#include "game/button.h"

namespace artillery {

using ci::ColorA8u;
using std::string;
using glm::vec2;

Button::Button(const ci::ColorA8u& label_color)
    : label_color_(label_color), is_hovered_(false), is_visible_(true) {}

void Button::Draw() const {
  if (!is_visible_) {
    return;
  }

  if (is_hovered_) {
    ci::gl::color(hover_color_);
  } else {
    ci::gl::color(background_color_);
  }

  ci::gl::drawSolidRect(rectangle_);

  ci::gl::color(label_color_);
  ci::gl::drawStrokedRect(rectangle_, border_width_);

  ci::gl::drawStringCentered(
      display_label_, rectangle_.getCenter(), label_color_);
}

void Button::Update(const vec2& mouse_location) {
  if (is_visible_) {
    is_hovered_ = rectangle_.contains(mouse_location);
  }
}

void Button::SetVisibility(bool is_visible) {
  is_visible_ = is_visible;
}

void Button::ChangeLabel(bool should_set_main_label) {
  if (should_set_main_label) {
    display_label_ = main_label_;
  } else {
    display_label_ = alternate_label_;
  }
}

bool Button::IsHoveredOver() const {
  return is_hovered_;
}

bool Button::IsVisible() const {
  return is_visible_;
}

} // namespace artillery
