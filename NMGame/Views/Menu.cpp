#include "Menu.h"
#include <string>

Menu::Menu()
{
	mViewMenu = new Sprite("Assets/menu.png");
	mViewMenu->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);

	mSelection = new Animation("Assets/select.png", 2, 1, 2, 0.3f);
	mSelection->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2 + 125);

	mNumbers.push_back(new Sprite("Assets/2.png"));
	mNumbers.push_back(new Sprite("Assets/0.png"));
	mNumbers.push_back(new Sprite("Assets/2.png"));
	mNumbers.push_back(new Sprite("Assets/0.png"));
	mNumbers.push_back(new Sprite("Assets/2.png"));
	mNumbers.push_back(new Sprite("Assets/0.png"));

	mNumbers[0]->SetPosition(GameGlobal::GetWidth() / 2 - 68, GameGlobal::GetHeight() / 2 + 153);
	mNumbers[1]->SetPosition(GameGlobal::GetWidth() / 2 - 52, GameGlobal::GetHeight() / 2 + 153);
	mNumbers[2]->SetPosition(GameGlobal::GetWidth() / 2 - 8, GameGlobal::GetHeight() / 2 + 153);
	mNumbers[3]->SetPosition(GameGlobal::GetWidth() / 2 + 8, GameGlobal::GetHeight() / 2 + 153);
	mNumbers[4]->SetPosition(GameGlobal::GetWidth() / 2 + 52, GameGlobal::GetHeight() / 2 + 153);
	mNumbers[5]->SetPosition(GameGlobal::GetWidth() / 2 + 68, GameGlobal::GetHeight() / 2 + 153);
}

Menu::~Menu()
{
	delete mViewMenu;
	delete mSelection;
	for (int i = 0; i < mNumbers.size(); i++)
	{
		delete mNumbers.at(i);
	}
	mNumbers.clear();
}

void Menu::UpdateBulletCount(int missle, int thunder, int rocket)
{
	for (int i = 0; i < 6; i++)
		delete mNumbers.at(i);

	mNumbers[0] = new Sprite(("Assets/" + std::to_string(missle / 10) + ".png").c_str());
	mNumbers[1] = new Sprite(("Assets/" + std::to_string(missle % 10) + ".png").c_str());
	mNumbers[2] = new Sprite(("Assets/" + std::to_string(thunder / 10) + ".png").c_str());
	mNumbers[3] = new Sprite(("Assets/" + std::to_string(thunder % 10) + ".png").c_str());
	mNumbers[4] = new Sprite(("Assets/" + std::to_string(rocket / 10) + ".png").c_str());
	mNumbers[5] = new Sprite(("Assets/" + std::to_string(rocket % 10) + ".png").c_str());

	mNumbers[0]->SetPosition(GameGlobal::GetWidth() / 2 - 68, GameGlobal::GetHeight() / 2 + 153);
	mNumbers[1]->SetPosition(GameGlobal::GetWidth() / 2 - 52, GameGlobal::GetHeight() / 2 + 153);
	mNumbers[2]->SetPosition(GameGlobal::GetWidth() / 2 - 8, GameGlobal::GetHeight() / 2 + 153);
	mNumbers[3]->SetPosition(GameGlobal::GetWidth() / 2 + 8, GameGlobal::GetHeight() / 2 + 153);
	mNumbers[4]->SetPosition(GameGlobal::GetWidth() / 2 + 52, GameGlobal::GetHeight() / 2 + 153);
	mNumbers[5]->SetPosition(GameGlobal::GetWidth() / 2 + 68, GameGlobal::GetHeight() / 2 + 153);
}

void Menu::Update(float dt)
{
	mSelection->Update(dt);
}

void Menu::Draw()
{
	mViewMenu->Draw();
	mSelection->Draw();
	for (int i = 0; i < mNumbers.size(); i++)
		mNumbers.at(i)->Draw();
}

void Menu::OnKeyPressed(int key)
{
	if (key == VK_LEFT)
	{
		if (mSelection->GetPosition().x == GameGlobal::GetWidth() / 2 - 60)
			mSelection->SetPosition(GameGlobal::GetWidth() / 2 + 60, mSelection->GetPosition().y);
		else
			mSelection->SetPosition(mSelection->GetPosition().x - 60, mSelection->GetPosition().y);
	}
	else if (key == VK_RIGHT)
	{
		if (mSelection->GetPosition().x == GameGlobal::GetWidth() / 2 + 60)
			mSelection->SetPosition(GameGlobal::GetWidth() / 2 - 60, mSelection->GetPosition().y);
		else
			mSelection->SetPosition(mSelection->GetPosition().x + 60, mSelection->GetPosition().y);
	}
}

Animation* Menu::GetSelection()
{
	return mSelection;
}

vector<Sprite*> Menu::GetNumbers()
{
	return mNumbers;
}

int Menu::GetSkill()
{
	if (mSelection->GetPosition().x == GameGlobal::GetWidth() / 2 - 60)
		return 1;
	else if (mSelection->GetPosition().x == GameGlobal::GetWidth() / 2)
		return 2;
	else return 3;
}