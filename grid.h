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
    void copyGrid(const Grid& other);

    void deletGrid() {
    Node* currentRowHead = head;
    while (currentRowHead != NULL) {
        Node* current = currentRowHead;
        currentRowHead = currentRowHead->down;

        while (current != NULL) {
            Node* nextNode = current->right;
            delete current;
            current = nextNode;
        }
    }
    
    }
    public:

    Grid(int r , int c);
    ~Grid();
    Grid(const Grid& other);
    void initializeGrid();
    void placeItems(char label); 
    void insert(int x, int y , char v , char l);
    char getValue(int x, int y)const;
    void setValue(int x, int y , char v);
    char getLabel(int x, int y)const;
    void setLabel(int x, int y , char l)const;
    Node* getNode(int x, int y)const;
    void displayLabels()const;
    void displayValues()const;
    int getRows()const;
    int getCols()const;


};

#endif 
