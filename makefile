main_reqs = ./includes/game_core.hpp ./includes/game_screen.hpp
game_screen_reqs = ./includes/game_core.hpp ./includes/game_screen.hpp
main_dir = ./test_files/
core_dir = ./core/
inc_dir = ./includes/

#outputs the final file (named `out`)
output : game_screen.o main.o
	clang++ -o out main.o game_screen.o -lncurses

#compiles an object file `game_screen.o`. Component of executable `out`
game_screen.o : $(game_screen_reqs) $(outer_libs)
	clang++ $(core_dir)game_screen.cpp -c -lncurses

#compiles an object file `main.o`. Component of executable `out`. Contains int main()
main.o : $(main_reqs)
	clang++ $(main_dir)main.cpp $(core_dir)game_screen.cpp -c -lncurses

clean : 
	rm -f main.o game_screen.o