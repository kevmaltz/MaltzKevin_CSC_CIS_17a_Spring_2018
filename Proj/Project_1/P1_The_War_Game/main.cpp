/* 
 * File:   main.cpp
 * Author: Kevin Maltz
 * Created on April 6, 2018, 8:43 PM
 * Purpose: 
 */

//System Libraries
#include <iostream> //Basic user input/output
#include <string>   //Unit/Location/player names
#include <fstream>  //Read & Write to text and binary files for setup and restart
#include <iomanip>  //Used for formatting the board display
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
const short ROW_MX = 13;//Maximum number of rows on the board
const short COL_MX = 5; //Maximum number of columns on the board
const int N_PCS = 25;   //Number of pieces per player
const int RM_CL = 13;   //Must be = to the c of Location.dsply[r][c]
const int RM_RW = 5;    //Must be = to the r of Location.dsply[r][c]

//Function Prototypes
Location **initBrd(fstream &);  //Initializes the board
void initPcs(fstream &, Unit [], Unit []);  //Initialize data for all pieces(Unit structures)
int stPlyrs(string &, string &, bool &);    //Sets the players and their names, returns number of human players
void setPcs(Location **, Unit [], string);
void ocpy(Location*, Unit*);    //Occupy a location with the passed Unit, modify displays of location to reflect
void unOcpy(Location*);         //Remove Unit from passed location, remove unit from displays as well
void dspBrd(Location **, int);  //Displays the board
void ptBrdLoc(Location **);     //Test if binary file properly read to board structure array
void ptPlyrs(Unit [], Unit []); //Test if player pieces read in successfully

