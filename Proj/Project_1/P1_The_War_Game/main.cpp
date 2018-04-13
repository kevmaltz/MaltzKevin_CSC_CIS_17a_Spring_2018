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
const int N_PCS = 25;

//Function Prototypes
Location **initBrd(fstream &);
void initPcs(fstream &, Unit [], Unit []);
void ptBrdLoc(Location **); //test if binary file properly read to board structure array
void ptPlyrs(Unit [], Unit []);

//Execution begins here
int main(int argc, char** argv) 
{
    int nPlyr = 0;
    string plyr1;
    string plyr2;
    bool ai = false;
    unsigned int turn = 0;  //The current turn number. Increments +1 every turn
    
    fstream setup("setup.dat", ios::in | ios::binary);
    Location **board;   //13x5 board
    Unit p1Pcs[N_PCS];
    Unit p2Pcs[N_PCS];
//    int nmLngth;
//    char* buf;
    if(setup.is_open() && setup.good())
    {
        board = initBrd(setup);
        initPcs(setup, p1Pcs, p2Pcs);
        //Read in data for each piece, copy p1Pcs to p2Pcs after each read
//        for(int i=0; i < N_PCS; i++)
//        {
//            setup.read(reinterpret_cast<char*>(&nmLngth), sizeof(nmLngth));
//            setup.read(reinterpret_cast<char*>(&(p1Pcs[i].priority)), sizeof(p1Pcs[i].priority));
//            setup.read(reinterpret_cast<char*>(&(p1Pcs[i].inPlay)), sizeof(p1Pcs[i].inPlay));
//            buf = new char[nmLngth + 1];
//            setup.read(buf,nmLngth);
//            buf[nmLngth] = '\0';
//            p1Pcs[i].name = buf;
//            p2Pcs[i].priority = p1Pcs[i].priority;
//            p2Pcs[i].inPlay = p1Pcs[i].inPlay;
//            p2Pcs[i].name = p1Pcs[i].name;
//            delete [] buf;
//        }
        setup.close();
    }
    else    //Return exit failure if setup file fails to open.
    {
        cout << "ERROR: unable to open file Setut.dat, exiting program\n";
        return EXIT_FAILURE;
    }
    ptBrdLoc(board);
    ptPlyrs(p1Pcs, p2Pcs);
    
    cout << "Enter number of players(2 max): ";
    cin >> nPlyr;
    while(nPlyr != 1 && nPlyr != 2)
    {
        cout << "Invalid number of player. Re-enter(max 2): ";
        cin >> nPlyr;
    }
    if(nPlyr == 1)
    {
        cin.ignore(1000, '\n');
        cout << "Enter player name: ";
        getline(cin, plyr1);
        plyr2 = "computer";
        ai = true;
    }
    if(nPlyr == 2)
    {
        cin.ignore(1000, '\n');
        cout << "Enter player 1's name: ";
        getline(cin, plyr1);
        cout << "Enter player 2's name: ";
        getline(cin, plyr2);
    }
    //TODO - Allow players to set up pieces
    
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
        {   //Read in binary data to a location structure
            setup.read(reinterpret_cast<char *>(board[r]+c), sizeof(board[r][c]));
            //Ensure all Unit* set to NULL. Ensures no bad memory read in from file
            board[r][c].occUnit = NULL;
        }
    }
    return board;
}


void initPcs(fstream &setup, Unit p1[], Unit p2[])
{
    int nmLngth;
    char* buf;
    for(int i=0; i < N_PCS; i++)
        {
            setup.read(reinterpret_cast<char*>(&nmLngth), sizeof(nmLngth));
            setup.read(reinterpret_cast<char*>(&(p1[i].priority)), sizeof(p1[i].priority));
            setup.read(reinterpret_cast<char*>(&(p1[i].inPlay)), sizeof(p1[i].inPlay));
            buf = new char[nmLngth + 1];
            setup.read(buf,nmLngth);
            buf[nmLngth] = '\0';
            p1[i].name = buf;
            p2[i].priority = p1[i].priority;
            p2[i].inPlay = p1[i].inPlay;
            p2[i].name = p1[i].name;
            delete [] buf;
        }
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
void ptPlyrs(Unit p1[], Unit p2[])
{
    for(int i=0; i < N_PCS; i++)
    {
        cout << "P1: " << p1[i].priority << " " << p1[i].inPlay << " " << p1[i].name << endl;
        cout << "P2: " << p2[i].priority << " " << p2[i].inPlay << " " << p2[i].name << endl;
    }
}