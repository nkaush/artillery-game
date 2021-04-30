//
// Created by Neil Kaushikkar on 4/30/21.
//

#include "ui/toggle_button.h"

namespace artillery {

ToggleButton::ToggleButton() : Button(), is_toggled_(false) {}

void ToggleButton::Draw() const {
  Button::Draw();

  if (is_visible_ && is_toggled_) {
    ci::gl::color(border_color_);
    ci::gl::drawSolidRect(toggle_rect_);
  }
}

void ToggleButton::Update(const glm::vec2& mouse_position) {
  Button::Update(mouse_position);
}

void ToggleButton::Toggle(const glm::vec2& mouse_position) {
  if (rectangle_.contains(mouse_position)) {
    is_toggled_ = !is_toggled_;
  }
}

bool ToggleButton::IsToggled() const {
  return is_toggled_;
}

} // namespace artillery
