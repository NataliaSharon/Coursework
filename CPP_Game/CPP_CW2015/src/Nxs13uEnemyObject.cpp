#include "header.h"
#include "Nxs13uEnemyObject.h"
#include "Nxs13uMain.h"

Nxs13uEnemyObject::Nxs13uEnemyObject(Nxs13uMain* pEngine, int id, int radius, int colour, int x, int y, int speedX, int speedY)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
	, id(id)
	, radius(radius)
	, colour(colour)
	, x(x)
	, y(y)
	, speedX(speedX)
	, speedY(speedY)
{

	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = x;
	m_iCurrentScreenY = m_iPreviousScreenY = y;

	// And make it visible
	SetVisible(true);
}

// Destructor 
Nxs13uEnemyObject::~Nxs13uEnemyObject(void)
{
}


void Nxs13uEnemyObject::Draw()
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

void Nxs13uEnemyObject::DoUpdate(int currentTime)
{
	//keep the objects in the playing field 
	//so the dimensions of the player field is (0,50), (600,50), (0,550), (600,550)
	int fieldXmin = 0;
	int fieldXmax = 600;
	int fieldYmin = 50;
	int fieldYmax = 550;

	if (id == 3){ //for start page, enemy must be able to travel anywhere
		fieldXmin = 0;
		fieldXmax = GetEngine()->GetScreenWidth();
		fieldYmin = 0;
		fieldYmax = GetEngine()->GetScreenHeight();
	}

	// Alter position for speed - this makes the ball appear to vibrate 
	// remember that speed is basically pixels travelled per tick
	m_iCurrentScreenX += (speedX * rand() % (difficulty + 1));
	m_iCurrentScreenY += (speedY * rand() % (difficulty + 1));

	// Check for bounce off the edge
	if (m_iCurrentScreenX < fieldXmin + radius)
	{
		m_iCurrentScreenX = fieldXmin + radius;
		if (speedX < 0)
			speedX = -speedX;
	}
	if (m_iCurrentScreenX > fieldXmax - radius)
	{
		m_iCurrentScreenX = fieldXmax - radius;
		if (speedX > 0)
			speedX = -speedX;
	}
	if (m_iCurrentScreenY < fieldYmin + radius)
	{
		m_iCurrentScreenY = fieldYmin + radius;
		if (speedY < 0)
			speedY = -speedY;
	}
	if (m_iCurrentScreenY > fieldYmax - radius)
	{
		m_iCurrentScreenY = fieldYmax - radius;
		if (speedY > 0)
			speedY = -speedY;
	}

	// Set current position 
	m_iCurrentScreenX = (int)(m_iCurrentScreenX + speedX);
	m_iCurrentScreenY = (int)(m_iCurrentScreenY + speedY);

	//dynamic cast
	DisplayableObject* playerObject;

	//COLLISIONS
	if (id == 2){ //FOR GAME MODE ENEMY (not start-up page enemy)
		for (int objectId = 0; (playerObject = m_pMainEngine->GetDisplayableObject(objectId)) != NULL; objectId++)
		{
			if (playerObject == this) // This is us, skip it
				continue;
	
			//get the difference between the player and the enemy
			int playerSize = 40;
			int xDifference = playerObject->GetXCentre() - m_iCurrentScreenX;
			int yDifference = playerObject->GetYCentre() - m_iCurrentScreenY;

			// Pythagorus' theorum, if the distance is smaller than the size (radius size of both objects), then it is a collission
			if (((xDifference*xDifference) + (yDifference*yDifference)) < ((playerSize + radius)*(playerSize + radius)))
			{

				//move 70 pixels away from user and go in opposite direction (prevents re-collision)
				speedX = -speedX;
				speedY = -speedY;

				if (speedX < 0 || m_iCurrentScreenX > 530)
					m_iCurrentScreenX = m_iCurrentScreenX - 70;
				else 
					m_iCurrentScreenX = m_iCurrentScreenX + 70;

				if (speedY < 0 || m_iCurrentScreenY > 480)
					m_iCurrentScreenY = m_iCurrentScreenY - 70;
				else
					m_iCurrentScreenY = m_iCurrentScreenY + 70;  

				collision = true;

				//check which player it collided with - lives are passed back to Nxs13uMain
				if (objectId == 0)
				player1lives--;
				else if (objectId == 1)
				player2lives--; 
				
			}
			// end of collissions 
		}
	}

	RedrawObjects();
}
