#pragma once

#include "BsOAPrerequisites.h"
#include "BsOAAudio.h"
#include "Audio/BsAudioReverb.h"
#include "BsOAEffectsObjects.h"

namespace bs {

	class OAAudioReverb : public AudioReverb {
	public:
		OAAudioReverb();
		virtual ~OAAudioReverb();

		/** @copydoc AudioReverb::setSource */
		void setSource(const HAudioSource& source) override;

		/** @copydoc AudioReverb::setIR */
		void setIR(const HAudioClip& clip) override;

		/** @copydoc AudioReverb::setWetVolume */
		void setWetVolume(float volume) override;

		/** @copydoc AudioReverb::setDryVolume */
		void setDryVolume(float volume) override;

		/** @copydoc AudioReverb::setDecayTime */
		void setDecayTime(float time) override;

		/** @copydoc AudioReverb::setEarlyDelay */
		void setEarlyDelay(float delay) override;

		/** @copydoc AudioReverb::setLateDelay */
		void setLateDelay(float delay) override;

		/** @copydoc AudioReverb::setHFReference */
		void setHFReference(float hfref) override;

		/** @copydoc AudioReverb::setHFDecayRatio */
		void setHFDecayRatio(float ratio) override;

		/** @copydoc AudioReverb::setDiffusion */
		void setDiffusion(float diffusion) override;

		/** @copydoc AudioReverb::setDensity */
		void setDensity(float density) override;

		/** @copydoc AudioReverb::setLowShelfFrequencies */
		void setLowShelfFrequencies(float freq) override;

		/** @copydoc AudioReverb::setLowShelfGain */
		void setLowShelfGain(float gain) override;

		/** @copydoc AudioReverb::setHighCut */
		void setHighCut(float freq) override;

		/** @copydoc AudioReverb::setEarlyLateMix */
		void setEarlyLateMix(float elm) override;

		/** @copydoc AudioReverb::setWetLevel */
		void setWetLevel(float level) override;

		/** @copydoc AudioReverb::setReverbPreset */
		void setReverbPreset(AudioReverbPreset preset);

		/** @copydoc AudioReverb::setPosition */
		void setPosition(Vector3 position);

		/** @copydoc AudioReverb::setMixDistance */
		void setMinDistance(float distance);

		/** @copydoc AudioReverb::setMaxDistance */
		void setMaxDistance(float distance);

		/*
		* Methods in addition to those in common with FMOD. 
		*/

		void setEarlyDelayGain(float gain);

		void setEarlyDelayPan(float panGain);

		void setLateDelayGain(float gain);

		void setLateDelayPan(float panGain);

		void setAirAbsorptionGainHF(float gain);

		void setEchoTime(float time);

		void setEchoDepth(float depth);

		void setModulationTime(float time);

		void setModulationDepth(float depth);

	private:
		friend class OAAudio;

		/** @copydoc IResourceListener::onClipChanged */
		void onClipChanged() override;

		UINT32 mSource;
		UINT32 mEffects;
		UINT32 mSlot;
		
		float minDistance;
		float maxDistance;
		Vector3 positionReverb;
	};

	/** @} */
}