/**
 * @file obstacle.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/obstacle.h"
#include <iostream> /* debugging */
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Obstacle::Obstacle() :
    motion_handler_(this),
    motion_behavior_(this) {
  set_color(OBSTACLE_COLOR);
  set_pose(OBSTACLE_POSITION);
  set_radius(OBSTACLE_RADIUS);
  set_type(kObstacle);
  // Obstacle should be moving when user starts game NOT when program started
  set_default_velocity(WheelVelocity(0, 0));
  set_last_velocity(WheelVelocity(2, 2));
}

void Obstacle::TimestepUpdate(unsigned int dt) {
  if (this->reverse_state_) {
    // increment the ticks it has been in reverse state
    reverse_state_tick_++;
  }
  if (this->reverse_state_tick_ > 25) {
    this->reverse_state_ = false;
    this->reverse_state_tick_ = 0;
    this->EndReverseArc();
  }
  // Update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());
} /* TimestepUpdate() */

void Obstacle::StartSpeed() {
  motion_handler_.set_velocity(2.0, 2.0);
}

void Obstacle::ResumeSpeed() {
  this->motion_handler_.set_velocity(this->get_last_velocity());
}

void Obstacle::PauseSpeed() {
  // store velocity before the pause
  this->set_last_velocity(this->motion_handler_.get_velocity());
  // stop the Obstacle
  this->motion_handler_.set_velocity(0, 0);
}

void Obstacle::HandleCollision(EntityType object_type, ArenaEntity * object) {
  switch (object_type) {
  case kObstacle:  // Subtract an available life
  case kRightWall:
  case kLeftWall:
  case kTopWall:
  case kBottomWall:
  case kBase:  // change base color
    if (object != NULL)
      // object->set_color({ 255, 0, 0 });
    break;
  case kEntity:
  case kRobot:
  case kUndefined:
  default: break;
  }
  // Stop, pivot, move in arc (same direction everytime)
  std::cout << "Obstacle's HandleCollsion() was called." << std::endl;
  this->reverse_state_ = true;
  this->reverse_state_tick_ = 0;
  ReverseArc();
}

void Obstacle::ReverseArc() {
  if (this->moving_forward_) {
    motion_handler_.set_velocity(-2.0, -1.0);
    this->moving_forward_ = false;
  } else {
    motion_handler_.set_velocity(1.0, 2.0);
    this->moving_forward_ = true;
  }
}

void Obstacle::EndReverseArc() {
  if (this->moving_forward_) {
    motion_handler_.set_velocity(2.0, 2.0);
  } else {
    motion_handler_.set_velocity(-2.0, -2.0);
  }
}

NAMESPACE_END(csci3081);
