#include "Grid.h"
#include <iostream>
#include <iomanip>
#include <locale>

Grid::Grid(): isMine(false), isOpened(false), isExploded(false), mineCount(0) {}

// Initialize static member
int Grid::gridOpenCount = 0;

// Mutators
void Grid::setMine() { this->isMine = true; }
void Grid::setExploded() { this->isExploded = true; }
void Grid::setMineCount(int mineCount) { this->mineCount = mineCount; }
void Grid::open() { this->isOpened = true; }
void Grid::close() { this->isOpened = false; }

// Static member functions
void Grid::resetGridOpenCount() { Grid::gridOpenCount = 0; }
void Grid::open_a_grid() { Grid::gridOpenCount += 1; }
int Grid::getOpenCount() { return Grid::gridOpenCount; }

// Accessors
bool Grid::getIsMine() { return this->isMine; }
bool Grid::getIsOpened() { return this->isOpened; }
int Grid::getMineCount() { return this->mineCount; }

// Render function Implementation
void Grid::render() {
    if (!isOpened) { std::wcout << BLACK_SQ; }
    else {
        if (isMine && isExploded) { std::wcout << EXPLOSION; }
        else if (isMine && !isExploded) { std::wcout << BOMB; }
        else if (mineCount > 0) { std::wcout << std::setw(2) << std::setfill(L' ') << mineCount; }
        else { std::wcout << L"  "; }
    }
}
