//
// Created by Neil Kaushikkar on 4/18/21.
//

#ifndef ARTILLERY_ARTILLERY_APP_H
#define ARTILLERY_ARTILLERY_APP_H

#include "game_engine.h"

#include "Cinder/app/App.h"
#include "Cinder/app/RendererGl.h"
#include "Cinder/gl/gl.h"

#include <string>

namespace artillery {

class ArtilleryApp : public ci::app::App {
 public:
  ArtilleryApp();

  void draw() override;

  void update() override;

  void mouseMove(ci::app::MouseEvent event) override;

  void keyDown(ci::app::KeyEvent event) override;

 private:
  static const std::string kGameSettingsFilePath;

  glm::vec2 mouse_location_;

  GameEngine game_engine_;
};

}

#endif  // ARTILLERY_ARTILLERY_APP_H
