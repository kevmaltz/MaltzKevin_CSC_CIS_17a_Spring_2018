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
    inline bool XOR(int lh, int rh){return (!(lh && rh)) && (lh || rh);}
    inline bool XOR(bool lh, bool rh){return (!(lh && rh)) && (lh || rh);}
    bool mveVld(Location **, int, int, int, int, Unit *);
    bool isRRopn(Location **, int, int, int, char);
    void combat(Unit *, Location &); //Determines combat results
    void move(Location **, int pTurn);    //Move a piece from one location to another
    void ocpy(Location*, Unit*);    //Occupy a location with the passed Unit, modify displays of location to reflect
    void unOcpy(Location*);         //Remove Unit from passed location, remove unit from displays as well
    std::string frmtCse(std::string);         //Formats string to proper noun capitalization
    int isWnr(int, Unit [], Unit[]);       //Determines if the specified player has won the game
    void wrtLog(std::fstream &, Location**, Unit[], Unit[]);
    void undo(std::fstream &, Location**, Unit [], Unit [], int &);
}

#endif /* PLAY_H */

