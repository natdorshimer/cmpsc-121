#include <iostream>
using namespace std;

//Homework #6: Hearts
//Written by: Natalie Dorshimer
//CMPSC 121 Section 004

//Function descriptions are below main function
//They are listed by class
//Non-class functions are below all the class functions

//Note:
//No extra credit is completed for this program


//Rule related constants
const int playerSize = 5; //0 is an empty slot
const int handSize = 13;
const int deckSize = 52;
const int user = 1;
const int gameOverScore = 100; //the score that ends the game

//Card related constants
const int CLUBS = 1;
const int DIAMONDS = 2;
const int SPADES = 3;
const int HEARTS = 4;
const int JACK = 11;
const int QUEEN = 12;
const int KING = 13;
const int ACE = 14;

//Constant related to deck shuffling
const int randomizer = 1000;  //The higher the number, the more the deck is shuffled

//Classes: 
class card
{
	public:
	int number;
	int suit;

	//sets card.number and card.suit = 0
	void initialize();

	//Displays the cards number in its name
	void displayNumber();

	//Displays the suits name
	void displaySuit();

	//"The (Number) of (Suit)
	void displayCard() {
		cout << "The "; displayNumber(); cout << " of "; displaySuit();
	}

	//Checks to see if both number and suit are == 0
	//Returns true if they are
	bool isZero();


};

class player
{
	public:
	int playerNumber;
	int totalScore;
	int turnScore;
	bool trickStatus; //True if they are leading the trick. False otherwise

	//An array of cards to represent the hand
	card hands[handSize];   

	//Displays the player's hand
	void displayHand();

	//Checks to see if the player has that suit
	bool hasSuit(int suit);

};

class deck
{
	public:
		card cards[deckSize];

		//Shuffles the deck
		void shuffle();
	
		//Initializes the game deck to a standard deck of 52 cards
		void initialize(void);
		
		//initializes, shuffles, and deals the deck to players
		void dealDeck(player players[]);
	
};	



//Non-Class Functions

//Checks if the player has the two of clubs (for bonus)
bool hasTwoClubs(player players);

//returns true if the player has a suit that isn't hearts
//This is because they can't lead with a heart until it's been played
bool hasNotHearts(player player)
{
	if((player.hasSuit(CLUBS) == true || player.hasSuit(SPADES) || player.hasSuit(DIAMONDS) == true))
		return true;
	else
		return false;
}

//Modifies turnScore for a single placement of cards on a table
void getLoser(card table[], player players[]);

//Modifies players.totalScore by adding the players.turnScore whenever all cards are used up
void getScore(player players[]);

//Plays a card for a single turn of hearts
//Players place a card to the table according to the rules. 
void playCard(card table[], player players[], int playerNumber, bool heartStatus);

//Function that uses playCard for 13 rounds. 
//The function ends when all cards are gone, which is always 13 iterations
void takeTurn(player players[], card table[], bool &heartStatus);




//This handles and uses the functions described to simulate the game of hearts
//Calls: takeTurn, deck::dealDeck
//       Those functions call all the other functions in this program though
int main()
{ 
	//main function variables
	//There aren't that many. Functions do the heavy lifting
	deck gameDeck;
	player gamePlayers[playerSize];
	card table[playerSize];
	char answer = 'y';

	
	//Initializing the player arrays
	//Didn't bother making a function for this since it's only used once
	for(int i = 1; i < playerSize; i++)
	{
		gamePlayers[i].turnScore = 0;
		gamePlayers[i].totalScore = 0;
		gamePlayers[i].trickStatus = false;

		for(int j = 0; j < handSize; j++)
			gamePlayers[i].hands[j].initialize();
	}

	

	do //This is the loop for the entire program. Program ends when the player opts out
	{
		//Is the game still going variable
		bool gameStatus = true;
		int roundNumber = 1;


		do  //This is the loop for a single game. Ends when the game is over
		{
			//deals a deck to players
			gameDeck.dealDeck(gamePlayers);

			bool heartStatus;
			
			//Does a turn of the game
			//13 individual turns (1 for each card in the hand)
			cout << "***Round " << roundNumber << "***" << endl;
			takeTurn(gamePlayers,table,heartStatus);
			roundNumber++;

			//If any of of the players have a score of over 100, the game is over
			for(int i = 1; i < playerSize; i++)
				if(gamePlayers[i].totalScore > gameOverScore)
					gameStatus = false;

		} while(gameStatus);


		//Whoever has the smallest amount of points is the winner
		int winner = 1;
		for(int i = 2; i < playerSize; i++)
			if(gamePlayers[i].totalScore < gamePlayers[winner].totalScore)
				winner = i;


		//To make you feel special when you win
		cout << "The winner of this game is "; 
		if(winner == user) cout << "you!" << endl;
		if(winner != user) cout << "Player " << winner << "!" << endl;


		cout << "Play again (y/n)? ";
		cin >> answer;
		cout << endl << endl;

	} while(answer == 'y');

	return 0; 
}


