/* 
 * File:   Deck.h
 * Author: rcc
 * Created on April 30, 2014, 1:58 PM
 * Specification for the Deck
 */

#ifndef DECK_H
#define	DECK_H

#include "Card.h"

class Deck{
   private:
       Card **card;
       int *index;
       int nCards;
       int nDelt;
   public:
       Deck(int);
       ~Deck(){
           for(int i=0;i<nCards;i++){delete card[i];}
           delete []card;
       }
       void shuffle();
       int *deal(int);
};


#endif	/* DECK_H */

