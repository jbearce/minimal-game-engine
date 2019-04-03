#include "../includes/game_screen.hpp"

void game_screen::empty_screen() {
    if (true) {
        int result;
        setupterm( NULL, STDOUT_FILENO, &result );
        if (result <= 0) return;
    }

    putp( tigetstr( "clear" ) );
}

void game_screen::set_position(position& input) {
    
}