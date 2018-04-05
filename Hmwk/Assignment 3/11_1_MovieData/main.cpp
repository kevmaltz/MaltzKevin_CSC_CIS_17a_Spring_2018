/****************************************************************************** 
 * File:   main.cpp
 * Author: Kevin Maltz
 * Created on March 25, 2018 12:14 PM
 * Purpose: Display movie information in formatted structure
 ******************************************************************************/
//System Libraries
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//Structures
struct MvieDta
{
    std::string title;		//Title of Movie
    std::string director;	//Director of movie
    int year;			//Release year of movie
    int runTime;		//Movie runtime, in minutes
};

//User defined functions
MvieDta getMvie();
void shwMvie( MvieDta film);

int main(int argc, char** argv) 
{
    MvieDta movie1;
    MvieDta movie2;
    
    //Get movie data
    movie1 = getMvie();
    movie2 = getMvie();
    
    //Output Movie data
    shwMvie( movie1);
    shwMvie( movie2);

    return 0;
}
MvieDta getMvie()
{
    MvieDta movie;
    cout << "Enter name of a movie: ";
    getline(cin, movie.title);
    cout << endl;
    cout << "Enter the movie Director: ";
    getline(cin, movie.director);
    cout << endl;
    cout << "Enter the year the movie was released: ";
    cin >> movie.year;
    cout << endl;
    cout << "Enter the movie running time (in minutes): ";
    cin >> movie.runTime;
    cin.ignore(1000, '\n');
    cout << endl << endl;
    
    return movie;
}
void shwMvie( MvieDta film)
{
	cout << left;
	cout << setw(8) << "Title" << ": " << film.title << endl;
	cout << setw(8) << "Director" << ": " << film.director << endl;
	cout << setw(8) << "Year" << ": " << film.year << endl;
	cout << setw(8) << "Run time" << ": " << film.runTime << " minutes";
	cout << endl << endl;
}
