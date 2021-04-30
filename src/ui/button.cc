//
// Created by Neil Kaushikkar on 4/30/21.
//

#include "ui/button.h"

namespace artillery {

using ci::ColorA8u;

Button::Button(const ColorA8u& border_color)
    : border_color_(border_color), is_visible_(true),
      is_hovered_(false), border_width_(0) {}

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

  ci::gl::color(border_color_);
  ci::gl::drawStrokedRect(rectangle_, border_width_);
}

void Button::Update(const glm::vec2& mouse_location) {
  if (is_visible_) {
    is_hovered_ = rectangle_.contains(mouse_location);
  }
}

void Button::SetVisibility(bool is_visible) {
  is_visible_ = is_visible;
}

bool Button::IsHoveredOver() const {
  return is_hovered_;
}

bool Button::IsVisible() const {
  return is_visible_;
}

} // namespace artillery