//playCard and takeTurn are the drivers of this game

//Plays a card for a single turn of hearts
//Players place a card to the table according to the rules. 
//Parameters: card table[]: card array of size 5
//            players[] player array of size 5
//            playerNumber: the player that is placing the card in the table
//            heartStatus: the variable that determines if the person can lead with a heart
//                         not modified in this function, so not passed as reference
void playCard(card table[], player players[], int playerNumber, bool heartStatus)
{
	int cardNumber;
	int playerLead;

	for(int i = 1; i < playerSize; i++)
		if(hasTwoClubs(players[i]) == true)
			players[i].trickStatus = true;

	for(int i = 1; i < playerSize; i++)
		if(players[i].trickStatus == true)
			playerLead = i;
	

	//this function takes all four different combinations of player status and lead status (user? lead?)

	//User Cases:

	//The case if the player is the user and they aren't the lead
	if(playerNumber == user && playerNumber != playerLead)
	{
		do
		{
			cout << "What card would you like to play?  ";
				cin >> cardNumber; cout << endl;

			if(cardNumber < 0 || cardNumber > 12 || players[playerNumber].hands[cardNumber].isZero() == true)
				cout << "Please play a card that you have." << endl;
			else if((table[playerLead].suit != players[playerNumber].hands[cardNumber].suit) && (players[playerNumber].hasSuit(table[playerLead].suit) == true))
			{
				cout << "Please play a card of the leader's suit. Lead Suit: "; table[playerLead].displaySuit(); 
				cout << endl;
			}

		} while( ((table[playerLead].suit != players[playerNumber].hands[cardNumber].suit) && (players[playerNumber].hasSuit(table[playerLead].suit) == true)) || (cardNumber < 0 || cardNumber > 12 || players[playerNumber].hands[cardNumber].isZero() == true));
		//While the player has the suit of the lead but did not play a suit of the lead or the player did not place a card that he had.

		table[playerNumber] = players[playerNumber].hands[cardNumber];
		players[playerNumber].hands[cardNumber].initialize();

		cout << "You play the "; table[playerNumber].displayCard(); 
		cout << endl;
	}

	//The case if the player is the user and the lead
	else if(playerNumber == user && playerLead == playerNumber)
	{
		do
		{
			if(hasTwoClubs(players[playerNumber]) == true)
			{
				for(int i = 0; i < handSize; i++)
					if(players[playerNumber].hands[i].suit == CLUBS && players[playerNumber].hands[i].number == 2)
						cardNumber = i;
					
			}

			else 
			{
				cout << "Choose a card to lead with.";
				cin >> cardNumber;

				if( (heartStatus == false && players[playerNumber].hands[cardNumber].suit == HEARTS) && (hasNotHearts(players[playerNumber]) == true))
					cout << "You cannot lead with a hearts until one has been played. " << endl;
				if(cardNumber < 0 || cardNumber > 12 || players[playerNumber].hands[cardNumber].isZero() == true)
					cout << "Please choose an actual card. " << endl;
			}


		} while((cardNumber < 0 || cardNumber > 12 || players[playerNumber].hands[cardNumber].isZero() == true) || ( (heartStatus == false && players[playerNumber].hands[cardNumber].suit == HEARTS) && (hasNotHearts(players[playerNumber]) == true) ) );
			//checks for invalid hearts and makes sure it's a valid card


		table[playerNumber] = players[playerNumber].hands[cardNumber];
		players[playerNumber].hands[cardNumber].initialize();
		cout << "You lead with the "; table[playerNumber].displayCard(); cout << endl;
	}


	//Cases that are not the player:

	//The player is not the user and the player is the lead
	else if(playerNumber != user && playerLead == playerNumber)
	{
		if(hasTwoClubs(players[playerNumber]) == true)
			{
				for(int i = 0; i < handSize; i++)
					if(players[playerNumber].hands[i].suit == CLUBS && players[playerNumber].hands[i].number == 2)
					{
						cout << "Player " << playerNumber << " leads with the two of clubs." << endl;
						table[playerNumber] = players[playerNumber].hands[i];
						players[playerNumber].hands[i].initialize();
					}
			}


		else
		{
			do
			{
				cardNumber = rand()%13;
			} while ( (heartStatus == false && players[playerNumber].hands[cardNumber].suit == HEARTS) && (hasNotHearts(players[playerNumber]) == true) || players[playerNumber].hands[cardNumber].isZero() == true );
			//checks for invalid hearts and makes sure it's a valid card
		

		table[playerNumber] = players[playerNumber].hands[cardNumber];
		players[playerNumber].hands[cardNumber].initialize();

		cout << "Player " << playerNumber << " leads with the "; table[playerNumber].displayCard(); cout << endl;

		}
	} 


	//The player is not the user and the player is not the lead
	else if(playerNumber != user && playerNumber != playerLead)
	{
		do
		{
			cardNumber = rand()%13;
		}while(((table[playerLead].suit != players[playerNumber].hands[cardNumber].suit) && (players[playerNumber].hasSuit(table[playerLead].suit) == true)) || players[playerNumber].hands[cardNumber].isZero() == true);

		table[playerNumber] = players[playerNumber].hands[cardNumber];
		players[playerNumber].hands[cardNumber].initialize();

		cout << "Player " << playerNumber << " plays the "; table[playerNumber].displayCard(); cout << endl;
	}


}

