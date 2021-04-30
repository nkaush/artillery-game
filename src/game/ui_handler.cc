//
// Created by Neil Kaushikkar on 4/30/21.
//

#include "game/ui_handler.h"

namespace artillery {

using std::vector;

using ci::ColorA8u;
using ci::Rectf;

using glm::vec2;

UIHandler::UIHandler() {}

void UIHandler::Draw(const vector<size_t>& player_hitpoints,
                     const vector<ColorA8u>& tank_colors,
                     size_t max_hitpoints) const {
  start_button_.Draw();
  toggle_button_.Draw();

  DrawHitpointsBars(player_hitpoints, tank_colors, max_hitpoints);
}

void UIHandler::Configure() {
  start_button_.ChangeLabel(true);
}

void UIHandler::Update(const GameState& game_state, const vec2& mouse_location) {
  start_button_.Update(mouse_location);
  toggle_button_.Update(mouse_location);

  if (game_state == GameState::kGameOver) {
    start_button_.ChangeLabel(false);
    start_button_.SetVisibility(true);
  }
}

void UIHandler::HandleMouseDown(const vec2& mouse_location) {
  toggle_button_.Toggle(mouse_location);

  if (start_button_.IsHoveredOver()) {
    start_button_.SetVisibility(false);
  }
}

bool UIHandler::IsStartButtonVisible() const {
  return start_button_.IsVisible();
}

bool UIHandler::IsStartButtonHoveredOver() const {
  return start_button_.IsHoveredOver();
}

void UIHandler::DrawHitpointsBars(const vector<size_t>& player_hitpoints,
                                  const vector<ColorA8u>& tank_colors,
                                  size_t max_hitpoints) const {
  auto max_bar_length = static_cast<float>(max_hitpoints);

  // find the top left point of the hitpoints bar
  for (size_t idx = 0; idx < player_hitpoints.size(); idx++) {
    vec2 vertical_component =
        hp_render_settings_.vertical_padding_ * vec2(0, idx + 1);
    vertical_component += vec2(0, hp_render_settings_.bar_height_ * idx);
    vec2 upper_pt = hp_render_settings_.horizontal_padding_ + vertical_component;

    // find the lower right point of the hitpoints bar background
    float bar_length = max_bar_length * hp_render_settings_.bar_length_scalar_;
    vec2 horizontal_change = vec2(bar_length, hp_render_settings_.bar_height_);
    Rectf back = Rectf(upper_pt, upper_pt + horizontal_change);

    ci::gl::color(hp_render_settings_.total_hitpoints_color_);
    ci::gl::drawSolidRect(back);

    // find the lower right point of the hitpoints bar front display
    bar_length = static_cast<float>(player_hitpoints.at(idx))
                     * hp_render_settings_.bar_length_scalar_;
    horizontal_change = vec2(bar_length, hp_render_settings_.bar_height_);
    Rectf front = Rectf(upper_pt, upper_pt + horizontal_change);

    ci::gl::color(tank_colors.at(idx));
    ci::gl::drawSolidRect(front);

    // Label the hitpoints bar
    std::string label = hp_render_settings_.label_prefix_
                        + std::to_string(idx + 1)
                        + hp_render_settings_.label_suffix_
                        + std::to_string(player_hitpoints.at(idx));
    ci::gl::drawString(label, upper_pt + hp_render_settings_.label_padding_,
                       hp_render_settings_.label_color_);
  }

}

} // namespace artillery
