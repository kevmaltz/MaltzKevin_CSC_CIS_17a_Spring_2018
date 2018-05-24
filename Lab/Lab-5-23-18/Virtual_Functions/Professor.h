/* 
 * File:   Professor.h
 * Author: Kevin Maltz
 * Created on May 23, 2018, 2:27 PM
 */

#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "Person.h"

class Professor : public Person{
    private:
        int pub;
        int id;
    public:
        Professor();
        void getdata();
        void putdata();
};

#endif /* PROFESSOR_H */

