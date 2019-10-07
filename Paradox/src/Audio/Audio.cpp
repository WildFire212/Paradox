#include "Audio.h"

namespace Paradox {
	namespace audio {
Audio::Audio(std::string filename)
{
	alGenBuffers(1,&m_AudioBuffer);
	loadSound(filename); 

}
	

void  Audio::loadSound (std::string filename) {
	WaveData waveFile; 
	waveFile.load(filename); 

	alBufferData(m_AudioBuffer, waveFile.format,(void*)waveFile.data, waveFile.size,waveFile.frequency);
}


void Audio::setListener(maths::vec3 position)
{
	alListener3f(AL_POSITION, position.x , position.y, position.z); 
	alListener3f(AL_VELOCITY, 0, 0, 0); 
}

const ALuint Audio::getAudioBuffer() const
{
	return m_AudioBuffer; 
}

Audio::~Audio()
{
	alDeleteBuffers(1, &m_AudioBuffer); 
}
} }
