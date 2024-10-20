#include "player.h"
#include<utility>
#include<curses.h>
#include<curses.h>
using namespace std;

Player::Player(int x, int y, int moves, const Grid& grid) : initialGrid(grid) {
    this->x = x;
    this->y = y;
    this->moves = moves;
    this->hasKey = false;
    label = 'P';
    score = 0;
    keyX = keyY = doorX = doorY = -1;
}

int Player::getX() {
    return x;
}

int Player::getY() {
    return y;
}

bool Player::haveKey() {
    return hasKey;
}

bool Player::move(Grid& grid, char direction) {
    if (moves <= 0) {
        gameOver("You are out of moves LOL xD");
    }
    int newX = x;
    int newY = y;
    if (direction == 'w' || direction == 'W')
        newX = x - 1;
    else if (direction == 's' || direction == 'S')
        newX = x + 1;
    else if (direction == 'a' || direction == 'A')
        newY = y - 1;
    else if (direction == 'd' || direction == 'D')
        newY = y + 1;
    else if (direction == 'u' || direction == 'U')
        return undoMove(grid);

    if (grid.getValue(newX, newY) != '#') {
        pair<int, int> lastMove = moveHistory.peek();

        if (newX != lastMove.first || newY != lastMove.second) {
            if (grid.getValue(newX, newY) == 'D' && !hasKey) {
                mvprintw(0, 0, "\n--The door is locked--\n");
                refresh();
                return false;
            }

            grid.setLabel(x, y, '.');
            moveHistory.push(x, y);
            x = newX;
            y = newY;

            char currentCell = grid.getValue(x, y);
            if (currentCell == 'K') {
                hasKey = true;
                grid.setValue(x, y, '.');
            }
            else if (currentCell == 'C') {
                mvprintw(0, 0, "\nYou gained an extra Undo\n");
                refresh();
                score += 2;
                undos++;
                coinsCollected.add_coin(x, y);
                grid.setValue(x, y, '.');
            }
            else if (currentCell == 'B') {
                grid.setValue(x, y, '.');
                grid.setLabel(x, y, label);
                gameOver("You stepped on a bomb LOLxD");
                return false;
            }
            else if (currentCell == 'D') {
                if (hasKey) {
                    grid.setValue(x, y, '.');
                    grid.setLabel(x, y, label);
                    gameWin();
                    return false;
                }
            }

            grid.setLabel(x, y, label);
            moves--;
            return true;
        }
        else {
            return false;
        }
    }

    return true;


}

bool Player::undoMove(Grid& grid) {
    if (undos > 0 && !moveHistory.isEmpty()) {
        grid.setValue(x, y, '.');
        grid.setLabel(x, y, '.');
        x = moveHistory.peek().first;
        y = moveHistory.peek().second;
        moveHistory.pop();
        grid.setValue(x, y, label);
        grid.setLabel(x, y, label);
        undos--;
        return true;
    }
    mvprintw(0,0,"--Undo Not Possible(No Undos left or no Move history)--\n");
    return false;

}

void Player::gameOver(string reason) {
    mvprintw(0, 0, "\nGameOver : %s\n", reason.c_str());
    mvprintw(1, 0, "Your Final Score : %d\n", score);
    mvprintw(2, 0, "| | | Initial Grid | | |\n");
    refresh();
    coinsCollected.display_coinHistory();
    initialGrid.displayValues();
    exit(0);
}

void Player::gameWin() {
    score += moves;
    mvprintw(0, 0, "\nYou Won!!\n");
    mvprintw(1, 0, "Your Final Score : %d\n", score);
    mvprintw(2, 0, "| | | Initial Grid | | |\n");
    refresh();
    coinsCollected.display_coinHistory();
    initialGrid.displayValues();
    exit(0);
}

int calculateDistance(int x, int y, int targetX, int targetY) {
    return abs(x - targetX) + abs(y - targetY);
}

void Player::sense() {
    int targetX = hasKey ? doorX : keyX;
    int targetY = hasKey ? doorY : keyY;

    if (targetX == -1 || targetY == -1) {
        mvprintw(0, 0, "Hint:\n");
        refresh();
        return;
    }
    if (moveHistory.isEmpty()) {
        mvprintw(0, 0, "Hint:\n");
        refresh();
        return;
    }
    int currentDistance = calculateDistance(x, y, targetX, targetY);
    int prevDistance = calculateDistance(moveHistory.peek().first, moveHistory.peek().second, targetX, targetY);
    if (currentDistance < prevDistance) {
        mvprintw(0, 0, "Hint: Closer\n");
        refresh();
    }
    else if (currentDistance > prevDistance) {
        mvprintw(0, 0, "Hint: Moving Away\n");
        refresh();
    }
    else {
        mvprintw(0, 0, "Hint : You are at same postion\n");
        refresh();
    }

}
