#include "DisplayableObject.h"

class Nxs13uMain;

class Nxs13uEnemyObject :
	public DisplayableObject
{
public:
	Nxs13uEnemyObject(Nxs13uMain* pEngine, int id, int radius, int colour, int x, int y, int speedX, int speedY);
	virtual ~Nxs13uEnemyObject(void);
	void Draw();
	void DoUpdate(int currentTime);

private:
	/** Pointer to the main engine object */
	Nxs13uMain* m_pMainEngine;

	// Unique id for object, passed to engine to identify it
	int id;

	// Size of thing to draw
	int radius;

	// Colour index to draw with
	int colour;

	//co-rdinates
	int x;
	int y;

	//speed
	int speedX;
	int speedY;
};

