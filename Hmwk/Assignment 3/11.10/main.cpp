/****************************************************************************** 
 * File:   main.cpp
 * Author: Kevin Maltz
 * Created on March 26, 2018 at 2:18PM
 * Purpose: Manage Speakers and speaker information for a Speakers' Bureau. Find
 * and print out speakers when searching bureau by topic.
 ******************************************************************************/
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//Structures
struct Speaker
{
    string name = "test";
    long long int phneNum = 0;
    string topic = "";
    float fee = -1;
};
//Function Prototypes
void menu();
void modMenu();
void getInfo(Speaker *spkr);	//Fills all fields for a speaker
void modInfo(Speaker *spkr);	//Modify the data stored for a speaker
void prntSpk(Speaker *spkr);	//Print out all info for a single speaker
void PrntBur(Speaker **bureau, int nSpkr);	//Print out full bureau
void fndTpc(Speaker **bureau, int nSpkr, string key); //Search for a speaker topic

//Global contants
const int B_SIZE = 10; //Size of Speakers' Bureau
int main() 
{
    int nSpkr = 0;	//Number of speakers entered
    int spkr;		//Bureau element to modify data of
    int choice;	//Menu choice input
    string keyword;	//Topic keyword
    bool exit = false;	//Exit program or not
    Speaker **bureau = new Speaker*[B_SIZE];	//Array of speakers
    for(int i = 0; i < B_SIZE; i++)
        bureau[i] = new Speaker;
    do
    {
        //Display and get menu choice
        menu();
        cout << "Enter the menu option number of your choice: ";
        cin >> choice;
        cin.ignore(1000,'\n');
        switch(choice)
        {
            case 1: if(nSpkr >= B_SIZE)
          		{
          			cout << "No more new speakers may be added.\n";
          			break;
          		}
            		getInfo(bureau[nSpkr]);
                    nSpkr++;
                    break;	//Get speaker info
            case 2: cout << "Enter bureau number of speaker( 1 to max ): ";
                    cin >> spkr;
     			cin.ignore(1000,'\n');
                    if(spkr <= nSpkr && spkr > 0)
                         modInfo(bureau[spkr-1]);
                    else
                         cout << "No such speaker exists\n\n";
                    break;	//Modify speaker info
            case 3: cout << "Enter topic keyword to search for: ";
          		getline(cin, keyword);
          		if(keyword.length() > 1)
                        {
          			fndTpc(bureau, nSpkr, keyword);
                                cout << "Press ENTER to return to the menu.";
                                cin.ignore(1000, '\n');
                        }
          		else
          			cout << "Invalid keyword.\n";
          		break;
            case 4: PrntBur(bureau, nSpkr);
                    cout << "Press ENTER to return to the menu.";
                    cin.ignore(1000, '\n');
                    break;	//Print speaker
            case 5: exit = true;
                    break; //Exit program
            default:cout << "Invalid choice.\n";
        }
    }while(!exit);
    
    cout << "Thank you for using Speakers' Bureau Manager 1.0!\n";

    //Cleanup
    for(int i=0; i < B_SIZE; i++)
	    delete bureau[i];
    delete [] bureau;

    return 0;
}

void menu()	//Displays the main menu
{
    cout << "1. Enter new speaker\n";
    cout << "2. Modify a speaker's information\n";
    cout << "3. Search the bureau for speakers by topic\n";
    cout << "4. Print out information for all speakers\n";
    cout << "5. Exit program\n";
}
void modMenu()	//Displays the menu for the modInfo function
{
    cout << "1. Modify speaker name\n";
    cout << "2. Modify phone number\n";
    cout << "3. Modify speaking topic\n";
    cout << "4. Modify fee's due\n";
    cout << "5. Return to main menu\n";
}
void getInfo(Speaker *spkr) //Fills all fields for a speaker
{
    //Get speaker name, verify that field was filled.
    do
    {
        cout << "Enter the speaker's name: ";
        getline(cin, spkr->name);
        cout << "\nSpeaker name: " << spkr->name << endl;
    }while(spkr->name == "");

    //Get phone number, verify number entered
    do
    {
        cout << "Enter speaker's phone number(no spaces): ";
        cin >> spkr->phneNum;
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "\nSpeaker phone number is: " << spkr->phneNum << endl;
    }while(spkr->phneNum < 1000000);

    //Get speaker's speaking topic
    do
    {
        cout << "Enter speaking topic: ";
        getline(cin, spkr->topic);
        cout << "\nSpeaking topic is: " << spkr->topic << endl;
    }while(spkr->topic == "");

    //Get fee's owed by speaker
    do
    {
        cout << "Enter fee's owed by speaker: ";
        cin >> spkr->fee;
        cin.ignore(1000,'\n');
    }while(spkr->fee < 0);
}
void modInfo(Speaker *spkr) //Modify the data stored for a speaker
{
    int choice;
    bool exit = false;

    do
    {
        modMenu();
        cout << "Enter Choice: ";
        cin >> choice;
        cin.ignore(1000,'\n');
        switch(choice)
        {
            case 1: cout << "Current: " << spkr->name << endl;
                    cout << "Input new speaker name: ";
                    getline(cin, spkr->name);
                    break;
            case 2: cout << "Current: " << spkr->phneNum << endl;
                    do
                    {
                        cout << "Input new phone number: ";
                        cin >> spkr->phneNum;
                        cin.ignore(1000,'\n');
                    }while(spkr->phneNum < 1000000);
                    break;
            case 3: cout << "Current: " << spkr->topic << endl;
                    cout << "Input new speaking topic: ";
                    getline(cin, spkr->topic);
                    break;
            case 4: cout << "Current: " << spkr->fee << endl;
                    do
                    {   
                        cout << "Input new fee's: ";
                        cin >> spkr->fee;
                        cin.ignore(1000,'\n');
                    }while(spkr->fee < 0);
                    break;
            case 5: exit = true;
                    break;
            default: cout << "Invalid menu entry\n";
        }
    }while(!exit);
}
void prntSpk(Speaker *spkr)
{
	const int SPCING = 9;
	cout << setw(SPCING) << "Name" << ": " << spkr->name << endl;
	cout << setw(SPCING) << "Telephone" << ": " << spkr->phneNum 
		<< endl;
	cout << setw(SPCING) << "Topic" << ": " << spkr->topic << endl;
	cout << setw(SPCING) << "Fee's Due" << ": " << spkr->fee 
		<< endl << endl;
}
void PrntBur(Speaker **bureau, int nSpkr)	//Print out full bureau
{
    for(int i=0; i < nSpkr; i++)
    {
        prntSpk(bureau[i]);
    }
}
void fndTpc(Speaker **bureau, int nSpkr, string key) //Search for a speaker topic
{
	bool mtchFnd = false;
	for(int i=0; i < nSpkr; i++)
	{
		if(bureau[i]->topic.find(key) != -1)
		{
			prntSpk(bureau[i]);
			mtchFnd = true;
		}
	}
	if(!mtchFnd)
		cout << "No matches found.\n";
}