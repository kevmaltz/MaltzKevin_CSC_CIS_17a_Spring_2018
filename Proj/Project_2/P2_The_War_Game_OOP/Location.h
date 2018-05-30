/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Location.h
 * Author: Kevin Maltz
 *
 * Created on April 21, 2018, 4:57 PM
 */

#ifndef LOCATION_H
#define LOCATION_H

#include "Constants.h"
#include "Unit.h"
#include "Display.h"
//struct Location{
//    char type;      //What type of position is it. Camp/Battlefield/Frontline/Headquarters/Mountain
//    bool isOcp;     //If location occupied, set true
//    bool isRR;      //Set true if location is on railroad line
//    char dsply1[RM_RW][RM_CL]; //Display for player 1
//    char dsply2[RM_RW][RM_CL]; //Display for player 2
//    Unit *occUnit;  //Pointer to unit occupying the location.
//};
class Board;
class Location{
    friend Board;
    protected:
        bool isOcp;
        Display pView[2];
        Unit *occUnit;
        Location **range;
    public:
        Location();
        virtual void ocpy(Unit*);
        virtual void unOcpy();
        
};

#endif /* LOCATION_H */

