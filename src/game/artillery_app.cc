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

    start_button_ = json_object.at("start_button_").get<Button>();
    start_button_.ChangeLabel(true);

    game_engine_ = json_object.get<GameEngine>();
    game_engine_.ConfigureTanks();
  }
}

void ArtilleryApp::draw() {
  ci::gl::clear(game_engine_.GetBackgroundColor());
  game_engine_.Draw(mouse_location_);

  start_button_.Draw();
  ci::gl::color(ci::Color(1, 1, 1));
}

void ArtilleryApp::update() {
  game_engine_.AdvanceToNextFrame();
  start_button_.Update(mouse_location_);
  game_engine_.PointActiveTankBarrel(mouse_location_);

  if (game_engine_.GetGameState() == GameState::kGameOver) {
    start_button_.ChangeLabel(false);
    start_button_.SetVisibility(true);
  }
}

void ArtilleryApp::mouseDown(MouseEvent event) {
  if (start_button_.IsHoveredOver()) {
    start_button_.SetVisibility(false);

    if (game_engine_.GetGameState() == GameState::kGameOver) {
      game_engine_.Reload();
    }
  }
}

void ArtilleryApp::mouseMove(MouseEvent event) {
  mouse_location_ = event.getPos();
}

void ArtilleryApp::keyDown(KeyEvent event) {
  // If the start button is active, do not allow commands until game is started
  if (start_button_.IsVisible()) {
    return;
  }

  switch (event.getCode()) {
    case KeyEvent::KEY_SPACE:
      game_engine_.ShootBulletFromActiveTank();
      break;
    case KeyEvent::KEY_RIGHT:
      game_engine_.MoveCurrentTank(false);
      break;
    case KeyEvent::KEY_LEFT:
      game_engine_.MoveCurrentTank(true);
      break;
  }
}

} // namespace artillery
