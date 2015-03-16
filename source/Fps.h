//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// Fps.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "GLAHGraphics.h"
#include <iostream>

class Fps
{
public:
    // Constructor
    Fps()
	{
		deltaCounter = 0.0f;
		currentFPS = 0;
		tickCounter = 0;
	}

	void SetIncrementInterval(float incrementInterval)
	{
		this->incrementInterval = incrementInterval;
	}



	void Update()
	{
		deltaCounter += GetDeltaTime();
		++tickCounter;
	}

    // Get fps
    int get()
    {
		//only get the fps once every incrementInterval
		if (deltaCounter > incrementInterval)
		{
			//get the fps
			float ffps = tickCounter/deltaCounter;
			int ifps = (int) (ffps);
			currentFPS = ifps;

			//reset frame and delta counter
			deltaCounter = 0.f;
			tickCounter = 0;

			return ifps;
		}
		else //if we havent hit our incrementInterval, return current (previous) fps
		{
			return currentFPS;
		}
    }
private:
	float incrementInterval;//how often should the value change? 
	float deltaCounter; //+= getDeltaTime; //each update
	int tickCounter;
	int currentFPS;
};