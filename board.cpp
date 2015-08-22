#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "board.h"
using namespace std;

//functions for board
Board::Board()
{
	saleStatus = false;
	houses = 0;
	owner = -1;
	colourRentFlag = false;
	mortgageFlag = false;
}

void Board::setSaleStatus(bool propertySaleStatus)
{
	saleStatus = propertySaleStatus;
}
bool Board::getSaleStatus()
{
	return saleStatus;	
}

void Board::setHouses(int propertyHouses)
{
	houses = propertyHouses;
}
int Board::getHouses()
{
	return houses;	
}

void Board::setName(string propertyName)
{
	name = propertyName;
}
string Board::getName()
{
	return name;
}

void Board::setColour(string propertyColour)
{
	colour = propertyColour;
}
string Board::getColour()
{
	return colour;
}

void Board::setBuyPrice(int propertyPrice)
{
	buyPrice = propertyPrice;
}
int Board::getBuyPrice()
{
	return buyPrice;
}

void Board::setRent(int propertyRent)
{
	rent = propertyRent;
}
int Board::getRent()
{
	return rent;
}

void Board::setRentHouse1(int propertyRentHouse1)
{
	rentHouse1 = propertyRentHouse1;
}
int Board::getRentHouse1()
{
	return rentHouse1;
}

void Board::setRentHouse2(int propertyRentHouse2)
{
	rentHouse2 = propertyRentHouse2;
}
int Board::getRentHouse2()
{
	return rentHouse2;
}

void Board::setRentHouse3(int propertyRentHouse3)
{
	rentHouse3 = propertyRentHouse3;
}
int Board::getRentHouse3()
{
	return rentHouse3;
}

void Board::setRentHouse4(int propertyRentHouse4)
{
	rentHouse4 = propertyRentHouse4;
}
int Board::getRentHouse4()
{
	return rentHouse4;
}

void Board::setRentHotel(int propertyRentHotel)
{
	rentHotel = propertyRentHotel;
}
int Board::getRentHotel()
{
	return rentHotel;
}

void Board::setOwner(int propertyOwner)
{
	owner = propertyOwner;
}
int Board::getOwner()
{
	return owner;
}

void Board::setMortgageFlag(bool propertyMortgageFlag)
{
	mortgageFlag = propertyMortgageFlag;
}
bool Board::getMortgageFlag()
{
	return mortgageFlag;
}

void Board::setMortgageValue(int propertyMortgageValue)
{
	mortgageValue = propertyMortgageValue;
}
int Board::getMortgageValue()
{
	return mortgageValue;
}

void Board::setUnMortgageValue(int propertyUnMortgageValue)
{
	unMortgageValue = propertyUnMortgageValue;
}
int Board::getUnMortgageValue()
{
	return unMortgageValue;
}

void Board::setHouseCost(int propertyHouseCost)
{
	houseCost = propertyHouseCost;
}
int Board::getHouseCost()
{
	return houseCost;
}

void Board::setColourRentFlag(bool propertyColourRentFlag)
{
	colourRentFlag = propertyColourRentFlag;
}
bool Board::getColourRentFlag()
{
	return colourRentFlag;
}
