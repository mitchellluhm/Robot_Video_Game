/**
 * @file motion_handler_robot.cc
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_robot.h"
#include "src/motion_behavior_differential.h"
#include <iostream> /* debugging */

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// @TODO add clamped

double MotionHandlerRobot::GetNewSpeedByLimit(double init_speed, double factor,
                                            double limit, bool limit_is_max) {
  if (limit_is_max) {
    if (init_speed + factor > limit)
      return limit;
    else
      return init_speed + factor;
  } else {
    if (init_speed - factor < limit)
      return limit;
    else
      return init_speed - factor;
  }
}

void MotionHandlerRobot::StopSpeed() {
  set_velocity(0, 0);
}

void MotionHandlerRobot::TurnLeft() {
  // decrease left wheel, increase right wheel
  // need to make sure speeds stay in limits
  double wv_left = get_velocity().left;
  double wv_right = get_velocity().right;
  double ang_delta = get_angle_delta();
  double dec_left, inc_right;

  dec_left = GetNewSpeedByLimit(wv_left, ang_delta, 0, false);
  inc_right = GetNewSpeedByLimit(wv_right, ang_delta, 10, true);

  set_velocity(dec_left, inc_right);
}

void MotionHandlerRobot::TurnRight() {
  // increase left wheel, decrease right wheel
  // need to make sure speeds stay in limits
  double wv_left = get_velocity().left;
  double wv_right = get_velocity().right;
  double ang_delta = get_angle_delta();
  double inc_left, dec_right;

  inc_left = GetNewSpeedByLimit(wv_left, ang_delta, 10, true);
  dec_right = GetNewSpeedByLimit(wv_right, ang_delta, 0, false);

  set_velocity(inc_left, dec_right);
}

void MotionHandlerRobot::IncreaseSpeed() {
  // check if IncreaseSpeed would put past the limit
  double wv_left = get_velocity().left;
  double wv_right = get_velocity().right;
  double wv_delta = get_speed_delta();
  double inc_left, inc_right;

  inc_left = GetNewSpeedByLimit(wv_left, wv_delta, 10, true);
  inc_right = GetNewSpeedByLimit(wv_right, wv_delta, 10, true);

  set_velocity(inc_left, inc_right);
}

void MotionHandlerRobot::DecreaseSpeed() {
  // check if DecreaseSpeed would go negative
  double wv_left = get_velocity().left;
  double wv_right = get_velocity().right;
  double wv_delta = get_speed_delta();
  double dec_left, dec_right;

  dec_left = GetNewSpeedByLimit(wv_left, wv_delta, 0, false);
  dec_right = GetNewSpeedByLimit(wv_right, wv_delta, 0, false);

  set_velocity(dec_left, dec_right);
}

void MotionHandlerRobot::UpdateVelocity() {
  if (entity_->get_touch_sensor()->get_output()) {
    entity_->RelativeChangeHeading(+180);
  }
}

double MotionHandlerRobot::clamp_vel(double vel) {
  // @TODO: don't go backwards
  double clamped = 0.0;
  if (vel > 0) {
    clamped = (vel > get_max_speed()) ?
              get_max_speed():
              vel;
  } else {
    clamped = (vel < -get_max_speed()) ?
              -get_max_speed():
              vel;
  }
  return clamped;
} /* clamp_vel() */

NAMESPACE_END(csci3081);
