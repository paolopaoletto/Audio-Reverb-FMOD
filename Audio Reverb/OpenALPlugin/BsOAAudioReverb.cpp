#include "BsOAAudioReverb.h"

namespace bs 
{
	OAAudioReverb::OAAudioReverb()
	{
		gOAAudio()._registerReverb(this);
	}

	OAAudioReverb::~OAAudioReverb()
	{
		gOAAudio()._unregisterReverb(this);
	}

	void OAAudioReverb::setSource(const HAudioSource& source)
	{
		AudioReverb::setSource(source);
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
	}

	void OAAudioReverb::setDensity(float density)
	{
		AudioReverb::setDensity(density);

		mReverbPreset.flDensity = mDensity;
	}

	void OAAudioReverb::setGain(float gain)
	{
		AudioReverb::setGain(gain);

		mReverbPreset.flGain = mGain;
	}

	void OAAudioReverb::setGainHF(float gain)
	{
		AudioReverb::setGainHF(gain);

		mReverbPreset.flGainHF = mGainHF;
	}

	void OAAudioReverb::setGainLF(float gain)
	{
		AudioReverb::setGainLF(gain);

		mReverbPreset.flGainLF = mGainLF;
	}

	void OAAudioReverb::setDecayTime(float time)
	{
		AudioReverb::setDecayTime(time);

		mReverbPreset.flDecayTime = mDecayTime;
	}

	void OAAudioReverb::setDecayHFRatio(float ratio)
	{
		AudioReverb::setDecayHFRatio(ratio);

		mReverbPreset.flDecayHFRatio = mDecayHFRatio;
	}

	void OAAudioReverb::setDecayLFRatio(float ratio)
	{
		AudioReverb::setDecayLFRatio(ratio);

		mReverbPreset.flDecayLFRatio = mDecayLFRatio;
	}

	void OAAudioReverb::setReflectionGain(float gain)
	{
		AudioReverb::setReflectionGain(gain);

		mReverbPreset.flReflectionsGain = mReflectionGain;
	}

	void OAAudioReverb::setReflectionDelay(float delay)
	{
		AudioReverb::setReflectionDelay(delay);

		mReverbPreset.flReflectionsDelay = mReflectionDelay;
	}

	void OAAudioReverb::setReflectionPan(Vector3 pan)
	{
		AudioReverb::setReflectionPan(pan);

		mReverbPreset.flReflectionsPan[0] = mReflectionPan.x;
		mReverbPreset.flReflectionsPan[1] = mReflectionPan.y;
		mReverbPreset.flReflectionsPan[2] = mReflectionPan.z;
	}

	void OAAudioReverb::setLateReverbGain(float gain)
	{
		AudioReverb::setLateReverbGain(gain);

		mReverbPreset.flLateReverbGain = mLateReverbGain;
	}

	void OAAudioReverb::setLateReverbDelay(float delay)
	{
		AudioReverb::setLateReverbDelay(delay);

		mReverbPreset.flLateReverbDelay = mLateReverbDelay;
	}

	void OAAudioReverb::setLateReverbPan(Vector3 pan)
	{
		AudioReverb::setLateReverbPan(pan);

		mReverbPreset.flLateReverbPan[0] = mLateReverbPan.x;
		mReverbPreset.flLateReverbPan[1] = mLateReverbPan.y;
		mReverbPreset.flLateReverbPan[2] = mLateReverbPan.z;
	}

	void OAAudioReverb::setEchoTime(float time)
	{
		AudioReverb::setEchoTime(time);

		mReverbPreset.flEchoTime = mEchoTime;
	}

	void OAAudioReverb::setEchoDepth(float depth)
	{
		AudioReverb::setEchoDepth(depth);

		mReverbPreset.flEchoDepth = mEchoDepth;
	}

	void OAAudioReverb::setModulationTime(float time)
	{
		AudioReverb::setModulationTime(time);

		mReverbPreset.flModulationTime = mModulationTime;
	}

	void OAAudioReverb::setModulationDepth(float depth)
	{
		AudioReverb::setModulationDepth(depth);

		mReverbPreset.flModulationDepth = mModulationDepth;
	}

	void OAAudioReverb::setHFReference(float hfref)
	{
		AudioReverb::setHFReference(hfref);

		mReverbPreset.flHFReference = mHFReference;
	}

	void OAAudioReverb::setLFReference(float hfref)
	{
		AudioReverb::setLFReference(hfref);

		mReverbPreset.flLFReference = mLFReference;
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
	}

	void OAAudioReverb::setAirAbsorptionGainHF(float gain)
	{
		AudioReverb::setAirAbsorptionGainHF(gain);

		mReverbPreset.flAirAbsorptionGainHF = mAirAbsorptionGainHF;
	}

	void OAAudioReverb::setDecayHFLimit(bool limit)
	{
		AudioReverb::setDecayHFLimit(limit);

		mReverbPreset.iDecayHFLimit = mDecayHFLimit;
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

}