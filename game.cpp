#include<iostream>
#include "grid.h"
#include "player.h"
#include <ctime>
#include <cstdlib>
using namespace std;


class Game{
    
    Grid grid;
    Player player;

    public:
    Game(int rows , int cols) : grid(rows , cols) , player(0,0,0){
        grid.initializeGrid();
        srand(time(0));
        int randomX = rand()%4+1;
        int randomY = rand()%4+1;
        player = Player(randomX , randomY, 6);
        grid.setValue(randomX , randomY , 'P');
        while(true){
            grid.display();
            cout<<"Move WASD : ";
            char d;
            cin>>d;
            player.move(grid , d);
        }
    }

    
};

int main(){
    int rows = 15;
    int cols = 15;
    Game game(rows , cols);
    return 0;
}