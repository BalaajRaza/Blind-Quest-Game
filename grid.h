#ifndef GRID_H
#define GRID_H

#include<iostream>
using namespace std;

class Node{
    public:
    char val;
    char label;
    int x;
    int y;
    Node* left;
    Node* right;
    Node* up;
    Node* down;

    Node(char v, char l , int X , int Y){
        label = l;
        val = v;
        x = X;
        y = Y;
        left = NULL;
        right = NULL;
        up = NULL;
        down = NULL;
    }
};

class Grid{
    
    Node* head;
    int rows;
    int cols;
    public:

    Grid(int r , int c);
    void initializeGrid();
    void placeItems(char label); 
    void insert(int x, int y , char v , char l);
    char getValue(int x, int y);
    void setValue(int x, int y , char v);
    char getLabel(int x, int y);
    void setLabel(int x, int y , char l);
    Node* getNode(int x, int y);
    void display();
    int getRows();
    int getCols();


};

#endif 
