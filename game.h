#ifndef GAME_H
#define GAME_H


#include "tilemaps.h"
#include "bitmaps.h"


// === Game Functions ===
void clearMap() {
    // Removes all items from stage map

    // Blocks move offscreen
    nBlocks = 0;
    for(byte i = 0; i < MAX_BLOCKS; i++) {
        blocksX[i] = MAX_X + 2;
    }

    // Clear Bombs
    for(byte i = 0; i < MAX_BOMBS; i++) {
        bombsLive[i] = false;
    }

    // Clear Faces
    for(byte i = 0; i < MAX_FACES; i++) {
        facesLive[i] = false;
    }
}


void setBlock(byte x, byte y) {
    // Sets one block at the indicated x,y coords
    for(byte i = 0; i < MAX_BLOCKS; i++) {
        if(blocksX[i] == MAX_X + 2) {
            blocksX[i] = x;
            blocksY[i] = y;
            nBlocks++;
            break;
        }
    }
}


void randomizeSpawns(byte xPos[MAX_SPAWN_PLAYER], byte yPos[MAX_SPAWN_PLAYER]) {
    // Sets player and goal positions

    // Position
    byte player = random(nPlayerSpawns);
        playerX = xPos[player];
        playerY = yPos[player];

    byte goal = random(nPlayerSpawns);
    while(goal == player) {
        goal = random(nPlayerSpawns);
    }
    goalX = xPos[goal];
    goalY = yPos[goal];

    // Player sprite
    if(goalX == playerX) {
        playerSpriteFrame = 4;
    } else if(goalX > playerX) {
        playerSpriteFrame = 0;
    }   else {
        playerSpriteFrame = 1;
    }
}


void randomizeKey(byte xPos[MAX_SPAWN_KEY], byte yPos[MAX_SPAWN_KEY]) {
    // Spawns key in random location
    byte posIndx = random(nKeySpawns);
    keyX = xPos[posIndx];
    keyY = yPos[posIndx];
}


void setBomb(byte x, byte y) {
    // Sets one bomb at specified coords
    for(byte i = 0; i < MAX_BOMBS; i++) {
        if(!bombsLive[i]) {
            bombsX[i] = x;
            bombsY[i] = y;
            bombsType[i] = random(2);
            bombsFrame[i] = random(2);
            bombsLive[i] = true;
            break;
        }
    }
}


void randomizeBombs(byte xPos[MAX_SPAWN_BOMBS], byte yPos[MAX_SPAWN_BOMBS]) {
    // Get available positions
    byte validPositions[MAX_SPAWN_BOMBS] = {0};
    for(byte b=0; b < nBombSpawns; b++) {
        validPositions[b] = 1;
    }

    // Set bombs
    for(byte bomb=0; bomb < nBombs; bomb++) {
        byte posIndx = random(nBombs);
        while(validPositions[posIndx] == 0) {
            if(posIndx < nBombSpawns - 1) {
                posIndx++;
            } else {
                posIndx = 0;
            }
        }
        setBomb(xPos[posIndx], yPos[posIndx]);
        validPositions[posIndx] = 0;
    }
}


void setFace(byte x, byte y) {
    // Sets one face at specified coords
    for(byte i = 0; i < MAX_FACES; i++) {
        if(!facesLive[i]) {
            facesX[i] = x;
            facesY[i] = y;
            facesType[i] = random(3);
            facesFrame[i] = random(2);
            facesLive[i] = true;
            break;
        }
    }
}


void randomizeFaces(byte xPos[MAX_SPAWN_FACES], byte yPos[MAX_SPAWN_FACES]) {
    // Get available positions
    byte validPositions[MAX_SPAWN_FACES] = {0};
    for(byte b=0; b < nFaceSpawns; b++) {
        validPositions[b] = 1;
    }

    // Set faces
    for(byte face=0; face < nFaces; face++) {
        byte posIndx = random(MAX_SPAWN_FACES);
        while(validPositions[posIndx] == 0) {
            if(posIndx < MAX_SPAWN_FACES - 1) {
                posIndx++;
            } else {
                posIndx = 0;
            }
        }
        setFace(xPos[posIndx], yPos[posIndx]);
        validPositions[posIndx] = 0;
    }
}


byte readMap(byte nMap, byte nTile) {
    // Returns a tile from a map
    if (nMap == 0) {
        return pgm_read_byte(&map0[nTile]);
    } else if (nMap == 1) {
        return pgm_read_byte(&map1[nTile]);
    } else if (nMap == 2) {
        return pgm_read_byte(&map2[nTile]);
    } else if (nMap == 3) {
        return pgm_read_byte(&map3[nTile]);
    } else if (nMap == 4) {
        return pgm_read_byte(&map4[nTile]);
    }
}


