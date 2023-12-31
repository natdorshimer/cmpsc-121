#include <iostream>
using namespace std;

//Note: The main function design is actually psuedocode.
//		It's what I expect the main function to look like
//      The functions I made are included after the main function
//      You should read the discriptions of those to have the best idea of what main is doing
//Should I use parallel arrays or multidimensional arrays for the hands?


//***About the 2-Dimensional Hand Arrays***
//hands[][deckSize] is an occurrence array where each row is a player's hand
//Each entry in the row corresponds to the number of that card
//hands[5][ACE] is the number of ace cards the player 5 has
//hands[0][] is an empty row that will never be used to lower errors in the program


//All occurence arrays will obey the entries listed below


//Probably the only global constants necessary
const int deckSize = 14;     //The number of cards 
const int SIZE = 9;    //Max number of players. 0th isn't counted
const int ACE = 1;           //There is no zero card
const int JACK = 11, QUEEN = 12, KING = 13;
const int user = 1, player2 = 2, player3 = 3; //etc.

const char cardsArray[5][deckSize] {
	{0,0,0,0,0}
	{'A','C','E',0,0}
	{'T','W','O',0,0}
	{'T','H','R','E','E'}
	{'F','O','U','R',0}
	{'F','I','V','E',0}
	{'S','I','X',0,0}
	{'S','E','V','E','N'}
	{'E','I','G','H','T'}
	{'N','I','N','E',0}
	{'T','E','N',0,0}
	{'J','A','C','K',0}
	{'Q','U','E','E','N'}
	{'K','I','N','G',0}


};

