/* 
 * File:   main.cpp
 * Author: Kevin Maltz
 * Created on April 4, 2018, 8:13 PM
 * Purpose: Play a coin game. Toss a Quarter, Dime and Nickel, if heads comes
 *          up then add the coin value to your balance. Stop flipping coins when
 *          you get to or go over the winning value threshold. Win if balance
 *          is equal to winning value threshold, loss if player went over.
 */

//System Libraries
#include <iostream>
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
    
    const int Q_VAL = 25;   //Cent value of a Quarter
    const int D_VAL = 10;   //Cent value of a Dime
    const int N_VAL = 5;    //Cent value of a Nickel
    const int WIN_BAL = 100;//Balance value to end the game and check for a win
    
    Coin qrtr;              //Quarter
    Coin dime;              //Dime
    Coin nickl;             //Nickel
    int balance = 0;        //Balance in USD cents
    
    do
    {
        //Toss the coins
        qrtr.toss();
        dime.toss();
        nickl.toss();
        //Check the results
        if(qrtr.getSdUp() == "heads")
        {
            cout << "Quarter came up heads, adding " << Q_VAL
                 << " cents to the balance\n";
            balance += Q_VAL;
        }
        else
            cout << "Quarter came up tails\n";
        if(dime.getSdUp() == "heads")
        {
            cout << "Dime came up heads, adding " << D_VAL
                 << " cents to the balance\n";
            balance += D_VAL;
        }
        else
            cout << "Dime came up tails\n";
        if(nickl.getSdUp() == "heads")
        {
            cout << "Nickel came up heads, adding " << N_VAL
                 << " cents to the balance\n";
            balance += N_VAL;
        }
        else
            cout << "Nickel came up tails\n";
        cout << "Balance is currently: " << balance << " cents\n\n";
    }while(balance < WIN_BAL);
    
    if(balance == WIN_BAL)
        cout << "Congratulations! You won! You're balance is exactly "
             << balance << " cents.\n";
    else if (balance == (WIN_BAL + Q_VAL + D_VAL + N_VAL - 5))
        cout << "Big loss! You have the worst luck today!/n"
             << "Seriously, don't leave your house.\n";
    else if(balance > WIN_BAL)
        cout << "You don't have that much luck, your coins overshot the win by "
             << balance - WIN_BAL << " cents\n.";
    else
        cout << "I don't know how you got here, you should still be playing O_O"
             << endl;
    
    return 0;
}