void setFloorMap(byte nMap) {
    // Sets up map elements for new floor
    clearMap();
    // Declare placeholders
    nBombSpawns = 0;
    byte posBombsX[MAX_SPAWN_BOMBS] = {0};
    byte posBombsY[MAX_SPAWN_BOMBS] = {0};

    nFaceSpawns = 0;
    byte posFacesX[MAX_SPAWN_FACES] = {0};
    byte posFacesY[MAX_SPAWN_FACES] = {0};

    nKeySpawns = 0;
    byte posKeyX[MAX_SPAWN_KEY] = {0};
    byte posKeyY[MAX_SPAWN_KEY] = {0};

    nPlayerSpawns = 0;
    byte posSpawnX[MAX_SPAWN_PLAYER] = {0};
    byte posSpawnY[MAX_SPAWN_PLAYER] = {0};

    byte tileType;
    byte x = 0;
    byte y = 0;

    // Set static blocks and populate possible random tile arrays
    for(byte t = 0; t < 105; t++) {
        tileType = readMap(nMap, t);

        switch(tileType) {
            case 1: // Blocks
                setBlock(x,y);
                break;

            case 2: // Bombs
                if(nBombSpawns < MAX_SPAWN_BOMBS) {
                    posBombsX[nBombSpawns] = x;
                    posBombsY[nBombSpawns] = y;
                    nBombSpawns++;
                }
                break;

            case 3: // Faces
                if(nFaceSpawns < MAX_SPAWN_FACES) {
                    posFacesX[nFaceSpawns] = x;
                    posFacesY[nFaceSpawns] = y;
                    nFaceSpawns++;
                }
                break;

            case 4: // Key
                if(nKeySpawns < MAX_SPAWN_KEY) {
                    posKeyX[nKeySpawns] = x;
                    posKeyY[nKeySpawns] = y;
                    nKeySpawns++;
                }
                break;

            case 5: // Goal/Player
                if(nPlayerSpawns < MAX_SPAWN_PLAYER) {
                    posSpawnX[nPlayerSpawns] = x;
                    posSpawnY[nPlayerSpawns] = y;
                    nPlayerSpawns++;
                }
                break;
        }
        // Increment x/y coords
        x++;
        if(x > MAX_X){
            x = 0;
            y++;
        }
    }
    // Place items
    randomizeSpawns(posSpawnX, posSpawnY);
    randomizeKey(posKeyX, posKeyY);
    randomizeBombs(posBombsX, posBombsY);
    randomizeFaces(posFacesX,posFacesY);
}


void setFloorVars(){
    // Sets basic state variables before each stage
    playerTurn = true;
    goalLocked = true;
    showHazards = false;
    showPlayer = false;
    playerStarting = true;
    startWait = 0;
}


void setFloorDifficulty() {
    if(ENABLE_HARDMODE) {
        nFaces = MAX_FACES;
        nBombs = MAX_BOMBS;
        faceAttack = 100;
    } else {
        if(stage < 10) {
            nFaces = difficultyFaces[stage];
            nBombs = difficultyBombs[stage];
            faceAttack = difficultyAttack[stage] - 1;
        } else {
            nFaces = difficultyFaces[9];
            nBombs = difficultyBombs[9];
            faceAttack = difficultyAttack[9] - 1;
        }
    }
}


void setMapType() {
    // Selects next map type
    byte nextMap;
    if(ENABLE_LEVEL_SELECT) {
        nMap = SELECT_LEVEL;
    } else {
        do {
            nextMap = random(MAP_TYPES);
        } while(nMap == nextMap);
        nMap = nextMap;
    }
}


void setFloor() {
    // Handles new floor setup
    setFloorVars();
    setFloorDifficulty();
    setMapType();
    setFloorMap(nMap);
}


bool checkOccupiedBlocks(byte x, byte y){
    // Returns true if a block is on the specified tile
    bool occupied = false;

    for(byte i=0; i<nBlocks; i++) {
        if(blocksX[i] == x && blocksY[i] == y) {
            occupied = true;
        }
    }
    return occupied;
}


