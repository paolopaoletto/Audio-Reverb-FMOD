#include "BsAudioReverb.h"
#include "Audio/BsAudio.h"
#include "Private/RTTI/BsAudioReverbRTTI.h"

namespace bs {

	AudioReverb::AudioReverb()
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
		mIsReverbIR = true;

		markListenerResourcesDirty();
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

	void AudioReverb::setPosition(Vector3 position)
	{
		mPosition = position;
	}

	void AudioReverb::setMinDistance(float distance)
	{
		mMinDistance = distance;
	}

	void AudioReverb::setMaxDistance(float distance)
	{
		mMaxDistance = distance;
	}

	SPtr<AudioReverb> AudioReverb::create() 
	{
		return gAudio().createReverb();
	}

	void AudioReverb::getListenerResources(Vector<HResource>& resources) 
	{
		if (mIr != nullptr)
			resources.push_back(mIr);
	}

	void AudioReverb::notifyResourceChanged(const HResource& resource) 
	{
		onClipChanged();
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