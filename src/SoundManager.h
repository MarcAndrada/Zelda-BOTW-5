#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "includes.h"
#include <SFML/Audio.hpp>

#define MAX_SOUNDS 40

class SoundManager
{
	public:
		SoundManager();
		~SoundManager();
	
		int playSound(const char* filepath, bool loop = false);
		void loadSound(const char* filepath);

		void soundPause(int soundID);
		void soundResume(int soundID);
		void soundStop(int soundID);
		
		void musicPause();
		void musicResume();
		void musicStop();
		bool musicIsPlaying();

		bool soundIsPlaying(int soundID);
		static SoundManager* getInstance();
		
		
	private:
		sf::SoundBuffer* getBuffer(const char* file);
		void updateSoundFirstFreeSlot();

		static SoundManager*					instance;
		
		std::map<std::string, sf::SoundBuffer*> mSndBufferMap;
		std::vector<sf::Sound*>					mSoundVector;
		sf::Music*								mCurrentBGM;
		
		int mCurretSoundIndex = 0;
	
};

#endif