//
// Created by Neil Kaushikkar on 4/30/21.
//

#ifndef ARTILLERY_TOGGLE_BUTTON_H
#define ARTILLERY_TOGGLE_BUTTON_H

#include "ui/button.h"

#include "utilities/json_manager.h"

#include <nlohmann/json.hpp>
#include "cinder/gl/gl.h"

namespace artillery {

class ToggleButton : public Button {
 public:
  ToggleButton();

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(ToggleButton, rectangle_, toggle_rect_,
                                 background_color_, hover_color_, border_width_)

  void Draw() const override;

  void Update(const glm::vec2& mouse_position) override;

  void Toggle(const glm::vec2& mouse_position);

  bool IsToggled() const;

 private:
  ci::Rectf toggle_rect_;
  bool is_toggled_;
};

} // namespace artillery

#endif  // ARTILLERY_TOGGLE_BUTTON_H
