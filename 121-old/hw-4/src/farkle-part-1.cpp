#include <iostream>
#include <math.h>
using namespace std;

const int SIZE = 6;                //Array size for dice

//These constants are all for scoring the dice. They can be changed here for different scoring rules
const int straightScore = 1000;
const int threeAlike = 100;
const int fourAlike = threeAlike*2;
const int fiveAlike = fourAlike*2;
const int sixAlike = fiveAlike*2;
const int threePair = 500;


//Functions
int rollDie();							    //rolls a die between 1 and 6
int scoreDice(int[]);                       //Scores the set of dice

void rollArray(int[], int size);		    //Rolls a random array of of SIZE entries
void convertInput(int,int[],int&);          //Converts an input into an array
void convertOccurence(const int[],int[]);   //Converts a standard array of die into an occurence array


//boolean values to check for in main function
bool hasStraight(int[]);       //Does the set have a straight?
bool hasThreePair(int[]);      //Does the set have a three pair?
bool scoreable(int[]);         //Is the set of dice GIVEN scoreable?
bool validity(int[],int[]);    //Checks to see if the dice the user inputs match up with the dice given
bool validDice(int[]);         //Is the set of dice INPUT have all valid dice for scoring?






//calls: convertINput, scoreable, scoreDice
int main()
{
	//The following two variables refer to the dice being rolled
	int rolledDice[SIZE];       
	int rolledDiceSize = SIZE; 

	//Variables for dice user inputs
	int diceInputArray[SIZE];
	int diceSize;         
	int diceInput;
	
	//Score variables
	int totalScore = 0;

	
	char answer = 'y';
	while(answer == 'y')
	{
		//BEGINNING OF TURN
		cout << "The turn begins... " << endl;

		//If the rolled dice are scoreable, then this if statement will run
		//If the rolled dice are not scoreable, then, as the rules state, -->
		//	the total score is reduced to zero and the turn ends. 
		char turnAnswer = 'y';
		while(turnAnswer == 'y')
		{
			//BEGINNING OF ROUND
			rollArray(rolledDice,rolledDiceSize);
			if(scoreable(rolledDice) == true)
			{
				//The loop is in case the user uses an invalid selection of dice
				//validity tests whether or not the selection matches up with the given dice
				//validDice tests whether or not ALL of the given dice can be given a score
				//If validity fails or validDice fails, the user has to input again
				do
				{
					cout << "Please enter the dice you wish to score, with NO spaces:  ";
						cin >> diceInput;

					//Converting user input into an array
					convertInput(diceInput,diceInputArray,diceSize);
			
					if(validity(diceInputArray,rolledDice) == false)
						cout << "You can't use those dice. Please input a valid selection of dice." << endl;

					else if(validDice(diceInputArray) == false)
						cout << "Those dice are not scoreable. Please input a valid selection of dice." << endl;

	
				} while(validity(diceInputArray,rolledDice) == false || validDice(diceInputArray) == false);   //Loop only works while false
				
	
				//The hot dice specification
				//If the user can score all of the rolled dice, then he can use 6 on the next turn
				//Otherwise, the amount of dice will be reduced by the amount he uses (diceSize)
				if(rolledDiceSize != diceSize)
					rolledDiceSize = rolledDiceSize - diceSize;    //For the next iteration 
	
				else if(rolledDiceSize == diceSize)
					rolledDiceSize = SIZE;

	
				//Score from the previous turn + the score from the input
				totalScore = totalScore + scoreDice(diceInputArray); 
				cout << "Score so far this turn: " << totalScore << endl;
				

				//END OF ROUND 
				if(rolledDiceSize != SIZE)
				{
					cout << "You may continue, rolling " << rolledDiceSize << " die. Do so (y/n)?  ";
					cin >> turnAnswer;
				}
				else if(rolledDiceSize == SIZE)
					cout << "Hot dice! You must roll again." << endl;
		
			}
		
			//This only runs if the above if statement did not and the rolled dice are not scoreable
			//END OF ROUND
			else
			{
				cout << "There is no way to score. Turn ends! Total = " << totalScore << endl;
				turnAnswer = 'n'; //The end of the round
			}
		}
		

		//END OF TURN
		//Initializing variables because turn is over
		totalScore = 0; //Because rolledDiceSize = 0;
		rolledDiceSize = SIZE; //For the next turn

		cout <<  endl << "Player another turn (y/n)?  ";
		cin >> answer;
	}

	
	return 0;
}

//Takes a given array (dice[]) and creates a occurence array from it (occurenceDice[])
//All functions using arrays will be occurence arrays
void convertOccurence(const int dice[], int occurenceDice[])
{
	//Initializing the dice
	for (int i = 0; i < SIZE; i++)
		occurenceDice[i] = 0;
	

	for (int i = 0; i < SIZE; i++)
	{
		if(dice[i] != 0)
			occurenceDice[dice[i]-1] = occurenceDice[dice[i]-1] + 1;
	}
	
}


//Rolls a die between 1 and 6
int rollDie() { 
	return (rand()%6 + 1); 
}

