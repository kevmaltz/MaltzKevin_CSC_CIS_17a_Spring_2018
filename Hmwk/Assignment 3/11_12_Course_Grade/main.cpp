/****************************************************************************** 
 * File:   main.cpp
 * Author: Kevin Maltz
 * Created on March 26, 2018
 * Purpose: Take data on a user specified number of students with x number of
 * exams and calculate their average scores and letter grade. Output this
 * information in a formatted report.
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Structures
struct Student
{
    std::string name;
    int id;
    short *tests;
    float avgScr;
    char grade;
};
    
struct GrdTble
{
    struct GrdSet
    {
        int minScr;
        char grade;
    };
    
    GrdSet a;
    GrdSet b;
    GrdSet c;
    GrdSet d;
    GrdSet f;
    
    GrdTble()
    {
        //A grade criteria
        a.grade = 'A';
        a.minScr = 91;
        
        //B grade criteria
        b.grade = 'B';
        b.minScr = 81;
        
        //C grade criteria
        c.grade = 'C';
        c.minScr = 71;
        
        //D grade criteria
        d.grade = 'D';
        d.minScr = 61;
        
        //F grade criteria
        f.grade = 'F';
        f.minScr = 0;
    }
};

int main(int argc, char** argv) 
{
    int nTests;         //Number of scores per student
    int nStuds;         //Number of students
    Student *classRm;   //Classroom. Will hold all students in the class
    GrdTble grdTble;    //Table holding letter grade criteria
    
    cout << "Enter number of students: ";
    cin >> nStuds;
    cout << "Enter number of exams per student: ";
    cin >> nTests;
    cout << endl;
    
    classRm = new Student[nStuds];
    for(int i=0; i < nStuds; i++)
    {
        classRm[i].tests = new short[nTests];
    }
    
    //Input student info
    for(int i=0; i < nStuds; i++)
    {
        cin.ignore(1000,'\n');
        cout << "Input data for student #" << i + 1 << endl;
        cout << "----------------------------\n";
        cout << "Enter student name: ";
        getline(cin,classRm[i].name);
        cout << "Enter ID number: ";
        cin >> classRm[i].id;
        //Get test scores
        for(int j=0; j < nTests; j++)
        {
            cout << "test #" << j + 1 << " score: ";
            cin >> classRm[i].tests[j];
            while(classRm[i].tests[j] < 0)
            {
                cout << "Invalid score. Re-enter test #" << j + 1 << ": ";
                cin >> classRm[i].tests[j];
            }
        }
    }
    //Compute test average for each student
    for(int i=0; i < nStuds; i++)
    {
        int total;
        total = 0;
        for(int j=0; j < nTests; j++)
        {
            total += classRm[i].tests[j];
        }
        
        classRm[i].avgScr = static_cast<float>(total) / nTests;
    }
    
    //Compute the letter grade for each student
    for(int i=0; i < nStuds; i++)
    {
        if(classRm[i].avgScr < grdTble.d.minScr)
            classRm[i].grade = grdTble.f.grade;
        else if(classRm[i].avgScr < grdTble.c.minScr)
            classRm[i].grade = grdTble.d.grade;
        else if(classRm[i].avgScr < grdTble.b.minScr)
            classRm[i].grade = grdTble.c.grade;
        else if(classRm[i].avgScr < grdTble.a.minScr)
            classRm[i].grade = grdTble.b.grade;
        else
            classRm[i].grade = grdTble.a.grade;
    }
    
    //Output table of students info
    cout << endl << endl;
    cout << fixed << showpoint << setprecision(1) << left;
    cout << setw(15) << "NAME" << setw(8) << "ID" 
         << setw(12) << "AVG SCORE" << "GRADE\n";
    cout << "----------------------------------------\n";
    for(int i=0; i < nStuds; i++)
    {
        cout << setw(15) << classRm[i].name << setw(8) << classRm[i].id 
             << setw(12) << classRm[i].avgScr << classRm[i].grade << endl;
    }
    
    //Clean up
    for(int i=0; i < nStuds; i++)
    {
        delete []classRm[i].tests;
    }
    delete []classRm;

    return 0;
}

