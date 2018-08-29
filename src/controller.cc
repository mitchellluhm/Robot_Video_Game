/**
 * @file controller.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>
#include <iostream> /* debugging */
#include "src/arena_params.h"
#include "src/common.h"
#include "src/controller.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

Controller::Controller() : last_dt(0) {
  // Initialize default properties for various arena entities
  arena_params aparams;
  aparams.n_obstacles = N_OBSTACLES;
  aparams.n_bases = N_BASES;
  aparams.x_dim = ARENA_X_DIM;
  aparams.y_dim = ARENA_Y_DIM;

  arena_ = new Arena(&aparams);

  // Start up the graphics (which creates the arena).
  // Run() will enter the nanogui::mainloop().
  viewer_ = new GraphicsArenaViewer(&aparams, arena_, this);
}

void Controller::Run() { viewer_->Run(); }

void Controller::AdvanceTime(double dt) {
  if ((last_dt + dt) <= .05) {
    last_dt += dt;
    return;
  }
  last_dt = 0;
  arena_->AdvanceTime(dt);
}

void Controller::AcceptCommunication(Communication com) {
  arena_->AcceptCommand(ConvertComm(com));
}

/** Converts communication from one source to appropriate communication to
 * the other source. For example, the viewer sends a kKeyUp communication,
 * and this translate to a kIncreaseSpeed communication to Arena.
 */
/**
  * @TODO: Complete the conversion code for all key presses.
  */
Communication Controller::ConvertComm(Communication com) {
  switch (com) {
  case (kKeyUp) :
    if (viewer_->IsPaused()) {
      return kNone;
    } else {
      return kIncreaseSpeed;
    }
  case (kKeyDown) :
    if (viewer_->IsPaused()) {
      return kNone;
    } else {
      return kDecreaseSpeed;
    }
  case (kKeyLeft) :
    if (viewer_->IsPaused()) {
      return kNone;
    } else {
      return kTurnLeft;
    }
  case (kKeyRight) :
    if (viewer_->IsPaused()) {
      return kNone;
    } else {
      return kTurnRight;
    }
  case (kPlay) :std::cout << "PLAY PRESSED" << std::endl;
    return kPlay;
  case (kPause) :std::cout << "PAUSE PRESSED" << std::endl;
    return kPause;
  case (kNewGame) : std::cout << "NEW GAME PRESSED" << std::endl;
    // KILL ARENA ENTITIES
    arena_->CleanArena();
    ResetArena();
    viewer_->ResetCommonGraphics();
    /*
    delete arena_;
    delete viewer_;
    arena_params aparams2;
    aparams2.n_obstacles = N_OBSTACLES;
    aparams2.n_bases = N_BASES;
    aparams2.x_dim = ARENA_X_DIM;
    aparams2.y_dim = ARENA_Y_DIM;
    arena_ = new Arena(&aparams2);
    viewer_ = new GraphicsArenaViewer(&aparams, arena_, this);
    */
    return kReset;
    /*
  case (kIncreaseSpeed):
  case (kDecreaseSpeed):
  case (kTurnRight):
  case (kTurnLeft):
  case (kReset):
  case (kWon):
  case (kLost):
    */
  default:
    return kNone;
  }
}

void Controller::ResetArena() {
  std::cout << "ResetArena() started" << std::endl;
  arena_->DeleteFactory();
  arena_->ReconstructArena();
  std::cout << "ResetArena() finished" << std::endl;
}

NAMESPACE_END(csci3081);
