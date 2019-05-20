#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>

using namespace std;

vector<vector<char>> import_file(string input) {
    vector<vector<char>> output;
    ifstream inputFile(input);
    string line;
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            vector<char> currLine;
            int lineSize = line.length();
            for(int i = 0; i < lineSize; ++i) {
                currLine.push_back(line[i]);
            }
            output.push_back(currLine);
        }
        inputFile.close();
    } else {
        cout << "Error: file " << input << " could not be opened or does not exist." << endl;
    }
    return output;
}

struct coord {
    //current player coordinates:
    int x = 11;
    int y = 1;
};

void clear_screen() {
    for(int i = 0; i < 50; ++i) {
        addch('\n');
    }
    refresh();
}

//determines the width and height of the map. Exports to a coord type struct
coord initialize_map(vector<vector<char>>& map) {
    coord mapSize;
    mapSize.x = map[0].size();
    mapSize.y = map.size();
    for(int i = 0; i < mapSize.y; ++i) {
        int mapRowSize = map[i].size();
        if (mapRowSize > mapSize.x) {
            mapSize.x = mapRowSize;
        }
    }
    return mapSize;
}

void draw_map(vector<vector<char>>& map, coord& mapSize, coord& pos) {
    int cursor_row = 3;
    int cursor_col = 0;
    refresh();
    for(int row = 0; row < mapSize.y; ++row) {
        move(cursor_row, cursor_col);
        int mapRowSize = map[row].size();
        for(int col = 0; col < mapRowSize; ++col) {
            if (pos.x == col && pos.y == row){
                addch('G');
            } else {
                addch(map[row][col]);
            }
        }
        refresh();
        cursor_row += 1;
        move(cursor_row, cursor_col);
    }
    refresh();
}

//determines wether coord set 1 is within the bounds of coord set 2
bool legal(coord &loc, coord& map) {
    if (loc.x < map.x && loc.x > 0 && loc.y < map.y && loc.y > 0) {
        return true;
    }
    return false;
}

//Move the player if a valid key is pressed, and the new pos is valid
void move_player(vector<vector<char>>& map, coord& mapSize, coord& pos, char usrKey) {
    
    coord newPos = pos;

    if (usrKey == 'w') {
        newPos.y -= 1;
    } else if (usrKey == 'a') {
        newPos.x -= 1;
    } else if (usrKey == 's') {
        newPos.y += 1;
    } else if (usrKey == 'd') {
        newPos.x += 1;
    }

    char movePt = map[newPos.y][newPos.x];

    if (movePt != 'X' && legal(newPos, mapSize)) {
        pos = newPos;

        move(0,0);
        addstr("Successful overwrite: ");
        addch(movePt);
        addstr(" X pos: ");
        string xPos = to_string(pos.x);
        string yPos = to_string(pos.y);
        for(int i = 0; i < xPos.size(); i++) {
            addch(xPos[i]);
        }
        addstr(" Y pos: ");
        for(int i = 0; i < yPos.size(); i++) {
            addch(yPos[i]);
        }
        refresh();
    } else {
        move(0,0);
        addstr("Failed overwrite: ");
        addch(movePt);
        addstr(" X pos: ");
        string xPos = to_string(pos.x);
        string yPos = to_string(pos.y);
        for(int i = 0; i < xPos.size(); i++) {
            addch(xPos[i]);
        }
        addstr(" Y pos: ");
        for(int i = 0; i < yPos.size(); i++) {
            addch(yPos[i]);
        }
        refresh();
    }
    clear_screen();
    draw_map(map, mapSize, pos);
}

int main() {
    string input = "null";
    coord playerPos;
    vector<vector<char>> gameMap = import_file("gamemap.csv");
    coord mapSize = initialize_map(gameMap);
    cout << "Map size: " << mapSize.x << " x " << mapSize.y << "(wxh)" << endl;
    cin >> input;
    int userInput;
    initscr();
    timeout(-1);
    noecho();
    refresh();
    draw_map(gameMap, mapSize, playerPos);
    //nodelay(stdscr, TRUE);
    while(char(userInput) != 'q') {
        userInput = getch();
        if (char(userInput) != 'q') {
            move_player(gameMap, mapSize, playerPos, char(userInput));
            userInput = 0;
        }
    }
    endwin();
    return 0;
}