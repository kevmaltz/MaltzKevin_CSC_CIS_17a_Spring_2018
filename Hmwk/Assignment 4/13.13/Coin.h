/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Coin.h
 * Author: Kevin Maltz
 *
 * Created on April 4, 2018, 7:20 PM
 */

#ifndef COIN_H
#define COIN_H

#include <string>
using namespace std;

class Coin 
{
    private:
        string sideUp;
    public:
        Coin();
        void toss();
        string getSdUp(){return sideUp;}
};

#endif /* COIN_H */

