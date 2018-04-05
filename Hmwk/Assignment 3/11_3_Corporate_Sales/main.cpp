/****************************************************************************** 
 * File:   main.cpp
 * Author: Kevin Maltz
 * Created on March 25, 2018 11:11 PM
 * Purpose: Track quarterly and total sales for 4 divisions of a corporation 
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct DivisionData
{
	string name;			//Division name
	float qSales[4];		//Quarterly sales, in order 1 -> 4
	float totSale;			//Total annual sales
	float avgQSls;			//Avg quarterly sales
};
int main() 
{
    const int SIZE = 4;		//Number of divisions in corporation
	
    DivisionData corpDiv[SIZE];	//Array of structs for all divisions
	
    //Input and Validation
    for(int count = 0; count < SIZE; count ++)
    {
        cout << "Enter Division name: ";
        getline(cin, corpDiv[count].name);
        cout << endl << endl;;
        for(int q = 0; q < SIZE; q++)
        {
            cout << "Enter quarter " << q + 1 << " sales in $: ";
            cin >> corpDiv[count].qSales[q];
            cout << endl;
            while(corpDiv[count].qSales[q] < 0)
            {
                cout << endl;
                cout << "Invalid sales figure, Re-enter sales for Q"
                     << q+1 << ": ";
                cin >> corpDiv[count].qSales[q];
                cout << endl;
            }
            cout << endl;
            cin.ignore(1000, '\n');
        }
    }
	
    //Initialize Total Sales to zero for all divisions
    for(int count = 0; count < SIZE; count++)
        corpDiv[count].totSale = 0;
	
    //Computations
    for(int count = 0; count < SIZE; count++)
    {
	for(int q = 0; q < SIZE; q++)
	corpDiv[count].totSale += corpDiv[count].qSales[q];
			
	corpDiv[count].avgQSls = ( corpDiv[count].totSale / SIZE );
    }
	
    //Output
    cout << left << fixed << showpoint << setprecision(2);
    for(int count = 0; count < SIZE; count ++)
    {
	cout << setw(12) << "Division" << ":  " << corpDiv[count].name << endl;
        for(int q = 0; q < SIZE; q++)
	{
            cout << "Q" << q+1 << setw(10) << " Sales" << ": $"
                 << corpDiv[count].qSales[q] << endl;
	}
        cout << setw(12) << "Total Sales" << ": $" << corpDiv[count].totSale;
	cout << endl;
	cout << setw(12) << "Avg Q Sales" << ": $" << corpDiv[count].avgQSls;
	cout << endl << endl;
    }
	
    return 0;
}