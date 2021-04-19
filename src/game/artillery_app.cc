//
// Created by Neil Kaushikkar on 4/18/21.
//

#include "game/artillery_app.h"

namespace artillery {

using ci::app::MouseEvent;
using ci::app::KeyEvent;

using glm::normalize;
using glm::vec2;

const ci::Color8u ArtilleryApp::kBackgroundColor = ci::Color8u(98, 187, 193);

ArtilleryApp::ArtilleryApp()
    : tank_(vec2(50, 400), Tank::kDefaultTurretOffset, 40, 15, 10, 30, 3, 106, 113, 82),
      bullet_(vec2(-10, -10), vec2(0, 0), 0, 0, 0, 1) { }

void ArtilleryApp::draw() {
  ci::gl::clear(kBackgroundColor);



  bullet_.Draw();
  tank_.Draw();
  ci::gl::color(ci::Color("red"));
  ci::gl::drawLine(tank_.GetBarrelPivotPosition(), mouse_location_);

}

void ArtilleryApp::update() {
  bullet_.UpdatePosition();
}

void ArtilleryApp::mouseMove(MouseEvent event) {
  mouse_location_ = event.getPos();
  tank_.PointBarrel(mouse_location_);
}

void ArtilleryApp::keyDown(KeyEvent event) {
  vec2 vel;
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_SPACE:
      bullet_ = tank_.ShootBullet();
      break;
  }
}

}
