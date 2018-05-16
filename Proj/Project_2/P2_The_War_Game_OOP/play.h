/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   play.h
 * Author: Kevin Maltz
 *
 * Created on April 21, 2018, 5:41 PM
 */

#ifndef PLAY_H
#define PLAY_H

#include <string>

#include "Constants.h"
#include "Unit.h"
#include "Location.h"
namespace play{
    ///XOR logic gate, no short circuit behavior
    inline bool XOR(int lh, int rh){return (!(lh && rh)) && (lh || rh);}
    ///XOR logic gate, no short circuit behavior
    inline bool XOR(bool lh, bool rh){return (!(lh && rh)) && (lh || rh);}
    ///Validates movement selection
    bool mveVld(Location **, int, int, int, int, Unit *);
    ///Checks if railroad along selected path if obstacle free
    bool isRRopn(Location **, int, int, int, char);
    ///Determines combat results
    void combat(Unit *, Location &);
    ///Move a piece from one location to another
    void move(Location **, int pTurn);
    ///Occupy a location with the passed Unit, modify displays of location to reflect
    void ocpy(Location*, Unit*);
    ///Remove Unit from passed location, remove unit from displays as well
    void unOcpy(Location*);
    ///Formats string to proper noun capitalization
    std::string frmtCse(std::string);
    ///Determines if the specified player has won the game
    int isWnr(int, Unit [], Unit[]);
    ///Write out the game to a binary log file
    void wrtLog(std::fstream &, Location**, Unit[], Unit[]);
    ///Sets board to an earlier game state as specified by player
    void undo(std::fstream &, Location**, Unit [], Unit [], int &);
}

#endif /* PLAY_H */

