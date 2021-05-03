//
// Created by Neil Kaushikkar on 4/30/21.
//

#include "game/ui_handler.h"

namespace artillery {

using std::vector;

using ci::ColorA8u;
using ci::Rectf;

using glm::vec2;

UIHandler::UIHandler()
    : pause_status_(GamePauseStatus::kUnPausedWaitingForAction) {}

void UIHandler::Draw() const {
  start_button_.Draw();
  pause_button_.Draw();
  pause_menu_.Draw();

  for (const ProgressBar& progress_bar : hitpoints_bars_) {
    progress_bar.Draw();
  }
}

void UIHandler::Configure(const vector<ci::ColorA8u>& tank_colors,
                          float max_hitpoints) {
  // Create a aim assistance toggle button for each tank in the game
  pause_menu_.Configure(tank_colors.size());
  start_button_.ChangeLabel(true);

  hitpoints_bars_ = vector<ProgressBar>();
  hitpoints_bars_.reserve(tank_colors.size() * sizeof(ProgressBar));

  // Create a hitpoints bar for each tank in the game
  for (size_t idx = 0; idx < tank_colors.size(); idx++) {
    hitpoints_bars_.emplace_back(
        hp_render_settings_, tank_colors.at(idx), max_hitpoints, idx);
  }
}

void UIHandler::Update(const glm::vec2& mouse_location,
                       const GameActivityState& game_state,
                       const HitpointsUpdateStatus& hitpoints_status,
                       const std::vector<size_t>& player_hitpoints) {
  // Handle hover interactions of UI elements that change color when hovered over
  start_button_.Update(mouse_location);
  pause_button_.Update(mouse_location);
  pause_menu_.Update(mouse_location);

  // Update the hitpoints progress bars if any tank(s) were recently hit
  if (hitpoints_status != HitpointsUpdateStatus::kNoTanksHit) {
    for (size_t idx = 0; idx < hitpoints_bars_.size(); idx++) {
      hitpoints_bars_.at(idx).UpdateProgress(
          static_cast<float>(player_hitpoints.at(idx)));
    }
  }

  // If the game has finished, show the restart button
  if (game_state == GameActivityState::kGameOver) {
    start_button_.ChangeLabel(false);
    start_button_.SetVisibility(true);
  }
}

void UIHandler::HandleMouseDown(const vec2& mouse_location) {
  pause_button_.Pause(mouse_location);

  // If the pause button was just clicked, send a signal indicating so
  if (pause_status_ == GamePauseStatus::kUnPausedWaitingForAction
      && pause_button_.IsPaused()) {
    pause_status_ = GamePauseStatus::kGamePaused;
  }

  // If the unpause button was just clicked, send a signal indicating so
  if (pause_status_ == GamePauseStatus::kPausedWaitingForAction
      && !pause_button_.IsPaused()) {
    pause_status_ = GamePauseStatus::kGameUnPaused;
  }

  // If the game is paused, show the pause menu
  pause_menu_.SetVisibility(pause_button_.IsPaused());
  pause_menu_.HandleMouseDown(mouse_location);

  // If the start button was clicked, hide it
  if (start_button_.IsHoveredOver() && !IsGamePaused()) {
    start_button_.SetVisibility(false);
  }
}

void UIHandler::SetPauseMenuStates(const vector<bool>& button_states) {
  pause_menu_.SetToggleButtonStates(button_states);
}

bool UIHandler::IsStartButtonVisible() const {
  return start_button_.IsVisible();
}

bool UIHandler::IsStartButtonHoveredOver() const {
  return start_button_.IsHoveredOver();
}

bool UIHandler::IsGamePaused() const {
  return pause_status_ == GamePauseStatus::kPausedWaitingForAction
    || pause_status_ == GamePauseStatus::kGamePaused;
}

GamePauseStatus UIHandler::RetrieveGamePauseStatus() {
  GamePauseStatus current_status = pause_status_;

  // Receive the signal sent the instant the game is paused/un-paused
  if (current_status == GamePauseStatus::kGamePaused) {
    // acknowledge signal as received and signal we are waiting for user input
    pause_status_ = GamePauseStatus::kPausedWaitingForAction;
  } else if (current_status == GamePauseStatus::kGameUnPaused) {
    pause_status_ = GamePauseStatus::kUnPausedWaitingForAction;
  }

  return current_status;
}

std::vector<bool> UIHandler::GetPauseMenuStates() const {
  return pause_menu_.GetToggleButtonStates();
}

} // namespace artillery
