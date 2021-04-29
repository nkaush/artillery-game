//
// Created by Neil Kaushikkar on 4/29/21.
//

#ifndef ARTILLERY_BUTTON_H
#define ARTILLERY_BUTTON_H

#include "utilities/json_manager.h"

#include <nlohmann/json.hpp>
#include "cinder/gl/gl.h"
#include <string>

namespace artillery {

class Button {
 public:
  Button(const ci::ColorA8u& label_color=ci::ColorA8u(0, 0, 0, 255));

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(
      Button, main_label_, alternate_label_, rectangle_, background_color_,
      hover_color_, border_width_)

  void Draw() const;

  void Update(const glm::vec2& mouse_location);

  void SetVisibility(bool is_visible);

  void ChangeLabel(bool should_set_main_label);

  bool IsHoveredOver() const;

  bool IsVisible() const;

 private:
  std::string display_label_;
  std::string main_label_;
  std::string alternate_label_;

  ci::Rectf rectangle_;

  ci::ColorA8u background_color_;
  ci::ColorA8u hover_color_;
  ci::ColorA8u label_color_;

  bool is_hovered_;
  bool is_visible_;

  float border_width_;
};

} // namespace artillery

#endif  // ARTILLERY_BUTTON_H
