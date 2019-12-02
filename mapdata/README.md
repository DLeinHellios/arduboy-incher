# Incher - maptool.py

## Basic Use
1. Build .csv file (specifications below) and save in mapdata directory
2. Run maptool.py and type "command <FILENAME>" - without ".csv"
3. Copy content of exported header file to tilemaps.h and add selection logic to readMap() in game.h

## Command List
- QUIT - Exit program
- HELP - Print command list
- FILE - Print CSV file guidelines
- CONVERT <MAPNAME> - Converts CSV map to byte array
- LIST - Lists CSV files in script directory
- REMOVE - Removes all header files from program directory

## CSV File
Map files can be constructed in any CSV editor (Microsoft Excel, LibreOffice Calc, etc.), but due to variation in editors, they should contain nothing but the cell values in the exported file. The map grid is 15x7 tiles, or 105 individual tile values. All original maps are included as .csv files as examples

Here are the values representing the individual tiles:

    0 = Empty
    1 = Block
    2 = Bomb
    3 = Face
    4 = Key
    5 = Spawn/Goal

There are quantity restrictions for tile types. Note that the map defines the *possible* locations of certain spawns, they are placed at random.

    0 <= Blocks <= 50
    5 <= Bombs <= 10
    3 <= Faces <= 5
    1 <= Keys <=  4
    2 <= Spawn/Goal <= 4
