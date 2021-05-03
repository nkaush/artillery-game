//
// Created by Neil Kaushikkar on 4/30/21.
//

#ifndef ARTILLERY_UI_HANDLER_H
#define ARTILLERY_UI_HANDLER_H

#include "game_status.h"

#include "ui/pause_button.h"
#include "ui/click_button.h"
#include "ui/progress_bar.h"
#include "ui/pause_menu.h"

#include "cinder/gl/gl.h"
#include <vector>
#include <string>

namespace artillery {

class UIHandler {
 public:
  /**
   * This macro from from the nlohmann::json parsing library will generate the
   * boilerplate code required to construct a UIHandler object with the
   * default constructor and populate it with fields from the json. The macro
   * also generates boilerplate code to serialize this object.
   */
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(
      UIHandler, start_button_, pause_button_, hp_render_settings_, pause_menu_)

  /**
   * Default constructor. Initializes an empty UIHandler.
   */
  UIHandler();

  /**
   * Configures this UIHandler object after its fields have been populated with
   * deserialized JSON. Sets up the pause menu and hitpoints progress bars.
   * @param tank_colors - the colors of each tank in the game
   * @param max_hitpoints - the max number of hitpoints a tank can have
   */
  void Configure(const std::vector<ci::ColorA8u>& tank_colors,
                 float max_hitpoints);

  /**
   * Renders all of the UI components on the window.
   */
  void Draw() const;

  /**
   * Updates all of the UI components. Shades buttons if they are hovered over
   * by the mouse. Updates the progress bars with the hitpoints of each player.
   * @param mouse_location - a vec2 with the coordinates of the user's mouse
   * @param game_state - a GameActivityState enum indicating the
   *                     activity state of the game
   * @param hitpoints_status - a HitpointsUpdateStatus enum indicating whether
   *                           the hitpoints progress bars need to be updated
   * @param player_hitpoints - a vector of size_t indicating the number
   *                           of hitpoints each player has
   */
  void Update(const glm::vec2& mouse_location,
              const GameActivityState& game_state,
              const HitpointsUpdateStatus& hitpoints_status,
              const std::vector<size_t>& player_hitpoints);

  /**
   * Executes the UI interaction logic after a user click. Updates game states
   * based on the UI elements interacted with.
   * @param mouse_location - a vec2 with the coordinates of the user's mouse
   */
  void HandleMouseDown(const glm::vec2& mouse_location);

  /**
   * Sets the states of the toggle buttons before showing the pause menu.
   * @param button_states - a vector of bool indicating the toggle state of
   *                        each button in the pause menu
   */
  void SetPauseMenuStates(const std::vector<bool>& button_states);

  /**
   * Getter for the visibility of the start button.
   * @return a bool indicating whether the start button is visible
   */
  bool IsStartButtonVisible() const;

  /**
   * Getter for the hover status of the start button.
   * @return a bool indicating whether the start button is being hovered over
   */
  bool IsStartButtonHoveredOver() const;

  /**
   * Getter for whether the game is paused or not.
   * @return a bool indicating whether the game is paused or not
   */
  bool IsGamePaused() const;

  /**
   * Retrieves the enum signal sent after a pause button interaction. Updates
   * the internal GamePauseStatus state to signal the signal has been received
   * and the UI logic is waiting for a user action.
   * @return the current GamePauseStatus of the UI interaction logic
   */
  GamePauseStatus RetrieveGamePauseStatus();

  /**
   * Gets the toggle state of each toggle button in the pause menu.
   * @return a vector of bool indicating the toggle state of each button
   */
  std::vector<bool> GetPauseMenuStates() const;

 private:
  // The UI that the user can interact with
  ClickButton start_button_;
  PauseButton pause_button_;
  PauseMenu pause_menu_;

  // The settings loaded from deserialized JSON used to render hitpoints bars
  ProgressBarRenderSettings hp_render_settings_;
  std::vector<ProgressBar> hitpoints_bars_;

  GamePauseStatus pause_status_;
};

} // namespace artillery

#endif  // ARTILLERY_UI_HANDLER_H
