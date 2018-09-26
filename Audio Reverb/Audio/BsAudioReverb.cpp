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

	void AudioReverb::setDiffusion(float diffusion)
	{
		mDiffusion = diffusion;
	}

	void AudioReverb::setDensity(float density)
	{
		mDensity = density;
	}

	void AudioReverb::setGain(float gain) 
	{
		mGain = gain;
	}

	void AudioReverb::setGainHF(float gain) 
	{
		mGainHF = gain;
	}

	void AudioReverb::setGainLF(float gain) 
	{
		mGainLF = gain;
	}

	void AudioReverb::setDecayTime(float time)
	{
		mDecayTime = time;
	}

	void AudioReverb::setDecayHFRatio(float ratio) 
	{
		mDecayHFRatio = ratio;
	}

	void AudioReverb::setDecayLFRatio(float ratio) 
	{
		mDecayLFRatio = ratio;
	}

	void AudioReverb::setReflectionGain(float gain) 
	{
		mReflectionGain = gain;
	}

	void AudioReverb::setReflectionDelay(float delay) 
	{
		mReflectionDelay = delay;
	}

	void AudioReverb::setReflectionPan(Vector3 pan) 
	{
		mReflectionPan = pan;
	}

	void AudioReverb::setLateReverbGain(float gain) 
	{
		mLateReverbGain = gain;
	}

	void AudioReverb::setLateReverbDelay(float delay) 
	{
		mLateReverbDelay = delay;
	}

	void AudioReverb::setLateReverbPan(Vector3 pan) 
	{
		mLateReverbPan = pan;
	}

	void AudioReverb::setEchoTime(float time) 
	{
		mEchoTime = time;
	}

	void AudioReverb::setEchoDepth(float depth) 
	{
		mEchoDepth = depth;
	}

	void AudioReverb::setModulationTime(float time) 
	{
		mModulationTime = time;
	}

	void AudioReverb::setModulationDepth(float depth) 
	{
		mModulationDepth = depth;
	}

	void AudioReverb::setHFReference(float hfref)
	{
		mHFReference = hfref;
	}

	void AudioReverb::setLFReference(float hfref) 
	{
		mLFReference = hfref;
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

	void AudioReverb::setRoomRolloffFactor(float factor) 
	{
		mRoomRolloffFactor = factor;
	}

	void AudioReverb::setAirAbsorptionGainHF(float gain) 
	{
		mAirAbsorptionGainHF = gain;
	}

	void AudioReverb::setDecayHFLimit(bool limit) 
	{
		mDecayHFLimit = limit;
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