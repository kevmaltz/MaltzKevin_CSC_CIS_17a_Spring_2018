/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestScores.cpp
 * Author: Kevin Maltz
 * 
 * Created on April 4, 2018, 5:35 PM
 */
#include <iostream>
#include "TestScores.h"
using namespace std;

void TestScores::setScr(int tstNum, int score)
{
    if(tstNum > 0 && tstNum <= N_TST)
    {
        if(score >= 0 && score <=100)
            scores[tstNum - 1] = score;
        else
            cout << "Invalid score\n";
    }
    else
        cout << "Invalid Test Number\n";
}

int TestScores::getScr(int tstNum)
{
    if(tstNum > 0 && tstNum <= N_TST)
        return scores[tstNum - 1];
    else
        return -1;
}

float TestScores::avgScr()
{
    float total = 0;
    for(int i=0; i < N_TST; i++)
        total += scores[i];
    return total / N_TST;
}