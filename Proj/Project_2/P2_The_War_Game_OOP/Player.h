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
    static int nPlyrs = 0;
    static Unit **pieces = nullptr;
    private:
        std::string name;
        int id;
        //Unit *pieces;
    public:
        Player();
        ~Player();
        virtual void move();
};

#endif /* PLAYER_H */