//Execution begins here
int main(int argc, char** argv) 
{
    int nPlyr;              //Number of human players
    string plyr1;           //Name of player 1
    string plyr2;           //Name of player 2
    bool ai = false;        //Playing against AI?
    unsigned int turn = 0;  //The current turn number. Increments +1 every turn
    
    fstream setup("setup.dat", ios::in | ios::binary);
    Location **board;   //13x5 game board
    Unit p1Pcs[N_PCS];  //Holds all of player 1's pieces
    Unit p2Pcs[N_PCS];  //Holds all of player 2's pieces
    
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
    //Display the board, right now with no pieces.
    dspBrd(board,1);
    //player 1 piece setup
    setPcs(board, p1Pcs, plyr1);
            
    //player 2 piece setup
    setPcs(board, p2Pcs, plyr2);
//TODO - /*FOR AI IMPLEMENTATION*/
//    if(ai)
//        aiStPcs(board, p2Pcs);
//    else
//        setPcs(board, p2Pcs, plyr2);
    
    
    
    
    
    
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
    int nPlyr = 0;  //Number of human players. Sentinel value of 0
    
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
    int id = pcs[0].plyrID; //Which player is setting their pieces
    
    cout << endl << endl;
    cout << pNme << " place your pieces on the board.\n";
    //Begin setup
    do
    {
        allSet = true;
        mtchInd = -1;
        cout << "Unplaced pieces:\n";
        //Display all pieces not yet in play/set on board
        for(int i=0; i < N_PCS; i++)
        {
            if(pcs[i].inPlay == false)
                cout << pcs[i].name << endl;
        }
        //Get and validate piece selection by player
        do
        {
            repeat = false;
            //Prompt for choice of piece
            cout << pNme << " select a piece by typing in the name: ";
            getline(cin, slctn);

            //Convert string to proper case formatting
            slctn[0] = toupper(slctn[0]);
            for(int i=1; i<slctn.length(); i++)
                slctn[i] = tolower(slctn[i]);

            //Proper capitalization for Field Marshal
            if(slctn.length() == 13)
                slctn[6] = toupper(slctn[6]);

            //Check if piece exists and not in play. If valid store index of selected unit
            for(int i=0; i < N_PCS; i++)
            {
                if(pcs[i].inPlay == false)
                    if(pcs[i].name == slctn)
                    {
                        mtchInd = i;
                        break;  //Stop looking as soon as a matching piece is found
                    }
            }

            //If no valid match found notify player and restart piece selection
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
                //Valid row of locations depend on the player ID
                if(id == 1 && (slctR < 0 || slctR > R_MX_P1))
                {
                    repeat = true;
                    cout << "Invalid location\n";
                }
                else if(id == 2 && (slctR < R_MN_P2 || slctR >= ROW_MX))
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
            
            //Check if chosen location is already occupied, if yes decide what to do
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
            {
                allSet = false;
                break;  //Stop looking as soon as any unset piece is found
            }
    }while(!allSet);
}
void ocpy(Location* loc, Unit* unit)
{
    //Occupy location, place unit at location, set unit as in play
    loc->isOcp = true;
    loc->occUnit = unit;
    unit->inPlay = true;
    //Depending on owner of unit, configure board display at location for each player
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
    //Set unit as out of play, remove unit from location, un-occupy location
    loc->occUnit->inPlay = false;
    loc->occUnit = NULL;
    loc->isOcp = false;
    //Clear board display of location for both players
    for(int r=1; r < RM_RW-1; r++)
        for(int c=1; c < RM_CL-1; c++)
        {
            loc->dsply1[r][c] = ' ';
            loc->dsply2[r][c] = ' ';
        }
}
void dspBrd(Location **board, int pID)
{
    //Always display the current players' board half on bottom
    if(pID == 1)
    {
        //Label the columns for the player, top of board
        cout << right << setw(8) << "C0" << setw(18) << "C1" 
             << setw(18) << "C2" << setw(18) << "C3" << setw(18) << " C4\n"; 
        for(int bR=ROW_MX-1; bR >= 0; bR--)
        {
            for(int rmR=0; rmR < RM_RW; rmR++)
            {
                for(int bC=0; bC < COL_MX; bC++)
                {
                    for(int rmC=0; rmC < RM_CL; rmC++)
                        cout << board[bR][bC].dsply1[rmR][rmC];
                    if(bC != (COL_MX-1))
                    {
                        //Handles the horizontal pathing displayed on the board
                        if(rmR == 2)
                            switch(bR)
                            {
                                case 12: cout << "-----"; break;
                                case 11: cout << "=|=|="; break;
                                case 10: cout << "-----"; break;
                                case 9: cout << "-----"; break;
                                case 8: cout << "-----"; break;
                                case 7: cout << "=|=|="; break;
                                case 6: cout << "     "; break;
                                case 5: cout << "=|=|="; break;
                                case 4: cout << "-----"; break;
                                case 3: cout << "-----"; break;
                                case 2: cout << "-----"; break;
                                case 1: cout << "=|=|="; break;
                                case 0: cout << "-----"; break;
                            }
                        else 
                            cout << "     ";
                    }
                }
                //Display row numbers on right of board
                if(rmR == 2)
                    cout << "  R" << bR<< endl;
                else
                    cout << endl;
            }
            //Handle the vertical pathing displayed on the board
            switch(bR)
            {
                case 12:
                    cout << "      |                 |                 |                 |                 |\n";
                    cout << "      |                 |                 |                 |                 |\n";
                    cout << "      |                 |                 |                 |                 |\n";
                    break;
                case 11:
                    cout << "     |_|     \\          |          /      |      \\          |          /     |_|\n";
                    cout << "     |_|       \\        |        /        |        \\        |        /       |_|\n";
                    cout << "     |_|         \\      |      /          |          \\      |      /         |_|\n";
                    break;
                case 10:
                    cout << "     |_|         /      |      \\          |          /      |      \\         |_|\n";
                    cout << "     |_|       /        |        \\        |        /        |        \\       |_|\n";
                    cout << "     |_|     /          |          \\      |      /          |          \\     |_|\n";
                    break;
                case 9:
                    cout << "     |_|     \\          |          /      |      \\          |          /     |_|\n";
                    cout << "     |_|       \\        |        /        |        \\        |        /       |_|\n";
                    cout << "     |_|         \\      |      /          |          \\      |      /         |_|\n";
                    break;
                case 8:
                    cout << "     |_|         /      |      \\          |          /      |      \\         |_|\n";
                    cout << "     |_|       /        |        \\        |        /        |        \\       |_|\n";
                    cout << "     |_|     /          |          \\      |      /          |          \\     |_|\n";
                    break;
                case 7:
                    cout << "     |_|                                 |_|                                 |_|\n";
                    cout << "     |_|                                 |_|                                 |_|\n";
                    cout << "     |_|                                 |_|                                 |_|\n";
                    break;
                case 6:
                    cout << "     |_|                                 |_|                                 |_|\n";
                    cout << "     |_|                                 |_|                                 |_|\n";
                    cout << "     |_|                                 |_|                                 |_|\n";
                    break;
                case 5:
                    cout << "     |_|     \\          |          /      |      \\          |          /     |_|\n";
                    cout << "     |_|       \\        |        /        |        \\        |        /       |_|\n";
                    cout << "     |_|         \\      |      /          |          \\      |      /         |_|\n";
                    break;
                case 4:
                    cout << "     |_|         /      |      \\          |          /      |      \\         |_|\n";
                    cout << "     |_|       /        |        \\        |        /        |        \\       |_|\n";
                    cout << "     |_|     /          |          \\      |      /          |          \\     |_|\n";
                    break;
                case 3:
                    cout << "     |_|     \\          |          /      |      \\          |          /     |_|\n";
                    cout << "     |_|       \\        |        /        |        \\        |        /       |_|\n";
                    cout << "     |_|         \\      |      /          |          \\      |      /         |_|\n";
                    break;
                case 2:
                    cout << "     |_|         /      |      \\          |          /      |      \\         |_|\n";
                    cout << "     |_|       /        |        \\        |        /        |        \\       |_|\n";
                    cout << "     |_|     /          |          \\      |      /          |          \\     |_|\n";
                    break;
                case 1:
                    cout << "      |                 |                 |                 |                 |\n";
                    cout << "      |                 |                 |                 |                 |\n";
                    cout << "      |                 |                 |                 |                 |\n";
                    break;
                default: break;
                    
            }
        }
        //Label the columns for the player, bottom of board
        cout << right << setw(8) << "C0" << setw(18) << "C1" 
             << setw(18) << "C2" << setw(18) << "C3" << setw(18) << " C4\n";
    }
    else if(pID == 2)
    {
        //Label the columns for the player, top of board
        cout << right << setw(8) << "C4" << setw(18) << "C3" 
             << setw(18) << "C2" << setw(18) << "C1" << setw(18) << " C0\n";
        for(int bR=0; bR < ROW_MX; bR++)
        {
            for(int rmR=0; rmR < RM_RW; rmR++)
            {
                for(int bC=COL_MX-1; bC >= 0; bC--)
                {
                    for(int rmC=0; rmC < RM_CL; rmC++)
                        cout << board[bR][bC].dsply2[rmR][rmC];
                    if(bC != 0)
                        {
                        //Handles the horizontal pathing displayed on the board
                            if(rmR == 2)
                                switch(bR)
                                {
                                    case 12: cout << "-----"; break;
                                    case 11: cout << "=|=|="; break;
                                    case 10: cout << "-----"; break;
                                    case 9: cout << "-----"; break;
                                    case 8: cout << "-----"; break;
                                    case 7: cout << "=|=|="; break;
                                    case 6: cout << "     "; break;
                                    case 5: cout << "=|=|="; break;
                                    case 4: cout << "-----"; break;
                                    case 3: cout << "-----"; break;
                                    case 2: cout << "-----"; break;
                                    case 1: cout << "=|=|="; break;
                                    case 0: cout << "-----"; break;
                                }
                            else 
                                cout << "     ";
                        }
                }
                //Display row numbers on right of board
                if(rmR == 2)
                    cout << "  R" << bR<< endl;
                else
                    cout << endl;
            }
            //Handles the vertical pathing displayed on the board
            switch(bR)
            {
                case 0:
                    cout << "      |                 |                 |                 |                 |\n";
                    cout << "      |                 |                 |                 |                 |\n";
                    cout << "      |                 |                 |                 |                 |\n";
                    break;
                case 1:
                    cout << "     |_|     \\          |          /      |      \\          |          /     |_|\n";
                    cout << "     |_|       \\        |        /        |        \\        |        /       |_|\n";
                    cout << "     |_|         \\      |      /          |          \\      |      /         |_|\n";
                    break;
                case 2:
                    cout << "     |_|         /      |      \\          |          /      |      \\         |_|\n";
                    cout << "     |_|       /        |        \\        |        /        |        \\       |_|\n";
                    cout << "     |_|     /          |          \\      |      /          |          \\     |_|\n";
                    break;
                case 3:
                    cout << "     |_|     \\          |          /      |      \\          |          /     |_|\n";
                    cout << "     |_|       \\        |        /        |        \\        |        /       |_|\n";
                    cout << "     |_|         \\      |      /          |          \\      |      /         |_|\n";
                    break;
                case 4:
                    cout << "     |_|         /      |      \\          |          /      |      \\         |_|\n";
                    cout << "     |_|       /        |        \\        |        /        |        \\       |_|\n";
                    cout << "     |_|     /          |          \\      |      /          |          \\     |_|\n";
                    break;
                case 5:
                    cout << "     |_|                                 |_|                                 |_|\n";
                    cout << "     |_|                                 |_|                                 |_|\n";
                    cout << "     |_|                                 |_|                                 |_|\n";
                    break;
                case 6:
                    cout << "     |_|                                 |_|                                 |_|\n";
                    cout << "     |_|                                 |_|                                 |_|\n";
                    cout << "     |_|                                 |_|                                 |_|\n";
                    break;
                case 7:
                    cout << "     |_|     \\          |          /      |      \\          |          /     |_|\n";
                    cout << "     |_|       \\        |        /        |        \\        |        /       |_|\n";
                    cout << "     |_|         \\      |      /          |          \\      |      /         |_|\n";
                    break;
                case 8:
                    cout << "     |_|         /      |      \\          |          /      |      \\         |_|\n";
                    cout << "     |_|       /        |        \\        |        /        |        \\       |_|\n";
                    cout << "     |_|     /          |          \\      |      /          |          \\     |_|\n";
                    break;
                case 9:
                    cout << "     |_|     \\          |          /      |      \\          |          /     |_|\n";
                    cout << "     |_|       \\        |        /        |        \\        |        /       |_|\n";
                    cout << "     |_|         \\      |      /          |          \\      |      /         |_|\n";
                    break;
                case 10:
                    cout << "     |_|         /      |      \\          |          /      |      \\         |_|\n";
                    cout << "     |_|       /        |        \\        |        /        |        \\       |_|\n";
                    cout << "     |_|     /          |          \\      |      /          |          \\     |_|\n";
                    break;
                case 11:
                    cout << "      |                 |                 |                 |                 |\n";
                    cout << "      |                 |                 |                 |                 |\n";
                    cout << "      |                 |                 |                 |                 |\n";
                    break;
                default: break;

            }
        }
        //Label the columns for the player, bottom of board
        cout << right << setw(8) << "C4" << setw(18) << "C3" 
             << setw(18) << "C2" << setw(18) << "C1" << setw(18) << " C0\n";
    }
    else
        cout << "ERROR: Cannot display the board.\n";
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