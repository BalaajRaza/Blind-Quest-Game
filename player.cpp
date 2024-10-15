#include "player.h"
#include<utility>
using namespace std;

    Player::Player(int x , int y , int moves ,const Grid& grid): initialGrid(grid){
            this->x = x;
            this->y = y;
            this->moves = moves;
            this->hasKey = false;
            label = 'P';
            score = 0;
    }

    int Player::getX(){
        return x;
    }
    
    int Player::getY(){
        return y;
    }

    bool Player::haveKey(){
        return hasKey;
    }

    bool Player::move(Grid& grid , char direction){
        if(moves <= 0){
            gameOver("You are out of moves LOL xD");
        }
        int newX = x;
        int newY = y;
        if(direction == 'w' || direction == 'W')
        newX = x-1;
        else if(direction == 's' || direction == 'S')
        newX = x+1;
        else if(direction == 'a' || direction == 'A')
        newY = y-1;
        else if(direction == 'd' || direction == 'D')
        newY = y+1;
        else if(direction == 'u' || direction == 'U')
        return undoMove(grid);

        if(grid.getValue(newX , newY) != '#'){
            pair<int,int> lastMove = moveHistory.peek();

            if(newX != lastMove.first || newY != lastMove.second){
                if (grid.getValue(newX, newY) == 'D' && !hasKey){
                    cout << "\n--The door is locked--\n";
                    return true;
                }

                grid.setLabel(x,y,'.');
                moveHistory.push(x,y);
                x = newX;
                y = newY;

                char currentCell = grid.getValue(x , y);
                if(currentCell == 'K'){
                    hasKey = true;
                    grid.setValue(x , y , '.');
                }
                else if(currentCell == 'C'){
                    cout<<"\nYou gained and extra Undo\n";
                    score+=2;
                    undos++;
                    grid.setValue(x , y , '.');
                }
                else if(currentCell == 'B'){
                    grid.setValue(x , y , '.');
                    gameOver("You stepped on a bomb LOLxD");
                    return false;
                }
                else if(currentCell == 'D'){
                    if(hasKey){
                        gameWin();
                        return false;
                    }
                }

                grid.setLabel(x,y,label);
                moves--;
                return true;
            }else{
                cout<<"\n--Invalid Move--\n";
            }
        }

        return true;


    }

    bool Player::undoMove(Grid& grid){
        if(undos>0 && !moveHistory.isEmpty()){
            grid.setValue(x , y , '.');
            grid.setLabel(x,y,'.');
            x = moveHistory.peek().first;
            y = moveHistory.peek().second;
            moveHistory.pop();
            grid.setValue(x , y , label);
            grid.setLabel(x,y,label);
            undos--;
            return true;
        }
        cout<<"--Undo Not Possible(No Undos left or no Move history)--\n";
        return false;

    }

    void Player::gameOver(string reason){
        cout<<"GameOver : "<<reason<<endl;
        cout<<"Your Final Score : "<<score<<endl;
        cout<<"\n| | | Initial Grid | | |\n";
        initialGrid.displayValues();
        exit(0);
    }

    void Player::gameWin(){
        score+=moves;
        cout<<"You Won!!\n";
        cout<<"Your Final Score : "<<score<<endl;
        cout<<"\n| | | Initial Grid | | |\n";
        initialGrid.displayValues();
        exit(0);
    }