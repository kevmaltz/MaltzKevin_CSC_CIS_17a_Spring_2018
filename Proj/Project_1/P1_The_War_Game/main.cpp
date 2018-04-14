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
Location **initBrd(fstream &);  //Initializes the board
void initPcs(fstream &, Unit [], Unit []);  //Initialize data for all pieces(Unit structures)
int stPlyrs(string &, string &, bool &);    //Sets the players and their names, returns number of human players
void ptBrdLoc(Location **); //Test if binary file properly read to board structure array
void ptPlyrs(Unit [], Unit []); //Test if player pieces read in successfully

//Execution begins here
int main(int argc, char** argv) 
{
    int nPlyr;
    string plyr1;
    string plyr2;
    bool ai = false;
    unsigned int turn = 0;  //The current turn number. Increments +1 every turn
    
    fstream setup("setup.dat", ios::in | ios::binary);
    Location **board;   //13x5 board
    Unit p1Pcs[N_PCS];
    Unit p2Pcs[N_PCS];
    
    if(setup.is_open() && setup.good())
    {
        //Read in data for every location on the board
        board = initBrd(setup);
        //Read in data for each piece
        initPcs(setup, p1Pcs, p2Pcs);
        
        setup.close();
    }
    else    //Return exit failure if setup file fails to open.
    {
        cout << "ERROR: unable to open file Setut.dat, exiting program\n";
        return EXIT_FAILURE;
    }
    
    //Set player(s) and return number of human players
    nPlyr = stPlyrs(plyr1, plyr2, ai);
    //TODO - Display the board, right now with no pieces.
    //TODO - Allow players to set up pieces
    string slctn;   //piece selection entered by player
    int mtchInd;    //Index of Unit.name in pxPcs that matches slctn. -1 sentinel value
    bool allSet;    //Stays true if all pieces have been set on the board
    //player 1 piece setup
    cout << "Place your pieces on the board.\n";
    do
    {
        allSet = true;
        mtchInd = -1;
        cout << "Unplaced pieces:\n";
        for(int i=0; i < N_PCS; i++)
        {
            if(p1Pcs[i].inPlay == false)
                cout << p1Pcs[i].name << endl;
        }
        //Prompt for choice of piece
        cout << "Select a piece by typing in the name: ";
        getline(cin, slctn);
        //Convert string to proper case formatting
        slctn[0] = toupper(slctn[0]);
        for(int i=1; i<slctn.length(); i++)
            slctn[i] = tolower(slctn[i]);
        //Proper capitalization for Field Marshal
        if(slctn.length() == 13)
            slctn[6] = toupper(slctn[6]);
        //Check if selection is valid. If valid store index of selected unit
        for(int i=0; i < N_PCS; i++)
        {
            if(p1Pcs[i].inPlay == false)
                if(p1Pcs[i].name == slctn)
                    mtchInd = i;
        }
        //If no valid match found notify player and restart loop from top
        if(mtchInd == -1)
        {
            cout << "Invalid selection\n";
            allSet = false;
            continue;
        }
        cout << "made it past continue statement on invalid input\n";
        for(int i=0; i < N_PCS; i++)
        {
            if(p1Pcs[i].inPlay == false)
                allSet = false;
        }
    }while(!allSet);    //TODO - write algorithm for placing pieces, otherwise infinite loop
    //player 2 piece setup
    
    
    
    
    
    
    
    
    //Cleanup
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
    int nmLngth;    //Length of string to be read in from binary, minus the null
    char* buf;      //Buffer for reading in a string from the binary file
    for(int i=0; i < N_PCS; i++)
        {
            setup.read(reinterpret_cast<char*>(&nmLngth), sizeof(nmLngth));
            setup.read(reinterpret_cast<char*>(&(p1[i].priority)), sizeof(p1[i].priority));
            setup.read(reinterpret_cast<char*>(&(p1[i].inPlay)), sizeof(p1[i].inPlay));
            buf = new char[nmLngth + 1];
            setup.read(buf,nmLngth);
            buf[nmLngth] = '\0';
            p1[i].name = buf;
            //Copy over Unit structure from p1 to p2
            p2[i].priority = p1[i].priority;
            p2[i].inPlay = p1[i].inPlay;
            p2[i].name = p1[i].name;
            //Release memory before next iteration to prevent memory leaks
            delete [] buf;
        }
}
int stPlyrs(string &plyr1, string &plyr2, bool &plyNPC)
{
    int nPlyr = 0;
    
    cout << "2 player game or 1 player vs AI available\n";
    cout << "Enter number of players(2 max): ";
    cin >> nPlyr;
    cin.ignore(1000, '\n');
    while(nPlyr != 1 && nPlyr != 2)
    {
        cout << "Invalid number of player. Re-enter(max 2): ";
        cin >> nPlyr;
        cin.ignore(1000, '\n');
    }
    if(nPlyr == 1)
    {
        cout << "Enter player name: ";
        getline(cin, plyr1);
        plyr2 = "NPC";
        plyNPC = true;
    }
    if(nPlyr == 2)
    {
        cout << "Enter player 1's name: ";
        getline(cin, plyr1);
        cout << "Enter player 2's name: ";
        getline(cin, plyr2);
    }
    return nPlyr;
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