#include <iostream>
using namespace std;

//Written by: Natalie Dorshimer
//On the Date: April 10th, 2014
//CMPSC 121
//Homework #5: Old Maid


//***About the 2-Dimensional Hand Arrays***
//hands[][deckSize] is an occurrence array where each row is a player's hand
//Each entry in the row corresponds to the number of that card
//hands[5][ACE] is the number of ace cards the player 5 has
//hands[0][] is an empty row that will never be used to lower errors in the program
//hands[player][0] corresponds to a players status in the game.
//					if hands[player][0] == 1, that player is in the game 
//                  if hands[player][0] == 0, they are not in the game

//About the rotation of taking cards:
//I start with player1 (you) taking a card from player2
//The last player takes from you, and the next turn begins


//All occurence arrays will obey the entries listed below
//Global Constants
const int deckSize = 14;			//The number of cards 
const int SIZE = 7;					//Max number of players according to the array. 0th isn't counted. I made this program with 8 being max, but it looks like 6 was the max
const int maxSize = SIZE - 1;       //Arbitrary values determined by my grading overlords
const int minSize = 2;
const int ACE = 1, QUEEN = 12, KING = 13;
const int user = 1;
//player2 = 2, etc


//An array with card names to easily display them based off of a card number
const char cardsArray[14][5] = {
	{0,0,0,0,0} ,
	{'A','C','E',0,0} ,
	{'T','W','O',0,0} ,
	{'T','H','R','E','E'} ,
	{'F','O','U','R',0} ,
	{'F','I','V','E',0} ,
	{'S','I','X',0,0} ,
	{'S','E','V','E','N'} ,
	{'E','I','G','H','T'} ,
	{'N','I','N','E',0} ,
	{'T','E','N',0,0} ,
	{'J','A','C','K',0} , 
	{'Q','U','E','E','N'} ,
	{'K','I','N','G',0}
};


//Functions used in the program
//For detailed descriptions, hover over the name or scroll down below the main function

int randDraw( int amount );
int getSize( int player, const int hands[][deckSize] );

void getMatch( int hands[][deckSize] );
void displayCard( int card );

bool cardTest( const int placement, const int hands[][deckSize] );

void distributeDeck( const int deck[], int hands[][deckSize], const int playerSize );
void displayHand( int player, const int hands[][deckSize] );
void drawCard( int hands[][deckSize], int firstPlayer, int secondPlayer, int );
void nextPlayer( int hands[][deckSize], int& placement );
void takeTurn( int hands[][deckSize], int& playerIncrement, int card );



int main()
{
	//Declaration of key variables
	char playGame;
	int hands[SIZE][deckSize];
	const int deck[deckSize] = {0,4,4,4,4,4,4,4,4,4,4,4,3,4};
	//1 Queen is removed deck[QUEEN] = 3;
   


	do 
	{
		int playerSize = maxSize;  //# of players determined by user. Initialized to 6, but user changes it
		int turnCount = 1;   //Counts the turn the game is on

		
		do { //This loop forces the user to choose between 2 and 6
			if(playerSize > maxSize || playerSize < minSize)
				cout << "Please choose an appropriate player size." << endl;
			cout << "How many players would you like? (including yourself. Max: "
				 << maxSize << ", Min: " << minSize << ")  ";
				cin >> playerSize;
				cout << endl;
		} while(playerSize > maxSize || playerSize < minSize);


		cout << "The game begins... " << endl << endl;
		//Distributes deck according to playerSize
		distributeDeck(deck,hands,playerSize);
		getMatch(hands);


		while(getSize(user,hands) > 0 && cardTest(user,hands) == true) 
		{
			//The turn always starts with user, but playerIncrement isn't always player 2
			//playerIncrement is the next player in the game after user
			int playerIncrement = user; 
			nextPlayer(hands,playerIncrement);
				

			cout << "You currently have these cards in your hand:  " << endl;
			displayHand(user,hands); cout << endl;



			int card = 1; //Initialized to not set off if statement at beginning
			cout << "You get to draw a card from Player " << playerIncrement << " containing " 
				 << getSize(playerIncrement,hands) << " cards " << endl;

			do {
				if(card < 1 || card > getSize(playerIncrement,hands))
					cout << "Please choose an appropriate card value" << endl;
				cout << "Choose a number from 1 to " << getSize(playerIncrement,hands) << "   ";
					cin >> card;
			} while(card < 1 || card > getSize(playerIncrement,hands));
			cout << endl;



			//This takes the whole turn
			//Lots of information is displayed with this function
			//I also display the turn the game is on
			cout << "Turn " << turnCount << endl;
			takeTurn(hands,playerIncrement,card);
			turnCount++;
			cout << endl;



			
			if(getSize(user,hands) > 0 && cardTest(user,hands) == false)
				cout << "You are the only player remaining. You lose!" << endl;

			else if(getSize(user,hands) == 0 && cardTest(user,hands) == true)
				cout << "You have no cards! A winner!" << endl;

		}


		cout << "Game over!" << endl << "Play another game (y/n)?  "; 
			cin >> playGame;
		cout << endl << endl;

	} while(playGame == 'y');


	return 0;
}

