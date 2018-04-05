/* 
 * File:   main.cpp
 * Author: Kevin Maltz
 * Created on April 4, 2018, 7:18 PM
 * Purpose: Flip a coin 20 times, then display the number of heads and tails 
 *          results
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries
#include "Coin.h"

//Global Constants - Math, Science, Conversions, 2D Array Sizes

//Function Prototypes

//Execution begins here

int main(int argc, char** argv) 
{
    srand(static_cast<unsigned int>(time(NULL)));
    
    int nFlips = 20;
    Coin coin;
    string result;
    int nHds = 0;
    int nTls = 0;
    
    for(int i=0; i < nFlips; i++)
    {
        coin.toss();
        result = coin.getSdUp();
        cout << "Coin toss is " << result << endl;
        if(result == "heads"){nHds++;}
        else{nTls++;}
    }
    cout << "\nResults\n" << "-------\n";
    cout << "Heads: " << nHds << endl;
    cout << "Tails: " << nTls << endl;
    
    return 0;
}

