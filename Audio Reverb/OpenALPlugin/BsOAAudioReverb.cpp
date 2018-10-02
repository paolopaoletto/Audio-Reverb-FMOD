#include "BsOAAudioReverb.h"

namespace bs 
{
	OAAudioReverb::OAAudioReverb()
	{
		gOAAudio()._registerReverb(this);
		rebuild();
	}

	OAAudioReverb::~OAAudioReverb()
	{
		clear();
		gOAAudio()._unregisterReverb(this);
	}

	void OAAudioReverb::setSource(const HAudioSource& source)
	{
		AudioReverb::setSource(source);

		if (!gOAAudio()._isExtensionSupported("ALC_EXT_EFX"))
			LOGERR("EAX is not supported on this current machine.");

		auto device = gOAAudio()._getDevice();

		mAttribute[0] = ALC_MAX_AUXILIARY_SENDS;
		mAttribute[1] = 4;

		alcGetIntegerv(device, ALC_MAX_AUXILIARY_SENDS, 1, &mSends);

		auto& contexts = gOAAudio()._getContexts();
		UINT32 numContexts = (UINT32)contexts.size();
		for (UINT32 i = 0; i < numContexts; i++)
		{
			if (contexts.size() > 1)
				alcMakeContextCurrent(contexts[i]);
		}
	}

	void OAAudioReverb::setIR(const HAudioClip& clip)
	{
		AudioReverb::setIR(clip);
	}

	void OAAudioReverb::setWetVolume(float volume)
	{
		AudioReverb::setWetVolume(volume);
	}

	void OAAudioReverb::setDryVolume(float volume)
	{
		AudioReverb::setDryVolume(volume);
	}

	void OAAudioReverb::setDiffusion(float diffusion)
	{
		AudioReverb::setDiffusion(diffusion);

		mReverbPreset.flDiffusion = mDiffusion;
		alEffectf(mEffects, AL_EAXREVERB_DIFFUSION, mReverbPreset.flDiffusion);
	}

	void OAAudioReverb::setDensity(float density)
	{
		AudioReverb::setDensity(density);

		mReverbPreset.flDensity = mDensity;
		alEffectf(mEffects, AL_EAXREVERB_DENSITY, mReverbPreset.flDensity);
	}

	void OAAudioReverb::setGain(float gain)
	{
		AudioReverb::setGain(gain);

		mReverbPreset.flGain = mGain;
		alEffectf(mEffects, AL_EAXREVERB_GAIN, mReverbPreset.flGain);
	}

	void OAAudioReverb::setGainHF(float gain)
	{
		AudioReverb::setGainHF(gain);

		mReverbPreset.flGainHF = mGainHF;
		alEffectf(mEffects, AL_EAXREVERB_GAINHF, mReverbPreset.flGainHF);
	}

	void OAAudioReverb::setGainLF(float gain)
	{
		AudioReverb::setGainLF(gain);

		mReverbPreset.flGainLF = mGainLF;
		alEffectf(mEffects, AL_EAXREVERB_GAINLF, mReverbPreset.flGainLF);
	}

	void OAAudioReverb::setDecayTime(float time)
	{
		AudioReverb::setDecayTime(time);

		mReverbPreset.flDecayTime = mDecayTime;
		alEffectf(mEffects, AL_EAXREVERB_DECAY_TIME, mReverbPreset.flDecayTime);
	}

	void OAAudioReverb::setDecayHFRatio(float ratio)
	{
		AudioReverb::setDecayHFRatio(ratio);

		mReverbPreset.flDecayHFRatio = mDecayHFRatio;
		alEffectf(mEffects, AL_EAXREVERB_DECAY_HFRATIO, mReverbPreset.flDecayHFRatio);
	}

	void OAAudioReverb::setDecayLFRatio(float ratio)
	{
		AudioReverb::setDecayLFRatio(ratio);

		mReverbPreset.flDecayLFRatio = mDecayLFRatio;
		alEffectf(mEffects, AL_EAXREVERB_DECAY_LFRATIO, mReverbPreset.flDecayLFRatio);
	}

	void OAAudioReverb::setReflectionGain(float gain)
	{
		AudioReverb::setReflectionGain(gain);

		mReverbPreset.flReflectionsGain = mReflectionGain;
		alEffectf(mEffects, AL_EAXREVERB_REFLECTIONS_GAIN, mReverbPreset.flReflectionsGain);
	}

	void OAAudioReverb::setReflectionDelay(float delay)
	{
		AudioReverb::setReflectionDelay(delay);

		mReverbPreset.flReflectionsDelay = mReflectionDelay;
		alEffectf(mEffects, AL_EAXREVERB_REFLECTIONS_DELAY, mReverbPreset.flLateReverbDelay);
	}

