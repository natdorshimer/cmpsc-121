#include <iostream>
using namespace std;

int main()
{
	//Declared variables
	int people;     // number of people at the party (input)
	int pizzas;     // number of 8-slice pizzas purchased for a party (input)
	int smallShare; // number of slices everyone gets, if divided evenly (output)
	int largeShare; // number of slices some might get, sharing leftovers (output)
	int numSmall;   // number of people getting the smaller share (output)
	int numLarge;   // number of people getting the larger share (output)
	int slices;     // number of slices in the pizzas

	//Introduction and user entries
	cout << "How many pizzas are there? ";
		cin >> pizzas;
	cout << "How many people are there? ";
		cin >> people;

	//Calculations
	slices = pizzas*8;              
	smallShare = slices/people;      //Everyone gets this amount, possily with slices%people leftover
	numLarge = slices%people;        //However much is leftover is also the number of people with extras
	numSmall = people - numLarge;    //numSmall + numLarge = people
	largeShare = smallShare + 1;     //It is impossible for people to get more than 1 extra


	//I have to include an if/or statement, otherwise the dialog will be awkward

	if (numLarge > 0)  //This only occurs if there are leftovers, and it can't be split evenly
	{

		cout << numSmall << " people get " << smallShare << " slices, while " << numLarge << " people would get " << largeShare << " slices.";

	}

	else               //This occurs if there aren't leftovers, and can be distributed evenly.
	{

		cout << numSmall << " people get " << smallShare << " slices.";

	}

	return 0;
}