/* 
 * File:   main.cpp
 * Author: Kevin Maltz
 * Created on April 4, 2018, 5:35 PM
 * Purpose: Take three test scores and print out the average score.
 */

//System Libraries
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries
#include "TestScores.h"

//Global Constants - Math, Science, Conversions, 2D Array Sizes

//Function Prototypes

//Execution begins here

int main(int argc, char** argv) 
{
    TestScores scores;
    
    //Set all the test scores
    scores.setScr(1,59);
    scores.setScr(2,100);
    scores.setScr(3,89);
    
    cout << fixed << showpoint << setprecision(2);
    cout << "The average test scores is: " << scores.avgScr() << endl;

    return 0;
}

