//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// EnemyBase.cpp
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#include "EnemyBase.h"
#include "FrameworkHelpers.h"
#include <iostream>
#include <string>

//init static members
vector<EnemyBulletPtr> EnemyBase::bullets;


//EnemyBase(Player* player, float spawnAt);
//spawnAt -- what time (in seconds) do we spawn this enemy at? 
//EnemyBase::EnemyBase(Player* player, const float& spawnAt, const int& health)	
EnemyBase::EnemyBase(const float& spawnTime, const int& health, const Vector2D& pos, float* plyrX, float* plyrY)	
{
	this->spawnTime = spawnTime;
	this->health = health;
	this->spawned = false;
	this->throwOutObject = false;
	this->pos = pos;
	this->plyrX = plyrX;
	this->plyrY = plyrY;

	//randomize max speed between the floor and ceiling
	maxSpeed = (float)RandomNumber((int)classMaxSpeedFloor, (int)classMaxSpeedCeiling);

	points = 100;//TODO make this per enemy

	if ( bullets.size() == 0 )
	{
		EnemyBase::InitialiseBullets();
	}

	soundAsplode = BASS_StreamCreateFile(false,SOUND_ENEMY_DEATH,0,0,0);
	soundLaser = BASS_StreamCreateFile(false,SOUND_ENEMY_LASER,0,0,0);

	for ( int i = 0; i < DEATH_ANIMATION_FRAMES; ++ i)
	{
		string fileName = "./images/explosion/frame";
		fileName += to_string(i+1);
		fileName += "x.png";
		deathAnimations[i] = CreateSprite( fileName.c_str(), 256, 256, true );
	}
}

void EnemyBase::MoveAway(Vector2D& velocity)
{
	Vector2D direction = Vector2D(*plyrX, *plyrY) - pos;
	direction.Normalise();

	direction.SetX(-direction.GetX());
	direction.SetY(-direction.GetY());

	velocity += direction * ENEMY_FORCE_MOVE_AWAY;
	if ( velocity.GetLength() > maxSpeed ) 	
		velocity.SetLength(maxSpeed);
	//Vector2D scaledVelocity = velocity * GetDeltaTime();
	pos += velocity;
}

float EnemyBase::X()
{
	return pos.GetX();
}

float EnemyBase::Y()
{
	return pos.GetY();
}

bool EnemyBase::Alive()
{
	if ( health <= 0  ) 
		return false;
	return true;
}

void EnemyBase::Spawn()
{
	spawned = true;
}

float EnemyBase::SpawnTime()
{
	return spawnTime;
}

bool EnemyBase::HasSpawned()
{
	return spawned;		
}

//bool EnemyBase::Hit(const int& dmg)
//return true if hit resulted in a kill
//return false if enemy still alive
int EnemyBase::Hit(const int& dmg)
{
	health -= dmg;
	if ( health <= 0 )
	{
		Die();
		return points;
	}
	return 0;
}

//returns true when animation has complete
bool EnemyBase::AnimateDeath()
{
	timeSinceDeath += GetDeltaTime();
	int deathAnimationNum = (int)(floor(timeSinceDeath * DEATH_ANIMATION_SPEED));
	if ( deathAnimationNum > DEATH_ANIMATION_FRAMES - 1 ) //finished animating
	{
		throwOutObject = true;
		return throwOutObject;
	}
	
	MoveSprite(deathAnimations[deathAnimationNum], X(), Y());
	DrawSprite(deathAnimations[deathAnimationNum]);
	return throwOutObject;
}

//bool EnemyBase::CollidedWithPlayer()
//{	
//	//dont process anything if enemy is not alive or has not spawned
//	if  ( Alive() )
//	{
//		float d = sqrt(pow(x - player->GetX(), 2) + pow(y - player->GetY(), 2));
//		if ( d < player->GetPlayerWidth() )
//			return true;		
//	}//if ( Alive() )		
//	
//	return false;
//}
void EnemyBase::SetDeathFrames(unsigned int* deathAnimation)
{
	for (int i = 0; i < DEATH_ANIMATION_FRAMES; ++i )
	{
		this->deathAnimations[i] = deathAnimation[i];
	}
}

void EnemyBase::Die()
{
	timeSinceDeath = 0.0f;
	BASS_ChannelPlay(soundAsplode, true);
}


void EnemyBase::Draw(const float& plyrX, const float& plyrY)
{
	if ( !throwOutObject )
	{
		if ( HasSpawned() ) 
		{
			//draw bullets
			for(int i = 0; i < MAX_BULLETS; i++)
			{    
				if  (bullets[i]->Active() )
				{
					bullets[i]->Draw();
				}
			}



			if ( Alive() )
			{
				MoveSprite(sprite, X(), Y());	
				RotateSpriteToAngle(sprite, AngleToPlayer(plyrX, plyrY));
				DrawSprite(sprite);	
			}
			else 
				AnimateDeath();
		}
	}
}

//Angle to player in radians (-3 to 3)
float 
EnemyBase::AngleToPlayer(const float& plyrX, const float& plyrY)
{
	return atan2(plyrY - Y(), plyrX - X());
}

float 
EnemyBase::DistanceToPlayer(const float& plyrX, const float& plyrY)
{
	float dx = plyrX - X();
	float dy = plyrY - Y();
	return sqrt(dx * dx + dy * dy);
}

bool
EnemyBase::ThrowAway()
{
	return throwOutObject;
}

float EnemyBase::classMaxSpeedCeiling = 0.f;
float EnemyBase::classMaxSpeedFloor = 0.f;

void
EnemyBase::SetMaxSpeedCeiling(float maxSpeed)
{
	EnemyBase::classMaxSpeedCeiling = maxSpeed;
}
void
EnemyBase::SetMaxSpeedFloor(float maxSpeed)
{
	EnemyBase::classMaxSpeedFloor = maxSpeed;
}

EnemyBulletPtr EnemyBase::GetInactiveBullet()
{
	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		if (!bullets[i]->Active())
		{
			return bullets[i];
		}
	}
	return bullets[0];
}

//check collisions then move bullets
void EnemyBase::UpdateBullets()
{
	for(int i = 0; i < MAX_BULLETS; i++)
	{    
		if  (bullets[i]->Active() )
		{
			//bullets[i]->Update(GetDeltaTime());    
			bullets[i]->Update();    
		}
	}
}

void EnemyBase::ResetBullets()
{
	for(int i = 0; i < MAX_BULLETS; i++)
	{    
		if  (bullets[i]->Active() )
		{
			bullets[i]->UninitialiseBullet();    
		}
	}

}

void EnemyBase::Shoot()
{
	Vector2D dir;
	GetSpriteAngleVector(sprite, dir);
	EnemyBase::GetInactiveBullet()->InitialiseBullet(pos.GetX(), pos.GetY(), dir);
	BASS_ChannelPlay(soundLaser, true);
}

void EnemyBase::InitialiseBullets()
{
	for ( int i = 0; i < MAX_BULLETS; ++i )
	{
		EnemyBase::bullets.push_back(make_shared<EnemyBullet>());
	}
}