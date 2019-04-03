#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "game_core.hpp"
#include <unistd.h>
#include <term.h>

namespace screen {
    void clear_screen();
    void set_position(position& input);
}
#endif // SCREEN_HPP
