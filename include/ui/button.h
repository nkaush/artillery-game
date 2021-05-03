//
// Created by Neil Kaushikkar on 4/30/21.
//

#ifndef ARTILLERY_BUTTON_H
#define ARTILLERY_BUTTON_H

#include "cinder/gl/gl.h"

namespace artillery {

/**
 * This class represents a generic button that changes color when hovered
 * over by the user's mouse. This button also has functionality to stop being
 * rendered at any time if the button is set to not visible.
 */
class Button {
 public:
  /**
   * Default constructor. Sets the border color to black.
   * @param border_color
   */
  explicit Button(const ci::ColorA8u& border_color=ci::ColorA8u(0, 0, 0, 255));

  /**
   * Creates a Button object with the specified parameters.
   * @param center - a vec2 indicating the coordinates of the button's center
   * @param width - a float indicating the width of the button
   * @param height - a float indicating the height of the button
   * @param border_width - a float indicating the width of the button border
   * @param background_color - a ColorA8u object indicating the color to render
   *                           the button in while it is idle
   * @param hover_color - a ColorA8u object indicating the color to render the
   *                      button in when the user mouse hovers over it
   * @param border_color - a ColorA8u object indicating the color to render the
   *                       button border in - default black
   */
  Button(const glm::vec2& center, float width, float height, float border_width,
         const ci::ColorA8u& background_color, const ci::ColorA8u& hover_color,
         const ci::ColorA8u& border_color=ci::ColorA8u(0, 0, 0, 255));

  /**
   * Default destructor. All derived classes must override the destructor.
   */
  virtual ~Button() = default;

  /**
   * Renders the button on the window. All derived classes must override this.
   */
  virtual void Draw() const;

  /**
   * Updates the button color if the user mouse is hovering over this button.
   * All derived classes must override this method.
   * @param mouse_location - a vec2 indicating the coordinates of the user mouse
   */
  virtual void Update(const glm::vec2& mouse_location);

  /**
   * Set the visibility of this button.
   * @param is_visible - a bool indicating the visibility of the button
   */
  void SetVisibility(bool is_visible);

  /**
   * Gets whether this button is being hovered over by the user's mouse.
   * @return a bool indicating whether this button is being hovered over
   */
  bool IsHoveredOver() const;

  /**
   * Gets whether this button is visible in the window.
   * @return a bool indicating whether this button is visible in the window
   */
  bool IsVisible() const;

 protected:
  // The bounding rectangle used to render the button
  ci::Rectf rectangle_;

  // The colors used when rendering this button
  ci::ColorA8u hover_color_;
  ci::ColorA8u border_color_;
  ci::ColorA8u background_color_;

  bool is_visible_;
  bool is_hovered_;

  float border_width_;
};

} // namespace artillery

#endif  // ARTILLERY_BUTTON_H
