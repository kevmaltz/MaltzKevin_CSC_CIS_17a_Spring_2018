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
    int plyrID;     //ID of player who owns the unit.( ID = 1 or ID = 2 )
};
struct Location
{
    char type;      //What type of position is it. Camp/Battlefield/Frontline/Headquarters/Mountain
    bool isOcp;     //If location occupied, set true
    bool isRR;      //Set true if location is on railroad line
    char dsply1[5][13]; //Display for player 1
    char dsply2[5][13]; //Display for player 2
    Unit *occUnit;  //Pointer to unit occupying the location.
};

//Global Constants - Math, Science, Conversions, 2D Array Sizes
const short ROW_MX = 13;
const short COL_MX = 5;
const int N_PCS = 25;
const int RM_CL = 13;   //Must be = to the c of Location.dsply[r][c]
const int RM_RW = 5;    //Must be = to the r of Location.dsply[r][c]

//Function Prototypes
Location **initBrd(fstream &);  //Initializes the board
void initPcs(fstream &, Unit [], Unit []);  //Initialize data for all pieces(Unit structures)
int stPlyrs(string &, string &, bool &);    //Sets the players and their names, returns number of human players
void setPcs(Location **, Unit [], string);
void ocpy(Location*, Unit*);    //Occupy a location with the passed Unit, modify displays of location to reflect
void unOcpy(Location*);         //Remove Unit from passed location, remove unit from displays as well
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
    
    /*SET PIECES ON BOARD*/
    string slctn;   //piece selection entered by player
    int mtchInd;    //Index of Unit.name in pxPcs that matches slctn. -1 sentinel value
    bool allSet;    //Stays true if all pieces have been set on the board
    int slctR, slctC;   //selected row and column of location to place a piece
    bool locGd;     //Set true if entered location is valid
    char rpPc;      //Choice to replace a piece if location is already occupied
    bool repeat;    //General boolean to use if loops need repeating
    const int R_MX_P1 = 5;  //Maximum row index player 1 can set pieces at
    const int R_MN_P2 = 7;  //Minimum row index player 2 can set pieces at
    //player 1 piece setup
    setPcs(board, p1Pcs, plyr1);
//    cout << plyr1 << " place your pieces on the board.\n";
//    do
//    {
//        allSet = true;
//        mtchInd = -1;
//        cout << "Unplaced pieces:\n";
//        for(int i=0; i < N_PCS; i++)
//        {
//            if(p1Pcs[i].inPlay == false)
//                cout << p1Pcs[i].name << endl;
//        }
//        
//        do
//        {
//            repeat = false;
//            //Prompt for choice of piece
//            cout << "Select a piece by typing in the name: ";
//            getline(cin, slctn);
//
//            //Convert string to proper case formatting
//            slctn[0] = toupper(slctn[0]);
//            for(int i=1; i<slctn.length(); i++)
//                slctn[i] = tolower(slctn[i]);
//
//            //Proper capitalization for Field Marshal
//            if(slctn.length() == 13)
//                slctn[6] = toupper(slctn[6]);
//
//            //Check if piece selection is valid. If valid store index of selected unit
//            for(int i=0; i < N_PCS; i++)
//            {
//                if(p1Pcs[i].inPlay == false)
//                    if(p1Pcs[i].name == slctn)
//                    {
//                        mtchInd = i;
//                        break;
//                    }
//            }
//
//            //If no valid match found notify player and restart loop from top
//            if(mtchInd == -1)
//            {
//                cout << "Invalid selection\n";
//                repeat = true;
//            }
//        }while(repeat);
//        
//        //Setup pieces on board
//        do
//        {
//            repeat = false;
//            do  //Get and validate location selection. Repeats till location is valid
//            {
//                slctR = slctC = -1;
//                cout << "Enter row,column to select a location to place the " << p1Pcs[mtchInd].name 
//                     <<": ";
//                //TODO - change this to use a stringstream to catch any error in the way user inputs numbers
//                cin >> slctR; cin.ignore(1000,','); 
//                cin >> slctC; cin.ignore(1000,'\n');
//                if(slctR < 0 || slctR > R_MX_P1)
//                {
//                    locGd = false;
//                    cout << "Invalid location\n";
//                }
//                else if(slctC < 0 || slctC >= COL_MX)
//                {
//                    locGd = false;
//                    cout << "Invalid location\n";
//                }
//            }while(locGd == false);
//            
//            //Check if chosen location is already occupied, decide what to do
//            if(board[slctR][slctC].occUnit != NULL)
//            {
//                cout << board[slctR][slctC].occUnit->name
//                     << " is already at that location.\nDo you wish to replace it with "
//                     << p1Pcs[mtchInd].name << "? Enter Y or N: ";
//                cin >> rpPc; cin.ignore(1000,'\n');
//                
//                //Repeat location selection process if no, replace piece otherwise
//                if(rpPc == 'n' || rpPc == 'N')
//                    repeat = true;
//                else if(rpPc == 'y' || rpPc == 'Y')
//                    unOcpy(&board[slctR][slctC]);
//                    //board[slctR][slctC].occUnit->inPlay = false;
//                else
//                {
//                    cout << "Invalid entry. Replacing piece anyways.\n";
//                    unOcpy(&board[slctR][slctC]);
//                    //board[slctR][slctC].occUnit->inPlay = false;
//                }
//            }
//        }while(repeat);
//        ocpy(&board[slctR][slctC], &p1Pcs[mtchInd]);
////        board[slctR][slctC].occUnit = &p1Pcs[mtchInd];
////        board[slctR][slctC].occUnit->inPlay = true;
//        
//        //If any pieces are not yet set in play, allSet=false and loop setup
//        for(int i=0; i < N_PCS && allSet; i++)
//            if(p1Pcs[i].inPlay == false)
//                allSet = false;
//    }while(!allSet);
//   
            
    //player 2 piece setup
    setPcs(board, p2Pcs, plyr2);