bool checkOccupiedHazards(byte x, byte y) {
    // Returns true if a hazard is occupying the specified tile
    bool occupied = false;

    // Faces
    if(!occupied) {
        for(byte i=0; i<nFaces; i++) {
            if(facesLive[i] && facesX[i] == x && facesY[i] == y) {
                occupied = true;
            }
        }
    }

    // Bombs
    if(!occupied) {
        for(byte i=0; i<nBombs; i++) {
            if(bombsLive[i] && bombsX[i] == x && bombsY[i] == y) {
                occupied = true;
            }
        }
    }

    return occupied;
}


void startGame() {
    // Begins new game
    arduboy.initRandomSeed(); // Seed RNG
    stage = 0;
    lives = BASE_LIVES;
    setFloor();
    gameState = 1;
}


// ---- Input ----
void moveUp() {
    playerY--;
    // Choose Sprite
    switch(playerSpriteFrame) {
        case 0:
            playerSpriteFrame = 2;
            break;
        case 1:
            playerSpriteFrame = 3;
            break;
        case 4:
            playerSpriteFrame = 2;
            break;
        default:
            playerSpriteFrame = 5;
            break;
    }
    playerTurn = false;
}


void moveDown() {
    playerY++;
    // Choose Sprite
    switch(playerSpriteFrame) {
        case 2:
            playerSpriteFrame = 0;
            break;
        case 3:
            playerSpriteFrame = 1;
            break;
        case 5:
            playerSpriteFrame = 1;
            break;
        default:
            playerSpriteFrame = 4;
            break;
    }
    playerTurn = false;
}


void moveLeft() {
    playerX--;
    playerSpriteFrame = 1;
    playerTurn = false;
}


void moveRight() {
    playerX++;
    playerSpriteFrame = 0;
    playerTurn = false;
}


bool checkGameOver() {
    // Ends game at 0 lives
    if(lives < 1) {
        gameState = 2;
        return true;
    } else {
        return false;
    }
}


void checkPlayerDeath() {
    // Check if standing on hazard
    if(checkOccupiedHazards(playerX, playerY)) {
        playerDead = true;
    }
}


void gameInput() {
    if(playerTurn && !playerDead && !playerLevel && !playerStarting) {
        arduboy.pollButtons();
        // Move up
        if(arduboy.justPressed(UP_BUTTON) && playerY > 0) {
            if(!checkOccupiedBlocks(playerX,playerY-1)) {
                moveUp();
                checkPlayerDeath();
            }
        }
        // Move down
        if(arduboy.justPressed(DOWN_BUTTON) && playerY < MAX_Y) {
            if(!checkOccupiedBlocks(playerX,playerY+1)) {
                moveDown();
                checkPlayerDeath();
            }
        }
        // Move right
        if(arduboy.justPressed(RIGHT_BUTTON) && playerX < MAX_X) {
            if(!checkOccupiedBlocks(playerX+1,playerY)) {
                moveRight();
                checkPlayerDeath();
            }
        }
        // Move left
        if(arduboy.justPressed(LEFT_BUTTON) && playerX > 0) {
            if(!checkOccupiedBlocks(playerX-1,playerY)) {
                moveLeft();
                checkPlayerDeath();
            }
        }
    }
}


// ---- Enemy AI ----
bool attackPlayer(byte face) {
    // Moves to attack adjacent player
    int distanceX = playerX - facesX[face];
    int distanceY = playerY - facesY[face];
    bool moved = false;

    if(abs(distanceX) < 2 && abs(distanceY) < 2) {
        moved = true;
        int roll = random(100);
        if(roll < faceAttack) {
            facesX[face] = playerX;
            facesY[face] = playerY;
            checkPlayerDeath();
        }
    }
    return moved;
}


bool validateMove(byte x, byte y) {
    if(x < 0 || x > MAX_X) {
        return false;
    }
    if(y < 0 || y > MAX_Y) {
        return false;
    }
    if(checkOccupiedBlocks(x,y)) {
        return false;
    }
    if(checkOccupiedHazards(x,y)) {
        return false;
    }
    if(x == keyX && y == keyY && goalLocked) {
        return false;
    }
    if(x == goalX && y == goalY) {
        return false;
    }

    return true;
}


void faceMove(byte face) {
    // Player is not adjacent, move randomly
    byte possibleX[9] = {0};
    byte possibleY[9] = {0};
    bool movePossible[9] = {0};

    // Populate adjacent spaces
    int c = 0; // Count tiles
    for(int x=-1; x<2; x++) {
        for(int y=-1; y<2; y++) {
            possibleX[c] = facesX[face] + x;
            possibleY[c] = facesY[face] + y;
            movePossible[c] = validateMove(possibleX[c],possibleY[c]);
            c++;
        }
    }

    // Move to a random valid position
    int roll = random(9);
        for(byte i=0; i<FACE_RETRY; i++) {
            if(movePossible[roll]) {
                facesX[face] = possibleX[roll];
                facesY[face] = possibleY[roll];
                break;
            } else {
                roll = random(9);
            }
        }
}


