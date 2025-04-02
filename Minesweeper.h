#ifndef _MINESWEEPER_H_
#define _MINESWEEPER_H_
#include "Grid.h"

// #define _debug_

class Minesweeper {
private:
    int sizeX;      // The width of the grid map 
    int sizeY;      // The height of the grid map 
    int mineNum;    // The number of mine 

    bool explode;   // If any mine explode, player lose 
    bool win;       // If all the empty grid is opened, player win 
 
    Grid** map = nullptr;  // The 2D grid map

private: 
    // Prepare new grid map 
 
    // Ask the player for sizeX, sizeY and mineNum.  
    // Then call createNewMap(), generateMines(), and countMine() 
    void newGame(); 
     
    // Create new 2D grid map (2D Array)      
    void createNewMap(); 
 
    // Clear map before new round start
    void clearMap();
    
    // Randomly choose the grid to insert mines, provided by TA.  
    // DO NOT MODIFY! 
    void generateMines();
    
    // Count the number of neighbor grids that contain mines.
    void countMine(int y, int x); 
 
    // In-game interaction 
 
    // Open the selected grid, check if the input is valid first.
    // If the opened grid is a mine, explode!
    // If the opened grid’s mineCount is 0, call propagateWhiteSpace() 
    void openGrid(int pressedPosY, int pressedPosX); 
 
    // Propagate the white space recursively. 
    // Stop the recursion if the grid (1) is a mine,
    // (2) is already opened, or (3) its mineCount is not 0 
    void propagateWhiteSpace(int pressedPosY, int pressedPosX); 
 
    // After game setting 
    void explodeAllMines(); // Used when the player hit a mine
    void revealAllGrids();  // Used when the player reveal all the non-mine grids
     
    // Helper functions 
     
    // Check if a game is won by comparing the gridOpenCount, 
    // grid map size, and mine count 
    void checkWin(); 
 
    // Check if a input pos is valid 
    bool isPosValid(int posY, int posX); 
 
    // Render 
    // Render the grid map 
    void render(bool forceShowBombs = false);

public: 
    void run();     // The main logic process of the game

    void set_all_isopened(bool);
};

#endif
