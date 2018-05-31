/* 
 * File:   Board.h
 * Author: Kevin Maltz
 *
 * Created on May 29, 2018, 9:57 PM
 */

#ifndef BOARD_H
#define BOARD_H

#include "Location.h"
#include "Player.h"

class Board{
    friend Player;
    protected:
        Location **board;
        void combat();
    public:
        Board();
        ~Board();
        ///Occupy a location with the passed Unit, modify displays of location to reflect
        void ocpy(Location*, Unit*);
        ///Remove Unit from passed location, remove unit from displays as well
        void unOcpy(Location*);
        void dsplBrd(int);
};

#endif /* BOARD_H */

