#ifndef COINS
#define COINS

#include<iostream>
using namespace std;

class coin_history{
    public:
    struct coin{
        int x;
        int y;
        coin* next;
        coin(int x, int y):x(x) , y(y), next(NULL){}
    };

    coin* head;
    coin_history():head(NULL){}
    ~coin_history();
    void add_coin(int x, int y);
    void display_coinHistory();
};


#endif