	void OAAudioReverb::setReflectionPan(Vector3 pan)
	{
		AudioReverb::setReflectionPan(pan);

		mReverbPreset.flReflectionsPan[0] = mReflectionPan.x;
		mReverbPreset.flReflectionsPan[1] = mReflectionPan.y;
		mReverbPreset.flReflectionsPan[2] = mReflectionPan.z;
		alEffectf(mEffects, AL_EAXREVERB_REFLECTIONS_PAN, (*mReverbPreset.flReflectionsPan));
	}

	void OAAudioReverb::setLateReverbGain(float gain)
	{
		AudioReverb::setLateReverbGain(gain);

		mReverbPreset.flLateReverbGain = mLateReverbGain;
		alEffectf(mEffects, AL_EAXREVERB_LATE_REVERB_GAIN, mReverbPreset.flLateReverbGain);
	}

	void OAAudioReverb::setLateReverbDelay(float delay)
	{
		AudioReverb::setLateReverbDelay(delay);

		mReverbPreset.flLateReverbDelay = mLateReverbDelay;
		alEffectf(mEffects, AL_EAXREVERB_LATE_REVERB_DELAY, mReverbPreset.flLateReverbDelay);
	}

	void OAAudioReverb::setLateReverbPan(Vector3 pan)
	{
		AudioReverb::setLateReverbPan(pan);

		mReverbPreset.flLateReverbPan[0] = mLateReverbPan.x;
		mReverbPreset.flLateReverbPan[1] = mLateReverbPan.y;
		mReverbPreset.flLateReverbPan[2] = mLateReverbPan.z;
		alEffectf(mEffects, AL_EAXREVERB_LATE_REVERB_PAN, (*mReverbPreset.flLateReverbPan));
	}

	void OAAudioReverb::setEchoTime(float time)
	{
		AudioReverb::setEchoTime(time);

		mReverbPreset.flEchoTime = mEchoTime;
		alEffectf(mEffects, AL_EAXREVERB_ECHO_TIME, mReverbPreset.flEchoTime);
	}

	void OAAudioReverb::setEchoDepth(float depth)
	{
		AudioReverb::setEchoDepth(depth);

		mReverbPreset.flEchoDepth = mEchoDepth;
		alEffectf(mEffects, AL_EAXREVERB_ECHO_DEPTH, mReverbPreset.flEchoDepth);
	}

	void OAAudioReverb::setModulationTime(float time)
	{
		AudioReverb::setModulationTime(time);

		mReverbPreset.flModulationTime = mModulationTime;
		alEffectf(mEffects, AL_EAXREVERB_MODULATION_TIME, mReverbPreset.flModulationTime);
	}

	void OAAudioReverb::setModulationDepth(float depth)
	{
		AudioReverb::setModulationDepth(depth);

		mReverbPreset.flModulationDepth = mModulationDepth;
		alEffectf(mEffects, AL_EAXREVERB_MODULATION_DEPTH, mReverbPreset.flModulationDepth);
	}

	void OAAudioReverb::setHFReference(float hfref)
	{
		AudioReverb::setHFReference(hfref);

		mReverbPreset.flHFReference = mHFReference;
		alEffectf(mEffects, AL_EAXREVERB_HFREFERENCE, mReverbPreset.flHFReference);
	}

	void OAAudioReverb::setLFReference(float hfref)
	{
		AudioReverb::setLFReference(hfref);

		mReverbPreset.flLFReference = mLFReference;
		alEffectf(mEffects, AL_EAXREVERB_LFREFERENCE, mReverbPreset.flLFReference);
	}

	void OAAudioReverb::setHighCut(float freq)
	{
		// FMOD Features.
	}

	void OAAudioReverb::setEarlyLateMix(float elm)
	{
		// FMOD Features.
	}

	void OAAudioReverb::setWetLevel(float level)
	{
		// FMOD Features.
	}

	void OAAudioReverb::setRoomRolloffFactor(float factor)
	{
		AudioReverb::setRoomRolloffFactor(factor);

		mReverbPreset.flRoomRolloffFactor = mRoomRolloffFactor;
		alEffectf(mEffects, AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, mReverbPreset.flRoomRolloffFactor);
	}

	void OAAudioReverb::setAirAbsorptionGainHF(float gain)
	{
		AudioReverb::setAirAbsorptionGainHF(gain);

		mReverbPreset.flAirAbsorptionGainHF = mAirAbsorptionGainHF;
		alEffectf(mEffects, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, mReverbPreset.flAirAbsorptionGainHF);
	}

	void OAAudioReverb::setDecayHFLimit(bool limit)
	{
		AudioReverb::setDecayHFLimit(limit);

		mReverbPreset.iDecayHFLimit = mDecayHFLimit;
		alEffecti(mEffects, AL_EAXREVERB_DECAY_HFLIMIT, mReverbPreset.iDecayHFLimit);
	}

