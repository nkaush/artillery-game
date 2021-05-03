//
// Created by Neil Kaushikkar on 4/18/21.
//

#include "game/artillery_app.h"
#include "game/game_status.h"

#include <nlohmann/json.hpp>
#include <fstream>

namespace artillery {

using ci::app::MouseEvent;
using ci::app::KeyEvent;

using glm::vec2;

using nlohmann::json;

using std::string;

const string ArtilleryApp::kGameSettingsFilePath = "data/game_settings.json";
const string ArtilleryApp::kRenderSettingsFilePath = "data/render_settings.json";

ArtilleryApp::ArtilleryApp() {
  std::ifstream game_settings(kGameSettingsFilePath);

  // Load the game settings from a JSON file and configure all game elements
  if (game_settings.is_open()) {
    json game_engine_json;
    game_settings >> game_engine_json;

    game_engine_ = game_engine_json.get<GameEngine>();
    game_engine_.ConfigureTanks();

    game_settings.close();
  } else {
    throw std::invalid_argument("Could not load game settings JSON.");
  }

  std::ifstream render_settings(kRenderSettingsFilePath);

  // Load the UI render settings from a JSON file and configure all UI elements
  if (render_settings.is_open()) {
    json render_settings_json;
    render_settings >> render_settings_json;

    ui_handler_ = render_settings_json.get<UIHandler>();
    ui_handler_.Configure(game_engine_.GetTankColors(),
                          game_engine_.GetMaxHitpoints());

    render_settings.close();
  } else {
    throw std::invalid_argument("Could not load UI rendering settings JSON.");
  }
}

void ArtilleryApp::draw() {
  ci::gl::clear(game_engine_.GetBackgroundColor());

  game_engine_.Draw(mouse_location_); // render all game elements
  ui_handler_.Draw();                 // render all UI elements

  // Make the current reference color white so the colors render correctly
  ci::gl::color(ci::Color(1, 1, 1));
}

void ArtilleryApp::update() {
  game_engine_.AdvanceToNextFrame();
  game_engine_.PointActiveTankBarrel(mouse_location_);

  ui_handler_.Update(mouse_location_, game_engine_.GetGameActivityState(),
                     game_engine_.RetrieveHitpointsUpdateStatus(),
                     game_engine_.GetPlayerHitpoints());
}

void ArtilleryApp::mouseDown(MouseEvent event) {
  ui_handler_.HandleMouseDown(event.getPos());

  GamePauseStatus pause_status = ui_handler_.RetrieveGamePauseStatus();

  // If the game is paused, get the current aim assistance state of each player
  if (pause_status == GamePauseStatus::kGamePaused) {
    ui_handler_.SetPauseMenuStates(game_engine_.GetPlayerAimAssistanceStatus());
  } else if (pause_status == GamePauseStatus::kGameUnPaused) {
    // if the game is un-paused, set the aim assistance state of each player
    game_engine_.SetPlayerAimAssistance(ui_handler_.GetPauseMenuStates());
  }

  // Restart the game if the restart button is clicked, and the game is over
  if (ui_handler_.IsStartButtonHoveredOver()
      && game_engine_.GetGameActivityState() == GameActivityState::kGameOver
      && !ui_handler_.IsGamePaused()) {
    game_engine_.Restart();
  }
}

void ArtilleryApp::mouseMove(MouseEvent event) {
  mouse_location_ = event.getPos();
}

void ArtilleryApp::keyDown(KeyEvent event) {
  // If the start button is active, do not allow commands until game is started
  if (ui_handler_.IsStartButtonVisible() || ui_handler_.IsGamePaused()) {
    return;
  }

  switch (event.getCode()) {
    case KeyEvent::KEY_SPACE: // shoot a bullet if SPACE is pressed
      game_engine_.ShootBulletFromActiveTank();
      break;
    case KeyEvent::KEY_RIGHT:
      // move the current player right if the right arrow is pressed
      game_engine_.MoveCurrentTank(false);
      break;
    case KeyEvent::KEY_LEFT:
      // move the current player left if the left arrow is pressed
      game_engine_.MoveCurrentTank(true);
      break;
  }
}

} // namespace artillery
