#include "DisplayableObject.h"

class Nxs13uMain;

class Nxs13uPlayerTwoObject :
	public DisplayableObject
{
public:
	Nxs13uPlayerTwoObject(Nxs13uMain* pEngine, int radius, int colour, int x, int y);
	virtual ~Nxs13uPlayerTwoObject(void);
	void Draw();
	void DoUpdate(int currentTime);

private:
	/** Pointer to the main engine object */
	Nxs13uMain* m_pMainEngine;

	// Size of thing to draw
	int radius;

	// Colour index to draw with
	int colour;

	//co-rdinates
	int x;
	int y;

};
