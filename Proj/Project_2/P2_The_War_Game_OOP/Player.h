/* 
 * File:   Player.h
 * Author: Kevin Maltz
 *
 * Created on May 29, 2018, 9:58 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Unit.h"

class Player{
    static int nPlyrs = 0;  //use to assign id value to player
    private:
        std::string name;
        int id;
        Unit *pieces;
    public:
        Player();
        ~Player();
        virtual void play();
};

#endif /* PLAYER_H */

