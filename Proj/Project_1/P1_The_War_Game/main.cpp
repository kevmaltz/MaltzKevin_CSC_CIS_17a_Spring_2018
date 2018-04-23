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
#include "Constants.h"
#include "Unit.h"
#include "Location.h"
#include "setup.h"
#include "play.h"

//Global Constants - Math, Science, Conversions, 2D Array Sizes

//Function Prototypes
void dspBrd(Location **, int);  //Displays the board
void dspHP(int);                //displays the horizontal paths on the board
void dspVP1(int);               //displays the vertical paths on the board for player 1
void dspVP2(int);               //displays the vertical paths on the board for player 2

//Execution begins here
int main(int argc, char** argv) 
{
    char undo;              //Y(es) or N(o) for undo option to be enabled
    string plyr1;           //Name of player 1
    string plyr2;           //Name of player 2
    int turn = 0;  //The current turn number. Increments +1 every turn
    int curPlyr;            //Current player whos turn it is
    bool winner = false;
    fstream log;            //Fstream object for logging when undo enabled
    fstream fin("setup.dat", ios::in | ios::binary);
    Location **board;   //13x5 game board
    Unit p1Pcs[N_PCS];  //Holds all of player 1's pieces
    Unit p2Pcs[N_PCS];  //Holds all of player 2's pieces
    
    if(fin.is_open() && fin.good()){
        //Read in data for every location on the board
        board = setup::initBrd(fin);
        //Read in data for each piece
        setup::initPcs(fin, p1Pcs, p2Pcs);
        fin.close();
    }
    else{   //Return exit failure if setup file fails to open.
        cout << "ERROR: unable to open file Setup.dat, exiting program\n";
        return EXIT_FAILURE;
    }
    //Enable or Disable undo function
    cout << "Enable undo functionality? Y/N: ";
    cin >> undo; cin.ignore(1000,'\n');
    //Set player(s) and return number of human players
    setup::stPlyrs(plyr1, plyr2);
    //player 1 piece setup
    dspBrd(board,1);
    setup::gmeSet(board, p1Pcs, plyr1, 1);
    //player 2 piece setup
    dspBrd(board,2);
    setup::gmeSet(board, p2Pcs, plyr2, 2);
    //Open REDO file
    if(undo == 'Y' || undo == 'y'){
        log.open("log.txt", ios::in | ios::out);
        if(log.bad() || !log.is_open()){
            cout << "ERROR: unable to open file log.dat, disabling undo option\n";
            undo = 'N';
        }
    }
    //PLAY
    do{
        curPlyr = turn%2 + 1;
        //Player move
        cout << "ROUND " << turn/2 + 1 << endl;
        if(curPlyr == 1){
            cout << plyr1 << "'s turn.\n";
            cout << "Press Enter to begin your turn\n";
            cin.ignore(1000,'\n');
        }
        else{
            cout << plyr2 << "'s turn.\n";
            cout << "Press Enter to begin your turn\n";
            cin.ignore(1000,'\n');
        }
        //Check if player wants to undo a move
        if(undo == 'Y' || undo == 'y')
            play::undo(log, board, p1Pcs, p2Pcs, turn);
        dspBrd(board, curPlyr);
        play::move(board, curPlyr);
        //TODO - Write out current gamestate to file here
        play::wrtLog( log, board, p1Pcs, p2Pcs);
        //Check if won game
        winner = play::isWnr(curPlyr, p1Pcs, p1Pcs);
        //Increment turn counter
        turn++;
    }while(!winner);
    if(undo == 'Y' || undo == 'y')
        log.close();
    //Declare the winner
    if(winner == 1)
        cout << "Congratulations " << plyr1 <<"! You won!\n";
    else if(winner == 2)
        cout << "Congratulations " << plyr2 <<"! You won!\n";
    else
        cout <<"What happened??? You both lose.\n";
    
    //Cleanup
    for(int r=0; r < ROW_MX; r++)
        delete[] board[r];
        delete [] board;
    
    return EXIT_SUCCESS;
}
void dspBrd(Location **board, int pID){
    //Always display the current players' board half on bottom
    if(pID == 1){
        //Label the columns for the player, top of board
        cout << right << setw(8) << "C1" << setw(18) << "C2" 
             << setw(18) << "C3" << setw(18) << "C4" << setw(18) << " C5\n";
        // bR/bC = current board row/col; rmR/rmC = current row/col of indv location display
        for(int bR=ROW_MX-1; bR >= 0; bR--){
            for(int rmR=0; rmR < RM_RW; rmR++){
                for(int bC=0; bC < COL_MX; bC++){
                    for(int rmC=0; rmC < RM_CL; rmC++)
                        cout << board[bR][bC].dsply1[rmR][rmC];
                    if(bC != (COL_MX-1)){
                        //Handles the horizontal pathing displayed on the board
                        if(rmR == 2)
                            dspHP(bR);
                        else 
                            cout << "     ";
                    }
                }
                //Display row numbers on right of board
                if(rmR == 2)
                    cout << "  R" << bR+1 << endl;
                else
                    cout << endl;
            }
            //Handle the vertical pathing displayed on the board
            dspVP1(bR);
        }
        //Label the columns for the player, bottom of board
        cout << right << setw(8) << "C1" << setw(18) << "C2" 
             << setw(18) << "C3" << setw(18) << "C4" << setw(18) << " C5\n";
    }
    else if(pID == 2){
        //Label the columns for the player, top of board
        cout << right << setw(8) << "C5" << setw(18) << "C4" 
             << setw(18) << "C3" << setw(18) << "C2" << setw(18) << " C1\n";
        for(int bR=0; bR < ROW_MX; bR++){
            for(int rmR=0; rmR < RM_RW; rmR++){
                for(int bC=COL_MX-1; bC >= 0; bC--){
                    for(int rmC=0; rmC < RM_CL; rmC++)
                        cout << board[bR][bC].dsply2[rmR][rmC];
                    if(bC != 0){
                        //Handles the horizontal pathing displayed on the board
                            if(rmR == 2)
                                dspHP(bR);
                            else 
                                cout << "     ";
                        }
                }
                //Display row numbers on right of board
                if(rmR == 2)
                    cout << "  R" << bR+1 << endl;
                else
                    cout << endl;
            }
            //Handles the vertical pathing displayed on the board
            dspVP2(bR);
        }
        //Label the columns for the player, bottom of board
        cout << right << setw(8) << "C5" << setw(18) << "C4" 
             << setw(18) << "C3" << setw(18) << "C2" << setw(18) << " C1\n";
    }
    else
        cout << "ERROR: Cannot display the board.\n";
}
void dspHP(int brdRow)
{
    switch(brdRow){
        case 11: cout << "=|=|="; break;
        case 7: cout << "=|=|="; break;
        case 6: cout << "     "; break;
        case 5: cout << "=|=|="; break;
        case 1: cout << "=|=|="; break;
        default: cout << "-----"; break;
    }
}
void dspVP1(int brdRow){
    switch(brdRow){
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
void dspVP2(int brdRow){
    switch(brdRow){
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