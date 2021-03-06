#ifndef CONSTANTS_H
#define CONSTANTS_H


#define GAME_FPS 30 // Frames per second

#define ENABLE_LEVEL_SELECT 0 // Enables level select option
#define SELECT_LEVEL 0 // Select level # if level select | n < MAP_TYPES
#define MAP_TYPES 5 // Max number for random map selection | needs selection logic in readMap() and array in tilemaps.h
#define OFFSET_X 4 // Pixel offset for drawing game screen
#define MAX_X 14 // Number of horizonal tiles - 1
#define MAX_Y 6 // Number of vertical tiles - 1

#define ENABLE_HARDMODE 0 // Forces maximum difficulty
#define BASE_LIVES 3 // Starting player lives
#define FACE_RETRY 5 // Number of tries for a face to select a valid movement (high value = slowdown)
#define MAX_BLOCKS 50 // Max block tiles per floor
#define MAX_BOMBS 5 // Max bombs spawned per floor
#define MAX_FACES 3 // Max faces spawned per floor

#define MAX_SPAWN_BOMBS 10 // Number of possible bomb spawns max
#define MAX_SPAWN_FACES 5 // Number of possible face spawns
#define MAX_SPAWN_KEY 4 // Number of possible key spawns
#define MAX_SPAWN_PLAYER 4 // Max number of player/stairs spawns ( >2 )

#define ANIMATE_BOARD 1 // Toggle animated faces and bombs
#define FACE_DELAY 4 // Number of frames between face movement
#define FACE_SPEED 10 // Frames between animating faces
#define BOMB_SPEED 6 // Frames between animating bombs
#define DEATH_DELAY 50 // Number of frames to wait on death
#define DEATH_FRAMES 7 // Number of death animation frames
#define FLOOR_DELAY 50 // Number of frames to wait on level-up
#define FLOOR_FRAMES 8 // Number of level-up animation frames
#define GOAL_DELAY 3 // Number of frames to update goal animation
#define GOAL_FRAMES 3 // Number of frames in goal animation
#define FLOOR_START_DELAY 90 // Delay for start of board animation
#define MENU_DELAY 30 // Delay before 'Press A'
#define INTRO_DELAY 4 // Delay for intro animation timing


#endif
