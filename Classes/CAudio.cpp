#include"CAudio.h"

void playSound(const std::string & filePath, bool loop, float volumn)
{
	cocos2d::experimental::AudioProfile *profile = new cocos2d::experimental::AudioProfile;
	profile->name = std::string("bgm");
	profile->maxInstances = 10;
	cocos2d::experimental::AudioEngine::play2d(filePath, loop, volumn, profile);
}