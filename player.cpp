#include "player.h"
#include<utility>
using namespace std;

    Player::Player(int x , int y , int moves){
            this->x = x;
            this->y = y;
            this->moves = moves;
            this->hasKey = false;
            label = 'P';
            //moveHistory.push(x, y);
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

            /*pair<int,int>*/ auto lastMove = moveHistory.peek();

            // cout << "Current Position: (" << x << ", " << y << ")" << endl;
            // cout << "Attempting to Move to: (" << newX << ", " << newY << ")" << endl;
            // cout << "Last Move: (" << lastMove.first << ", " << lastMove.second << ")" << endl;

            if(newX != lastMove.first || newY != lastMove.second){
                grid.setValue(x , y , '.');
                grid.setLabel(x,y,'.');
                moveHistory.push(x,y);
                x = newX;
                y = newY;
                moves--;

                char currentCell = grid.getValue(x , y);
                if(currentCell == 'K'){
                    hasKey = true;
                    grid.setValue(x , y , '.');
                }
                else if(currentCell == 'C'){
                    undos++;
                    grid.setValue(x , y , '.');
                }
                grid.setValue(x, y ,label);
                grid.setLabel(x,y,label);
                return true;
            }else{
                cout<<"\n--Invalid Move--\n";
            }
        }

        return false;


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