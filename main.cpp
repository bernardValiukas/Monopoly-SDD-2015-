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

int rollDice();
void movePlayer(Player player[], Board board[], int playerID);
void buyProperty(Player player[], Board board[], int playerID, int playerPosition); 
void auction(Player player[], Board board[], int numberPlayers, int propertyPosition);
void trade();
void manageProperty();
void rent(Player player[], Board board[], int playerID);

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
	
	string stringNumPlayers;
	int numPlayers;
	string playerName;
	int roundNum;
	int turnDoubledRolled;
	int maxNameLength = 10;     
	int position;
	
	bool endTurn = false;
	bool diceRolled = false;
	
	string selection; 																// Allows user to input a character selection.
	string turnSelection;
	titleScreen();
	
	for ( ; ; ) 																		// BEGIN GAME OR EXIT
    {
    	cout << "  Enter selection (B or E): "; 										// Prompt for user input. 
	    cin >> selection; 																// Takes in players selection.      
	    if ((selection == "b") || (selection == "B")) 									// If 'b' or 'B' was selected.
		{
	    	break; 																		// It will break the loop and continue down to the player selection.
		}
		else if ((selection == "e") || (selection == "E")) 								// If 'e' or 'E' was selected
		{
	        system("PAUSE");
            return EXIT_SUCCESS; 														// Exits the program. 
		}
    }

	cout << endl;
	cout << "How many players? (2-6)" << endl;											//asks how many players for game
	cin >> stringNumPlayers;

	
	while(stringNumPlayers != "2" && stringNumPlayers != "3" && stringNumPlayers != "4" && stringNumPlayers != "5" && stringNumPlayers != "6")			//if number of players is outside 2-6 asks to re-enter number of players
	{
		cout << "Number of players must be between 2 and 6." << endl;
		cout << "Please enter number of players." << endl;
		cin >> stringNumPlayers; 														//re-enters new value of numPlayers
	}
	numPlayers = atoi(stringNumPlayers.c_str());										//converts string into integer and assign value to numPlayers
	
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
	for ( ; ; )
	{
	
		for(int i=0 ; i<numPlayers ; i++)
		{
			while(endTurn == false)
			{
				system("cls");
				monopolyHeading();
				
				cout << playerArray[i].getName() << "'s turn " << "(Player " << i+1 << " )." << endl;
				cout << "--------------------------------------------------------------------------------" << endl;
				
				cout << "Money Available: $" << playerArray[i].getBalance() << endl;	//prints out player's balance
				cout << "You are at: " << boardArray[playerArray[i].getPosition()].getName() << endl; //prints property player is at
				cout <<"\nWhat would you like to do?" << endl;
				cout << "(D) Declare Bankruptcy" << endl;								//options for the player for each turn
				cout << "(R) Roll Dice." << endl;
				cout << "(T) Trade." << endl;
				cout << "(M) Manage Property" << endl;
				cout << "(E) End turn" << endl;
				cin >> turnSelection;													//reads in player input
				
				if(turnSelection == "R" || turnSelection == "r")						//if player wants to roll dice
				{	
					if(diceRolled == false)												//checks to see if player has already rolled dice for turn
					{
						diceRolled = true;												//bool to say dice has been rolled
						movePlayer(playerArray, boardArray, i);							//function that calls upon rice rolling function and then moves player
						if(boardArray[playerArray[i].getPosition()].getOwner() != -1 && boardArray[playerArray[i].getPosition()].getOwner() != i) // checks if property is owner and player themself doesn't own it
						{
							cout << "Call to rent Function" << endl;
							rent(playerArray, boardArray, i);							//calls rent function
						}
						buyProperty(playerArray, boardArray, i, playerArray[i].getPosition());	//checks if property is available to buy and allows player to purchase
						if(boardArray[playerArray[i].getPosition()].getOwner() == -1 && boardArray[playerArray[i].getPosition()].getColour() != "NULL" ) //checks if property is able to be bought and if player did not buy it
						{
							auction(playerArray, boardArray, numPlayers, playerArray[i].getPosition());		//starts auction for available property
						}
					}
					else
					{
						cout << "You have already rolled your dice for this turn." << endl;
					}
				}
				
				if(turnSelection == "T" || turnSelection == "t")						//if player wants to trade
				{
					trade();
				}
				if(turnSelection == "M" || turnSelection == "m")						//if player wants to manage property
				{
					manageProperty();
				}
				if(turnSelection == "E" || turnSelection == "e")						//if player wants to end turn
				{
					if(diceRolled == false)												//makes player roll dice before they can end turn
					{
						cout << "NOT ALLOWED. You have not rolled your dice for this turn." << endl;
					}
					else
					{
						endTurn = true;													//breaks while loop for player turn
					}
				}
				system("pause");
			}
			
			endTurn = false;															//resets endTurn for next player
			diceRolled = false;															//resets diceRolled for next player
		}
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
void setBoardRentHouse3(Board board[])													//sets rent for 3 houses of all instances - read in from file
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
void setBoardRentHouse4(Board board[])												//sets rent for 4 houses for all instances - read in from file
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
void setBoardRentHotel(Board board[])												//sets rent for a hotel for all instanes - read in from file
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

int rollDice()																		//creates random number between 1-6 for die
{
	srand(time(NULL));																//uses time as a seed to made number
	int randomNumber = rand() % 6 + 1;
	return randomNumber;
}

void movePlayer(Player player[], Board board[], int playerID)									//function to move player along board
{
	int i = playerID;
	int firstRoll = rollDice();																	//calls die rolling function for first die 
	system("pause");																			//pause for time delay in seed for random number
	int secondRoll = rollDice();																//calls die rolling function for second dice
	int rollTotal = firstRoll + secondRoll;
	cout << firstRoll << endl;
	cout << secondRoll << endl;
	
	if(firstRoll == secondRoll)
	{
		player[i].setDoublesRolled(player[i].getDoublesRolled()+1);								//increases doubles rolled count by one
	}
	
	player[i].setPosition(player[i].getPosition() + rollTotal);									//increases player position by total dice scored
	if(player[i].getPosition() > 39)															//checks if position is beyond range of board
	{
		player[i].setPosition(player[i].getPosition() - 40);									//resets position to revolve around board
	}
	cout << "You landed on: " << board[player[i].getPosition()].getName() << endl;				//prints property name of position
}
void buyProperty(Player player[], Board board[], int playerID, int playerPosition)				//function to ask if player wants to buy property
{
	int i = playerID;
	string selection;

	if(board[playerPosition].getColour() != "NULL" && board[playerPosition].getOwner() == -1)	//checks if property is a type that can be bought and if another player owns
	{
		cout << "Would you like to buy this property?(Y/N)" << endl;							
		cin >> selection;																		//user input to buy property
		while(selection != "Y" && selection != "y" && selection != "N" && selection != "n")		//checks if user input is valid (Y/N) || (y/n)
		{
			cout << "Invalid Selection. Would you like to buy this property? (Y/N)" << endl;
			cin >> selection;																	//reads in user input to buy property
		}	
		if(selection == "Y" || selection == "y")												//if player wants to buy
		{
			if(board[playerPosition].getBuyPrice() > player[i].getBalance())					//checks if player has enough money
			{
				cout << "You cannot afford this property." << endl;
			}
			else
			{
				player[i].setBalance(player[i].getBalance() - board[playerPosition].getBuyPrice());	//deducts price of property from user
				board[playerPosition].setOwner(i);												//sets onwner of property using player primary key
				cout << "Property Bought" << endl;
			}
		}
	}
	else if (board[playerPosition].getColour() != "NULL")										//if property is onwned by another player
	{
		cout << "Property Taken" << endl;
	}
	else
	{
		cout << "NULL Property" << endl;

	}
}
void auction(Player player[], Board board[], int numberPlayers, int propertyPosition)					//function to auction property
{																										//
	int playersOut = 0;																					//players that have forfeited
	int playerBid =0;
	int highestBid =9;																					//bids entered have to be at least 10
	int winningID = 0;																					//playerID of current winner of auction
	bool firstRound = false;																			
	bool propertySold = false;
	
	while(propertySold == false)																		//loop that continues until property is sold or no one is interested
	{	
		for(int i = 0; i<numberPlayers; i++)															//player loop
		{
			if(playersOut == numberPlayers-1 && firstRound == true)										//all players execept one have forfeited and that it is past first round
			{
				cout << endl;
				cout << player[winningID].getName() << " (Player " << winningID+1 << ")"<< " bought the property for $" << highestBid << "."<< endl;
				propertySold = true;																	//property has been successfully auctioned
				board[propertyPosition].setOwner(winningID);											//assigns owner of property to ID of winner
				player[winningID].setBalance(player[winningID].getBalance() - highestBid);				//deducts bid from winners account
				break;																					//break player loop
			}
			if(player[i].getAuctionFlag() == 0)															//checks if player has not surrended 
			{
				system("cls");
				monopolyHeading();
				cout << "AUCTION - " << "Starting bid MUST be $10.     " << "Property Available: " << board[propertyPosition].getName() << endl;
				cout << "--------------------------------------------------------------------------------" << endl;
				cout << player[i].getName() << "'s turn. " << "(Player " << i+1 << ")"<< endl;
				if(highestBid != 9)
				{
					cout << "Highest Bid: $" << highestBid << endl; 									//tells user of current wining bid
				}
				cout << "What would you like to bid? (0 means leaves auction)" <<endl;
				cout << "Money Available: $" << player[i].getBalance() << endl;
				cin >> playerBid;

				while(playerBid > player[i].getBalance())												//loop to check if player can afford bid
				{
					cout << "You cannot afford this offer. (Please enter a lower bid)" << endl;
					cin >> playerBid;																	//re-reads player input
				}
				while(playerBid <= highestBid && playerBid !=0)											//checks if bid is greater than highest bid and is not a surrender
				{
					cout << "Bid is not high enough. Please enter higher bid." << endl;
					cin >> playerBid;
				}
				if(playerBid == 0)																		//checks if player wants to surrender
				{
					cout << "You have left the auction." << endl;
					player[i].setAuctionFlag(true);														//sets flag to say user is out of auction
					playersOut = playersOut+1;															//increments player out by one
				}
				else																					//successful bid
				{
					cout << "You have highest bid."  << endl;
					highestBid = playerBid;																//assigns highest bid to what user entered
					winningID = i ;																		//sets current winner to the ID of player
				}
			}
			if(i == numberPlayers-1)																	//used to make sure last player of first round of auction doesn't automatically get property
			{
				firstRound = true;																		//flags first round has happened
			}
			system("pause");
		}
		
		if (playersOut == numberPlayers)																//checks if no players want the auctioned property
		{
			cout << "Property was not sold." << endl;
			break;																						//breaks while loop because property was unable to be sold
		}
		for(int i=0 ;  i<numberPlayers ; i++)															//resets the auction flag for players for the next auction
		{
			player[i].setAuctionFlag(false);
		}
	}
}

void trade()
{
	cout << "Trade Function." << endl;
}

void manageProperty()
{
	cout << "Manage Property function." << endl;
}

void rent(Player player[], Board board[], int playerID)
{
	cout << "Rent Function." << endl;
}
