//
// Created by Neil Kaushikkar on 4/30/21.
//

#ifndef ARTILLERY_UI_HANDLER_H
#define ARTILLERY_UI_HANDLER_H

#include "game/game_engine.h"

#include "ui/click_button.h"
#include "ui/toggle_button.h"

#include "cinder/gl/gl.h"
#include <vector>
#include <string>

namespace artillery {

/**
 * This struct contains information on how to render the bars that indicate
 * the number of hitpoints each player has.
 */
struct HitpointsRenderingSettings {
  glm::vec2 vertical_padding_;
  glm::vec2 horizontal_padding_;
  glm::vec2 label_padding_;

  size_t bar_height_;
  float bar_length_scalar_;

  std::string label_prefix_;
  std::string label_suffix_;

  ci::ColorA8u total_hitpoints_color_;
  ci::ColorA8u label_color_;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    HitpointsRenderingSettings, vertical_padding_, horizontal_padding_,
    bar_height_, bar_length_scalar_, total_hitpoints_color_, label_prefix_,
    label_suffix_, label_color_, label_padding_)

class UIHandler {
 public:
  UIHandler();

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(
      UIHandler, start_button_, toggle_button_, hp_render_settings_)

  void Configure();

  void Draw(const std::vector<size_t>& player_hitpoints,
            const std::vector<ci::ColorA8u>& tank_colors,
            size_t max_hitpoints) const;

  void Update(const GameState& game_state, const glm::vec2& mouse_location);

  void HandleMouseDown(const glm::vec2& mouse_location);

  bool IsStartButtonVisible() const;

  bool IsStartButtonHoveredOver() const;

 private:
  ClickButton start_button_;
  ToggleButton toggle_button_;

  HitpointsRenderingSettings hp_render_settings_;

  void DrawHitpointsBars(const std::vector<size_t>& player_hitpoints,
                         const std::vector<ci::ColorA8u>& tank_colors,
                         size_t max_hitpoints) const;
};

} // namespace artillery

#endif  // ARTILLERY_UI_HANDLER_H
