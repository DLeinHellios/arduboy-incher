// Incher - Worm Guiding Simulator for the Arduboy Game System
// Code by Dial
// Art by Schuss

#include "constants.h"
#include "globals.h"
#include "game.h"
#include "menu.h"


void setup() { // Runs once at start
    arduboy.begin();
    arduboy.setFrameRate(GAME_FPS);
}


void loop() { // Main Loop
    if(!arduboy.nextFrame()) {return;}
    arduboy.clear();

    switch(gameState) {
        case 0:
            menuFrame();
            break;

        case 1:
            gameFrame();
            break;

        case 2:
            endFrame();
            break;
    }
    arduboy.display();
}
