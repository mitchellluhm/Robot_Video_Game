/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot.h"
#include "src/params.h"

#include "src/base.h" /* */

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot() :
    motion_handler_(this),
    motion_behavior_(this),
    lives_(9) {
  set_type(kRobot);
  set_color(ROBOT_COLOR);
  set_pose(ROBOT_INIT_POS);
  set_radius(ROBOT_RADIUS);
  set_default_velocity(WheelVelocity(0, 0));
  set_last_velocity(WheelVelocity(0, 0));
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(unsigned int dt) {
  // Update heading as indicated by touch sensor
  motion_handler_.UpdateVelocity();

  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

  // Reset Sensor for next cycle
  sensor_touch_->Reset();
} /* TimestepUpdate() */

void Robot::Reset() {
  set_pose(ROBOT_INIT_POS);
  motion_handler_.set_max_speed(ROBOT_MAX_SPEED);
  motion_handler_.set_max_angle(ROBOT_MAX_ANGLE);
  sensor_touch_->Reset();
} /* Reset() */

void Robot::ResumeSpeed() {
  motion_handler_.set_velocity(this->get_last_velocity());
}

void Robot::PauseSpeed() {
  // store velocity before the pause
  this->set_last_velocity(this->motion_handler_.get_velocity());
  // stop the Obstacle
  this->motion_handler_.set_velocity(0, 0);
}
void Robot::HandleCollision(EntityType object_type, ArenaEntity * object) {
  switch (object_type) {
  case kObstacle:  // Subtract an available life
  case kRightWall:
  case kLeftWall:
  case kTopWall:
  case kBottomWall:
    std::cout << this->get_lives() << std::endl;
    this->set_lives(this->get_lives() - 1);  // lose a life
    break;
  case kBase:  // change base color
    object->set_color({ 0, 255, 0 });
    dynamic_cast <Base*> (object)->set_captured(true);
    break;
  case kEntity:
  case kRobot:
  case kUndefined:
  default: break;
  }

  this->motion_handler_.StopSpeed();  // stop the robot
  sensor_touch_->HandleCollision(object_type, object);
}

void Robot::IncreaseSpeed() {
  motion_handler_.IncreaseSpeed();
}
void Robot::DecreaseSpeed() {
  motion_handler_.DecreaseSpeed();
}
void Robot::TurnRight() {
  motion_handler_.TurnRight();
}
void Robot::TurnLeft() {
  motion_handler_.TurnLeft();
}

NAMESPACE_END(csci3081);
