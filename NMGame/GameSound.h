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
	void PlayRepeat(std::string filePath);
	void Stop(std::string name);
	void Close(std::string name);

private:
	static GameSound* mInstance;
	std::string GetName(std::string s);
};

