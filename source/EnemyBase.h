//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// EnemyBase.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#pragma once

//#include "Player.h"
#include "GLAHGraphics.h"
#include "CONSTS.H"
#include "Vector.h"
#include "EnemyBullet.h"
#include <vector>
#include "bass.h"

enum ENEMY_TYPE
{
	ENEMY1,
	ENEMY2
};

class EnemyBase
{
public:
	//EnemyBase(Player* player, float spawnAt);
	//player -- need this to check collisions
	//spawnTime -- what time (in seconds) do we spawn this enemy at? 
	//EnemyBase(Player* player, const float& spawnAt, const int& health);
	EnemyBase(const float& spawnTime, const int& health, const Vector2& pos, float* plyrX, float* plyrY);
	virtual void Move(const float& plyrX, const float& plyrY, bool playerAlive) = 0; //must be defined by derived class
	void MoveAway(Vector2& velocity);
	float X();
	float Y();
	bool Alive();//return false if health <= 0
	void Spawn(); //enemy will start moving and drawing once Spawn() is called
	float SpawnTime(); //time in seconds from the start of the level when enemy should spawn
	bool HasSpawned(); //has the enemy spawned yet? 	
	bool AnimateDeath(); //return true when animation is complete. 
	//bool CollidedWithPlayer(); //returns true if this sprite collides with Player sprite
	int Hit(const int& dmg); //health -= dmg. returns points to award
	bool ThrowAway();//should we toss this Enemy? i.e. has it been killed and the death animation is complete.
	void Draw(const float& plyrX, const float& plyrY);
	//void DoCollisionChecks();

	static void SetMaxSpeedCeiling(float maxSpeed); //set ceiling for enemy max speed
	static void SetMaxSpeedFloor(float minSpeed); //set the floor for enemy max speed

	static void UpdateBullets();
	static vector<EnemyBulletPtr> bullets;
	static void ResetBullets();

protected: 
	void SetDeathFrames(SDL_Texture** deathAnimation); //to be called by derived class
	float AngleToPlayer(const float& plyrX, const float& plyrY);
	float DistanceToPlayer(const float& plyrX, const float& plyrY);
	SDL_Texture* sprite;
	SDL_Texture* deathAnimations[DEATH_ANIMATION_FRAMES];//constraint: all enemies must have DEATH_ANIMATION_FRAMES death frames
	Vector2 pos;
	
	float *plyrX, *plyrY;

	int health;
	float timeSinceDeath; //not set until Hit() that results in a kill.	
	//Player* player;
	float spawnTime;
	bool spawned;
	void Die();
	bool throwOutObject;


	//statics
	static float classMaxSpeedCeiling;
	static float classMaxSpeedFloor;
	static EnemyBulletPtr GetInactiveBullet();
	static void InitialiseBullets();

	//Shoot
	void Shoot();

	//sounds
//	HSTREAM soundAsplode;
//	HSTREAM soundLaser;

	float maxSpeed;

	int points; //how many points do we get for a kill? 
private:	

};

//Enemy List ( a list of EnemyBase Types )
typedef list<shared_ptr<EnemyBase> > EnemyList;

//Single smart pointer to EnemyBase
typedef shared_ptr<EnemyBase> EnemyBasePtr;