//
// Created by Neil Kaushikkar on 4/30/21.
//

#include "ui/toggle_button.h"

namespace artillery {

using ci::ColorA8u;
using ci::Rectf;

using glm::vec2;

ToggleButton::ToggleButton() : Button(), is_toggled_(false) {}

ToggleButton::ToggleButton(
    const vec2& button_center, const ColorA8u& background_color,
    const ColorA8u& hover_color, float button_width, float button_height,
    float toggle_rect_width, float toggle_rect_height, float border_width)
    : Button(button_center, button_width, button_height,
             border_width, background_color, hover_color),
      is_toggled_(false) {
  // Center the inner toggle rectangle in the button center coordinate given
  vec2 offset(toggle_rect_width / 2, toggle_rect_height / 2);
  toggle_rect_ = Rectf(button_center - offset, button_center + offset);
}

void ToggleButton::Draw() const {
  Button::Draw();

  // Only draw the inner toggle rectangle if the button is visible & toggled on
  if (is_visible_ && is_toggled_) {
    ci::gl::color(border_color_);
    ci::gl::drawSolidRect(toggle_rect_);
  }
}

void ToggleButton::Update(const glm::vec2& mouse_position) {
  Button::Update(mouse_position);
}

void ToggleButton::SetToggleStatus(bool is_toggled) {
  is_toggled_ = is_toggled;
}

void ToggleButton::Toggle(const glm::vec2& mouse_position) {
  // flip the toggle state when the button is clicked
  if (rectangle_.contains(mouse_position)) {
    is_toggled_ = !is_toggled_;
  }
}

bool ToggleButton::IsToggled() const {
  return is_toggled_;
}

} // namespace artillery
