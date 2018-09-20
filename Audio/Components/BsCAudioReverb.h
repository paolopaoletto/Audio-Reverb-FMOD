#pragma once

#include "BsCorePrerequisites.h"
#include "Audio/BsAudioReverb.h"
#include "Scene/BsComponent.h"

namespace bs 
{
	/** @addtogroup Components-Core
	 *  @{
	 */

	 /**
	  * @copydoc	AudioReverb
	  *
	  * @note Wraps AudioReverb as a Component.
	  */

	class BS_CORE_EXPORT BS_SCRIPT_EXPORT(m:Audio, m:AudioReverb) CAudioReverb : public Component 
	{
	public:
		CAudioReverb(const HSceneObject& parent);
		virtual ~CAudioReverb() {}

		/** @copydoc AudioReverb::setSource */
		BS_SCRIPT_EXPORT(n:Source,pr:setter)
		void setSource(const HAudioSource& source);

		/** @copydoc AudioReverb::getSource */
		BS_SCRIPT_EXPORT(n:Source,pr:getter)
		HAudioSource getSource() { return mSource; }

		/** @copydoc AudioReverb::setIR */
		BS_SCRIPT_EXPORT(n:IR,pr:setter)
		void setIR(const HAudioClip& clip);

		/** @copydoc AudioReverb::getIR */
		BS_SCRIPT_EXPORT(n:IR,pr:getter)
		HAudioClip getIR() { return mIr; }

		/** @copydoc AudioReverb::setWetVolume */
		BS_SCRIPT_EXPORT(n:WetVolume,pr:setter)
		void setWetVolume(float volume);

		/** @copydoc AudioReverb::getWetVolume */
		BS_SCRIPT_EXPORT(n:WetVolume,pr:getter)
		float getWetVolume() const { return mWetVolume; }

		/** @copydoc AudioReverb::setDryVolume */
		BS_SCRIPT_EXPORT(n:DryVolume,pr:setter)
		void setDryVolume(float volume);

		/** @copydoc AudioReverb::getDryVolume */
		BS_SCRIPT_EXPORT(n:DryVolume,pr:getter)
		float getDryVolume() const { return mDryVolume; }

		/** @copydoc AudioReverb::setDecayTime */
		BS_SCRIPT_EXPORT(n:DecayTime,pr:setter)
		void setDecayTime(float time);

		/** @copydoc AudioReverb::getDecayTime */
		BS_SCRIPT_EXPORT(n:DecayTime,pr:getter)
		float getDecayTime() const { return mDecayTime; }

		/** @copydoc AudioReverb::setEarlyDelay */
		BS_SCRIPT_EXPORT(n:EarlyDelay,pr:setter)
		void setEarlyDelay(float delay);

		/** @copydoc AudioReverb::getEarlyDelay */
		BS_SCRIPT_EXPORT(n:EarlyDelay,pr:getter)
		float getEarlyDelay() const { return mEarlyDelay; }

		/** @copydoc AudioReverb::setLateDelay */
		BS_SCRIPT_EXPORT(n:LateDelay,pr:setter)
		void setLateDelay(float delay);

		/** @copydoc AudioReverb::getLateDelay */
		BS_SCRIPT_EXPORT(n:LateDelay,pr:getter)
		float getLateDelay() const { return mLateDelay; }

		/** @copydoc AudioReverb::setHFReferemce */
		BS_SCRIPT_EXPORT(n:HFReference,pr:setter)
		void setHFReference(float hfref);

		/** @copydoc AudioReverb::getHFReference */
		BS_SCRIPT_EXPORT(n:HFReference,pr:getter)
		float getHFReference() const { return mHFReference; }

		/** @copydoc AudioReverb::setHFDecayRatio */
		BS_SCRIPT_EXPORT(n:HFDecayRatio,pr:setter)
		void setHFDecayRatio(float ratio);

		/** @copydoc AudioReverb::getHFReference */
		BS_SCRIPT_EXPORT(n:HFDecayRatio,pr:getter)
		float getHFDecayRatio() const { return mHFDecayRatio; }

		/** @copydoc AudioReverb::setDiffusion */
		BS_SCRIPT_EXPORT(n:Diffusion,pr:setter)
		void setDiffusion(float diffusion);

		/** @copydoc AudioReverb::getDiffusion */
		BS_SCRIPT_EXPORT(n:Diffusion,pr:getter)
		float getDiffusion() const { return mDiffusion; }

		/** @copydoc AudioReverb::setDensity */
		BS_SCRIPT_EXPORT(n:Density,pr:setter)
		void setDensity(float density);

		/** @copydoc AudioReverb::getDensity */
		BS_SCRIPT_EXPORT(n:Density,pr:getter)
		float getDensity() const { return mDensity; }