//    cout << plyr2 << " place your pieces on the board.\n";
//    do
//    {
//        allSet = true;
//        mtchInd = -1;
//        cout << "Unplaced pieces:\n";
//        for(int i=0; i < N_PCS; i++)
//        {
//            if(p2Pcs[i].inPlay == false)
//                cout << p2Pcs[i].name << endl;
//        }
//        
//        do
//        {
//            repeat = false;
//            //Prompt for choice of piece
//            cout << "Select a piece by typing in the name: ";
//            getline(cin, slctn);
//
//            //Convert string to proper case formatting
//            slctn[0] = toupper(slctn[0]);
//            for(int i=1; i<slctn.length(); i++)
//                slctn[i] = tolower(slctn[i]);
//
//            //Proper capitalization for Field Marshal
//            if(slctn.length() == 13)
//                slctn[6] = toupper(slctn[6]);
//
//            //Check if piece selection is valid. If valid store index of selected unit
//            for(int i=0; i < N_PCS; i++)
//            {
//                if(p2Pcs[i].inPlay == false)
//                    if(p2Pcs[i].name == slctn)
//                    {
//                        mtchInd = i;
//                        break;
//                    }
//            }
//
//            //If no valid match found notify player and restart loop from top
//            if(mtchInd == -1)
//            {
//                cout << "Invalid selection\n";
//                repeat = true;
//            }
//        }while(repeat);
//        
//        //Setup pieces on board
//        do
//        {
//            repeat = false;
//            do  //Get and validate location selection. Repeats till location is valid
//            {
//                slctR = slctC = -1;
//                cout << "Enter row,column to select a location to place the " << p2Pcs[mtchInd].name 
//                     <<": ";
//                //TODO - change this to use a stringstream to catch any error in the way user inputs numbers
//                cin >> slctR; cin.ignore(1000,','); 
//                cin >> slctC; cin.ignore(1000,'\n');
//                if(slctR < R_MN_P2 || slctR >= ROW_MX)
//                {
//                    locGd = false;
//                    cout << "Invalid location\n";
//                }
//                else if(slctC < 0 || slctC >= COL_MX)
//                {
//                    locGd = false;
//                    cout << "Invalid location\n";
//                }
//            }while(locGd == false);
//            
//            //Check if chosen location is already occupied, decide what to do
//            if(board[slctR][slctC].occUnit != NULL)
//            {
//                cout << board[slctR][slctC].occUnit->name
//                     << " is already at that location.\nDo you wish to replace it with "
//                     << p2Pcs[mtchInd].name << "? Enter Y or N: ";
//                cin >> rpPc; cin.ignore(1000,'\n');
//                
//                //Repeat location selection process if no, replace piece otherwise
//                if(rpPc == 'n' || rpPc == 'N')
//                    repeat = true;
//                else if(rpPc == 'y' || rpPc == 'Y')
//                    unOcpy(&board[slctR][slctC]);
//                    //board[slctR][slctC].occUnit->inPlay = false;
//                else
//                {
//                    cout << "Invalid entry. Replacing piece anyways.\n";
//                    unOcpy(&board[slctR][slctC]);
//                    //board[slctR][slctC].occUnit->inPlay = false;
//                }
//            }
//        }while(repeat);
//        ocpy(&board[slctR][slctC], &p2Pcs[mtchInd]);
////        board[slctR][slctC].occUnit = &p2Pcs[mtchInd];
////        board[slctR][slctC].occUnit->inPlay = true;
//        
//        //If any pieces are not yet set in play, allSet=false and loop setup
//        for(int i=0; i < N_PCS && allSet; i++)
//            if(p2Pcs[i].inPlay == false)
//                allSet = false;
//    }while(!allSet);
    
    
    
    
    
    
    
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
            
            //Set ownership of pieces
            p1[i].plyrID = 1;
            p2[i].plyrID = 2;
            
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
void setPcs(Location **board, Unit pcs[], string pNme)
{
    string slctn;   //piece selection entered by player
    int mtchInd;    //Index of Unit.name in pxPcs that matches slctn. -1 sentinel value
    bool allSet;    //Stays true if all pieces have been set on the board
    int slctR, slctC;   //selected row and column of location to place a piece
    char rpPc;      //Choice to replace a piece if location is already occupied
    bool repeat;    //General boolean to use if loops need repeating
    const int R_MX_P1 = 5;  //Maximum row index player 1 can set pieces at
    const int R_MN_P2 = 7;  //Minimum row index player 2 can set pieces at
    int id = pcs[0].plyrID;
    
    
    cout << pNme << " place your pieces on the board.\n";
    do
    {
        allSet = true;
        mtchInd = -1;
        cout << "Unplaced pieces:\n";
        for(int i=0; i < N_PCS; i++)
        {
            if(pcs[i].inPlay == false)
                cout << pcs[i].name << endl;
        }
        
        do
        {
            repeat = false;
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

            //Check if piece selection is valid. If valid store index of selected unit
            for(int i=0; i < N_PCS; i++)
            {
                if(pcs[i].inPlay == false)
                    if(pcs[i].name == slctn)
                    {
                        mtchInd = i;
                        break;
                    }
            }

            //If no valid match found notify player and restart loop from top
            if(mtchInd == -1)
            {
                cout << "Invalid selection\n";
                repeat = true;
            }
        }while(repeat);
        
        //Setup pieces on board
        do
        {
            repeat = false;;
            do  //Get and validate location selection. Repeats till location is valid
            {
                repeat = false;
                slctR = slctC = -1;
                cout << "Enter row,column( #,# ) to select a location to place the " 
                     << pcs[mtchInd].name << ": ";
                //TODO - change this to use a stringstream to catch any error in the way user inputs numbers
                cin >> slctR; cin.ignore(1000,','); 
                cin >> slctC; cin.ignore(1000,'\n');
                if(id == 1 && slctR < 0 || slctR > R_MX_P1)
                {
                    repeat = true;
                    cout << "Invalid location\n";
                }
                else if(id == 2 && slctR < R_MN_P2 || slctR >= ROW_MX)
                {
                    repeat = true;
                    cout << "Invalid location\n";
                }
                else if(slctC < 0 || slctC >= COL_MX)
                {
                    repeat = true;
                    cout << "Invalid location\n";
                }
            }while(repeat);
            
            //Check if chosen location is already occupied, decide what to do
            if(board[slctR][slctC].occUnit != NULL)
            {
                cout << board[slctR][slctC].occUnit->name
                     << " is already at that location.\nDo you wish to replace it with "
                     << pcs[mtchInd].name << "? Enter Y or N: ";
                cin >> rpPc; cin.ignore(1000,'\n');
                
                //Repeat location selection process if no, replace piece otherwise
                if(rpPc == 'n' || rpPc == 'N')
                    repeat = true;
                else if(rpPc == 'y' || rpPc == 'Y')
                    unOcpy(&board[slctR][slctC]);
                else
                {
                    cout << "Invalid entry. Replacing piece anyways.\n";
                    unOcpy(&board[slctR][slctC]);
                }
            }
        }while(repeat);
        ocpy(&board[slctR][slctC], &pcs[mtchInd]);
        
        //If any pieces are not yet set in play, allSet=false and loop setup
        for(int i=0; i < N_PCS && allSet; i++)
            if(pcs[i].inPlay == false)
                allSet = false;
    }while(!allSet);
}
void ocpy(Location* loc, Unit* unit)
{
    loc->isOcp = true;
    loc->occUnit = unit;
    unit->inPlay = true;
    if(unit->plyrID == 1)
    {
        if(unit->name == "Field Marshal")
            for(int c=0; c < 7; c++)
                loc->dsply1[2][2+c] = unit->name[6+c];
        else
            for(int c=0; c < unit->name.length(); c++)
                loc->dsply1[2][2+c] = unit->name[c];
        for(int c=2; c < RM_CL-2; c++)
            loc->dsply2[2][c] = '?';
            
    }
    else
    {
        if(unit->name == "Field Marshal")
            for(int c=0; c < 7; c++)
                loc->dsply2[2][2+c] = unit->name[6+c];
        else
            for(int c=0; c < unit->name.length(); c++)
                loc->dsply2[2][2+c] = unit->name[c];
        for(int c=2; c < RM_CL-2; c++)
            loc->dsply1[2][c] = '?';
    }
}
void unOcpy(Location* loc)
{
    loc->occUnit->inPlay = false;
    loc->occUnit = NULL;
    loc->isOcp = false;
    for(int r=1; r < RM_RW-1; r++)
        for(int c=1; c < RM_CL-1; c++)
        {
            loc->dsply1[r][c] = ' ';
            loc->dsply2[r][c] = ' ';
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
        for(int i=0; i < RM_CL; i++)
        {
            for(int c=0; c < COL_MX; c++)
                for(int j=0; j < RM_RW; j++)
                {
                    cout << brd[r][c].dsply1[i][j];
                    if(j==12)
                        cout << "     ";
                }
            cout << endl;
        }
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