//Takes one whole turn of a game. 
//Pre-Condition: player[] is an array of players who all have hands filled with hearts
//               table[] is an array of size playerSize 
//Post-Condition: players[].hands[] are all empty (players[].hands[i].isZero() == true) 
//Parameters: players[]: an array of players of size 5
//            table[] array of cards of size 5
//            bool heartStatus: determines if a player can lead with a heart
void takeTurn(player players[], card table[], bool &heartStatus)
{
	//heartStatus is always false at the beginning of a turn
	heartStatus = false;

	for(int turnCount = 1; turnCount <= 13; turnCount++)
	{
		cout << "*Turn: " << turnCount << "*" << endl;
		cout << "Scores: " << endl;

		//Display the scores at the beginning of each turn.
		for(int i = 1; i < playerSize; i++)
		{
			cout << "Player " << i << " total score: " << players[i].totalScore << ".   Turn Score: " << players[i].turnScore;
			cout << endl;
		} cout << endl;

		players[user].displayHand();
		
		int playerLead;


		for(int i = 1; i < playerSize; i++)
		{
			if(hasTwoClubs(players[i]) == true && turnCount == 1) {
				players[i].trickStatus = true;
				playerLead = i; }
			else if(players[i].trickStatus == true && turnCount != 1)
				playerLead = i;
		}

		//Does the playerLead first
		playCard(table,players,playerLead,heartStatus);
		for(int i = 1; i < playerSize; i++)
			if(i != playerLead)
				playCard(table,players,i,heartStatus);
			
		//This code runs to check if a hearts was played
		//This is for the extra credit
		for(int i = 1; i < playerSize; i++)
			if(table[i].suit == HEARTS)
				heartStatus = true;
		
		//This allocates the score for each player and clears the table
		//Switches the trickStatus to true for the person leading the trick
		getLoser(table,players);
		cout << endl;
		cout << "***" << endl << endl;

	}

	getScore(players);
	for(int i = 1; i < playerSize; i++)
		players[i].trickStatus = false;
	
}


