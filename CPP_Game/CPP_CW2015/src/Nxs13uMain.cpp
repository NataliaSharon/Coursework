#include "header.h" 
#include "BaseEngine.h" 
//#include "templates.h"

//drawing objects
#include "Nxs13uPlayerOneObject.h" 
#include "Nxs13uPlayerTwoObject.h" 
#include "Nxs13uEnemyObject.h"

#include "Nxs13uMain.h"
#include "JPGImage.h" //loading images
#include "TileManager.h" //drawing tiles

//opening and writing to files
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//public variables across all classes - keeps track of player lives
int textFileLives;
int player1lives;
int player2lives;
char fileName[] = "stats.txt"; //name of file
//set collisions to true so that hearts are draw
bool collision = true;
//difficulty
int difficulty = 1;


Nxs13uMain::Nxs13uMain()
//passing values to the superclass constructor
: BaseEngine( 3 ) //max number of moving objects you can draw
, gameState(startPage) //initial page is start page
{
	// Variables
	ifstream file;
	string stream;
	int lines[] = { 0, 0, 0, 0, 0, 0 }; //[0] for first line, [1] for second line etc

	// Open or create a new text file

	file.open(fileName);

	// Get data from file
	for (int i = 0; i <= 5; i++){
		if (!file.eof()){
			getline(file, stream); // Get line from the file and assign to tempData
			lines[i] = atoi(stream.c_str());
		}
	}

	textFileLives = lines[1];
	player1lives = lines[1];
	player2lives = lines[1];
	file.close();
}

Nxs13uMain::~Nxs13uMain()
{
}

//drawing background
void Nxs13uMain::SetupBackgroundBuffer()
{

	switch (gameState)
	{
		case gameMode: //CASE OF GAME MODE
		{
			//white background
			FillBackground(0xFFFFFF);
			//find out width
			for (int width = 0; width < GetScreenWidth(); width++)
			{
				//find out height
				for (int height = 0; height < this->GetScreenHeight(); height++)
				{
					if (width > 600)
					{
						SetBackgroundPixel(width, height, 0xF5D9D9); //set up side bar background colour
					}

					if (height < 50 || height > 550) 
					{
						SetBackgroundPixel(width, height, 0xF5D9D9); //set up player bar background colours
					}
				}
			}

			//so the dimensions of the player field is (0,50), (600,50), (0,550), (600,550)

			//now background the player field with vertical lines
			for (int width = 0; width < 601; width += 50) //every 50 pixels of player field
			{
				for (int height = 50; height < 550; height++) //draw the line
				{
					SetBackgroundPixel(width, height, 0xBDBDBD);
				}
			}

			//now background the player field with horizontal lines
			for (int width = 0; width < 600; width++) //draw the line
			{
				for (int height = 50; height < 551; height += 50) //every 50 pixels of player field
				{
					SetBackgroundPixel(width, height, 0xBDBDBD);
				}
			}
		} break;

		case startPage: 	// CASE OF START PAGE
		{		
			// Tell it to draw tiles from x1,y1 to x2,y2 in tile array,
			// to the background of this screen
			tiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 20, 30);

			// Draw images loaded from file - player controls
			ImageData player1Controls, player2Controls;
			// Load the image file into an image object - at the normal size
			player1Controls.LoadImage("Player1Ctrl.png");
			player1Controls.RenderImageWithMask(this->GetBackground(), 0, 0, 170, 270, player1Controls.GetWidth(), player1Controls.GetHeight());
			player2Controls.LoadImage("Player2Ctrl.png");
			player2Controls.RenderImageWithMask(this->GetBackground(), 0, 0, 480, 270, player2Controls.GetWidth(), player2Controls.GetHeight());
		} break;

		case gameOver: 	// CASE OF GAME OVER
		{
			// Tell it to draw tiles from x1,y1 to x2,y2 in tile array,
			// to the background of this screen
			tiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 20, 30);
		} break;
	}
	
}