//This function returns a number between 1 and the number inputed
//This will be used to figure out which card to draw from a player
//Simulates the affect of everyone shuffling their hand after drawing a card
//Parameters: int amount
int randDraw(int amount) {
return (rand()%amount + 1);
}


//Returns a value equal to the number of cards in the hand
//Parameters: int hands[][deckSize]: 2 dimensional occurence array of all cards in play
//			  int player: the player you wish to know the hand size of
int getSize(int player,const int hands[][deckSize])
{
	int digits = 0;

	for(int i = ACE; i < deckSize; i++)
		digits = digits + hands[player][i];

	return digits;


}


//Displays the card with value int card corresponding to cardsArray
//Pre-Condition: card is between 0 and 14
//Parameters: int card: the card value of a given card
void displayCard(int card)
{
	for(int i = 0; i < 5 && cardsArray[card][i] != 0; i++)
		cout << cardsArray[card][i];
}



//This function displays the cards in the hand to the user
//Pre-Condition: hand[][deckSize] is an occurence array with each position corresponding to a card value
//Example: If the array in hands[user][] is {0,0,1,1,1,0,0,0,1,0,0,0,1,0} it will display on screen:
//		You currently have these cards in your hand:
//		Three Queen Two Eight Four
//Parameters:	int player:  the player whose hand you want to display
//				const int hands[][deckSize]: the array containing all hands of all players
void displayHand(int player, const int hands[][deckSize])
{
	for(int i = 0; i < deckSize; i++)
		if(hands[player][i] > 0) {
			for(int j = 0; j < 5 && cardsArray[i][j] != 0; j++)
				cout << cardsArray[i][j];
				cout << " ";
		}

}



//This function sorts all of the hands array for pairs and discards them
//At the end, the function also checks for winners
//This is called at the end of drawCard to take out winners from the game
//Pre-Condition: hands is a multidimensional occurrence array following structure listed at top
//Post-Condition: if there are winners, they are removed (hands[player][0] = 0)
//				  if there are pairs or quadruples, they are removed (hands[player][card] = 0)
//Parameters:     hands occurrence array 
//calls: displayCard
void getMatch(int hands[][deckSize])
{
	for(int i = 1; i < SIZE; i++) {
		for(int j = 1; j < deckSize; j++) {

			//If, for some odd string of luck, they have all four cards to start off with
			if(hands[i][j] >= 4) {
				hands[i][j] = 0;
				if(i == 1) {
					cout << "You discarded four "; displayCard(j); cout << "s from your hand. Lucky! " << endl; }
				else {
					cout << "Player " << i << " discarded four "; displayCard(j); cout << "s from their hand. Lucky! " << endl; }
			}

			//If they have 3 cards, this will only take away two
			else if(hands[i][j] >= 2) 
			{
				hands[i][j] = hands[i][j] - 2;
				if(i == 1) {
				 cout << "You discarded matching "; displayCard(j); cout << "s from your hand " << endl; }
				else {
					cout << "Player " << i << " discarded matching "; displayCard(j); cout << "s " << endl; }
			}

		}

		//If they have no cards and if they are still in the game
		if(getSize(i,hands) == 0 && hands[i][0] == 1)
		{
			hands[i][0] = 0; //They are removed from the game now

			//This is to ensure that it does not repeat text if the user wins
			if(i != user)
				cout << "Player " << i << " has won!" << endl;
		}
	}
}


//This function draws a random card from the second player and adds it to the first player's hand
//The function then displays what happened to the user
//The function uses two different methods to calculate random cards
//Which method it uses is dependent on which player is drawing
//Pre-Condition: hand[][deckSize] is an occurrence array where getSize(firstPlayer,hands) and getSize(secondPlayer,hands) are > 0
//Post-Condition: a value is removed from hands[secondPlayer][card] and added to hands[firstPlayer][card]
//Parameters:	int firstPlayer: the player who is taking the card
//				int secondPlayer: the player who is getting their card taken
//				int card: an arbitrary card value
//calls:getMatch, displayCard
void drawCard(int hands[][deckSize], int firstPlayer, int secondPlayer,int card)
{
	
	//I originally attempted to do a varying random function based off of int card
	//The problem with this is that all attempts yielded a heavy bias towards lower numbered cards
	//Note: The bias was too extreme. All methods of randomization with card resulted in too much of a bias between 1-8
	//      Almost no values between 10 and king were obtained. Better to give the illusion of choice with variation
	//      Instructor said this was OK. Randomization with occurrence arrays is difficult
	card = rand()%(KING) + 1;
	while(hands[secondPlayer][card] == 0)
			card = rand()%(13) + 1;		


	
	//Take from the firstPlayer and add to the secondPlayer's hand
	hands[firstPlayer][card]++;
	hands[secondPlayer][card]--;


	//These statements control what is displayed when cards are moved from one hand to another
	//If 2 players takes cards from each other you shouldn't know their values
	if(firstPlayer == user) {
		cout << "You draw a "; displayCard(card); cout << " from Player " << secondPlayer << endl; }
	else if(secondPlayer == user) {
		cout << "Player " << firstPlayer << " takes your "; displayCard(card); cout << endl; }

	else if(firstPlayer != user && secondPlayer != user)
		cout << "Player " << firstPlayer << " takes a card from Player " << secondPlayer << endl;


	//This will check for duplicates and remove them, and determine if a player won
	getMatch(hands);
}





