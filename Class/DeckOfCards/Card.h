/* 
 * File:   Card.h
 * Author: Dr. Mark E. Lehr
 * Created on April 30, 2014, 12:56 PM
 * Card Specification
 */

#ifndef CARD_H
#define	CARD_H

class Card{
   private:
       char number;
   public:
       Card(int);
       char suit();
       char name();
       char value();
       char getNumber(){return number;}
};


#endif	/* CARD_H */

