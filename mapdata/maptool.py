#!/usr/bin/env python3
# maptool.py - Converts map data from .CSV to byte array for Incher

import sys, os


#----- Information -----
def print_help():
    '''Prints command list'''
    print("====== COMMAND LIST ======")
    print("QUIT - Exit program")
    print("HELP - Print this menu")
    print("FILE - Print CSV file guidelines")
    print("CONVERT <MAPNAME> - Converts CSV map to byte array")
    print("LIST - Lists CSV files in script directory")
    print("REMOVE - Removes all header files from program directory")
    print("==========================")




def print_file():
    '''Prints CSV file formatting instructions'''
    print("======= FILE GUIDE =======")
    print("CSV - Saved in same directory as maptool.py")
    print("Size - 15x7 cells (columns A-H, rows 1-7)")
    print("==========================")
    print("Tile Values - For CSV cells")
    print("  0 - Empty")
    print("  1 - Block")
    print("  2 - Bomb")
    print("  3 - Face")
    print("  4 - Key")
    print("  5 - Spawn/Goal")
    print("==========================")
    print("Tile Quantities - Minimum/Maximum")
    print("  0 <= Blocks <= 50")
    print("  2 <= Spawns <= 4")
    print("  5 <= Bombs <= 10")
    print("  3 <= Faces <= 5")
    print("  1 <= Keys <=  4")
    print("==========================")


def print_list():
    '''Prints all CSV files in program directory'''
    mapfiles = []
    for file in os.listdir():
        if file[-4:].lower() == ".csv":
            mapfiles.append(file)
    mapfiles.sort()

    print("======= MAP FILES =======")
    for map in mapfiles:
        print("  " + map)
    print("=========================")


def remove_headers():
    '''Removes all header files from program directory'''
    removed = False
    for file in os.listdir():
        if file[-2:] == ".h":
            os.remove(file)
            removed = True

    if removed:
        print("SUCCESS: All header files have been deleted")
    else:
        print("ERROR: No header files detected")


#----- Conversion -----
def read_map(filename):
    '''Accepts CSV file name, opens and prepares file for conversion'''
    mapdata = []
    with open(filename + ".csv") as mapfile:
        for line in mapfile:
            line = line.rstrip() # Remove linebreak
            mapline = line.split(",") # Split into list of tiles
            while '' in mapline: # Remove blank strings
                mapline.remove('')
            mapdata += mapline

    return mapdata


def validate_size(mapdata):
    '''Validates number of tiles in map file returns true if valid'''
    if len(mapdata) != 105:
        return False

    else:
        return True


def validate_tiles(mapdata, filename):
    '''Validates tile content in map data, returns true if valid'''
    # Valid tile counts
    validBlocks = [0,50]
    validBombs = [5,10]
    validFaces = [3,5]
    validKeys = [1,4]
    validSpawns = [2,4]

    # Count tiles
    tileCounts = [0,0,0,0,0,0]
    for tile in mapdata:
        if tile == "0":   # Empty
            tileCounts[0] += 1
        elif tile == '1': # Block
            tileCounts[1] += 1
        elif tile == '2': # Bomb
            tileCounts[2] += 1
        elif tile == '3': # Face
            tileCounts[3] += 1
        elif tile == '4': # Key
            tileCounts[4] += 1
        elif tile == '5': # Spawn
            tileCounts[5] += 1
        else:
            return False

    # Print map info
    print("====== Map Info ======")
    print("    Name = " + filename)
    print("    Empty = " + str(tileCounts[0]) + "/--")
    print("    Blocks = " + str(tileCounts[1]) + "/" + str(validBlocks[1]))
    print("    Bombs = " + str(tileCounts[2]) + "/" + str(validBombs[1]))
    print("    Faces = " + str(tileCounts[3]) + "/" + str(validFaces[1]))
    print("    Key = " + str(tileCounts[4]) + "/" + str(validKeys[1]))
    print("    Spawns = " + str(tileCounts[5]) + "/" + str(validSpawns[1]))
    print("======================")

    # Print warnings
    if tileCounts[1] > validBlocks[1]:
        print("WARNING: Blocks exceed maximum!")
    if tileCounts[2] > validBombs[1]:
        print("WARNING: Bombs exceed maximum!")
    if tileCounts[2] < validBombs[0]:
        print("WARNING: Bombs below minimum!")
    if tileCounts[3] > validFaces[1]:
        print("WARNING: Faces exceed maximum!")
    if tileCounts[3] < validFaces[0]:
        print("WARNING: Faces below minimum!")
    if tileCounts[4] > validKeys[1]:
        print("WARNING: Key spawns exceed maximum!")
    if tileCounts[4] < validKeys[0]:
        print("WARNING: No Key Spawn!")
    if tileCounts[5] > validSpawns[1]:
        print("WARNING: Player/Stairs spawns above maximum!")
    if tileCounts[5] < validSpawns[0]:
        print("WARNING: Player/Stairs spawns below minimum!")

    return True


def validate_map(mapdata, filename):
    '''Validates map size and content'''

    if not validate_size(mapdata):
        print("ERROR: Incorrect map size, file not converted!")
        return False

    if not validate_tiles(mapdata, filename):
        print("ERROR: Unidentfied characters detected, file not converted!")
        return False

    return True


def write_map(mapdata, filename):
    '''Writes converted map as formatted C++ header file'''
    convertFile = open(filename + ".h", "w")
    convertFile.write("const uint8_t PROGMEM " + filename + "[] =\n{\n")

    byteLine = []
    widthCounter = 0
    for tile in mapdata:
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

    print("SUCCESS: Converted file written as " + filename + ".h")


def convert_map(filename):
    '''Top-level map conversion function, accepts filename and exports converted map as C++ header file'''

    try:
        mapdata = read_map(filename)
    except:
        print("ERROR: Invalid read file, file not converted!")
        return

    if not validate_map(mapdata, filename):
        return

    try:
        write_map(mapdata, filename)
    except:
        print("ERROR: Cannot open write file, file not converted!")
        return


#----- Commands -----
def cmd_input():
    '''Collect command input, prep for parser'''
    cmd = input("> ")
    cmd = cmd.split(" ")
    return cmd


def cmd_parse(cmd):
    if cmd[0].lower() in ["exit","quit","q"]:
        sys.exit()

    elif cmd[0].lower() in ["help","h","?",""]:
        print_help()

    elif cmd[0].lower() in ["file","f"]:
        print_file()

    elif cmd[0].lower() in ["convert","c"] and len(cmd) == 2:
        convert_map(cmd[1])

    elif cmd[0].lower() in ["list","l","ls"]:
        print_list()

    elif cmd[0].lower() in ["remove","r","rm"]:
        remove_headers()

    else:
        print("Invalid command! Type HELP for a list of commands")


def cmd_handler():
    '''Top-level command parser, handles input, parsing, and execution'''
    cmd_parse(cmd_input())
    cmd_handler()


#----------------------
def main():
    print("Incher Map Tool - By Dial")
    print("Type HELP for a list of commands, QUIT to exit")
    cmd_handler()


#=========================================
if __name__ == "__main__":
    main()
