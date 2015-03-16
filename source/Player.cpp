//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// Player.cpp
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#include "AIE.h"
#include "FrameworkHelpers.h"
#include "Player.h"
#include "CONSTS.H"
#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;

Player::Player()
	: thrust(0.f, 0.f), velocity(0.f, 0.f), pos(GetPlayerStartX(), GetPlayerStartY()), left(-1.f, 0.f), right(1.f, 0.f), up(0.f, 1.f), down(0.f, -1.f), neutral(0.f, 0.f)
{
//	bulletReloadTime = MAX_BULLET_RELOAD_TIME;

	tableLoaded = false;
	ReloadData();

	timeSinceLastKill = 0.0f;
	points = 0;
	combo = 0;

	currentReloadBulletTime = 0.0f;
	alive = true;
	lives = LIVES;

	soundDeath = BASS_StreamCreateFile(false,SOUND_PLAYER_DEATH,0,0,0);
	soundThrust = BASS_StreamCreateFile(false,SOUND_PLAYER_THRUST,0,0,BASS_SAMPLE_LOOP);
	soundThrust2 = BASS_StreamCreateFile(false,SOUND_PLAYER_THRUST2,0,0,BASS_SAMPLE_LOOP);
	
	
	soundShot = BASS_StreamCreateFile(false,SOUND_PLAYER_LASER,0,0,0);	
	soundPowerup = BASS_StreamCreateFile(false,SOUND_POWERUP,0,0,0);	

	ResetAccuracyStats();

	powerUpFireRateMulti = 0;

	comboSounds.push_back(BASS_StreamCreateFile(false, "./sound/Combo01.mp3",0,0,0));
	comboSounds.push_back(BASS_StreamCreateFile(false, "./sound/Combo02.mp3",0,0,0));
	comboSounds.push_back(BASS_StreamCreateFile(false, "./sound/Combo03.mp3",0,0,0));
	comboSounds.push_back(BASS_StreamCreateFile(false, "./sound/Combo04.mp3",0,0,0));
	comboSounds.push_back(BASS_StreamCreateFile(false, "./sound/Combo05.mp3",0,0,0));
	comboSounds.push_back(BASS_StreamCreateFile(false, "./sound/Combo06.mp3",0,0,0));
	comboSounds.push_back(BASS_StreamCreateFile(false, "./sound/Combo07.mp3",0,0,0));
	comboSounds.push_back(BASS_StreamCreateFile(false, "./sound/Combo08.mp3",0,0,0));
	comboSounds.push_back(BASS_StreamCreateFile(false, "./sound/Combo09.mp3",0,0,0));
	comboSounds.push_back(BASS_StreamCreateFile(false, "./sound/Combo10.mp3",0,0,0));

	for ( int i = 0; i < 10; ++i )
	{
		BASS_ChannelSetAttribute(comboSounds[i], BASS_ATTRIB_VOL, 0.1f);
	}
}

Player::~Player()
{
	//DestroySprite(sprite);
	TurnOffEngine();
}

void
Player::ReloadData()
{
	char * error = NULL;
	dm.Select("Highscores.db", "PLAYER", "*", "", "", error);
}

void Player::InitSprites()
{
	sprite = CreateSprite( "./images/PNG/playerShip1_blue.png", PLAYER_WIDTH, PLAYER_HEIGHT, true );
	currentSprite = sprite;

	for ( int i = 0; i < DEATH_ANIMATION_FRAMES; ++ i)
	{
		string fileName = "./images/explosion/frame";
		fileName += to_string(i+1);
		fileName += "x.png";
		deathAnimations[i] = CreateSprite( fileName.c_str(), 256, 256, true );
	}


	//create gun sprite
	gun = CreateSprite("./images/PNG/Parts/gun01.png", 33 / 2, 17 / 2, true );

	tableLoaded = true;
}

void Player::SetControlScheme(CONTROL_SCHEME_DEFINIITIONS controlScheme)
{
	this->controlScheme = controlScheme;
}

float Player::X(){ return pos.GetX(); }
float Player::Y(){ return pos.GetY(); }

float* Player::XPtr(){ return pos.XPtr(); }
float* Player::YPtr(){ return pos.YPtr(); }

float Player::GetPlayerStartX(){return SCREEN_WIDTH * 0.5f;}
float Player::GetPlayerStartY(){return SCREEN_HEIGHT * 0.5f;}
//float Player::GetPlayerWidth(){return 99.f;}
//float Player::GetPlayerHeight(){return 75.f;}
void Player::SetMovementKeys( unsigned int moveLeft, unsigned int moveRight ) { moveLeftKey = moveLeft; moveRightKey = moveRight; }
int Player::GetLeftZoneEdge(){ return PLAYER_WIDTH / 2; }
int Player::GetRightZoneEdge(){ return SCREEN_WIDTH - (PLAYER_WIDTH / 2); }

