#pragma once
#include "../Animation.h"
class IntroAnimation : public Animation
{
public:
	IntroAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL) : Animation(filePath, totalFrame, rows, columns, timePerFrame, colorKey)
	{
		timeWait = 0;
	}
	~IntroAnimation();
	void Update(float dt);
private:
	float timeWait;
};