#!/usr/bin/env python3
# Converts map data in .csv to byte array for Incher

# DIRECTIONS: Create map .csv -> run convert script -> enter filename ->
#   copy contents of exported .h into tilemaps.h -> add selection logic in readMap() in game.h

################################
#   When constructing .csv:    #
#   0 = Open tile              #
#   1 = Block                  #
#   2 = Bomb Spawn             #
#   3 = Face Spawn             #
#   4 = Key Spawn              #
#   5 = Player/Stairs Spawn    #
################################

import sys


def init_conversion():
    print("############################################")
    print("#         Incher Map Converter             #")
    print("#     Converts .csv to Incher map code     #")
    print("############################################")
    print("#           Map Requirements:              #")
    print("#            Blocks <= 50                  #")
    print("#           2 <= Spawns <= 4               #")
    print("#           5 <= Bombs <= 10               #")
    print("#            3 <= Faces <= 5               #")
    print("#            1 <= Keys <=  4               #")
    print("############################################")
    print("#              Tile Values:                #")
    print("#                0 = Open                  #")
    print("#                1 = Block                 #")
    print("#                2 = Bomb                  #")
    print("#                3 = Face                  #")
    print("#                4 = Key                   #")
    print("#                5 = Spawn                 #")
    print("############################################\n")
    fileName = input("Enter import file name (w/o '.csv'): ")
    print()
    return fileName


def read_map(fileName):
    mapTiles = []
    try:
        with open(fileName + ".csv") as mapData:
            for line in mapData:
                rawDat = line.split(",")
                rawDat[-1] = rawDat[-1][0]
                mapTiles += rawDat

        return mapTiles

    except:
        print("\nERROR: Invalid read file!\n")
        sys.exit();


def validate_map(mapTiles, fileName):
    error = False

    # Template
    maxBlocks = 50
    minBombs = 5
    maxBombs = 10
    minFaces = 3
    maxFaces = 5
    maxKeys = 4
    minSpawns = 2
    maxSpawns = 4

    # Counters
    nBlocks = 0
    nBombs = 0
    nFaces = 0
    nKeys = 0
    nSpawns = 0

    # Count Tiles
    for tile in mapTiles:
        if tile == '1':
            nBlocks += 1
        elif tile == '2':
            nBombs += 1
        elif tile == '3':
            nFaces += 1
        elif tile == '4':
            nKeys += 1
        elif tile == '5':
            nSpawns += 1

    # Print Info
    print("====== Map Info ======")
    print("Name = " + fileName)
    print("Blocks = " + str(nBlocks) + "/" + str(maxBlocks))
    print("Bombs = " + str(nBombs) + "/" + str(maxBombs))
    print("Faces = " + str(nFaces) + "/" + str(maxFaces))
    print("Key = " + str(nKeys) + "/" + str(maxKeys))
    print("Spawns = " + str(nSpawns) + "/" + str(maxSpawns))
    print("======================")

    # Print warnings
    if nBlocks > maxBlocks:
        print("WARNING: Blocks exceed maximum!")
        error = True
    if nBombs > maxBombs:
        print("WARNING: Bombs exceed maximum!")
        error = True
    if nBombs < minBombs:
        print("WARNING: Bombs below minimum!")
        error = True
    if nFaces > maxFaces:
        print("WARNING: Faces exceed maximum!")
        error = True
    if nFaces < minFaces:
        print("WARNING: Faces below minimum!")
        error = True
    if nKeys > maxKeys:
        print("WARNING: Key spawns exceed maximum!")
        error = True
    if nKeys < 1:
        print("WARNING: No Key Spawn!")
        error = True
    if nSpawns > maxSpawns:
        print("WARNING: Player/Stairs spawns above maximum!")
        error = True
    if nSpawns < minSpawns:
        print("WARNING: Player/Stairs spawns below minimum!")
        error = True

    return error


def write_map(mapTiles, fileName, error):
    try:
        convertFile = open(fileName + ".h", "w")
        convertFile.write("const uint8_t PROGMEM " + fileName + "[] =\n{\n")

        byteLine = []
        widthCounter = 0
        for tile in mapTiles:
            if widthCounter < 5:
                byteLine.append(tile)
                widthCounter += 1
            else:
                convertFile.write("    " + ",".join(byteLine) + ",\n")
                byteLine = [tile]
                widthCounter = 1

        convertFile.write("    " + ",".join(byteLine) + ",\n")
        convertFile.write("};")
        convertFile.close()

        if not error:
            print("No errors found!")
        print("======================")
        print("SUCCESS: Converted file written as " + fileName + ".h")
        if error:
            print("WARNING: Map data may contain errors!")
        print()

    except:
        print("ERROR: Cannot open write file!\n")


def main():
    fileName = init_conversion();
    mapTiles = read_map(fileName)
    error = validate_map(mapTiles, fileName)
    write_map(mapTiles, fileName, error)


#=========================================
if __name__ == "__main__":
    main()
