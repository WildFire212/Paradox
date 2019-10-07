#pragma once
#include"al.h"
#include"../maths/maths.h"
#include"Audio.h"
namespace Paradox {
	namespace audio {
class AudioSource
{
private: 
	ALuint m_SourceID; 


public:
	AudioSource();
	~AudioSource();

	void playSound(const Audio& audio);
	bool isPlaying();

	void continuePlaying();
	void pause(); 
	void stopPlaying(); 

	
	//setter and getter
	void setLooping(bool loop);

	void setPosition(maths::vec3 position );
	void setPitch(float pitch);
	void setVolume(float volume);
	
};

} }
