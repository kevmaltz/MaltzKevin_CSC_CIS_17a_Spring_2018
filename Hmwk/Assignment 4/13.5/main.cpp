/* 
 * File:   main.cpp
 * Author: Kevin Maltz
 * Created on April 3, 2018, 5:49 PM
 * Purpose: Show off the ReteailItm class by creating three objects and
 * utilizing the constructor. Reads the desired data from a text file.
 */

//System Libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

//User Libraries
#include "RetailItm.h"

//Global Constants - Math, Science, Conversions, 2D Array Sizes

//Function Prototypes
void prntInv(const vector<RetailItm> inv);

//Execution begins here
int main(int argc, char** argv) 
{
    string desc;    //Item Description
    int units;      //Number of units on hand
    float price;    //Price per unit
    vector <RetailItm> invtry;
    
    fstream fin("data.txt", ios::in); //open a file stream in input mode
    if(!fin.fail()) //If opening the file did not fail, then proceed
    {
        do  //Read in the three peices of data needed for object constructor till eof
        {
        getline(fin,desc);
        fin >> units >> price;
        fin.ignore(1000,'\n');
        invtry.push_back(RetailItm(desc,units,price));
        }while(!fin.eof());
        fin.close();
        //Print out entire inventory
        prntInv(invtry);
    }
        
    return 0;
}

void prntInv(vector<RetailItm> inv)
{
    cout << left << setw(20) << "Description" << setw(20) << "Units on Hand"
         << "Price\n";
    for(int i=0; i < inv.size(); i++)
    {
        cout << setw(20) << inv[i].getDsc() << setw(20) << inv[i].getUnt()
             << inv[i].getPrc() << endl;
    }
}