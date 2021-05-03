//
// Created by Neil Kaushikkar on 4/18/21.
//

#ifndef ARTILLERY_ARTILLERY_APP_H
#define ARTILLERY_ARTILLERY_APP_H

#include "game_engine.h"
#include "ui_handler.h"

#include "ui/toggle_button.h"
#include "ui/click_button.h"

#include "cinder/app/RendererGl.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include <string>

namespace artillery {

/**
 * This class is used to handle the user-interface interaction.
 */
class ArtilleryApp : public ci::app::App {
 public:
  // The number of frames to run through per second
  static constexpr float kFrameRate = 100;

  // The title of the window this app displays in
  static const std::string kAppName;

  /**
   * Default constructor invoked when Cinder starts the app. Loads the game
   * settings json file containing all the settings for this game.
   */
  ArtilleryApp();

  /**
   * Draw all of the components of the game on the window.
   */
  void draw() override;

  /**
   * Update all of the components of the game on the window.
   */
  void update() override;

  /**
   * Executes the user's request from clicking UI elements.
   * @param event - a MouseEvent class containing the new mouse coordinates
   */
  void mouseDown(ci::app::MouseEvent event) override;

  /**
   * Updates the stored mouse position whenever the user moves the mouse.
   * @param event - a MouseEvent class containing the new mouse coordinates
   */
  void mouseMove(ci::app::MouseEvent event) override;

  /**
   * Fulfills actions when keys corresponding to those actions are pressed.
   * @param event - a KeyEvent object containing a value/name of the key pressed
   */
  void keyDown(ci::app::KeyEvent event) override;

 private:
  // The path to the settings json files in the working directory
  static const std::string kGameSettingsFilePath;
  static const std::string kRenderSettingsFilePath;

  // The location of the user's mouse in relation to the origin at the top left
  glm::vec2 mouse_location_;

  // The game engine object that manages and executes all the logic of the game
  GameEngine game_engine_;

  // The object that manages and executes all logic of user interaction
  UIHandler ui_handler_;
};

}

#endif  // ARTILLERY_ARTILLERY_APP_H
