// Practice with Arrays
// CMPSC 121       Fall 2013
// Name: Natalie Dorshimer
// This program provides a little practice
// programming with arrays.  All of the function
// prototypes have already been provided, so the
// exercise is all about manipulating the arrays themselves.

// NOTE: None of your changes to this file are to be in
// the main function, but only in the indicated places.
// This will facilitate testing code for different data.

#include <iostream>			// access to cin, cout
#include <iomanip>			// access to setw
using namespace std;

// some function prototypes to be implemented later
void printArray( const int[] );						// show the contents of an array
void printPermuted( const int[], const int[] );		//    or in a permuted order

void ArrayTest( const int[], const int[], int );	// various array practice loops

void reflow( char[], int );							// rearrange some character data

int main()
{
	// These arrays hold data to be tested with.  Different sizes!
	int arrayOne[] = { 3, 1, 7, 5,10, 8, 2, 9, 6, 4 };
	int arrayTwo[] = { 3,-1, 7, 5,-3, 8,-2, 9,-6, 4, 2, -8 };

	// These are used to change the order in which array 
	// elements are processed. (They make the data appear sorted)
	int permute1[] = { 1, 6, 0, 9, 3, 8, 2, 5, 7, 4 };
	int permute2[] = { 11, 8, 4, 6, 1, 10, 0, 9, 3, 2, 5, 7 };
	
	// A string is just an array of characters
	char getty[] = 
"Four score and seven years ago, our forefathers brought\
 forth on this continent a new nation, conceived in liberty\
 and dedicated to the proposition that all men are created equal.";
	char reform[200];			// to hold a copy of the above
	
	ArrayTest( arrayOne, permute1, 10 );
    ArrayTest( arrayTwo, permute2, 12 );
	
	for (int i = 60; i >= 40; i -= 10)
	{
		cout << '|' << setw(i) << '|' << endl;
		strcpy_s(reform, getty);
		reflow(reform, i);
		cout << reform << endl << endl;
	}
}

// printArray
// Display the contents of the array, all on the same line
// 
// Parameters:      list[]		the array to display
//					size		number of elements in array to display
void printArray( const int list[], int size )
{
	for(int i = 0; i < size; i++)
		cout << setw(4) << list[i];
	
	cout << endl;
}

// printPermuted
// Display the contents of the array on one line, in a permuted order
// 
// Parameters:	list[]		the array to display
//				permute[]   a permutation of the values 0 to size-1
//				size		number of elements in these arrays
//
// Ex. if the first three elements of permute[] are 4, 0, 3
//     then the first three values displayed are list[4], list[0], list[3]
void printPermuted( const int list[], const int permute[], int size )
{

	//  STEP 2:  Complete the function here.
	//           For neat output, use setw(4) as the last function did.
	for(int i = 0; i < size; i++)
	{
		cout << setw(4) << list[permute[i]];

	}
	cout << endl;
}

// STEP 3:  Implement this function.
//
// Hint: assume the first array value is the largest value,
// then search the array is a larger one,
// remembering where that largest value is.
//
// maximumPosition
// find the maximum value of an array
//
// Parameters:  list[]		the array to examine
//				length		number of array elements to examine
// Returns:  the position of the maximum value in the array
//     e.g. if the largest is in list[4], return 4
//     NOTE: Not the largest value itself, but its position
//
// Hint: assume the first array value is the largest value,
// then see if there is a larger one.
int maximumPosition( const int list[], int length )
{
	int maxPos = 0;					// initialized to please the compiler
	int maxVal = list[0];           //Gotta start somewhere

	for(int i = 0; i < length; i++)
	{
		if(list[i] > maxVal)
		{
			maxVal = list[i];
			maxPos = i;
		}
	}


	return maxPos;
}

//  ArrayTest
//  Just a bunch of random operations on arrays
//  Parameters:	list[]		an array of values to handle
//				permute[]	a permutation of the list
//              size		number of elements in these arrays
//  Local Var:  list2[]		another array to manipulate
void ArrayTest( const int list[], const int permute[], int size )
{
	int list2[20];		// big enough (we won't use it all)

	// STEP 4:  Display the contents of the argument 'list'
	//			of the 'size' given above
	//          Call a function above to do so (NO LOOP here!)
	//			Syntax Hint: you want the display the entire array,
	//			    not just one subscripted array element.
	//		    The brackets [] are not part of the name of the array.
	//          NOTE: NO credit if you do not call the function above

	printArray(list,size);

	// STEP 5:  Compute the sum of the elements of the argument 'list'
	//          whose size was given as a parameter

	int sum = 0;						// sum of no numbers is zero

	for(int i = 0; i < size; i++)
		sum = sum + list[i];

    cout << "The sum is " << sum << endl;

	// STEP 6:  Count the odd values in the argument 'list'

    int count = 0;						// no odd values found yet

	for(int i = 0; i < size; i++)
	{
		if(list[i]%2 != 0)
			count++;
	}
	cout << "There are " << count << " odd values." << endl;

	// STEP 7:  If you have not already done so, compile and test the above code.

    // STEP 8:  Copy all the values from list into list2 (in the same order)
	//          You will have to do this one element at a time.

	for(int i = 0; i < size; i++)
		list2[i] = list[i];

	// STEP 9:  Display the values of list2, permuted by the array called permute
	//          NOTE:  You must use a function implemented above!
	cout << "Permuted list2 (should appear sorted): "; printPermuted(list2,permute,size); cout << endl;
	
	
	// This loop implements a selection sort, assuming the maximumPosition
	// function works properly.  It places the largest values at the end first.
	for (int len = size; len > 1; len--)
		swap( list2[len-1], list2[maximumPosition( list2, len )] );

	// STEP 10:  Display the values of list2 now!  (not permuted)
	//           NOTE:  This still uses a function implemented above.
	//           Since the list has been sorted, it should appear so.
	cout << "Unpermuted list2 (after sorting): "; printArray(list2,size); cout << endl;



	cout << endl;

	// STEP 11:  Test your results.  The array should appear sorted in both cases.
}

	// STEP 12:  Complete the following function.  The main program will test it.
	// Try to understand how the algorithm works before diving into the code

//  reflow
//  Rearranges text to fit on a screen within assumed margins.
//  Parameters:	text[]		text to rearrange
//				lineLength	maximum number of characters per line
//
//  Overall algorithm:
//  Start from the beginning of the text
//  While the remaining text > length of a line
//      Skip forward over a number of characters equal to the line length
//      Search backwards for a space character   ' '
//			(hint: this is a nested loop)
//	    Replace the space with a newline character   '\n'
void reflow( char text[], int lineLength ) 
{
	int  textLength = int(strlen(text));		// total number of characters
    int position = 0;
	int count = 1;

	while((textLength - position) > lineLength)
	{
		position = position + lineLength;
		for(int i = position; text[position] != ' '; position--) { /*empty*/ }
		
		text[position] = '\n';

		position++;


	}

	


}



	// Hint: for the while condition listed above,
	//    with a current a current position in the text and total textLength,
	//       how much of the text remains to be examined?