//Makes an occurence array filled with random
void rollArray(int regularDice[], int arraySize)
{
	int dice[SIZE];

	for(int i = 0; i < SIZE; i++)
		dice[i] = 0;

	for(int i = 0; i < arraySize; i++)
		dice[i] = rollDie();

	
	//Output the array before converting it to occurence
	cout << "Rolling " << arraySize << ":";
	for(int i = 0; i < arraySize; i++)
		cout << dice[i] << " ";

	//Converts the roll array to an Occurence array
	//It's more useful this way
	convertOccurence(dice,regularDice);       

	cout << endl;
}


//convertInput:
//counts the individual digits in an integer value
//used to allow a single input value to represent a set of dice to keep
//The outputed array is an OCCURENCE array
void convertInput(int inputValue, int regularDice[], int& digits)
{
	int dice[SIZE];

	for(int i = 0; i < SIZE; i++)
		dice[i] = 0;

	//Turns the inputValue into single digits to input into dice[]
	for(int i = 0; i < SIZE; i++)
	{
		dice[i] = inputValue%10;           //Assigns last digit to array
		inputValue = inputValue/10;        //Truncates the last digit
	}

	//Converts it to an occurence array
	convertOccurence(dice,regularDice);   
	
	//Since this is an occurence array now, adding entries gives the number of digits
	digits = 0;
	for(int i = 0; i < SIZE;i++)
		digits = digits + regularDice[i];      

}
//hasStraight:
//returns a boolean indicating that the set of dice is a straight
//(one each of all the values from 1 to 6)
//Parameter:
//	dice (input int array) : the dice to examine

bool hasStraight(int dice[])
{
	bool straight;

	for(int i = 0; i < SIZE; i++)
	{
		if(dice[i] != 1)
			straight = false;
	}

	return straight;
}



//hasThreePair:
//returns a boolean indicating that the set of dice has three pair
//(two each of three different values)
//Parameter:
//    dice	(input int array)	the dice to examine

bool hasThreePair(int dice[])
{
	bool threePair = false;

	int count = 0;
	for(int i = 0; i < SIZE; i++)
	{
		if(dice[i] == 2)
			count++;
	}
	
	if(count == 3)
		threePair = true;

	return threePair;
}

//scoreable:
//returns a boolean indicating whether it is possible to score with any dice
//if this returns false ( no score possible ), the current turn will end
//Parameter:
//	dice (input int array) : the dice to examine
//Pre-condition:
//	the total number of dice represented is between 1 and 6, inclusive
//Calls: hasStraight, hasThreePair

bool scoreable(int dice[])
{
	bool valid = false;

	//Runs until it goes through the array or it finds a five or a one dice
	for(int i = 0; i < SIZE && valid == false; i++)
	{
		if (dice[0] != 0 || dice[4] != 0)
			valid = true;

		if (dice[i] >= 3)
			valid = true;
	}

	if(hasStraight(dice) == true)
		valid = true;
	else if(hasThreePair(dice) == true)   //Can't have straight and three pair
		valid = true;

	return valid;

}


int scoreDice(int dice[])     
{   

	int score = 0;
	int scoreTemp = 0;
	int count = 0;

	//(1/4)*(450-50*(i+1))*dice[i]; produces the score for a 1 or a 5 if there are 1 or two of those die
	//If there's two dice of value five, it will return a value of 100
	//If there's two dice of value one, it will return a value of 200
	for(int i = 0; i < SIZE; i++)
	{
		if((dice[i] == 1 || dice[i] == 2)  && (i == 0 || i == 4))
		{
			if(i == 0)
				score = score + 100*dice[i];
			if(i == 4)
				score = score + 50*dice[i];
		}
			
	

		//Alike scores
		//You can't have a three alike and a four alike, so they're all else-ifs 
		if(dice[i] == 3 && i == 1)
			score = score + 1000;
		else if(dice[i] == 3 && i != 0)
			score = score + threeAlike*(i+1);
		else if(dice[i] == 4)
			score = score + fourAlike*(i+1);
		else if(dice[i] == 5)
			score = score + fiveAlike*(i+1);
		else if(dice[i] == 6)
			score = score + sixAlike*(i+1);

		if(hasStraight(dice) == true)
			score = straightScore;

		if(hasThreePair(dice) == true)
			score = threePair;
		
	}

	return score;
}


//In order for the function to be valid, the function must check if each element matches up with the given dice
//In other words, the occurence version of the input array must have elements less than or equal to the given occurance
//This is because the the chosenDice can only use dice the given dice has.
bool validity(int chosenDice[],int rolledDice[])
{

	bool valid = true;

	for(int i = 0; i < SIZE; i++)
	{
		if(chosenDice[i] > rolledDice[i])
			valid = false;
	}

	return valid;
}



//Checks to see if ALL dice can be used 
//If it has 2 or less of a die that's not 1 or 5, it is invalid
	//Unless it is a straight or a threePair
bool validDice(int dice[])
{
	bool valid = true;

	for(int i = 0; i < SIZE; i++)
	{
		if((dice[1] <= 2 && dice[1] > 0) && hasStraight(dice) == false && hasThreePair(dice) == false)
			valid = false;
		else if((dice[2] <= 2 && dice[2] > 0) && hasStraight(dice) == false && hasThreePair(dice) == false)
			valid = false;
		else if((dice[3] <= 2 && dice[3] > 0) && hasStraight(dice) == false && hasThreePair(dice) == false)
			valid = false;
		else if((dice[5] <= 2 && dice[5] > 0) && hasStraight(dice) == false && hasThreePair(dice) == false)
			valid = false;
	}

	return valid;
}