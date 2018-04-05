
/* 
 * File:   Deck.h
 * Author: rcc
 * Created on April 30, 2014, 1:58 PM
 * Specification for the Deck
 */

#include "Deck.h"

#include <cstdlib>
using namespace std;

Deck::Deck(int numCards){
    //Create an array of 52 cards
    nCards=numCards;
    card=new Card*[nCards];
    //Allocate the index;
    index=new int[nCards];
    //Check out all the cards
    for(int i=0;i<nCards;i++){
        card[i]=new Card(i%52);
        index[i]=i;
    }
    nDelt=0;
}

void Deck::shuffle(){
    for(int shfl=1;shfl<=7;shfl++){
        for(int nCard=0;nCard<nCards;nCard++){
            int random=rand()%nCards;//[0,nCards-1]
            int temp=index[nCard];
            index[nCard]=index[random];
            index[random]=temp; 
        }
    }
}

int *Deck::deal(int n){
    int *hand=new int[n];
    for(int i=nDelt;i<nDelt+n;i++){
        hand[i]=index[i];
    }
    nDelt+=n;
    return hand;
}