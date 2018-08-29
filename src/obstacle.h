/**
 * @file obstacle.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_OBSTACLE_H_
#define SRC_OBSTACLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/arena_mobile_entity.h"
#include "src/common.h"
#include "src/motion_handler.h"
#include "src/motion_behavior_differential.h"
#include "src/entity_type.h"
#include "src/pose.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing an immobile obstacle within the Arena.
 *
 * Since obstacles are immobile, the Obstacle class is very simple.
 */
class Obstacle : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor.
   */
  Obstacle();

  /**
   * @brief Get the name of the Obstacle for visualization purposes, and to
   * aid in debugging.
   */
  std::string get_name() const override {
    return "Obstacle" + std::to_string(get_id());
  }


  /**
   * @brief Update the Obstacle's position and velocity after the specified
   * duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
   * @brief Get the Obstacle moving at a default speed
   */
  void StartSpeed();

  /**
   * @brief Handles the collision by setting the sensor to activated.
   */
  void HandleCollision(EntityType object_type,
                       ArenaEntity * object = NULL) override;

  /**
   * @brief Upon collision, obstacle should move in a reverse arc trajectory
   * for a fixed amount of time.
   */
  void ReverseArc();

  /**
   * @brief After reversing in arc trajectory, straighten the velocity
   */
  void EndReverseArc();

  /**
   * @brief Called when game starts of user unpauses to get obstacles moving
   * at their last speed.
   */
  void ResumeSpeed() override;

  /**
   * @brief Called when user pauses. Saves the last velocity for use later in
   * ResumeSpeed()'s future call.
   */
  void PauseSpeed() override;

 private:
  MotionHandler motion_handler_;
  MotionBehaviorDifferential motion_behavior_;
  // used as a state machine when obstacle is in reverse arc motion
  bool reverse_state_{false};
  // ticker counter for how long obstacle has been in reverse arc motion
  unsigned int reverse_state_tick_{0};
  // used to know which direction the obstacle is moving
  bool moving_forward_{true};
};

NAMESPACE_END(csci3081);

#endif  // SRC_OBSTACLE_H_