	void OAAudioReverb::setReverbPreset(AudioReverbPreset preset)
	{
		AudioReverb::setReverbPreset(preset);

		switch (mPreset) 
		{
		case AudioReverbPreset::Generic:
			mReverbPreset = EFX_REVERB_PRESET_GENERIC;

		case AudioReverbPreset::PaddedCell:
			mReverbPreset = EFX_REVERB_PRESET_PADDEDCELL;

		case AudioReverbPreset::Room:
			mReverbPreset = EFX_REVERB_PRESET_ROOM;

		case AudioReverbPreset::BathRoom:
			mReverbPreset = EFX_REVERB_PRESET_BATHROOM;

		case AudioReverbPreset::LivingRoom:
			mReverbPreset = EFX_REVERB_PRESET_LIVINGROOM;

		case AudioReverbPreset::StoneRoom:
			mReverbPreset = EFX_REVERB_PRESET_STONEROOM;

		case AudioReverbPreset::ConcertHall:
			mReverbPreset = EFX_REVERB_PRESET_CONCERTHALL;

		case AudioReverbPreset::Cave:
			mReverbPreset = EFX_REVERB_PRESET_CONCERTHALL;

		case AudioReverbPreset::Arena:
			mReverbPreset = EFX_REVERB_PRESET_ARENA;

		case AudioReverbPreset::Hangar:
			mReverbPreset = EFX_REVERB_PRESET_HANGAR;

		case AudioReverbPreset::CarpetteHallway:
			mReverbPreset = EFX_REVERB_PRESET_CARPETEDHALLWAY;

		case AudioReverbPreset::Hallway:
			mReverbPreset = EFX_REVERB_PRESET_HALLWAY;

		case AudioReverbPreset::StoneCorridor:
			mReverbPreset = EFX_REVERB_PRESET_STONECORRIDOR;

		case AudioReverbPreset::Alley:
			mReverbPreset = EFX_REVERB_PRESET_ALLEY;

		case AudioReverbPreset::Forest:
			mReverbPreset = EFX_REVERB_PRESET_FOREST;

		case AudioReverbPreset::City:
			mReverbPreset = EFX_REVERB_PRESET_CITY;

		case AudioReverbPreset::Mountains:
			mReverbPreset = EFX_REVERB_PRESET_MOUNTAINS;

		case AudioReverbPreset::Quarry:
			mReverbPreset = EFX_REVERB_PRESET_QUARRY;

		case AudioReverbPreset::Plain:
			mReverbPreset = EFX_REVERB_PRESET_PLAIN;

		case AudioReverbPreset::ParkingLot:
			mReverbPreset = EFX_REVERB_PRESET_PARKINGLOT;

		case AudioReverbPreset::Sewerpipe:
			mReverbPreset = EFX_REVERB_PRESET_SEWERPIPE;

		case AudioReverbPreset::Underwater:
			mReverbPreset = EFX_REVERB_PRESET_UNDERWATER;
		}

		alEffectf(mEffects, AL_EAXREVERB_DENSITY, mReverbPreset.flDensity);
		alEffectf(mEffects, AL_EAXREVERB_DIFFUSION, mReverbPreset.flDiffusion);
		alEffectf(mEffects, AL_EAXREVERB_GAIN, mReverbPreset.flGain);
		alEffectf(mEffects, AL_EAXREVERB_GAINHF, mReverbPreset.flGainHF);
		alEffectf(mEffects, AL_EAXREVERB_GAINLF, mReverbPreset.flGainLF);
		alEffectf(mEffects, AL_EAXREVERB_DECAY_TIME, mReverbPreset.flDecayTime);
		alEffectf(mEffects, AL_EAXREVERB_DECAY_HFRATIO, mReverbPreset.flDecayHFRatio);
		alEffectf(mEffects, AL_EAXREVERB_DECAY_LFRATIO, mReverbPreset.flDecayLFRatio);
		alEffectf(mEffects, AL_EAXREVERB_REFLECTIONS_GAIN, mReverbPreset.flReflectionsGain);
		alEffectf(mEffects, AL_EAXREVERB_REFLECTIONS_DELAY, mReverbPreset.flReflectionsDelay);
		alEffectf(mEffects, AL_EAXREVERB_REFLECTIONS_PAN, (*mReverbPreset.flReflectionsPan));
		alEffectf(mEffects, AL_EAXREVERB_LATE_REVERB_GAIN, mReverbPreset.flLateReverbGain);
		alEffectf(mEffects, AL_EAXREVERB_LATE_REVERB_DELAY, mReverbPreset.flLateReverbDelay);
		alEffectf(mEffects, AL_EAXREVERB_LATE_REVERB_PAN, (*mReverbPreset.flLateReverbPan));
		alEffectf(mEffects, AL_EAXREVERB_ECHO_TIME, mReverbPreset.flEchoTime);
		alEffectf(mEffects, AL_EAXREVERB_ECHO_DEPTH, mReverbPreset.flEchoDepth);
		alEffectf(mEffects, AL_EAXREVERB_MODULATION_TIME, mReverbPreset.flModulationTime);
		alEffectf(mEffects, AL_EAXREVERB_MODULATION_DEPTH, mReverbPreset.flModulationDepth);
		alEffectf(mEffects, AL_EAXREVERB_HFREFERENCE, mReverbPreset.flHFReference);
		alEffectf(mEffects, AL_EAXREVERB_LFREFERENCE, mReverbPreset.flLFReference);
		alEffectf(mEffects, AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, mReverbPreset.flRoomRolloffFactor);
		alEffectf(mEffects, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, mReverbPreset.flAirAbsorptionGainHF);
		alEffecti(mEffects, AL_EAXREVERB_DECAY_HFLIMIT, mReverbPreset.iDecayHFLimit);
	}

