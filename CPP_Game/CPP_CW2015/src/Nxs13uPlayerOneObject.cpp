#include "header.h"
#include "Nxs13uPlayerOneObject.h"
#include "Nxs13uMain.h"



Nxs13uPlayerOneObject::Nxs13uPlayerOneObject(Nxs13uMain* pEngine, int radius, int colour, int x, int y)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
	, radius(radius)
	, colour(colour)
	, x(x)
	, y(y)
{

	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = x;
	m_iCurrentScreenY = m_iPreviousScreenY = y;

	// And make it visible
	SetVisible(true);
}

// Destructor 
Nxs13uPlayerOneObject::~Nxs13uPlayerOneObject(void)
{
}


void Nxs13uPlayerOneObject::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	//set colours
	unsigned int colourCode = 0x000000;
	switch (colour)
	{
	case (0) :
		colourCode = 0xFF0000;
		break;

	case(1) :
		colourCode = 0x0000FF;
		break;

	case(2) :
		colourCode = 0x009933;
		break;
	}

	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - radius,
		m_iCurrentScreenY - radius,
		m_iCurrentScreenX + radius,
		m_iCurrentScreenY + radius,
		colourCode);

	// This tells the system where to 'undraw' the object from
	StoreLastScreenPositionForUndraw();

}

void Nxs13uPlayerOneObject::DoUpdate(int currentTime)
{

	// Change position if player presses a key 

	if (GetEngine()->IsKeyPressed(SDLK_w)) //player 1 up
	{
		m_iCurrentScreenY -= 2;
	}
	if (GetEngine()->IsKeyPressed(SDLK_s)) //player 1 down
	{
		m_iCurrentScreenY += 2;
	}
	if (GetEngine()->IsKeyPressed(SDLK_a)) //player  1 left
	{
		m_iCurrentScreenX -= 2;
	}
	if (GetEngine()->IsKeyPressed(SDLK_d)) //player 1 right
	{
		m_iCurrentScreenX += 2;
	}

	//keep the objects in the playing field 
	//so the dimensions of the player field is (0,50), (600,50), (0,550), (600,550)
	int fieldXmin = 0;
	int fieldXmax = 600;
	int fieldYmin = 50;
	int fieldYmax = 550;

	if ((m_iCurrentScreenX) < fieldXmin + radius)
		m_iCurrentScreenX = fieldXmin + radius ;
	if (m_iCurrentScreenX > fieldXmax - radius)
		m_iCurrentScreenX = fieldXmax - radius;
	if (m_iCurrentScreenY < fieldYmin + radius)
		m_iCurrentScreenY = fieldYmin + radius;
	if (m_iCurrentScreenY > fieldYmax - radius)
		m_iCurrentScreenY = fieldYmax - radius;

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}
