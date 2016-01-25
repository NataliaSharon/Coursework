#include "header.h"

#include <ctime>

#include "templates.h"

// Needs one of the following #includes, to include the class definition
#include "BouncingBallMain.h"
#include "SimpleDemo.h"
#include "Demo1Main.h"
#include "Demo2Main.h"
#include "Demo3Main.h"
#include "DemoMain.h"
#include "Demo4Main.h"
#include "Nxs13uMain.h"

//specifies size of window
#define BASE_SCREEN_WIDTH 800
#define BASE_SCREEN_HEIGHT 600



int main(int argc, char *argv[])
{
	int iResult;

	// Send random number generator with current time
	::srand(time(0));

	// Needs just one of the two following lines:
	//BouncingBallMain oMain;
	//SimpleDemo oMain;
	//Demo1Main oMain;
	//Demo2Main oMain;
	//Demo3Main oMain;
	//Demo4Main oMain;
	Nxs13uMain oMain;
	

	char buf[1024];
	sprintf( buf, "My Demonstration Program : Size %d x %d", BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT );
	//specifies windows caption
	//I've added two more text files into the src folder
	//iResult = oMain.Initialise( buf, BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT, "Lato-Semibold.ttf", 24 );
	iResult = oMain.Initialise(buf, BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT, "After the Goldrush.ttf", 75);
	iResult = oMain.MainLoop();
	oMain.Deinitialise();

	return iResult;
}
