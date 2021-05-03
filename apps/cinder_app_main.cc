//
// Created by Neil Kaushikkar on 4/18/21.
//

#include "game/artillery_app.h"

using artillery::ArtilleryApp;

void PrepareSettings(ArtilleryApp::Settings* settings) {
  settings->setResizable(false);
  settings->setWindowSize(artillery::Terrain::kWindowWidth,
                          artillery::Terrain::kWindowHeight);
  settings->setFrameRate(artillery::ArtilleryApp::kFrameRate);
  settings->setTitle(artillery::ArtilleryApp::kAppName);
}

CINDER_APP(ArtilleryApp, ci::app::RendererGl, PrepareSettings);