//This function takes cards out of deck[] and randomly 
//The smaller the playerSize, the more cards each player will have
//distributes them to hand according to playersize
//Pre-Condition: deck[] and hand[][deckSize] are occurence arrays and playersSize is <= 8			
//Post-Condition: hands array has all cards from deck. Each player has an equal (plus or minus 1) number of cards
//Calls: randDraw
//Parameters:   const int deck[]: a single dimensional occurrence array of all cards
//				hands[][deckSize]: multidimensional occurrence array holding all cards of every hand
//              const int playerSize: variable that determines the amount of cards to give to each player
void distributeDeck(const int deck[], int hands[][deckSize], const int playerSize)
{
	int deckCopy[deckSize];
	int cards;
	int extraCards;


	//Initializing the deck copy
	for(int i = 0; i < deckSize; i++)
		deckCopy[i] = deck[i];

	//Initializing the hands array
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < deckSize; j++)
			hands[i][j] = 0;


	cards = 51/playerSize;
	extraCards = 51%playerSize;

	for(int i = user; i <= playerSize; i++)
	{
		while(getSize(i,hands) < cards)
		{
			//This loop ensures deckCopy[random] is always > 0
			//KING = 13 is the largest column number in the array
			int random = randDraw(KING);
			while(deckCopy[random] == 0)
				random = randDraw(KING);

			//Takes one out of deckCopy and adds it to hands
			deckCopy[random]--;
			hands[i][random]++;


		}

		//This will get rid of the extra cards
		//The last player is a bit lucky in this sense
		if(extraCards > 0) 
		{
			int randomExtra = randDraw(KING);
				while(deckCopy[randomExtra] == 0)
					randomExtra = randDraw(KING);

			deckCopy[randomExtra]--;
			hands[i][randomExtra]++;
			extraCards--;
		}
	}

	//This makes all players in the game have hands[player][0] = 1
	for(int i = 1; i <= playerSize; i++)
			hands[i][0]++;


}


//Returns TRUE if every player past placement has cards
//This is used to see if there are players remaining beyond placement
//Tests the hands[player][0] column for the players status
//Pre-Condition: hands[][deckSize] is an occurence array with deckSize columns  and placement <= 8
//Parameters:	const int placement: the placement you want to test
//				const int hands[][deckSize]: the hands occurrence array of cards
bool cardTest(const int placement, const int hands[][deckSize])
{
	bool test = false;
	for(int i = (placement+1); i < SIZE && test == false; i++) 
		if(hands[i][0] > 0)
				test = true;

	return test;

}

//This function modifies placement so that it is the next placement of a player that is in the game
//If there are no players ahead of placement, placement == 0
//This relies on the main function to make use of placement == 0
//i.e.: If placement == 0, what placement was previously takes from the user in drawCard
//Pre-Condition: Placement is between 1 and SIZE and cardTest(placement,hands) == true
//Post-Condition: placement is such a value that getSize(placement,hands) > 0 and is greater than its previous value
//Parameters:	const int hands[][deckSize]: the hands array
//				int& placement: reference parameter the function changes according to conditions
//calls: cardTest
void nextPlayer(int hands[][deckSize], int& placement)
{
	if(cardTest(placement,hands) == true)
	{
		int count = 0;
		for(int i = placement + 1; i < SIZE && count == 0; i++) {
			if(hands[i][0] > 0) {
				placement = i;
				count++; }
		}
	}

	else if(cardTest(placement,hands) == false)
		placement = 0;
	
}



//takeTurn takes a single turn of the game, a rotation of players taking cards from each other
//It uses drawCard and nextPlayer to process the game for both user and AI
//Parameters: hands: multidimensional hand array
//			  playerIncrement: an increment variable used to rotate between AI
//			  card:  the card the user inputs to select from the AI
//calls: drawCard,nextPlayer,getSize
void takeTurn(int hands[][deckSize],int& playerIncrement, int card)
{
	int i = user;
	//While i < SIZE and while i != the last player in the sequence
	while(i < SIZE && playerIncrement != 0 && i != 0) {
			drawCard(hands,i,playerIncrement,card);
			nextPlayer(hands,i);  //i is now the next player who is in the game
			playerIncrement = i;  
			nextPlayer(hands,playerIncrement); //playerIncrement is now the player after i
		}


	//This only runs if the user didn't win on this turn
	//If i = 0 ever equals zero, the turn is already over
	if(getSize(user,hands) != 0 && cardTest(user,hands) == true && i != 0)
		drawCard(hands,i,user,card);

	//Runs only if the user won from drawing a card and the last player can't draw from you
	else if(getSize(user,hands) == 0)
		cout << "Player " << i << " cannot take a card from you because you have no cards!" << endl;
}
