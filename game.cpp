#include<iostream>
#include "grid.h"
#include "player.h"
#include <ctime>
#include <cstdlib>
#include<thread>
#include <chrono>
#include<string>
#include<curses.h>
#include<curses.h>

using namespace std;


class Game {

    Grid grid;
    Player player;
    string mode;

    void setKeyAndDoorPositions() {
        for (int i = 0; i < grid.getRows(); i++) {
            for (int j = 0; j < grid.getCols(); j++) {
                if (grid.getValue(i, j) == 'K') {
                    player.setKey(i, j);
                }
                else if (grid.getValue(i, j) == 'D') {
                    player.setDoor(i, j);
                }
            }
        }
    }

    int minimumMoves(int px, int py) {
        int keyX = -1;
        int keyY = -1;
        int doorX = -1;
        int doorY = -1;

        for (int i = 0; i < grid.getRows(); i++) {
            for (int j = 0; j < grid.getCols(); j++) {
                if (grid.getValue(i, j) == 'K') {
                    keyX = i;
                    keyY = j;
                }
                else if (grid.getValue(i, j) == 'D') {
                    doorX = i;
                    doorY = j;
                }
            }
        }

        if (keyX == -1 || doorX == -1) {
            return -1;
        }

        int movesToKey = abs(px - keyX) + abs(py - keyY);
        int keyToDoor = abs(keyX - doorX) + abs(keyY - doorY);

        return movesToKey + keyToDoor;
    }

    void setPlayerMovesandUndos() {
        int minMoves = minimumMoves(player.getX(), player.getY());
        if (minMoves == -1) {
            mvprintw(0, 0, "Error: Sorry it's on our side. Try restarting the game");
            refresh(); 
            exit(1);
        }
        int totalMoves, undos;
        if (mode == "easy") {
            totalMoves = minMoves + 6;
            undos = 6;
        }
        else if (mode == "medium") {
            totalMoves = minMoves + 2;
            undos = 2;
        }
        else if (mode == "hard") {
            totalMoves = minMoves;
            undos = 0;
        }
        else {
            mvprintw(0, 0, "Error: Invalid game mode. Please restart the game.");
            refresh(); 
            exit(1);
        }

        player = Player(player.getX(), player.getY(), totalMoves, grid);
        setKeyAndDoorPositions();
        player.setUndos(undos);
    }

    void replaceCoins() {
        while (true) {
            this_thread::sleep_for(chrono::seconds(10));
            for (int i = 0; i < grid.getRows(); i++) {
                for (int j = 0; j < grid.getCols(); j++) {
                    if (grid.getValue(i, j) == 'C') {
                        grid.setValue(i, j, '.');
                        grid.setLabel(i, j, '.');
                        grid.placeItems('C');
                    }
                }
            }
        }
    }

public:
    Game(int rows, int cols, string mode) : grid(rows, cols), player(0, 0, 0, grid) {
       this->mode = mode;
       grid.initializeGrid();
       srand(time(0));
       int randomX = rand() % 4 + 1;
       int randomY = rand() % 4 + 1;
       grid.setValue(randomX, randomY, 'P');
       grid.setLabel(randomX, randomY, 'P');

       initscr();
       start_color();
       init_pair(1, COLOR_GREEN, COLOR_BLACK);
       attron(COLOR_PAIR(1));

       player = Player(randomX, randomY, 0, grid);
       setPlayerMovesandUndos();

       thread coinReplacer(&Game::replaceCoins, this);
       coinReplacer.detach();



       while (true) {
          clear();
          mvprintw(1, 0, "| | | MODE : %s | | |\n", mode.c_str());
          mvprintw(2, 0, "Moves Left : %d | Undos Left : %d\n", player.getMoves(), player.getUndos());
          mvprintw(3, 0, "Have Key : %s\n", player.haveKey() ? "true" : "false");
          mvprintw(4, 0, "Score : %d\n", player.getScore());

          player.sense();
          grid.displayLabels();
          mvprintw(cols+5, 0, "Move WASD or Undo(U) : ");
          char d;
          d = getch();
          if (!player.move(grid, d)) {
              mvprintw(0, 0, "Invalid Move!\n");
          }

          endwin();
    }

    }

    void setMode(string m) {
        mode = m;
    }


};

int main() {
   initscr();
   start_color();
   init_pair(1, COLOR_GREEN, COLOR_BLACK);
   attron(COLOR_PAIR(1));
   
   mvprintw(0, 0, "| | | | BLIND QUEST GAME | | | |\n");
   mvprintw(1, 0, "Enter game mode :");
   refresh();

   char mode[10];
   getstr(mode);

   int rows = 0;
   int cols = 0;

   string MODE = string(mode);
   if (MODE == "easy") {
       rows = cols = 10;  
   }
   else if (MODE == "medium") {
       rows = cols = 15;
   }
   else if (MODE == "hard") {
      rows = cols = 20;
   }
   Game game(rows, cols, MODE);

   getch();
   endwin();
   return 0;
}