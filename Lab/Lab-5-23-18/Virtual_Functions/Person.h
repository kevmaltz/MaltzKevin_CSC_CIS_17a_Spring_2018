/* 
 * File:   Person.h
 * Author: Kevin Maltz
 * Created on May 23, 2018, 2:08 PM
 * Purpose: Abstract class
 */

#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person{
    protected:
        std::string name;
        int age;
        int id;
    public:
        virtual ~Person()=0;
};

#endif /* PERSON_H */

