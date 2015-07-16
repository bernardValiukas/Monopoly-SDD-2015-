#include <iostream>
#include <cstdlib>
#include "player.h"
using namespace std;

Player::Player() 																		//creates preset values for player attributes
{
	balance = 1500;
	jailCards = 0;
	position = 0;
	doublesRolled = 0;
}

void Player::setBalance(int playerBalance)
{
	balance = playerBalance;
}
int Player::getBalance() 																//access balance
{
	return balance;
}

void Player::setName(string playerName)													//set name of player
{
	name = playerName;
}

string Player::getName()																//access player's name
{
	return name;
}

void Player::setPosition(int playerPosition)											//sets position of player on board
{
	position = playerPosition;
}

int Player::getPosition()																//access position number of player
{
	return position;
}

void Player::setJailCards (int playerJailCards)											//sets number of jail cards for player
{
	jailCards = playerJailCards;
}

void Player::setDoublesRolled(int turnDoublesRolled)									//sets number of doubles rolled //to do: reset for end of each turn
{
	doublesRolled = turnDoublesRolled;
}

int Player::getDoublesRolled()															//access number of doubles rolled for a player
{
	return doublesRolled;
}










