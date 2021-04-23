//
// Created by Neil Kaushikkar on 4/18/21.
//

#include "game/artillery_app.h"

namespace artillery {

using ci::app::MouseEvent;
using ci::app::KeyEvent;

using glm::vec2;

const ci::Color8u ArtilleryApp::kBackgroundColor = ci::Color8u(98, 187, 193);

ArtilleryApp::ArtilleryApp() : game_engine_() {
}

void ArtilleryApp::draw() {
  ci::gl::clear(kBackgroundColor);

  game_engine_.Draw(mouse_location_);
}

void ArtilleryApp::update() {
  game_engine_.AdvanceToNextFrame();
}

void ArtilleryApp::mouseMove(MouseEvent event) {
  mouse_location_ = event.getPos();
  game_engine_.PointActiveTankBarrel(mouse_location_);
}

void ArtilleryApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_SPACE:
      game_engine_.ShootBulletFromActiveTank();
      break;
  }
}

}
