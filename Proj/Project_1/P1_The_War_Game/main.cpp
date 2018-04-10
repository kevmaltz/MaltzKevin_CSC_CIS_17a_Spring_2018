/* 
 * File:   main.cpp
 * Author: Kevin Maltz
 * Created on April 6, 2018, 8:43 PM
 * Purpose: 
 */

//System Libraries
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
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
    char type;      //What type of position is it. Camp/Battlefield/Frontline/Headquarters/Mountain
    bool isOcp;     //If location occupied, set true
    bool isRR;      //Set true if location is on railroad line
    Unit *occUnit;  //Pointer to unit occupying the location.
};

//Global Constants - Math, Science, Conversions, 2D Array Sizes
const short ROW_MX = 13;
const short COL_MX = 5;
//Function Prototypes
Location **initBrd(fstream &);
void ptBrdLoc(Location **); //test if binary file properly read to board structure array

//Execution begins here
int main(int argc, char** argv) 
{
    fstream setup("setup.dat", ios::in | ios::binary);
    Location **board;   //13x5 board
    if(setup.is_open() && setup.good())
    {
        board = initBrd(setup);
        setup.close();
    }
    else
    {
        cout << "ERROR: unable to open file Setut.dat, exiting program\n";
        return EXIT_FAILURE;
    }
    ptBrdLoc(board);
    
    for(int r=0; r < ROW_MX; r++)
        delete[] board[r];
        delete [] board;
    
    return EXIT_SUCCESS;
}

Location **initBrd(fstream &setup)
{
    Location **board;
    board = new Location*[ROW_MX];
    for(int r=0; r < ROW_MX; r++)
    {
        board[r] = new Location[COL_MX];
        for(int c=0; c < COL_MX; c++)
        {
            setup.read(reinterpret_cast<char *>(board[r]+c), sizeof(board[r][c]));
            board[r][c].occUnit = NULL;
        }
    }
    return board;
}
void ptBrdLoc(Location **brd)
{
    for(int r=0; r < ROW_MX; r++)
    {
        for(int c=0; c < COL_MX; c++)
            cout << brd[r][c].type << " ";
        cout << endl;
        for(int c=0; c < COL_MX; c++)
            cout << brd[r][c].isOcp << " ";
        cout << endl;
        for(int c=0; c < COL_MX; c++)
            cout << brd[r][c].isRR << " ";
        cout << endl;
        for(int c=0; c < COL_MX; c++)
            cout << brd[r][c].occUnit << " ";
        cout << endl;
    }
}