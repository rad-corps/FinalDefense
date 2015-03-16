#pragma once

#include "Vector.h"
#include "CONSTS.h"

class SpawnPointGenerator
{
public:
	SpawnPointGenerator();
	~SpawnPointGenerator();

	Vector2 Generate(ENEMY_SPAWN_POINTS point, int widthMargin, int heightMargin);
};

