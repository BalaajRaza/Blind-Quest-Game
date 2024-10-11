#include<iostream>
#include "grid.h"
#include "player.h"
#include <ctime>
#include <cstdlib>
using namespace std;


class Game{
    
    Grid grid;
    Player player;
    string mode;

    int minimumMoves(int px, int py){
        int keyX = -1;
        int keyY = -1;
        int doorX = -1;
        int doorY = -1;

        for(int i=0;i<grid.getRows();i++){
            for(int j=0;j<grid.getCols();j++){
                if(grid.getValue(i,j) == 'K'){
                    keyX = i;
                    keyY = j;
                }
                else if(grid.getValue(i,j) == 'D'){
                    doorX = i;
                    doorY = j;
                }
            }
        }

        if(keyX==-1 || doorX==-1){
            return -1;
        }

        int movesToKey = abs(px - keyX) + abs(py - keyY);
        int keyToDoor = abs(keyX - doorX) + abs(keyY - doorY);

        return movesToKey+keyToDoor;
    }

    void setPlayerMovesandUndos(){
        int minMoves = minimumMoves(player.getX() , player.getY());
        if(minMoves == -1){
            cout<<"Error: Sorry it's on our side. Try restarting the game";
            exit(1);
        }
        int totalMoves , undos;
        if(mode=="easy"){
            totalMoves = minMoves + 6;
            undos = 6;
        }
        else if(mode=="medium"){
            totalMoves = minMoves + 2;
            undos = 2;
        }
        else if(mode == "hard"){
            totalMoves = minMoves;
            undos = 0;
        }
        else{
            cout<<"Error: Invalid game mode. Please restart the game.";
            exit(1);
        }

        player = Player(player.getX() , player.getY() , totalMoves);
        player.setUndos(undos);
    }

    void gameOver(string reason){
        cout<<"GameOver : "<<reason<<endl;
        exit(0);
    }

    public:
    Game(int rows , int cols , string mode) : grid(rows , cols) , player(0,0,0){
        this->mode = mode;
        grid.initializeGrid();
        srand(time(0));
        int randomX = rand()%4+1;
        int randomY = rand()%4+1;
        player = Player(randomX , randomY, 6);
        grid.setValue(randomX , randomY , 'P');
        grid.setLabel(randomX , randomY , 'P');
        setPlayerMovesandUndos();
        while(true){
            cout<<"Moves Left : "<<player.getMoves() <<" | Undos Left : "<<player.getUndos()<<endl;
            grid.display();
            cout<<"Move WASD or Undo(U) : ";
            char d;
            cin>>d;
            if(!player.move(grid , d)){
                cout<<"invalid Move !" <<endl;
            }
            
            if(player.getMoves() <= 0){
                gameOver("You have no moves left :(");
            }
            if(grid.getValue(player.getX() , player.getY()) == 'B'){
                gameOver("You stepped on a bomb LOL xD");
            }

            if(grid.getValue(player.getX() , player.getY()) == 'D' && player.haveKey()){
                gameOver("You found the door and escaped :D");
            }
        }
    }

    void setMode(string m){
        mode = m;
    }

    
};

int main(){
    cout<<"| | | | BLIND QUEST GAME | | | |\n";
    cout<<"Enter game mode :";
    string mode;
    getline(cin,mode);
    cout<<"\n------------------------------------\n";

    int rows = 15;
    int cols = 15;
    Game game(rows,cols,mode);
    return 0;
}