#include "Components/BsCAudioReverb.h"
#include "Scene/BsSceneObject.h"
#include "Private/RTTI/BsCAudioReverbRTTI.h"

namespace bs
{
	CAudioReverb::CAudioReverb()
	{
		setName("AudioReverb");

		mNotifyFlags = TCF_Transform;
	}

	CAudioReverb::CAudioReverb(const HSceneObject& parent)
		: Component(parent)
	{
		setName("AudioReverb");

		mNotifyFlags = TCF_Transform;
	}

	void CAudioReverb::setSource(const HAudioSource& source)
	{
		if (mSource == source)
			return;

		mSource = source;

		if (mInternal != nullptr)
			mInternal->setSource(source);
	}

	void CAudioReverb::setIR(const HAudioClip& clip)
	{
		if (mIr == clip)
			return;

		mIr = clip;

		if (mInternal != nullptr)
			mInternal->setIR(clip);
	}

	void CAudioReverb::setDryVolume(float volume)
	{
		if (mDryVolume == volume)
			return;

		mDryVolume = volume;

		if (mInternal != nullptr)
			mInternal->setDryVolume(volume);
	}

	void CAudioReverb::setDiffusion(float diffusion)
	{
		if (mDiffusion == diffusion)
			return;

		mDiffusion = diffusion;

		if (mInternal != nullptr)
			mInternal->setDiffusion(diffusion);
	}

	void CAudioReverb::setDensity(float density)
	{
		if (mDensity == density)
			return;

		mDensity = density;

		if (mInternal != nullptr)
			mInternal->setDensity(density);
	}

	void CAudioReverb::setGain(float gain) 
	{
		if (mGain == gain)
			return;

		mGain = gain;

		if (mInternal != nullptr)
			mInternal->setGain(gain);
	}

	void CAudioReverb::setGainHF(float gain) 
	{
		if (mGainHF == gain)
			return;

		mGainHF = gain;

		if (mInternal != nullptr)
			mInternal->setGainHF(gain);
	}

	void CAudioReverb::setGainLF(float gain) 
	{
		if (mGainLF == gain)
			return;

		mGainLF = gain;

		if (mInternal != nullptr)
			mInternal->setGainLF(gain);
	}

	void CAudioReverb::setDecayTime(float time)
	{
		if (mDecayTime == time)
			return;

		mDecayTime = time;

		if (mInternal != nullptr)
			mInternal->setDecayTime(time);
	}

	void CAudioReverb::setDecayHFRatio(float ratio) 
	{
		if (mDecayHFRatio == ratio)
			return;

		mDecayHFRatio = ratio;

		if (mInternal != nullptr)
			mInternal->setDecayHFRatio(ratio);
	}

	void CAudioReverb::setDecayLFRatio(float ratio) 
	{
		if (mDecayLFRatio == ratio)
			return;

		mDecayLFRatio = ratio;

		if (mInternal != nullptr)
			mInternal->setDecayLFRatio(ratio);
	}

	void CAudioReverb::setReflectionGain(float gain) 
	{
		if (mReflectionGain == gain)
			return;

		mReflectionGain = gain;

		if (mInternal != nullptr)
			mInternal->setReflectionGain(gain);
	}

	void CAudioReverb::setReflectionDelay(float delay)
	{
		if (mReflectionDelay == delay)
			return;

		mReflectionDelay = delay;

		if (mInternal != nullptr)
			mInternal->setReflectionDelay(delay);
	}

	void CAudioReverb::setReflectionPan(Vector3 pan)
	{
		if (mReflectionPan == pan)
			return;

		mReflectionPan = pan;

		if (mInternal != nullptr)
			mInternal->setReflectionPan(pan);
	}

	void CAudioReverb::setLateReverbGain(float gain) 
	{
		if (mLateReverbGain == gain)
			return;

		mLateReverbGain = gain;

		if (mInternal != nullptr)
			mInternal->setLateReverbGain(gain);
	}

	void CAudioReverb::setLateReverbDelay(float delay)
	{
		if (mLateReverbDelay == delay)
			return;

		mLateReverbDelay = delay;

		if (mInternal != nullptr)
			mInternal->setLateReverbDelay(delay);
	}

	void CAudioReverb::setLateReverbPan(Vector3 pan)
	{
		if (mLateReverbPan == pan)
			return;

		mLateReverbPan = pan;

		if (mInternal != nullptr)
			mInternal->setLateReverbPan(pan);
	}

	void CAudioReverb::setEchoTime(float time) 
	{
		if (mEchoTime == time)
			return;

		mEchoTime = time;

		if (mInternal != nullptr)
			mInternal->setEchoTime(time);
	}

	void CAudioReverb::setEchoDepth(float depth)
	{
		if (mEchoDepth == depth)
			return;

		mEchoDepth = depth;

		if (mInternal != nullptr)
			mInternal->setEchoDepth(depth);
	}

	void CAudioReverb::setModulationTime(float time) 
	{
		if (mModulationTime == time)
			return;

		mModulationTime = time;

		if (mInternal != nullptr)
			mInternal->setModulationTime(time);
	}

