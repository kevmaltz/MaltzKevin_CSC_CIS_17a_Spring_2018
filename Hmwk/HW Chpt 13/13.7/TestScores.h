/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestScores.h
 * Author: Kevin Maltz
 *
 * Created on April 4, 2018, 5:35 PM
 */

#ifndef TESTSCORES_H
#define TESTSCORES_H

class TestScores 
{
    private:
        static const int N_TST = 3;
        int scores[N_TST];
    public:
        TestScores(){}
        int getScr(int tstNum);
        void setScr(int tstNum, int score);
        float avgScr();
};

#endif /* TESTSCORES_H */