//*****Card Functions:

//Sets a card number and suit to zero
void card::initialize()
{
	number = 0;
	suit = 0;
}

//Displays the number of the card in name
void card::displayNumber()
{
	switch(number)
	{
		case ACE: cout << "Ace"; break;
		case 2: cout << "Two"; break;
		case 3: cout << "Three"; break;
		case 4: cout << "Four"; break;
		case 5: cout << "Five"; break;
		case 6: cout << "Six"; break;
		case 7: cout << "Seven"; break;
		case 8: cout << "Eight"; break;
		case 9: cout << "Nine"; break;
		case 10: cout << "Ten"; break;
		case JACK: cout << "Jack"; break;
		case QUEEN: cout << "Queen"; break;
		case KING: cout << "King"; break;
	}

}

//Displays the suit of the card in name
//Note: Isn't called anywhere in the main function, but falled in other functions
void card::displaySuit()
{
	switch(suit)
	{
		case CLUBS: cout << "Clubs"; break;
		case DIAMONDS: cout << "Diamonds"; break;
		case SPADES: cout << "Spades"; break;
		case HEARTS: cout << "Hearts"; break;
	}

}

//Returns true if the card's number and suit are zero, false if it isn't
bool card::isZero()
{
	if(number == 0)
		return true;
	else if(suit == 0)
		return true;
	else
		return false;

}



//*****Player functions:

//This function displays the hand of the player
//The number outputed corresponds to the placement of the card in the hand
//The user must input these numbers to select a card
//Note: removed if statement for if the computers used it
//calls: card::displayNumber(), card::displaySuit() 
void player::displayHand()
{
	//This function is only used by the user, so there is no need to account for other players
	cout << "Your hand:  " << endl;


	cout << "Clubs:   ";
	for( int i = 0; i < handSize; i++)
	{	

		if(hands[i].number != 0 && hands[i].suit == CLUBS) {
			cout << i << "--"; hands[i].displayNumber(); cout << "     "; 
		} 

	} cout << endl;

			
	cout << "Diamonds:   ";
	for( int i = 0; i < handSize; i++)
	{

		if(hands[i].number != 0 && hands[i].suit == DIAMONDS) {
			cout << i << "--"; hands[i].displayNumber(); cout << "     "; 
		}

	} cout << endl;


	cout << "Spades:   ";
	for( int i = 0; i < handSize; i++)
	{

		if(hands[i].number != 0 && hands[i].suit == SPADES) {
			cout << i << "--"; hands[i].displayNumber(); cout << "     "; 
		}

	} cout << endl;


	cout << "HEARTS:   "; 
	for( int i = 0; i < handSize; i++)
	{

		if(hands[i].number != 0 && hands[i].suit == HEARTS)  {
			cout << i << "--"; hands[i].displayNumber(); cout << "     "; 
		}

	} cout << endl << endl;

}

//Checks to see if the player has that suit in their hand
//Returns true if they do, false if they don't
bool player::hasSuit(int suit)
{
	bool validity = false;
	for(int i = 0; i < handSize; i++)
	{
		if(hands[i].suit == suit)
			validity = true;

	}

	return validity;

}






//*****Deck Functions

//Creates a deck of 52 cards with 4 suits of each number
//Post-Condition: deck.cards[] has all the cards of an actual deck
void deck::initialize(void)
{
	for(int i = 0; i < deckSize; i++)
		cards[i].initialize();

	//Continues until deckPlacement reaches deckSize
	//The loop starts at cards[0] = 2 of clubs and continues to the last ACE
	int deckPlacement = 0;
	for(int i = 0; deckPlacement < deckSize; i++)
	{
		for(int j = 1; j <= 4; j++)
		{
			cards[deckPlacement].number = (i+2);
			cards[deckPlacement].suit = j;
			deckPlacement++;
		}
	}
}

//Makes two random integers that correspond to a card in the deck
//These two placements are then swaped
//This is done randomizer times. The higher the number, the more random it is
void deck::shuffle()
{
	for(int i = 0; i < randomizer; i++)
	{
		int rand1 = rand()%deckSize;
		int rand2 = rand()%deckSize;
		swap(cards[rand1],cards[rand2]);
	}
}

