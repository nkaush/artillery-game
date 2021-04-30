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

const string ArtilleryApp::kGameSettingsFilePath = "data/game_settings.json";
const string ArtilleryApp::kRenderSettingsFilePath = "data/render_settings.json";

ArtilleryApp::ArtilleryApp() {
  std::ifstream game_settings(kGameSettingsFilePath);

  if (game_settings.is_open()) {
    json game_engine_json;
    game_settings >> game_engine_json;

    game_engine_ = game_engine_json.get<GameEngine>();
    game_engine_.ConfigureTanks();

    game_settings.close();
  }

  std::ifstream render_settings(kRenderSettingsFilePath);

  if (render_settings.is_open()) {
    json render_settings_json;
    render_settings >> render_settings_json;

    ui_handler_ = render_settings_json.get<UIHandler>();
    ui_handler_.Configure();

    render_settings.close();
  }
}

void ArtilleryApp::draw() {
  ci::gl::clear(game_engine_.GetBackgroundColor());
  game_engine_.Draw(mouse_location_);

  ui_handler_.Draw(game_engine_.GetPlayerHitpoints(),
                   game_engine_.GetTankColors(),
                   game_engine_.GetMaxHitPoints());

  ci::gl::color(ci::Color(1, 1, 1));
}

void ArtilleryApp::update() {
  game_engine_.AdvanceToNextFrame();
  game_engine_.PointActiveTankBarrel(mouse_location_);

  ui_handler_.Update(game_engine_.GetGameState(), mouse_location_);
}

void ArtilleryApp::mouseDown(MouseEvent event) {
  ui_handler_.HandleMouseDown(event.getPos());

  if (ui_handler_.IsStartButtonHoveredOver()
      && game_engine_.GetGameState() == GameState::kGameOver) {
    game_engine_.Reload();
  }
}

void ArtilleryApp::mouseMove(MouseEvent event) {
  mouse_location_ = event.getPos();
}

void ArtilleryApp::keyDown(KeyEvent event) {
  // If the start button is active, do not allow commands until game is started
  if (ui_handler_.IsStartButtonVisible()) {
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
