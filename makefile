#note: this makefile is not configured for the current project. It's an example only
main_reqs = ./includes/game_core.hpp ./includes/game_screen.hpp
game_screen_reqs = ./includes/game_core.hpp ./includes/game_screen.hpp
game_terrain_reqs = ./includes/game_core.hpp ./includes/game_terrain.hpp $(main_reqs)
game_character_reqs = ./includes/game_core.hpp ./includes/game_character.hpp
main_dir = ./test_files/
core_dir = ./core/
inc_dir = ./includes/
obj_files = game_terrain.o game_screen.o main.o game_character.o

game_character.o : $(game_character_reqs)
	clang++ $(core_dir)game_character.cpp -c -lncurses

game_terrain.o : $(game_terrain_reqs)
	clang++ $(core_dir)game_terrain.cpp -c -lncurses

#compiles an object file `game_screen.o`. Component of executable `out`
game_screen.o : $(game_screen_reqs)
	clang++ $(core_dir)game_screen.cpp -c -lncurses

#compiles an object file `main.o`. Component of executable `out`. Contains int main()
main.o : $(main_reqs)
	clang++ $(main_dir)main.cpp $(core_dir)game_screen.cpp -c -lncurses

#outputs the final file (named `out`)
output : game_screen.o main.o game_terrain.o
	clang++ -o out $(obj_files) -lncurses

clean : 
	rm -f main.o game_screen.o