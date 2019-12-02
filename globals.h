#ifndef GLOBALS_H
#define GLOBALS_H


#include <Arduboy2.h>
#include <Sprites.h>
#include "constants.h"


Arduboy2Base arduboy;
Sprites sprites;

// System
byte gameState = 0; // Main app state
byte menuState = 0; // Menu page state

// Animation
int menuWait = 0; // Reserved for timing delays in input
byte gameoverFrame = 0; // Frame for game over animation
byte faceMoveWait = 0; // Holds frame timing for face move delay
int faceAnimateWait = 0; // Wait to change face animation
int bombAnimateWait = 0; // Wait to change bomb animation
byte deathWait = 0; // Wait for death animation
byte floorWait = 0; // Wait for level-up animation
byte startWait = 0; // Wait for floor start animation to complete
byte goalFrame = 0; // Current frame of goal animation
byte goalWait = 0; // Duration between goal animation frame changes

// Flags
bool playerDead; // Player is currently dead
bool playerLevel; // Player is currently waiting for next floor
bool playerStarting; // Player is currently starting next stage
bool playerTurn; // Currently the players turn
bool goalLocked; // True until key is collected
bool showHazards; // Used to hide hazards for animation
bool showPlayer; // User to hide players for animation

// Player
byte stage = 0; // Successfully completed floors
byte lives = BASE_LIVES; // Current worms available
byte playerX = 0; // Player worm x-position
byte playerY = 0; // Player worm y-position
byte playerSpriteFrame; // Current player sprite frame
byte playerDeathFrame; // Current player death animation frame
byte playerLevelFrame; // Current player level-up animation frame

// Hazards
byte blocksX[MAX_BLOCKS]; // Blocks x-position
byte blocksY[MAX_BLOCKS]; // Blocks y-position
byte nBlocks = 0; // Number of currently active blocks (counted)

byte bombsX[MAX_BOMBS]; // Bombs x-position
byte bombsY[MAX_BOMBS]; // Bombs y-position
bool bombsLive[MAX_BOMBS] = {0}; // Are bombs active?
byte bombsType[MAX_BOMBS]; // Sets bomb wick side
byte bombsFrame[MAX_BOMBS]; // Sets bomb sprite frame
byte nBombs = MAX_BOMBS; // Number of bombs to spawn (set by difficulty)
byte nBombSpawns; // Number of bomb spawns in map

byte facesX[MAX_FACES];
byte facesY[MAX_FACES];
byte facesType[MAX_FACES]; // Designate variety of face sprite
byte facesFrame[MAX_FACES]; // Which frame of face is drawn
bool facesLive[MAX_FACES] = {0}; // Alive flags
bool facesMoved[MAX_FACES] = {0}; // Has moved flags
byte faceCounter = 0; // Counts frames between face movemement
byte nFaces = MAX_FACES; // Number of faces to spawn (set by difficulty)
byte nFaceSpawns; // Number of face spawns on map
byte faceAttack = 99; // Chance of adjacent face attacking

// Difficulty
byte difficultyFaces[10] = {1,1,2,2,2,3,3,3,3,3}; // Number of faces in first 10 floors
byte difficultyBombs[10] = {2,4,3,4,5,1,2,3,4,5}; // Number of faces in first 10 floors
byte difficultyAttack[10] = {90,95,80,85,90,70,75,80,85,90}; // Chance of adjacent face attacking, first 10 floors

// Stage
byte nMap; // Current stage map
byte goalX; // Portal x-position
byte goalY; // Portal y-position
byte keyX; // Key x-position
byte keyY; // Key y-position
byte nKeySpawns; // Number of key spawns on map
byte nPlayerSpawns; // Number of player/stairs spawns on map

// Menu Animation
byte introWait = 0; // Counts intro timing
byte introCount = 0; // Counts to halve face and worm animation
byte introFaceFrame = 0; // Tracks frame of title and info animation
byte introGoalFrame = 0; // Frame of goal on info screen
byte introFace = 3; // Face that appears on title screen - randoms after game over

#endif