void faceAction(byte face) {
    if(faceCounter >= FACE_DELAY) {

        if(!attackPlayer(face)) {
            faceMove(face);
        }

        facesMoved[face] = true;
        faceCounter = 0;
    }
    faceCounter++;
}


void faceTurns() {
    bool endTurn = true;
    if(!playerTurn) {
        for(byte f = 0; f < nFaces; f++) {
            if(facesLive[f] && !facesMoved[f]) {
                faceAction(f);
                endTurn = false;
                break;
            }
        }
    }

    if(endTurn) {
        playerTurn = true;
        for(byte f = 0; f < nFaces; f++) {
            facesMoved[f] = false;
        }
    }
}


// ---- Update ----
void playerDeath() {
    // Handle player death timing
    if(playerDead && deathWait > DEATH_DELAY) {
        // Death
        deathWait = 0;
        lives--;
        playerDead = false;
        // Game over
        if(!checkGameOver()) {
            setFloor();
        }

    } else if(playerDead && deathWait > 10) {
        deathWait++;
        if(playerDead && deathWait > 21) {
            if(playerDeathFrame <= DEATH_FRAMES && (deathWait-21) % 3 == 0) {
                playerDeathFrame++;
            }

        } else if(playerDead && deathWait > 20) {
            showPlayer = false;
            playerDeathFrame = 0;

        } else {
            showHazards = false;
        }

    } else if(playerDead) {
        deathWait++;
    }
}


void playerLevelUp() {
    // Handle player floor increase timing
    if(playerLevel && floorWait > FLOOR_DELAY) {
        // Level Up
        floorWait = 0;
        playerLevel = false;
        stage++;
        if(stage > 99) {
            stage = 99;
        }
        setFloor();

    } else if(playerLevel && floorWait > 10) {
        floorWait++;
        if(playerLevel && floorWait > 21) {
            if(playerLevelFrame <= FLOOR_FRAMES && (floorWait-21) % 3 == 0) {
                playerLevelFrame++;
            }

        } else if(playerLevel && floorWait > 20) {
            showPlayer = false;
            playerLevelFrame = 0;

        } else {
            showHazards = false;
        }

    } else if(playerLevel) {
        floorWait++;
    }
}


void floorStartup() {
    // Manages floor starting animation
    if(playerStarting) {
        if(startWait > FLOOR_START_DELAY) {
            showHazards = true;
            playerStarting = false;
        } else if(startWait > (FLOOR_FRAMES-1) * 4) {
            showPlayer = true;
            startWait++;
        } else {
            startWait++;
        }
    }
}


void bombAnimate() {
    // Flips bomb frames
    if(bombAnimateWait > BOMB_SPEED) {
        for(int b=0; b<nBombs; b++) {
            if(bombsFrame[b]) {
                bombsFrame[b] = 0;
            } else {
                bombsFrame[b] = 1;
            }
        }
        bombAnimateWait = 0;
    }
    bombAnimateWait++;
}


void faceAnimate() {
    // Flips face frames
    if(faceAnimateWait > FACE_SPEED) {
        int f = random(nFaces);
        if(facesFrame[f]) {
            facesFrame[f] = 0;
        } else {
            facesFrame[f] = 1;
        }
        faceAnimateWait = random(-30/nFaces,0);
    }
    faceAnimateWait++;
}


void goalAnimate() {
    // Conducts goal portal animation
    if(goalWait > GOAL_DELAY) {
        goalWait = 0;
        goalFrame++;
        if(goalFrame >= GOAL_FRAMES) {
            goalFrame = 0;
        }
    } else {
        goalWait++;
    }
}


void updateGame() {
    // Update each frame
    floorStartup();
    playerDeath();
    playerLevelUp();
    if(ANIMATE_BOARD) {
        bombAnimate();
        faceAnimate();
        goalAnimate();
    }

    // Advance Stage
    if(!goalLocked && playerX == goalX && playerY == goalY) {
        playerLevel = true;

    // Unlock Goal
    } else if(goalLocked && playerX == keyX && playerY == keyY) {
        goalLocked = false;

    // Move Faces
    } else {
        faceTurns();
    }
}


