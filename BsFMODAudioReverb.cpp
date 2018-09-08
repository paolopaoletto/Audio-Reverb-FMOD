#include "BsFMODAudioReverb.h"

namespace bs 
{

	FMODAudioReverb::FMODAudioReverb() 
		: ir(nullptr), channel(nullptr), reverbGroup(nullptr), 
		reverbUnit(nullptr), channelHead(nullptr), reverbConnection(nullptr),
		reverb3D(nullptr)
	{
		gFMODAudio()._registerReverb(this);
	}

	FMODAudioReverb::~FMODAudioReverb() 
	{
		gFMODAudio()._unregisterReverb(this);
	}

	void FMODAudioReverb::setSource(const HAudioSource& source) 
	{
	
	}

	void FMODAudioReverb::setIR(const HAudioClip& clip) 
	{
	
	}

	void FMODAudioReverb::setWetVolume(float volume) 
	{
	
	}

	void FMODAudioReverb::setDryVolume(float volume) 
	{
	
	}

	void FMODAudioReverb::setDecayTime(float time)
	{

	}

	void FMODAudioReverb::setEarlyDelay(float delay)
	{

	}

	void FMODAudioReverb::setLateDelay(float delay)
	{

	}

	void FMODAudioReverb::setHFReference(float hfref)
	{

	}

	void FMODAudioReverb::setHFDecayRatio(float ratio)
	{

	}

	void FMODAudioReverb::setDiffusion(float diffusion)
	{

	}

	void FMODAudioReverb::setDensity(float density)
	{

	}

	void FMODAudioReverb::setLowShelfFrequencies(float freq)
	{

	}

	void FMODAudioReverb::setLowShelfGain(float gain)
	{

	}

	void FMODAudioReverb::setHighCut(float freq)
	{

	}

	void FMODAudioReverb::setEarlyLateMix(float elm)
	{

	}

	void FMODAudioReverb::setWetLevel(float level)
	{

	}

}
