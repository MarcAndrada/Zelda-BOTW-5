#include "SoundManager.h"

SoundManager* SoundManager::instance = NULL;
SoundManager* SoundManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new SoundManager;
	}

	return instance;
}

void SoundManager::updateSoundFirstFreeSlot()
{
	mCurretSoundIndex = 0;
	for (int i = 0; i < MAX_SOUNDS; i++)
	{
		if (mSoundVector[i] == NULL)
		{
			mCurretSoundIndex = i;
			break;
		}
		else
		{
			sf::Time duration = mSoundVector[i]->getBuffer()->getDuration();
			sf::Time offset = mSoundVector[i]->getPlayingOffset();
			if ((offset.asMilliseconds() >= duration.asMilliseconds() || offset.asMilliseconds() == 0) && !soundIsPlaying(i))
			{
				soundStop(i);
				mCurretSoundIndex = i;
				break;
			}
		}
	}
}

SoundManager::SoundManager()
{
	if (instance != NULL)
	{
		return;
	}
	mCurretSoundIndex = 0;
	mSoundVector.resize(MAX_SOUNDS, NULL);
	mCurrentBGM = NULL;
}

SoundManager::~SoundManager()
{
}

int SoundManager::playSound(const char* filepath, bool loop)
{
	sf::SoundBuffer* buffer = getBuffer(filepath);
	if (mSoundVector[mCurretSoundIndex] != NULL)
	{
		updateSoundFirstFreeSlot();
	}
	int soundID = mCurretSoundIndex;
	mSoundVector[soundID] = new sf::Sound();
	mSoundVector[soundID]->setBuffer(*buffer);
	mSoundVector[soundID]->play();
	mSoundVector[soundID]->setLoop(loop);
	updateSoundFirstFreeSlot();
	return soundID;
}

void SoundManager::loadSound(const char* filepath){
	getBuffer(filepath);
}

void SoundManager::soundPause(int soundID)
{
	if (soundID < 0 || soundID >= MAX_SOUNDS) { return; }
	if (mSoundVector[soundID] == NULL) { return; }
	if (soundIsPlaying(soundID)){
		mSoundVector[soundID]->pause();
	}
}
void SoundManager::soundResume(int soundID)
{
	if (soundID < 0 || soundID >= MAX_SOUNDS) { return; }
	if (mSoundVector[soundID] == NULL) { return; }
	if (soundIsPlaying(soundID)) {
		mSoundVector[soundID]->play();
	}
}
void SoundManager::soundStop(int soundID){
	if (soundID < 0 || soundID >= MAX_SOUNDS) { return; }
	if (mSoundVector[soundID] == NULL){ return; }
	
	mSoundVector[soundID]->stop();
	delete(mSoundVector[soundID]);
	mSoundVector[soundID] = NULL;
}

void SoundManager::musicPause()
{
	if (mCurrentBGM == NULL)
	{
		return;
	}
	if (musicIsPlaying())
	{
		mCurrentBGM->pause();
	}
}

void SoundManager::musicResume()
{
	if (mCurrentBGM == NULL){
		return;
	}
	if (!musicIsPlaying()){
		mCurrentBGM->play();
	}
}

void SoundManager::musicStop()
{
	if (mCurrentBGM == NULL){
		return;
	}

	mCurrentBGM->stop();
	delete(mCurrentBGM);
	mCurrentBGM = NULL;
}

bool SoundManager::musicIsPlaying()
{
	if (mCurrentBGM == NULL) {
		return false;
	}
	return mCurrentBGM->getStatus() == sf::Sound::Playing;
}



bool SoundManager::soundIsPlaying(int soundID)
{
	if (soundID < 0 || soundID >= MAX_SOUNDS) { return false; }
	if (mSoundVector[soundID] == NULL) { return false; }
	return mSoundVector[soundID]->getStatus() == sf::Sound::Playing;
}



sf::SoundBuffer* SoundManager::getBuffer(const char* file)
{
	std::map<std::string, sf::SoundBuffer*>::iterator it = mSndBufferMap.find(file);
	if (it == mSndBufferMap.end()){
		sf::SoundBuffer* buffer = new sf::SoundBuffer();
		if (!buffer->loadFromFile(file)){
			std::cout << "Error opening" << file << std::endl;
			return NULL;
		}
		std::cout << "Add sound" << file << "(first request)" << std::endl;
		mSndBufferMap.insert(std::pair<std::string, sf::SoundBuffer*>(file, buffer));
		it = mSndBufferMap.find(file);
	}
	return it->second;
}
