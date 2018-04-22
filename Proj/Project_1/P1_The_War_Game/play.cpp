#include <iostream>

#include "play.h"

namespace play{
    using namespace std;
    void combat(Unit *attckr, Location &loc){
        if(attckr->priority == 10){
            //Bomb blows up, so do you!
            unOcpy(&loc);
            attckr->inPlay = false;
        }
        else if(attckr->name == "Engineers" && loc.occUnit->name == "Landmines"){
            //Remove Landmines
            unOcpy(&loc);
            //Place Engineers at the location
            ocpy(&loc, attckr);
        }
        else{
            if(attckr->priority > loc.occUnit->priority){
                //Defender dies, invasion succeeds
                unOcpy(&loc);
                ocpy(&loc, attckr);
            }
            else if(attckr->priority < loc.occUnit->priority){
                //Attacker dies, invasion fails
                attckr->inPlay = false;
            }
            else if(attckr->priority == loc.occUnit->priority){
                //Mutual destruction, location is now empty
                unOcpy(&loc);
                attckr->inPlay = false;
            }
        }
    }
    bool mveVld(Location **board, int strtR, int strtC, int desR, int desC, int id){
        bool vld = true;        //True by default, set false if invalid move found
        int dspR = strtR - desR;//Absolute Row displacement of unit
        int dspC = strtC - desC;//Absolute Column displacement of unit
        //Take the absolute value of the displacement
        if(dspR < 0)
            dspR *= -1;
        if(dspC < 0)
            dspC *= -1;
        //Check if both starting location and destination are on the board
        if(strtR<0 || strtC<0 || desR<0 || desC<0)
            vld = false;
        else if(strtR >= ROW_MX || strtC >= COL_MX || desR >= ROW_MX || desC >= COL_MX)
            vld = false;
        //Check if Frontline or Mountains were selected as destination
        else if(board[desR][desC].type == 'M' || board[desR][desC].type == 'F')
            vld = false;
        //Check if location is occupied that it is not players own unit
        else if(board[desR][desC].isOcp && board[desR][desC].occUnit->plyrID == id)
            vld = false;
        //If move is <1,1> then make sure a Camp location is invloved
        else if(dspR == 1 && dspC == 1){
            if(board[strtR][strtC].type != 'C' && board[desR][desC].type != 'C')
                vld = false;
        }
        else if(dspR > 1 && dspC > 1)    //TODO - place the engineer exception in here later
            vld = false;
        else if(XOR(dspR > 1, dspC > 1) && board[strtR][strtC].isRR){
            if(!board[desR][desC].isRR)
                vld = false;
            else if(dspR > 1)
                vld = isRRopn(board, strtR, strtC, desR, 'r');
            else
                vld = isRRopn(board, strtR, strtC, desC, 'c');
        }
        return vld;
    }
    bool isRRopn(Location **board, int initR, int initC, int dest, char drctn)
    {
        bool rrOpn = true;
        if(drctn == 'c'){
            if(dest - initC > 0){
                for(int c=initC+1; c < dest && rrOpn; c++)
                    if(board[initR][c].isOcp || !board[initR][c].isRR)
                        rrOpn = false;
            }
            else if(dest - initC < 0)
                for(int c=initC-1; c > dest && rrOpn; c--)
                    if(board[initR][c].isOcp || !board[initR][c].isRR)
                        rrOpn = false;
        }
        else if(drctn == 'r'){
            if(dest - initR > 0){
                for(int r=initR+1; r < dest && rrOpn; r++)
                    if(board[r][initC].isOcp || !board[r][initC].isRR)
                        rrOpn = false;
            }
            else if(dest - initR < 0)
                for(int r=initR-1; r > dest && rrOpn; r--)
                    if(board[r][initC].isOcp || !board[r][initC].isRR)
                        rrOpn = false;
        }
        return rrOpn;
    }
    void move(Location **board, int pTurn){
        bool vldMve;
        int strtR, strtC;   //(R,C) of starting position
        int desR, desC;     //(R,C) of destination position
        Unit *unit;
        //Loop until valid move is entered
        do{
            //Prompt player for movement
            cout << "Enter the location of the piece you want to move. Use R,C format: ";
            cin >> strtR; cin.ignore(1000,','); 
            cin >> strtC; cin.ignore(1000,'\n');
            cout << "Enter your destination in R,C format: ";
            cin >> desR; cin.ignore(1000,','); 
            cin >> desC; cin.ignore(1000,'\n');
            //Validate movement
            vldMve = mveVld(board, strtR, strtC, desR, desC, pTurn);
            if(!vldMve)
                cout << "Invalid Move\n";
            if(board[strtR][strtC].isOcp){
                unit = board[strtR][strtC].occUnit;
                if(unit->plyrID != pTurn){
                cout << "That is not your piece!\n";
                vldMve = false;
                }
                else if(unit->name == "Flag" || unit->name == "Landmines"){
                    cout << unit->name << " cannot ever be moved.\n";
                    vldMve = false;
                }
            }
            else{
                cout << "No piece available to move from that location.\n";
                vldMve = false;
            }
        }while(!vldMve);
        //Now make the move, including combat
        if(board[desR][desC].isOcp)
            combat(unit, board[desR][desC]);
        else{
            unOcpy(&board[strtR][strtC]);
            ocpy(&board[desR][desC], unit);
        } 
    }
    void ocpy(Location* loc, Unit* unit){
        //Occupy location, place unit at location, set unit as in play
        loc->isOcp = true;
        loc->occUnit = unit;
        unit->inPlay = true;
        //Depending on owner of unit, configure board display at location for each player
        if(unit->plyrID == 1){
            if(unit->name == "Field Marshal")
                for(int c=0; c < 7; c++)
                    loc->dsply1[2][2+c] = unit->name[6+c];
            else
                for(int c=0; c < unit->name.length(); c++)
                    loc->dsply1[2][2+c] = unit->name[c];
            for(int c=2; c < RM_CL-2; c++)
                loc->dsply2[2][c] = '?';

        }
        else{
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
    void unOcpy(Location* loc){
        //Set unit as out of play, remove unit from location, un-occupy location
        loc->occUnit->inPlay = false;
        loc->occUnit = NULL;
        loc->isOcp = false;
        //Clear board display of location for both players
        for(int r=1; r < RM_RW-1; r++)
            for(int c=1; c < RM_CL-1; c++){
                loc->dsply1[r][c] = ' ';
                loc->dsply2[r][c] = ' ';
            }
    }
    string frmtCse(string s){
        int pos = -1;
        //rewrites entire string, minus first character, to lowercase value
        for(int i=1; i<s.length(); i++)
            s[i] = tolower(s[i]);
        //Capitalize first letter of every space separated word in the string
        do{
            s[pos+1] = toupper(s[pos+1]);
            pos = s.find_first_of(' ', pos+1);
        }while(pos != -1);

        return s;
    }
    int isWnr(int id, Unit p1[], Unit p2[])
    {
        int winner = 0;
        if(id == 1)
            if(!p2[N_PCS - 1].inPlay)
                winner = id;
        if(id == 2)
            if(!p1[N_PCS - 1].inPlay)
                winner = id;
        return winner;
    }
}
    void wrtLog(std::fstream &, Location**, Unit[], Unit[]){
        
    }