#ifndef GRID_H
#define GRID_H

#include<iostream>
using namespace std;

class Node{
    public:
    char val;
    int x;
    int y;
    Node* left;
    Node* right;
    Node* up;
    Node* down;

    Node(char v , int X , int Y){
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
    void insert(int x, int y , char v);
    char getValue(int x, int y);
    void setValue(int x, int y , char v);
    Node* getNode(int x, int y);
    void display();


};

#endif 
