#pragma once

#include "BsFMODPrerequisites.h"
#include "BsFMODAudio.h"
#include "Audio/BsAudioReverb.h"

namespace bs {

	class FMODAudioReverb : public AudioReverb {
	public:
		FMODAudioReverb();
		virtual ~FMODAudioReverb();

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

	private:
		friend class FMODAudio;

		FMOD::Sound* ir;
		FMOD::Channel* channel;
		FMOD::ChannelGroup* reverbGroup;
		FMOD::DSP* reverbUnit;
		FMOD::DSP* channelHead;
		FMOD::DSPConnection* reverbConnection;

		INT32 irSoundBits;
		INT32 IrSoundChannels;
		UINT32 irLength;

		FMOD_SOUND_FORMAT irSoundFormat;
		FMOD_SOUND_TYPE irSoundType;

		FMOD::Reverb3D* reverb3D;
		FMOD_REVERB_PROPERTIES prop;
	};

	/** @} */
}