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
	enum class BS_SCRIPT_EXPORT(m:Audio) AudioReverbPreset 
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
	enum class BS_SCRIPT_EXPORT(m:Audio) AudioReverbPresetIR {
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

		/** Determines the reverberation decay time in ms unit measure. */
		virtual void setDecayTime(float time);

		/** @copydoc setDecayTime() */
		float getDecayTime() const { return mDecayTime; }

		/** 
		* Determines the initial reflection delay time
		* in ms unit measure.
		*/
		virtual void setEarlyDelay(float delay);

		/** @copydoc setEarlyDelay() */
		float getEarlyDelay() const { return mEarlyDelay; }

		/** 
		* Determines the late reverberation delay time relative to initial reflection 
		* in ms unit measure.
		*/
		virtual void setLateDelay(float delay);

		/** @copydoc setLateDelay() */
		float getLateDelay() const { return mLateDelay; }

		/** Determines the high frequencies of the reverb in unit Hz unit measure. */
		virtual void setHFReference(float hfref);

		/** @copydoc setHFReference() */
		float getHFReference() const { return mHFReference; }

		/** 
		* Determines the high-frequency to mid-frequency decay time ratio 
		* in % unit measure.
		*/
		virtual void setHFDecayRatio(float ratio);

		/** @copydoc setHFDecayRatio() */
		float getHFDecayRatio() const { return mHFDecayRatio; }

		/** 
		* Determines the value that controls the space density in the late reverberation decay.
		* in % unit measure.
		**/
		virtual void setDiffusion(float diffusion);

		/** @copydoc setDiffusion() */
		float getDiffusion() const { return mDiffusion; }

		/** 
		* Value that controls the modal density in the late reverberation decay.
		* in % unit measure.
		*/
		virtual void setDensity(float density);

		/** @copydoc setDensity() */
		float getDensity() const { return mDensity; }

		/** Determines the low frequency of the reverb in Hz unit measure. */
		virtual void setLowShelfFrequencies(float freq);

		/** @copydoc setLowShelfFrequencies() */
		float getLowShelfFrequencies() const { return mLowShelfFrequencies; }

		/** 
		* Determines the relative space level in the low frequencies 
		* in dB unit measure.
		*/
		virtual void setLowShelfGain(float gain);

		/** @copydoc setLowShelfGain() */
		float getLowShelfGain() const { return mLowShelfGain; }

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
		
		struct {
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

		bool mIsReverbIR = false;

		float mMinDistance = 10.0f;
		float mMaxDistance = 40.0f;
		Vector3 mPosition = { -10.0f, 0.0f, 0.0f };

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