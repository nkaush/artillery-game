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
  /**
   * This macro from from the nlohmann::json parsing library will generate the
   * boilerplate code required to construct a ClickButton object with the
   * default constructor and populate it with fields from the json. The macro
   * also generates boilerplate code to serialize this object.
   */
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(
      ClickButton, main_label_, alternate_label_, rectangle_,
      background_color_, hover_color_, border_width_)

  /**
   * Default constructor. Used to create a click button from deserialized JSON.
   */
  ClickButton();

  /**
   * Default destructor. Defined since this class is derived from Button class.
   */
  ~ClickButton() override = default;

  /**
   * Renders this click button on the window. Draws the button and its label.
   */
  void Draw() const override;

  /**
   * Updates the button color if the user mouse is hovering over this button.
   * @param mouse_location - a vec2 indicating the coordinates of the user mouse
   */
  void Update(const glm::vec2& mouse_location) override;

  /**
   * Changes the label to the label specified. Sets the label as the main label
   * if 'should_set_main_label' is true, otherwise uses the alternate label.
   * @param should_set_main_label - a bool indicating whether to use main label
   */
  void ChangeLabel(bool should_set_main_label);

 private:
  // The label displayed when drawing the button
  std::string display_label_;

  // Stores the main label of this button
  std::string main_label_;

  // Stores the alternate label of this button
  std::string alternate_label_;
};

} // namespace artillery

#endif  // ARTILLERY_CLICK_BUTTON_H
