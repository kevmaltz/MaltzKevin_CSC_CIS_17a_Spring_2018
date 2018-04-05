/* 
 * File:   RetailItm.h
 * Author: Kevin Maltz
 *
 * Created on April 3, 2018, 5:52 PM
 */

#ifndef RETAILITM_H
#define RETAILITM_H

#include <string>
using namespace std;

class RetailItm 
{
    private:
        string desc;    //Item Description
        int units;      //Number of units on hand
        float price;    //Price per unit
    public:
        RetailItm(string, int, float);
        ~RetailItm(){}
        void updtDsc(string);
        string getDsc(){return desc;}const
        void updtUnt(int);
        int getUnt(){return units;}const
        float getPrc(){return price;}const
        void updtPrc(float);
};

#endif /* RETAILITM_H */

