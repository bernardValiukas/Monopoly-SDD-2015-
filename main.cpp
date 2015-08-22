/*
	Monopoly
	Authors:
		Amelia Paton
		Jackson Valiukas
	Last Edited:
		22-08-15
	Version:
		2.1
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream> 																		//read in and create text files
#include "player.h" 																	//links player header file to main
#include "board.h" 																		//links board header file to main
using namespace std;

//Amelia's Functions
void monopolyHeading();
void titleScreen();
void propertyASCII(Board board[], int propertyID);
void communityChestASCII(int cardID);
void chanceASCII(int cardID);
void diceASCII(int firstRoll, int secondRoll);
void winner();

//Jackson's Functions
void setBoardNames(Board board[]);
void setBoardColours(Board board[]);
void setBoardBuyPrice(Board board[]);
void setBoardRent(Board board[]);
void setBoardRentHouse1(Board board[]);
void setBoardRentHouse2(Board board[]);
void setBoardRentHouse3(Board board[]);
void setBoardRentHouse4(Board board[]);
void setBoardRentHotel(Board board[]);
void setBoardMortgageValue(Board board[]);
void setBoardUnMortgageValue(Board board[]);
void setBoardHouseCost(Board board[]);


int rollDie();																						//returns random number between 1 and 6 for die

void movePlayer(Player player[], Board board[], int playerID, int jailDiceTotal, int roundNum, int numPlayers); //moves player and performs actions for special positions e.g. community chest
void buyProperty(Player player[], Board board[], int playerID, int playerPosition); //checks if player wants to buy property and sells it to them
void auction(Player player[], Board board[], int numberPlayers, int propertyPosition); // performs auction for unowned property
void trade(Player player[], Board board[], int playerID, int numPlayers);	//trade function between players
void manageProperty(Player player[], Board board[], int playerID);	//mortgage/unmortgage propery, sell and buy buildings
void rent(Player player[], Board board[], int playerID, int numPlayers); //function to deduct rent from player if property owned and add to owner.
void colourManage(Player player[], Board board[], int numPlayers);	//checks if a player owns a colour group as well as number of stations/utilities owned
bool isNumeric(string userInput); //checks if a string is numeric and returns true if it is
bool canBuyBuilding(Board board[], string propertyColour, int propertyID);//checks if a player can upgrade a property, returns bool
bool canSellBuilding(Board board[], string propertyColour, int propertyID); //checks if a player can sell a house on a property, returns bool
void chance(Player player[], Board board[], int playerID, int roundNum, int numPlayers); // chance function that performs all the chance card actions
void communityChest(Player player[], Board board[], int playerID, int roundNum, int numPlayers); // community chest function  that performs all the community chance card actions
void bankrupt(Player player[], Board board[], int playerID, string reason, int numPlayers); //allows a player to declare bankruptcy or manage property as well as the transfer of assets to other players and the bank
void inJail(Player player[], Board board[], int playerID, int roundNum, int numPlayers); //player options for when in jail

int main(int argc, char** argv) 
{
	Board boardArray[40];												//initialises the baord to array of 40 instances
	setBoardNames(boardArray);											//sets names of board from file
	setBoardColours(boardArray);										//sets colours of board from file
	setBoardBuyPrice(boardArray);										//sets buy prices of board from file
	setBoardRent(boardArray);											//sets rents of board from file 
	setBoardRentHouse1(boardArray);										//sets rent for 1 house from file
	setBoardRentHouse2(boardArray);										//sets rent for 2 houses from file
	setBoardRentHouse3(boardArray);										//sets rent for 3 houses from file
	setBoardRentHouse4(boardArray);										//sets rent for 4 houses from file
	setBoardRentHotel(boardArray); 										//sets rent for a hotel from hotel
	setBoardMortgageValue(boardArray);									//sets mortgagae value for properties from file
	setBoardUnMortgageValue(boardArray);								//sets unmortgage value for properties from file
	setBoardHouseCost(boardArray);										//sets house cost for properties from file
	
	string stringNumPlayers;											//reads as string first for error checking
	int numPlayers;														//players in game
	string playerName;													//name of player
	int roundNum = 0;	
	int maxNameLength = 10;												//maximum input for name     													
	
	bool endTurn = false;												//sets when a turn is finished for player
	bool diceRolled = false;											//sets that player has rolled already for turn
	
	int bankruptTotal =0;												//number of bankrupt players
	int winnerID = -1;													//sentinel value of winner player ID
	bool validInput = false;											//flag if input is valid
	
	string selection; 													// Allows user to input a character selection to begin game
	string turnSelection;												//player option at player menu
	titleScreen();														//calls the ASCII for monopoly title screen
	
	for ( ; ; ) 																		// BEGIN GAME OR EXIT 							//Contents of infinite loop Amelia
    {
    	cout << "  Enter selection : " << endl; 								// Prompt for user input. 
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
		else if ((selection == "i") || (selection == "I")) // If 'e' or 'E' was selected
		{
	        system("CLS");
	        cout << "--------------------------------------------------------------------------------" << endl;
	        cout << "                                 == MONOPOLY ==                                 " << endl;
	        cout << "                               == INSTRUCTIONS ==                               " << endl;
			cout << "--------------------------------------------------------------------------------" << endl;
			cout << "                                                                                " << endl;
			cout << " SET IT UP!                                                                     " << endl;
			cout << "  Give each player: 5x $1, 1x $5, 2x $10, 1x $20, 1x $50, 4x $100, 2x $500      " << endl;
			cout << "  a total of $1500).                                                            " << endl;
			cout << "  Shuffle the chance cards and the community chest cards.                       " << endl;
			cout << "                                                                                " << endl;
			cout << " PLAY!                                                                          " << endl;
			cout << "  How to win: Move around the board buying as many properties (Streets, Railway " << endl;
			cout << "  Stations and Utillities) as you can. The more you own, the more rent you'll   " << endl;
			cout << "  get. If you're the last player with any money when all other players have     " << endl;
			cout << "  gone bankrupt, you win!                                                       " << endl;
			cout << "                                                                                " << endl;
			cout << " WHO GOES FIRST?                                                                " << endl;
			cout << "  Each player rolls both white dice. The highest roller starts.                 " << endl;
			cout << "                                                                                " << endl;
			cout << " ON YOUR TURN!                                                                  " << endl;
			cout << "  (1) Roll both white dice.                                                     " << endl;
			cout << "  (2) Move forward that number of spaces.                                       " << endl;
			cout << "  (3) Where did you land?                                                       " << endl;
			cout << "  (4) If you rolled a double, roll the dice again, and take another turn.       " << endl;
			cout << "      WATCH OUT! If you roll a double 3 times in the smae turn, you must go     " << endl;
			cout << "      to jail!                                                                  " << endl;
			cout << "  (5) Your turn is over. The player in your left goes next.                     " << endl;
			cout << "                                                                                " << endl;
			cout << " START PLAYING!                                                                 " << endl;
			cout << "  That's all you need to know, so get going!                                    " << endl;
			cout << "                                                                                " << endl;
			cout << "--------------------------------------------------------------------------------" << endl;
			system("PAUSE");
		}
    }

	cout << endl;
	cout << "How many players? (2-6)" << endl;											//asks how many players for game
	cin >> stringNumPlayers;															//reads number of players as string to check for bad input
	validInput = isNumeric(stringNumPlayers);											//checks if input is numeric and returns true/false
	while(validInput == false)															//loop while input is invalid
	{
		cout << "Invalid input." << endl;											
		cout << "Please enter number of players." << endl;
		cin >> stringNumPlayers;														//re-reads new player input
		validInput = isNumeric(stringNumPlayers);										//checks if valid
	}
	numPlayers = atoi(stringNumPlayers.c_str());										//converts string into integer and assign value to numPlayers
	while(numPlayers<2 || numPlayers>6)													//checks if number of players is between 2-6 (inclusive)
	{
		cout << "Number of player must be between 2 and 6." << endl;
		cout << "Please enter number of players." << endl;
		cin >> numPlayers;																//re-reads new number of players
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
	
	for ( ; ; )																			//infinite loop so there are multiple rounds 
	{	
		roundNum += 1;																	//adds one to the round count
		if(winnerID != -1)																//checks of there is a winner
		{
			break;																		//breaks infinite for loop
		}
		
		for(int i=0 ; i<numPlayers ; i++)												//loop to go through all players
		{
			for(int j=0 ; j<numPlayers ; j++)
			{
				if(playerArray[j].getBankruptFlag() == true)							//checks if player is bankrupt
				{
					bankruptTotal += 1;													//increases bannkrupt by one
				}
			}
			
			if(bankruptTotal == numPlayers -1)											//checks if there is only player left that is not bankrupt
			{
				for(int j = 0; j<numPlayers; j++)										//loop to run through number of players
				{
					if(playerArray[j].getBankruptFlag() == false)						//checks of player is not bankrupt
					{
						winnerID = j;													//assigns winnerID to id of player that is not bankrupt
					}
				}
				system("pause");														//pauses program
				break;																	//breaks the player loop
			}			
			
			while(endTurn == false && playerArray[i].getBankruptFlag() == false)		//loop continues if player is not bankrupt and have not ended their turn
			{
				system("cls");															//clears screen
				monopolyHeading();														//ASCII for monopoly heading
				colourManage(playerArray, boardArray, numPlayers);						//checks if any colour groups are owned and number of stations/utilities owned by all players
				
				cout << playerArray[i].getName() << "'s turn " << "(Player " << i+1 << " ).     Round " << roundNum << endl;
				if(playerArray[i].getDoublesRolled() > 0)								//checks of a player has rolled doubles earlier in turn
				{
					cout << "*Extra Roll Available*"<< endl;
				}
				cout << "--------------------------------------------------------------------------------" << endl;
				
				cout << "Money Available: $" << playerArray[i].getBalance() << endl;	//prints out player's balance
				if (playerArray[i].getJailTrack() == -1)								//checks if player is in jail// -1 is sentinel value
				{
					cout << "You are at: " << boardArray[playerArray[i].getPosition()].getName() << endl; //prints property player is at and if not in jail
				}
				else																	//player is in jail
				{
					cout << "You are at: Jail" << endl; //prints that player is at jail
				}
				cout <<"\nWhat would you like to do?" << endl;
				cout << "(D) Declare Bankruptcy" << endl;								//options for the player for each turn
				cout << "(R) Roll Dice." << endl;
				cout << "(T) Trade." << endl;
				cout << "(M) Manage Property" << endl;
				cout << "(E) End turn" << endl;
				cout << "* If doubles are rolled end turn to have the extra roll. *" << endl;


				cin >> turnSelection;													//reads in player input
				
				if(turnSelection == "D" || turnSelection == "d")						// selection is D || d
				{
					bankrupt(playerArray, boardArray, i, "bankReason", numPlayers);		//calls bankrupt function
					if(playerArray[i].getBankruptFlag() == true)						//checks if player is bankrupt
					{
						system("pause");
					}
				}
				
				if(turnSelection == "R" || turnSelection == "r")						//if player wants to roll dice
				{	
					if(diceRolled == false)												//checks to see if player has already rolled dice for turn
					{
						if(playerArray[i].getJailTrack() == -1)							//checks if player is not in jail
						{
							diceRolled = true;												//bool to say dice has been rolled
							movePlayer(playerArray, boardArray, i, 0, roundNum, numPlayers);			//function that calls upon rice rolling function and then moves player
							if(playerArray[i].getPosition() == 30 || playerArray[i].getJailTrack() != -1) //checks if player's new position is go to jail or gone tp jail because 3 doubles thrown in a row
							{
								cout << "Go to Jail. Turn has ended." << endl;
								playerArray[i].setJailTrack(roundNum);					//sets the round that the player was sent to jail
								endTurn = true;											//sets that turn has ended for player
								system("pause");
								break;													//breaks while loop for player menu for player
							}
						}
						else															//jail options // jail track number is not sentinel
						{	
							diceRolled = true;											//sets that player has rolled dice for turn
							inJail(playerArray, boardArray, i, roundNum, numPlayers);	//calls jail function for options while in jail e.g. pay bail
							if(playerArray[i].getBankruptFlag() == true)				//checks if player is bankrupt
							{
								bankruptTotal += 1;										//adds one to the number of bankrupt players
								system("pause");
								break;													//breaks while loop for player menu
							} 
						}
						if(boardArray[playerArray[i].getPosition()].getOwner() != -1 && boardArray[playerArray[i].getPosition()].getOwner() != i) // checks if property has owner and player themself doesn't own it
						{
							if(playerArray[i].getCancelRent() == false)					//checks of rent already collected from chance / community chest
							{
								rent(playerArray, boardArray, i, numPlayers);			//calls rent function
								playerArray[i].setCancelRent(false);					//resets cancel rent flag
							}
							else														
							{
								playerArray[i].setCancelRent(false);					//resets cancel rent flag for next turn
							}
						}
						if(playerArray[i].getCancelBuy() == false)						//checks of player cannot buy property because moved because of chance / community chest
						{
							buyProperty(playerArray, boardArray, i, playerArray[i].getPosition());	//checks if property is available to buy and allows player to purchase
							playerArray[i].setCancelBuy(false);							//resets cancel buy flag
						}
						else
						{
							playerArray[i].setCancelBuy(false);							//resets cancel buy flag
						}
						if(boardArray[playerArray[i].getPosition()].getOwner() == -1 && boardArray[playerArray[i].getPosition()].getColour() != "NULL" ) //checks if property is able to be bought and if player did not buy it
						{
							auction(playerArray, boardArray, numPlayers, playerArray[i].getPosition());		//starts auction for available property
						}
					}
					else																//if player has already rolled dice
					{
						cout << "You have already rolled your dice for this turn." << endl;
					}
				}
				
				if(turnSelection == "T" || turnSelection == "t")						//if player wants to trade
				{
					trade(playerArray, boardArray, i, numPlayers);						//calls trade function
					colourManage(playerArray, boardArray, numPlayers);					//manage colour groups , stations and utilities owned for all players
				}
				if(turnSelection == "M" || turnSelection == "m")						//if player wants to manage property (M || m))
				{
					manageProperty(playerArray, boardArray, i);							//calls manage property function
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
			
			if(playerArray[i].getDoublesRolled() > 0 && playerArray[i].getJailTrack() == -1) // checks of player has rolled doubles and is not in jail
			{
				i = i-1;																//decreases player loop by one to repeat turn of player
			}
			
		}
	}
	system("cls");																		//clears screen
	winner();																			//calls ASCII for winning title
	cout << endl;
	cout << playerArray[winnerID].getName() << " has won MONOPOLY!!!"<< endl;			//prints has won monopoly
	cout << "Game brought to you by Roso's School of Banter." << endl;
	cout << "Made by Amelia Paton and Jackson Valiukas" << endl;
	
	system("pause");
	return EXIT_SUCCESS;									
	
}

void titleScreen()																		//ASCII functiom for title screen
{
	//Amelia - Title Screen 27/6/15
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "..##.....##..#######..##....##..#######..########...#######..##.......##....##." << endl;
    cout << "..###...###.##.....##.###...##.##.....##.##.....##.##.....##.##........##..##.." << endl; 
	cout << "..####.####.##.....##.####..##.##.....##.##.....##.##.....##.##.........####..." << endl;
	cout << "..##.###.##.##.....##.##.##.##.##.....##.########..##.....##.##..........##...." << endl;  //Title ASCII
	cout << "..##.....##.##.....##.##..####.##.....##.##........##.....##.##..........##...." << endl;
	cout << "..##.....##.##.....##.##...###.##.....##.##........##.....##.##..........##...." << endl;
	cout << "..##.....##..#######..##....##..#######..##.........#######..########....##...." << endl << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "  BEGIN GAME (B)                 INSTRUCTIONS (I)                EXIT GAME (E)  " << endl; // Directs user to choose option. 
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
	ifstream file;																		//declares to read in a file called file
	file.open("txts/propertyNames.txt");												//opens file
	string fileArray[40];																//creates array of 40 elements
	if(file.is_open())																	//checks if file is open
	{
		for(int i=0 ; i<40 ; i++)														//loop that runs for 40 times
		{
			getline(file,fileArray[i]);													//assigns line in file to element in array
		}
	}
	file.close();																		//closes file
	for(int i=0 ; i<40 ; i++)															//loop for 40 times
	{
		board[i].setName(fileArray[i]);													//assgins data in element to the attribute in the board instance
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
void setBoardMortgageValue(Board board[])													//sets mortgage value of all instances - read in from file
{
	ifstream file;
	file.open("txts/propertyMortgageValue.txt");
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
		board[i].setMortgageValue(fileArray[i]);
	}
}
void setBoardUnMortgageValue(Board board[])													//sets unmortgage value of all instances - read in from file
{
	ifstream file;
	file.open("txts/propertyUnmortgageValue.txt");
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
		board[i].setUnMortgageValue(fileArray[i]);
	}
}
void setBoardHouseCost(Board board[])												//sets house cost for all instances - read in from file
{
	ifstream file;
	file.open("txts/propertyHouseCost.txt");
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
		board[i].setHouseCost(fileArray[i]);
	}
}

int rollDie()																		//creates random number between 1-6 for die
{
	srand(time(NULL));																//uses time as a seed to made number
	int randomNumber = rand() % 6 + 1;
	return randomNumber;
}

void movePlayer(Player player[], Board board[], int playerID, int jailDiceTotal, int roundNum, int numPlayers)	//function to move player along board
{
	int i = playerID;																//assigns player ID to i
	int firstRoll =0;																//initializes firstRoll
	int secondRoll =0;																//initializes secondRoll
	int rollTotal =0;																//initilizes rollTotal
	if(jailDiceTotal ==0)															//checks if player has not rolled dice from jail
	{
		firstRoll = rollDie();														//calls die rolling function for first die 
		system("pause");															//pause for time delay in seed for random number
		secondRoll = rollDie();														//calls die rolling function for second dice
		rollTotal = firstRoll + secondRoll;											//adds first and second roll together
	}
	else
	{
		rollTotal = jailDiceTotal;													//roll total assigned result of total rolled from jail
	}
	
	diceASCII(firstRoll, secondRoll);												//ASCII function for dice rolled
	if(firstRoll == secondRoll && firstRoll !=0)									//checks if rolled doubles
	{
		cout << "Doubles Rolled!!!" << endl;
		player[i].setDoublesRolled(player[i].getDoublesRolled()+1);					//increases doubles rolled count by one
	}
	else
	{
		player[i].setDoublesRolled(0);												//resets doubles rolled
	}
	if(player[i].getDoublesRolled() !=3)											//if player has not rolled 3 doubles in a row
	{
		player[i].setPosition(player[i].getPosition() + rollTotal);					//increases player position by total dice scored
		if(player[i].getPosition() > 39)											//checks if position is beyond range of board
		{
			player[i].setPosition(player[i].getPosition() - 40);					//resets position to revolve around board
			cout << "Passed GO. Collect $200." << endl;
			player[i].setBalance(player[i].getBalance() + 200);						//adds 200 to player wallet if they have passed go
		}
		cout << "You landed on: " << board[player[i].getPosition()].getName() << endl;		//prints property name of position
		propertyASCII(board, player[i].getPosition());								//calls ascii function for property
		if(board[player[i].getPosition()].getColour() != "NULL")					//if property type is not a station, utility or colour group
		{
			cout << "Colour / Type: " << board[player[i].getPosition()].getColour() << endl; // prints type of property
		}
		
		if(player[i].getPosition() == 2 || player[i].getPosition() == 33) 			//player lands on a community chest
		{
			communityChest(player, board, i, roundNum, numPlayers);					//calls community chest function
		}
		if(player[i].getPosition() == 4) 											// player lamds onincome tax
		{
			string taxOption;														//declares option for tax
			int totalWorth = player[i].getBalance() + player[i].getPropertyWorth() + (player[i].getJailCards()*50); //total worth is balance + cost properties stated on board and jail cards (50)
			int tax = totalWorth/10;												//tax is 10% of total worth
			cout << "Pay $200 tax or 10% of total worth? (200/10)" << endl;
			cin >> taxOption;														//reads in option for tax
			while(taxOption != "200" && taxOption != "10")							//loop while option is not for $200 or 10%
			{
				cout << "Invalid input." << endl;
				cout << "Please enter option." << endl;
				cin >> taxOption;													//reads in new input
			}
			if(taxOption == "200")													//if option was $200
			{
				while(player[i].getBalance() < 200 && player[i].getBankruptFlag() == false) //loop while player cannot afford tax and is not bankrupt
				{
					cout << "Cannot afford tax." << endl;
					bankrupt(player, board, i, "bankReason", numPlayers);			//calls bankrupt function so player can declare bankrupt or manage
				}
				if(player[i].getBankruptFlag() == false)							//if player is not bankrupt
				{
					player[i].setBalance(player[i].getBalance() - 200);				//deduct $200 from wallet
				}
			}
			else if(taxOption == "10")												//option selected was 10%
			{
				while(player[i].getBalance() < tax && player[i].getBankruptFlag() == false)	//loop while player cannot afford tax and is bankrupt
				{	;
					cout << "Cannot afford tax." << endl;
					bankrupt(player, board, i, "bankReason", numPlayers);			//calls bankrupt function
				}
				if(player[i].getBankruptFlag() == false)							//if player is not bankrupt
				{
					cout << "Income tax: $" << tax << endl;
					player[i].setBalance(player[i].getBalance() - tax);				//deduct tax from wallet
				}
			}
		}
		if(player[i].getPosition() == 7 || player[i].getPosition() == 22) 			//if player lands on chance
		{
			chance(player, board, i, roundNum, numPlayers);							//calls chance function
		}
		if(player[i].getPosition() == 38)											//if player lands on super tax
		{
			while(100 > player[i].getBalance() && player[i].getBankruptFlag() == false)	//loop while player cannot afford tax and is not bankrupt
			{
				cout << "Cannot afford tax." << endl;
				bankrupt(player, board, i, "bankReason", numPlayers);				//calls bankrupt fumction
			}
			if(player[i].getBankruptFlag() == false)								//if player is not bankrupt
			{
				player[i].setBalance(player[i].getBalance() -100);					//deducts $100 from wallet
			}
		}
	}
	else																			//if players throws three consecutive doubles
	{
		cout << "Three consecutive doubles thrown." << endl;
		player[i].setPosition(10);													//sends player to jail
		player[i].setJailTrack(roundNum);											//sets round player was sent to jail
		player[i].setDoublesRolled(0);												//resets doubles rolled for player
	}
}
void buyProperty(Player player[], Board board[], int playerID, int playerPosition)	//function to ask if player wants to buy property
{
	int i = playerID;																//assigns player ID to i
	string selection;																//declare selection of player

	if(board[playerPosition].getColour() != "NULL" && board[playerPosition].getOwner() == -1)	//checks if property is a type that can be bought and if another player owns
	{
		cout << "Would you like to buy this property for $" <<board[playerPosition].getBuyPrice() << "?(Y/N)" << endl;							
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
				player[i].setPropertyWorth(player[i].getPropertyWorth() + board[playerPosition].getBuyPrice()); // increases worth of properties bought with board value of property
				board[playerPosition].setOwner(i);												//sets onwner of property using player primary key
				cout << "Property Bought" << endl;
			}
		}
	}

}
void auction(Player player[], Board board[], int numberPlayers, int propertyPosition)					//function to auction property
{																										
	int playersOut = 0;																					//players that have forfeited
	int playerBid =0;																					//bid of player
	int highestBid =9;																					//bids entered have to be at least 10
	int winningID = 0;																					//playerID of current winner of auction
	bool firstRound = false;																			//bool for first round of auction
	bool propertySold = false;																			//flag to see if property bought in auction
	bool validInput = false;																			//flag for valid input
	string stringPlayerBid;
	
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
				player[i].setPropertyWorth(player[i].getPropertyWorth() + highestBid);
				break;																					//break player loop
			}
			if(player[i].getBankruptFlag() == true && player[i].getAuctionFlag() == false)				//checks if player was bankrupt when entering auction
			{	
				player[i].setAuctionFlag(true);															//sets flag so bankrupt player cannot bid
				playersOut = playersOut +1;																//increases number of players out of auction by one
				
			}
			if(player[i].getAuctionFlag() == false && player[i].getBankruptFlag() == false)				//checks if player has not surrended 
			{
				system("cls");																			//clear screen
				monopolyHeading();
				cout << "AUCTION - " << "Starting bid MUST be $10.     " << "Property Available: " << board[propertyPosition].getName() << endl;
				cout << "--------------------------------------------------------------------------------" << endl;
				cout << player[i].getName() << "'s turn. " << "(Player " << i+1 << ")"<< endl;
				if(highestBid != 9)																		//if highest bid is not the first minimum bid
				{
					cout << "Highest Bid: $" << highestBid << endl; 									//tells user of current wining bid
				}
				cout << "What would you like to bid? (0 means leaves auction)" <<endl;
				cout << "Money Available: $" << player[i].getBalance() << endl;
				cin >> stringPlayerBid;																	//reads in bid as string
				validInput = isNumeric(stringPlayerBid);												//checks if bid is fully numeric
				
				while(validInput == false)																//while bid is not numeric
				{
					cout << "Invalid input." << endl;
					cout << "Please enter bid." << endl;
					cin >> stringPlayerBid;																//reads in new bid
					validInput = isNumeric(stringPlayerBid);											//checks if new bid is valid
				}
				playerBid = atoi(stringPlayerBid.c_str());												//converts string bid to numeric that is assigned to an integer variable
				
				while((playerBid > player[i].getBalance()) || (playerBid <=highestBid && playerBid !=0))	//loop to check if player can afford bid
				{
					if(playerBid > player[i].getBalance())												//if player cannot afford bid
					{
						cout << "You cannot afford this offer. (Please enter a lower bid)" << endl;
					}
					if(playerBid <= highestBid)															//if bid is not above lowest bid
					{
						cout << "Bid is not high enough. Please enter higher bid." << endl;
					}
					cin >> stringPlayerBid;																//reads in new bid
					validInput = isNumeric(stringPlayerBid);											//checks if new bid is numeric
					while(validInput == false)															//loop while bid is not numeric
					{
						cout << "Invalid input." << endl;
						cout << "Please enter bid." << endl;
						cin >> stringPlayerBid;															//reads in new bid
						validInput = isNumeric(stringPlayerBid);										//checks if new bid is numeric
					}
					playerBid = atoi(stringPlayerBid.c_str());											//assigns valid bid to an integer variable
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

void trade(Player player[], Board board[], int playerID, int numPlayers)								//function for trade
{
	string stringSelection;																				//string declared for selection
	int selection;																						//integer declared for selection
	int trader1= playerID;																				//assigns ID of player who selected trade to trader1
	int trader2;																						//declare the ID of other player in trade
	bool tradable1[40];																					//array of properties trader1 can offer
	bool tradable2[40];																					//array of properties trader2 can offer
	bool offer1[40];																					//array of properties offered by trader1
	bool offer2[40];																					//array of properties offered by trader2
	int moneyTrade1=0;																					//money offered by trader1
	int moneyTrade2=0;																					//money offered by trader2
	bool validInput = false;																		
	
	string stringTrader2;																				
	
	for(int i=0 ; i<40; i++)																			//loop for all properties
	{
		tradable1[i] = false;																			//sets all elements in trading arrays to falsse
		tradable2[i] = false;
		offer1[i] = false;
		offer2[i] = false;
	}
	system("cls");
	monopolyHeading();
	cout << "Trade - " << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << player[trader1].getName() << "'s turn. " << "(Player " << trader1+1 << ")"<< endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "Player(s) you can trade with." << endl;
	
	for(int i=0 ; i<numPlayers ; i++)																	//loop for number of players
	{
		if(player[i].getBankruptFlag() == false && i != trader1)										//checks of player is not bankrupt and not trader1
		{
			cout << "(" << i+1 << ") " << player[i].getName() << endl; 									//prints ID used by players amd name
		}
	}

	cout << "Enter the player's number that you want to trade with." << endl;
	cin >> stringTrader2;
	validInput = isNumeric(stringTrader2);
	while(validInput == false)
	{
		cout << "Invalid input." << endl;
		cout << "Please enter ID of player you want to trade with." << endl;
		cin >> stringTrader2;
		validInput = isNumeric(stringTrader2);
	}
	trader2 = atoi(stringTrader2.c_str());
	trader2 = trader2 -1;
	while(trader2 == trader1 || player[trader2].getBankruptFlag() == true || trader2 < 0  || trader2 > numPlayers -1)
	{
		cout << "Invalid player selection. Please enter another player number." << endl;
		cin >> stringTrader2;
		validInput = isNumeric(stringTrader2);
		while(validInput == false)
		{
			cout << "Invalid input." << endl;
			cout << "Please enter ID of player you want to trade with." << endl;
			cin >> stringTrader2;
			validInput = isNumeric(stringTrader2);
		}
	}
	trader2 = atoi(stringTrader2.c_str());
	trader2 = trader2 -1;
	
	for(int i=0 ; i<40 ; i++)																			//loop for all properties
	{
		if(board[i].getOwner() == trader1 && board[i].getHouses() == 0)									//checks if owned by trader1 and has no houses
		{
			tradable1[i] = true;																		//assigns that property can be traded by trader1
		}
		if(board[i].getOwner() == trader2 && board[i].getHouses() == 0)									//checks if owned by trader2 and has no houses
		{
			tradable2[i] = true;																		//assigns that property can be trader by trader2
		}
	}
	
	while(selection !=0)																				//while player wants to continue to offer properties
	{
		system("cls");
		monopolyHeading();
		cout << "Trade - " << endl;
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << player[trader1].getName() << "'s turn. " << "(Player " << trader1+1 << ")"<< endl;
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << "Enter Property you want to trade using ID.(0 means stop offering new properties)" << endl;
		cout << "Property you can trade: " << endl;
		
		for(int i=0 ; i<40 ; i++)																		//prints properties that can be offered by trader1
		{
			if(tradable1[i] == true)
			{
				cout << "("<< i << ")" <<" - " << board[i].getName() << endl;
			}
		}
		if(player[trader1].getJailCards() > 0)															//prints if can trade get put of jail cards
		{
			cout <<"(40) Jail Cards at $50" << endl;
		}
		cout << endl;
		cout << "Property Offered: " << endl;
		for(int i =0 ; i<40 ; i++)																		//properties offered by the player so far printed
		{
			if(offer1[i] == true)
			{
				cout << board[i].getName() << endl;
			}
		}
		
		cin >> stringSelection;																			//reads in property ID player wants to offer as string
		validInput = isNumeric(stringSelection);														//checks if offer is numeric
		while(validInput == false)																		//loop while input is not numeric
		{
			cout << "Invalid input." << endl;
			cout << "Please enter property ID that you want to trade." << endl;
			cin >> stringSelection;																		//reads in new propety ID to be offered
			validInput = isNumeric(stringSelection);													//checks if valid
		}
		selection = atoi(stringSelection.c_str());														//assigns string property ID to integer variable
		if(selection == 0)																				//if selection was 0
		{
			cout << "Properties stopped being offered." << endl;
			break;																						//ends properties being offered by trader1
		}		
		if(selection == 40)																				//if player wants to offer jail cards
		{
			if(player[trader1].getJailCards() == 0)														//checks if trader1 has jail cards
			{
				cout << "Do not own any 'Get Out of Jail' cards." << endl;
			}
			else if(player[trader2].getBalance() <50)													//checks if player can afford to pay for cards ($50)
			{
				cout << "Other player cannot afford trade." << endl;
			}
			else																						//if other player can afford and player has cards to offfer
			{
				player[trader2].setBalance(player[trader2].getBalance() -50);							//dedeucts $50 from trdaer2 balance
				player[trader1].setBalance(player[trader1].getBalance() +50);							//adds 50 to trader1 wallet
				player[trader1].setJailCards(player[trader1].getJailCards() - 1);						//deducts number of jail cards trader1 has by one
				player[trader2].setJailCards(player[trader2].getJailCards() + 1);						//adds 1 to number of jail cards trader2 owns
				if(player[trader1].getChanceJailCard() == true)											//if jail card came from chance
				{
					player[trader1].setChanceJailCard(false);											//trader1 jail chance card to false
					player[trader2].setChanceJailCard(true);											//trder2 jail chance card to true
				}
				else																					//if jail card from community chest
				{
					player[trader1].setCommunityJailCard(false);										
					player[trader2].setCommunityJailCard(true);
				}
			}
		}
		while(selection > 40 || selection < 0 || tradable1[selection] == false)							//if property ID not on board and is not tradable option by trader1
		{
			cout << "Invalid property ID entered. Please re-enter ID of property." << endl;
			cin >> stringSelection;																		//reads in new property ID as string
			validInput = isNumeric(stringSelection);													//checks if ID is numeric
			while(validInput == false)																	//loop while is not numeric
			{
				cout << "Invalid input." << endl;
				cout << "Please enter property ID that you want to trade." << endl;
				cin >> stringSelection;																	//reads in new ID
				validInput = isNumeric(stringSelection);												//checks if is numeric
			}
			selection = atoi(stringSelection.c_str());													//assigns valid ID to an integer variable
			if(selection == 0)																			//if player wants to stop offering
			{
				break;																					//breaks offering loop
			}
		}
		if(selection != 0)																				//if ID was not to stop offering
		{
			cout << board[selection].getName() << " was offered." << endl;								//prints property offered
			offer1[selection] = true;																	//makes ID true in offer array
			tradable1[selection] = false;																//makes ID false so property cannot be offered again
		}
		system("pause");		
	}

	selection =-1;																						//resets selection to sentinel
	while(selection !=0)																				//loop while money wants to be offered
	{
		cout << "Would you like to offer money with the trade?" << endl;
		cout << "0 means don't offer money." << endl;
		cin >> stringSelection;																			//reads in money to be traded as string
		validInput = isNumeric(stringSelection);														//checks if input is numeric
		while(validInput == false)																		//loop while input is not numeric
		{
			cout << "Invalid input." << endl;
			cout << "Please enter money you want to offer in trade." << endl;
			cin >> stringSelection;																		//reads in new money offer
			validInput = isNumeric(stringSelection);													//checks if offer is numeric
		}
		selection = atoi(stringSelection.c_str());														//assigns string to an integer variable
		if(selection == 0)																				//if player does not want to offer money
		{
			break;																						//break money offer loop
		}
		while(player[trader1].getBalance() < selection)													//checks of trader1 can afford offer
		{
			cout << "You do not have enough money. Please re-enter amount." << endl;
			cin >> stringSelection;																		//reads in new offer
			validInput = isNumeric(stringSelection);													//check if numeric
			while(validInput == false)																	//loop while input is not numeric
			{
				cout << "Invalid input." << endl;
				cout << "Please enter money you want to offer in trade." << endl;
				cin >> stringSelection;																	//read in new offer
				validInput = isNumeric(stringSelection);												//checks if numeric
			}
			selection = atoi(stringSelection.c_str());													//assigns offer to integer variable
		
		}
		cout << "$" << selection << " was offered." << endl;											//prints the valid offer by palyer
		moneyTrade1 = selection;																		//assigns offer to moneyTrade1
		system("pause");
		break;
	}
	
	selection = -1;																						//resets selection

	while(selection != 0)																				//second trader starts // refer to trader1 process as to how it works for plauer 2
	{
		system("cls");
		monopolyHeading();
		cout << "Trade - " << board[trader1].getName() << endl;
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << player[trader2].getName() << "'s turn for other half of trade. " << "(Player " << trader2+1 << ")"<< endl;
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << "Property you can trade: " << endl;
	
		for(int i=0 ; i<40 ; i++)
		{
			if(tradable2[i] == true)
			{
				cout << "("<< i << ")" <<" - " << board[i].getName() << endl;
			}
		}
		cout << endl;
		cout << "Property Offered:" << endl;
		for(int i=0 ; i<40 ; i++)
		{
			if(offer2[i] == true)
			{
				cout << board[i].getName() << endl;
			}
		}
		if(player[trader2].getJailCards() > 0)
		{
			cout <<"(40) Jail Cards at $50" << endl;
		}
		while(selection !=0)
		{
			cout << "Enter Property you want to trade using ID.(0 means stop offering new properties)" << endl;
			cin >> stringSelection;
			validInput = isNumeric(stringSelection);
			while(validInput == false)
			{
				cout << "Invalid input." << endl;
				cout << "Please enter property ID that you want to trade." << endl;
				cin >> stringSelection;
				validInput = isNumeric(stringSelection);
			}
			selection = atoi(stringSelection.c_str());
			
			if(selection == 0)
			{
				cout << "Properties stopped being offered." << endl;
				break;
			}		
			if(selection == 40)
			{
				if(player[trader2].getJailCards() == 0)
				{
					cout << "Do not own any 'Get Out of Jail' cards." << endl;
				}
				else if(player[trader1].getBalance() <50)
				{
					cout << "Other player cannot afford trade." << endl;
				}
				else
				{
					player[trader1].setBalance(player[trader1].getBalance() -50);
					player[trader2].setBalance(player[trader2].getBalance() +50);
					player[trader2].setJailCards(player[trader2].getJailCards() - 1);
					player[trader1].setJailCards(player[trader1].getJailCards() + 1);
					if(player[trader2].getChanceJailCard() == true)
					{
						player[trader2].setChanceJailCard(false);
						player[trader1].setChanceJailCard(true);
					}
					else
					{
						player[trader2].setCommunityJailCard(false);
						player[trader1].setCommunityJailCard(true);
					}
				}
			}
			
			while(selection > 40 || selection < 0 || tradable2[selection] == false)
			{
				cout << "Invalid property ID entered. Please re-enter ID of property." << endl;
				cin >> stringSelection;
				validInput = isNumeric(stringSelection);
				while(validInput == false)
				{
					cout << "Invalid input." << endl;
					cout << "Please enter property ID that you want to trade." << endl;
					cin >> stringSelection;
					validInput = isNumeric(stringSelection);
				}
				selection = atoi(stringSelection.c_str());
				if(selection ==0)
				{
					break;
				}
			}
			if(selection != 0)
			{
				cout << board[selection].getName() << " was offered." << endl;		
				offer2[selection] = true;
				tradable2[selection] = false;
			}
		}
	}
	selection =-1;
	while(selection !=0)
	{
		cout << "Would you like to offer money with the trade?" << endl;
		cout << "0 means don't offer money." << endl;
		cin >> stringSelection;
		validInput = isNumeric(stringSelection);
		while(validInput == false)
		{
			cout << "Invalid input." << endl;
			cout << "Please enter money you want to offer in trade." << endl;
			cin >> stringSelection;
			validInput = isNumeric(stringSelection);
		}
		selection = atoi(stringSelection.c_str());
		
		if(selection == 0)
		{
			break;
		}
		while(player[trader2].getBalance() < selection)
		{
			cout << "You do not have enough money. Please re-enter amount." << endl;
			cin >> stringSelection;
			validInput = isNumeric(stringSelection);
			while(validInput == false)
			{
				cout << "Invalid input." << endl;
				cout << "Please enter money you want to offer in trade." << endl;;
				cin >> stringSelection;
				validInput = isNumeric(stringSelection);
			}
			selection = atoi(stringSelection.c_str());

		}
		cout << "$" << selection << " was offered." << endl;
		moneyTrade2 = selection;
		break;
	}																							//end of trader2 offer turn
	
	for(int i =0 ; i<40 ; i++)																	//loop for all properties
	{
		if(offer1[i] == true)																	//if trader1 offered property
		{
			board[i].setOwner(trader2);															//set owner to trader2
		}
		if(offer2[i] == true)																	//if trader2 offered property
		{			
			board[i].setOwner(trader1);															//set owner to trader1
		}
	}
	player[trader1].setBalance(player[trader1].getBalance() - moneyTrade1);						//deducts money offered by trader1 balance from trader1 wallet
	player[trader2].setBalance(player[trader2].getBalance() + moneyTrade1);						//adds money offered by trader1 to trader2 balance
	
	player[trader2].setBalance(player[trader2].getBalance() - moneyTrade2);						//deducts money offered by trader1 balance from trader2 wallet
	player[trader1].setBalance(player[trader1].getBalance() + moneyTrade2);						//adds money offered by trader2 to trader1 balance

}																								//end of trade function

void manageProperty(Player player[], Board board[], int playerID)								//manage property function
{
	string stringPropertySelection;
	int propertySelection;
	bool validInput = false;
	bool canSell = false;																		//flag if property can be downgraded
	bool canBuy = false;																		//flag if property can be upgraded
	string selection ="";
	system("cls");
	monopolyHeading();
	cout << "Manage Property - " << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << player[playerID].getName() << "'s turn." << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "Money Available: $" << player[playerID].getBalance() << endl;
	cout << "Property Owned." << endl;
	
	for(int i=0 ; i<40 ; i++)																	//prints all property owned by player and the property ID
	{
		if(board[i].getOwner() == playerID)
		{
			cout << "(" << i << ") " << board[i].getName() << " (" << board[i].getColour() << ")" << endl;
		}
	}
	cout << "Please enter ID of property you want to manage. (0 to exit managing)" << endl;	
	cin >> stringPropertySelection;																//read ID of property to be managed
	validInput = isNumeric(stringPropertySelection);											//checks if ID is numeric
	while(validInput == false)																	//loop while input is numeric
	{
		cout << "Invalid input." << endl;
		cout << "Please enter ID of property you want to manage." << endl;
		cin >> stringPropertySelection;															//read in new input
		validInput = isNumeric(stringPropertySelection);										//checks if new input is numeric
	}
	propertySelection = atoi(stringPropertySelection.c_str());									//assigns string to interger variable
	int i = propertySelection;
	while(board[i].getOwner() != playerID && i != 0)											//checks if player owns property of ID entered
	{
		cout << "You do not own that property." << endl;
		cout << "Please enter property ID." << endl;
		cin >> stringPropertySelection;															//reads in new input
		validInput = isNumeric(stringPropertySelection);										//checks new input
		while(validInput == false)											
		{
			cout << "Invalid input." << endl;
			cout << "Please enter ID of property you want to manage." << endl;
			cin >> stringPropertySelection;														//reads in new input
			validInput = isNumeric(stringPropertySelection);									//checks validity of new input
		}
		propertySelection = atoi(stringPropertySelection.c_str());								//assigns variable to integer 
		i = propertySelection;
	}
	if(propertySelection == 0)																	//checks if input is 0
	{
		cout << "Managing has ended." << endl;													//ends property manage function actions
	}
	else																						//if selection is not 0
	{
		cout << "Manage: " << board[i].getName() << endl;
		cout << "Color/Type: " << board[i].getColour() << endl;										
		if(board[i].getHouses() != 5)															//prints number of houses on property
		{
			cout << "Buildings: "<< board[i].getHouses() << endl;
		}
		else
		{
			cout << "Buildings: Hotel" << endl;
		}
		if(board[i].getMortgageFlag() == false && board[i].getHouses() ==0)						//prints if property can be mortgaged
		{
			cout << "(M) Mortgage property" << endl;
		}
		else
		{
			cout << "(UM) Unmortgage property" << endl;											//prints if property can be unmortgaged
		}
		if(board[i].getColourRentFlag() == true)												//checks if colour group owned
		{
			canBuy = canBuyBuilding(board, board[i].getColour(), i);							//checks of houses can be bought for property through function call
			canSell = canSellBuilding(board, board[i].getColour(), i);							//checks if property can have buildings sold				
			if(canSell == true)																	
			{
				cout << "(SH) Sell houses" << endl;
			}
			if(canBuy == true)
			{
			cout << "(BH) Buy houses" << endl;
			}
		}
		cout << "What would you like to do?" << endl;
		cin >> selection;																		//asks for action regarding property
		if(board[i].getMortgageFlag() == false && (selection == "M" || selection == "m"))		//if player wants to mortgage and property is not already mortgaged
		{
			cout << "Do you want to take a mortgage for $" << board[i].getMortgageValue() << "? (Y/N)" << endl;
			cin >> selection;																	//reads in answer to mortgage
			if(selection == "Y" || selection == "y")											//if they want mortgage
			{
				cout << "Mortgage taken on " << board[i].getName() << endl;
				board[i].setMortgageFlag(true);													//mortgage flag set to true for property
				player[playerID].setBalance(player[playerID].getBalance() + board[i].getMortgageValue()); // adds mortgage value to player wallet
			}
		}
		if(board[i].getMortgageFlag() == true && (selection == "UM" || selection == "um"))		//if player wants to unmortgage and does have a mortgage on property
		{
			cout << "Do you want to unmortgage for $" << board[i].getUnMortgageValue() << "? (Y/N)" << endl; //asks player to confirm decision
			cin >> selection;
			if(selection == "Y" || selection == "y")											//if answer is yes
			{
				if(player[playerID].getBalance() > board[i].getUnMortgageValue())				//checks if can afford mortgage
				{
					cout << "Mortgage taken off " << board[i].getName() << endl;
					board[i].setMortgageFlag(false);											//mortgage flag set to false for property
					player[playerID].setBalance(player[playerID].getBalance() - board[i].getUnMortgageValue());//deducts unmortgage value from player wallet
				}
				else																			//if player cannot afford to unmortgage
				{
					cout << "You cannot afford to unmortgage this property." << endl;
				}
			}
		}
		if(canSell == true && (selection == "SH" || selection == "sh"))							//if player wants to sell buildings and property can be downgraded
		{
			cout << "Do you want to sell a house for $" << board[i].getHouseCost() /2 << endl;
			cin >> selection;
			if(selection == "Y" || selection == "y")											//confirm player decision
			{
				board[i].setHouses(board[i].getHouses() - 1);									//decreases number of houses by one
				player[playerID].setBalance(player[playerID].getBalance() + (board[i].getHouseCost() /2));	//sell price is added to player wallet at half buy price
			}
		}
		if(canBuy == true && (selection == "BH" || selection == "bh"))							//if player want to buy houses and property can be upgraded
		{
			cout << "Do you want to buy a house for $" << board[i].getHouseCost() << endl;
			cin >> selection;																	//confirm player decision
			if(selection == "Y" || selection == "y")
			{
				if(player[playerID].getBalance() > board[i].getHouseCost())						//if player can afford upgrade
				{
					board[i].setHouses(board[i].getHouses() + 1);								//adds 1 to houses on property
					player[playerID].setBalance(player[playerID].getBalance() - board[i].getHouseCost());//deducts house cost from wallet
					player[playerID].setPropertyWorth(player[playerID].getPropertyWorth() + board[i].getHouseCost());//adds house cost to property worth which is used for income tax
				}
				else																			//if player cannot afford upgrade
				{
					cout << "You cannot afford to upgrade this property." << endl;
				}
			}
		}
	}
	
}

void rent(Player player[], Board board[], int playerID, int numPlayers)							//rent function
{
	int i = playerID;
	int position = player[i].getPosition();														//assign position to position of player
	int ownerID = board[position].getOwner();													// assign variable owner of property
	int rent =0;																				//initialise rent to 0
	
	if(board[position].getMortgageFlag() == false)												//if there is no mortgage on property
	{
		if(board[position].getHouses() == 0 && board[position].getColour() != "Station" && board[position].getColour() != "Utility")//if property has no houses and is not a station or utility
		{
			if(board[position].getColourRentFlag() == false)									//if colour group is not owned
			{
				rent =  board[position].getRent();												//assigns rent
			}
			else																				//if colour group owned then double rent
			{
				rent = board[position].getRent()*2;
			}
		}
		if(board[position].getHouses() == 1)													//if one houses owned
		{
			rent = board[position].getRentHouse1();												//assign rent
		}	
		if(board[position].getHouses() == 2)													//if rwo houses owned
		{
			rent = board[position].getRentHouse2();	
		}	
		if(board[position].getHouses() == 3)													//if 3 houses owned
		{
			rent = board[position].getRentHouse3();
		}	
		if(board[position].getHouses() == 4)													//if four houses owned
		{
			rent = board[position].getRentHouse4();
		}	
		if(board[position].getHouses() == 5)													//if property has a hotel
		{
			rent = board[position].getRentHotel();
		}	
		if(board[position].getColour() == "Utility")											//if property is a utility
		{
			srand(time(NULL));
			int firstRoll = rand() % 6+1;														//rolls die
			system("pause");
			int secondRoll = rand() % 6+1;														//rolls another die
			diceASCII(firstRoll, secondRoll);													//displays dice rolled as ASCII
			if(player[ownerID].getUtilitiesOwned() == 1)										//if one utility is owned
			{
				rent = (firstRoll+secondRoll)*4;												//rent is 4 times dice total
			}
			else if(player[ownerID].getUtilitiesOwned() ==2)									//if both utilities owned by one player
			{
				rent = (firstRoll+secondRoll)*10;												//rent is 10 times roll total
			}
		}
		else if(board[position].getColour() == "Station")										//if property is a station
		{
			if(player[ownerID].getStationsOwned() ==1)											//one station owned
			{
				rent = 25;																		//assigns rent
			}
			else if(player[ownerID].getStationsOwned() ==2)										//two stations owned by one player
			{
				rent = 50;
			}
			else if(player[ownerID].getStationsOwned() ==3)										//three stations owned by one player
			{
				rent = 100;
			}
			else if(player[ownerID].getStationsOwned() ==4)										//four stations owned by one player
			{
				rent = 200;
			}
		}
	}
	else																						//mortgage taken out on property
	{
		cout << "Rent cannot be taken on property with mortgage." << endl;					
	}
	while(player[playerID].getBalance() < rent && player[playerID].getBankruptFlag() == false)	//checks if player can afford rent
	{
		cout << "Cannot afford to pay rent." << endl;
		bankrupt(player, board, playerID, "playerReason", numPlayers);							//calls bankrupt function
		system("pause");
	}
	if(player[playerID].getBankruptFlag() == false)												//if player is not bankrupt
	{
		player[playerID].setBalance(player[playerID].getBalance() - rent);						//deducts rent from player
		player[ownerID].setBalance(player[ownerID].getBalance() + rent);						//adds rent collected to owner wallet
		cout << "Rent: $" << rent << endl;
	}
}

void colourManage(Player player[], Board board[], int numPlayers)								//colour manage function
{
	for(int i =0 ; i<40 ; i++)																	//loop for all property
	{
		board[i].setColourRentFlag(false);														//sey colour group owned to false
	}
	for(int i =0 ; i<numPlayers ; i++)															//player loop
	{
		int station = 0;																		//initialise all group groups and property types
		int utility = 0;
		int brown = 0;
		int lightBlue=0;
		int purple = 0;
		int orange = 0;
		int red = 0;
		int yellow =0;
		int green =0;
		int blue =0;
		
		int playerID = i;
		
		for(int j=0 ; j<40 ; j++)																//property loop
		{
			if(board[j].getOwner() == playerID && board[j].getColour() == "Station")			//if property owner matches the current player ID in loop and property is a station
			{
				station += 1;																	//increase stations owned by one
			}
			if(board[j].getOwner() == playerID && board[j].getColour() == "Utility")			
			{
				utility += 1;
			}
			if(board[j].getOwner() == playerID && board[j].getColour() == "Brown")
			{
				brown += 1;
			}		
			if(board[j].getOwner() == playerID && board[j].getColour() == "Light Blue")
			{
				lightBlue += 1;
			}	
			if(board[j].getOwner() == playerID && board[j].getColour() == "Purple")
			{
				purple += 1;
			}		
			if(board[j].getOwner() == playerID && board[j].getColour() == "Orange")
			{
				orange += 1;
			}
			if(board[j].getOwner() == playerID && board[j].getColour() == "Red")
			{
				red += 1;
			}	
			if(board[j].getOwner() == playerID && board[j].getColour() == "Yellow")
			{
				yellow += 1;
			}		
			if(board[j].getOwner() == playerID && board[j].getColour() == "Green")
			{
				green += 1;
			}
			if(board[j].getOwner() == playerID && board[j].getColour() == "Blue")
			{
				blue += 1;
			}																
		}
		player[i].setStationsOwned(station);													//assigns number of stations owned by player to player
		player[i].setUtilitiesOwned(utility);													//assigns number of utilities owned by player to player
		if(brown == 2)																			//if two brown properties owned by player
		{
			board[1].setColourRentFlag(true);													//sets colour group owned by player to property to true
			board[3].setColourRentFlag(true);													//sets colour group owned by plaey to property to true
		}
		if(lightBlue == 3)
		{
			board[6].setColourRentFlag(true);
			board[8].setColourRentFlag(true);
			board[9].setColourRentFlag(true);
		}
		if(purple == 3)
		{
			board[11].setColourRentFlag(true);
			board[13].setColourRentFlag(true);
			board[14].setColourRentFlag(true);
		}
		if(orange == 3)
		{
			board[16].setColourRentFlag(true);
			board[18].setColourRentFlag(true);
			board[19].setColourRentFlag(true);
		}
		if(red == 3)
		{
			board[21].setColourRentFlag(true);
			board[23].setColourRentFlag(true);
			board[24].setColourRentFlag(true);
		}
		if (yellow == 3)
		{
			board[26].setColourRentFlag(true);
			board[27].setColourRentFlag(true);
			board[29].setColourRentFlag(true);
		}
		if(green == 3)
		{
			board[31].setColourRentFlag(true);
			board[32].setColourRentFlag(true);
			board[34].setColourRentFlag(true);
		}
		if(blue == 2)
		{
			board[37].setColourRentFlag(true);
			board[79].setColourRentFlag(true);
		}
	}
}

bool isNumeric(string userInput)														//checks if input from player is numeric
{
	string character;																	
	bool valid = true;																	//string valid until proven not
	for(int i=0 ; i<userInput.length() ; i++)											//loop for user input string length
	{
		character = userInput[i];														//assigns index value of string tp a variable
		if(character != "0" && character != "1" && character != "2" && character != "3" && character != "4" && character != "5" && character != "6" && character != "7" && character != "8" && character != "9") //checks if index is not a numebr
		{
			valid = false;																//sets valid to false
			break;																		//breaks loop because string has non-numeric value in it
		}
	}
	if(valid == false)																	//if string is fully numeric
	{		
		return false;																	//return true from function
	}
	else																				//if string is not valid
	{
		return true;																	//return false from function
	}
}
bool canBuyBuilding(Board board[], string propertyColour, int propertyID)				//function to see if property can be upgraded
{
	int highest = 0;																	//intitializes lower number of houses in colour group to 0
	int lowest = 5;																		//initializes number if houses in colour group to 5
	for(int i=0; i<40 ; i++)															//loop for all properties
	{
		if(board[i].getColour() == propertyColour)										//checks of property in loop matches the colour of propety being checked
		{
			if(board[i].getHouses() < lowest)											//if houses on property is lower than lowest in group so far
			{
				lowest = board[i].getHouses(); 											//assigns lowest to number of houses on property
			}
			if(board[i].getHouses() > highest)											//if houses on property is higher than highest in group so far
			{
				highest = board[i].getHouses(); 										//assigns highest to number of houses on property
			}			
		}
	}
	if(lowest == board[propertyID].getHouses() && highest !=5)							//if houses on property matches lowest in group and is not a maximum number of houses
	{
		return true;																	//returns true from function
	}
	else																				//if houses on property does not match lowest or at maximum
	{
		return false;																	//return false from function
	}
}
bool canSellBuilding(Board board[], string propertyColour, int propertyID)				//function to see if property can be downgraded
{
	int highest = 0;
	int lowest = 5;
	for(int i=0; i<40 ; i++)															//loop for all properties
	{
		if(board[i].getColour() == propertyColour)										//checks if property in loop matches propertbeing checked
		{
			if(board[i].getHouses() < lowest)											//if houses on property is lower than lowest in group so far
			{
				lowest = board[i].getHouses(); 											//assigns lowest to number of houses on property
			}
			if(board[i].getHouses() > highest)											//if houses on property is higher than highest in group so far
			{
				highest = board[i].getHouses(); 										//assigns highest to number of houses on property
			}			
		}
	}
	if(highest == board[propertyID].getHouses() && highest != 0)						//checks if highest in group matches houses on property being checked and higest is not 0
	{
		return true;																	//able to sell houses on property
	}
	else
	{
		return false;																	//not able to sell houses on property
	}
}

void propertyASCII(Board board[], int propertyID)										//function to display ASCII for properties on board
{
	int i = propertyID;																	//assigns ID of property to i
	if (board[i].getName() == "GO")														//checks if name of property using ID matches respective ASCII
	{
        // GO
        cout << "|----------------------------------|" << endl;							//prints ASCII for property to screen
        cout << "|              COLLECT             |" << endl;
        cout << "|            $200 SALARY           |" << endl;
        cout << "|            AS YOU PASS           |" << endl;
        cout << "|   #############   #############  |" << endl;
        cout << "|   ##              ##         ##  |" << endl;
        cout << "|   ##     ######   ##         ##  |" << endl;
        cout << "|   ##         ##   ##         ##  |" << endl;
        cout << "|   ##         ##   ##         ##  |" << endl;
        cout << "|   #############   #############  |" << endl;
        cout << "|      ,'|____________________,    |" << endl;
        cout << "|    -,   ____________________|    |" << endl;
        cout << "|      ',|                         |" << endl;
        cout << "|----------------------------------|" << endl;
	}
	
	if (board[i].getName() == "Old Kent Road")
	{   
    	// BROWN
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|       OLD KENT ROAD       |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                   $2 |" << endl;
		cout << "| Rent with colour set   $4 |" << endl;
		cout << "| Rent with [1]         $10 |" << endl;
		cout << "| Rent with [2]         $30 |" << endl;
		cout << "| Rent with [3]         $90 |" << endl;
		cout << "| Rent with [4]        $160 |" << endl;
		cout << "| Rent with hotel      $250 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost      $50 each |" << endl;
		cout << "| Hotels cost      $50 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
	}
	if(board[i].getName() == "Community Chest")
	{
    	cout << "|---------------------------|" << endl;
		cout << "|                           |" << endl;
		cout << "|        COMMUNITY          |" << endl;
		cout << "|          CHEST            |" << endl;
		cout << "|                           |" << endl;
		cout << "|                           |" << endl;
		cout << "|           _____________ _ |" << endl;
		cout << "|          / /          / / |" << endl;
		cout << "|         / /          / /  |" << endl;
		cout << "|   _____/_/_________/_/    |" << endl;
		cout << "|  |    __     |     |      |" << endl;
		cout << "|  |---{__}----| [ ] |      |" << endl;
		cout << "|  |___________|_____|      |" << endl;
		cout << "|                           |" << endl;
		cout << "|                           |" << endl;
		cout << "|---------------------------|" << endl; 
	}
	
	if (board[i].getName() == "Whitechapel Road")
	{ 
	    // BROWN
	    cout << "|---------------------------|" << endl;
	    cout << "|        TITLE DEED         |" << endl;
        cout << "|     WHITECHAPEL ROAD      |" << endl;
        cout << "|---------------------------|" << endl;
		cout << "| Rent                   $4 |" << endl;
		cout << "| Rent with colour set   $8 |" << endl;
		cout << "| Rent with [1]         $20 |" << endl;
		cout << "| Rent with [2]         $60 |" << endl;
		cout << "| Rent with [3]        $180 |" << endl;
		cout << "| Rent with [4]        $320 |" << endl;
		cout << "| Rent with hotel      $450 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost      $50 each |" << endl;
		cout << "| Hotels cost      $50 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
	}
	
	if(board[i].getName() == "Income Tax")
	{
		cout << "|---------------------------|" << endl;
		cout << "|                           |" << endl;
		cout << "|        INCOME TAX         |" << endl;
		cout << "|                           |" << endl;
		cout << "|                           |" << endl;
		cout << "|                           |" << endl;
		cout << "|                           |" << endl;
		cout << "|            /\\             |" << endl;
		cout << "|            \\/             |" << endl;
		cout << "|                           |" << endl;
		cout << "|                           |" << endl;
		cout << "|                           |" << endl;
		cout << "|                           |" << endl;
		cout << "|         PAY $200          |" << endl;
		cout << "|                           |" << endl;
		cout << "|---------------------------|" << endl;
	}
	
	if (board[i].getName() == "Kings Cross Station")
	{ 
	    // STATION
		cout << "|---------------------------|" << endl;
		cout << "|     _________             |" << endl;
		cout << "|      |  _  |    __        |" << endl;
		cout << "|      | | | |____\\/_       |" << endl;
		cout << "|      | |_| |       \\      |" << endl;
		cout << "|      | __  |  _  _  |     |" << endl;
		cout << "|      |/  \\_|_/ \\/ \\/      |" << endl;
		cout << "|       \\__/   \\_/\\_/	    |" << endl;
		cout << "|                           |" << endl;
		cout << "|        KINGS CROSS        |" << endl;
		cout << "|          STATION          |" << endl;
		cout << "| Rent                  $25 |" << endl;
		cout << "| 2 Stations are owned  $50 |" << endl;
		cout << "| 3 Stations are owned $100 |" << endl;
		cout << "| 4 Stations are owned $200 |" << endl;
		cout << "|---------------------------|" << endl;
    }
    
    if (board[i].getName() == "The Angel Islington")
	{
        // BLUE
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|   THE ANGEL, ISLINGTON    |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                   $6 |" << endl;
		cout << "| Rent with colour set  $12 |" << endl;
		cout << "| Rent with [1]         $30 |" << endl;
		cout << "| Rent with [2]         $90 |" << endl;
		cout << "| Rent with [3]        $270 |" << endl;
		cout << "| Rent with [4]        $400 |" << endl;
		cout << "| Rent with hotel      $550 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost      $50 each |" << endl;
		cout << "| Hotels cost      $50 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
	}
	if(board[i].getName() == "Chance")
	{
		cout << "|---------------------------|" << endl;
		cout << "|                           |" << endl;
		cout << "|          CHANCE           |" << endl;
		cout << "|          ______           |" << endl;
		cout << "|         / ___  \\          |" << endl;
		cout << "|        / /   \\  |         |" << endl;
		cout << "|        |_|    | |         |" << endl;
		cout << "|               | |         |" << endl;
		cout << "|              / /          |" << endl;
		cout << "|             / /           |" << endl;
		cout << "|            / /            |" << endl;
		cout << "|           |_|             |" << endl;
		cout << "|            _              |" << endl;
		cout << "|           |_|             |" << endl;
		cout << "|                           |" << endl;
		cout << "|---------------------------|" << endl;
	}
	
	if(board[i].getName() == "Euston Road")
	{
		// BLUE
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|        EUSTON ROAD        |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                   $6 |" << endl;
		cout << "| Rent with colour set  $12 |" << endl;
		cout << "| Rent with [1]         $30 |" << endl;
		cout << "| Rent with [2]         $90 |" << endl;
		cout << "| Rent with [3]        $270 |" << endl;
		cout << "| Rent with [4]        $400 |" << endl;
		cout << "| Rent with hotel      $550 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost      $50 each |" << endl;
		cout << "| Hotels cost      $50 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
	}
	
	if (board[i].getName() == "Pentonville Road")
	{
	    // BLUE
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|     PENTONVILLE ROAD      |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                   $8 |" << endl;
		cout << "| Rent with colour set  $16 |" << endl;
		cout << "| Rent with [1]         $40 |" << endl;
		cout << "| Rent with [2]        $100 |" << endl;
		cout << "| Rent with [3]        $300 |" << endl;
		cout << "| Rent with [4]        $450 |" << endl;
		cout << "| Rent with hotel      $600 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost      $50 each |" << endl;
		cout << "| Hotels cost      $50 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;	
	}
	if(board[i].getName() == "Just Visiting")
	{
	    cout << "|----------------------------------|" << endl;
            cout << "|  ||  ||  ||  ||  ||  ||          |" << endl;
            cout << "|  ||  ||  ||__||  ||  ||    J     |" << endl;
            cout << "|  ||  ||  |    |  ||  ||          |" << endl;
            cout << "|  ||  ||  | IN |  ||  ||    U     |" << endl;
            cout << "|  ||  ||  |JAIL|  ||  ||          |" << endl;
            cout << "|  ||  ||  | __ |  ||  ||    S     |" << endl;
            cout << "|  ||  ||  ||  ||  ||  ||          |" << endl;
            cout << "|  ||  ||  ||  ||  ||  ||    T     |" << endl;
            cout << "|__||__||__||__||__||__||          |" << endl;
            cout << "|                                  |" << endl;
            cout << "|    V I S I T I N G               |" << endl;
            cout << "|                                  |" << endl;
            cout << "|----------------------------------|" << endl;
	}
	if (board[i].getName() == "Pall Mall")
	{
	    // PINK
        cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|        PALL MALL          |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                  $10 |" << endl;
		cout << "| Rent with colour set  $20 |" << endl;
		cout << "| Rent with [1]         $50 |" << endl;
		cout << "| Rent with [2]        $150 |" << endl;
		cout << "| Rent with [3]        $450 |" << endl;
		cout << "| Rent with [4]        $625 |" << endl;
		cout << "| Rent with hotel      $750 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost     $100 each |" << endl;
		cout << "| Hotels cost     $100 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
	}
	
	if (board[i].getName() == "Electric Company")
	{		
		// UTILITY
		cout << "|---------------------------|" << endl;
		cout << "|             ,/            |" << endl;
		cout << "|           ,'/   	         |" << endl;
		cout << "|         ,' /_____,        |" << endl;
		cout << "|       ,'____   ,'         |" << endl;
		cout << "|            / ,'           |" << endl;
		cout << "|           /.'             |" << endl;
		cout << "|      ELECTRIC COMPANY     |" << endl;
		cout << "|  If one Utility is owned  |" << endl;
		cout << "|   rent is 4 times amount  |" << endl;
		cout << "|      shown on dice.       |" << endl;
		cout << "|                           |" << endl;
		cout << "|   If both Utilities are   |" << endl;
		cout << "|  owned, rent is 10 times  |" << endl;
		cout << "|   amount shown on dice.   |" << endl;
		cout << "|---------------------------|" << endl;
	}
	
	if (board[i].getName() == "Whitehall")
	{	
		// PINK
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|        WHITEHALL          |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                  $10 |" << endl;
		cout << "| Rent with colour set  $20 |" << endl;
		cout << "| Rent with [1]         $50 |" << endl;
		cout << "| Rent with [2]        $150 |" << endl;
		cout << "| Rent with [3]        $450 |" << endl;
		cout << "| Rent with [4]        $625 |" << endl;
		cout << "| Rent with hotel      $750 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost     $100 each |" << endl;
		cout << "| Hotels cost     $100 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
	}
	
	if (board[i].getName() == "Northumberland Avenue")
	{
	 	// PINK
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|   NORTHUMBERLAND AVENUE   |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                  $12 |" << endl;
		cout << "| Rent with colour set  $24 |" << endl;
		cout << "| Rent with [1]         $60 |" << endl;
		cout << "| Rent with [2]        $180 |" << endl;
		cout << "| Rent with [3]        $500 |" << endl;
		cout << "| Rent with [4]        $700 |" << endl;
		cout << "| Rent with hotel      $900 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost     $100 each |" << endl;
		cout << "| Hotels cost     $100 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
	}
	
	if (board[i].getName() == "Marylebone Station")
	{
	    // STATION
		cout << "|---------------------------|" << endl;
		cout << "|     _________             |" << endl;
		cout << "|      |  _  |    __        |" << endl;
		cout << "|      | | | |____\\/_       |" << endl;
		cout << "|      | |_| |       \\      |" << endl;
		cout << "|      | __  |  _  _  |     |" << endl;
		cout << "|      |/  \\_|_/ \\/ \\/      |" << endl;
		cout << "|       \\__/   \\_/\\_/	    |" << endl;
		cout << "|                           |" << endl;
		cout << "|         MARYLEBONE        |" << endl;
		cout << "|          STATION          |" << endl;
		cout << "| Rent                  $25 |" << endl;
		cout << "| 2 Stations are owned  $50 |" << endl;
		cout << "| 3 Stations are owned $100 |" << endl;
		cout << "| 4 Stations are owned $200 |" << endl;
		cout << "|---------------------------|" << endl;
	}
	
	if (board[i].getName() == "Bow Street")
	{	
		// ORANGE 
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|        BOW STREET         |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                  $14 |" << endl;
		cout << "| Rent with colour set  $28 |" << endl;
		cout << "| Rent with [1]         $70 |" << endl;
		cout << "| Rent with [2]        $200 |" << endl;
		cout << "| Rent with [3]        $550 |" << endl;
		cout << "| Rent with [4]        $750 |" << endl;
		cout << "| Rent with hotel      $950 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost     $100 each |" << endl;
		cout << "| Hotels cost     $100 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
	}
	
	if (board[i].getName() == "Marlborough Street")
	{
	 	//ORANGE
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|     MARLBOROUGH STREET    |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                  $14 |" << endl;
		cout << "| Rent with colour set  $28 |" << endl;
		cout << "| Rent with [1]         $70 |" << endl;
		cout << "| Rent with [2]        $200 |" << endl;
		cout << "| Rent with [3]        $550 |" << endl;
		cout << "| Rent with [4]        $750 |" << endl;
		cout << "| Rent with hotel      $950 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost     $100 each |" << endl;
		cout << "| Hotels cost     $100 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
	}
	
	if (board[i].getName() == "Vine Street")
	{
	    // ORANGE
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|        VINE STREET        |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                  $16 |" << endl;
		cout << "| Rent with colour set  $32 |" << endl;
		cout << "| Rent with [1]         $80 |" << endl;
		cout << "| Rent with [2]        $220 |" << endl;
		cout << "| Rent with [3]        $600 |" << endl;
		cout << "| Rent with [4]        $800 |" << endl;
		cout << "| Rent with hotel     $1000 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost     $100 each |" << endl;
		cout << "| Hotels cost     $100 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;	
	}
	
	if (board[i].getName() == "Strand")
	{
	    // RED
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|          STRAND           |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                  $18 |" << endl;
		cout << "| Rent with colour set  $36 |" << endl;
		cout << "| Rent with [1]         $90 |" << endl;
		cout << "| Rent with [2]        $250 |" << endl;
		cout << "| Rent with [3]        $700 |" << endl;
		cout << "| Rent with [4]        $875 |" << endl;
		cout << "| Rent with hotel     $1050 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost     $150 each |" << endl;
		cout << "| Hotels cost     $150 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
	}
	
	if (board[i].getName() == "Fleet Street")
	{
		//RED
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|       FLEET STREET        |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                  $18 |" << endl;
		cout << "| Rent with colour set  $36 |" << endl;
		cout << "| Rent with [1]         $90 |" << endl;
		cout << "| Rent with [2]        $250 |" << endl;
		cout << "| Rent with [3]        $700 |" << endl;
		cout << "| Rent with [4]        $875 |" << endl;
		cout << "| Rent with hotel     $1050 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost     $150 each |" << endl;
		cout << "| Hotels cost     $150 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
	}
	
	if (board[i].getName() == "Trafalgar Square")
	{
		//RED
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|     TRAFALGAR SQUARE      |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                  $20 |" << endl;
		cout << "| Rent with colour set  $40 |" << endl;
		cout << "| Rent with [1]        $100 |" << endl;
		cout << "| Rent with [2]        $300 |" << endl;
		cout << "| Rent with [3]        $750 |" << endl;
		cout << "| Rent with [4]        $925 |" << endl;
		cout << "| Rent with hotel     $1100 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost     $150 each |" << endl;
		cout << "| Hotels cost     $150 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;	
	}
	
	if (board[i].getName() == "Fenchurch St Station")
	{
	 	// STATION
		cout << "|---------------------------|" << endl;
		cout << "|     _________             |" << endl;
		cout << "|      |  _  |    __        |" << endl;
		cout << "|      | | | |____\\/_       |" << endl;
		cout << "|      | |_| |       \\      |" << endl;
		cout << "|      | __  |  _  _  |     |" << endl;
		cout << "|      |/  \\_|_/ \\/ \\/      |" << endl;
		cout << "|       \\__/   \\_/\\_/	    |" << endl;
		cout << "|                           |" << endl;
		cout << "|       FENCHURCH ST        |" << endl;
		cout << "|          STATION          |" << endl;
		cout << "| Rent                  $25 |" << endl;
		cout << "| 2 Stations are owned  $50 |" << endl;
		cout << "| 3 Stations are owned $100 |" << endl;
		cout << "| 4 Stations are owned $200 |" << endl;
		cout << "|---------------------------|" << endl;
    }
    
    if (board[i].getName() == "Leicester Square")
	{
	    //YELLOW
	    cout << "|---------------------------|" << endl;
	    cout << "|        TITLE DEED         |" << endl;
	    cout << "|     LEICESTER SQUARE      |" << endl;
	    cout << "|---------------------------|" << endl;
	    cout << "| Rent                  $22 |" << endl;
	    cout << "| Rent with colour set  $44 |" << endl;
	    cout << "| Rent with [1]        $110 |" << endl;
	    cout << "| Rent with [2]        $330 |" << endl;
	    cout << "| Rent with [3]        $800 |" << endl;
	    cout << "| Rent with [4]        $975 |" << endl;
	    cout << "| Rent with hotel     $1150 |" << endl;
	    cout << "|---------------------------|" << endl;
	    cout << "| Houses cost     $150 each |" << endl;
	    cout << "| Hotels cost     $150 each |" << endl;
	    cout << "|           (plus 4 houses) |" << endl;
	    cout << "|---------------------------|" << endl;
    }
    
    if (board[i].getName() == "Coventry Street")
	{
	    //YELLOW
	    cout << "|---------------------------|" << endl;
	    cout << "|        TITLE DEED         |" << endl;
	    cout << "|     COVENTRTY STREET      |" << endl;
	    cout << "|---------------------------|" << endl;
	    cout << "| Rent                  $22 |" << endl;
	    cout << "| Rent with colour set  $44 |" << endl;
	    cout << "| Rent with [1]        $110 |" << endl;
	    cout << "| Rent with [2]        $330 |" << endl;
	    cout << "| Rent with [3]        $800 |" << endl;
	    cout << "| Rent with [4]        $975 |" << endl;
	    cout << "| Rent with hotel     $1150 |" << endl;
	    cout << "|---------------------------|" << endl;
	    cout << "| Houses cost     $150 each |" << endl;
	    cout << "| Hotels cost     $150 each |" << endl;
	    cout << "|           (plus 4 houses) |" << endl;
	    cout << "|---------------------------|" << endl;
	}
    
    if (board[i].getName() == "Water Works")
	{
        // UTILITY
		cout << "|---------------------------|" << endl;
		cout << "|         [======]	         |" << endl;
		cout << "|    	      ||             |" << endl;
		cout << "|     |]____/  \\____        |" << endl;
		cout << "|     ||_____==___  \\	     |" << endl;
		cout << "|     |]          |_|       |" << endl;
		cout << "|       	                 |" << endl;
		cout << "|       WATER WORKS         |" << endl;
		cout << "|  If one Utility is owned  |" << endl;
		cout << "|   rent is 4 times amount  |" << endl;
		cout << "|      shown on dice.       |" << endl;
		cout << "|                           |" << endl;
		cout << "|   If both Utilities are   |" << endl;
		cout << "|  owned, rent is 10 times  |" << endl;
		cout << "|   amount shown on dice.   |" << endl;
		cout << "|---------------------------|" << endl;
    }
    
	if (board[i].getName() == "Piccadilly")
	{
	    //YELLOW
	    cout << "|---------------------------|" << endl;
	    cout << "|        TITLE DEED         |" << endl;
	    cout << "|        PICCADILLY         |" << endl;
	    cout << "|---------------------------|" << endl;
	    cout << "| Rent                  $24 |" << endl;
	    cout << "| Rent with colour set  $48 |" << endl;
	    cout << "| Rent with [1]        $120 |" << endl;
	    cout << "| Rent with [2]        $360 |" << endl;
	    cout << "| Rent with [3]        $850 |" << endl;
	    cout << "| Rent with [4]       $1025 |" << endl;
	    cout << "| Rent with hotel     $1200 |" << endl;
	    cout << "|---------------------------|" << endl;
	    cout << "| Houses cost     $150 each |" << endl;
	    cout << "| Hotels cost     $150 each |" << endl;
	    cout << "|           (plus 4 houses) |" << endl;
	    cout << "|---------------------------|" << endl;
	}
	
	if (board[i].getName() == "Regent Street")
	{
	 	// GREEN
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|       REGENT STREET       |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                  $26 |" << endl;
		cout << "| Rent with colour set  $52 |" << endl;
		cout << "| Rent with [1]        $130 |" << endl;
		cout << "| Rent with [2]        $390 |" << endl;
		cout << "| Rent with [3]        $900 |" << endl;
		cout << "| Rent with [4]       $1100 |" << endl;
		cout << "| Rent with hotel     $1275 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost     $200 each |" << endl;
		cout << "| Hotels cost     $200 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
    }
    
	if (board[i].getName() == "Oxford Street")
	{    
        // GREEN
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|       OXFORD STREET       |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                  $26 |" << endl;
		cout << "| Rent with colour set  $52 |" << endl;
		cout << "| Rent with [1]        $130 |" << endl;
		cout << "| Rent with [2]        $390 |" << endl;
		cout << "| Rent with [3]        $900 |" << endl;
		cout << "| Rent with [4]       $1100 |" << endl;
		cout << "| Rent with hotel     $1275 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost     $200 each |" << endl;
		cout << "| Hotels cost     $200 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
    }

	if (board[i].getName() == "Bond Street")
	{     
        // GREEN
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|        BOND STREET        |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                  $28 |" << endl;
		cout << "| Rent with colour set  $56 |" << endl;
		cout << "| Rent with [1]        $150 |" << endl;
		cout << "| Rent with [2]        $450 |" << endl;
		cout << "| Rent with [3]       $1000 |" << endl;
		cout << "| Rent with [4]       $1200 |" << endl;
		cout << "| Rent with hotel     $1400 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost     $200 each |" << endl;
		cout << "| Hotels cost     $200 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
    }

	if (board[i].getName() == "Liverpool Street Station")
	{      
        // STATION
		cout << "|---------------------------|" << endl;
		cout << "|     _________             |" << endl;
		cout << "|      |  _  |    __        |" << endl;
		cout << "|      | | | |____\\/_       |" << endl;
		cout << "|      | |_| |       \\      |" << endl;
		cout << "|      | __  |  _  _  |     |" << endl;
		cout << "|      |/  \\_|_/ \\/ \\/      |" << endl;
		cout << "|       \\__/   \\_/\\_/	    |" << endl;
		cout << "|                           |" << endl;
		cout << "|        LIVERPOOL ST       |" << endl;
		cout << "|          STATION          |" << endl;
		cout << "| Rent                  $25 |" << endl;
		cout << "| 2 Stations are owned  $50 |" << endl;
		cout << "| 3 Stations are owned $100 |" << endl;
		cout << "| 4 Stations are owned $200 |" << endl;
		cout << "|---------------------------|" << endl;
    }
    
    if (board[i].getName() == "Park Lane")
	{     
		// BLUE
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|        PARK LANE          |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                  $35 |" << endl;
		cout << "| Rent with colour set  $70 |" << endl;
		cout << "| Rent with [1]        $175 |" << endl;
		cout << "| Rent with [2]        $500 |" << endl;
		cout << "| Rent with [3]       $1100 |" << endl;
		cout << "| Rent with [4]       $1300 |" << endl;
		cout << "| Rent with hotel     $1500 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost     $200 each |" << endl;
		cout << "| Hotels cost     $200 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
    }
 	if(board[i].getName() == "Super Tax")
 	{
		cout << "|---------------------------|" << endl;
		cout << "|                           |" << endl;
		cout << "|                           |" << endl;
		cout << "|                           |" << endl;
		cout << "|           ,==.            |" << endl;
		cout << "|           \\\\//            |" << endl;
		cout << "|          .-~~-.           |" << endl;
		cout << "|        ,\",-\"\"-.\".         |" << endl;
		cout << "|       | |      | |        |" << endl;
		cout << "|       | |      | |        |" << endl;
		cout << "|       \". `,\",-\" ,\"        |" << endl;
		cout << "|          '-~~-'           |" << endl;
		cout << "|                           |" << endl;
		cout << "|        SUPER TAX          |" << endl;
		cout << "|                           |" << endl;
		cout << "|---------------------------|" << endl;
	}
    if (board[i].getName() == "Mayfair")
	{     
        // BLUE
		cout << "|---------------------------|" << endl;
		cout << "|        TITLE DEED         |" << endl;
		cout << "|         MAYFAIR           |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Rent                  $50 |" << endl;
		cout << "| Rent with colour set $100 |" << endl;
		cout << "| Rent with [1]        $200 |" << endl;
		cout << "| Rent with [2]        $600 |" << endl;
		cout << "| Rent with [3]       $1400 |" << endl;
		cout << "| Rent with [4]       $1700 |" << endl;
		cout << "| Rent with hotel     $2000 |" << endl;
		cout << "|---------------------------|" << endl;
		cout << "| Houses cost     $200 each |" << endl;
		cout << "| Hotels cost     $200 each |" << endl;
		cout << "|           (plus 4 houses) |" << endl;
		cout << "|---------------------------|" << endl;
	}
}
void communityChestASCII(int cardID)															//ASCII function for community chest
{
	int i = cardID;																				//assigns ID of community chest card to i
	if(i == 1)																					//if ID of card matches respective number 
	{
		cout << "|-------------------------------------|" << endl;								//prints ASCII for card
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|              BANK ERROR             |" << endl;
	    cout << "|            IN YOUR FAVOUR.          |" << endl;
	    cout << "|             COLLECT $200.           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i == 2)
	{
		cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|            ADVANCE TO GO.           |" << endl;
	    cout << "|            (COLLECT $200)           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i == 3)
	{
		cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|           YOU ARE ASSESSED          |" << endl;
	    cout << "|          FOR STREET REPAIRS.        |" << endl;
	    cout << "|         PAY $40 PER HOUSE AND       |" << endl;
	    cout << "|        $115 PER HOTEL YOU OWN.      |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;	
	}
	if(i == 4)
	{
		cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|            YOU HAVE WON             |" << endl;
	    cout << "|           SECOND PRIZE IN           |" << endl;
	    cout << "|          A BEAUTY CONTEST.          |" << endl;
	    cout << "|             COLLECT $10.            |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;	
	}
	if(i ==5)
	{
		cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|          FROM SALE OF STOCK         |" << endl;
	    cout << "|             YOU GET $50.            |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==6)
	{
		cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|             YOU INHERIT             |" << endl;
	    cout << "|                $100.                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==7)
	{
		cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|         IT IS YOUR BIRTHDAY         |" << endl;
	    cout << "|             COLLECT $10             |" << endl;
	    cout << "|          FROM EVERY PLAYER.         |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==8)
	{
		cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|             RECIEVE $25             |" << endl;
	    cout << "|           CONSULTANCY FEE.          |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==9)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|     | |     | |     | |     | |     |" << endl;
	    cout << "|     | |     | |     | |     | |     |" << endl;
	    cout << "|     | |     | |     | |     | |     |" << endl;
	    cout << "|     | |     | |     | |     | |     |" << endl;
	    cout << "|     | |     | |     | |     | |     |" << endl;
	    cout << "|     | |     | |     | |     | |     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "| GO TO JAIL. GO DIRECTLY TO JAIL, DO |" << endl;
	    cout << "|  NOT PASS GO, DO NOT COLLECT $200.  |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==10)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|            HOSPITAL FEES.           |" << endl;
	    cout << "|               PAY $100              |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==11)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|          INCOME TAX REFUND.         |" << endl;
	    cout << "|             COLLECT $20.            |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==12)
	{
	  	cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|             SCHOOL FEES             |" << endl;
	    cout << "|               PAY $50.              |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==13)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|       LIFE INSURANCE MATURES.       |" << endl;
	    cout << "|            COLLECT $100.            |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==14)
	{
	  	cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|         HOLIDAY FUND MATURES        |" << endl;
	    cout << "|             RECIEVE $100.           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==15)
	{
	  	cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|             DOCTORS FEES            |" << endl;
	    cout << "|               PAY $50.              |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==16)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|           COMMUNITY CHEST           |" << endl;
		cout << "|                                     |" << endl;
	    cout << "|     | |     | |     | |     | |     |" << endl;
	    cout << "|     | |    / /       \\ \\    | |     |" << endl;
	    cout << "|     | |   / /         \\ \\   | |     |" << endl;
	    cout << "|     | |  | |           | |  | |     |" << endl;         
	    cout << "|     | |  \\ \\          / /   | |     |" << endl;
	    cout << "|     | |   \\ \\        / /    | |     |" << endl;
	    cout << "|         GET OUT OF JAIL FREE.       |" << endl;
	    cout << "|     This card may be kept until     |" << endl;
	    cout << "|         needed or traded.           |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}

}
void chanceASCII(int cardID)																	//ASCII function for chance
{
	int i = cardID;																				//assigns ID of card to i
	if(i ==1)																					//if ID of card matches respective number
	{
	    cout << "|-------------------------------------|" << endl;								//prints ASCII for card
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|             ADVANCE TO              |" << endl;
	    cout << "|             PALL MALL.              |" << endl;
	    cout << "|           IF YOU PASS GO,           |" << endl;
	    cout << "|            COLLECT $200.            |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==2)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|     | |     | |     | |     | |     |" << endl;
	    cout << "|     | |    / /       \\ \\    | |     |" << endl;
	    cout << "|     | |   / /         \\ \\   | |     |" << endl;
	    cout << "|     | |  | |           | |  | |     |" << endl;         
	    cout << "|     | |  \\ \\          / /   | |     |" << endl;
	    cout << "|     | |   \\ \\        / /    | |     |" << endl;
	    cout << "|         GET OUT OF JAIL FREE.       |" << endl;
	    cout << "|     This card may be kept until     |" << endl;
	    cout << "|         needed or traded.           |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==3)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|        MAKE GENERAL REPAIRS         |" << endl;
	    cout << "|        ON ALL YOUR PROPERTY:        |" << endl;
	    cout << "|       FOR EACH HOUSE PAY $25,       |" << endl;
	    cout << "|       FOR EACH HOTEL PAY $100.      |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==4)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|            BANK PAYS YOU            |" << endl;
	    cout << "|           DIVIDEND OF $50.          |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==5)
	{
		cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|           ADVANCE TO GO.            |" << endl;
	    cout << "|           (COLLECT $200)            |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==6)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|   ________________________________  |" << endl;
	    cout << "|    ||     ||     ||     ||     ||   |" << endl;
	    cout << "|    ||     ||     ||     ||     ||   |" << endl;
	    cout << "|    ||     ||     ||     ||     ||   |" << endl;
	    cout << "|    ||     ||     ||     ||     ||   |" << endl;
	    cout << "|    ||     ||     ||     ||     ||   |" << endl;
	    cout << "|   _||_____||_____||_____||_____||_  |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|  GO TO JAIL. GO DIRECTLY TO JAIL,   |" << endl;
	    cout << "| DO NOT PASS GO, DO NOT COLLECT $200.|" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==7)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|             ADVANCE TO              |" << endl;
	    cout << "|       THE NEAREST UTILIlITY.        |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|       If UNOWNED, you may           |" << endl;
	    cout << "|      buy it from the Bank.          |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|       If OWNED, throw dice          |" << endl;
	    cout << "|      and pay owner 10 times         |" << endl;
	    cout << "|        the amount thrown.           |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==8)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|             ADVANCE TO              |" << endl;
	    cout << "|          TRAFALGAR SQUARE.          |" << endl;
	    cout << "|           IF YOU PASS GO,           |" << endl;
	    cout << "|            COLLECT $200.            |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==9)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|           YOUR BUILDING             |" << endl;
	    cout << "|           LOAN MATURES.             |" << endl;
	    cout << "|           COLLECT $150.             |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==10)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|           TAKE A TRIP TO            |" << endl;
	    cout << "|        KINGS CROSS STATION.         |" << endl;
	    cout << "|           IF YOU PASS GO,           |" << endl;
	    cout << "|            COLLECT $200.            |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==11)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|             ADVANCE TO              |" << endl;
	    cout << "|              MAYFAIR.               |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==12)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|        YOU HAVE BEEN ELECTED        |" << endl;
	    cout << "|        CHAIRMAN OF THE BOARD.       |" << endl;
	    cout << "|         PAY EACH PLAYER $50.        |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==13)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|          SPEEDING FINE $15          |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==14)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|               GO BACK               |" << endl;
	    cout << "|            THREE SPACES.            |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==15)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|    ADVANCE TO THE NEAREST STATION.  |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|     If UNOWNED, you may buy it      |" << endl;
	    cout << "|           from the Bank.            |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|     If OWNED, pay owner twice       |" << endl;
	    cout << "|      the rental to which they       |" << endl;
	    cout << "|       are otherwise entitled.       |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
	if(i ==16)
	{
	    cout << "|-------------------------------------|" << endl;
	    cout << "|               CHANCE                |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|    ADVANCE TO THE NEAREST STATION.  |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|     If UNOWNED, you may buy it      |" << endl;
	    cout << "|           from the Bank.            |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|     If OWNED, pay owner twice       |" << endl;
	    cout << "|      the rental to which they       |" << endl;
	    cout << "|       are otherwise entitled.       |" << endl;
	    cout << "|                                     |" << endl;
	    cout << "|-------------------------------------|" << endl;
	}
}
void diceASCII(int firstRoll, int secondRoll)                                                               //function to display ascii dice
{
	if (firstRoll == 1 && secondRoll == 1 )                                                                 //checks to see if both dice are equal and outputs ascii
	{
		cout << "+------+       +------+" << endl;
		cout << "|      |       |      |" << endl;
   		cout << "|  <>  |       |  <>  |" << endl;
		cout << "|      |       |      |" << endl;
	    cout << "+------+       +------+" << endl;
	}	
	if(firstRoll == 2 && secondRoll == 2 )
	{
		cout << "+------+       +------+" << endl;
		cout << "|<>    |       |<>    |" << endl;
		cout << "|      |       |      |" << endl;
		cout << "|    <>|       |    <>|" << endl;
		cout << "+------+       +------+" << endl;
	}
	if(firstRoll == 3 && secondRoll == 3)
	{
		cout << "+------+       +------+" << endl;
    	cout << "|<>    |       |<>    |" << endl;
    	cout << "|  <>  |       |  <>  |" << endl;
    	cout << "|    <>|       |    <>|" << endl;
    	cout << "+------+       +------+" << endl;
	}
	if(firstRoll == 4 && secondRoll == 4)
	{
		cout << "+------+       +------+" << endl;
    	cout << "|<>  <>|       |<>  <>|" << endl;
    	cout << "|      |       |      |" << endl;
    	cout << "|<>  <>|       |<>  <>|" << endl;
    	cout << "+------+       +------+" << endl;
	}
	if(firstRoll == 5 && secondRoll == 5)
	{
		cout << "+------+       +------+" << endl;
    	cout << "|<>  <>|       |<>  <>|" << endl;
    	cout << "|  <>  |       |  <>  |" << endl;
    	cout << "|<>  <>|       |<>  <>|" << endl;
    	cout << "+------+       +------+" << endl;
	}
	if(firstRoll == 6 && secondRoll == 6)
	{
		cout << "+------+       +------+" << endl;
    	cout << "|<>  <>|       |<>  <>|" << endl;
    	cout << "|<>  <>|       |<>  <>|" << endl;
    	cout << "|<>  <>|       |<>  <>|" << endl;
    	cout << "+------+       +------+" << endl;	
	}
	if (firstRoll == 1 && secondRoll == 2 || firstRoll == 2 && secondRoll == 1 )                            //checks first and second throw and displays dice and reverse of throws also works
    {
		cout << "+------+       +------+" << endl;
    	cout << "|      |       |<>    |" << endl;
    	cout << "|  <>  |       |      |" << endl;
    	cout << "|      |       |    <>|" << endl;
    	cout << "+------+       +------+" << endl;
	}
	if (firstRoll == 1 && secondRoll == 3 || firstRoll == 3 && secondRoll == 1 )
    {
		cout << "+------+       +------+" << endl;
    	cout << "|      |       |<>    |" << endl;
    	cout << "|  <>  |       |  <>  |" << endl;
    	cout << "|      |       |    <>|" << endl;
    	cout << "+------+       +------+" << endl;
	}
	if (firstRoll == 1 && secondRoll == 4 || firstRoll == 4 && secondRoll == 1 )
    {
		cout << "+------+       +------+" << endl;
    	cout << "|      |       |<>  <>|" << endl;
    	cout << "|  <>  |       |      |" << endl;
    	cout << "|      |       |<>  <>|" << endl;
    	cout << "+------+       +------+" << endl;
	}
	if (firstRoll == 1 && secondRoll == 5 || firstRoll == 5 && secondRoll == 1 )
    {
		cout << "+------+       +------+" << endl;
    	cout << "|      |       |<>  <>|" << endl;
    	cout << "|  <>  |       |  <>  |" << endl;
    	cout << "|      |       |<>  <>|" << endl;
    	cout << "+------+       +------+" << endl;
	}
	if (firstRoll == 1 && secondRoll == 6 || firstRoll == 6 && secondRoll == 1 )
 	{
		cout << "+------+       +------+" << endl;
 		cout << "|      |       |<>  <>|" << endl;
		cout << "|  <>  |       |<>  <>|" << endl;
   		cout << "|      |       |<>  <>|" << endl;
   		cout << "+------+       +------+" << endl;
		}	
	if (firstRoll == 2 && secondRoll == 3 || firstRoll == 3 && secondRoll == 2 )
    {
		cout << "+------+       +------+" << endl;
    	cout << "|<>    |       |<>    |" << endl;
    	cout << "|      |       |  <>  |" << endl;
    	cout << "|    <>|       |    <>|" << endl;	
    	cout << "+------+       +------+" << endl;
	}	
	if (firstRoll == 2 && secondRoll == 4 || firstRoll == 4 && secondRoll == 2 )
    {
		cout << "+------+       +------+" << endl;
    	cout << "|<>    |       |<>  <>|" << endl;
    	cout << "|      |       |      |" << endl;
    	cout << "|    <>|       |<>  <>|" << endl;
    	cout << "+------+       +------+" << endl;
	}
	if (firstRoll == 2 && secondRoll == 5 || firstRoll == 5 && secondRoll == 2 )
    {
		cout << "+------+       +------+" << endl;
	   	cout << "|<>    |       |<>  <>|" << endl;
		cout << "|      |       |  <>  |" << endl;
    	cout << "|    <>|       |<>  <>|" << endl;
    	cout << "+------+       +------+" << endl;
	}
	if (firstRoll == 2 && secondRoll == 6 || firstRoll == 6 && secondRoll == 2 )
    {
		cout << "+------+       +------+" << endl;
	    cout << "|<>    |       |<>  <>|" << endl;
	    cout << "|      |       |<>  <>|" << endl;
	    cout << "|    <>|       |<>  <>|" << endl;
	    cout << "+------+       +------+" << endl;
	}
	if (firstRoll == 3 && secondRoll == 4 || firstRoll == 4 && secondRoll == 3 )
	{
		cout << "+------+       +------+" << endl;
	  	cout << "|<>    |       |<>  <>|" << endl;
	  	cout << "|  <>  |       |      |" << endl;
	   	cout << "|    <>|       |<>  <>|" << endl;
	   	cout << "+------+       +------+" << endl;
	}
	if (firstRoll == 3 && secondRoll == 5 || firstRoll == 5 && secondRoll == 3 )
    {
		cout << "+------+       +------+" << endl;
    	cout << "|<>    |       |<>  <>|" << endl;
    	cout << "|  <>  |       |  <>  |" << endl;
    	cout << "|    <>|       |<>  <>|" << endl;
    	cout << "+------+       +------+" << endl;
	}
	if (firstRoll == 3 && secondRoll == 6 || firstRoll == 6 && secondRoll == 3 )
    {
		cout << "+------+       +------+" << endl;
	   	cout << "|<>    |       |<>  <>|" << endl;
	   	cout << "|  <>  |       |<>  <>|" << endl;
	   	cout << "|    <>|       |<>  <>|" << endl;
	   	cout << "+------+       +------+" << endl;
	}
	if (firstRoll == 4 && secondRoll == 5 || firstRoll == 5 && secondRoll == 4 )
    {
		cout << "+------+       +------+" << endl;
    	cout << "|<>  <>|       |<>  <>|" << endl;
    	cout << "|      |       |  <>  |" << endl;
    	cout << "|<>  <>|       |<>  <>|" << endl;
    	cout << "+------+       +------+" << endl;
	}
	if (firstRoll == 4 && secondRoll == 6 || firstRoll == 6 && secondRoll == 4 )
    {
		cout << "+------+       +------+" << endl;
    	cout << "|<>  <>|       |<>  <>|" << endl;
    	cout << "|      |       |<>  <>|" << endl;
    	cout << "|<>  <>|       |<>  <>|" << endl;
    	cout << "+------+       +------+" << endl;
	}
	if (firstRoll == 5 && secondRoll == 6 || firstRoll == 6 && secondRoll == 5 )
    {
		cout << "+------+       +------+" << endl;
    	cout << "|<>  <>|       |<>  <>|" << endl;
    	cout << "|  <>  |       |<>  <>|" << endl;
    	cout << "|<>  <>|       |<>  <>|" << endl;
    	cout << "+------+       +------+" << endl;
	}
	return;                                                                                                //return to main loop
}

void chance(Player player[], Board board[], int playerID, int roundNum, int numPlayers)						//function for chance actions
{
	srand(time(NULL));																						//uses time as a seed to made number
	int cardID = rand() % 16 + 1;																			//makes random number for card ID to be used
	int i = playerID;
	bool chanceJailCard = false;																			//initialise if jail card has been picked up by player
	
	for(int i=0 ; i<numPlayers ; i++)																		//checks if any player own the jail card for chance
	{
		if(player[i].getChanceJailCard() == true)
		{
			chanceJailCard = true;	
		}
	}
	
	while(cardID == 2 && chanceJailCard == true)															//generates new card ID if jail card ID selected and card has already been taken
	{
		cardID = rand() % 16+1;
	}
	chanceASCII(cardID);
	
	if(cardID == 1) //ADVANCE TO PALL MALL. IF YOU PASS GO, COLLECT $200.
	{
		if(player[i].getPosition() == 7)
		{
			player[i].setPosition(11);
		}
		else
		{
			player[i].setPosition(11);
			player[i].setBalance(player[i].getBalance() + 200);
		}
		player[i].setCancelBuy(true);
	}
	if(cardID == 2) //GET OUT OF JAIL FREE. This card may be kept until needed or traded.
	{
		player[i].setJailCards(player[i].getJailCards()+1);
		player[i].setChanceJailCard(true);
	}
	if(cardID == 3) //MAKE GENERAL REPAIRS ON ALL YOUR PROPERTY: FOR EACH HOUSE PAY $25, FOR EACH HOTEL PAY $100.
	{
		int housesOwned =0;
		int hotelsOwned =0;
		int totalPayment =0;
		
		for(int j =0 ; j<40 ; j++)
		{
			if(board[j].getOwner() == i && board[j].getHouses() !=5)
			{
				housesOwned = housesOwned + board[j].getHouses();
			}
			else if(board[j].getOwner() == i && board[j].getHouses() ==5)
			{
				hotelsOwned = hotelsOwned + 1;
			}
		}
		totalPayment = (housesOwned*25) + (hotelsOwned*100);
		cout << "Repair cost: $" << totalPayment << endl;
		while(totalPayment > player[i].getBalance() && player[i].getBankruptFlag() == false)
		{
			bankrupt(player, board, i, "bankReason", numPlayers);
		}
		if(player[i].getBankruptFlag() == false)
		{
			player[i].setBalance(player[i].getBalance() - totalPayment);		
		}
	}
	if(cardID ==4) //BANK PAYS YOU DIVIDEND OF $50.
	{
		player[i].setBalance(player[i].getBalance()+50);
	}
	if(cardID ==5) //ADVANCE TO GO. (COLLECT $200)
	{
		player[i].setPosition(0);
		player[i].setBalance(player[i].getBalance() +200);
	}
	if(cardID ==6) //GO TO JAIL. GO DIRECTLY TO JAIL, DO NOT PASS GO, DO NOT COLLECT $200.
	{
		player[i].setPosition(10);
		player[i].setJailTrack(roundNum);
	}
	if(cardID ==7) //ADVANCE TO THE NEAREST UTILITY. IF UNOWNED, YOU MAY BUY IT FROM THE BANK. IF OWNED, THROW DICE AND PAY OWNER 10 TIMES THE AMOUNT THROWN.
	{
		int utilityPayment = 0;
		if(player[i].getPosition() == 7)
		{
			cout << "Nearest Utility: " << board[12].getName() << endl;
			player[i].setPosition(12);
			if(board[12].getOwner() == -1)
			{
				buyProperty(player, board, playerID, 12);
				if(board[12].getOwner() == -1)
				{
					auction(player, board, numPlayers, 12 );
				}
			}
			else if(board[12].getOwner() != i)
			{
				int firstRoll = rollDie();
				int secondRoll = rollDie();
				utilityPayment = (firstRoll+secondRoll)*10;
				diceASCII(firstRoll, secondRoll);
				while(utilityPayment > player[i].getBalance() && player[i].getBankruptFlag() == false)
				{
					bankrupt(player, board, i, "playerReason", numPlayers );
				}
				if(player[i].getBankruptFlag() == false)
				{
					player[i].setBalance(player[i].getBalance() - utilityPayment);
				}
			}
		}
		if(player[i].getPosition() == 22)
		{
			cout << "Nearest Utility: " << board[28].getName();
			player[i].setPosition(28);
			if(board[28].getOwner() == -1 && player[i].getBankruptFlag() == false)
			{
				buyProperty(player, board, playerID, 28);
				if(board[28].getOwner() == -1)
				{
					auction(player, board, numPlayers, 28 );
				}
			}
			else if(board[12].getOwner() != i)
			{
				int firstRoll = rollDie();
				int secondRoll = rollDie();
				utilityPayment = (firstRoll+secondRoll)*10;
				diceASCII(firstRoll, secondRoll);
				while(utilityPayment > player[i].getBalance() && player[i].getBankruptFlag() == false)
				{
					bankrupt(player, board, i, "playerReason", numPlayers );
				}
				if(player[i].getBankruptFlag() == false)
				{
					player[i].setBalance(player[i].getBalance() - utilityPayment);
					cout << "Rent: $" << utilityPayment << endl;
					player[i].setCancelRent(true);
					
					int ownerID = board[player[i].getPosition()].getOwner();
					player[ownerID].setBalance(player[ownerID].getBalance() + utilityPayment);
				}				
			}
		}
	}
	if(cardID ==8) //ADVANCE TO TRAFALGAR SQUARE, IF YOU PASS GO, COLLECT $200.
	{
		if(player[i].getPosition() == 7)
		{
			player[i].setPosition(24);
		}
		else
		{
			player[i].setPosition(24);
			player[i].setBalance(player[i].getBalance() +200);
		}
		player[i].setCancelBuy(true);
	}
	if(cardID ==9) //YOUR BUILDING LOAN MATURES. COLLECT $150.
	{
		player[i].setBalance(player[i].getBalance() +150);
	}
	if(cardID ==10) //TAKE A TRIP TO KINGS CROSS STATION. IF YOU PASS GO, COLLECT $200.
	{
		player[i].setPosition(5);
		player[i].setBalance(player[i].getBalance() +200);
		player[i].setCancelBuy(true);
	}
	if(cardID ==11) //ADVANCE TO MAYFAIR.
	{
		player[i].setPosition(39);
		player[i].setCancelBuy(true);
	}
	if(cardID == 12) //YOU HAVE BEEN ELECTED CHAIRMAN OF THE BOARD. PAY EACH PLAYER $50.
	{
		int toPay =0;
		int chairmanPayment =0;
		for(int j=0 ; j<40 ; j++)
		{
			if(player[j].getBankruptFlag() ==false && j != i)
			{
				toPay = toPay +1;
			}
		}
		while(player[i].getBalance() < toPay*50 && player[i].getBankruptFlag() == false)
		{
			bankrupt(player,board, i, "bankReason", numPlayers);
		}
		if(player[i].getBankruptFlag() == false)
		{
			player[i].setBalance(player[i].getBalance() - (toPay*50));
			for(int j =0 ; j<numPlayers ; j++)
			{
				if(player[j].getBankruptFlag() == false && j != i);
				{
					player[j].setBalance(player[j].getBalance() + 50);
				}
			}
		}		
		
	}
	if(cardID == 13) //SPEEDING FINE $15.
	{
		while(15 > player[i].getBalance() && player[i].getBankruptFlag() == false)
		{
			bankrupt(player, board, i, "bankReason", numPlayers );
		}
		if(player[i].getBankruptFlag() == false)
		{
			player[i].setBalance(player[i].getBalance() - 15);
		}
		player[i].setBalance(player[i].getBalance() - 15);
	}
	if(cardID ==14) //GO BACK THREE SPACES.
	{
		player[i].setPosition(player[i].getPosition() -3);
	}
	if(cardID == 15 || cardID == 16) //ADVANCE TO THE NEAREST STATION. IF UNOWNED, YOU MAY BUY IT FROM THE BANK. IF OWNED, PAY OWNER TWICE THE RENTAL TO WHICH THEY ARE OTHERWISE ENTITLED.
	{
		int playerPosition = player[i].getPosition();
		int current =0;
		int rentToPay =0;
		while(board[current].getColour() != "Station")
		{
			current = current + 1;
		}
		cout << "Nearest Station: " << board[current].getName() << endl;
		player[i].setPosition(current);
		if(board[current].getOwner() == -1)
		{
			buyProperty(player, board, i, current);
			if(board[current].getOwner() == -1 && player[i].getBankruptFlag() == false)
			{
				auction(player, board, numPlayers, current);
			}
		}
		else if(board[i].getOwner() != i)
		{
			int owner = board[current].getOwner();
			int stationsOwned = player[owner].getStationsOwned();
			if(player[owner].getStationsOwned() ==1)
			{
				rentToPay = 50; 
			}
			else if(player[owner].getStationsOwned() ==2)
			{
				rentToPay = 100; 
			}
			else if(player[owner].getStationsOwned() ==3)
			{
				rentToPay = 200; 
			}			
			else if(player[owner].getStationsOwned() ==4)
			{
				rentToPay = 400; 
			}
			cout << "Rent: $" << rentToPay << endl;
			player[i].setCancelRent(true);
		}
		while(rentToPay > player[i].getBalance() && player[i].getBankruptFlag() == false)
		{
			bankrupt(player, board, i, "playerReason", numPlayers );
		}
		if(player[i].getBankruptFlag() == false)
		{
			player[i].setBalance(player[i].getBalance() - rentToPay);
			int ownerID = board[player[i].getPosition()].getOwner();
			player[ownerID].setBalance(player[ownerID].getBalance() + rentToPay);
		}
	}
}
void communityChest(Player player[], Board board[], int playerID, int roundNum, int numPlayers)
{
	srand(time(NULL));																//uses time as a seed to made number
	int cardID = rand() % 16 + 1;
	int i = playerID;
	bool communityJailCard = false;
	
	for(int i=0 ; i<numPlayers ; i++)
	{
		if(player[i].getCommunityJailCard() == true)
		{
			communityJailCard = true;	
		}
	}
	
	while(cardID == 16 && communityJailCard == true)
	{
		cardID = rand() % 16+1;
	}
	communityChestASCII(cardID);
	
	if(cardID == 1) //BANK ERROR IN YOUR FAVOUR COLLECT $200.
	{
		player[i].setBalance(player[i].getBalance() +200);	
	}
	if(cardID ==2) //ADVANCE TO GO (COLLECT $200).
	{
		player[i].setPosition(0);
		player[i].setBalance(player[i].getBalance() + 200);	
	}
	if(cardID == 3) //YOU ARE ASSESSED FOR STREET REPAIRS: PAY $40 PER HOUSE AND $115 PER HOTEL YOU OWN.
	{
		int housesOwned =0;
		int hotelsOwned  =0;
		int totalPayment =0;
		
		for(int j =0 ; j<40 ; j++)
		{
			if(board[j].getOwner() == i && board[j].getHouses() !=5)
			{
				housesOwned = housesOwned + board[j].getHouses();
			}
			else if(board[j].getOwner() == i && board[j].getHouses() ==5)
			{
				hotelsOwned = hotelsOwned + 1;
			}
		}
		totalPayment = (housesOwned*40) + (hotelsOwned*115);
		cout << "Repair cost: $" << totalPayment << endl;
		while(totalPayment > player[i].getBalance() && player[i].getBankruptFlag() == false)
		{
			bankrupt(player, board, i, "bankReason", numPlayers );
		}
		if(player[i].getBankruptFlag() == false)
		{
			player[i].setBalance(player[i].getBalance() - totalPayment);
		}		
	}
	if(cardID ==4) //YOU HAVE WON SECOND PRIZE IN A BEAUTY CONTEST. COLLECT $10.
	{
		player[i].setBalance(player[i].getBalance() +10);
	}
	if(cardID ==5) //FROM SALE OF STOCK YOU GET $40.
	{
		player[i].setBalance(player[i].getBalance() +40);
	}
	if(cardID ==6) //YOU INHERIT $100.
	{
		player[i].setBalance(player[i].getBalance() +100);
	}
	if(cardID ==7) //IT IS YOUR BIRTHDAY. COLLECT $10 FROM EVERY PLAYER.
	{
		int canPayID = -1;
		for(int j=0 ; j<numPlayers ; j++)
		{
			while(player[j].getBalance() < 10 && player[j].getBankruptFlag() ==false && j != i)
			{
				bankrupt(player, board, j, "playerReason", numPlayers);
			}
			if(player[j].getBankruptFlag() == false)
			{
				player[j].setBalance(player[j].getBalance() -10);
				player[i].setBalance(player[i].getBalance() +10);
			}
		}
	}
	if(cardID ==8) //RECEIVE $25 CONSULTANCY FEE.
	{
		while(25 > player[i].getBalance() && player[i].getBankruptFlag() == false)
		{
			bankrupt(player, board, i, "bankReason", numPlayers );
		}
		if(player[i].getBankruptFlag() == false)
		{
			player[i].setBalance(player[i].getBalance() - 25);
		}
	}	
	if(cardID ==9) //GO TO JAIL. GO DIRECTLY TO JAIL, DO NOT PASS GO, DO NOT COLLECT $200.
	{
		player[i].setPosition(10);
		player[i].setJailTrack(roundNum);
	}
	if(cardID ==10) //HOSPITAL FEES. PAY $10.
	{
		while(10 > player[i].getBalance() && player[i].getBankruptFlag() == false)
		{
			bankrupt(player, board, i, "bankReason", numPlayers );
		}
		if(player[i].getBankruptFlag() == false)
		{
			player[i].setBalance(player[i].getBalance() - 10);
		}
	}
	if(cardID ==11) //INCOME TAX REFUND. COLLECT $20.
	{
		player[i].setBalance(player[i].getBalance() +20);
	}
	if(cardID ==12) //SCHOOL FEES. PAY $50.
	{
		while(50 > player[i].getBalance() && player[i].getBankruptFlag() == false)
		{
			bankrupt(player, board, i, "bankReason", numPlayers );
		}
		if(player[i].getBankruptFlag() == false)
		{
			player[i].setBalance(player[i].getBalance() - 50);
		}
	}
	if(cardID == 13) //LIFE INSURANCE MATURES. COLLECT $100.
	{
		player[i].setBalance(player[i].getBalance() +100);
	}
	if(cardID == 14) //HOLIDAY FUND MATURES. RECEIVE $100.
	{
		player[i].setBalance(player[i].getBalance() +100);
	}
	if(cardID == 15) //DOCTOR'S FEES. PAY $50.
	{
		while(50 > player[i].getBalance() && player[i].getBankruptFlag() == false)
		{
			bankrupt(player, board, i, "bankReason", numPlayers );
		}
		if(player[i].getBankruptFlag() == false)
		{
			player[i].setBalance(player[i].getBalance() - 50);
		}
	}
	if(cardID == 16) //GET OF JAIL FREE. This card may be kept until needed or traded.
	{
		player[i].setJailCards(player[i].getJailCards() +1);
		player[i].setCommunityJailCard(true);
	}
}
void bankrupt(Player player[], Board board[], int playerID, string reason, int numPlayers) // function if player cannot afford to pay
{
	string selection;
	int receiveAssetID =-1;																	//initalize ID of owner of property
	cout << "(D) Declare bankruptcy" << endl;
	cout << "(M) Manage property" << endl;
	cin >> selection;																		//reads in player option
	while(selection != "D" && selection != "d" && selection != "M" && selection != "m")		//loop if input is not M || D
	{
		cout << "Invalid input." << endl;
		cout << "Please enter selection." << endl;
		cin >> selection;																	//read in new input
	}
	
	
	if(selection == "M" || selection == "m")												//if player chooses to manage property
	{
		manageProperty(player, board, playerID);											//calls manage property function
	}
	else if(selection == "D" || selection == "d")											//if player chooses to declare bankruptcy
	{
		cout << "You are now bankrupt. GAME OVER!!!" << endl;
		player[playerID].setBankruptFlag(true);												//sets bankrupt flag to true for player
		if(reason == "playerReason")														//if bankrupt because of another player e.g rent 
		{
			receiveAssetID = board[player[playerID].getPosition()].getOwner();				//assign receive assets ID to owner of property bankrupt player is on
			player[receiveAssetID].setJailCards(player[receiveAssetID].getJailCards() + player[playerID].getJailCards());	//transfer all jailcards to player
			player[receiveAssetID].setBalance(player[receiveAssetID].getBalance() + player[playerID].getBalance());			//gives remaining balance to owner
			player[playerID].setBalance(0);													//sets bankrupt player balance to 0
			player[playerID].setJailCards(0);												//sets bankrupt player jail cards to 0
			
			for(int i=0 ; i<40 ; i++)														//loop through all properties
			{
				if(board[i].getOwner() == playerID && board[i].getMortgageFlag() == true)	//checks if bankrupt player has mortgage on property
				{
					board[i].setOwner(receiveAssetID);										//transfer property ownership to player receiving assets
					cout << "Do you want to repay the mortgage for " << board[i].getName() << " at $" << board[i].getUnMortgageValue() <<" now? (Y/N)" << endl;
					cin >> selection;														//checks if new owner wants to pay new mortgage now
					while(selection != "Y" &&  selection != "y" && selection != "N" && selection != "n") //checks that input is yes or no
					{
						cout << "Invalid input." << endl;
						cout << "Please enter selection." << endl;
						cin >> selection;													//reads in new input
					}
					if(selection == "Y" || selection == "y")								//if they choose to pay mortgage
					{
						if(player[receiveAssetID].getBalance() > board[i].getUnMortgageValue())//check if can afford
						{
						cout << "Mortgage paid for " << board[i].getName() << ".";
						board[i].setMortgageFlag(false);									//mortgage flag removed frpom property
						player[receiveAssetID].setBalance(player[receiveAssetID].getBalance() - board[i].getUnMortgageValue()); // deduct unmortgage cost from new owner wallet
						}
						else																//if cannot afford to pay mortgage now
						{
							cout << "Cannot afford to unmortgage at present time." << endl;
						}
					}
					else																	//player has to pay interest now for mortgaged property
					{
						cout << "$" << board[i].getUnMortgageValue() - board[i].getMortgageValue() << " to keep mortgage." << endl;
						if(player[receiveAssetID].getBalance() < board[i].getUnMortgageValue() - board[i].getMortgageValue() )// if new owner cannot afford to pay interest
						{
							cout << "Cannot afford to keep mortgage." << endl;
							bankrupt(player, board, receiveAssetID, "bankReason", numPlayers);	//call bankrupt function for new owner
						}
						else																//if player can afford interest
						{
							cout << "Mortgage kept." << endl;
							int interest = board[i].getUnMortgageValue() - board[i].getMortgageValue(); //calculates interest
							player[receiveAssetID].setBalance(player[receiveAssetID].getBalance() - interest);	//deducts interest from new owner wallet
						}
					}
				}
			}
		}
		else if(reason == "bankReason")														//if player bankrupt because of bank
		{
			cout << "Properties owned will be auctioned." << endl;
			system("pause");
			for(int i =0 ; i<40 ; i++)														//loop for all properties
			{
				if(board[i].getOwner() == playerID)											//if players owns property
				{
					board[i].setOwner(-1);													//resets owner
					board[i].setHouses(0);													//resets houses
					board[i].setColourRentFlag(false);										//sets colour group owned
					board[i].setMortgageFlag(false);										//resets mortgage flag
					board[i].setSaleStatus(false);											//resets sale status
					auction(player, board, numPlayers, i);									//calls auction function for property
				}
			}
		}
	}
}

void inJail(Player player[], Board board[], int playerID, int roundNum, int numPlayers)		//function for player options while in jail
{
	string jailSelection;
	int i = playerID;
	
	int firstRoll = rollDie();																//rolls dice for player and displays as ASCII
	system("pause");
	int secondRoll = rollDie();
	int diceTotal = firstRoll + secondRoll;
	diceASCII(firstRoll, secondRoll);															
	
	if (firstRoll == secondRoll)															//if doubles rolled
	{
		cout << "You have rolled doubles and are out of jail." << endl;
		player[i].setJailTrack(-1);															//resets sentinel for jail tracking
		movePlayer(player, board, i, diceTotal, roundNum, numPlayers);						//moves player with total from dice rolled
	}
	if(player[i].getJailTrack() != -1)														//if player still in jail
	{
		cout << "Would you like to pay $50 to get out of jail? (Y/N)" << endl;				//option to pay $50 for bail
		cin >> jailSelection;																//reads in player decision
		while(jailSelection != "Y" && jailSelection != "y" && jailSelection != "N" && jailSelection !="n")	//checks if input was yes or no
		{
			cout << "Invalid selection. Please re-enter selection." << endl;	
			cin >> jailSelection;															//reads in new selection
		}
		if(jailSelection == "Y" || jailSelection == "y")									//if player says yes
		{
			if(player[i].getBalance() < 50)													//checks if player can afford bail
			{
				cout << "You cannot afford to pay bail." << endl;
			}
			else
			{
				player[i].setBalance(player[i].getBalance() - 50);							//deducts bail cost from player wallet
				cout << "You have paid $50 for bail." << endl; 
				player[i].setJailTrack(-1);													//resets jail track to sentinel
				movePlayer(player, board, i, diceTotal, roundNum, numPlayers);				//move player out of jail
			}
		}
	}
	if(player[i].getJailTrack() != -1)														//if player still in jail
	{
		if(player[i].getJailCards() > 0)													//checks if player has jail cards
		{
			cout << "Would you like to use your 'Get Out of Jail' card? (Y/N)" << endl;
			cout << "Cards Available: " << player[i].getJailCards() << endl;
			cin >> jailSelection;
			while(jailSelection != "Y" && jailSelection != "y" && jailSelection != "N" && jailSelection !="n")//while input is not yes or no
			{
				cout << "Invalid selection. Please re-enter selection." << endl;
				cin >> jailSelection;														//reads in new selection
			}		
			if(jailSelection == "Y" || jailSelection == "y")								//if player decision is yes
			{	
				cout << "You have used a 'Get Out of Jail' card" << endl;
				player[i].setJailCards(player[i].getJailCards() -1);						//deducts jail cards owned by player by one
				player[i].setJailTrack(-1);													//resets jail track for player
				movePlayer(player, board, i, diceTotal, roundNum, numPlayers);				//move player
				if(player[i].getChanceJailCard() == true)									//check where jail card came from
				{
					player[i].setChanceJailCard(false);										//returns card back to pile
				}
				else
				{
					player[i].setCommunityJailCard(false);									//returns card back to pile
				}
			}
		}
	}
	if(player[i].getJailTrack() != -1 && player[i].getJailTrack() == roundNum + 3)			//if player has been in jail for three straight rounds
	{
		cout << "You have been in jail for three consecutive rounds. You have to pay $50." << endl;
		while(player[i].getBalance() < 50 && player[i].getBankruptFlag() == false)			//while player cannot afford bail
		{
			cout << "You cannot afford bail." << endl;
			bankrupt(player, board, i, "bankReason", numPlayers);							//calls bankrupt function
		}

		if(player[i].getBankruptFlag() == false)											//if player is not bankrupt
		{
			player[i].setBalance(player[i].getBalance() - 50);								//deduct bail from wallet
			player[i].setJailTrack(-1);														//resets jail track
			movePlayer(player, board, i, diceTotal, roundNum, numPlayers);					//moves player
		}
	}
}

void winner()																				//ASCII for winner of game
{	
    cout << "--------------------------------------------------------------------------------" << endl;
	cout << "..............##.....##.###.##....##.##....##.########.########..##............." << endl;
	cout << "..............##.....##..#..###...##.###...##.##.......##.....##.##............." << endl;
	cout << "..............##.###.##..#..##.##.##.##.##.##.######...#######...##............." << endl;
	cout << "..............####.####..#..##..####.##..####.##.......##....#...##............." << endl;
	cout << "..............###...###..#..##...###.##...###.##.......##.....#................." << endl;
	cout << "..............##.....##.###.##....##.##....##.########.##......#.##............." << endl;
	cout << "--------------------------------------------------------------------------------" << endl; 
}
