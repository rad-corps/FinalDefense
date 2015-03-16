#pragma once

#include "LevelBase.h"

class Level1 : public LevelBase
{
public: 
	Level1(float * plyrX, float * plyrY);
	~Level1();
	WaveInfo CreateNextWave();
private:
	WaveInfo Wave1();
	WaveInfo Wave2();
	WaveInfo Wave3();
	WaveInfo Wave4();
	WaveInfo Wave5();
	WaveInfo Wave6();
	WaveInfo Wave7();
	WaveInfo Wave8();
	WaveInfo Wave9();
	WaveInfo Wave10();
	//WaveInfo Wave11();
	//WaveInfo Wave12();

	float *plyrX;
	float *plyrY;

	int enemyCount; 
	int waveNum;

	
};