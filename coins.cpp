#include "coins.h"
#include<iostream>
using namespace std;

coin_history::~coin_history(){
    coin* current = head;
    while (current != NULL) {
        coin* next = current->next;
        delete current;
        current = next;
    }
}

void coin_history::add_coin(int x, int y){
    coin* newCoin = new coin(x,y);
    newCoin->next = head;
    head = newCoin;
}

void coin_history::display_coinHistory(){
    cout<<"Coins Collected : ";
    coin* current = head;
    while(current!=NULL){
        cout << "(" << current->x << ", " << current->y << ") ";
        current = current->next;
    }
    cout<<endl;
}