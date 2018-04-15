/* 
 * File:   Displays.h
 * Author: Kevin Maltz
 *
 * Created on April 14, 2018, 4:39 PM
 */

#ifndef DISPLAYS_H
#define DISPLAYS_H
/******************************************************************************
 * The character arrays in here represent all the different possible displays
 * that any location on the board can have, as well as all the connecting 
 * pathways. The naming convention of the locations is based on the 
 * representative letter of the location type followed by the first two letters 
 * of the occupying unit. For empty locations the letter code is EM, and for 
 * hidden enemy units the letter code is HI.
 * EX: Field Marshal in the Headquarters would be H_FI
 * 
 * Pathways follow a separate naming convention. The convention is RR for
 * railroads and BR for basic roads. This is followed by the orientation letter
 * code. For horizontal and vertical pathways the code is HZ & VR,respectively. 
 * Traversing the board lengthwise is considered horizontal. For the slanted 
 * pathways the letter codes are IN for increasing and DE for decreasing. 
 * Increasing/Decreasing is determined by viewing the pathway as it traverses
 * from left to right.
 * EX: A pathway connecting the Post at [1][0] and the Camp at [1][1] is labeled
 * as BR_IN
 ******************************************************************************/
static const int RM_WD = 13;
static const int RM_HT = 5;
static const int RM_HT2 = 10;
static const char P_EM[RM_HT][RM_WD] = 
{{'=','=','=','=','=','=','=','=','=','=','=','=','='},
 {'=',' ',' ',' ','P','O','S','T',' ',' ',' ',' ','='},
 {'=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','='},
 {'=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','='},
 {'=','=','=','=','=','=','=','=','=','=','=','=','='} };

static const char C_EM[RM_HT][RM_WD] =
{{' ',' ',' ','=','=','=','=','=','=','=',' ',' ',' '},
 {' ','/',' ',' ','C','A','M','P',' ',' ',' ','\\',' '},
 {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
 {' ','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ','/',' '},
 {' ',' ',' ','=','=','=','=','=','=','=',' ',' ',' '} };

static const char H_EM[RM_HT][RM_WD] = 
{{' ',' ',' ','=','=','=','=','=','=','=',' ',' ',' '},
 {' ','/',' ',' ',' ','H','Q',' ',' ',' ',' ','\\',' '},
 {'=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','='},
 {'=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','='},
 {'=','=','=','=','=','=','=','=','=','=','=','=','='} };

static const char F_EM[RM_HT][RM_WD] = 
{{'=','=','=','=','=','=','=','=','=','=','=','=','='},
 {'=',' ','F','R','O','N','T','L','I','N','E',' ','='},
 {'=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','='},
 {'=',' ','F','R','O','N','T','L','I','N','E',' ','='},
 {'=','=','=','=','=','=','=','=','=','=','=','=','='} };

#endif /* DISPLAYS_H */

