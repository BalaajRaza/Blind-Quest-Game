#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <utility>
#include "grid.h"
using namespace std;

class node{
    public:
    int x;
    int y;
    node* next;
    node(int x , int y){
        this->x = x;
        this->y = y;
        this->next = NULL;
    }
};

class stack{
    node* top;
    public:
    stack(){top = NULL;}

    void push(int x , int y){
        node* newNode = new node(x , y);
        if(top == NULL){
            top = newNode;
        }
        else{
            newNode->next = top;
            top = newNode;

        }
    }

    void pop(){
        if(top == NULL){
            return;
        }
        else{
            node* temp = top;
            top = top->next;
            delete temp;
        }
    }
    pair<int , int> peek(){
        if(top == NULL){
            return make_pair(-1,-1);
        }
        else{
            
            return make_pair(top->x , top->y);
        }
    }
    bool isEmpty() {
        return top == NULL;
    }
};

class Player{
    int x;
    int y;
    int undos;
    int moves;
    int score;
    bool hasKey;
    char label;
    stack moveHistory;
    Grid initialGrid;

    public:
    Player(int x , int y, int moves , const Grid& grid);
    int getX();
    int getY();
    bool haveKey();
    bool move(Grid& grid , char direction);
    bool undoMove(Grid& grid);
    void setUndos(int u){undos = u;}
    int getUndos(){return undos;}
    void setMoves(int moves) {this->moves = moves;}
    int getMoves(){return moves;}
    void gameOver(string reason);
    void gameWin();
    int getScore(){return score;}

    
};

#endif 