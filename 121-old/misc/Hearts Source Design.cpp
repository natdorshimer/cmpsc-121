#include <iostream>
using namespace std;

const int playerSize = 5; //0 is an empty slot

struct card
{
	int number;
	int suit;
};

class player
{
	private:
		int playerNumber;
	public:
		int totalScore;
		int turnScore;
		bool trickStatus; //True if they are leading the trick. False otherwise

		card hands[14];   //Occurrence array. hands[0] holds no information

		//Puts card in table[]. Entry corresponds to player number
		//i.e table[1] corresponds to the card put onto the table by player 1 (you)
		//Pre-Condition: table[] has at least a size of 5
		//Parameters: card table[]
		void placeCard(card table[]);  
};

//Gets the loser based off the cards in play and gives them the correct turnScore
//Pre-Condition: table[] is an array where the entry is the card inputted by that player
//               table[1] is the card input by player 1+
//Post-Condition: player[].turnScore is changed if the player takes the trick
//                player[].trickStatus is changed to true if that player takes the trick
//Parameters: card table[]: array of cards. table[1] refers to the card input by player 1.
void getLoser(card table[]);

//Distributes the cards of the deck to the players
//This happens at the beginning of every round
//Paramters: players[]: array of cards
//Note: I may make the deck a class similar to the lecture notes
//This would then have distribute deck call deck.shuffle() 
void distributeDeck(card players[]);

//Gets the score for a whole turn. if player[playerNumber].turnScore == 26, shoot the moon is checked
//Pre-Condition: player[] is an array of players. players[1] corresponds to player1, etc
//Post-Condition: player[].totalScore is changed appropriately and player[].turnScore is reduced to zero
//Parameters:   player players[]: a variable of the player class that where the entries correspond to playerNumber
//                                players[0] is empty
void getScore(player players[]);

//Does a single turn of hearts. The person who takes the trick has points added to their player[player#].turnScore
//Person who leads is determined by player.trickStatus
//Pre-Condition: player[] is an array of size playerSize with an empty player[0]. 
//Post-Condition: The player who takes the trick has a score added to his player.turnScore. table[] is emptied
//Parameters: player[], table[]
void doTurn(player players[], card table[]);

//Allows the player to trade cards according to turn rules
//Done at the start of each round
//Pre-Condition: turn is a number between 1 and 13;
//Post-Condition: Depending on the turn, 3 cards are switched between each player
//Parameters: player player[]
//            int turn: the number of the turn
void tradeCards(player player[], int turn);

//Adds all the players.turnScores and checks if it == 26. Returns true if round is over
//Pre-Condition: player[] is an array of size playerSize with an empty player[0]
//parameters: player players[] 
bool roundOver(player players[]);


//This handles and uses the functions described to simulate the game of hearts
//Calls: placeCard,getLoser,distributeDeck,getScore,doTurn,tradeCards,roundOver
int main()
{ 
	
	
	return 0; }