void Player::Accellerate(Vector2D& accel)
{
	velocity += accel;
}

void Player::ApplyFriction()
{
	velocity.SetLength(velocity.GetLength() * dm.GetValueFloat(0, "FRICTION") );
}

Bullet& Player::GetInactiveBullet()
{
	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		if (!bullets[i].Active())
		{
			return bullets[i];
		}
	}
	return bullets[0];
}

void
Player::CheckPlayerBounds()
{
	if ( pos.GetX() < (float)GetLeftZoneEdge() )
		pos.SetX((float)GetLeftZoneEdge());
	if ( pos.GetX() > (float)GetRightZoneEdge() )
		pos.SetX((float)GetRightZoneEdge());
	if (pos.GetY() > (float)SCREEN_HEIGHT)
		pos.SetY((float)SCREEN_HEIGHT);
	if (pos.GetY() < 0.f)
		pos.SetY(0.f);
}

//check collisions then move bullets
//FIXED UPDATE METHOD
void Player::UpdateBullets()
{
	currentReloadBulletTime += GetDeltaTime();
	for(int i = 0; i < MAX_BULLETS; i++)
	{    
		if  (bullets[i].Active() )
		{
			bullets[i].Update(GetDeltaTime());    
		}
	}
}

void Player::Shoot()
{
	//play sound
	BASS_ChannelPlay(soundShot, true);
	Vector2D gunDir, tempPos;
	GetSpriteAngleVector(gun, gunDir);
	tempPos = gunDir;
	tempPos.SetLength(40.f);
	GetInactiveBullet().InitialiseBullet(gunPos.GetX() + tempPos.GetX(), gunPos.GetY() + tempPos.GetY(), gunDir);
	currentReloadBulletTime = 0.0f;
	shotsFired++;
}

void 
Player::RotateShipAndWeapons()
{
	float rot  = dm.GetValueFloat(0, "ROTATION_SPEED");

	if ( movementState == PLAYER_MOVEMENT_STATE::PLAYER_THRUSTING ) 
	{
		float dirRadians = GetRadiansFromVector(dir);
		float targetRadians = GetRadiansFromVector(thrust);
		if ( dirRadians < 0 ) dirRadians += 2 * M_PI;
		if ( targetRadians < 0 ) targetRadians += 2 * M_PI;

		float cwDist;
		float acwDist;

		if ( dirRadians > targetRadians )
		{
			acwDist = (2 * M_PI) - dirRadians + targetRadians;
			cwDist = dirRadians - targetRadians;
		}
		else if ( dirRadians <= targetRadians )
		{
			acwDist = targetRadians - dirRadians;
			cwDist = (2 * M_PI) - targetRadians + dirRadians;
		}

		const float ROTATION_TOLLERANCE = 0.2f;

		//rotate either clockwise or anti clockwise. 
		if ( cwDist > acwDist ) //anticlockwisw
		{
			if ( (acwDist) > ROTATION_TOLLERANCE )
				RotateSprite(sprite, rot);
			else
				RotateSpriteToVector(sprite, thrust);
		}
		else 
		{
			if ( (cwDist) > ROTATION_TOLLERANCE )
				RotateSprite(sprite, -rot);
			else
				RotateSpriteToVector(sprite, thrust);
		}
	}

	GetMouseLocation(mouseX, mouseY);
	mouseVec = Vector2D((float)mouseX, -((float)mouseY - SCREEN_HEIGHT));
	Vector2D direction = mouseVec - pos;
	Vector2D shipDir = thrust;	
	direction.Normalise();	
	shipDir.Normalise();	
	RotateSpriteToVector(gun, direction);
}

void Player::SetThrust(Vector2D thrust)
{
	this->thrust += thrust;
	movementState = PLAYER_MOVEMENT_STATE::PLAYER_THRUSTING;
}

