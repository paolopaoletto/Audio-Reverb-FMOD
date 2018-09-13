#include "BsAudioReverb.h"
#include "Audio/BsAudio.h"
#include "Private/RTTI/BsAudioReverbRTTI.h"

namespace bs {

	AudioReverb::AudioReverb()
		: mWetVolume(1.0f), mDryVolume(1.0f), mIsReverbIR(false), 
		mPreset(AudioReverbPreset::SmallRoom),
		mDecayTime(500.0f), mEarlyDelay(5.0f), mLateDelay(9.0f),
		mHFReference(5000.0f), mHFDecayRatio(40.0f), mDiffusion(100.0f),
		mDensity(100.0f), mLowShelfFrequencies(250.0f), mLowShelfGain(10.0f),
		mHighCut(20000.0f), mEarlyLateMix(50.0f), mWetLevel(-8.0f)
	{

	}

	AudioReverb::~AudioReverb() {
	
	}

	void AudioReverb::setSource(const HAudioSource& source) 
	{
		mSource = source;
	}

	void AudioReverb::setIR(const HAudioClip& clip) 
	{
		mIr = clip;
	}

	void AudioReverb::setWetVolume(float volume) 
	{
		mWetVolume = volume;
	}

	void AudioReverb::setDryVolume(float volume) 
	{
		mDryVolume = volume;
	}

	void AudioReverb::setDecayTime(float time) 
	{
		mDecayTime = time;
	}

	void AudioReverb::setEarlyDelay(float delay) 
	{
		mEarlyDelay = delay;
	}

	void AudioReverb::setLateDelay(float delay) 
	{
		mLateDelay = delay;
	}

	void AudioReverb::setHFReference(float hfref) 
	{
		mHFReference = hfref;
	}

	void AudioReverb::setHFDecayRatio(float ratio) 
	{
		mHFDecayRatio = ratio;
	}

	void AudioReverb::setDiffusion(float diffusion) 
	{
		mDiffusion = diffusion;
	}

	void AudioReverb::setDensity(float density) 
	{
		mDensity = density;
	}

	void AudioReverb::setLowShelfFrequencies(float freq) 
	{
		mLowShelfFrequencies = freq;
	}

	void AudioReverb::setLowShelfGain(float gain) 
	{
		mLowShelfGain = gain;
	}

	void AudioReverb::setHighCut(float freq) 
	{
		mHighCut = freq;
	}

	void AudioReverb::setEarlyLateMix(float elm) 
	{
		mEarlyLateMix = elm;
	}

	void AudioReverb::setWetLevel(float level) 
	{
		mWetLevel = level;
	}

	void AudioReverb::setReverbPreset(AudioReverbPreset preset) 
	{
		mPreset = preset;
	}

	SPtr<AudioReverb> AudioReverb::create() 
	{
		return gAudio().createReverb();
	}

	RTTITypeBase* AudioReverb::getRTTIStatic()
	{
		return AudioReverbRTTI::instance();
	}

	RTTITypeBase* AudioReverb::getRTTI() const
	{
		return AudioReverb::getRTTIStatic();
	}
}