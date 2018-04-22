/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Unit.h
 * Author: Kevin Maltz
 *
 * Created on April 21, 2018, 4:57 PM
 */

#ifndef UNIT_H
#define UNIT_H

#include <string>
struct Unit{
    unsigned short priority;  //The value representing its position on the attack hierarchy, higher is better
    bool inPlay;    //If unit is still in play, set true. When unit leaves play, set false.
    std::string name;    //Name of piece
    int plyrID;     //ID of player who owns the unit.( ID = 1 or ID = 2 )
};

#endif /* UNIT_H */

