//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// Player.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "Vector.h"
#include "bullet.h"
#include <list>
#include "CONSTS.h"
#include "bass.h"
#include "DatabaseManager.h"
#include "SDL2/SDL.h"


enum PLAYER_MOVEMENT_STATE
{
	PLAYER_THRUSTING,
	PLAYER_NEUTRAL
};


//PLAYER CLASS
class Player
{
public:
	////ACCESSOR METHODS
	//static float GetPlayerWidth();
	//static float GetPlayerHeight();

	float X();
	float Y();

	float* XPtr();
	float* YPtr();

	//check for player movement
	//move x of player based on keydown but do not go outside of boundaries
	void UpdatePlayer();
	void UpdateBullets();
	void Draw();

	//Get Number of Player SPARE Lives
	int Lives();
	int FireRate();
	void Respawn();
	int Combo();		//get the current combo (0 if none)

	void AddPoints( const unsigned int& points);
	int Points();

	//PLAYER MOVEMENT KEYS
	unsigned int moveLeftKey;
	unsigned int moveRightKey;
	void SetMovementKeys( unsigned int moveLeft, unsigned int moveRight );

	//Add the powerup effects to the player
	//returns the number of points received from power up
	int AddPowerUp(POWER_UP_TYPES type); 

	//Player(EnemyList& enemies);
	Player();
	~Player();

	void Die();
	bool Alive();

	void SetControlScheme(CONTROL_SCHEME_DEFINIITIONS controlScheme);

	//turn engine sound loop on/off
	void TurnOnEngine();
	void TurnOffEngine();

	void ReloadData();						//reload player database values

	void IncrementHitCounter();				//used for calculating accuracy
	void ResetAccuracyStats();				//reset each wave
	float Accuracy();

	void ApplyFriction();					//needs to be called on FixedUpdate

	Bullet bullets[MAX_BULLETS];

private:
	float GetFireRate();
	PLAYER_MOVEMENT_STATE movementState;
	void SetThrust(Vector2 thrust);
	void InitSprites();
	void SetGunPos();
	void AdjustEnginePitch();
	//bool CheckCollision();
	void CheckPlayerBounds();
	void Accellerate(Vector2& accel);
	Bullet& GetInactiveBullet();
	void Shoot();
	float GetPlayerStartX();
	float GetPlayerStartY();
	int GetLeftZoneEdge();
	int GetRightZoneEdge();
		
	void HandleUserInput();
	bool AnimateDeath();			//return true on complete
	void GameOver();
	void RotateShipAndWeapons();


	//player position and physics
	Vector2 pos;
	Vector2 gunPos;
	Vector2 dir;
	Vector2 thrust;
	Vector2 velocity;
	const Vector2 left;
	const Vector2 right;
	const Vector2 up;
	const Vector2 down;
	const Vector2 neutral;

	//game rules
	int lives;						//decremented each time the player collides with an enemy or bullet
	bool alive;						//set to false immediately after impact to kick off death animation. 
	float currentReloadBulletTime;	//time since last Shoot command
	float timeSinceDeath;
	float timeSinceLastKill;		//used for calculating combos
	int combo;						//0 after timeSinceLastKill expires.
	unsigned int points;			//player points
	
	//Accuracy variables
	int hitCounter;
	int shotsFired;

	//game objects
	//	list<Enemy1*> enemies;

	

	CONTROL_SCHEME_DEFINIITIONS controlScheme;


	//SPRITES
	SDL_Texture* sprite;
	SDL_Texture* deathAnimations[7];
	SDL_Texture* currentSprite;
	//unsigned int hudLives[MAX_LIVES]; //5 is max num of lives
	SDL_Texture* gun;

	//SOUNDS
	vector<HSTREAM> comboSounds;
	HSTREAM soundShot;
	HSTREAM soundDeath;
	HSTREAM soundThrust;
	HSTREAM soundThrust2;
	HSTREAM soundPowerup;


	int mouseX;
	int mouseY;
	Vector2 mouseVec;

	DatabaseManager dm;
	bool tableLoaded;


	//Power Up Modifiers
	//float bulletReloadTime; 

	int powerUpFireRateMulti;


};
