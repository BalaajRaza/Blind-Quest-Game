#include "grid.h"

Grid::Grid(int r , int c){
    rows = r;
    cols = c;
    head = NULL;
    //initializeGrid();
}
void Grid::initializeGrid(){
    for(int i = 0 ; i<rows;i++){
        for(int j = 0;j<cols;j++){
            if(i==0 || j==0 || i==rows-1 || j==cols-1){
                insert(i , j , '#');
            }
            else{
                insert(i , j , '.');
            }
        }
}
}

void Grid::insert(int x , int y ,char v){
    Node* newNode = new Node(v,x,y);
    if(!head){
        head = newNode;
    }
    else{
        Node* current = getNode(x,y);
        if (current){
            current->val = v;
            delete newNode;
            return;
        }

        Node* left = (y > 0) ? getNode(x , y-1) : NULL;
        Node* up = (x > 0) ? getNode(x-1 , y) : NULL;
        if (left) {
            left->right = newNode;
            newNode->left = left;
        }
        if (up) {
            up->down = newNode;
            newNode->up = up;
        }
        if(left && left->down){
            newNode->down = left->down;
            left->down->up = newNode;
        }
        if(up && up->right){
            newNode->right = up->right;
            up->right->left = newNode;
        }
        
    }
}

char Grid::getValue(int x , int y){
    Node* current = getNode(x,y);
    return current ? current->val : ' ';
}

void Grid::setValue(int x , int y , char val){
    Node* current = getNode(x , y);
    if(current){
        current->val = val;
    }
}

Node* Grid::getNode(int x , int y){
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        return NULL;
    }
    Node* current = head;
    while(current){
        if(current->x == x && current->y == y){
            return current;
        }

        if(current->y < y && current->right){
            current = current->right;
        }
        else if(current->x < x && current->down){
            current = current->down;
        }
        else{
            break;
        }
    }
    return NULL;
}

void Grid::display(){
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            cout<<getValue(i,j)<<" ";
        }
        cout<<endl;
    }
}