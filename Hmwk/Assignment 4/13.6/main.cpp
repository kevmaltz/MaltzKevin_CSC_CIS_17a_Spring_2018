/* 
 * File:   main.cpp
 * Author: Kevin Maltz
 * Created on April 4, 2018, 10:59 AM
 * Purpose: Show off the Invtry class. Reads inventory from a file, takes one 
 *          away from every item in inventory, and applies a 30% discount to
 *          the entire inventory. Printing out after every change.
 */

//System Libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

//User Libraries
#include "Invtry.h"

//Global Constants - Math, Science, Conversions, 2D Array Sizes

//Function Prototypes
void prntDHdr();
void prntInv(vector<Invtry>);

//Execution begins here

int main(int argc, char** argv) 
{
    int idNum;
    int qnty;
    float price;
    vector<Invtry> invtry;
    
    fstream fin("data.txt", ios::in);
    if(fin.is_open())
    {
        do
        {
            fin >> idNum >> qnty >> price;
            invtry.push_back(Invtry(idNum, qnty, price));            
        }while(!fin.eof());
        fin.close();
    }
    
    //Output the inventory
    prntInv(invtry);
    
    //Remove 1 from every inventory item
    for(int i=0; i < invtry.size(); i++)
    {
        invtry[i].setQnty(invtry[i].getQnty() - 1);
    }
    //Display changed inventory
    cout << endl << endl;
    prntInv(invtry);
    
    //Discount entire inventory 30%
    for(int i=0; i < invtry.size(); i++)
    {
        invtry[i].setCst(invtry[i].getCst() * 0.7);
    }
    //Display discounted inventory
    prntInv(invtry);
    
    return 0;
}

void prntDHdr()
{
    cout << left << setw(5) << "ID #" << right << setw(5) << "Qnty"
         << setw(11) << "Unit Cost" << setw(12) << "Total Cost" << endl;
    cout << left << setw(5) << "----" << right << setw(5) << "----" << setw(11)
         << "---------"<< setw(12) << "----------" << endl;
}

void prntInv(vector<Invtry> invtry)
{
    prntDHdr();
    for(int i=0; i < invtry.size(); i++)
    {
        cout << left << setw(5) << invtry[i].getItmN();
        cout << right << setw(5) << invtry[i].getQnty();
        cout << fixed << showpoint << setprecision(2);
        cout << setw(11) << invtry[i].getCst();
        cout << setw(12) << invtry[i].getTCst();
        cout << endl;
    }
}