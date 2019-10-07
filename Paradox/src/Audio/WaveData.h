#pragma once 
#include <stdio.h>
#include<al.h>
#include<alc.h>
#include<string>

namespace Paradox {
	namespace audio {
		
class WaveData {
public: 
		ALsizei size;
		ALsizei frequency;
		ALenum format;
		unsigned char* data;

	private:
	struct RIFFHeader {
		char chunkID[4];
		long chunkSize; 
		char format[4]; 
	};

	struct WAVEFormat {
		char subChunkID[4]; 
		long subChunkSize; 
		short audioFormat; 
		short numChannels; 
		long sampleRate; 
		long byeRate; 
		short blockAlign; 
		short bitsPerSample; 
	};
	int const * a; 
	struct WAVE_Data {
		char subChunkID[4];
		long subChunk2Size;
	};

public :
	WaveData(); 
	~WaveData(); 
	bool loadWavFile(const char* filename, ALsizei* size, ALsizei* frequency,
		ALenum* format);
	void load(std::string filename);
	 
};
} }