		/** @copydoc AudioReverb::setLowShelfFrequencies */
		BS_SCRIPT_EXPORT(n:LowShelfFrequencies,pr:setter)
		void setLowShelfFrequencies(float freq);

		/** @copydoc AudioReverb::getLowShelfFrequencies */
		BS_SCRIPT_EXPORT(n:LowShelfFrequencies,pr:getter)
		float getLowShelfFrequencies() const { return mLowShelfFrequencies; }

		/** @copydoc AudioReverb::setLowShelfGain */
		BS_SCRIPT_EXPORT(n:LowShelfGain,pr:setter)
		void setLowShelfGain(float gain);

		/** @copydoc AudioReverb::getLowShelfGain */
		BS_SCRIPT_EXPORT(n:LowShelfGain,pr:getter)
		float getLowShelfGain() const { return mLowShelfGain; }

		/** @copydoc AudioReverb::setHighCut */
		BS_SCRIPT_EXPORT(n:HighCut,pr:setter)
		void setHighCut(float freq);

		/** @copydoc AudioReverb::getHighCut */
		BS_SCRIPT_EXPORT(n:HighCut,pr:getter)
		float getHighCut() const { return mHighCut; }

		/** @copydoc AudioReverb::setEarlyLateMix */
		BS_SCRIPT_EXPORT(n:EarlyLateMix,pr:setter)
		void setEarlyLateMix(float elm);

		/** @copydoc AudioReverb::getEarlyLateMix */
		BS_SCRIPT_EXPORT(n:EarlyLateMix,pr:getter)
		float getEarlyLateMix() const { return mEarlyLateMix; }

		/** @copydoc AudioReverb::setWetLevel */
		BS_SCRIPT_EXPORT(n:WetLevel,pr:setter)
		void setWetLevel(float level);

		/** @copydoc AudioReverb::getWetLevel */
		BS_SCRIPT_EXPORT(n:WetLevel,pr:getter)
		float getWetLevel() const { return mWetLevel; }

		/** @copydoc AudioReverb::setReverbPreset */
		BS_SCRIPT_EXPORT(n:Preset,pr:setter)
		void setReverbPreset(AudioReverbPreset preset);

		/** @copydoc AudioReverb::getReverbPreset */
		BS_SCRIPT_EXPORT(n:WetLevel,pr:getter)
		AudioReverbPreset getReverbPreset() { return mPreset; }

		/** @name Internal
		 *  @{
		 */

		/** Returns the AudioReverb implementation wrapped by this component. */
		AudioReverb* _getInternal() const { return mInternal.get(); }

		/** @} */

		/************************************************************************/
		/* 						COMPONENT OVERRIDES                      		*/
		/************************************************************************/

	protected:
		friend class SceneObject;

		/** @copydoc Component::onInitialized() */
		void onInitialized() override;

		/** @copydoc Component::onDestroyed() */
		void onDestroyed() override;

		/** @copydoc Component::onDisabled() */
		void onDisabled() override;

		/** @copydoc Component::onEnabled() */
		void onEnabled() override;

		/** @copydoc Component::onTransformChanged() */
		void onTransformChanged(TransformChangedFlags flags) override;

		/** @copydoc Component::update() */
		void update() override;
	protected:
		using Component::destroyInternal;

		/** Creates the internal representation of the AudioReverb and restores the values saved by the Component. */
		void restoreInternal();

		/** Destroys the internal AudioReverb representation. */
		void destroyInternal();

		/**
		 * Updates the transform of the internal AudioReverb representation from the transform of the component's scene
		 * object.
		 */
		void updateTransform();

		SPtr<AudioReverb> mInternal;
		float mWetVolume = 1.0f;
		float mDryVolume = 1.0f;

		struct 
		{
			float mDecayTime = 500.0f;
			float mEarlyDelay = 5.0f;
			float mLateDelay = 9.0f;
			float mHFReference = 5000.f;
			float mHFDecayRatio = 40.0f;
			float mDiffusion = 100.0f;
			float mDensity = 100.0f;
			float mLowShelfFrequencies = 250.0f;
			float mLowShelfGain = 10.0f;
			float mHighCut = 20000.0f;
			float mEarlyLateMix = 50.0f;
			float mWetLevel = -8.0f;
		};

		HAudioSource mSource;
		HAudioClip mIr;

		AudioReverbPreset mPreset = AudioReverbPreset::SmallRoom;

		/************************************************************************/
		/* 								RTTI		                     		*/
		/************************************************************************/

	public:
		friend class AudioReverbRTTI;
		static RTTITypeBase* getRTTIStatic();
		RTTITypeBase* getRTTI() const override;

	protected:
		CAudioReverb();

	};
}