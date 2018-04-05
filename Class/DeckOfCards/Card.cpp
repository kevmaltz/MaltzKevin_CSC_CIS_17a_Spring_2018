/* 
 * File:   Card.h
 * Author: Dr. Mark E. Lehr
 * Created on April 30, 2014, 12:56 PM
 * Card Implementation
 */

#include "Card.h"

//Implement the Constructor
Card::Card(int number){
    if(number<0)number=0;
    if(number>51)number%=52;
    this->number=static_cast<char>(number);
}

char Card::suit(){
    if(number<13)return 'S';
    if(number<26)return 'H';
    if(number<39)return 'C';
    return 'D';
}

char Card::name(){
    char aName[]={'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    return aName[number%13];
}

char Card::value(){
    char n=number%13+1;
    if(n>10)return 10;
    return n;
}
