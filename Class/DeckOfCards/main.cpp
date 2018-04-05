/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on April 30, 2014, 12:54 PM
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Our Libraries
#include "Card.h"
#include "Deck.h"

//Global Constants

//Function Prototypes
void prntHnd(int *,int);

//Execution Begins Here!
int main(int argc, char** argv) {
    //Initialize the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Create an array of 52 cards
    int nCards=52;
    Deck deck(nCards);
    
    //Deal a hand
    int nDelt=5;
    deck.shuffle();
    int *hand=deck.deal(nDelt);

    //Delete the arrays
    prntHnd(hand,nDelt);
    
    //Exit stage right
    return 0;
}

void prntHnd(int *hand,int n){
    for(int i=0;i<n;i++){
        Card c(hand[i]);
        cout<<c.name()<<c.suit()<<endl;
    }
    delete []hand;
}