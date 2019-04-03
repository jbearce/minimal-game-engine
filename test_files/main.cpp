//compile with: clang++ `pkg-config --libs ncurses` main.cpp

#include <iostream>
#include <unistd.h>
#include <term.h>
#include "../includes/game_screen.hpp"

int main() {
    game_screen::empty_screen();    
    return 0;
}