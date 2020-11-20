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

void GameSound::Play(std::string filePath)
{
	std::string str = "open " + filePath + " type mpegvideo alias mp3";
	mciSendString(const_cast<char*>(str.c_str()), NULL, 0, NULL);
	mciSendString("play mp3", NULL, 0, NULL);
}

void GameSound::Stop()
{
	mciSendString("stop mp3", NULL, 0, NULL);
}

void GameSound::Close()
{
	mciSendString("close mp3", NULL, 0, NULL);
}