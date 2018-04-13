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
    char type;      //What type of position is it. (C)amp/(P)ost/(F)rontline/(H)eadquarters/(M)ountain
    bool isOcp;     //If location occupied, set true
    bool isRR;      //Set true if location is on railroad line
    Unit *occUnit;  //Pointer to unit occupying the location.
};

//Global Constants - Math, Science, Conversions, 2D Array Sizes

//Function Prototypes

//Execution begins here

int main(int argc, char** argv) 
{
    const int NUM_LOC = 65;
    const int ROW_MX = 13;
    const int COL_MX = 5;
    fstream txt("text_input.txt", ios::in);
    fstream bin("Setup.dat", ios::out | ios::binary);
    Location stream[5];
    string ptrRaw;
    string tmpBool;
    
    for(int r=0; r< ROW_MX; r++)
    {
        for(int c=0; c < COL_MX; c++)
        {
            txt.get(stream[c].type);
            txt.ignore(1000,'#');
        }
        txt.ignore(1000, '\n');
        for(int c=0; c < COL_MX; c++)
        {
            getline(txt, tmpBool, '#');
            tmpBool=="0"?stream[c].isOcp = false:stream[c].isOcp=true;
        }
        txt.ignore(1000, '\n');
        for(int c=0; c < COL_MX; c++)
        {
            getline(txt, tmpBool, '#');
            tmpBool=="0"?stream[c].isRR = false:stream[c].isRR=true;
        }
        txt.ignore(1000, '\n');
        for(int c=0; c < COL_MX; c++)
        {
            getline(txt, ptrRaw, '#');
            stream[c].occUnit = NULL;
            /* For use in undo files, DO NOT USE FOR SETUP! pointers are dynamic
            getline(txt, ptrRaw, '#');
                if(ptrRaw == "0" || ptrRaw == "NULL")
                stream[c].occUnit = NULL;
            else
                stream[c].occUnit = reinterpret_cast<Unit*>(strtol(ptrRaw.c_str(),NULL,0));
             */
        }
        txt.ignore(1000, '\n');
        txt.ignore(1000, '\n');
        
        //Write out data to binary file
        bin.write(reinterpret_cast<char *>(&stream), sizeof(stream));
    }
    
    txt.close();
    
    //Write the information for all player pieces to the binary file
    txt.open("pieces.txt", ios::in);
    Unit temp;
    int nmLngth;
    do
    {
    txt >> temp.priority >> temp.inPlay;
    txt.ignore(1000,' ');
    getline(txt, temp.name);
    //Write to binary
    nmLngth = temp.name.length();
    bin.write(reinterpret_cast<char*>(&nmLngth),sizeof(nmLngth));
    bin.write(reinterpret_cast<char*>(&(temp.priority)), sizeof(temp.priority));
    bin.write(reinterpret_cast<char*>(&(temp.inPlay)), sizeof(temp.inPlay));
    bin.write(temp.name.c_str(),nmLngth);
    }while(!txt.eof());
    
    txt.close();
    bin.close();
    
//    Test if pieces.txt correctly written to binary.
//    bin.open("Setup.dat", ios::in | ios::binary);
//    Unit test;
//    char *buf;
//    int tstLngth;
//    int n=0;
//    do
//    {
//        n++;
//        bin.read(reinterpret_cast<char*>(&tstLngth), sizeof(tstLngth));
//        bin.read(reinterpret_cast<char*>(&(test.priority)), sizeof(test.priority));
//        bin.read(reinterpret_cast<char*>(&(test.inPlay)), sizeof(test.inPlay));
//        buf = new char[tstLngth + 1];
//        bin.read(buf,tstLngth);
//        buf[tstLngth] = '\0';
//        test.name = buf;
//        cout << test.priority << " " << test.inPlay << " " << test.name << endl;
//        delete [] buf;
//    }while(n<25);//!bin.eof());
//    
//    bin.close();
    
    return 0;
}

