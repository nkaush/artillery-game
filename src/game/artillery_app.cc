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

const string ArtilleryApp::kGameSettingsFilePath =
    "../../../../../data/game_settings.json";

ArtilleryApp::ArtilleryApp() {
  std::ifstream game_settings(kGameSettingsFilePath);

  if (game_settings.is_open()) {
    json json_object;
    game_settings >> json_object;

    game_engine_ = json_object.get<GameEngine>();
    game_engine_.ConfigureTanks();
  }
}

void ArtilleryApp::draw() {
  ci::gl::clear(game_engine_.GetBackgroundColor());
  game_engine_.Draw(mouse_location_);
}

void ArtilleryApp::update() {
  game_engine_.AdvanceToNextFrame();
  game_engine_.PointActiveTankBarrel(mouse_location_);
}

void ArtilleryApp::mouseMove(MouseEvent event) {
  mouse_location_ = event.getPos();
}

void ArtilleryApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_SPACE:
      game_engine_.ShootBulletFromActiveTank();
      break;
    case ci::app::KeyEvent::KEY_RIGHT:
      game_engine_.MoveCurrentTank(false);
      break;
    case ci::app::KeyEvent::KEY_LEFT:
      game_engine_.MoveCurrentTank(true);
      break;
    case ci::app::KeyEvent::KEY_r:
      std::cout << "r pressed" << std::endl; // TODO fix this
      if (game_engine_.GetGameState() == GameState::kGameOver) {
        std::cout << "reloaded" << std::endl;
        game_engine_.Reload();
      }
      break;
  }
}

}
