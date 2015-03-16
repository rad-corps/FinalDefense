#pragma once

#include "Vector2D.h"
#include "CONSTS.h"

class SpawnPointGenerator
{
public:
	SpawnPointGenerator();
	~SpawnPointGenerator();

	Vector2D Generate(ENEMY_SPAWN_POINTS point, int widthMargin, int heightMargin);
};

