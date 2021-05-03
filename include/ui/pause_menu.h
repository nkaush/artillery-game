//
// Created by Neil Kaushikkar on 4/30/21.
//

#ifndef ARTILLERY_PAUSE_MENU_H
#define ARTILLERY_PAUSE_MENU_H

#include "toggle_button.h"

#include "utilities/json_manager.h"

#include <nlohmann/json.hpp>
#include "cinder/gl/gl.h"
#include <vector>
#include <string>

namespace artillery {

/**
 * This class describes the menu shown when the game is paused. Users can adjust
 * their aim assistance settings within the menu.
 */
class PauseMenu {
 public:
  /**
   * This macro from from the nlohmann::json parsing library will generate the
   * boilerplate code required to construct a PauseMenu object with the
   * default constructor and populate it with fields from the json. The macro
   * also generates boilerplate code to serialize this object.
   */
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(
      PauseMenu, menu_rectangle_center_, background_color_,
      button_background_color_, button_hover_color_, button_label_prefix_,
      menu_label_, label_padding_, vertical_padding_, button_left_padding_,
      button_height_, button_width_, button_toggle_width_,
      button_toggle_height_, button_border_width_)

  /**
   * Default constructor. Used when creating a PauseMenu form deserialized JSON.
   * @param label_color - a ColorA8u object that describes the color of the menu
   *                      labels. Defaults to black with 100% alpha.
   */
  explicit PauseMenu(const ci::ColorA8u& label_color=ci::ColorA8u(0, 0, 0, 255));

  /**
   * Configure the pause menu by creating a setting for each player in the game.
   * @param num_buttons - the number of buttons to create - one for each player
   */
  void Configure(size_t num_buttons);

  /**
   * Set the visibility of the menu.
   * @param is_visible - a bool indicating if the pause menu should be visible
   */
  void SetVisibility(bool is_visible);

  /**
   * Render the pause menu on the window if the pause menu is set to be visible.
   */
  void Draw() const;

  /**
   * Highlight any buttons if the user mouse is hovering over them.
   * @param mouse_position - a vec2 indicating the coordinates of the user mouse
   */
  void Update(const glm::vec2& mouse_position);

  /**
   * Toggle any buttons in the menu if the mouse clicks on any buttons.
   * @param mouse_position - a vec2 indicating the coordinates of the user mouse
   */
  void HandleMouseDown(const glm::vec2& mouse_position);

  /**
   * Set the toggle states of each button in the menu.
   * @param button_states - a vector of bool with toggle states of each button
   */
  void SetToggleButtonStates(const std::vector<bool>& button_states);

  /**
   * Get the toggle states of each toggle button in the menu.
   * @return a vector of bool indicating the toggle state of each button.
   */
  std::vector<bool> GetToggleButtonStates() const;

 private:
  // Used when rendering the menu
  ci::ColorA8u background_color_;
  ci::ColorA8u label_color_;
  ci::ColorA8u button_background_color_;
  ci::ColorA8u button_hover_color_;

  // Used when rendering the menu
  ci::Rectf menu_rectangle_;
  glm::vec2 menu_rectangle_center_;

  // The UI components of the menu
  std::vector<ToggleButton> toggle_buttons_;
  std::string button_label_prefix_;
  std::vector<std::string> button_labels_;
  std::vector<glm::vec2> button_label_positions_;

  // Used in determining where to render the menu
  glm::vec2 menu_label_position_;
  std::string menu_label_;

  // Used in determining where to render the menu
  float label_padding_;
  float vertical_padding_;
  float button_left_padding_;
  float button_height_;
  float button_width_;
  float button_toggle_width_;
  float button_toggle_height_;
  float button_border_width_;

  // Contains the internal state about whether to render the menu
  bool is_visible_;
};

} // namespace artillery

#endif  // ARTILLERY_PAUSE_MENU_H
