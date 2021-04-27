//
// Created by Neil Kaushikkar on 4/18/21.
//

#ifndef ARTILLERY_ARTILLERY_APP_H
#define ARTILLERY_ARTILLERY_APP_H

#include "game_engine.h"

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
  // The path to the game settings json file in the cmake working directory
  static const std::string kGameSettingsFilePath;

  // The location of the user's mouse in relation to the origin at the top left
  glm::vec2 mouse_location_;

  // The game engine object that manages and executes all the logic of the game
  GameEngine game_engine_;
};

}

#endif  // ARTILLERY_ARTILLERY_APP_H