	void CAudioReverb::setModulationDepth(float depth)
	{
		if (mModulationDepth == depth)
			return;

		mModulationDepth = depth;

		if (mInternal != nullptr)
			mInternal->setModulationDepth(depth);
	}

	void CAudioReverb::setHFReference(float hfref)
	{
		if (mHFReference == hfref)
			return;

		mHFReference = hfref;

		if (mInternal != nullptr)
			mInternal->setHFReference(hfref);
	}

	void CAudioReverb::setLFReference(float hfref)
	{
		if (mLFReference == hfref)
			return;

		mLFReference = hfref;

		if (mInternal != nullptr)
			mInternal->setLFReference(hfref);
	}

	void CAudioReverb::setHighCut(float freq)
	{
		if (mHighCut == freq)
			return;

		mHighCut = freq;

		if (mInternal != nullptr)
			mInternal->setHighCut(freq);
	}

	void CAudioReverb::setEarlyLateMix(float elm)
	{
		if (mEarlyLateMix == elm)
			return;

		mEarlyLateMix = elm;

		if (mInternal != nullptr)
			mInternal->setEarlyLateMix(elm);
	}

	void CAudioReverb::setWetLevel(float level)
	{
		if (mWetLevel == level)
			return;

		mWetLevel = level;

		if (mInternal != nullptr)
			mInternal->setWetLevel(level);
	}

	void CAudioReverb::setRoomRolloffFactor(float factor) 
	{
		if (mRoomRolloffFactor == factor)
			return;

		mRoomRolloffFactor = factor;

		if (mInternal != nullptr)
			mInternal->setRoomRolloffFactor(factor);
	}

	void CAudioReverb::setAirAbsorptionGainHF(float gain) 
	{
		if (mAirAbsorptionGainHF == gain)
			return;

		mAirAbsorptionGainHF = gain;

		if (mInternal != nullptr)
			mInternal->setAirAbsorptionGainHF(gain);
	}

	void CAudioReverb::setDecayHFLimit(bool limit) 
	{
		if (mDecayHFLimit == limit)
			return;

		mDecayHFLimit = limit;

		if (mInternal != nullptr)
			mInternal->setDecayHFLimit(limit);
	}

	void CAudioReverb::setReverbPreset(AudioReverbPreset preset)
	{
		if (mPreset == preset)
			return;

		mPreset = preset;

		if (mInternal != nullptr)
			mInternal->setReverbPreset(preset);
	}

	void CAudioReverb::setPosition(Vector3 position) 
	{
		if (mPosition == position)
			return;

		mPosition = position;

		if (mInternal != nullptr)
			mInternal->setPosition(position);
	}

	void CAudioReverb::setMinDistance(float distance) 
	{
		if (mMinDistance == distance)
			return;

		mMinDistance = distance;

		if (mInternal != nullptr)
			mInternal->setMinDistance(distance);
	}

	void CAudioReverb::setMaxDistance(float distance) 
	{
		if (mMaxDistance == distance)
			return;

		mMaxDistance = distance;

		if (mInternal != nullptr)
			mInternal->setMaxDistance(distance);
	}

	void CAudioReverb::onInitialized()
	{

	}

	void CAudioReverb::onDestroyed()
	{
		destroyInternal();
	}

	void CAudioReverb::onDisabled()
	{
		destroyInternal();
	}

	void CAudioReverb::onEnabled()
	{
		restoreInternal();
	}

	void CAudioReverb::onTransformChanged(TransformChangedFlags flags)
	{
		if (!SO()->getActive())
			return;

		if ((flags & (TCF_Parent | TCF_Transform)) != 0)
			updateTransform();
	}

	void CAudioReverb::update()
	{
		// TODO: update position of the reverb. 
	}

	void CAudioReverb::restoreInternal()
	{
		if (mInternal == nullptr)
			mInternal = AudioReverb::create();

		mInternal->setSource(mSource);
		mInternal->setIR(mIr);
		mInternal->setWetVolume(mWetVolume);
		mInternal->setDryVolume(mDryVolume);
		mInternal->setDecayTime(mDecayTime);
		mInternal->setHFReference(mHFReference);
		mInternal->setDiffusion(mDiffusion);
		mInternal->setDensity(mDensity);
		mInternal->setHighCut(mHighCut);
		mInternal->setEarlyLateMix(mEarlyLateMix);
		mInternal->setWetLevel(mWetLevel);
		mInternal->setReverbPreset(mPreset);

		updateTransform();
	}

	void CAudioReverb::destroyInternal()
	{
		mInternal = nullptr;
	}

	void CAudioReverb::updateTransform()
	{
		mInternal->setTransform(SO()->getTransform());
	}

	RTTITypeBase* CAudioReverb::getRTTIStatic()
	{
		return CAudioReverbRTTI::instance();
	}

	RTTITypeBase* CAudioReverb::getRTTI() const
	{
		return CAudioReverb::getRTTIStatic();
	}

}