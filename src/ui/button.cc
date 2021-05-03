//
// Created by Neil Kaushikkar on 4/30/21.
//

#include "ui/button.h"

namespace artillery {

using ci::ColorA8u;
using ci::Rectf;
using glm::vec2;

Button::Button(const ColorA8u& border_color)
    : border_color_(border_color), is_visible_(true),
      is_hovered_(false), border_width_(0) {}

Button::Button(
    const vec2& center, float width, float height, float border_width,
    const ci::ColorA8u& background_color, const ci::ColorA8u& hover_color,
    const ci::ColorA8u& border_color)
    : hover_color_(hover_color), border_color_(border_color),
      background_color_(background_color), is_visible_(true),
      is_hovered_(false), border_width_(border_width) {
  // Center the button's bounding rectangle at the provided button center
  vec2 offset(width / 2, height / 2);
  rectangle_ = Rectf(center - offset, center + offset);
}

void Button::Draw() const {
  if (!is_visible_) { // if the button is not visible, DO NOT draw it
    return;
  }

  // set the button color based on whether the button is being hovered over
  if (is_hovered_) {
    ci::gl::color(hover_color_);
  } else {
    ci::gl::color(background_color_);
  }

  // Draw the button and the border of the button
  ci::gl::drawSolidRect(rectangle_);
  ci::gl::color(border_color_);
  ci::gl::drawStrokedRect(rectangle_, border_width_);
}

void Button::Update(const glm::vec2& mouse_location) {
  // if the button is visible and contains the user's mouse, update it's status
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
