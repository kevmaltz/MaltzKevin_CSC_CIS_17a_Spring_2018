/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   setup.h
 * Author: Kevin Maltz
 *
 * Created on April 21, 2018, 5:12 PM
 */

#ifndef SETUP_H
#define SETUP_H

#include <fstream>
#include <string>

#include "Constants.h"
#include "Unit.h"
#include "Location.h"
namespace setup{
    Location **initBrd(std::fstream &);  //Initializes the board
    void initPcs(std::fstream &, Unit [], Unit []);  //Initialize data for all pieces(Unit structures)
    void gmeSet(Location**, Unit[], std::string, int);
    void spdSet(Location**, Unit[], int, std::string);    //Setup players board from random config file
    int fndMtch(Unit[], std::string);           //Get index of matching unit in array, if exists
    void stPlyrs(std::string &, std::string &);    //Sets the player names
    void setPcs(Location **, Unit [], std::string);
    void whoNtSt(Unit[]);           //Lists all pieces not yet in play for a single player
}

#endif /* SETUP_H */

