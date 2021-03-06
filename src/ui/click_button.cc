//
// Created by Neil Kaushikkar on 4/29/21.
//

#include "ui/click_button.h"

namespace artillery {

using std::string;
using glm::vec2;

ClickButton::ClickButton() : Button() {}

void ClickButton::Draw() const {
  // Use the base class implementation of the Draw method
  Button::Draw();

  // Draw the label only if the button is visible
  if (is_visible_) {
    ci::gl::drawStringCentered(
        display_label_, rectangle_.getCenter(), border_color_);
  }
}

void ClickButton::Update(const vec2& mouse_location) {
  // Use the base class implementation of the Update method
  Button::Update(mouse_location);
}

void ClickButton::ChangeLabel(bool should_set_main_label) {
  if (should_set_main_label) {
    display_label_ = main_label_;
  } else {
    display_label_ = alternate_label_;
  }
}

} // namespace artillery
