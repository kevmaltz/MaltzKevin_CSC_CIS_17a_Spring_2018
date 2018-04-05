/* 
 * File:   Array.cpp
 * Author: rcc
 * 
 * Created on March 28, 2018, 2:26 PM
 */

#include "Array.h"
#include <cstdlib>
#include <ctime>
#include <valarray>
using namespace std;

Array::Array(int r, int c){
    row=r<=1?2:r>32?32:r;
    col=c<=1?2:c>32?32:c;
    data=new int*[row];
    for(int i=0;i<row;i++){
        data[i] = new int[col];
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            data[i][j]=rand()%90+10;
        }
    }
}

Array::~Array(){
    for(int i=0;i<row;i++){
        delete []data[i];
    }
    delete []data;
}
    
int Array::getData(int indx)const{
    int size = row*col;
    if(indx>=0&&indx<size)
        return data[indx/col][indx%col];
    else return data[0][0];
}