// ---- Drawing ----
void drawGrid() {
        for(byte x=0; x<=MAX_X+1; x++) {
            for(byte y=0; y<=MAX_Y+1; y++) {
                arduboy.drawPixel((x*8)+OFFSET_X,y*8,WHITE);
            }
    }
}


void drawFloorShade() {
    // Draws shade for floor start animation
    if(playerStarting) {
        if(startWait > 30) {
            arduboy.fillRect(0,startWait - 30,127,63,BLACK);
        } else {
            arduboy.fillRect(0,0,127,63,BLACK);
        }
    }
}


void drawBlocks() {
    for(byte i=0; i < nBlocks; i++) {
        sprites.drawOverwrite(OFFSET_X+(blocksX[i]*8),blocksY[i]*8,block,0);
    }
}


void drawBombs() {
    if(showHazards) {
        for(byte i=0; i < nBombs; i++) {
            if(bombsLive[i]) {
                if(bombsType[i] == 0) {
                    sprites.drawOverwrite(OFFSET_X+(bombsX[i]*8),bombsY[i]*8,bomb0,bombsFrame[i]);
                } else {
                    sprites.drawOverwrite(OFFSET_X+(bombsX[i]*8),bombsY[i]*8,bomb1,bombsFrame[i]);
                }
            }
        }
    }
}


void drawFaces() {
    if(showHazards) {
        for(byte i=0; i<nFaces; i++) {
            if(facesLive[i]) {
                if(facesType[i] == 0) {
                    sprites.drawOverwrite(OFFSET_X+(facesX[i]*8),facesY[i]*8,face0,facesFrame[i]);
                } else if(facesType[i] == 1) {
                    sprites.drawOverwrite(OFFSET_X+(facesX[i]*8),facesY[i]*8,face1,facesFrame[i]);
                } else if(facesType[i] == 2) {
                    sprites.drawOverwrite(OFFSET_X+(facesX[i]*8),facesY[i]*8,face2,facesFrame[i]);
                }
            }
        }
    }
}


void drawPlayer() {
    if(showPlayer) {
        sprites.drawOverwrite((playerX*8)+OFFSET_X,playerY*8,player,playerSpriteFrame);

    } else if(playerDead && playerDeathFrame < DEATH_FRAMES) {
        sprites.drawOverwrite((playerX*8)+OFFSET_X,playerY*8,deathAnimation,playerDeathFrame);

    } else if(playerLevel && playerLevelFrame < FLOOR_FRAMES) {
        sprites.drawOverwrite((playerX*8)+OFFSET_X,playerY*8,levelAnimation,playerLevelFrame);

    } else if(playerStarting) {
        sprites.drawOverwrite((playerX*8)+OFFSET_X,playerY*8,levelAnimation,(FLOOR_FRAMES - 1)-(startWait/4));
    }
}


void drawMap() {
    // Goal and Key
    if(!playerLevel) {
        if(goalLocked) {
            sprites.drawOverwrite((goalX*8)+OFFSET_X,goalY*8,lock,0);
            sprites.drawOverwrite((keyX*8)+OFFSET_X,keyY*8,lock,1); // Stage key
        } else {
            sprites.drawOverwrite((goalX*8)+OFFSET_X,goalY*8,goal,goalFrame);
            sprites.drawOverwrite(OFFSET_X+56,57,lock,2); // UI Key
        }
    }
    // Blocks
    drawBlocks();
}


void drawUI() {
    // Stage
    sprites.drawOverwrite(OFFSET_X + 3,57,text,0);
    sprites.drawOverwrite(OFFSET_X + 28,57,equals,0);
    if(stage > 9) {
        sprites.drawOverwrite(OFFSET_X+34,57,nums,stage/10); // Tens
        sprites.drawOverwrite(OFFSET_X+39,57,nums,stage-((stage/10)*10)); // Ones
    } else {
        sprites.drawOverwrite(OFFSET_X+34,57,nums,stage);
    }

    // Lives
    sprites.drawOverwrite(OFFSET_X+80,57,text,1);
    sprites.drawOverwrite(OFFSET_X + 108,57,equals,0);
    sprites.drawOverwrite(OFFSET_X+114,57,nums,lives-1);
}


void drawGame() {
    // Draw all game elements
    drawMap();
    drawFloorShade();
    drawBombs();
    drawPlayer();
    drawFaces();
    drawUI();
    drawGrid();
}


// =========================
void gameFrame() {
    // Conducts one frame while game is active
    gameInput();
    updateGame();
    drawGame();

}


#endif