//Main function
//This handles the game process itself
//calls: drawCard, getSize, displayHand, cardTest
int main()
{
	//This is the main game
	//The do loops will let the player keep playing
	char playGame;

	int deck[deckSize];
		for(int i = ACE; i < deckSize; i++) 
			deck[i] = 4;  //4 cards of each in a deck

		deck[QUEEN]--; //This removes a queen from the game

    
	int hands[playerSize][deckSize]; //The multidimensional array for the hands of players

	//do loop allows user to choose if they want to play again
	do 
	{
		int playerSize;
		//I may make this a loop in case the user picks a number higher than 8 or less than or equal to 1
		cout << "How many players would you like? (including yourself. Max: 8)";
			cin >> playerSize;


		//Distributing cards in deck to players
		//Number of cards each player has is determined by playerSize
		distributeDeck(deck,hands,playerSize);


		//The game loop ends when the user runs out of cards or all the AI do
		//Then the program allows the user to choose if they want to play again
		while(getSize(user,hands) > 0 && cardTest(user,hands) == true) 
		{
			int playerIncrement = user + 1;
			while(getSize(playerIncrement,hands) == 0)
				playerIncrement++; //This will ensure that the person you are drawing from is in the game


			cout << "You currently have these cards in your hand:  " << endl;
			displayHand(user,hands); cout << endl;

			cout << "You get to draw a card from a hand containing " << getSize(playerIncrement,hands) << endl;
			cout << "Choose a number from 1 to " << getSize(playerIncrement,hands) << endl;
				cin >> card;
			for(int i = user; i < SIZE;)
			{
				//If there are people who have cards ahead of that person
				if(cardTest(i,hands) == true)
				{
					drawCard(i,playerIncrement);

					i = playerIncrement;

				
					if(cardTest(i,hands) == true)
					{
						playerIncrement++;
					
					while(getSize(playerIncrement,hands) == 0)
						playerIncrement++; }
				}
				//The last person in the sequence with cards draws from the user
				else if(cardTest(i,hands) == false)
					drawCard(i,user);
			}

		

			
			if(getSize(user,hands) > 0 && cardTest(user,hands) == false)
				cout << "You are the only player remaining. You lose!" << endl;

			else if(getSize(user,hands) == 0 && cardTest(user,hands) == true)
				cout << "You have no cards! A winner!" << endl;

		}


		cout << "Game over!" << endl << "Play another game (y/n)?"; 
		cin >> playGame;

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
//			int player: the player you wish to know the hand size of
int getSize(int player,const int hands[][deckSize])
{
	int digits = 0;

	for(int i = 0; i < deckSize; i++)
		digits = digits + hands[player][i]

	return digits;


}



//The person drawing the card (user) takes a card from the card pool of another player
//Outputs different text depending on who draws from who
//Does not output text if  (firstPlayer || secondPlayer) != user
//Pre-conditions: hands[][deckSize] is an occurence array of cards. 
//				(firstPlayer != secondPlayer) && (0 < (firstPlayer && secondPlayer) <= 8)  
//Post-condition: a card is removed from hands[firstPlayer][] and added to hands[secondPlayer][]
//Calls: randDraw, getSize
       //Side note: Can combine randDraw and drawCard. Might do that in final program
//Parameters: an occurrence array hands[][deckSize] and two player integers
//			 the first player takes the card from the second player
//           these integers correspond to hands[player][], the row of their hand array
void drawCard(int hands[][deckSize], int firstPlayer, int secondPlayer)
{
	card = randDraw(card);
	int count = 0;
	for(int i = 0; i < deckSize && count != card; i++)
	{
		if(hands[secondPlayer][i] == 1)
			count++;
	}
	hands[firstPlayer]++;
	hands[secondPlayer]--;

	if(firstPlayer == user);
		cout << "You draw a " << displayCard(count);
	else if(secondPlayer == user);
		cout << "A computer player takes your " << displayCard(count);
}



//This function displays the cards in the hand to the user
//Pre-Condition: hand[][deckSize] is an occurence array with each position corresponding to a card value
//Example: If the array in hands[user][] is {0,0,1,1,1,0,0,0,1,0,0,0,1,0} it will display on screen:
//		You currently have these cards in your hand:
//		Three Queen Two Eight Four
void displayHand(int player, const int hands[][deckSize])
{
	for(int i = 0; i < deckSize; i++)
		if(hands[player][i] > 0)
		{
			for(int j = 0; j < 5 && cardsArray[i][j] != 0; j++)
				cout << cardsArray[i][j];
				cout << " ";

		}

}

void displayCard(int card)
{
	for(int i = 0; i < 5 || cardsArray[i] == 0; i++)
		cout << cardsArray[cards][i];
	cout << endl;
}

//This function takes cards out of deck[] and randomly 
//The smaller the playerSize, the more cards each player will have
//distributes them to hand according to playersize
//Pre-Condition: deck[] and hand[][deckSize] are occurence arrays and playersSize is <= 8			
//Post-Condition: hands array has all cards from deck. Each player has an equal (plus or minus 1) number of cards
//Calls: randDraw
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
		for(int i = ACE; i < deckSize && getSize(hands[i][j]) < cards; i++)
		{
			//This loop ensures deckCopy[random] is always > 0
			int random = randDraw(13);
			while(deckCopy[random] == 0)
				random = randDraw(13);

			//Takes one out of deckCopy and adds it to hands
			deckCopy[random]--;
			hands[i][random]++;


		}

		//This will get rid of the extra cards
		//The last player is a bit lucky in this sense
		if(extraCards > 0) 
		{
			int randomExtra = randDraw(13);
				while(deckCopy[randomExtra] == 0)
					randomExtra = randDraw(13);

			deckCopy[randomExtra]--;
			hands[i][randomExtra]++;
			extraCards--;
		}
	}


}


//Returns TRUE if every player past placement has cards
//This is used to see if there are players remaining
//Pre-Condition: hands[][deckSize] is an occurence array with deckSize columns  and placement <= 8
//Paramters: placement: 
bool cardTest(const int placement, const int hands[][deckSize])
{
	bool test = false

	for(int i = (placement+1); i < SIZE && test == false; i++) 
		for(int j = 0; i < deckSize && test == false; i++) 
			if(hands[i][j] > 0)
				test = true;

	return test;

}
