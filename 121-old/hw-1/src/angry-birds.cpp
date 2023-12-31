// Angry Birds - Homework 1
// Written by:   Natalie Dorshimer
// On the Date:  January 21, 2014

//Given conditions on Angry Birds planet, this program solves the necessary altitude from which to drop a rock in order to hit the pigs
//Given a specified tree height and distance to pig stronghold, it also determines how far a rock will make it into the pig stronghold
//Acceleration due to gravity (g) is unknown: user inputs horizontal velocity and time

//Given:    x = horizontal displacement in meters and horizontal_Velocity is horizontal velocity
//				Pig Range and pigPerimeter are both used as different types of horizontal displacement
//			x = horizontal_Velocity*time   or   horizontal_Velocity = x/time 
//			y = vertical position and g is the acceleration due to gravity
//          y_final = y_initial - 1/2*g*t*t   if y_final=0, g=(y_initial*2)/t/t

#include <iomanip>
#include <iostream>     
#include <cmath>        
using namespace std;

int main()
{

	//Declared Variables
	const double Y_TEST_1 = 10;          //Altitude to calculate acceleration due to gravity
	const double Y_TEST_2 = 1000;        //Value to calculate range at altitude of 1000 m
	double x_range;                      //User declared rock range
	double g;                            //Acceleration due to gravity
	double horizontal_Velocity;          //Calculated velocity of angry bird or rock
	double pigAltitude;                  //altitude necessary to attack pigs at an entered range
	double pigRange;                     //How far away the pigs are
	double time;                         //General variable for time
	double treeHeight;                   //Height of the tree (extra credit)
	double pigPerimeter;                 //Distance inside the pig perimeter (extra credit)
	//End of declared variables



	//Beginning of the program
	cout << fixed << setprecision(2);                                              //Sets the precision of real numbers for the program
	cout << "An angry bird released a rock 10 meters above the ground." << endl;   //Gives the user context
	cout << "How far (in meters) did the rock fly when released at 10 meters? ";   //Tell the user to input distance after release in meters
		cin >> x_range;                                        
	cout << "How long (in seconds) did it take for the rock to fall 10 meters? ";  //Tell the user to input time until the rock hits the ground in seconds
		cin >> time; 



	//Calculates the horizontal velocity of the fully-laden angry bird, the gravitational acceleration on the planet, and the maximum range of the rock
	horizontal_Velocity = x_range/time;                       //calculate the horizontal velocity of the rock
	g = (2*Y_TEST_1)/(time*time);                             //Calculate acceleration due to gravity on angry bird planet
	x_range = horizontal_Velocity*sqrt(2*Y_TEST_2/g);         //Calculates range at maximum height of 1000 m (derived from altitude = 1/2 g t^2, solving for t and subsituting into x = horizontal_Velocity*t)


	cout << "The maximum range at an Angry Bird's maximum altitude of 1000 m is " << x_range <<  " m." << endl;  
		//Displays the calculation to the user and sets the precision for the program
	cout << "How far away are the pigs? (in meters) "; 
		cin >> pigRange; 


	
	//Calculate the altitude necessary for the rock to cover that distance with time = pigRange/horizontal_Velocity  and pigAltitude = (1/2)*g*t^2
	time = pigRange/horizontal_Velocity;
	pigAltitude = g*time*time/2;


	cout << "The angry bird needs to be at an altitude of " << pigAltitude << " m to hit the pigs" << endl;


	//Extra Credit is below//

	cout << "\nA weak angry bird wants to release a rock from a tree." << endl;         //Gives context to the user about the weak angry bird
	cout << "How tall is the tree? ";                                                   //User inputs tree height and distance to stronghold
		cin >> treeHeight; 
	cout << "How far is the pig stronghold? ";
		cin >> pigRange;                                                               

	//Calculations to solve for the distance between 
	time = sqrt(2*treeHeight/g);                //The time it takes for the rock to land on the ground
	x_range = horizontal_Velocity*time;           //Distance the rock travels
	pigPerimeter = x_range - pigRange;          //Distance the rock travels - distance to pig perimeter

	/* Possible Code

	if (pigPerimeter < 0)
	{

		cout << "You will not make it to the pig stronghold from this tree." << endl;

	}

	if (pigPerimeter == 0)
	{

		cout << "You just made it to the pig stronghold!" << endl;

	}

	else
	{

		cout << "You are " << pigPerimeter << " m within the pig stronghold!" << endl;

	}
	
	End of Possible Code */

	//Possible Code (current)
	cout << "You are " << pigPerimeter << " m within the pig stronghold!" << endl;
	//End of possible code (current)

	//End of Extra Credit//
	return 0;           
}
			