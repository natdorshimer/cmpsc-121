#include <iostream>
using namespace std;

int main()
{
	int amount;     // amount of money to come up with (input)
	int quarters;   // number of quarters required (output)
	int nickels;    // number of nickels required (output)
	int pennies;    // number of pennies required;
	int dimes;      //number of dimes required;

	cout << "How much money do we need? ";
	cin >> amount; // input the desired total
	
	quarters = amount/25;                                  //calculates the amount of quarters needed (floored by default)
	dimes = (amount-quarters*25)/10;                       //calculates the amount of dimes needed
	nickels = (amount-quarters*25-dimes*10)/5;             //calculates the amount of nickels needed 
	pennies = amount-quarters*25-dimes*10-nickels*5;       //calculates the amount of pennies needed

	cout << "We need " << quarters << " quarters, " << dimes << " dimes, " << nickels << " nickels, and " << pennies <<" pennies.";  //Tells the user the final result

	system("PAUSE");
	return 0;
}