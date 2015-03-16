#include "PauseMenu.h"


PauseMenu::PauseMenu()
{
	pauseMenuSprite = CreateSprite("./images/pause_screen.png", 1024, 768, false);

	char * error = NULL;
	dm.Select("Highscores.db", "PAUSE_MENU", "*", "", "", error);
	
	activeMenuItemColour = SColour(10,255,86,255);
	inactiveMenuItemColour = SColour(155,209,156,255);

	activePauseMenuOption = PAUSE_OPTION_RESUME;
}


PauseMenu::~PauseMenu()
{
}

GAMESTATES PauseMenu::Update()
{
	if ( IsKeyDown(SDLK_r) )
	{
		char * error = NULL;
		dm.Select("Highscores.db", "PAUSE_MENU", "*", "", "", error);
	}
	if ( IsKeyDown(SDLK_LEFT) )
	{
		if ( activePauseMenuOption == PAUSE_OPTION_QUIT )
		{
			activePauseMenuOption = PAUSE_OPTION_RESUME;
		}
	}
	if ( IsKeyDown(SDLK_RIGHT) )
	{
		if ( activePauseMenuOption == PAUSE_OPTION_RESUME )
		{
			activePauseMenuOption = PAUSE_OPTION_QUIT;
		}
	}
	if ( IsKeyDown(SDLK_RETURN) )
	{
		if ( activePauseMenuOption == PAUSE_OPTION_RESUME )
		{
			//resume game
			return GAMEPLAY;
		}
		if ( activePauseMenuOption == PAUSE_OPTION_QUIT )
		{
			//load menu
			return RESET_TO_MENU;
		}
	}
	return PAUSED;
}

void PauseMenu::Draw()
{
	MoveSprite(pauseMenuSprite, 0.f, (float)SCREEN_HEIGHT);
	DrawSprite(pauseMenuSprite);
	SetFont( INVADERS_FONT );

	if ( dm.Rows() > 0 )
	{		 
		if ( activePauseMenuOption == PAUSE_OPTION_RESUME ) 
		{
			DrawString("MAIN MENU", dm.GetValueInt(0, "QUIT_X"), dm.GetValueInt(0, "QUIT_Y"), 0.5f, inactiveMenuItemColour);
			DrawString("RETURN", dm.GetValueInt(0, "RESUME_X"), dm.GetValueInt(0, "RESUME_Y"), 0.5f, activeMenuItemColour);
		}
		if ( activePauseMenuOption == PAUSE_OPTION_QUIT ) 
		{
			DrawString("MAIN MENU", dm.GetValueInt(0, "QUIT_X"), dm.GetValueInt(0, "QUIT_Y"), 0.5f, activeMenuItemColour);
			DrawString("RETURN", dm.GetValueInt(0, "RESUME_X"), dm.GetValueInt(0, "RESUME_Y"), 0.5f, inactiveMenuItemColour);
		}
	}
}