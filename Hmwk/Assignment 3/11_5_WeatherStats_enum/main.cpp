/****************************************************************************** 
 * File:   main.cpp
 * Author: Kevin Maltz
 * Created on October 1, 2017, 2:37 PM
 * Purpose: Find the high/low temperatures, average monthly temperature, 
 *          average monthly rainfall, and total rainfall from a years worth
 *          of monthly rainfall and daily temperature data.
 ******************************************************************************/
//Libraries
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//Structure to hold temperature and rainfall data for a month
struct TmpNRain
{
    std::string month;  //Month of which the data is recorded in 
    float rainFll;      //Rainfall in inches for the month
    float hTemp;        //Highest temperature for the month, in fahrenheit
    float lTemp;        //Lowest temperature for the month, in fahrenheit
    float avgTemp;      //Average daily temperature for the month, in fahrenheit
};

enum Mnth {JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST,
           SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};

//User defined functions           
float avgRain(float totR,           //Total rainfall for a number of months
              const int N_MONTHS)   //The number of months
{
    return totR / N_MONTHS;
}

/******************************************************************************
 * Calculates and returns the average temperature in a given month by averaging
 * the daily temperature high and low temperatures.
 ******************************************************************************/
float clcAvgT(std::string month);   //Month for which avg. temp is being calc

/******************************************************************************
 * Calculates and returns the average of the monthly average temperature stored 
 * in each instance of the TmpNRain structure in an array.
 ******************************************************************************/
float clcAvgT(TmpNRain weather[],   //Array of structures containing temperature
                                    //and rain data for a given month each 
              const int N_MNTHS);   //Size of the array = number of months

void fllArry( TmpNRain wther[],     //Array of structures containing temperature
                                    //and rain data for a given month each 
              const int SIZE);      //Size of the passed array

int fndHghT( TmpNRain wther[],  //Array of structures containing temperature
                                //and rain data for a given month each 
             const int SIZE);   //Size of the passed array

int fndLowT( TmpNRain wther[],  //Array of structures containing temperature
                                //and rain data for a given month each 
             const int SIZE);   //Size of the passed array

void prntRep(float avgRn,           //Average monthly rainfall
             float totRn,           //Total rainfall
             float lTemp,           //Lowest temperature recorded
             std::string lTpMnth,   //Month lowest temperature occurred
             float hTemp,           //Highest temperature recorded
             std::string hTpMnth,   //Month highest temperature occurred
             float avgTmp);         //Average monthly temperature

float totRain( TmpNRain weather[],  //Array of structures containing temperature
                                    //and rain data for a given month each
               const int N_MNTHS);  //Number of months in the passed array 

using namespace std;

int main(int argc, char** argv) 
{
    /*********************************************************************
     * CONSTANTS
     * __________________________________________________________________
     * N_MONTHS         :The number of months in the data set
     *********************************************************************/
    const int N_MONTHS = 12;
    
    //Create array of TmpNRain structures to gold weather data for each month
    TmpNRain month[N_MONTHS];
    
    //Variables
    int hTIndx;         //Index of the structure with the highest hTemp value
    int lTIndx;         //Index of the structure with the lowest lTemp value
    float avgRn;        //Average monthly rainfall, in inches, for the given 
                        //time period
    float avgT;         //Average monthly temperature
    float totRn;        //Total rainfall over the given time period, in inches
    
    //Input data to array structures
    fllArry(month, N_MONTHS);
    
    //Calculate total rainfall
    totRn = totRain(month, N_MONTHS);
    
    //Calculate average monthly rainfall
    avgRn = avgRain(totRn, N_MONTHS);
    
    //Find month with highest temperature
    hTIndx = fndHghT(month, N_MONTHS);
    
    //Find month with lowest temperature
    lTIndx = fndLowT(month, N_MONTHS);
    
    //Calculate the average monthly temperature
    avgT = clcAvgT(month, N_MONTHS);
    
    //Output
    prntRep(avgRn, totRn, month[lTIndx].lTemp, month[lTIndx].month, 
            month[hTIndx].hTemp, month[hTIndx].month, avgT);

    return 0;
}

float clcAvgT(std::string month)
{
    const float MIN = -100;
    const float MAX = 140;
    
    float total = 0;
    float temp;
    int days;
    
    cout << "Enter number days in " << month << ": ";
    cin >> days;
    
    for(int m=JANUARY; m <= days; m++)
    {
        cout << "Enter the low temperature for day " << m << " : ";
        cin >> temp;
        while( temp < MIN || temp > MAX)
        {
            cout << "Invalid temperature. Re-enter: ";
            cin >> temp;
        }
        total += temp;
        
        cout << "Enter the high temperature for day " << m << " : ";
        cin >> temp;
         while( temp < MIN || temp > MAX)
        {
            cout << "Invalid temperature. Re-enter: ";
            cin >> temp;
        }
        total += temp;
    }
    
    return total / days;
}

float clcAvgT(TmpNRain weather[], const int N_MNTHS)
{
    float total = 0;            //Accumulator for temperature
    
    for( int month=JANUARY; month < N_MNTHS; month++)
    {
        total += weather[month].avgTemp;
    }
    
    return total / N_MNTHS;
}

void fllArry( TmpNRain month[], const int SIZE)
{
    for(int m=JANUARY; m < SIZE; m++)
    {
        
        cout << "Enter the name of the month: ";
        cin >> month[m].month; 
        
        //Get rainfall for the month
        cout << "Enter the rainfall, in inches, for the month: ";
        cin >> month[m].rainFll;
        
        //Get months high and low temps
        cout << "Enter the highest temperature for the month, in fahrenheit: ";
        cin >> month[m].hTemp;
        cout << "Enter the lowest temperature for the month, in fahrenheit: ";
        cin >> month[m].lTemp;
        
        //Call function to return average temperature for the month
        month[m].avgTemp = clcAvgT(month[m].month);
    }
}

int fndHghT(TmpNRain wther[], const int SIZE)
{
    int index = 0;
    float high = wther[JANUARY].hTemp;
    for(int month=FEBRUARY; month < SIZE; month++)
    {
        if( wther[month].hTemp > high)
        {
            high = wther[month].hTemp;
            index = month;
        }
    }
    
    return index;
}

int fndLowT( TmpNRain wther[], const int SIZE)
{
    int index = 0;
    float lwst = wther[JANUARY].lTemp;
    for(int month=FEBRUARY; month < SIZE; month++)
    {
        if( wther[month].lTemp < lwst)
        {
            lwst = wther[month].lTemp;
            index = month;
        }
    }
    
    return index;
}

void prntRep(float avgRn, float totRn, float lTemp, std::string lTpMnth,
             float hTemp, std::string hTpMnth, float avgTmp)
{
    cout << fixed << showpoint << setprecision(1);
    cout << "Average monthly rainfall: " << avgRn << " in.\n";
    cout << "Total annual rainfall: " << totRn << " in.\n";
    cout << "Average monthly temperature: " << avgTmp << " F\n";
    cout << lTpMnth << " had the lowest temperature at " << lTemp << "F\n";
    cout << hTpMnth << " had the highest temperature at " << hTemp << "F\n";
}