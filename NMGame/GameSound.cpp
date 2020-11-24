#include "GameSound.h"
GameSound* GameSound::mInstance = NULL;

GameSound::GameSound()
{
	
}

GameSound::~GameSound()
{

}

GameSound* GameSound::GetInstance()
{
	if (!mInstance)
	{
		mInstance = new GameSound();
	}
	return mInstance;
}

std::string GameSound::GetName(std::string s)
{
	std::string name = "";
	for (int i = s.length() - 5; i >= 0; i--)
	{
		if (s[i] != '/')
			name = s[i] + name;
		else break;
	}
	return name;
}

void GameSound::Play(std::string filePath)
{
	std::string name = GetName(filePath);
	std::string str = "open " + filePath + " type mpegvideo alias " + name;
	mciSendString(const_cast<char*>(str.c_str()), NULL, 0, NULL);
	std::string str2 = "play " + name + " from 0";
	mciSendString(const_cast<char*>(str2.c_str()), NULL, 0, NULL);
}

void GameSound::PlayRepeat(std::string filePath)
{
	std::string name = GetName(filePath);
	std::string str = "open " + filePath + " type mpegvideo alias " + name;
	mciSendString(const_cast<char*>(str.c_str()), NULL, 0, NULL);
	std::string str2 = "play " + name + " repeat";
	mciSendString(const_cast<char*>(str2.c_str()), NULL, 0, NULL);
}

void GameSound::Stop(std::string name)
{
	std::string str = "stop " + name;
	mciSendString(const_cast<char*>(str.c_str()), NULL, 0, NULL);
}

void GameSound::Close(std::string name)
{
	std::string str = "close " + name;
	mciSendString(const_cast<char*>(str.c_str()), NULL, 0, NULL);
}