void Player::HandleUserInput()
{
	//populate direction
	GetSpriteAngleVector(sprite, dir);

	float rot  = dm.GetValueFloat(0, "ROTATION_SPEED");
	if  (controlScheme == CONTROL_SCHEME_DEFINIITIONS::KEYBOARD_CONTROL)
	{		
		//handle user input
		if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_LEFT) )
			thrust += dir.Rotate90(false);
		if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_RIGHT) )
			thrust += dir.Rotate90(true);
		if ( (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_LEFT_SHIFT) ) || IsKeyDown(KEY_A)) {
			RotateSprite(sprite, rot);
			RotateSprite(gun, rot);
		}
		if ( (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT_SHIFT) ) || IsKeyDown(KEY_D)) { 
			RotateSprite(sprite, -rot);
			RotateSprite(gun, -rot);
		}
		if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
			thrust -= dir;
		if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
			thrust += dir;
		if (IsKeyDown(KEY_Q))
			thrust += dir.Rotate90(false);
		if (IsKeyDown(KEY_E))
			thrust += dir.Rotate90(true);
		if (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))
			if  (currentReloadBulletTime > GetFireRate())//bullet	
				Shoot();
	}
	else if ( controlScheme == CONTROL_SCHEME_DEFINIITIONS::KEYBOARD_AND_MOUSE_CONTROL )
	{
		if (IsKeyDown(KEY_A))						
			SetThrust(left);
		if (IsKeyDown(KEY_D))
			SetThrust(right);
		if ( IsKeyDown(KEY_S))
			SetThrust(down);
		if (IsKeyDown(KEY_W))
			SetThrust(up);
		if ( GetMouseButtonDown(0)  )
			if  (currentReloadBulletTime > GetFireRate())//bullet	
				Shoot();

		if ( thrust == neutral )
			movementState = PLAYER_MOVEMENT_STATE::PLAYER_NEUTRAL;

		RotateShipAndWeapons();
	}
	
	//avoid divide by 0
	if ( thrust != neutral )
		thrust.SetLength(dm.GetValueFloat(0, "THRUST_POWER"));


	
	Accellerate(thrust); //this sets velocity
	ApplyFriction();

	if ( velocity.GetLength() > dm.GetValueFloat(0, "MAX_SPEED") ) 
		velocity.SetLength(dm.GetValueFloat(0, "MAX_SPEED"));

	AdjustEnginePitch();

	//Vector2D scaledVec = velocity * GetDeltaTime();
	//pos += scaledVec;
	pos += velocity;
}

void Player::AdjustEnginePitch()
{	
	float velocityFloor = dm.GetValueFloat(0, "ENGINE_SOUND_VELOCITY_FLOOR");
	float soundMulti = dm.GetValueFloat(0, "ENGINE_SOUND_MULTIPLIER");
	float maxSpeed = dm.GetValueFloat(0, "MAX_SPEED");
	float minVol = dm.GetValueFloat(0, "ENGINE_THRUST2_MIN_VOL");
	float maxVol = dm.GetValueFloat(0, "ENGINE_THRUST2_MAX_VOL");
	float currentVelocity = 0.0f;
	
	//we dont want to alter pitch lower than velocity floor
	if ( velocity.GetLength() < velocityFloor )
	{
		currentVelocity = velocityFloor;
	}
	else
	{
		currentVelocity = velocity.GetLength();
	}

	float pitchMultiplyer = currentVelocity * soundMulti;

		//cout << "soundMulti: " << soundMulti 
		//<< "\t currentVelocity: " << currentVelocity 
		//<< "\t velocity.GetLength(): " << velocity.GetLength()
		//<< "\t pitchMultiplyer: " << pitchMultiplyer << endl;

	BASS_ChannelSetAttribute(soundThrust2, BASS_ATTRIB_FREQ, pitchMultiplyer);

	float velocityMultiplyer = currentVelocity / maxSpeed;
	float lerp = Lerp(minVol, maxVol, velocityMultiplyer);
	BASS_ChannelSetAttribute(soundThrust, BASS_ATTRIB_VOL, lerp);
}

int Player::Lives()
{
	return lives;
}

int Player::FireRate()
{
	return powerUpFireRateMulti;
}

void Player::Die()
{
	if ( alive )
	{
		BASS_ChannelPlay(soundDeath, true);
		this->TurnOffEngine();
		--lives;
		alive = false;
		timeSinceDeath = 0.f;
		--powerUpFireRateMulti;
		//bulletReloadTime = MAX_BULLET_RELOAD_TIME;
		velocity.SetX(0.f);
		velocity.SetY(0.f);
	}
}

float Player::GetFireRate()
{
	float ret = MAX_BULLET_RELOAD_TIME;
	
	for (int i = 0; i < powerUpFireRateMulti; ++i )
	{
		ret *= BULLET_RELOAD_DECREASER;
	}	

	return ret;
}

void Player::SetGunPos()
{	
	//get normalised player direction
	Vector2D tempPos = dir;
	tempPos.Normalise();
	tempPos.SetLength(13.f);
	gunPos.SetX(pos.GetX() - tempPos.GetX());
	gunPos.SetY(pos.GetY() - tempPos.GetY());
}

