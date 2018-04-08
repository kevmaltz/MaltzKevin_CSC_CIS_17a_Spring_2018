/* 
 * File:   main.cpp
 * Author: Kevin Maltz
 * Created on April 7, 2018, 1:02 PM
 * Purpose: 
 */

//System Libraries
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//User Libraries
struct Unit
{
    unsigned short priority;  //The value representing its position on the attack hierarchy, higher is better
    bool inPlay;    //If unit is still in play, set true. When unit leaves play, set false.
    string name;    //Name of piece
};
struct Location
{
    string type;    //What type of position is it. Camp/Battlefield/Frontline/Headquarters/Mountain
    bool isOcp;     //If location occupied, set true
    Unit *occUnit;  //Pointer to unit occupying the location.
    bool isRR;      //Set true if location is on railroad line
};

//Global Constants - Math, Science, Conversions, 2D Array Sizes

//Function Prototypes

//Execution begins here

int main(int argc, char** argv) 
{
    fstream txt("txt_input.txt", ios::in);
    fstream bin("Setup.txt", ios::out | ios::binary);
    Location stream; 
    
    do
    {
        txt.read(reinterpret_cast<char *>(&stream), sizeof(stream));
        bin.write(reinterpret_cast<char *>(&stream), sizeof(stream));
    }while(!txt.eof());

    return 0;
}

