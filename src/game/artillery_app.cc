//
// Created by Neil Kaushikkar on 4/18/21.
//

#include "game/artillery_app.h"

#include <nlohmann/json.hpp>
#include <fstream>

namespace artillery {

using ci::app::MouseEvent;
using ci::app::KeyEvent;
using nlohmann::json;
using std::string;
using glm::vec2;

const string ArtilleryApp::kGameSettingsFilePath = "/Users/neilkaushikkar/Cinder/my-projects/final-project-nkaush/src/data/game_settings.json";

ArtilleryApp::ArtilleryApp() {
  std::ifstream game_settings(kGameSettingsFilePath);

  if (game_settings.is_open()) {
    json json_object;
    game_settings >> json_object;

    game_engine_ = json_object.get<GameEngine>();
  }
}

void ArtilleryApp::draw() {
  ci::gl::clear(game_engine_.GetBackgroundColor());
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
