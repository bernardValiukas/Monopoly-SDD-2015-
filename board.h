#include <iostream>
#include <string>
using namespace std;

class Board
{
	public:																				//public functions of board pieces - use to change or view private variables
		
	private:
		bool saleSatus;																	//attributes of board instances (MUST use board functions to view or change values)
		int buyPrice;
		int playerOwnsNum; 																//do not know how to set out yet
		int boardPosition;
		string name;
		string colour;
		int rent;
		int rentHouse1;
		int rentHouse2;
		int rentHouse3;
		int rentHouse4;
		int rentHotel;
		int mortgageValue;
		int unMortgageValue;
};
