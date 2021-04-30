//
// Created by Neil Kaushikkar on 4/29/21.
//

#ifndef ARTILLERY_CLICK_BUTTON_H
#define ARTILLERY_CLICK_BUTTON_H

#include "ui/button.h"

#include "utilities/json_manager.h"

#include <nlohmann/json.hpp>
#include "cinder/gl/gl.h"
#include <string>

namespace artillery {

class ClickButton : public Button {
 public:
  ClickButton();

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(
      ClickButton, main_label_, alternate_label_, rectangle_,
      background_color_, hover_color_, border_width_)

  void Draw() const override;

  void Update(const glm::vec2& mouse_location) override;

  void ChangeLabel(bool should_set_main_label);

 private:
  std::string display_label_;
  std::string main_label_;
  std::string alternate_label_;
};

} // namespace artillery

#endif  // ARTILLERY_CLICK_BUTTON_H
