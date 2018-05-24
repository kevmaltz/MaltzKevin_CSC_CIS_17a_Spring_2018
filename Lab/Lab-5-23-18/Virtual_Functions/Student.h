/* 
 * File:   Student.h
 * Author: Kevin Maltz
 * Created on May 23, 2018, 2:28 PM
 */

#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include "Person.h"

class Student : public Person{
    private:
        std::vector<int> marks;
        int findSum();
    public:
        Student(int);
        void getdata();
        void putdata();
    
};

#endif /* STUDENT_H */

