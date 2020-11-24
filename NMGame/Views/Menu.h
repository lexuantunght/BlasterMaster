#pragma once
#include "../Sprite.h"
#include "../Animation.h"
class Menu
{
public:
	Menu();
	~Menu();
	void Update(float dt);
	void Draw();
	void OnKeyPressed(int key);
	vector<Sprite*> GetNumbers();
	Animation* GetSelection();
	int GetSkill();
	void UpdateBulletCount(int missle, int thunder, int rocket);
private:
	Sprite* mViewMenu;
	Animation* mSelection;
	vector<Sprite*> mNumbers;
};

