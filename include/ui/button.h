//
// Created by Neil Kaushikkar on 4/30/21.
//

#ifndef ARTILLERY_BUTTON_H
#define ARTILLERY_BUTTON_H

#include "cinder/gl/gl.h"

namespace artillery {

class Button {
 public:
  explicit Button(const ci::ColorA8u& border_color=ci::ColorA8u(0, 0, 0, 255));

  Button(const glm::vec2& center, float width, float height, float border_width,
         const ci::ColorA8u& background_color, const ci::ColorA8u& hover_color,
         const ci::ColorA8u& border_color=ci::ColorA8u(0, 0, 0, 255));

  virtual ~Button() = default;

  virtual void Draw() const;

  virtual void Update(const glm::vec2& mouse_location);

  void SetVisibility(bool is_visible);

  bool IsHoveredOver() const;

  bool IsVisible() const;

 protected:
  ci::Rectf rectangle_;

  ci::ColorA8u hover_color_;
  ci::ColorA8u border_color_;
  ci::ColorA8u background_color_;

  bool is_visible_;
  bool is_hovered_;

  float border_width_;
};

} // namespace artillery

#endif  // ARTILLERY_BUTTON_H
