#pragma comment(lib, "Winmm.lib")
#include <Windows.h>
#include <string>
class GameSound
{
public:
	static GameSound* GetInstance();
	GameSound();
	~GameSound();
	void Play(std::string filePath);
	void Stop();
	void Close();

private:
	static GameSound* mInstance;
};

