//made prime read to ensure all cards and info is there

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
void setBoardNames(Board board[]);
void setBoardColours(Board board[]);
void setBoardBuyPrice(Board board[]);
void setBoardRent(Board board[]);
void setBoardRentHouse1(Board board[]);
void setBoardRentHouse2(Board board[]);
void setBoardRentHouse3(Board board[]);
void setBoardRentHouse4(Board board[]);
void setBoardRentHotel(Board board[]);
void setBoardPropertyOwner(Board board[]);
int rollDice();
void movePlayer(Player player[], Board board[], int x); 

int main(int argc, char** argv) 
{
	Board boardArray[40];
	setBoardNames(boardArray);
	setBoardColours(boardArray);
	setBoardBuyPrice(boardArray);
	setBoardRent(boardArray);
	setBoardRentHouse1(boardArray);
	setBoardRentHouse2(boardArray);
	setBoardRentHouse3(boardArray);
	setBoardRentHouse4(boardArray);
	setBoardRentHotel(boardArray);
	setBoardPropertyOwner(boardArray); 
	
	int numPlayers;
	string playerName;
	int roundNum;
	int turnDoubledRolled;
	int maxNameLength = 10;     
	int position;
	
	char selection; 																// Allows user to input a character selection.
	string turnSelection;
	titleScreen();
	
	for ( ; ; ) 																		// BEGIN GAME OR EXIT
    {
    	cout << "  Enter selection (B or E): "; 										// Prompt for user input. 
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
		cout << "Player " << i+1 << ". Please enter your name. (Max 10 Characters)" << endl;
		cin >> playerName; 																//takes user input of name
		while(playerName.length() > maxNameLength)										//checks if name inputed is greater than 10 charaters
		{
			cout << "Name is too long. Please re-enter your name." << endl;
			cin >> playerName;															//re-enter value of user's name
		}
		playerArray[i].setName(playerName);												//sets name entered to attribute 'name' in player object 
	}
	
	for(int i=0 ; i<numPlayers ; i++)
	{
		system("cls");
		monopolyHeading();
		
		cout << playerArray[i].getName() << "'s turn " << "(Player " << i+1 << " )." << endl;
		cout << "--------------------------------------------------------------------------------" << endl;
		
		cout << "Money Available: $" << playerArray[i].getBalance() << endl;
		cout << "You are at: " << boardArray[playerArray[i].getPosition()].getName() << endl;
		cout <<"\nWhat would you like to do?" << endl;
		vout << "(D) Declare Bankruptcy"
		cout << "(R) Roll Dice." << endl;
		cout << "(T) Trade." << endl;
		cout << "(M) Manage Property" << endl;
		cin >> turnSelection;
		
		if(turnSelection == "R" || turnSelection == "r")
		{
			movePlayer(playerArray, boardArray, i);
		}
		system("pause");
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

void setBoardNames(Board board[])														//sets name of all instances - read in from file
{
	ifstream file;
	file.open("txts/propertyNames.txt");
	string fileArray[40];
	if(file.is_open())
	{
		for(int i=0 ; i<40 ; i++)
		{
			getline(file,fileArray[i]);
		}
	}
	file.close();
	for(int i=0 ; i<40 ; i++)
	{
		board[i].setName(fileArray[i]);
	}
}
void setBoardColours(Board board[])														//sets colour of all instances - read in from file
{
	ifstream file;
	file.open("txts/propertyColour.txt");
	string fileArray[40];
	if(file.is_open())
	{
		for(int i=0 ; i<40 ; i++)
		{
			getline(file,fileArray[i]);
		}
	}
	file.close();
	for(int i=0 ; i<40 ; i++)
	{
		board[i].setColour(fileArray[i]);
	}
}
void setBoardBuyPrice(Board board[])													//sets buying price of all instances - read in from file
{
	ifstream file;
	file.open("txts/propertyPrice.txt");
	int fileArray[40];
	if(file.is_open())
	{
		for(int i=0 ; i<40 ; i++)
		{
			file >> fileArray[i];
		}
	}
	file.close();
	for(int i=0 ; i<40 ; i++)
	{
		board[i].setBuyPrice(fileArray[i]);
	}
}
void setBoardRent(Board board[])														//sets base rent price of all instances - read in from file
{
	ifstream file;
	file.open("txts/propertyBaseRent.txt");
	int fileArray[40];
	if(file.is_open())
	{
		for(int i=0 ; i<40 ; i++)
		{
			file >> fileArray[i];
		}
	}
	file.close();
	for(int i=0 ; i<40 ; i++)
	{
		board[i].setRent(fileArray[i]);
	}
}
void setBoardRentHouse1(Board board[])													//sets rent for 1 house of all instances - read in from file
{
	ifstream file;
	file.open("txts/propertyRentOneHouse.txt");
	int fileArray[40];
	if(file.is_open())
	{
		for(int i=0 ; i<40 ; i++)
		{
			file >> fileArray[i];
		}
	}
	file.close();
	for(int i=0 ; i<40 ; i++)
	{
		board[i].setRentHouse1(fileArray[i]);
	}
}
void setBoardRentHouse2(Board board[])													//sets rent for 2 houses of all instances - read in from file
{
	ifstream file;
	file.open("txts/propertyRentTwoHouse.txt");
	int fileArray[40];
	if(file.is_open())
	{
		for(int i=0 ; i<40 ; i++)
		{
			file >> fileArray[i];
		}
	}
	file.close();
	for(int i=0 ; i<40 ; i++)
	{
		board[i].setRentHouse2(fileArray[i]);
	}
}
void setBoardRentHouse3(Board board[])
{
	ifstream file;
	file.open("txts/propertyRentThreeHouse.txt");
	int fileArray[40];
	if(file.is_open())
	{
		for(int i=0 ; i<40 ; i++)
		{
			file >> fileArray[i];
		}
	}
	file.close();
	for(int i=0 ; i<40 ; i++)
	{
		board[i].setRentHouse3(fileArray[i]);
	}
}
void setBoardRentHouse4(Board board[])
{
	ifstream file;
	file.open("txts/propertyRentFourHouse.txt");
	int fileArray[40];
	if(file.is_open())
	{
		for(int i=0 ; i<40 ; i++)
		{
			file >> fileArray[i];
		}
	}
	file.close();
	for(int i=0 ; i<40 ; i++)
	{
		board[i].setRentHouse4(fileArray[i]);
	}
}
void setBoardRentHotel(Board board[])
{
	ifstream file;
	file.open("txts/propertyRentHotel.txt");
	int fileArray[40];
	if(file.is_open())
	{
		for(int i=0 ; i<40 ; i++)
		{
			file >> fileArray[i];
		}
	}
	file.close();
	for(int i=0 ; i<40 ; i++)
	{
		board[i].setRentHotel(fileArray[i]);
	}
}
void setBoardPropertyOwner(Board board[])
{
	ifstream file;
	file.open("txts/propertyOwner.txt");
	string fileArray[40];
	if(file.is_open())
	{
		for(int i=0 ; i<40 ; i++)
		{
			file >> fileArray[i];
		}
	}
	file.close();
	for(int i=0 ; i<40 ; i++)
	{
		board[i].setOwner(fileArray[i]);
	}
}
int rollDice()
{
	srand(time(NULL));
	int randomNumber = rand() % 6 + 1;
	return randomNumber;
}

void movePlayer(Player player[], Board board[], int x)
{
	int i = x;
	string buySelection;
	int firstRoll = rollDice();
	system("pause");
	int secondRoll = rollDice();
	int rollTotal = firstRoll + secondRoll;
	cout << firstRoll << endl;
	cout << secondRoll << endl;
	
	if(firstRoll == secondRoll)
	{
		player[i].setDoublesRolled(player[i].getDoublesRolled()+1);
	}
	
	player[i].setPosition(player[i].getPosition() + rollTotal);
	if(player[i].getPosition() > 39)
	{
		player[i].setPosition(player[i].getPosition() - 40);
	}
	cout << "You landed on: " << board[player[i].getPosition()].getName() << endl;
	
	//insert if they want to buy property //read in file property owner
}
