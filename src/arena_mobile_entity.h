/**
 * @file arena_mobile_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_MOBILE_ENTITY_H_
#define SRC_ARENA_MOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>

#include "src/arena_entity.h"
#include "src/common.h"
#include "src/sensor_touch.h"
#include "src/wheel_velocity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A mobile entity in the Arena, capable of updating its own position
 * and/or velocity when asked by the simulation.
 *
 * All mobile entities must have a heading angle so that their orientation can
 * be properly drawn by the GraphicsArenaViewer.
 *
 * Since this is also a base class, many of its methods are intuitively
 * `virtual`.
 */
class ArenaMobileEntity : public ArenaEntity {
 public:
  /**
   * @brief ArenaMobileEntity's constructor.
   */

  ArenaMobileEntity()
    : ArenaEntity(),
    speed_(0),
    sensor_touch_(new SensorTouch),
    default_velocity_(WheelVelocity(2.0, 2.0)),
    last_velocity_(WheelVelocity(0.0, 0.0)) {
        set_mobility(true);
  }
  ArenaMobileEntity(const ArenaMobileEntity& other) = delete;
  ArenaMobileEntity& operator=(const ArenaMobileEntity& other) = delete;


  virtual double get_speed() { return speed_; }
  virtual void set_speed(double sp) { speed_ = sp; }

  /**
   * @brief called when mobile entity is overlapping with another item
   */
  virtual void HandleCollision(__unused EntityType object_type,
                               __unused ArenaEntity * object = NULL) {}

  /**
   * @brief Call when user unpauses or starts game to get mobile
   * entities moving again (if they were before).
   *
   * @TODO: implement this method just here rather than in both
   * obstacle and robot classes
   */
  virtual void ResumeSpeed() {}

  /**
   * @brief Call when user pauses to save last velocity and stop
   * any mobile entities.
   *
   * @TODO: implement this method just here rather than in both
   * obstacle and robot classes
   */
  virtual void PauseSpeed() {}

  bool get_game_started() {
    return game_started_;
  }

  void set_game_started(bool started) {
    game_started_ = started;
  }

  WheelVelocity get_default_velocity() {
    return default_velocity_;
  }

  void set_default_velocity(WheelVelocity wheel_vel) {
    default_velocity_ = wheel_vel;
  }

  WheelVelocity get_last_velocity() {
    return last_velocity_;
  }

  void set_last_velocity(WheelVelocity wheel_vel) {
    last_velocity_ = wheel_vel;
  }

  /**
   * @brief Get a pointer to the ArenaMobileEntity's touch sensor.
  */
  SensorTouch * get_touch_sensor() { return sensor_touch_; }

 private:
  double speed_;

 protected:
  // Using protected allows for direct access to sensor within entity.
  // It was awkward to have get_touch_sensor()->get_output() .
  SensorTouch * sensor_touch_;
  // is false until user hits start game button
  bool game_started_{false};
  // velocity of an entity in its natural starting state
  WheelVelocity default_velocity_;
  // the last velocity an entity had (save on pauses)
  WheelVelocity last_velocity_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_MOBILE_ENTITY_H_
