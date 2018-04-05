/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Array.h
 * Author: rcc
 *
 * Created on March 28, 2018, 2:26 PM
 */

#ifndef ARRAY_H
#define ARRAY_H

class Array{
    private:
        int row;
        int col;
        int **data;
    public:
        Array(int,int);
        ~Array();
        int getData(int)const;
        int getSize()const{return row*col;}
};

#endif /* ARRAY_H */

