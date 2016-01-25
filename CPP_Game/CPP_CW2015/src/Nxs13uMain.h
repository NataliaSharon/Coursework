//created Base Engine sub class
#pragma once
#include "header.h"
#include "BaseEngine.h"

#include "TileManager.h"
#include "Nxs13uTileManager.h"

class Nxs13uMain :
	public BaseEngine
{
protected:
	Nxs13uTileManager tiles;

public:
	Nxs13uMain();
	~Nxs13uMain();


	//draw background
	virtual void SetupBackgroundBuffer();

	//draw strings to screen
	virtual void DrawStrings();

	//create objects
	virtual int InitialiseObjects();

	//game play
	virtual void GameAction();

	//is Key Pressed
	void KeyDown(int iKeyCode);

	//undraw and redraw objects
	void UndrawObjects();
	void DrawObjects();

	//Get data from file at beginning, and write to file once game is over
	void UseFile();

	// Get a reference to the current tile manager
	Nxs13uTileManager& GetTileManager() { return tiles; }

public:
	// State number
	enum State { gameMode, startPage, gameOver };

private:
	State gameState;

};

extern int player1lives;
extern int player2lives;
extern bool collision;
extern int difficulty;

