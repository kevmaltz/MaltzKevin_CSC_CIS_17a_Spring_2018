/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Invtry.h
 * Author: Kevin Maltz
 *
 * Created on April 4, 2018, 11:34 AM
 */

#ifndef INVTRY_H
#define INVTRY_H

class Invtry
{
    private:
        int itmNum;
        int qnty;
        float cost;
        float totCost;  //Cost*Quantity. !Required by problem to be included!
        inline void setTCst(){totCost=qnty*cost;}
    public:
        Invtry(int i, int q, float c);    //itmNum, qnty, cost
        void setItmN(int i);
        void setQnty(int q);
        int getItmN(){return itmNum;}
        int getQnty(){return qnty;}
        float getCst(){return cost;}
        float getTCst(){return totCost;}
        void setCst(float c);
};

#endif /* INVTRY_H */