//draw text labels
void Nxs13uMain::DrawStrings()
{
	//font colours
	unsigned int fontColourBlack = 0x000000;
	unsigned int fontColourGreen = 0x009933;
	unsigned int fontColourBlue = 0x0000FF;
	unsigned int fontColourRed = 0xFF0000;

	// SWITCH
	switch (gameState)
	{
	case gameMode:
	{
		DrawScreenString(10, 15, "PLAYER 1 LIVES", fontColourBlue, GetFont("After the Goldrush.ttf", 20));
		DrawScreenString(10, 565, "PLAYER 2 LIVES", fontColourGreen, GetFont("After the Goldrush.ttf", 20));
		DrawScreenString(635, 100, "DODGE", fontColourBlack, GetFont("After the Goldrush.ttf", 30));
		DrawScreenString(615, 140, "THE RED", fontColourBlack, GetFont("After the Goldrush.ttf", 30));
		DrawScreenString(645, 180, "BALL", fontColourBlack, GetFont("After the Goldrush.ttf", 30));
		DrawScreenString(620, 300, "DIFFICULTY", fontColourBlack, GetFont("After the Goldrush.ttf", 20));
		
		if (difficulty == 1)
			DrawScreenString(650, 340, "1", fontColourRed, GetFont("After the Goldrush.ttf", 30));
		else 
			DrawScreenString(650, 340, "1", fontColourBlack, GetFont("After the Goldrush.ttf", 30));

		if (difficulty == 2)
			DrawScreenString(680, 340, "2", fontColourRed, GetFont("After the Goldrush.ttf", 30));
		else
			DrawScreenString(680, 340, "2", fontColourBlack, GetFont("After the Goldrush.ttf", 30));

		if (difficulty == 3)
			DrawScreenString(720, 340, "3", fontColourRed, GetFont("After the Goldrush.ttf", 30));
		else
			DrawScreenString(720, 340, "3", fontColourBlack, GetFont("After the Goldrush.ttf", 30));

	} break;

	case startPage:
	{
		DrawScreenString(185, 80, "DODGER", fontColourBlack, NULL);
		DrawScreenString(120, 230, "PLAYER 1", fontColourBlue, GetFont("After the Goldrush.ttf", 35));
		DrawScreenString(430, 230, "PLAYER 2", fontColourGreen, GetFont("After the Goldrush.ttf", 35));
		DrawScreenString(80, 450, "CHANGE DIFFICULTY USING NUMBER KEYS 1-3", fontColourBlack, GetFont("After the Goldrush.ttf", 20));
		DrawScreenString(95, 520, "PRESS SPACE TO BEGIN", fontColourBlack, GetFont("After the Goldrush.ttf", 35));
	} break;

	case gameOver:
	{
		DrawScreenString(85, 50, "GAME OVER", fontColourBlack, NULL);
		DrawScreenString(110, 490, "PRESS SPACE TO RE-PLAY", fontColourBlack, GetFont("After the Goldrush.ttf", 30));
		DrawScreenString(230, 540, "OR ESC TO EXIT", fontColourBlack, GetFont("After the Goldrush.ttf", 30));

		if (player1lives == 0)
		{
			DrawScreenString(210, 250, "PLAYER 2", fontColourGreen, GetFont("After the Goldrush.ttf", 50));
		}
		else if (player2lives == 0)
		{
			DrawScreenString(210, 250, "PLAYER 1", fontColourBlue, GetFont("After the Goldrush.ttf", 50));
		}
		DrawScreenString(275, 350, "WIN", fontColourBlack, NULL);
	} break;
	}
}


//Initialising Objects
int Nxs13uMain::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	//SWITCH
	switch (gameState)
	{
	case gameMode:
	{
		//COLOUR 0 = red, 1 = blue, 2 = green

		// Create an array one element larger than the number of objects that you want.
		CreateObjectArray(3);

		//Create objects and store in array
		StoreObjectInArray( 0, new Nxs13uPlayerOneObject(this, 40/*Radius*/, 1/*Colour*/, 80, 125 /*co-ordinates*/) ); //player 1
		StoreObjectInArray( 1, new Nxs13uPlayerTwoObject(this, 40/*Radius*/, 2/*Colour*/, 515, 470/*co-ordinates*/) ); //player 2
		StoreObjectInArray( 2, new Nxs13uEnemyObject(this, 2/*Id*/, 35/*Radius*/, 0/*Colour*/, 300, 300 /*co-ordinates*/, 1, 1 /*speed*/) ); //enemy
		StoreObjectInArray( 3, NULL);
		return 0;
	} break;

	case startPage:
	{
		CreateObjectArray(1);
		StoreObjectInArray(0, new Nxs13uEnemyObject(this, 3/*Id*/, 35/*Size*/, 0/*Colour*/, 300, 300 /*co-ordinates*/, 1, 1 /*speed*/) ); //enemy
		StoreObjectInArray(1, NULL);
		return 0;
	} break;

	case gameOver:
		return 0;
		break;
	}
	
}

