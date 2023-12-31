//Homework Number 2: Prime Factorization

//Written By:    Natalie Dorshimer
//On the Date:   Februrary 6, 2014

//This program accepts a series of positive integers and displays its prime factors

//How it works:
//This program uses a sqrt() method to determine if the number is prime early on. 
//If there are no factors before or at the square root of the input, then the number has to be prime. 
//Ex: 121. The factors of 121 are 11 and 11. This is a composite number and has factors of sqrt(121)
//All composite numbers have a maximum factor value of sqrt(input) for the lower valued one
//If there are no factors before or at sqrt(input), it is impossible for the number to have factors at all.
//Using this, you can determine if a number is prime early on to save computation time.
//This program also saves computation time by not using multiples of 2. 
//The iterations start at 2, increases by 1 to 3, and then increases by 2 from that point on. 
//This is because multiples of 2 have factors of 2. There is no point in using them. 

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	//Variables
	int input;           //The variable the user inputs
	int i;               //The increment variable for checking values.
	int factor;          //The variable used for factoring the input. Input will retain its value throughout the program until the user enters another.
	int prime_test;      //Variable to check prime status
	double sqrt_input;   //Variable set aside for square rooting the input so it doesn't have to calculate it each loop
	int constant1 = 0;   //Variable to test for primality. 

	//Beginning of the program. This part will not be repeated if the user continues after the first factor.
	cout << "What number should we factor?   " ;
		cin >> input;

	while (input > 0)    //To make it easy for the user to repeat the numbers they want to enter
	{
		cout << input << " = ";
		factor = input;
		sqrt_input = sqrt(input);
		i = 0;                           //i needs a starting value before increments are made
		prime_test = 0;                  //If this value never changes, it is a prime number

		while (i <= sqrt_input && prime_test == 0)         //There's no point in going beyond the square root. If it does, it's a prime number and I can label it that.
		{                                                  //Using sqrt_input as the limit for i, and having i go up by increments of 2 starting at 3. If a number is prime, this only computes approximately (sqrt(input)/2)/input  values.
			if (i == 2)                                    //For example, using 655360001, this program only has to calculate 0.004% of the numbers, reducing computation time dramatically
				i++;
			else                         
				i = i + 2;                                 //All even numbers aside from 2 are useless. Only odd numbers matter, so every iteration goes up by 2 instead, starting at i = 3.

			if (factor%i == 0)
			{
				factor = factor/i;
				cout << i << "*";
				i = 0;                                    //When the iteration starts up, i =0 turns into i = 2, which then turns into i = 3, then i = i + 2
				prime_test = 1;                           //This if statement is only run if the number isn't prime because i == input only when it is prime. Since i has to equal input for a prime number, and it never reaches it with the condition i <= sqrt(input), prime_number remains zero.
			}


		}


		//This piece of code runs if the number isn't prime as determined in the last step. This is so the program can end early if the number is prime, cutting down on calculation time. 
		if (prime_test == 1)             
		{
			while (i <= input)          
			{
				if (i == 2)                  
					i++;                  
				else                        
					i = i + 2;                           //Skipping half the numbers because even numbers don't really matter aside from the number 2

				if (factor%i == 0)
				{
					factor = factor/i;
					cout << i << "*";
					i = 0;
				}


			}
		}

		//If prime_test remains zero throughout the program, it's prime
		if (prime_test == 0)
			cout << "prime";
		else
			cout << "1";                 //This avoids a more complicated way to include the "*" sign in the output.
		
		
		cout << endl << "Enter another number, or enter 0 to end the program.    ";
			cin >> input;       //Program repeats for positive numbers > 0
	}


	return 0;
}