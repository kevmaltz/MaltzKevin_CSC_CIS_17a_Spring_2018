/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Display.h
 * Author: Kevin Maltz
 *
 * Created on May 24, 2018, 4:28 PM
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

class Unit;

class Display{
    private:
        char room[5][13];
    public:
        void show();
        void removeUnit();
        void addUnit(std::string);
};

#endif /* DISPLAY_H */

