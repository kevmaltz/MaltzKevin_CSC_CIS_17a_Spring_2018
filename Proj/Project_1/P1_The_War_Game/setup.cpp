#include <iostream>
#include <iomanip>

#include "setup.h"
#include "play.h"

namespace setup{
    using namespace std;
    using play::frmtCse;
    using play::ocpy;
    using play::unOcpy;
    
    Location **initBrd(fstream &setup){
        Location **board;
        board = new Location*[ROW_MX];
        for(int r=0; r < ROW_MX; r++){
            board[r] = new Location[COL_MX];
            for(int c=0; c < COL_MX; c++){   
                //Read in binary data to a location structure
                setup.read(reinterpret_cast<char *>(board[r]+c), sizeof(board[r][c]));
                //Ensure all Unit* set to NULL. Ensures no bad memory read in from file
                board[r][c].occUnit = NULL;
            }
        }
        return board;
    }
    void initPcs(fstream &setup, Unit p1[], Unit p2[]){
        int nmLngth;    //Length of string to be read in from binary, minus the null
        char* buf;      //Buffer for reading in a string from the binary file
        for(int i=0; i < N_PCS; i++){
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
    int fndMtch(Unit pcs[], string s){
        for(int i=0; i < N_PCS; i++){
            if(pcs[i].inPlay == false)
                if(pcs[i].name == s)
                    return i; //return value as soon as a match is found
        }
        return -1;  //Flag for no match found
    }
    void stPlyrs(string &plyr1, string &plyr2){
            cout << "Enter player 1's name: ";
            getline(cin, plyr1);
            cout << "Enter player 2's name: ";
            getline(cin, plyr2);
    }
    void setPcs(Location **board, Unit pcs[], string pNme){
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
        do{
            allSet = true;
            mtchInd = -1;
            cout << "Unplaced pieces:\n";
            //Display all pieces not yet in play/set on board
            whoNtSt(pcs);
            //Get and validate piece selection by player
            do{
                repeat = false;
                //Prompt for choice of piece
                cout << pNme << " select a piece by typing in the name: ";
                getline(cin, slctn);
                //Convert string to proper case formatting
                slctn = frmtCse(slctn);
                cout << "after conversion string is" << slctn << endl;
                //Check if piece exists and not in play. If valid store index of selected unit
                mtchInd = fndMtch(pcs, slctn);
                //If no valid match found notify player and restart piece selection
                if(mtchInd == -1){
                    cout << "Invalid selection\n";
                    repeat = true;
                }
            }while(repeat);//FIND ME        
            //Setup pieces on board
            do{
                repeat = false;;
                do{ //Get and validate location selection. Repeats till location is valid
                    repeat = false;
                    slctR = slctC = -1;
                    cout << "Enter row,column( #,# ) to select a location to place the " 
                         << pcs[mtchInd].name << ": ";
                    //TODO - change this to use a stringstream to catch any error in the way user inputs numbers
                    cin >> slctR; cin.ignore(1000,','); 
                    cin >> slctC; cin.ignore(1000,'\n');
                    //Valid row of locations depend on the player ID
                    if(id == 1 && (slctR < 0 || slctR > R_MX_P1)){
                        repeat = true;
                        cout << "Invalid location\n";
                    }
                    else if(id == 2 && (slctR < R_MN_P2 || slctR >= ROW_MX)){
                        repeat = true;
                        cout << "Invalid location\n";
                    }
                    else if(slctC < 0 || slctC >= COL_MX){
                        repeat = true;
                        cout << "Invalid location\n";
                    }
                }while(repeat);            
                //Check if chosen location is already occupied, if yes decide what to do
                if(board[slctR][slctC].occUnit != NULL){
                    cout << board[slctR][slctC].occUnit->name
                         << " is already at that location.\nDo you wish to replace it with "
                         << pcs[mtchInd].name << "? Enter Y or N: ";
                    cin >> rpPc; cin.ignore(1000,'\n');

                    //Repeat location selection process if no, replace piece otherwise
                    if(rpPc == 'n' || rpPc == 'N')
                        repeat = true;
                    else if(rpPc == 'y' || rpPc == 'Y')
                        unOcpy(&board[slctR][slctC]);
                    else{
                        cout << "Invalid entry. Replacing piece anyways.\n";
                        unOcpy(&board[slctR][slctC]);
                    }
                }
            }while(repeat);
            ocpy(&board[slctR][slctC], &pcs[mtchInd]);        
            //If any pieces are not yet set in play, allSet=false and loop setup
            for(int i=0; i < N_PCS && allSet; i++)
                if(pcs[i].inPlay == false){
                    allSet = false;
                    break;  //Stop looking as soon as any unset piece is found
                }
        }while(!allSet);
    }
    void whoNtSt(Unit pcs[]){
        int perLne = 0;
        for(int i=0; i < N_PCS; i++){
            if(pcs[i].inPlay == false){
                cout << setw(14) << pcs[i].name;
                perLne++;
                if(0 == (perLne % 3))
                    cout << endl;
            }
        }
        cout << endl;
    }
}

    /*Alternate implementation of setPlyrs for when AI capability is introduced*/
//    int stPlyrs(string &plyr1, string &plyr2, bool &plyNPC){
//        int nPlyr = 0;  //Number of human players. Sentinel value of 0
//
//        cout << "2 player game or 1 player vs AI available\n";
//        cout << "Enter number of players(2 max): ";
//        cin >> nPlyr;
//        cin.ignore(1000, '\n');
//        while(nPlyr != 1 && nPlyr != 2){
//            cout << "Invalid number of player. Re-enter(max 2): ";
//            cin >> nPlyr;
//            cin.ignore(1000, '\n');
//        }
//        if(nPlyr == 1){
//            cout << "Enter player name: ";
//            getline(cin, plyr1);
//            plyr2 = "NPC";
//            plyNPC = true;
//        }
//        if(nPlyr == 2){
//            cout << "Enter player 1's name: ";
//            getline(cin, plyr1);
//            cout << "Enter player 2's name: ";
//            getline(cin, plyr2);
//        return nPlyr;
//    }