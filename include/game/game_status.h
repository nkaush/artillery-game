//
// Created by Neil Kaushikkar on 5/2/21.
//

#ifndef ARTILLERY_GAME_STATUS_H
#define ARTILLERY_GAME_STATUS_H

namespace artillery {

/**
 * This enum is used to determine the state of the game and is used to relay
 * information about how to render the UI to the UI Handler object.
 */
enum class GameActivityState {
  kGameStart,
  kInProgress,
  kGameOver
};

/**
 * This enum is used to determine whether the game is paused or not. It also
 * determines whether the game has just been paused/un-paused. These 4 states
 * are used to pass game settings information configured in the settings menu
 * between the game engine and UI handler such that the information is sent
 * only once: on game pause and on game un-pause.
 */
enum class GamePauseStatus {
  kGamePaused,
  kGameUnPaused,
  kPausedWaitingForAction,
  kUnPausedWaitingForAction
};

/**
 * This enum is used as a signal sent when the UI rendering class should update
 * the progress bars that display the hitpoints of each player. This signal is
 * typically sent on game starts/restarts or when a tank is hit by a bullet.
 */
enum class HitpointsUpdateStatus {
  kTanksHit,
  kNoTanksHit,
  kForcedUpdate
};

} // namespace artillery

#endif  // ARTILLERY_GAME_STATUS_H
