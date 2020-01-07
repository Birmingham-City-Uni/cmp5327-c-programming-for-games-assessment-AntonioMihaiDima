#pragma once
#pragma comment (lib,"winmm.lib")
#include <Windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

class AudioManager {

public:
	void PlayMusic()
	{

		PlaySound(TEXT("background.wav"), NULL, SND_ASYNC | SND_LOOP);
	}






private:



};