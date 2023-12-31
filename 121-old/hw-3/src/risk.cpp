//Homework #3: Risk
//Written by:  Natalie Dorshimer
//On the Date: February 24, 2014

//This program simulates a battles between two armies in Risk. 

//Rules:
//When an army of size x attacks a defending army of size y, dice are rolled.
//The attacking army get a maximum of 3 die, or however many units they have. (Whichever is smaller)
//The defending army get a maximum of 2 die, or however many units they have. (Whichever is smaller)
//When the die are rolled, the maximum die are compared. Higher dice wins and the defender wins ties.
//Ex: Attacking army of size 5 rolls (5 6 1) and defending army of size 4 rolls (5 2). Result:
//Attack: (6 5 1) 
//Defend: (5 2  )   
//Attacking 6 beats 5 and attacking 5 defeats 2. Therefore, defending army loses two units. 
//Attack: Still has 5 units
//Defend: Lost 2: Down to army of size 2. 

//The user can pick up to four different choices, listed in the main function.
//These choices are all different variations of the described battle above. 

//Function descriptions
//The battles are decided with the skrimish() function, listed below main()
//Functions rollDie() and sortThree() are used in skirmish().
//rollDie() rolls function between 1 and 6. sortThree() sorts 3 things from greatest to smallest.

#include <iostream>
using namespace std;


//Functions used in main.
//rollDie gives a random number between 1 and 6
//sortThree sorts three numbers from greatest to smallest
//skirmish is a single battle between two armies. How this works is listed in the above description.
int rollDie();                                                     
void sortThree(int& first, int& second, int& third);
void skirmish(int& attackers, int& defenders);        



//Main:
//simulates multiple Risk battles, one after another, as many as a user desires
//Inputs (from the keyboard):
//   attack	(int)	the size of the attacking army 
//   defend	(int)	the size of the defending army
//   choice	(int)	user interface option controlling the simulation
//Calls:  skirmish
int main()
{
	int attack;        //The number of units the attacking army has
	int defend;        //The number of units the defending army has
	int choice;        //The course of action the user can take. (1 through 4)
	int withdraw;      //The variable that checks for withdrawal from battle
	int count = 0;     //If the loop ran once, this variable is changed. Adds two lines of spacing in between loops

	//Loop: Lets user decide if they want to continue
	for(char more = 'y'; more == 'y'; cin >> more)                   
	{
		//This adds two lines of spacing after the loop runs once. 
		//Improves readability of program
		if (count > 0)
			cout << endl << endl;

		//Initializing withdraw variable
		withdraw = 0;

		cout << "Please input attacker size:  ";
			cin >> attack;
		cout << "Please input defender army size:  ";
			cin >> defend;

		//Program restarts when player withdraws or armies are defeated
		//This loop only runs as long as:
		//   1. There are at least attack and defense units available
		//   2. The player does not withdraw
		while((attack > 0 && defend > 0) && withdraw == 0)
		{
			cout << "Please choose one of the following: " << endl;
			cout << "  1            attack for one round only" << endl;
			cout << "  2            attack until one army is completely defeated" << endl;
			cout << "  3            attack until attacking armies have ___ left" << endl;
			cout << "  4            withdraw from the battle"                     << endl;
				cin >> choice;


			//Attacking for one round is just a skirmish
			if(choice == 1)                     
				skirmish(attack, defend);

			//Attack until one army is completely defeated
			if(choice == 2)      
			{
				while(attack > 0 && defend > 0)        
					skirmish(attack, defend);
			}

			//Attack until armies have input left
			if(choice == 3)      
			{
				int reserve;
				cout << "How much do you wish to keep in reserve?   ";
					cin >> reserve;
					
				while((attack > reserve) && (attack > 0 && defend > 0))     //Must keep original loop conditions
					skirmish(attack, defend);

			}

			//Withdrawl Choice
			if(choice == 4)      
				withdraw = 1;
		}

		//count only needs to be changed once
		if (count == 0)                                 
			count++;

		cout << "Simulate another battle?  (y/n)   ";    //Will update as described in the for loop
	}

	return 0;
}




