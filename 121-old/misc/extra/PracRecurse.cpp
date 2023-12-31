// Practice with Recursion
// Fall 2013
// Just a little practice with recursive functions
#include <iostream>
#include <time.h>				// for seeing how slow stuff is
using namespace std;

// This program file will put the main program last, so that
// functions will not need to have prototypes.  They will all
// appear before they are called.

// NOTE:  For all of these, there is a return statement included
//     just to keep the compiler happy.  This return statement
//     contains a nonsense value, so should not be included in your code

// STEP 1:
// Complete the following function as a recursive function
// sumInts:
//    sum of the positive integers <= argument n
// Parameter:
//	  n   (integer input)	largest integer to include in the sum
int sumInts( int n )
{
	if(n <= 0)
		return 0;
	else
		return n + sumInts(n-1);
}

// STEP 2:
// Complete the following function as a recursive function
// sumSquares:
//    sum of the squares of the positive integers <= argument n
// Parameter:
//    n    (integer input)	largest integer whose square is included in sum
int sumSquares( int n )
{
	if(n <= 0)
		return 0;
	else
		return n*n+sumSquares(n - 1);
}

// STEP 3:
// Complete the following function as a recursive function
// sumArray:
//    sum of the first elements in an array
// Parameters:
//    arr	(integer array input)	array containing values to add up
//    n		(integer input)			number of elements to include in the sum
int sumArray( const int arr[], int n)
{
	if(n <= 1)
		return arr[0];

	else
		return arr[n-1] + sumArray(arr, n-1);
}
// step 4:
// Complete the following function as a recursive function
// intPower
//     raises a value to a power that is an integer
// Parameters:
//     base		(double input)		base to multiply as needed
//	   exponent (integer input)		exponent to use
// NOTE: The exponent may be Negative -- but that is an easy
//     adjustment to the value you get from a Positive exponent
//     (and can use a recursive call to get that)
double intPower( double base, int exponent)
{
	if(exponent >= 0)
	{
		if(exponent == 0)
			return 1;
		else
			return base*intPower(base,exponent-1);
	}

	else if(exponent < 0)
		return 1/intPower(base,(-1)*exponent);
}

// STEP 5:
// Compile and run your program to see how well it does.

// STEP 6:
// Complete the following function as a recursive function
// fibonacci
//     returns a number from the fibonacci series:
//         f(0) = 1; f(1) = 1; f(2) = 2; f(3) = 3; f(4) = 5
//	   each successive element is the sum of the preceding two
// Parameter:
//		pos	(integer input)		desired position in Fibonacci sequence
int fibonacci( int pos )
{
	if(pos <= 1)
		return 1;
	else
		return fibonacci(pos - 1) + fibonacci(pos - 2);
}

// STEP 7:
// Complete the following function WITHOUT recursion
// fibArray
//     fills an array with the fibonacci sequence, as described above
// Paramters:
//		arr		(integer array output)		array to fill
//		n		(integer input)				number of array elements to fill
void fibArray( int arr[], int n )
{
	for(int i = 0; i < n; i++)
		arr[i] = 0;
	arr[0] = 1;
	arr[1] = 1;

	for(int i = 2; i < n; i++)
		arr[i] = arr[i-1] + arr[i-2];
}
// STEP 8:
// Compile and run your code to see how it performs

// STEP 9:
// Compute the following problem using an array like STEP 7 did.
// changeWays:
//     counts the number of sequences of dimes and quarters
//		  that add up to a particular total
//     e.g. 60 cents can be supplied four different ways:
//		  25+25+10,  25+10+25,  10+25+25, 10+10+10+10+10+10
//	Hint: How many ways can I get my result if I first insert a dime?
//        How many ways can I get my result if I first insert a quarter?
int changeWays( int cost )
{
	int arr[100] = {0};		// enough array spaces for up to 500 cents
	arr[0] = 0;
	arr[1] = 0;
	arr[2] = 1;
	arr[3] = 0;
	arr[4] = 1;
	arr[5] = 1;

	cost = cost/5;
	for(int i = 6; i < 100; i++)
		arr[i] = arr[i - 2] + arr[i - 5];
	
	// To make best use of this array, divide values by 5
	// so 75 cents would be represented at subscript 75/5

	return arr[cost];
}

// STEP 10:
// See if your last answer worked, and in a reasonable amount of time

int main()
{
	int sample[10] = { 2, 3, 5, 7, 1, 9, 4, 8, 6, 10 };
	int fibList[50];
	int tick, tock;				// for timing fibonacci
	int fib;					// fibonacci answer

	cout << "The sum of the first 5 integers is 15 = " << sumInts(5) << endl;
	cout << "The sum of the first 9 integers is 45 = " << sumInts(9) << endl << endl;

	cout << "The sum of the first 3 squares is  14 = " << sumSquares(3) << endl;
	cout << "The sum of the first 7 squares is 140 = " << sumSquares(7) << endl << endl;

	cout << "The first four prime numbers add up to 17 = " << sumArray( sample, 4 ) << endl;
	cout << "The sum of the first 10 integers is 55 = " << sumArray( sample, 10 ) << endl << endl;

	cout << "2 to the 3rd power is 8 = " << intPower( 2.0, 3 ) << endl;
	cout << "4 to the 0th power is 1 = " << intPower( 4.0, 0 ) << endl;
	cout << "5 to the 5th power is 3125 = " << intPower( 5.0, 5 ) << endl;
	cout << "10 to the -3 power is 0.001 = " << intPower( 10.0, -3 ) << endl;
	cout << "0.1 to the -3 power is 1000 = " << intPower( 0.1, -3 ) << endl << endl;

	tick = clock();
	fib = fibonacci( 10 );
	tock = clock();
	cout << "Computed fibonacci(10) = 89 = " << fib << " in " << 
		((tock-tick)*1.0/CLOCKS_PER_SEC) << " seconds" << endl;
	tick = clock();
	fib = fibonacci( 40 );
	tock = clock();
	cout << "Computed fibonacci(40) = " << fib << " in " <<
		((tock-tick)*1.0/CLOCKS_PER_SEC) << " seconds" << endl;
	tick = clock();
	fibArray( fibList, 50 );
	tock = clock();
	cout << "Filled 50 element fibonacci array in " <<
		((tock-tick)*1.0/CLOCKS_PER_SEC) << " seconds" << endl;
	cout << "Fib[10] = " << fibList[10] << " and fib[40] = " << fibList[40] << endl << endl;

	cout << "There are " << changeWays( 60 ) << " ways to come up with 60 cents." << endl;
	cout << "There are " << changeWays( 15 ) << " ways to come up with 15 cents." << endl;
	cout << "There are " << changeWays(300 ) << " ways to come up with 3 dollars." << endl;

	return 0;
}