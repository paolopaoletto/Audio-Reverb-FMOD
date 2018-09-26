#pragma once

#include "BsCorePrerequisites.h"
#include "Resources/BsIResourceListener.h"
#include "Scene/BsSceneActor.h"

namespace bs
{
	/** @addtogroup Audio
	*  @{
	*/

	/** List of preset to apply for the reverb. */
	enum class BS_SCRIPT_EXPORT(m :Audio) AudioReverbPreset
	{
		/** Custom presets. */
		SmallRoom,	 /**< Small Room preset. */
			MediumRoom,	 /**< Medium Room preset. */
			LargeRoom,	 /**< Large Room preset. */
			ForestTrees, /**< Forest preset. */
			Bunker,		 /**< Bunker preset. */

			/** FMOD presets. */
			Off,
			Generic,
			PaddedCell,
			Room,
			BathRoom,
			LivingRoom,
			StoneRoom,
			Auditorium,
			ConcertHall,
			Cave,
			Arena,
			Hangar,
			CarpetteHallway,
			Hallway,
			StoneCorridor,
			Alley,
			Forest,
			City,
			Mountains,
			Quarry,
			Plain,
			ParkingLot,
			Sewerpipe,
			Underwater
	};

	/**
	*List of preset to apply for the Convolution reverb.
	* Just temporary. it will be one enum sharing the same element.
	*/
	enum class BS_SCRIPT_EXPORT(m :Audio) AudioReverbPresetIR {
		SmallRoom,
			MediumRoom,
			LargeRoom,
			Ambience,
			Forest,
			Bunker,
			Hall,
			Chamber,
			Cathedral,
			Plate
	};

	/**
	* Interface of the reverb applied to sources on the scene.
	* There are two reverb variation:
	* Convolution Reverb is the one that takes an impulse response in .wav format, making the virtual space from it.
	* Algorithmic Reverb is the one generated from the algorithm integrated into the library.
	*/
	class BS_CORE_EXPORT AudioReverb : public IReflectable, public SceneActor, public IResourceListener
	{
	public:
		virtual ~AudioReverb();

		/** The source in which the reverb will apply on. */
		virtual void setSource(const HAudioSource& source);

		/** @copydoc setSource() */
		HAudioSource getSource() { return mSource; }

		/** The Impulse Response to make Convolution Reverb. */
		virtual void setIR(const HAudioClip& clip);

		/** @copydoc setIR() */
		HAudioClip getIR() { return mIr; }

		/** Determines the wet gain of the reverb. */
		virtual void setWetVolume(float volume);

		/** @copydoc setWetVolume() */
		float getWetVolume() const { return mWetVolume; }

		/** Determines the dry gain of the reverb. */
		virtual void setDryVolume(float volume);

		/** @copydoc setDryVolume() */
		float getDryVolume() const { return mDryVolume; }
		
		/** Determines the diffusion of the reverb. */
		virtual void setDiffusion(float diffusion);

		/** @copydoc setDiffusion() */
		float getDiffusion() const { return mDiffusion; }

		/** Determines the density of the reverb. */
		virtual void setDensity(float density);

		/** @copydoc setDensity() */
		float getDensity() const { return mDensity; }

		/** Determines the gain of the reverb. */
		virtual void setGain(float gain);

		/** @copydoc setGain() */
		float getGain() const { return mGain; }

		/** Determines the gain at high frequencies. */
		virtual void setGainHF(float gain);

		/** @copydoc setGainHF() */
		float getGainHF() const { return mGainHF; }

		/** Determines the gain at low frequencies. */
		virtual void setGainLF(float gain); 

		/** @copydoc setGainLF() */
		float getGainLF() const { return mGainLF; }

		/** Determines the reverberation decay time in ms unit measure. */
		virtual void setDecayTime(float time);

		/** @copydoc setDecayTime() */
		float getDecayTime() const { return mDecayTime; }

		/** Determines the decay ratio at high frequencies. */
		virtual void setDecayHFRatio(float ratio);

		/** @copydoc setDecayHFRatio() */
		float getDecayHFRatio() const { return mDecayHFRatio; }

		/** Determines the decay ratio at low frequencies. */
		virtual void setDecayLFRatio(float ratio);

		/** @copydoc setDecayLFRatio() */
		float getDecayLFRatio() const { return mDecayLFRatio; }

		/** Determines the reflection gain of the reverb. */
		virtual void setReflectionGain(float gain);

		/** @copydoc setReflectionGain() */
		float getReflectionGain() const { return mReflectionGain; }

		/** Determines the reflection delay of the reverb. */
		virtual void setReflectionDelay(float delay);

		/** @copydoc setReflectionDelay() */
		float getReflectionDelay() const { return mReflectionDelay; }

		/** Determines the reflection pan of the reverb. */
		virtual void setReflectionPan(Vector3 pan);

		/** @copydoc setReflectionPan() */
		Vector3 getReflectionPan() const { return mReflectionPan; }

		/** Determines the late reflection gain of the reverb. */
		virtual void setLateReverbGain(float gain);

