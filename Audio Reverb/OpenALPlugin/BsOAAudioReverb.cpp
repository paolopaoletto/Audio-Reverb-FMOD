#include "BsOAAudioReverb.h"

namespace bs 
{
	OAAudioReverb::OAAudioReverb()
	{
		gOAAudio()._registerReverb(this);
	}

	OAAudioReverb::~OAAudioReverb()
	{
		gOAAudio()._unregisterReverb(this);
	}

	void OAAudioReverb::setSource(const HAudioSource& source)
	{
		
	}

	void OAAudioReverb::setIR(const HAudioClip& clip)
	{
		
	}

	void OAAudioReverb::setWetVolume(float volume)
	{

	}

	void OAAudioReverb::setDryVolume(float volume)
	{

	}

	void OAAudioReverb::setDiffusion(float diffusion)
	{

	}

	void OAAudioReverb::setDensity(float density)
	{

	}

	void OAAudioReverb::setGain(float gain)
	{

	}

	void OAAudioReverb::setGainHF(float gain)
	{

	}

	void OAAudioReverb::setGainLF(float gain)
	{

	}

	void OAAudioReverb::setDecayTime(float time)
	{

	}

	void OAAudioReverb::setDecayHFRatio(float ratio)
	{

	}

	void OAAudioReverb::setDecayLFRatio(float ratio)
	{

	}

	void OAAudioReverb::setReflectionGain(float gain)
	{

	}

	void OAAudioReverb::setReflectionDelay(float delay)
	{

	}

	void OAAudioReverb::setReflectionPan(Vector3 pan)
	{

	}

	void OAAudioReverb::setLateReverbGain(float gain)
	{

	}

	void OAAudioReverb::setLateReverbDelay(float delay)
	{

	}

	void OAAudioReverb::setLateReverbPan(Vector3 pan)
	{

	}

	void OAAudioReverb::setEchoTime(float time)
	{

	}

	void OAAudioReverb::setEchoDepth(float depth)
	{

	}

	void OAAudioReverb::setModulationTime(float time)
	{

	}

	void OAAudioReverb::setModulationDepth(float depth)
	{

	}

	void OAAudioReverb::setHFReference(float hfref)
	{

	}

	void OAAudioReverb::setLFReference(float hfref)
	{

	}

	void OAAudioReverb::setHighCut(float freq)
	{

	}

	void OAAudioReverb::setEarlyLateMix(float elm)
	{

	}

	void OAAudioReverb::setWetLevel(float level)
	{

	}

	void OAAudioReverb::setRoomRolloffFactor(float factor)
	{

	}

	void OAAudioReverb::setAirAbsorptionGainHF(float gain)
	{

	}

	void OAAudioReverb::setDecayHFLimit(bool limit)
	{

	}

	void OAAudioReverb::setReverbPreset(AudioReverbPreset preset)
	{

	}

	void OAAudioReverb::setPosition(Vector3 position)
	{

	}

	void OAAudioReverb::setMinDistance(float distance)
	{

	}

	void OAAudioReverb::setMaxDistance(float distance)
	{

	}

	void OAAudioReverb::onClipChanged()
	{

	}

}