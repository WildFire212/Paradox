#pragma once 
#include"al.h"
#include<string>
#include"WaveData.h"
#include"../maths/maths.h"
/*

	gc_initialize(0);	//initializing constructor .all contructors will be default
	gau_Manager* mgr;	//all in one audio manager
	mgr = gau_manager_create();
	gau_manager_destroy(mgr);
	gc_shutdown();
*/

namespace Paradox {
	namespace audio{

class Audio
{
private:
	ALuint m_AudioBuffer; 
public : 
	Audio(std::string filename);
	void  loadSound(std::string filename);
	
	void setListener(maths::vec3 position); 
	//getters and setters 
	const ALuint getAudioBuffer() const; 
	~Audio();
};
} }



