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
    public:
        Person(std::string n="", int a=0){name=n; age=a;}
        virtual ~Person();
};

#endif /* PERSON_H */

