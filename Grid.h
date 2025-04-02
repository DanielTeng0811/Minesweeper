// Grid.h
#ifndef _GRID_H_
#define _GRID_H_

const wchar_t BLACK_SQ = L'\u2B1B'; // black square
const wchar_t BOMB = L'\U0001F4A3';    // bomb symbol
const wchar_t EXPLOSION = L'\U0001F4A5'; // collision symbol
const wchar_t BOX_H = L'\u2500';    // horizontal line
const wchar_t BOX_V = L'\u2502';    // vertical line
const wchar_t BOX_UL = L'\u250C';   // upper left corner
const wchar_t BOX_UR = L'\u2510';   // upper right corner
const wchar_t BOX_LL = L'\u2514';   // lower left corner
const wchar_t BOX_LR = L'\u2518';   // lower right corner

class Grid { 
private:
    bool isMine;        // Indicate if the grid is a mine 
    bool isOpened;      // Indicate if the grid is opened
    bool isExploded;    // Indicate if the mine is exploded
    int mineCount;          // The neighbor mine count

    static int gridOpenCount;   // The number of opened grid 

public: 
    Grid();

    void setMine();
    void setExploded();
    void setMineCount(int mineCount);
    void open();
    void close();

    bool getIsMine();
    bool getIsOpened();
    int getMineCount();
    
    static void open_a_grid();
    static int getOpenCount();
    static void resetGridOpenCount();

    // Render 
    // Render the grid by checking the grid status. 
    // If the grid is not opened, render the blank icon. 
    // If the grid is opened and the mineCount is 0, render 2 spaces 
    // If the grid contains mine, is opened, and is exploded, render   
    // the exploded icon. 
    // If the grid contains mine, is opened, and is not exploded,  
    // render the bomb icon. 
    void render();     
}; 

#endif
