//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// CONSTS.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "AIE.h"
#include <list>
#include <memory> //shared_ptr (for whole project)
#include <string>

//uncomment below to use file system for high scores rather than database CPP
//#define USE_FILE_HIGH_SCORES

//uncomment below to use database system for high scores GDD
#define USE_DB_HIGH_SCORES


#define M_PI 3.14159265358979323846f

using namespace std;

//FIXED UPDATE
const float UPDATE_INTERVAL =  (1000.f / 30.f) / 1000;

//GAME PLAY MECHANICS
const int LIVES = 3;
const int MAX_LIVES = 9;
const int MAX_WAVES = 10;
const float MAX_COMBO_TIME = 0.3f;

//SCREEN RES
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

//BACKGROUND TILES
const int BG_TILE_WIDTH = 512;
const int BG_TILE_HEIGHT = 512;
const int BG_TILE_COLS = 3;
const int BG_TILE_ROWS = 3;
const float BG_Y_OFFSET_SPEED = 0.3f;
const float BG_Y_OFFSET2_SPEED = 0.6f;
const int BG_Y_OFFSET3_SPEED = 20;

//PLAYER CONSTS
const int PLAYER_WIDTH = 47;
const int PLAYER_HEIGHT = 62;

//ENEMY CONSTS
//const float ENEMYSINE_WIDTH = 84 / 1.6f;
const int ENEMYSINE_WIDTH = 52;
const int ENEMYSINE_HEIGHT = 58;
const float ENEMY_MAXSPEED = 6.0f;
const float ENEMY1_FORCE_MULTIPLIER = 0.0003f;
const float ENEMY2_FORCE_MULTIPLIER = 0.000001f;
const float ENEMY_FORCE_MOVE_AWAY = 1.f;
const int DEATH_ANIMATION_FRAMES = 7;
const float DEATH_ANIMATION_SPEED = 5.f;			//animate DEATH_ANIMATION_SPEED times per second
const float ENEMY2_SHOOT_POLL_INTERVAL = 0.1f;		//every 0.1 seconds, run the shoot chance equation
const float ENEMY2_SHOOT_CHANCE = 0.025f;			//2.5% chance of shot each poll

//BACKGROUND COLOUR
const SColour BG_COLOUR = SColour( 0x00, 0x00, 0x00, 0xFF );

////PHYSICS
//const float THRUST_POWER = 2.5f;
//const float ROTATION_SPEED = 400.f;
//const float MAX_SPEED = 250.f;
//const float FRICTION = 0.996f; //1=no friction, 0=max friction

//POWERUP modifiers
const int MAX_POWER_UPS = 6;
const float BULLET_RELOAD_DECREASER = 0.75f; 
const float POWERUP_SINE_SPEED = 0.1f;
const float POWERUP_SINE_DEPTH = 7.5f;
const float POWERUP_Y_SPEED = -2.5f;

//BULLETS
const float MAX_BULLET_RELOAD_TIME = 0.35f;
const int BULLET_WIDTH = 54;
const int BULLET_HEIGHT = 9;
const float PLAYER_BULLET_VELOCITY = 1000.f;
const int MAX_BULLETS = 20;
const float ENEMY_BULLET_VELOCITY = 10.f;




//GAMESTATES
enum GAMESTATES
{
	MAIN_MENU,
	GAMEPLAY,
	PAUSED,
	RESET_TO_MENU,
	SHUTDOWN
};

enum CONTROL_SCHEME_DEFINIITIONS
{
	KEYBOARD_CONTROL,
	KEYBOARD_AND_MOUSE_CONTROL,
	CONTROL_SCHEME_DEFINIITIONS_END
};

//POWER UP TYPES
enum POWER_UP_TYPES
{
	POWER_UP_WING_GUNS,
	POWER_UP_BACK_GUN,
	POWER_UP_SPEED_UP,
	POWER_UP_SHIELD,
	POWER_UP_FIRE_RATE
};

//SPAWN POINTS (needs to have enemy taken out of the name)
enum ENEMY_SPAWN_POINTS { 
	TOP, 
	LEFT, 
	RIGHT,
	BOTTOM,
	TOP_OR_BOTTOM,
	LEFT_OR_RIGHT,
	RANDOM_OFF_SCREEN,
	RANDOM_ON_SCREEN
};