//skirmish:
//simulates one competitive die roll event
//it rolls any needed dice, sorts them, and resolves the outcome
//Parameters:
//   attack	(int, modified)		the size of the attacking army
//   defend	(int, modified)		the size of the attacking army
//pre-condition:  both input parameters are greater than zero
//post-condition: one or both parameter is reduced in value
//		and neither is less than zero
//Calls:  rollDie, sortThree
void skirmish(int& attackers, int& defenders)         
{
	int die_A1, die_A2, die_A3;          //Attacking army dice
	int die_D1, die_D2, die_D3;          //Defending army dice
	int countA = 0;                      //This variable counts the amount of units attacking army lost
	int countD = 0;                      //Counts units that defending army lost


	//Following block of code determines the die number for attackers/defenders
	//A value of zero for a die means that there is no die. 
	
	//Both have to have at least one die
	die_A1 = rollDie();
	die_D1 = rollDie();

	if(attackers >= 3) //Attackers can have, at most, three die.
	{
		die_A2 = rollDie();
		die_A3 = rollDie();
	}
	if(attackers == 2)
	{
		die_A2 = rollDie();
		die_A3 = 0;
	}
	if(attackers == 1)
	{
		die_A2 = 0;
		die_A3 = 0;
	}

	//Defenders can have, at most, two die. 
	if(defenders >= 2)
	{
		die_D2 = rollDie();
		die_D3 = 0;
	}
	else
	{
		die_D2 = 0;
		die_D3 = 0;
	}
	//End of die determination 

	//This sorts the die for the attacking and defending armies
	sortThree(die_A1, die_A2, die_A3);
	sortThree(die_D1, die_D2, die_D3);
		

	    //Comparing the first set of die
		if (die_A1 > die_D1)
		{
			defenders--;                //Attackers only win if they are greater
			countD++;              //Defenders lost a unit
		}
		else
		{
			attackers--;                //Defenders win all ties
			countA++;              //Attackers lost a unit
		}

		//Comparing the second set of die
		//This block of code can only be run as there are die to compete. 
		//If either die = 0, the following code will NOT execute.
		//If there is only one die on defenders or attackers, only the code above will execute. 
		if ((die_A2 > die_D2) && die_A2 != 0 && die_D2 != 0)       //Second set of die.
		{
			defenders--;
			countD++;            //Defenders lost a unit
		}
		if ((die_A2 <= die_D2) && die_A2 != 0 && die_D2 !=0)       
		{
			attackers--;
			countA++;           //Attackers lost a unit
		}
		//There are no third set of dice: the minimum is bounded by the maximum of the defenders, which is two
		//Only the maximum valued dice matter
		//sortThree determined the maximum valud dice and assigned it to the first two dice. 
			//After sortThree executes, die_A3 is never used

		cout << "Attackers dice:   " << die_A1 << "   ";  if(die_A2 != 0) cout << die_A2 << "   "; if(die_A3 != 0) cout << die_A3; cout << endl;
		cout << "Defenders dice:   " << die_D1 << "   ";  if(die_D2 != 0) cout << die_D2; cout << endl;

		if(countA > 0) 
			cout << "Attacking army loses " << countA << endl;
		if(countD > 0)
			cout << "Defending army loses " << countD << endl;

		//Following code displays remaining army
		cout << "Remaining:   Attackers = " << attackers << "    Defenders = " << defenders << endl << endl;

}




//rollDie:
//rolls one six sided die
//Parameters:	none
//Returns a random integer from 1 to 6.
int rollDie()      
{
	int rand6;

	//rand()%6 produces values between 0 and 5. Adding 1 to it produces values between 1 and 6.
	rand6 = rand()%6 + 1;

	return rand6;
}


//sortThree:
//sorts its parameters so that they end up in decreasing order
//they can be in any order when the are provided, but will be sorted on exit
//Parameters:
//    first	(int, modified)
//    second	(int, modified)
//    third	(int, modified)
//pre-condition:  all values are between 0 and 6, inclusive
//post-condition: all three input values are returned, in sorted order
//		first has the largest, and third has the smallest
void sortThree(int& first, int& second, int& third)          
{

	if(third > second)
		swap(second,third);
	if(second > first)
		swap(second,first);
	if(third > second)
		swap(third,second);

	/* This code works, but I don't think it's what you're looking for
	while(second > first)
	{
		swap(second,third);
		swap(first,second);
	}

	if(third > second)
		swap(second,third);
		*/
	
	

}
