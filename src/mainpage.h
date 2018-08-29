/**
 * @file mainpage.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

/*! \mainpage Documentation Iteration 1 : Robot Video Game
 *
 * \section intro_sec Introduction
 *
 * This program is a video game. When the program is run ./arenaviewer
 * there user must click "Start Game" button in the top left corner to start the
 * game. Once the game is started, obstacles move by default and the user can
 * control the robot using the arrow keys (see controls).
 *
 * The objective is for the robot to capture each base (by touching it), before
 * the robot loses its live (by colliding into obstacles). The robot has 9
 * lives.
 *
 * \section Controls
 *
 * Up : Increase robot's speed
 *
 * Down : Decrease robot's speed
 *
 * Left : Turn robot to the left
 *
 * Right : Turn robot to the right
 *
 * User can click menu buttons with the mouse on top left corner to
 * start, pause, or resume the game.
 *
 * \section Code Structure
 *
 * The base of the code relies on the GraphicsArenaViewer (GUI) and the Arena.
 * The Controller communicates between the GraphicsArenaViewer and the Arena.
 * The Arena houses entities (robot, obstacles, bases). The entities can either
 * be mobile (robot, and obstacle) or immobile (bases). The EntityFactory is
 * response for making these entities. General game parameter options are to be
 * specified in the params.h file.
 *
 * Please view the UML diagram located on github (iteration1/docs/UML_ITER_1.pdf)
 * for a visualization of the structure and relationships.
 *
 */

#endif  // SRC_MAINPAGE_H_
