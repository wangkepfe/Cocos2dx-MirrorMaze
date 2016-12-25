#ifndef __C_AUDIO_H__
#define __C_AUDIO_H__

#include "cocos2d.h"
#include "AudioEngine.h"

void playSound(const std::string & filePath, bool loop = false, float volumn = 1.0f);

#endif