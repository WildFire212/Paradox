#include "AudioSource.h"

namespace Paradox {
	namespace audio  {


AudioSource::AudioSource()
{
	//initialize the source 
	alGenSources(1, &m_SourceID);
	//alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	//alSource1f()
}

void AudioSource::playSound(const Audio& audio)
{
	stopPlaying(); 
	alSourcei(m_SourceID, AL_BUFFER, audio.getAudioBuffer()); 
	continuePlaying(); 
}

bool AudioSource::isPlaying()
{
	ALint isPlaying; 
	 alGetSourcei(m_SourceID, AL_SOURCE_STATE, &isPlaying);
	 return isPlaying == AL_PLAYING;
}

void AudioSource::continuePlaying()
{
	alSourcePlay(m_SourceID); 
}

void AudioSource::pause()
{
	alSourcePause(m_SourceID); 
}


void AudioSource::stopPlaying()
{
	alSourceStop(m_SourceID); 
}


void AudioSource::setLooping(bool loop)
{
	alSourcei(m_SourceID, AL_LOOPING, loop? AL_TRUE : AL_FALSE); 
}

void AudioSource::setPosition(maths::vec3 position)
{
	alSource3f(m_SourceID, AL_POSITION, position.x, position.y, position.z);
}


void AudioSource::setPitch(float pitch)
{
	alSourcef(m_SourceID, AL_PITCH, pitch);
}

void AudioSource::setVolume(float volume)
{
	alSourcef(m_SourceID, AL_GAIN, volume);
}



AudioSource::~AudioSource()
{

	stopPlaying(); 
	alDeleteSources(1, &m_SourceID);
}
} }
