//
// Created by Neil Kaushikkar on 4/30/21.
//

#ifndef ARTILLERY_PAUSE_BUTTON_H
#define ARTILLERY_PAUSE_BUTTON_H

#include "button.h"

#include "utilities/json_manager.h"

#include <nlohmann/json.hpp>
#include "cinder/gl/gl.h"
#include <vector>

namespace artillery {

class PauseButton : public Button {
 public:
  PauseButton();

  ~PauseButton() override = default;

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(
      PauseButton, rectangle_, pause_icon_, play_icon_,
      background_color_, hover_color_, border_width_)

  void Draw() const override;

  void Update(const glm::vec2& mouse_position) override;

  void Toggle(const glm::vec2& mouse_position);

  bool IsPaused() const;

 private:
  static constexpr size_t kTrianglePointsCount = 3;

  std::vector<ci::Rectf> pause_icon_;

  glm::vec2 play_icon_[kTrianglePointsCount];

  bool is_paused_;
};

} // namespace artillery

#endif  // ARTILLERY_PAUSE_BUTTON_H
