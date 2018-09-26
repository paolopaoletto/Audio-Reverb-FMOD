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
		AudioReverb::setSource(source);
	}

	void OAAudioReverb::setIR(const HAudioClip& clip)
	{
		AudioReverb::setIR(clip);
	}

	void OAAudioReverb::setWetVolume(float volume)
	{
		AudioReverb::setWetVolume(volume);
	}

	void OAAudioReverb::setDryVolume(float volume)
	{
		AudioReverb::setDryVolume(volume);
	}

	void OAAudioReverb::setDiffusion(float diffusion)
	{
		AudioReverb::setDiffusion(diffusion);
	}

	void OAAudioReverb::setDensity(float density)
	{
		AudioReverb::setDensity(density);
	}

	void OAAudioReverb::setGain(float gain)
	{
		AudioReverb::setGain(gain);
	}

	void OAAudioReverb::setGainHF(float gain)
	{
		AudioReverb::setGainHF(gain);
	}

	void OAAudioReverb::setGainLF(float gain)
	{
		AudioReverb::setGainLF(gain);
	}

	void OAAudioReverb::setDecayTime(float time)
	{
		AudioReverb::setDecayTime(time);
	}

	void OAAudioReverb::setDecayHFRatio(float ratio)
	{
		AudioReverb::setDecayHFRatio(ratio);
	}

	void OAAudioReverb::setDecayLFRatio(float ratio)
	{
		AudioReverb::setDecayLFRatio(ratio);
	}

	void OAAudioReverb::setReflectionGain(float gain)
	{
		AudioReverb::setReflectionGain(gain);
	}

	void OAAudioReverb::setReflectionDelay(float delay)
	{
		AudioReverb::setReflectionDelay(delay);
	}

	void OAAudioReverb::setReflectionPan(Vector3 pan)
	{
		AudioReverb::setReflectionPan(pan);
	}

	void OAAudioReverb::setLateReverbGain(float gain)
	{
		AudioReverb::setLateReverbGain(gain);
	}

	void OAAudioReverb::setLateReverbDelay(float delay)
	{
		AudioReverb::setLateReverbDelay(delay);
	}

	void OAAudioReverb::setLateReverbPan(Vector3 pan)
	{
		AudioReverb::setLateReverbPan(pan);
	}

	void OAAudioReverb::setEchoTime(float time)
	{
		AudioReverb::setEchoTime(time);
	}

	void OAAudioReverb::setEchoDepth(float depth)
	{
		AudioReverb::setEchoDepth(depth);
	}

	void OAAudioReverb::setModulationTime(float time)
	{
		AudioReverb::setModulationTime(time);
	}

	void OAAudioReverb::setModulationDepth(float depth)
	{
		AudioReverb::setModulationDepth(depth);
	}

	void OAAudioReverb::setHFReference(float hfref)
	{
		AudioReverb::setHFReference(hfref);
	}

	void OAAudioReverb::setLFReference(float hfref)
	{
		AudioReverb::setLFReference(hfref);
	}

	void OAAudioReverb::setHighCut(float freq)
	{
		// FMOD Features.
	}

	void OAAudioReverb::setEarlyLateMix(float elm)
	{
		// FMOD Features.
	}

	void OAAudioReverb::setWetLevel(float level)
	{
		// FMOD Features.
	}

	void OAAudioReverb::setRoomRolloffFactor(float factor)
	{
		AudioReverb::setRoomRolloffFactor(factor);
	}

	void OAAudioReverb::setAirAbsorptionGainHF(float gain)
	{
		AudioReverb::setAirAbsorptionGainHF(gain);
	}

	void OAAudioReverb::setDecayHFLimit(bool limit)
	{
		AudioReverb::setDecayHFLimit(limit);
	}

	void OAAudioReverb::setReverbPreset(AudioReverbPreset preset)
	{
		AudioReverb::setReverbPreset(preset);
	}

	void OAAudioReverb::setPosition(Vector3 position)
	{
		// FMOD Features.
	}

	void OAAudioReverb::setMinDistance(float distance)
	{
		// FMOD Features.
	}

	void OAAudioReverb::setMaxDistance(float distance)
	{
		// FMOD Features.
	}

	void OAAudioReverb::onClipChanged()
	{

	}

}