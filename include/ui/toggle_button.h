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
  /**
   * This macro from from the nlohmann::json parsing library will generate the
   * boilerplate code required to construct a ToggleButton object with the
   * default constructor and populate it with fields from the json. The macro
   * also generates boilerplate code to serialize this object.
   */
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(ToggleButton, rectangle_, toggle_rect_,
                                 background_color_, hover_color_, border_width_)

  /**
   * Default constructor. Used to create a pause button from deserialized JSON.
   */
  ToggleButton();

  /**
   * Creates a pause button object.
   * @param button_center - a vec2 containing coordinates of the button's center
   * @param background_color - a ColorA8u indicating the button background color
   * @param hover_color - a ColorA8u indicating the color of the button when the
   *                      user mouse is hovering over the button
   * @param button_width - a float indicating the width of the button
   * @param button_height - a float indicating the height of the button
   * @param toggle_rect_width - a float indicating the inner rectangle width
   *                            that is displayed when the button is toggle on
   * @param toggle_rect_height - a float indicating the inner rectangle height
   *                             that is displayed when the button is toggle on
   * @param border_width - a float indicating the width of the button's border
   */
  ToggleButton(
      const glm::vec2& button_center, const ci::ColorA8u& background_color,
      const ci::ColorA8u& hover_color, float button_width, float button_height,
      float toggle_rect_width, float toggle_rect_height, float border_width);

  /**
   * Default destructor. Defined since this class is derived from Button class.
   */
  ~ToggleButton() override = default;

  /**
   * Renders this click button on the window. Draws the button frame. Draws the
   * button's inner toggle rectangle if the button is toggled on.
   */
  void Draw() const override;

  /**
   * Updates the button color if the user mouse is hovering over this button.
   * @param mouse_location - a vec2 indicating the coordinates of the user mouse
   */
  void Update(const glm::vec2& mouse_position) override;

  /**
   * Toggle the button state from either on to off or off to on if the user's
   * mouse clicks on the button.
   * @param mouse_position - a vec2 indicating the coordinates of the user mouse
   */
  void Toggle(const glm::vec2& mouse_position);

  /**
   * Override the button state to the bool specified: on (true) or off (false).
   * @param is_toggled - a bool indicating the new overridden button state
   */
  void SetToggleStatus(bool is_toggled);

  /**
   * Gets whether this button is toggled on or off.
   * @return a bool indicating if the button is toggled on (true) or off (false)
   */
  bool IsToggled() const;

 private:
  // The inner rectangle to render when the button is toggled on
  ci::Rectf toggle_rect_;

  // The internal state storing whether this button is toggled on
  bool is_toggled_;
};

} // namespace artillery

#endif  // ARTILLERY_TOGGLE_BUTTON_H
