//
// Created by Neil Kaushikkar on 4/18/21.
//

#ifndef ARTILLERY_ARTILLERY_APP_H
#define ARTILLERY_ARTILLERY_APP_H

#include "Cinder/app/App.h"
#include "Cinder/app/RendererGl.h"
#include "Cinder/gl/gl.h"

#include <core/tank.h>
#include <core/bullet.h>
#include <core/terrain.h>

namespace artillery {

class ArtilleryApp : public ci::app::App {
 public:
  ArtilleryApp();

  void draw() override;

  void update() override;

  void mouseMove(ci::app::MouseEvent event) override;

  void keyDown(ci::app::KeyEvent event) override;

  static const ci::Color8u kBackgroundColor;

 private:
  Tank tank_;
  Bullet bullet_;
  glm::vec2 mouse_location_;

  Terrain terrain_;
};

}

#endif  // ARTILLERY_ARTILLERY_APP_H
