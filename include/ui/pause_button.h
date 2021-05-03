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
  /**
   * This macro from from the nlohmann::json parsing library will generate the
   * boilerplate code required to construct a PauseButton object with the
   * default constructor and populate it with fields from the json. The macro
   * also generates boilerplate code to serialize this object.
   */
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(
      PauseButton, rectangle_, pause_icon_, play_icon_,
      background_color_, hover_color_, border_width_)

  /**
   * Default constructor. Used to create a pause button from deserialized JSON.
   */
  PauseButton();

  /**
   * Default destructor. Defined since this class is derived from Button class.
   */
  ~PauseButton() override = default;

  /**
   * Renders this button in the frame. Renders a play icon if the game is
   * paused. Renders a pause icon if the game is in progress.
   */
  void Draw() const override;

  /**
   * Updates the button color if the user mouse is hovering over this button.
   * @param mouse_location - a vec2 indicating the coordinates of the user mouse
   */
  void Update(const glm::vec2& mouse_position) override;

  /**
   * Pause the button state from either paused to in play or in play to paused.
   * @param mouse_position - a vec2 indicating the coordinates of the user mouse
   */
  void Pause(const glm::vec2& mouse_position);

  /**
   * Gets whether the button is currently in the paused state or not.
   * @return a bool indicating whether the button is in the paused state
   */
  bool IsPaused() const;

 private:
  // Used to determine the number of points to deserialize from play icon JSON
  static constexpr size_t kTrianglePointsCount = 3;

  // The rectangle components that make up the pause icon
  std::vector<ci::Rectf> pause_icon_;

  // The points that form the corners of the play icon triangle
  glm::vec2 play_icon_[kTrianglePointsCount];

  // Stores the state of the button: whether the button is in the pause state
  bool is_paused_;
};

} // namespace artillery

#endif  // ARTILLERY_PAUSE_BUTTON_H
