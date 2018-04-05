/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Invtry.h"

Invtry::Invtry(int i=0, int q=0, float c=0)    //itmNum, qnty, cost
{
    if(i >= 0)
        itmNum = i;
    if(q >= 0)
        qnty = q;
    if(!(c < 0))
        cost = c;
    setTCst();
}
void Invtry::setItmN(int i)
{
    if(i >= 0)
        itmNum = i;
}
void Invtry::setQnty(int q)
{
    if(q >= 0)
        qnty = q;
    setTCst();
}
void Invtry::setCst(float c)
{
    if(!(c < 0))
        cost = c;
    setTCst();
}