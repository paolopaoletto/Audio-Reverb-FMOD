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

	class BS_CORE_EXPORT BS_SCRIPT_EXPORT(m:Audio, n:AudioReverb) CAudioReverb : public Component 
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

		/** @copydoc AudioReverb::setGain */
		BS_SCRIPT_EXPORT(n:Gain,pr:setter)
		void setGain(float gain);

		/** @copydoc AudioReverb::getGainHF */
		BS_SCRIPT_EXPORT(n:Gain,pr:getter)
		float getGain() const { return mGain; }

		/** @copydoc AudioReverb::setGainHF */
		BS_SCRIPT_EXPORT(n:GainHF,pr:setter)
		void setGainHF(float gain);

		/** @copydoc AudioReverb::getGainHF */
		BS_SCRIPT_EXPORT(n:GainHF,pr:getter)
		float getGainHF() const { return mGainHF; }

		/** @copydoc AudioReverb::setGainLF */
		BS_SCRIPT_EXPORT(n:GainLF,pr:setter)
		void setGainLF(float gain);
		
		/** @copydoc AudioReverb::getGainLF */
		BS_SCRIPT_EXPORT(n:GainLF,pr:getter)
		float getGainLF() const { return mGainLF; }

		/** @copydoc AudioReverb::setDecayTime */
		BS_SCRIPT_EXPORT(n:DecayTime,pr:setter)
		void setDecayTime(float time);

		/** @copydoc AudioReverb::getDecayTime */
		BS_SCRIPT_EXPORT(n:DecayTime,pr:getter)
		float getDecayTime() const { return mDecayTime; }

		/** @copydoc AudioReverb::setDecayHFRatio */
		BS_SCRIPT_EXPORT(n:DecayHFRatio,pr:setter)
		void setDecayHFRatio(float ratio);

		/** @copydoc AudioReverb::getDecayHFRatio */
		BS_SCRIPT_EXPORT(n:DecayHFRatio,pr:getter)
		float getDecayHFRatio() const { return mDecayHFRatio; }

		/** @copydoc AudioReverb::setDecayLFRatio */
		BS_SCRIPT_EXPORT(n:DecayLFRatio,pr:setter)
		void setDecayLFRatio(float ratio);

		/** @copydoc AudioReverb::getDecayLFRatio */
		BS_SCRIPT_EXPORT(n:DecayLFRatio,pr:getter)
		float getDecayLFRatio() const { return mDecayLFRatio; }

		/** @copydoc AudioReverb::setReflectionGain */
		BS_SCRIPT_EXPORT(n:ReflectionGain,pr:setter)
		void setReflectionGain(float gain);

		/** @copydoc AudioReverb::getReflectionGain */
		BS_SCRIPT_EXPORT(n:ReflectionGain,pr:getter)
		float getReflectionGain() const { return mReflectionGain; }

		/** @copydoc AudioReverb::setReflectionDelay */
		BS_SCRIPT_EXPORT(n:ReflectionDelay,pr:setter)
		void setReflectionDelay(float delay);

		/** @copydoc AudioReverb::getReflectionDelay */
		BS_SCRIPT_EXPORT(n:ReflectionDelay,pr:getter)
		float getReflectionDelay() const { return mReflectionDelay; }

		/** @copydoc AudioReverb::setReflectionPan */
		BS_SCRIPT_EXPORT(n:ReflectionPan,pr:setter)
		void setReflectionPan(Vector3 pan);

		/** @copydoc AudioReverb::getReflectionPan */
		BS_SCRIPT_EXPORT(n:ReflectionPan,pr:getter)
		Vector3 getReflectionPan() const { return mReflectionPan; }

		/** @copydoc AudioReverb::setLateReverbGain */
		BS_SCRIPT_EXPORT(n:LateReverbGain,pr:setter)
		void setLateReverbGain(float gain);

		/** @copydoc AudioReverb::getLateReverbGain */
		BS_SCRIPT_EXPORT(n:LateReverbGain,pr:getter)
		float getLateReverbGain() const { return mLateReverbGain; }

		/** @copydoc AudioReverb::setLateReverbDelay */
		BS_SCRIPT_EXPORT(n:LateReverbDelay,pr:setter)
		void setLateReverbDelay(float delay);

		/** @copydoc AudioReverb::getLateReverbDelay */
		BS_SCRIPT_EXPORT(n:LateReverbDelay,pr:getter)
		float setLateReverbDelay() const { return mLateReverbDelay; }

		/** @copydoc AudioReverb::setLateReverbPan */
		BS_SCRIPT_EXPORT(n:LateReverbPan,pr:setter)
		void setLateReverbPan(Vector3 pan);

		/** @copydoc AudioReverb::getLateReverbPan */
		BS_SCRIPT_EXPORT(n:LateReverbPan,pr:getter)
		Vector3 getLateReverbPan() const { return mLateReverbPan; }

		/** @copydoc AudioReverb::setEchoTime */
		BS_SCRIPT_EXPORT(n:EchoTime,pr:setter)
		void setEchoTime(float time);

		/** @copydoc AudioReverb::getEchoTime */
		BS_SCRIPT_EXPORT(n:EchoTime,pr:getter)
		float getEchoTime() const { return mEchoTime; }

		/** @copydoc AudioReverb::setEchoDepth */
		BS_SCRIPT_EXPORT(n:EchoDepth,pr:setter)
		void setEchoDepth(float depth);

		/** @copydoc AudioReverb::getEchoDepth */
		BS_SCRIPT_EXPORT(n:EchoDepth,pr:getter)
		float getEchoDepth() const { return mEchoDepth; }

		/** @copydoc AudioReverb::setModulationTime */
		BS_SCRIPT_EXPORT(n:ModulationTime,pr:setter)
		void setModulationTime(float time);

		/** @copydoc AudioReverb::getModulationTime */
		BS_SCRIPT_EXPORT(n:ModulationTime,pr:getter)
		float getModulationTime() const { return mModulationTime; }

		/** @copydoc AudioReverb::setModulationDepth */
		BS_SCRIPT_EXPORT(n:ModulationDepth,pr:setter)
		void setModulationDepth(float depth);

		/** @copydoc AudioReverb::getModulationDepth */
		BS_SCRIPT_EXPORT(n:ModulationDepth,pr:getter)
		float getModulationDepth() const { return mModulationDepth; }

		/** @copydoc AudioReverb::setHFReference */
		BS_SCRIPT_EXPORT(n:HFReference,pr:setter)
		void setHFReference(float hfref);

		/** @copydoc AudioReverb::getHFReference */
		BS_SCRIPT_EXPORT(n:HFReference,pr:getter)
		float getHFReference() const { return mHFReference; }

		/** @copydoc AudioReverb::setLFReference */
		BS_SCRIPT_EXPORT(n:LFReference,pr:setter)
		void setLFReference(float freq);

		/** @copydoc AudioReverb::getLFReference */
		BS_SCRIPT_EXPORT(n:LFReference,pr:getter)
		float setLFReference() const { return mLFReference; }

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

		/** @copydoc AudioReverb::setRoomRolloffFactor */
		BS_SCRIPT_EXPORT(n:RoomRolloffFactor,pr:setter)
		void setRoomRolloffFactor(float factor);

		/** @copydoc AudioReverb::getRoomRolloffFactor */
		BS_SCRIPT_EXPORT(n:RoomRolloffFactor,pr:getter)
		float setRoomRolloffFactor() const { return mRoomRolloffFactor; }

		/** @copydoc AudioReverb::setAirAbsorptionGainHF */
		BS_SCRIPT_EXPORT(n:AirAbsorptionGainHF,pr:setter)
		void setAirAbsorptionGainHF(float gain);

		/** @copydoc AudioReverb::getAirAbsorptionGainHF */
		BS_SCRIPT_EXPORT(n:AirAbsorptionGainHF,pr:getter)
		float getAirAbsorptionGainHF() const { return mAirAbsorptionGainHF; }

		/** @copydoc AudioReverb::setDecayHFLimit */
		BS_SCRIPT_EXPORT(n:DecayHFLimit,pr:setter)
		void setDecayHFLimit(bool limit);

		/** @copydoc AudioReverb::getDecayHFLimit */
		BS_SCRIPT_EXPORT(n:DecayHFLimit:,pr:getter)
		bool getDecayHFLimit() const { return mDecayHFLimit; }

		/** @copydoc AudioReverb::setReverbPreset */
		BS_SCRIPT_EXPORT(n:Preset,pr:setter)
		void setReverbPreset(AudioReverbPreset preset);

		/** @copydoc AudioReverb::getReverbPreset */
		BS_SCRIPT_EXPORT(n:WetLevel,pr:getter)
		AudioReverbPreset getReverbPreset() { return mPreset; }

		/** @copydoc AudioReverb::setPosition */
		BS_SCRIPT_EXPORT(n:Position,pr:setter)
		void setPosition(Vector3 position);

		/** @copydoc AudioReverb::getPosition */
		BS_SCRIPT_EXPORT(n:Position,pr:getter)
		Vector3 getPosition() { return mPosition; }

		/** @copydoc AudioReverb::setMinDistance */
		BS_SCRIPT_EXPORT(n:MinDistance,pr:setter)
		virtual void setMinDistance(float distance);

		/** @copydoc AudioReverb::getMinDistance */
		BS_SCRIPT_EXPORT(n:MinDistance,pr:getter)
		float getMinDistance(float distance) { return mMinDistance; };

		/** @copydoc AudioReverb::setMaxDistance */
		BS_SCRIPT_EXPORT(n:MaxDistance,pr:setter)
		virtual void setMaxDistance(float distance);

		/** @copydoc AudioReverb::getMaxDistance */
		BS_SCRIPT_EXPORT(n:MaxDistance,pr:getter)
		float getMaxDistance(float distance) { return mMaxDistance; }

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
			float mDiffusion = 100.0f;
			float mDensity = 100.f;
			float mGain = 0.32f;
			float mGainHF = 0.89f;
			float mGainLF = 0.0f;
			float mDecayTime = 1.1f;
			float mDecayHFRatio = 0.83f;
			float mDecayLFRatio = 1.0f;
			float mReflectionGain = 0.05f;
			float mReflectionDelay = 0.007f;
			Vector3 mReflectionPan = Vector3::ZERO;
			float mLateReverbGain = 1.26f;
			float mLateReverbDelay = 0.01f;
			Vector3 mLateReverbPan = Vector3::ZERO;
			float mEchoTime = 0.25f;
			float mEchoDepth = 0.0f;
			float mModulationTime = 0.25f;
			float mModulationDepth = 0.0f;
			float mHFReference = 5000.0f;
			float mLFReference = 250.0f;
			float mHighCut = 20000.0f;
			float mEarlyLateMix = 50.0f;
			float mWetLevel = -8.0f;
			float mRoomRolloffFactor = 1.0f;
			float mAirAbsorptionGainHF = 0.994f;
			bool mDecayHFLimit = true;
		};

		HAudioSource mSource;
		HAudioClip mIr;

		AudioReverbPreset mPreset = AudioReverbPreset::SmallRoom;

		Vector3 mPosition = { -10.0f, 0.0f, 0.0f };
		float mMinDistance = 10.0f;
		float mMaxDistance = 40.0f;

		/************************************************************************/
		/* 								RTTI		                     		*/
		/************************************************************************/

	public:
		friend class CAudioReverbRTTI;
		static RTTITypeBase* getRTTIStatic();
		RTTITypeBase* getRTTI() const override;

	protected:
		CAudioReverb();

	};
}