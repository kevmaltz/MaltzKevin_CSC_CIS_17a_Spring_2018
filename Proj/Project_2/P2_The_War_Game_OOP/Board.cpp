#include "Board.h"
using namespace std;

Board::Board(){
    
}

Board::~Board(){
    
}

void Board::combat(){
    
}

void Board::move(){
    
}

///Occupy a location with the passed Unit, modify displays of location to reflect
void Board::ocpy(Location* loc, Unit* unit){
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
///Remove Unit from passed location, remove unit from displays as well
void Board::unOcpy(Location* loc){
    //Set unit as out of play, remove unit from location, un-occupy location
    loc->occUnit->inPlay = false;
    loc->occUnit = NULL;
    loc->isOcp = false;
    //Clear board display of location for both players
    for(int c=1; c < RM_CL-1; c++){
        loc->dsply1[2][c] = ' ';
        loc->dsply2[2][c] = ' ';
    }
}
void Board::dsplBrd(int pID){
    
}