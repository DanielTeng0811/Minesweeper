#include <locale>
#include "Minesweeper.h"

int main() {
    setlocale(LC_ALL, "");
    Minesweeper game;
    game.run(); 

    return 0;
}
