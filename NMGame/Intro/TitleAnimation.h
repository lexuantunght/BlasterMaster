#pragma once
#include "../Animation.h"
class TitleAnimation : public Animation
{
public:
	TitleAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL) : Animation(filePath, totalFrame, rows, columns, timePerFrame, colorKey)
	{
		timeLoad = 0;
	}
	~TitleAnimation();
	void Update(float dt);
private:
	float timeLoad;
};

