/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Coin.cpp
 * Author: Kevin Maltz
 * 
 * Created on April 4, 2018, 7:20 PM
 */

#include "Coin.h"

Coin::Coin()
{
    toss();
}
void Coin::toss()
{
    int side;
    side = rand() % 2;
    if(side)
        sideUp = "heads";
    else
        sideUp = "tails";
}