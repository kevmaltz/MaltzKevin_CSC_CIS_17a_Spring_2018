/* 
 * File:   BadLengthException.h
 * Author: rcc
 *
 * Created on May 23, 2018, 1:33 PM
 */

#ifndef BADLENGTHEXCEPTION_H
#define BADLENGTHEXCEPTION_H

class BadLengthException{
    private:
        int lngth;
    public:
        inline BadLengthException(int l){lngth = l;}
        inline int what(){return lngth;}
};

#endif /* BADLENGTHEXCEPTION_H */

