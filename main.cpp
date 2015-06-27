#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream> 																		//read in and create text files
#include <cassert> 																		//allows complete exiting from program
#include "player.h" 																	//links player header file to main
#include "board.h" 																		//links board header file to main
using namespace std;

void monopolyHeading();
void titleScreen();

int main(int argc, char** argv) 
{
	int numPlayers;
	string playerName;
	int roundNum;
	int turnDoubledRolled;
	int maxNameLength = 10;     
	
	titleScreen();
	
	for ( ; ; ) 																		// BEGIN GAME OR EXIT
    {
    	cout << "  Enter selection (B or E): "; 										// Prompt for user input. 
    	char selection; 																// Allows user to input a character selection.
	    cin >> selection; 																// Takes in players selection.
        
	    if ((selection == 'b') || (selection == 'B')) 									// If 'b' or 'B' was selected.
		{
	    	break; 																		// It will break the loop and continue down to the player selection.
		}
		
		else if ((selection == 'e') || (selection == 'E')) 								// If 'e' or 'E' was selected
		{
	        system("PAUSE");
            return EXIT_SUCCESS; 														// Exits the program. 
		}
		
		else 																			// If the entered selection was invalid.
		{
			cout << "Please re-enter your selection." << endl;							// Enter selection again.
			cin >> selection;
		}
    }

	cout << endl;
	cout << "How many players? (2-6)" << endl;											//asks how many players for game
	cin >> numPlayers;
	
	while(numPlayers > 6 || numPlayers < 2) 											//if number of players is outside 2-6 asks to re-enter number of players
	{
		cout << "Number of players must be between 2 and 6." << endl;
		cout << "Please enter number of players." << endl;
		cin >> numPlayers; 																//re-enters new value of numPlayers
	}
	
	Player playerArray[numPlayers]; 													//creates array of player instances

	for(int i=0 ; i<numPlayers ; i++)													//loop for each player to enter name
	{
		cout << "Player " << i+1 << ". Please enter your name." << endl;
		cin >> playerName; 																//takes user input of name
		while(playerName.length() > maxNameLength)										//checks if name inputed is greater than 10 charaters
		{
			cout << "Name is too long. Please re-enter your name." << endl;
			cin >> playerName;															//re-enter value of user's name
		}
		
		playerArray[i].setName(playerName);												//sets name entered to attribute 'name' in player object 
		
	}
	
	system("pause");
	return EXIT_SUCCESS;
	
}

void titleScreen()
{
	//Amelia - Title Screen 27/6/15
	char check; // checks that the amount entered was correct.
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "..##.....##..#######..##....##..#######..########...#######..##.......##....##." << endl;
    cout << "..###...###.##.....##.###...##.##.....##.##.....##.##.....##.##........##..##.." << endl; 
	cout << "..####.####.##.....##.####..##.##.....##.##.....##.##.....##.##.........####..." << endl;
	cout << "..##.###.##.##.....##.##.##.##.##.....##.########..##.....##.##..........##...." << endl;  //Title ASCII
	cout << "..##.....##.##.....##.##..####.##.....##.##........##.....##.##..........##...." << endl;
	cout << "..##.....##.##.....##.##...###.##.....##.##........##.....##.##..........##...." << endl;
	cout << "..##.....##..#######..##....##..#######..##.........#######..########....##...." << endl << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "  BEGIN GAME (B)                       |                         EXIT GAME (E)  " << endl; // Directs user to choose option. 
	cout << "--------------------------------------------------------------------------------";    
}
void monopolyHeading() //Amelia 27/6/15
{
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "                                 == MONOPOLY ==                                 " << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
}
