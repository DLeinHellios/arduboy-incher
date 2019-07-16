#ifndef MENU_H
#define MENU_H

// Contains functions for menu, info, and game over screens


// === Intro Animation ===
void startIntro() {
    introWait = 0;
    introFace = random(3);
}


void updateIntro() {
    if(introWait > INTRO_DELAY) {
        introWait = 0;

        // Update Frame
        introGoalFrame++;
        if(introCount) {
            introFaceFrame++;
            introCount = 0;
        } else {
            introCount++;
        }

        // Limit frames
        if(introFaceFrame > 1) {
            introFaceFrame = 0;
        }
        if(introGoalFrame > 2) {
            introGoalFrame = 0;
        }

    } else {introWait++;}
}


void drawIntro() {
    sprites.drawOverwrite(14,40,lgPlayer,introFaceFrame);
    switch(introFace) {
        case 0:
            sprites.drawOverwrite(95,40,lgFace0,introFaceFrame);
            break;
        case 1:
            sprites.drawOverwrite(95,40,lgFace1,introFaceFrame);
            break;
        case 2:
            sprites.drawOverwrite(95,40,lgFace2,introFaceFrame);
            break;
        case 3:
            sprites.drawOverwrite(95,40,lgGoal,introGoalFrame);
            break;
    }
}


// === Menu Functions ===

void menuInput() {
    arduboy.pollButtons();
    if(arduboy.justPressed(A_BUTTON)) {
        menuWait = 0;
        menuState = 1;
        introWait = 0;
    }
}


void drawMenu() {
    sprites.drawSelfMasked(9,10,title,0);
    sprites.drawSelfMasked(43,40,pressA,0);
    drawIntro();
}


void infoInput() {
    arduboy.pollButtons();
    if(arduboy.justPressed(A_BUTTON) && menuWait > MENU_DELAY) {
        menuWait = 0;
        startGame();
    }
}


void drawInfo() {
    arduboy.drawSlowXYBitmap(0,0,instructions,128,52);
    sprites.drawOverwrite(89,23,lgBomb,introFaceFrame);
    sprites.drawOverwrite(108,24,lgFace0,introFaceFrame);
    sprites.drawOverwrite(87,41,lgFace1,introFaceFrame);
    sprites.drawOverwrite(108,42,lgFace2,introFaceFrame);
    sprites.drawOverwrite(66,24,lgGoal,introGoalFrame);
    if(menuWait > MENU_DELAY) {
        sprites.drawOverwrite(35,46,pressA,0);
    }
}


void updateMenu() {
    menuWait++;
    updateIntro();
}


// =========================

void menuFrame() {
    // Conducts one frame of main menu
    switch(menuState) {
        case 0:
            menuInput();
            updateMenu();
            drawMenu();
            break;
        case 1:
            infoInput();
            updateMenu();
            drawInfo();
            break;
    }
}


// === Game Over Functions ===

void endInput() {
    arduboy.pollButtons();
    if(arduboy.justPressed(A_BUTTON)) {
        menuWait = 0;
        menuState = 0;
        gameState = 0;
        startIntro();
    }
}


void endUpdate() {
    if(menuWait > 6) {
        gameoverFrame++;
        if(gameoverFrame > 3) {
            gameoverFrame = 0;
        }
        menuWait = 0;
    }
    menuWait++;
}


void drawEnd() {
    sprites.drawSelfMasked(7,4,gameover,gameoverFrame);
    if(stage == 1) {
        sprites.drawOverwrite(18,40,survived,0);
        sprites.drawOverwrite(78,40,nums,1);
        sprites.drawOverwrite(86,40,text,0);
    } else if(stage < 10) {
        sprites.drawOverwrite(16,40,survived,0);
        sprites.drawOverwrite(76,40,nums,stage);
        sprites.drawOverwrite(84,40,text,0);
        sprites.drawOverwrite(109,40,plural,0);
    } else {
        sprites.drawOverwrite(14,40,survived,0);
        sprites.drawOverwrite(74,40,nums,stage/10);
        sprites.drawOverwrite(79,40,nums,stage-((stage/10)*10)); // Ones
        sprites.drawOverwrite(87,40,text,0);
        sprites.drawOverwrite(112,40,plural,0);
    }


}


// =========================

void endFrame() {
    endInput();
    endUpdate();
    drawEnd();
}


#endif