//Checks for and handles user input
void Player::UpdatePlayer()
{
	//We need to wait for the database to fetch data before we can initialise the HUD sprites.
	if ( dm.Rows() > 0 && !tableLoaded )
	{
		InitSprites();
	}
	else if ( !tableLoaded ) 
	{
		return;
	}

	SetGunPos();
	thrust = neutral;
	if ( alive )
	{
		//update combo 
		timeSinceLastKill += UPDATE_INTERVAL;
		
		//if the combo timer ran out: reset the combo
		if (combo > 0 && timeSinceLastKill > MAX_COMBO_TIME) 
		{
			combo = 0;
			//cout << "Combo Timeout" << endl;
		}
		
		//BELOW: removed for gameplay balancing.
		////////////////////////////////////////

		////if a bullet missed: reset the combo
		//for(int i = 0; i < MAX_BULLETS; i++)
		//{

			//if  (bullets[i].Missed() )
			//{   
			//	combo = 0;
			//	//cout << "Missed" << endl;
			//}
		//}

		HandleUserInput(); //movement and shooting
		CheckPlayerBounds(); // dont let the player go out of bounds
	}
	else //death animation
	{
		if ( AnimateDeath() )	//animation complete
		{
			pos.SetX(GetPlayerStartX());
			pos.SetY(GetPlayerStartY());
		}
	}
}

void Player::Draw()
{
	if  (!tableLoaded)
		return;

	MoveSprite( currentSprite, pos.GetX(), pos.GetY() );
	MoveSprite( gun, gunPos.GetX(), gunPos.GetY());	
	DrawSprite( currentSprite );				
	
	//gun was still appearing after death, bugfix. 
	if ( alive )
		DrawSprite( gun );

	for(int i = 0; i < MAX_BULLETS; i++)
	{    
		if  (bullets[i].Active() )
		{   
			bullets[i].Draw();
		}
	}
}

void Player::Respawn()
{
	alive = true;
	timeSinceDeath = 0.f;
	this->TurnOnEngine();
}

//return true when animation complete
bool
Player::AnimateDeath()
{
	timeSinceDeath += UPDATE_INTERVAL;
	int deathAnimationNum = (int)floor(timeSinceDeath * 5.f);
	if ( deathAnimationNum > 2 ) 
	{
		currentSprite = sprite;
		return true;
	}
	currentSprite = deathAnimations[deathAnimationNum];
	return false;
}

void Player::AddPoints( const unsigned int& points)
{
	
	++combo;

	if ( combo <= 10 )
		BASS_ChannelPlay(comboSounds[combo-1], true);
	else
		BASS_ChannelPlay(comboSounds[9], true);

	timeSinceLastKill = 0.0f;
	
	//add combo to score
	if ( combo > 1 )
	{
		this->points += combo * 25;
	}
	this->points += points;
}
int Player::Points()
{
	return points;
}
bool Player::Alive()
{
	return alive;
}
int Player::Combo()
{
	return combo;
}

void Player::TurnOnEngine()
{
	BASS_ChannelPlay(soundThrust, true);
	BASS_ChannelPlay(soundThrust2, true);
}
void Player::TurnOffEngine()
{
	BASS_ChannelStop(soundThrust);
	BASS_ChannelStop(soundThrust2);
}

void Player::IncrementHitCounter()
{
	++hitCounter;
}

void Player::ResetAccuracyStats()
{
	hitCounter = 0;
	shotsFired = 0;
}

float Player::Accuracy()
{
	if ( shotsFired == 0 )
		return 0.f;
	return (float)hitCounter / (float)shotsFired;
}


int Player::AddPowerUp(POWER_UP_TYPES type)
{
	points += 500;

	BASS_ChannelPlay(soundPowerup, true);
	if ( type == POWER_UP_TYPES::POWER_UP_FIRE_RATE ) 
	{
		if ( powerUpFireRateMulti < MAX_POWER_UPS )
		{
			powerUpFireRateMulti++;			
		}
		return 500;
	}
	else if ( type == POWER_UP_TYPES::POWER_UP_BACK_GUN ) 
	{

	}
	else if ( type == POWER_UP_TYPES::POWER_UP_SHIELD ) 
	{

	}
	else if ( type == POWER_UP_TYPES::POWER_UP_SPEED_UP ) 
	{

	}
	else if ( type == POWER_UP_TYPES::POWER_UP_WING_GUNS ) 
	{

	}
	return 0;
}