//POWER UP ANIMATIONS
#define ANIM_1_POWER_UP_WING_GUNS "./images/PNG/Power-ups/powerupBlue_bolt.png"
#define ANIM_2_POWER_UP_WING_GUNS "./images/PNG/Power-ups/powerupBlue.png"
#define ANIM_1_POWER_UP_BACK_GUN "./images/PNG/Power-ups/powerupGreen_bolt.png"
#define ANIM_2_POWER_UP_BACK_GUN "./images/PNG/Power-ups/powerupGreen.png"
#define ANIM_1_POWER_UP_SPEED "./images/PNG/Power-ups/powerupRed_star.png"
#define ANIM_2_POWER_UP_SPEED "./images/PNG/Power-ups/powerupRed.png"
#define ANIM_1_POWER_FIRE_RATE "./images/PNG/Power-ups/powerupGreen_bolt.png"
#define ANIM_2_POWER_FIRE_RATE "./images/PNG/Power-ups/powerupBlue_bolt.png"
#define ANIM_1_POWER_UP_SHIELD "./images/PNG/Power-ups/shield_gold.png"
#define ANIM_2_POWER_UP_SHIELD "./images/PNG/Power-ups/shield_silver.png"
const float POWER_UP_ANIMATION_SPEED = 0.15f;//hold each animation for 0.1 seconds

const int POWER_UP_WIDTH = 34;
const int POWER_UP_HEIGHT = 33;



//TIMING SETTINGS
const float TIME_BETWEEN_WAVES = 3.5f;
const float TIME_BETWEEN_PLAYER_RESPAWN = 3.f;
const float STARTING_ENEMY_SPAWN_SPEED = 1.0f;
const float ENEMY_SPAWN_SPEED_MULTIPLYER = 0.9f;

//FONTS
#define INVADERS_FONT "./fonts/feisarv5.fnt"
//#define NUMBERS_FONT "./fonts/digitalism.fnt"
#define NUMBERS_FONT "./fonts/polix_mono.fnt"



//HUD
struct HudInfo
{
	int waveNum;
	int lives;
	int fireRate;
	bool waveEnd;
	bool levelComplete;
	int currentCombo;
	bool alive;
	int fps;
	int score;
	int highScore;
	float powerUpPickupX;
	float powerUpPickupY;
	float plyrX;
	float plyrY;
	float timeSincePlayerDeath;
	float accuracy;
};


//HUD CONSTS
//const int PLAYER_HUD_WIDTH = 33;
//const int PLAYER_HUD_HEIGHT = 26;
//const int WAVES_HUD_WIDTH = 34;
//const int WAVES_HUD_HEIGHT = 33;
//const int GENERIC_MARGIN = 20;
//const int HUD_LEFT_MARGIN = 50;
//const int HUD_WAVE_MARGIN = 50;
//const int HUD_WAVE_NUM_MARGIN = 400;
//const int HUD_COMPLETE_MARGIN = 450;
//const int HUD_MARGINS = 100;
//const int HUD_BOTTOM_ROW = 60;
//const int HUD_RIGHT_MARGIN = 150;
//const int LEVEL_COMPLETE_MARGIN = 50;
//const int TEXT_HEIGHT = 25;
//const float CHAR_ENTRY_TIMER = 0.3f;

////MAIN MENU POSITIONS
//const int HIGH_SCORES_Y_STARTING_POINT = SCREEN_HEIGHT - 200;
//const int HIGH_SCORES_X_STARTING_POINT = 600;
//const int HIGH_SCORES_X_COLUMN_SPACING = 75;
//const int HIGH_SCORES_Y_ROW_SPACING = 26;
//const float HIGH_SCORES_FONT_SIZE = 1.0f;


//SOUND CONSTANTS
#define SOUND_PLAYER_LASER "./sound/PlayerLaser2.mp3"
#define SOUND_PLAYER_DEATH "./sound/PlayerExplode.mp3"
#define SOUND_PLAYER_THRUST "./sound/ThrusterLoop5.wav" //this one has the adjusted pitch
#define SOUND_PLAYER_THRUST2 "./sound/ThrusterLoop6.wav"//this one adjusts volume based on velocity
#define SOUND_ENEMY_LASER "./sound/EnemyLaser.mp3"
#define SOUND_ENEMY_DEATH "./sound/EnemyExplode.mp3"
#define SOUND_WAVE_COMPLETE "./sound/WaveComplete.mp3"
#define SOUND_CHANGE_SELECTION "./sound/ChangeSelection.mp3"
#define SOUND_CONFIRM_SELECTION "./sound/ConfirmSelection.mp3"
#define SOUND_WAVE_AMBIENCE "./sound/SpaceAmbience.mp3"
#define SOUND_POWERUP "./sound/powerup.wav"



////ENGINE SOUNDS
//const float ENGINE_SOUND_MULTIPLYER = 300.f;
//const float ENGINE_SOUND_VELOCITY_FLOOR = 3.f;
//const float ENGINE_THRUST2_MAX_VOL = 0.1f;
//const float ENGINE_THRUST2_MIN_VOL = 0.0f;

enum MENU_SELECTION
{
	START_GAME,
	CONTROL_SCHEME,
	HIGH_SCORES,
	QUIT,
	CREDITS,
	MENU_SELECTION_END
};

