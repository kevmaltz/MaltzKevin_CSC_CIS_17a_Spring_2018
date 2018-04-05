/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on March 12th, 2018, 1:59 PM
 * Purpose:  Structure utilizing a Dynamic 1-D Array
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
Array *fillAry(int);
void prntAry(Array *,int);
void destroy(Array *);

//Executions Begin Here!
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare and allocate memory for the array
    int size=100;
    Array *array=fillAry(size);
    
    //Print the random 2-Digit array
    prntAry(array,10);
    
    //Deallocate memory
    destroy(array);

    return 0;
}

void prntAry(Array *a,int perLine){
    cout<<endl;
    for(int i=0;i<a->size;i++){
        cout<<a->data[i]<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

void destroy(Array *a){
    if(!a){
        delete []a->data;
        delete []a;
    }
}

Array *fillAry(int n){
    //Is the size parameter valid
    if(n<=0)return 0;
    
    //Allocate the Structure pointer
    Array *array=new Array;
    array->size=n;
    
    //Allocate memory
    array->data=new int[array->size];
    
    //Fill with 2 digit random numbers
    for(int i=0;i<n;i++){
        array->data[i]=rand()%90+10;//[10-99]
    }
    
    //Return the array
    return array;
}