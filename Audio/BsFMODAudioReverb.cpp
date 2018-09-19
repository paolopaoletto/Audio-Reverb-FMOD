#include "BsFMODAudioReverb.h"

namespace bs {

	FMODAudioReverb::FMODAudioReverb() 
	{
		gFMODAudio()._registerReverb(this);
	}

	FMODAudioReverb::~FMODAudioReverb() 
	{
		gFMODAudio()._unregisterReverb(this);
	}

	void FMODAudioReverb::setSource(const HAudioSource& source) 
	{
		AudioReverb::setSource(source);

		/** Temporary positions */
		FMOD_VECTOR position = { -10.0f, 0.0f, 0.0f };

		const float min = 10.0f;
		const float max = 20.0f;

		FMOD::System* fmod = gFMODAudio()._getFMOD();
		if (!isReverbIR()) {
			fmod->createReverb3D(&reverb3D);
			reverb3D->setProperties(&prop);
			reverb3D->set3DAttributes(&position, min, max);
		}
	}

	void FMODAudioReverb::setIR(const HAudioClip& clip) 
	{
		AudioReverb::setIR(clip);

		FMOD::System* fmod = gFMODAudio()._getFMOD();
		//FMODAudioClip* fmodClip = static_cast<FMODAudioClip*>(mIr.get());
		
		if (isReverbIR() && clip != nullptr) {
			fmod->createChannelGroup("reverb", &reverbGroup);
			fmod->createDSPByType(FMOD_DSP_TYPE_CONVOLUTIONREVERB, &reverbUnit);
			reverbGroup->addDSP(FMOD_CHANNELCONTROL_DSP_TAIL, reverbUnit);
		}
	}

	void FMODAudioReverb::setWetVolume(float volume) 
	{
		AudioReverb::setWetVolume(volume);

		if (reverbUnit != nullptr) {
			reverbUnit->setParameterData(FMOD_DSP_CONVOLUTION_REVERB_PARAM_IR, &irData, irDataLength);
			reverbUnit->setParameterFloat(FMOD_DSP_CONVOLUTION_REVERB_PARAM_DRY, -80.0f);
		}

		if (reverbConnection != nullptr)
			reverbConnection->setMix(mWetVolume);
	}

	void FMODAudioReverb::setDryVolume(float volume) 
	{
		AudioReverb::setDryVolume(volume);
	}

	void FMODAudioReverb::setDecayTime(float time)
	{
		AudioReverb::setDecayTime(time);
		
		prop.DecayTime = mDecayTime;
	}

	void FMODAudioReverb::setEarlyDelay(float delay)
	{
		AudioReverb::setEarlyDelay(delay);

		prop.EarlyDelay = mEarlyDelay;
	}

	void FMODAudioReverb::setLateDelay(float delay)
	{
		AudioReverb::setLateDelay(delay);

		prop.LateDelay = mLateDelay;
	}

	void FMODAudioReverb::setHFReference(float hfref)
	{
		AudioReverb::setHFReference(hfref);

		prop.HFReference = mHFReference;
	}

	void FMODAudioReverb::setHFDecayRatio(float ratio)
	{
		AudioReverb::setHFDecayRatio(ratio);

		prop.HFDecayRatio = mHFDecayRatio;
	}

	void FMODAudioReverb::setDiffusion(float diffusion)
	{
		AudioReverb::setDiffusion(diffusion);

		prop.Diffusion = mDiffusion;
	}

	void FMODAudioReverb::setDensity(float density)
	{
		AudioReverb::setDensity(density);

		prop.Density = mDensity;
	}

	void FMODAudioReverb::setLowShelfFrequencies(float freq)
	{
		AudioReverb::setLowShelfFrequencies(freq);

		prop.LowShelfFrequency = mLowShelfFrequencies;
	}

	void FMODAudioReverb::setLowShelfGain(float gain)
	{
		AudioReverb::setLowShelfGain(gain);

		prop.LowShelfGain = mLowShelfGain;
	}

	void FMODAudioReverb::setHighCut(float freq)
	{
		AudioReverb::setHighCut(freq);

		prop.HighCut = mHighCut;
	}

	void FMODAudioReverb::setEarlyLateMix(float elm)
	{
		AudioReverb::setEarlyLateMix(elm);

		prop.EarlyLateMix = mEarlyLateMix;
	}

	void FMODAudioReverb::setWetLevel(float level)
	{
		AudioReverb::setWetLevel(level);

		prop.WetLevel = mWetLevel;
	}

	void FMODAudioReverb::onClipChanged() 
	{
	
	}
}