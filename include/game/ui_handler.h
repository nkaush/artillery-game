//
// Created by Neil Kaushikkar on 4/30/21.
//

#ifndef ARTILLERY_UI_HANDLER_H
#define ARTILLERY_UI_HANDLER_H

#include "game/game_engine.h"

#include "ui/pause_button.h"
#include "ui/click_button.h"
#include "ui/progress_bar.h"
#include "ui/pause_menu.h"

#include "cinder/gl/gl.h"
#include <vector>
#include <string>

namespace artillery {

enum class GamePauseStatus {
  kGamePaused,
  kGameUnPaused,
  kPausedWaitingForAction,
  kUnPausedWaitingForAction
};

class UIHandler {
 public:
  UIHandler();

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(
      UIHandler, start_button_, pause_button_, hp_render_settings_, pause_menu_)

  void Configure(const std::vector<ci::ColorA8u>& tank_colors,
                 float max_hitpoints);

  void Draw() const;

  void Update(const glm::vec2& mouse_location, const GameState& game_state,
              const std::vector<size_t>& player_hitpoints);

  void HandleMouseDown(const glm::vec2& mouse_location);

  void SetPauseMenuStates(const std::vector<bool>& button_states);

  bool IsStartButtonVisible() const;

  bool IsStartButtonHoveredOver() const;

  bool IsGamePaused() const;

  GamePauseStatus RetrieveGamePauseStatus();

  std::vector<bool> GetPauseMenuStates() const;

 private:
  ClickButton start_button_;
  PauseButton pause_button_;

  PauseMenu pause_menu_;

  ProgressBarRenderSettings hp_render_settings_;
  std::vector<ProgressBar> hitpoints_bars_;

  GamePauseStatus pause_status_;
};

} // namespace artillery

#endif  // ARTILLERY_UI_HANDLER_H
