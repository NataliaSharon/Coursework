#pragma once

#include "TileManager.h"

class Nxs13uTileManager :
	public TileManager
{
public:
	Nxs13uTileManager();
	~Nxs13uTileManager();

	// Draw a tile at a location on the screen determined by the tile
	// position and the base X and Y co-ordinates
	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;
};

