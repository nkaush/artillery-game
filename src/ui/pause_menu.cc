//
// Created by Neil Kaushikkar on 4/30/21.
//

#include "ui/pause_menu.h"

namespace artillery {

using ci::ColorA8u;
using ci::Rectf;

using glm::vec2;

using std::transform;
using std::vector;

PauseMenu::PauseMenu(const ColorA8u& label_color)
    : label_color_(label_color), label_padding_(0), vertical_padding_(0),
      button_left_padding_(0), button_height_(0), button_width_(0),
      button_toggle_width_(0), button_toggle_height_(0),
      button_border_width_(0), is_visible_(false) {}

void PauseMenu::Configure(size_t num_buttons) {
  float vertical_offset = (2 * vertical_padding_) + button_height_;
  auto button_count = static_cast<float>(num_buttons);

  float menu_width = button_left_padding_ + button_width_ + label_padding_;
  float menu_height =
       vertical_offset + (button_count * (vertical_padding_ + button_height_));

  vec2 offset(menu_width / 2, menu_height / 2);
  menu_rectangle_ = Rectf(menu_rectangle_center_ - offset,
                          menu_rectangle_center_ + offset);

  menu_label_position_ =
      vec2(label_padding_, vertical_padding_ + (button_height_ / 2));

  for (size_t idx = 0; idx < num_buttons; idx++) {
    float menu_item_vertical_padding =
        (static_cast<float>(idx) * (button_height_ + vertical_padding_))
        + vertical_offset + (button_height_ / 2);

    vec2 button_center(button_left_padding_, menu_item_vertical_padding);

    toggle_buttons_.emplace_back(
        button_center, button_background_color_, button_hover_color_,
        button_width_, button_height_, button_toggle_width_,
        button_toggle_height_, button_border_width_);

    std::cout << button_center << std::endl;

    button_label_positions_.emplace_back(
        label_padding_, menu_item_vertical_padding);

    button_labels_.push_back(button_label_prefix_ + std::to_string(idx + 1));
  }
}

void PauseMenu::Draw() const {
  if (!is_visible_) {
    return;
  }

  ci::gl::color(background_color_);
  ci::gl::drawSolidRect(menu_rectangle_);

  ci::gl::pushMatrices();
  ci::gl::translate(menu_rectangle_.getUpperLeft());

  ci::gl::drawString(menu_label_, menu_label_position_, label_color_);

  for (size_t idx = 0; idx < toggle_buttons_.size(); idx++) {
    toggle_buttons_.at(idx).Draw();

    ci::gl::drawString(
        button_labels_.at(idx), button_label_positions_.at(idx), label_color_);
  }

  ci::gl::popMatrices();
}

void PauseMenu::Update(const glm::vec2& mouse_position) {
  if (is_visible_) {
    vec2 reference_location = mouse_position - menu_rectangle_.getUpperLeft();

    for (ToggleButton& button : toggle_buttons_) {
      button.Update(reference_location);
    }
  }
}

void PauseMenu::SetVisibility(bool is_visible) {
  is_visible_ = is_visible;
}

void PauseMenu::HandleMouseDown(const glm::vec2& mouse_position) {
  if (is_visible_) {
    vec2 reference_location = mouse_position - menu_rectangle_.getUpperLeft();
    std::cout << reference_location << std::endl;

    for (ToggleButton& button : toggle_buttons_) {
      button.Toggle(reference_location);
    }
  }
}

void PauseMenu::SetToggleButtonStates(const vector<bool>& button_states) {
  for (size_t idx = 0; idx < toggle_buttons_.size(); idx++) {
    toggle_buttons_.at(idx).SetToggleStatus(button_states.at(idx));
  }
}

vector<bool> PauseMenu::GetToggleButtonStates() const {
  vector<bool> states(toggle_buttons_.size());
  auto checker = [] (const ToggleButton& button) { return button.IsToggled(); };

  transform(toggle_buttons_.begin(), toggle_buttons_.end(),
            states.begin(), checker);

  return states;
}

} // namespace artillery
