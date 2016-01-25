#include "header.h"
#include "Nxs13uTileManager.h"


Nxs13uTileManager::Nxs13uTileManager()
	: TileManager(50, 50) //size of tile
{
}


Nxs13uTileManager::~Nxs13uTileManager()
{
}

void Nxs13uTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	//draws tiles for the home page
		pEngine->DrawRectangle(
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + GetTileWidth(),
		iStartPositionScreenY + GetTileHeight(),
		pEngine->GetColour(0xF5D9D9),
		pSurface);
	
}