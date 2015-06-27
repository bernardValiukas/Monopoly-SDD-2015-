#include <iostream>
#include <string>
using namespace std;

class Player
{
	public:																				//public functions of Player - use to change or view private variables
		Player();																		//constructor for player attributes
		int getBalance();																//access balance for player
		void setName(string playerName);												//set name of player
		string getName();																//access name of player
		void setPosition (int playerPosition);											//set position of player
		int getPosition();																//access player's position
		void setJailCards(int playerJailCards);											//set number of jail cards for player
		int getJailCards;																//access number of jail cards for player
		void setDoublesRolled(int turnDoublesRolled);									//sets number of doubles rolled for player
		int getDoublesRolled();															//access doubles rolled
		
	private:																			//attributes of player instances (MUST use player functions to view or change values)
		string name;
		int balance;
		int position;
		int turn;
		int jailCards;
		int doublesRolled;
};
