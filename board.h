#include <iostream>
#include <string>
using namespace std;

class Board
{
	public:																				//public functions of board pieces - use to change or view private variables
		Board();
		void setSaleStatus(bool propertySaleStatus);
		bool getSaleStatus();
		void setHouses(int propertyHouses);
		int getHouses();
		void setName(string propertyName);
		string getName();
		void setColour(string propertyColour);
		string getColour();
		void setBuyPrice(int propertyPrice);
		int getBuyPrice();
		void setRent(int propertyRent);
		int getRent();
		void setRentHouse1(int propertyRentHouse1);
		int getRentHouse1();
		void setRentHouse2(int propertyRentHouse2);
		int getRentHouse2();
		void setRentHouse3(int propertyRentHouse3);
		int getRentHouse3();
		void setRentHouse4(int propertyRentHouse4);
		int getRentHouse4();
		void setRentHotel(int propertyRentHotel);
		int getRentHotel();
		void setOwner(int propertyOwnerID);
		int getOwner();
		void setMortgageFlag(bool propertyMortgageFlag);
		bool getMortgageFlag();
		void setMortgageValue(int propertyMortgageValue);
		int getMortgageValue();
		void setUnMortgageValue(int propertyUnMortgageValue);
		int getUnMortgageValue();
		void setHouseCost(int propertyHouseCost);
		int getHouseCost();		
		void setColourRentFlag(bool propertyColourRentFlag);
		bool getColourRentFlag();
		
	private:																			//attributes of board instances (MUST use board functions to view or change values)
		bool saleStatus;
		int houses;																		//5 houses means hotel
		string name;
		string colour;
		int buyPrice;
		int rent;
		int rentHouse1;
		int rentHouse2;
		int rentHouse3;
		int rentHouse4;	
		int rentHotel;
		int owner;
		bool mortgageFlag;
		int mortgageValue;
		int unMortgageValue;
		int houseCost;		
		bool colourRentFlag;		
		
};
