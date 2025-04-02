#include "Minesweeper.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <locale>

void Minesweeper::run() {
  do {
    this->newGame();

    this->render();
    while (!win && !explode) {
      int x, y;
      std::wcout << L"Enter X Y to open grid: ";
      std::wcin >> x >> y;
      if (this->isPosValid(y, x)) {
        this->openGrid(y, x);
        this->checkWin();
        this->render(win);
      } else {
        std::wcout << L"Invalid position!" << std::endl;
      }
    }
    if (win) {
      std::wcout << L"Congratulations! You won the game!" << std::endl;
    } else {
      std::wcout << L"Game Over! You hit a mine!" << std::endl;
    }
    wchar_t answer;
    std::wcout << L"Do you want to play another round? (y/n): ";
    std::wcin >> answer;
    clearMap();
    if (!(answer == L'y' || answer == L'Y')) {
      break;
    }
  } while (true);
}

void Minesweeper::newGame() {
  std::wcout << L"Enter grid size X Y and number of mines: ";
  std::wcin >> sizeX >> sizeY >> mineNum;
  this->explode = false;
  this->win = false;
  this->createNewMap();
  this->generateMines();
}

void Minesweeper::createNewMap() {
  map = new Grid *[this->sizeY];
  for (int i = 0; i < this->sizeY; i++) {
    map[i] = new Grid[this->sizeX];
  }
}

void Minesweeper::clearMap() {
  for (int i = 0; i < this->sizeY; i++) {
    if (map[i] != nullptr)
      delete[] map[i];
  }
  if (map != nullptr)
    delete[] map;
}

// DO NOT MODIFY!
void Minesweeper::generateMines() {
  srand(time(nullptr)); // Use current time as seed
  srand(42);
  int minesPlaced = 0;
  while (minesPlaced < mineNum) {
    int randY = rand() % sizeY; // Generate a random Y coordinate
    int randX = rand() % sizeX; // Generate a random X coordinate

    // Check whether the selected grid is already a mine
    if (!map[randY][randX].getIsMine()) {
      map[randY][randX].setMine(); // Set this grid as a mine
      minesPlaced++;
    }
  }
  for (int row = 0; row < sizeY; row++) {
    for (int col = 0; col < sizeX; col++) {
      if (!this->map[row][col].getIsMine()) {
        this->countMine(row, col);
      }
    }
  }
}

void Minesweeper::countMine(int y, int x) {
  int mineCount(0);
  if (this->isPosValid(y - 1, x - 1) && this->map[y - 1][x - 1].getIsMine())
    mineCount++;
  if (this->isPosValid(y - 1, x) && this->map[y - 1][x].getIsMine())
    mineCount++;
  if (this->isPosValid(y - 1, x + 1) && this->map[y - 1][x + 1].getIsMine())
    mineCount++;
  if (this->isPosValid(y, x - 1) && this->map[y][x - 1].getIsMine())
    mineCount++;
  if (this->isPosValid(y, x + 1) && this->map[y][x + 1].getIsMine())
    mineCount++;
  if (this->isPosValid(y + 1, x - 1) && this->map[y + 1][x - 1].getIsMine())
    mineCount++;
  if (this->isPosValid(y + 1, x) && this->map[y + 1][x].getIsMine())
    mineCount++;
  if (this->isPosValid(y + 1, x + 1) && this->map[y + 1][x + 1].getIsMine())
    mineCount++;
  this->map[y][x].setMineCount(mineCount);
}

void Minesweeper::openGrid(int posY, int posX) {
  if (this->isPosValid(posY, posX) && !(this->map[posY][posX].getIsOpened())) {
    if (this->map[posY][posX].getIsMine()) {
      this->set_all_isopened(true);
      this->explodeAllMines();
      this->explode = true;
      Grid::resetGridOpenCount();
      return;
    }
    this->map[posY][posX].open();
    if (this->map[posY][posX].getMineCount() == 0) {
      this->propagateWhiteSpace(posY, posX);
    }
    Grid::open_a_grid();
  }
}

void Minesweeper::propagateWhiteSpace(int posY, int posX) {
  this->openGrid(posY - 1, posX - 1);
  this->openGrid(posY - 1, posX);
  this->openGrid(posY - 1, posX + 1);
  this->openGrid(posY, posX - 1);
  this->openGrid(posY, posX + 1);
  this->openGrid(posY + 1, posX - 1);
  this->openGrid(posY + 1, posX);
  this->openGrid(posY + 1, posX + 1);
}

void Minesweeper::explodeAllMines() {
  this->explode = true;
  for (int row = 0; row < this->sizeY; row++) {
    for (int col = 0; col < this->sizeX; col++) {
      if (this->map[row][col].getIsMine())
        this->map[row][col].setExploded();
    }
  }
}

void Minesweeper::revealAllGrids() {}

void Minesweeper::checkWin() {
  if (Grid::getOpenCount() == (this->sizeY * this->sizeX - this->mineNum))
    this->win = true;
}

bool Minesweeper::isPosValid(int posY, int posX) {
  return (posX >= 0 && posX < this->sizeX) && (posY >= 0 && posY < this->sizeY);
}

void Minesweeper::render(bool forceShowBombs) {
  std::wcout << L"  x";
  for (int x = 0; x < sizeX; ++x) {
    std::wcout << std::setw(2) << std::setfill(L' ') << x;
  }
  std::wcout << std::endl << L" y" << BOX_UL;
  for (int x = 0; x < sizeX * 2; ++x) {
    std::wcout << BOX_H;
  }
  std::wcout << BOX_UR << std::endl;

  for (int y = 0; y < sizeY; ++y) {
    std::wcout << std::setw(2) << std::setfill(L' ') << y;
    std::wcout << BOX_V;
    for (int x = 0; x < sizeX; ++x) {
      if (!forceShowBombs)
        map[y][x].render();
      else {
        map[y][x].open();
        map[y][x].render();
        map[y][x].close();
      }
    }
    std::wcout << BOX_V << std::endl;
  }
  std::wcout << L"  " << BOX_LL;
  for (int x = 0; x < sizeX * 2; ++x) {
    std::wcout << BOX_H;
  }
  std::wcout << BOX_LR << std::endl;
}

void Minesweeper::set_all_isopened(bool open) {
  for (int row = 0; row < sizeY; row++) {
    for (int col = 0; col < sizeX; col++) {
      if (open) {
        this->map[row][col].open();
      } else {
        this->map[row][col].close();
      }
    }
  }
}
