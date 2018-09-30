#pragma once

#include "BsFMODPrerequisites.h"
#include "BsFMODAudio.h"
#include "Audio/BsAudioReverb.h"

namespace bs {

	class FMODAudioReverb : public AudioReverb 
	{
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

		/** @copydoc AudioReverb::setDiffusion */
		void setDiffusion(float diffusion) override;

		/** @copydoc AudioReverb::setDensity */
		void setDensity(float density) override;

		/** @copydoc AudioReverb::setGain */
		void setGain(float gain) override;

		/** @copydoc AudioReverb::setGainHF */
		void setGainHF(float gain) override;

		/** @copydoc AudioReverb::setGainLF */
		void setGainLF(float gain) override;

		/** @copydoc AudioReverb::setDecayTime */
		void setDecayTime(float time) override;

		/** @copydoc AudioReverb::setDecayHFRatio */
		void setDecayHFRatio(float ratio) override;

		/** @copydoc AudioReverb::setDecayLFRatio */
		void setDecayLFRatio(float ratio) override;

		/** @copydoc AudioReverb::setReflectionGain */
		void setReflectionGain(float gain) override;

		/** @copydoc AudioReverb::setReflectionDelay */
		void setReflectionDelay(float delay) override;

		/** @copydoc AudioReverb::setReflectionPan */
		void setReflectionPan(Vector3 pan) override;

		/** @copydoc AudioReverb::setLateReverbGain */
		void setLateReverbGain(float gain) override;

		/** @copydoc AudioReverb::setLateReverbDelay */
		void setLateReverbDelay(float delay) override;

		/** @copydoc AudioReverb::setLateReverbPan */
		void setLateReverbPan(Vector3 pan) override;

		/** @copydoc AudioReverb::setEchoTime */
		void setEchoTime(float time) override;

		/** @copydoc AudioReverb::setEchoDepth */
		void setEchoDepth(float depth) override;

		/** @copydoc AudioReverb::setModulationTime */
		void setModulationTime(float time) override;

		/** @copydoc AudioReverb::setModulationDepth */
		void setModulationDepth(float depth) override;

		/** @copydoc AudioReverb::setHFReference */
		void setHFReference(float hfref) override;

		/** @copydoc AudioReverb::setLFReference */
		void setLFReference(float hfref) override;

		/** @copydoc AudioReverb::setHighCut */
		void setHighCut(float freq) override;

		/** @copydoc AudioReverb::setEarlyLateMix */
		void setEarlyLateMix(float elm) override;

		/** @copydoc AudioReverb::setWetLevel */
		void setWetLevel(float level) override;

		/** @copydoc AudioReverb::setRoomRolloffFactor */
		void setRoomRolloffFactor(float factor) override;

		/** @copydoc AudioReverb::setAirAbsorptionGainHF */
		void setAirAbsorptionGainHF(float gain);

		/** @copydoc AudioReverb::setDecayHFLimit */
		void setDecayHFLimit(bool limit) override;

		/** @copydoc AudioReverb::setReverbPreset */
		void setReverbPreset(AudioReverbPreset preset);

		/** @copydoc AudioReverb::setPosition */
		void setPosition(Vector3 position);

		/** @copydoc AudioReverb::setMixDistance */
		void setMinDistance(float distance);

		/** @copydoc AudioReverb::setMaxDistance */
		void setMaxDistance(float distance);

	private:
		friend class FMODAudio;

		/** @copydoc IResourceListener::onClipChanged */
		void onClipChanged() override;

		FMOD::Sound* ir = nullptr;
		FMOD::Channel* channel = nullptr;
		FMOD::ChannelGroup* reverbGroup = nullptr;
		FMOD::DSP* reverbUnit = nullptr;
		FMOD::DSP* channelHead = nullptr;
		FMOD::DSPConnection* reverbConnection = nullptr;

		INT32 irSoundBits;
		INT32 IrSoundChannels;
		UINT32 irLength;
		UINT32 irDataLength;
		INT16 irData;

		FMOD_SOUND_FORMAT irSoundFormat;
		FMOD_SOUND_TYPE irSoundType;

		FMOD::Reverb3D* reverb3D = nullptr;
		FMOD_REVERB_PROPERTIES prop;

		float minDistance;
		float maxDistance;
		FMOD_VECTOR positionReverb;
	};

	/** @} */
}