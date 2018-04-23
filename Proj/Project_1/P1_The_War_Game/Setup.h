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
    ///Initializes the board using a setup file
    Location **initBrd(std::fstream &);
    ///Initialize data for all pieces(Unit structures)
    void initPcs(std::fstream &, Unit [], Unit []);
    ///Handles game setup options input by player
    void gmeSet(Location**, Unit[], std::string, int);
    ///Setup players board from a config file
    void spdSet(Location**, Unit[], int, std::string);
    ///Get index of matching unit in array, if exists
    int fndMtch(Unit[], std::string);
    ///Sets the player names
    void stPlyrs(std::string &, std::string &);
    ///Allows player to manually setup their pieces
    void setPcs(Location **, Unit [], std::string);
    ///Lists all pieces not yet in play for a single player, for use in manual setup
    void whoNtSt(Unit[]);
}

#endif /* SETUP_H */