//Deals the deck to 4 players:
//Pre-Condition: players[] is an array of size 5
//Post-Condition: players[1] through 4 have players[].hands[] filled with 13 cards copied from the deck
//calls: deck::initialize, deck::shuffle
//parameters:        player players[]: object of class players that has size 5.
void deck::dealDeck(player players[])
{
	//Initializes and shuffles the deck
	initialize();
	shuffle();

	int deckPlacement = 0;
	for(int i = 1; i < playerSize; i++)
	{
		for(int j = 0; j < 13; j++)
		{
			//Sets a card in the hand == to a card in the deck
			players[i].hands[j].number = cards[deckPlacement].number;
			players[i].hands[j].suit = cards[deckPlacement].suit;

			//And sets the card in that deck to zero
			cards[deckPlacement].number = 0;
			cards[deckPlacement].suit = 0;

			deckPlacement++;
	
		}
	}
}





//*****Non-Class specific functions

//Checks to see if the player has a two of clubs
//Returns true if it does
//False if it doesn't
//Parameters: player players: a single player (not array) in the game
bool hasTwoClubs(player players)
{
	bool twoOfClubs = false;
	for(int i = 0; i < handSize; i++)
		if(players.hands[i].number == 2 && players.hands[i].suit == CLUBS)
			twoOfClubs = true;

	return twoOfClubs;
}


//Gets the loser based off the cards in play and gives them the correct turnScore
//Pre-Condition: table[] is an array where the entry is the card inputted by that player
//               table[1] is the card input by player 1+
//Post-Condition: player[].turnScore is changed if the player takes the trick
//                player[].trickStatus is changed to true if that player takes the trick
//Parameters: card table[]: array of cards. table[1] refers to the card input by player 1.
//            player players[]: array of players.
void getLoser(card table[], player players[])
{
	int leader;
	for(int i = 1; i < playerSize; i++)
		if(players[i].trickStatus == true)
			leader = i;

	int currentLoser = leader;
	for(int i = 1; i < playerSize; i++)
	{
		if(table[currentLoser].suit == table[i].suit)
		{
			if( (table[currentLoser].number < table[i].number))
				currentLoser = i;
		}
		//This just initializes the trickStatus so they are all false
		players[i].trickStatus = false;
	}

	

	int scoreTotal = 0;
	for(int i = 1; i < playerSize; i++)
	{
		if(table[i].suit == HEARTS)
			scoreTotal++;
		else if(table[i].suit == SPADES && table[i].number == QUEEN)
			scoreTotal = scoreTotal + 13;
	}

	cout << "Player " << currentLoser << " takes the trick. They gained " << scoreTotal << " points." << endl;

	players[currentLoser].turnScore += scoreTotal;
	players[currentLoser].trickStatus = true;

}


//Gets the score for a whole turn. if player[playerNumber].turnScore == 26, shoot the moon is checked
//Pre-Condition: player[] is an array of players. players[1] corresponds to player1, etc
//Post-Condition: player[].totalScore is changed appropriately and player[].turnScore is reduced to zero
//Parameters:   player players[]: a variable of the player class that where the entries correspond to playerNumber
//                                players[0] is empty
void getScore(player players[])
{
	bool shootForTheMoon = false;
	for(int i = 1; i < playerSize; i++)
		if(players[i].turnScore == 26)
		{
			cout << "Player " << i << "shot for the moon! Everyone but Player " << i << "gains 26 points.";
			shootForTheMoon = true;
			cout << endl;
		}
	if(shootForTheMoon == false)
	{
		for(int i = 1; i < playerSize; i++)
		{
			players[i].totalScore = players[i].totalScore + players[i].turnScore;
			players[i].turnScore = 0;
		}
	}

	else if(shootForTheMoon == true)
	{
		for(int i = 1; i < playerSize; i++)
		{
			//This adds 26 to the score if they aren't the one who shot for the moon
			if(players[i].turnScore == 0)
				players[i].totalScore += 26;
			players[i].turnScore = 0;
		}

	}

}

