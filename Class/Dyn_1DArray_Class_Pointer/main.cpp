/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on March 26th, 2018, 1:36 PM
 * Purpose:  Class utilizing a Dynamic 1-D Array
 */

//System Libraries
#include <iostream>  //I/O Library
#include <cstdlib>   //srand, rand
#include <ctime>     //Time
using namespace std;

//User Libraries
#include "Array.h"

//Global Constants - Math, Science, Conversions, 2D Array Sizes

//Function Prototypes
void prntAry(const Array *,int);

//Executions Begin Here!
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare and allocate memory for the array
    int size=100;
    Array *array;
    array=new Array(size);
    
    //Print the random 2-Digit array
    prntAry(array,10);
    
    //Deallocate
    delete array;
    
    //Exit stage right!
    return 0;
}

void prntAry(const Array *a,int perLine){
    cout<<endl;
    for(int i=0;i<a->getSize();i++){
        cout<<a->getData(i)<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}