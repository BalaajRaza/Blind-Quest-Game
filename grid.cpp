#include "grid.h"
#include <ctime>
#include <cstdlib>

Grid::Grid(int r , int c):rows(r) , cols(c) , head(NULL){}

Grid::~Grid() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Node* current = getNode(i, j);
            if (current) {
            delete current;
            }
        }
    }
}

Grid::Grid(const Grid& other) : rows(other.rows), cols(other.cols), head(NULL) {
    copyGrid(other);
}

void Grid::copyGrid(const Grid& other){
    if(other.head){
        for(int i=0; i<rows;i++){
            for(int j=0;j<cols;j++){
                Node* current = other.getNode(i, j);
                if(current){
                    insert(i,j,current->val,current->label);
                }
            }
        }
    }

}

void Grid::initializeGrid(){
    srand(time(0));
    for(int i = 0 ; i<rows;i++){
        for(int j = 0;j<cols;j++){
            if(i==0 || j==0 || i==rows-1 || j==cols-1){
                insert(i , j , '#' , '#');
            }
            else{
                insert(i , j , '.' , '.');
            }
        }
    }
    for(int i=0;i<3;i++){
        placeItems('C');
    }

    for(int i=0;i<2;i++){
        placeItems('B');
    }
    placeItems('K');
    placeItems('D');
    
}

void Grid::placeItems(char label){
    int x;
    int y;
    do{
        x = rand()%(rows - 2) + 1;
        y = rand()%(cols - 2) + 1;
    }while(getValue(x , y) != '.');

    setValue(x,y,label);
    if(label == 'C'){
        setLabel(x,y,'C');
    }
}


void Grid::insert(int x , int y ,char v , char l){
    Node* newNode = new Node(v,l,x,y);
    if(!head){
        head = newNode;
    }
    else{
        Node* current = getNode(x,y);
        if (current){
            current->val = v;
            current->label = l;
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

char Grid::getValue(int x , int y)const{
    Node* current = getNode(x,y);
    return current ? current->val : ' ';
}

void Grid::setValue(int x , int y , char val){
    Node* current = getNode(x , y);
    if(current){
        current->val = val;
    }
}

char Grid::getLabel(int x , int y)const{
    Node* current = getNode(x,y);
    return current ? current->label : ' ';
}

void Grid::setLabel(int x , int y , char l)const{
    Node* current = getNode(x , y);
    if(current){
        current->label = l;
    }
}

Node* Grid::getNode(int x , int y)const{
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

void Grid::displayLabels()const{
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            cout<<getLabel(i,j)<<" ";
        }
        cout<<endl;
    }
}

void Grid::displayValues()const{
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            cout<<getValue(i,j)<<" ";
        }
        cout<<endl;
    }
}

int Grid::getRows()const{
    return rows;
}

int Grid::getCols()const{
    return cols;
}