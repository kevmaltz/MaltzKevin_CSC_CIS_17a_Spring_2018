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
    bool isRR;      //Set true if location is on railroad line
    Unit *occUnit;  //Pointer to unit occupying the location.
};

//Global Constants - Math, Science, Conversions, 2D Array Sizes

//Function Prototypes

//Execution begins here

int main(int argc, char** argv) 
{
    fstream txt("text_input.txt", ios::in);
    fstream bin("Setup.dat", ios::out | ios::binary);
    Location stream;
    string ptrRaw;
    string tmpBool;
    
    do
    {
        //Get data from text file
        getline(txt, stream.type);
        getline(txt, tmpBool);
        tmpBool=="0"?stream.isOcp = false:stream.isOcp=true;
        getline(txt, tmpBool);
        tmpBool=="0"?stream.isRR = false:stream.isRR=true;
        getline(txt, ptrRaw);
        if(ptrRaw == "0" || ptrRaw == "NULL")
            stream.occUnit = NULL;
        else
            stream.occUnit = reinterpret_cast<Unit*>(strtol(ptrRaw.c_str(),NULL,0));
        
        //Write out data to binary file
        bin.write(reinterpret_cast<char *>(&stream), sizeof(stream));
    }while(!txt.eof());
    
    txt.close();
    bin.close();

    return 0;
}

