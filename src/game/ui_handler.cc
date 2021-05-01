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

void UIHandler::Draw() const {
  start_button_.Draw();
  pause_button_.Draw();

  for (const ProgressBar& progress_bar : hitpoints_bars_) {
    progress_bar.Draw();
  }
}

void UIHandler::Configure(const vector<ci::ColorA8u>& tank_colors,
                          float max_hitpoints) {
  start_button_.ChangeLabel(true);

  hitpoints_bars_ = vector<ProgressBar>();
  hitpoints_bars_.reserve(tank_colors.size() * sizeof(ProgressBar));

  for (size_t idx = 0; idx < tank_colors.size(); idx++) {
    hitpoints_bars_.emplace_back(
        hp_render_settings_, tank_colors.at(idx), max_hitpoints, idx);
  }
}

void UIHandler::Update(const vec2& mouse_location, const GameState& game_state,
                       const vector<size_t>& player_hitpoints) {
  start_button_.Update(mouse_location);
  pause_button_.Update(mouse_location);

  for (size_t idx = 0; idx < hitpoints_bars_.size(); idx++) {
    hitpoints_bars_.at(idx).UpdateProgress(
        static_cast<float>(player_hitpoints.at(idx)));
  }

  if (game_state == GameState::kGameOver) {
    start_button_.ChangeLabel(false);
    start_button_.SetVisibility(true);
  }
}

void UIHandler::HandleMouseDown(const vec2& mouse_location) {
  pause_button_.Toggle(mouse_location);

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

} // namespace artillery