		/** @copydoc setLateReverbGain() */
		float getLateReverbGain() const { return mLateReverbGain; }

		/** Determines the late reflection delay of the reverb. */
		virtual void setLateReverbDelay(float delay);

		/** @copydoc setLateReverbDelay() */
		float setLateReverbDelay() const { return mLateReverbDelay; }

		/** Determines the late reflection pan of the reverb. */
		virtual void setLateReverbPan(Vector3 pan);

		/** @copydoc setLateReverbPan() */
		Vector3 getLateReverbPan() const { return mLateReverbPan; }

		/** Determines the echo time of the reverb. */
		virtual void setEchoTime(float time);

		/** @copydoc setEchoTime() */
		float getEchoTime() const { return mEchoTime; }

		/** Determines the echo depth of the reverb. */
		virtual void setEchoDepth(float depth);

		/** @copydoc setEchoDepth() */
		float getEchoDepth() const { return mEchoDepth; }

		/** Determines the modulation time of the reverb. */
		virtual void setModulationTime(float time);

		/** @copydoc setModulationTime() */
		float getModulationTime() const { return mModulationTime; }

		/** Determines the modulation depth of the reverb. */
		virtual void setModulationDepth(float depth);

		/** @copydoc setModulationDepth() */
		float getModulationDepth() const { return mModulationDepth; }

		/** Determines the reference at high frequencies. */
		virtual void setHFReference(float hfref);

		/** @copydoc setHFReference() */
		float getHFReference() const { return mHFReference; }

		/** Determines the reference at low frequencies. */
		virtual void setLFReference(float freq);

		/** @copydoc setLFReference() */
		float setLFReference() const { return mLFReference; }

		/**
		* Determines the relative space level at high frequencies
		* in Hz unit measure.
		*/
		virtual void setHighCut(float freq);

		/** @copydoc setHighCut() */
		float getHighCut() const { return mHighCut; }

		/**
		*Determines early reflections level relative to room effect
		* in % unit measure.
		*/
		virtual void setEarlyLateMix(float elm);

		/** @copydoc setEarlyLateMix() */
		float getEarlyLateMix() const { return mEarlyLateMix; }

		/**
		Determines the room effect level at mid frequencies
		*in dB unit measure.
		*/
		virtual void setWetLevel(float level);

		/** @copydoc setWetLevel() */
		float getWetLevel() const { return mWetLevel; }

		/** Determines the Room Rooloff Factor of the reverb. */
		virtual void setRoomRolloffFactor(float factor);

		/** @copydoc setRoomRolloffFactor() */
		float setRoomRolloffFactor() const { return mRoomRolloffFactor; }

		/** Determines the air absorption gain at high frequencies. */
		virtual void setAirAbsorptionGainHF(float gain);
		
		/** @copydoc setAirAbsorptionGainHF() */
		float getAirAbsorptionGainHF() const { return mAirAbsorptionGainHF; }

		/** Determines the decay limit at high frequencies. */
		virtual void setDecayHFLimit(bool limit); 

		/** @copydoc setDecayHFLimit() */
		bool getDecayHFLimit() const { return mDecayHFLimit; }

		/**
		* Boolean to determines which reverb to use.
		* if false: Algorithmic Reverb (Default)
		* else: Convolution Reverb
		*/
		bool isReverbIR() const { return mIsReverbIR; }

		/** Determines the reverb preset to use. */
		virtual void setReverbPreset(AudioReverbPreset preset);

		/** @copydoc setReverbPreset() */
		AudioReverbPreset getReverbPreset() { return mPreset; }

		/** Set the position of the reverb. */
		virtual void setPosition(Vector3 position);

		/** @copydoc setPosition() */
		Vector3 getPosition() { return mPosition; }

		/** Determines the minimum distance of the reverb from the source. */
		virtual void setMinDistance(float distance);

		/** @copydoc setMinDistance() */
		float getMinDistance(float distance) { return mMinDistance; };

		/** Determines the maximum distance of the reverb from the source. */
		virtual void setMaxDistance(float distance);

		/** @copydoc setMaxDistance() */
		float getMaxDistance(float distance) { return mMaxDistance; }

		/** Creates a new audio reverb. */
		static SPtr<AudioReverb> create();

	protected:
		AudioReverb();

		/** @copydoc IResourceListener::getListenerResources */
		void getListenerResources(Vector<HResource>& resources) override;

		/** @copydoc IResourceListener::notifyResourceChanged */
		void notifyResourceChanged(const HResource& resource) override;

		/** Triggered by the resources system whenever the attached audio clip changed (e.g. was reimported.) */
		virtual void onClipChanged() { }

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

		bool mIsReverbIR = false;

		Vector3 mPosition = { -10.0f, 0.0f, 0.0f };
		float mMinDistance = 10.0f;
		float mMaxDistance = 40.0f;

		/************************************************************************/
		/* 								RTTI		                     		*/
		/************************************************************************/
	public:
		friend class AudioReverbRTTI;
		static RTTITypeBase* getRTTIStatic();
		RTTITypeBase* getRTTI() const override;
	};

	/** @} */
}