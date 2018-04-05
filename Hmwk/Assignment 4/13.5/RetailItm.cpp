
/* 
 * File:   RetailItm.cpp
 * Author: Kevin Maltz
 * 
 * Created on April 3, 2018, 5:52 PM
 */

#include "RetailItm.h"

RetailItm::RetailItm(string d="No Description", int u=0, float p=0.0) 
{
    if(d.length() != 0)
        desc = d;
    if(u >= 0)
        units = u;
    if(p > 0)
        price = p;
}
void RetailItm::updtDsc(string d)
{
    if(d.length() != 0)
        desc = d;
}
void RetailItm::updtUnt(int u)
{
    if(u >= 0)
        units = u;
}
void RetailItm::updtPrc(float p)
{
    if(p > 0)
        price = p;
}