	void OAAudioReverb::setPosition(Vector3 position)
	{
		// FMOD Features.
	}

	void OAAudioReverb::setMinDistance(float distance)
	{
		// FMOD Features.
	}

	void OAAudioReverb::setMaxDistance(float distance)
	{
		// FMOD Features.
	}

	void OAAudioReverb::onClipChanged()
	{

	}

	void OAAudioReverb::buildGenObjects() 
	{
		// Get the effect object function
		BS_AL_GET_PROC_ADDRESS(alGenEffects, LPALGENEFFECTS);
		BS_AL_GET_PROC_ADDRESS(alDeleteEffects, LPALDELETEEFFECTS);
		BS_AL_GET_PROC_ADDRESS(alIsEffect, LPALISEFFECT);
		BS_AL_GET_PROC_ADDRESS(alEffecti, LPALEFFECTI);
		BS_AL_GET_PROC_ADDRESS(alEffectiv, LPALEFFECTIV);
		BS_AL_GET_PROC_ADDRESS(alEffectf, LPALEFFECTF);
		BS_AL_GET_PROC_ADDRESS(alEffectfv, LPALEFFECTFV);

		// Get the auxiliary effect slot object function
		BS_AL_GET_PROC_ADDRESS(alGenAuxiliaryEffectSlots, LPALGENAUXILIARYEFFECTSLOTS);
		BS_AL_GET_PROC_ADDRESS(alDeleteAuxiliaryEffectSlots, LPALDELETEAUXILIARYEFFECTSLOTS);
		BS_AL_GET_PROC_ADDRESS(alIsAuxiliaryEffectSlot, LPALISAUXILIARYEFFECTSLOT);
		BS_AL_GET_PROC_ADDRESS(alAuxiliaryEffectSloti, LPALAUXILIARYEFFECTSLOTI);
		BS_AL_GET_PROC_ADDRESS(alAuxiliaryEffectSlotiv, LPALAUXILIARYEFFECTSLOTIV);
		BS_AL_GET_PROC_ADDRESS(alAuxiliaryEffectSlotf, LPALAUXILIARYEFFECTSLOTF);
		BS_AL_GET_PROC_ADDRESS(alAuxiliaryEffectSlotfv, LPALAUXILIARYEFFECTSLOTFV);
	}

	void OAAudioReverb::rebuild()
	{
		auto& contexts = gOAAudio()._getContexts();
		UINT32 numContexts = (UINT32)contexts.size();

		{
			Lock lock(mMutex);

			for (UINT32 i = 0; i < numContexts; i++)
			{
				if (contexts.size() > 1)
					alcMakeContextCurrent(contexts[i]);

				UINT32 mEffects = 0;
				alGenEffects(1, &mEffects);
				alEffecti(mEffects, AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);

				UINT32 mSlot = 0;
				alGenAuxiliaryEffectSlots(1, &mSlot);
				alAuxiliaryEffectSloti(mSlot, AL_EFFECTSLOT_EFFECT, mEffects);
			}
		}

		for (UINT32 i = 0; i < numContexts; i++)
		{
			if (contexts.size() > 1)
				alcMakeContextCurrent(contexts[i]);

			// TODO: set reverb values to default.
		}

		buildGenObjects();
	}

	void OAAudioReverb::clear()
	{
		auto& contexts = gOAAudio()._getContexts();
		UINT32 numContexts = (UINT32)contexts.size();

		Lock lock(mMutex);
		for (UINT32 i = 0; i < numContexts; i++)
		{
			if (contexts.size() > 1)
				alcMakeContextCurrent(contexts[i]);

			alDeleteAuxiliaryEffectSlots(1, &mSlot);
			alDeleteEffects(1, &mEffects);
		}
	}

}