//Constantly Looping
void Nxs13uMain::GameAction()
{
	// Draw images loaded from file - player lives
	ImageData lives;

	// If too early to act then do nothing
	if (!IsTimeToAct()) // No sleep, will just keep polling constantly
		return;

	// Don't act for another 1 tick
	SetTimeToAct(1); 
	
	// SWITCH
	switch (gameState)
	{
	case gameMode:
	{
		//only redraw hearts if there was a collision (otherwise everything is constantly redrawn and slows the program down)
		if (collision)
		{
			// Load Images
			lives.LoadImage("LifeHeart.png");

			//Redraw background
			SetupBackgroundBuffer();

			//draw lives for player 1
			for (int player1livesDrawn = 0; player1livesDrawn < player1lives; player1livesDrawn++)
			{
				lives.RenderImageWithMask(this->GetBackground(), 0, 0, 260 + (player1livesDrawn * 55), 5, lives.GetWidth(), lives.GetHeight());
			}

			//draw lives for player 2
			for (int player2livesDrawn = 0; player2livesDrawn < player2lives; player2livesDrawn++)
			{
				lives.RenderImageWithMask(this->GetBackground(), 0, 0, 260 + (player2livesDrawn * 55), 555, lives.GetWidth(), lives.GetHeight());
			}

			collision = false;
		}

		//loop through required functions
		Redraw(true);
		UpdateAllObjects(GetModifiedTime());

		//check if game is over
		if (player1lives == 0 || player2lives == 0)
		{
			gameState = gameOver;
			// Force redraw of background
			SetupBackgroundBuffer();
			InitialiseObjects();
			UseFile();
		}
	} break;

	case startPage:
	{
		//loop through required functions
		Redraw(true);
		UpdateAllObjects(GetModifiedTime());
	}	break;

	case gameOver:
		break;
	}
}

//exit game
void Nxs13uMain::KeyDown(int iKeyCode)
{
	if (iKeyCode == SDLK_ESCAPE)
		SetExitWithCode(0);
	else if (iKeyCode == SDLK_1)
		difficulty = 1;
	else if (iKeyCode == SDLK_2)
		difficulty = 2;
	else if (iKeyCode == SDLK_3)
		difficulty = 3;
	else if (iKeyCode == SDLK_SPACE)
	{
		// SWITCH
		switch (gameState)
		{
		case gameMode:
			break;

		case startPage:
		{
			// Go to state gameMode
			gameState = gameMode;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			//Redraw(true);
			InitialiseObjects();
		}
		break;

		case gameOver:
			// Go to state startPage
			player1lives = textFileLives;
			player2lives = textFileLives;
			gameState = startPage;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			//Redraw(true);
			InitialiseObjects();
			//set variables in case player wishes to start again
			collision = true;
			difficulty = 1;
			break;
		}
	}
}

void Nxs13uMain::UndrawObjects()
{
		BaseEngine::UndrawObjects();
}

void Nxs13uMain::DrawObjects()
{
		BaseEngine::DrawObjects();
}


void Nxs13uMain::UseFile()
{
	
	fstream file;
	
	//open file
	file.open(fileName, std::ios::out);

	//check if file opened
	if (!file)
	{
		printf("file could not open\n");
	} else 
	{
			//write to file
			file << "Number of Lives:\n";
			file << textFileLives;
			file << "\nPlayer 1 Final Lives:\n";
			file << player1lives;
			file << "\nPlayer 2 Final Lives:\n";
			file << player2lives;

			//close file once we have finished
			file.close();
		
	}
	
}