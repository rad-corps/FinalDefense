#pragma once

#include "CONSTS.H"
#include "DatabaseManager.h"
#include "SDL2/SDL.h"

enum PAUSE_MENU_OPTIONS
{
	PAUSE_OPTION_RESUME,
	PAUSE_OPTION_QUIT
};

class PauseMenu
{
public:
	PauseMenu();
	~PauseMenu();

	GAMESTATES Update();
	void Draw();

private:
	SDL_Texture* pauseMenuSprite;
	DatabaseManager dm;
	PAUSE_MENU_OPTIONS activePauseMenuOption;

	SColour activeMenuItemColour;
	SColour inactiveMenuItemColour;
	
};

