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

	void CAudioReverb::setDecayTime(float time)
	{
		if (mDecayTime == time)
			return;

		mDecayTime = time;

		if (mInternal != nullptr)
			mInternal->setDecayTime(time);
	}

	void CAudioReverb::setEarlyDelay(float delay)
	{
		if (mEarlyDelay == delay)
			return;

		mEarlyDelay = delay;

		if (mInternal != nullptr)
			mInternal->setEarlyDelay(delay);
	}

	void CAudioReverb::setLateDelay(float delay)
	{
		if (mLateDelay == delay)
			return;

		mLateDelay = delay;

		if (mInternal != nullptr)
			mInternal->setLateDelay(delay);
	}

	void CAudioReverb::setHFReference(float hfref)
	{
		if (mHFReference == hfref)
			return;

		mHFReference = hfref;

		if (mInternal != nullptr)
			mInternal->setHFReference(hfref);
	}

	void CAudioReverb::setHFDecayRatio(float ratio)
	{
		if (mHFDecayRatio == ratio)
			return;

		mHFDecayRatio = ratio;

		if (mInternal != nullptr)
			mInternal->setHFDecayRatio(ratio);
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

	void CAudioReverb::setLowShelfFrequencies(float freq)
	{
		if (mLowShelfFrequencies == freq)
			return;

		mLowShelfFrequencies = freq;

		if (mInternal != nullptr)
			mInternal->setLowShelfFrequencies(freq);
	}

	void CAudioReverb::setLowShelfGain(float gain)
	{
		if (mLowShelfGain == gain)
			return;

		mLowShelfGain = gain;

		if (mInternal != nullptr)
			mInternal->setLowShelfGain(gain);
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

	void CAudioReverb::setReverbPreset(AudioReverbPreset preset)
	{
		if (mPreset == preset)
			return;

		mPreset = preset;

		if (mInternal != nullptr)
			mInternal->setReverbPreset(preset);
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
		mInternal->setEarlyDelay(mEarlyDelay);
		mInternal->setLateDelay(mLateDelay);
		mInternal->setHFReference(mHFReference);
		mInternal->setHFDecayRatio(mHFDecayRatio);
		mInternal->setDiffusion(mDiffusion);
		mInternal->setDensity(mDensity);
		mInternal->setLowShelfFrequencies(mLowShelfFrequencies);
		mInternal->setLowShelfFrequencies(mLowShelfGain);
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