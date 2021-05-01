//
// Created by Neil Kaushikkar on 4/30/21.
//

#include "ui/pause_button.h"

namespace artillery {

PauseButton::PauseButton() : Button(), is_paused_(false) {}

void PauseButton::Draw() const {
  Button::Draw();

  ci::gl::color(border_color_);
  ci::gl::pushMatrices();

  // center the reference frame at the center of the button to draw the icons
  ci::gl::translate(rectangle_.getCenter());

  if (is_paused_) { // draw the play icon when the game is paused
    ci::gl::drawSolidTriangle(play_icon_);
  } else { // draw the pause icon when the game is in play
    for (const ci::Rectf& rect : pause_icon_) {
      ci::gl::drawSolidRect(rect);
    }
  }

  ci::gl::popMatrices();
}

void PauseButton::Update(const glm::vec2& mouse_position) {
  Button::Update(mouse_position);
}

void PauseButton::Toggle(const glm::vec2& mouse_position) {
  if (rectangle_.contains(mouse_position)) {
    is_paused_ = !is_paused_;
  }
}

bool PauseButton::IsPaused() const {
  return is_paused_;
}

} // namespace artillery
