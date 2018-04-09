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
void initBrd(Location **, fstream &);
void ptBrdLoc(Location **); //test if binary file properly read to board structure array
//Execution begins here

int main(int argc, char** argv) 
{
    fstream setup("setup.dat", ios::in | ios::binary);
    Location **board;   //13x5 board
    board = new Location*[ROW_MX];
    for(int r=0; r < ROW_MX; r++)
    {
        board[r] = new Location[COL_MX];
    }
    if(setup.is_open() && setup.good())
        initBrd(board, setup);
    cout << board[0][0].type << endl;
    ptBrdLoc(board);
    
    for(int r=0; r < ROW_MX; r++)
        delete[] board[r];
        delete [] board;
    
    return 0;
}

void initBrd(Location **board, fstream &setup)
{
    //board = new Location*[ROW_MX];
    for(int r=0; r < ROW_MX; r++)
    {
        //board[r] = new Location[COL_MX];
        for(int c=0; c < COL_MX; c++)
        {
            setup.read(reinterpret_cast<char *>(board[r]+c), sizeof(board[r][c]));
            board[r][c].occUnit = NULL;
            cout << board[r][c].type << " " << board[r][c].isOcp << " "
                 << board[r][c].isRR << " " << board[r][c].occUnit << endl;
        }
    }
}
void ptBrdLoc(Location **brd)
{
    cout << "before first for loop\n";
    for(int r=0; r < ROW_MX; r++)
    {
        cout << "inside for loop #" << r+1 << endl;
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