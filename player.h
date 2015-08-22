#include <iostream>
#include <string>
using namespace std;

class Player
{
	public:																				//public functions of Player - use to change or view private variables
		Player();																		//constructor for player attributes
		void setBalance(int playerBalance);												//set balance for player
		int getBalance();																//access balance for player
		void setName(string playerName);												//set name of player
		string getName();																//access name of player
		void setPosition (int playerPosition);											//set position of player
		int getPosition();																//access player's position
		void setJailCards(int playerJailCards);											//set number of jail cards for player
		int getJailCards();																//access number of jail cards for player
		void setDoublesRolled(int turnDoublesRolled);									//sets number of doubles rolled for player
		int getDoublesRolled();															//access doubles rolled
		void setAuctionFlag(bool playerAuctionFlag);
		bool getAuctionFlag();
		void setBankruptFlag(bool playerBankruptFlag);
		bool getBankruptFlag();
		void setJailTrack(int playerJailTrack);
		int getJailTrack();
		void setStationsOwned(int playerStationsOwned);
		int getStationsOwned();
		void setUtilitiesOwned(int playerUtilitiesOwned);
		int getUtilitiesOwned();
		void setPropertyWorth(int playerPropertyWorth);
		int getPropertyWorth();
		void setChanceJailCard(bool playerChanceJailCard);
		bool getChanceJailCard();
		void setCommunityJailCard(bool playerCommunityJailCard);
		bool getCommunityJailCard();
		void setCancelRent(bool playerCancelRent);
		bool getCancelRent();
		void setCancelBuy(bool playerCancelBuy);
		bool getCancelBuy();

		
	private:																			//attributes of player instances (MUST use player functions to view or change values)
		string name;
		int balance;
		int position;
		int turn;
		int jailCards;
		int doublesRolled;
		bool auctionFlag;
		bool bankruptFlag;
		int jailTrack;
		int propertyWorth;
		int stationsOwned;
		int utilitiesOwned;
		bool chanceJailCard;
		bool communityJailCard;
		bool cancelRent;
		bool cancelBuy;
		
};
