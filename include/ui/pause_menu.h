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

class PauseMenu {
 public:
  explicit PauseMenu(const ci::ColorA8u& label_color=ci::ColorA8u(0, 0, 0, 255));

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(
      PauseMenu, menu_rectangle_center_, background_color_,
      button_background_color_, button_hover_color_, button_label_prefix_,
      menu_label_, label_padding_, vertical_padding_, button_left_padding_,
      button_height_, button_width_, button_toggle_width_,
      button_toggle_height_, button_border_width_)

  void Configure(size_t num_buttons);

  void SetVisibility(bool is_visible);

  void Draw() const;

  void Update(const glm::vec2& mouse_position);

  void HandleMouseDown(const glm::vec2& mouse_position);

  void SetToggleButtonStates(const std::vector<bool>& button_states);

  std::vector<bool> GetToggleButtonStates() const;

 private:
  ci::ColorA8u background_color_;
  ci::ColorA8u label_color_;
  ci::ColorA8u button_background_color_;
  ci::ColorA8u button_hover_color_;

  ci::Rectf menu_rectangle_;
  glm::vec2 menu_rectangle_center_;

  std::vector<ToggleButton> toggle_buttons_;

  std::string button_label_prefix_;
  std::vector<std::string> button_labels_;
  std::vector<glm::vec2> button_label_positions_;

  glm::vec2 menu_label_position_;
  std::string menu_label_;
  float label_padding_;

  float vertical_padding_;

  float button_left_padding_;
  float button_height_;
  float button_width_;
  float button_toggle_width_;
  float button_toggle_height_;
  float button_border_width_;

  bool is_visible_;
};

} // namespace artillery

#endif  // ARTILLERY_PAUSE_MENU_H
