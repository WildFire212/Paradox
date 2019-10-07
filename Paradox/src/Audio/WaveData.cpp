#include "WaveData.h"

namespace Paradox {
	namespace audio {
		WaveData::WaveData()
		{
		}

		WaveData::~WaveData()
		{
		}
		void WaveData::load(std::string filename) {
			bool file = loadWavFile(filename.c_str(), &this->size, &this->frequency, &this->format);
		}

		bool WaveData::loadWavFile(const char * filename, ALsizei * size, ALsizei * frequency, ALenum * format)
		{
			FILE* soundFile = NULL;
			WAVEFormat wave_format;
			RIFFHeader riff_header;
			WAVE_Data wave_data;

			try {
				soundFile = fopen(filename, "rb");
				if (!soundFile)
					throw (filename);

				fread(&riff_header, sizeof(RIFFHeader), 1, soundFile);

				if ((riff_header.chunkID[0] != 'R' ||
					riff_header.chunkID[1] != 'I' ||
					riff_header.chunkID[2] != 'F' ||
					riff_header.chunkID[3] != 'F') &&
					(riff_header.format[0] != 'W' ||
						riff_header.format[1] != 'A' ||
						riff_header.format[2] != 'V' ||
						riff_header.format[3] != 'E'))
					throw ("Invalid RIFF or WAVE Header");

				fread(&wave_format, sizeof(WAVEFormat), 1, soundFile);

				if (wave_format.subChunkID[0] != 'f' ||
					wave_format.subChunkID[1] != 'm' ||
					wave_format.subChunkID[2] != 't' ||
					wave_format.subChunkID[3] != ' ')
					throw ("Invalid Wave Format");

				if (wave_format.subChunkSize > 16)
					fseek(soundFile, sizeof(short), SEEK_CUR);

				fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);

				if (wave_data.subChunkID[0] != 'd' ||
					wave_data.subChunkID[1] != 'a' ||
					wave_data.subChunkID[2] != 't' ||
					wave_data.subChunkID[3] != 'a')
					throw ("Invalid data header");

				data = new unsigned char[wave_data.subChunk2Size];

				if (!fread(data, wave_data.subChunk2Size, 1, soundFile))
					throw ("error loading WAVE data into struct!");

				*size = wave_data.subChunk2Size;
				*frequency = wave_format.sampleRate;

				if (wave_format.numChannels == 1) {
					if (wave_format.bitsPerSample == 8)
						*format = AL_FORMAT_MONO8;
					else if (wave_format.bitsPerSample == 16)
						*format = AL_FORMAT_MONO16;
				}
				else if (wave_format.numChannels == 2) {
					if (wave_format.bitsPerSample == 8)
						*format = AL_FORMAT_STEREO8;
					else if (wave_format.bitsPerSample == 16)
						*format = AL_FORMAT_STEREO16;
				}


				fclose(soundFile);
				return true;
			}
			catch (char* error) {
				if (soundFile != NULL)
					fclose(soundFile);
				return false;
			}
		}

	}
}