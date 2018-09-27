#include "BsFMODAudioReverb.h"

namespace bs {

	FMODAudioReverb::FMODAudioReverb() 
	{
		gFMODAudio()._registerReverb(this);
	}

	FMODAudioReverb::~FMODAudioReverb() 
	{
		gFMODAudio()._unregisterReverb(this);
	}

	void FMODAudioReverb::setSource(const HAudioSource& source) 
	{
		AudioReverb::setSource(source);

		/** Temporary positions */
		FMOD_VECTOR position = { -10.0f, 0.0f, 0.0f };

		const float min = 10.0f;
		const float max = 20.0f;

		FMOD::System* fmod = gFMODAudio()._getFMOD();
		if (!isReverbIR()) {
			fmod->createReverb3D(&reverb3D);
			reverb3D->setProperties(&prop);
			reverb3D->set3DAttributes(&position, min, max);
		}
	}

	void FMODAudioReverb::setIR(const HAudioClip& clip) 
	{
		AudioReverb::setIR(clip);

		FMOD::System* fmod = gFMODAudio()._getFMOD();
		//FMODAudioClip* fmodClip = static_cast<FMODAudioClip*>(mIr.get());
		
		if (AudioReverb::isReverbIR() && clip != nullptr) {
			fmod->createChannelGroup("reverb", &reverbGroup);
			fmod->createDSPByType(FMOD_DSP_TYPE_CONVOLUTIONREVERB, &reverbUnit);
			reverbGroup->addDSP(FMOD_CHANNELCONTROL_DSP_TAIL, reverbUnit);
		}
	}

	void FMODAudioReverb::setWetVolume(float volume) 
	{
		AudioReverb::setWetVolume(volume);

		if (reverbUnit != nullptr) {
			reverbUnit->setParameterData(FMOD_DSP_CONVOLUTION_REVERB_PARAM_IR, &irData, irDataLength);
			reverbUnit->setParameterFloat(FMOD_DSP_CONVOLUTION_REVERB_PARAM_DRY, -80.0f);
		}

		if (reverbConnection != nullptr)
			reverbConnection->setMix(mWetVolume);
	}

	void FMODAudioReverb::setDryVolume(float volume) 
	{
		AudioReverb::setDryVolume(volume);
	}

	void FMODAudioReverb::setDiffusion(float diffusion)
	{
		AudioReverb::setDiffusion(diffusion);

		prop.Diffusion = mDiffusion;
	}

	void FMODAudioReverb::setDensity(float density)
	{
		AudioReverb::setDensity(density);

		prop.Density = mDensity;
	}

	void FMODAudioReverb::setGain(float gain)
	{
		// OpenAL Features.
	}

	void FMODAudioReverb::setGainHF(float gain)
	{
		// OpenAL Features.
	}

	void FMODAudioReverb::setGainLF(float gain)
	{
		// OpenAL Features.
	}

	void FMODAudioReverb::setDecayTime(float time)
	{
		AudioReverb::setDecayTime(time);

		prop.DecayTime = mDecayTime;
	}

	void FMODAudioReverb::setDecayHFRatio(float ratio)
	{

	}

	void FMODAudioReverb::setDecayLFRatio(float ratio)
	{
		// OpenAL Features.
	}

	void FMODAudioReverb::setReflectionGain(float gain)
	{
		// OpenAL Features.
	}

	void FMODAudioReverb::setReflectionDelay(float delay)
	{

	}

	void FMODAudioReverb::setReflectionPan(Vector3 pan)
	{
		// OpenAL Features.
	}

	void FMODAudioReverb::setLateReverbGain(float gain)
	{
		// OpenAL Features.
	}

	void FMODAudioReverb::setLateReverbDelay(float delay)
	{

	}

	void FMODAudioReverb::setLateReverbPan(Vector3 pan)
	{
		// OpenAL Features.
	}

	void FMODAudioReverb::setEchoTime(float time)
	{
		// OpenAL Features.
	}

	void FMODAudioReverb::setEchoDepth(float depth)
	{
		// OpenAL Features.
	}

	void FMODAudioReverb::setModulationTime(float time)
	{
		// OpenAL Features.
	}

	void FMODAudioReverb::setModulationDepth(float depth)
	{
		// OpenAL Features.
	}


	void FMODAudioReverb::setHFReference(float hfref)
	{
		AudioReverb::setHFReference(hfref);

		prop.HFReference = mHFReference;
	}


	void FMODAudioReverb::setLFReference(float hfref)
	{

	}

	void FMODAudioReverb::setHighCut(float freq)
	{
		AudioReverb::setHighCut(freq);

		prop.HighCut = mHighCut;
	}

	void FMODAudioReverb::setEarlyLateMix(float elm)
	{
		AudioReverb::setEarlyLateMix(elm);

		prop.EarlyLateMix = mEarlyLateMix;
	}

	void FMODAudioReverb::setWetLevel(float level)
	{
		AudioReverb::setWetLevel(level);

		prop.WetLevel = mWetLevel;
	}

	void FMODAudioReverb::setRoomRolloffFactor(float factor)
	{
		// OpenAL Features.
	}

	void FMODAudioReverb::setAirAbsorptionGainHF(float gain)
	{
		// OpenAL Features.
	}

	void FMODAudioReverb::setDecayHFLimit(bool limit)
	{
		// OpenAL Features.
	}

	void FMODAudioReverb::setReverbPreset(AudioReverbPreset preset)
	{
		AudioReverb::setReverbPreset(preset);

		switch (mPreset) 
		{
		case AudioReverbPreset::SmallRoom:
			prop = { 800, 4.0f, 11.0f, 3000.0f, 50.0f, 
					 100.0f, 100.0f, 350.0f, 0.0f, 200000.0f, 
					 70.0f, -6.0f };
		case AudioReverbPreset::MediumRoom:
			prop = { 1500, 8.0f, 12.0f, 2500.0f, 65.0f,
					 100.0f, 100.0f, 350.0f, 4.0f, 8500.0f,
					 45.0f, -6.0f };
		case AudioReverbPreset::LargeRoom:
			prop = { 3000, 8.0f, 12.0f, 2000.0f, 70.0f,
					 100.0f, 100.0f, 350.0f, 4.0f, 10000.0f,
					 60.0f, -6.0f };
		case AudioReverbPreset::Off:
			prop = { 1000.0f, 7.0f, 11.0f, 5000.0f, 100.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 20.0f, 
					96.0f, -80.0f };
		case AudioReverbPreset::Generic:
			prop = { 1500.0f, 7.0f, 11.0f, 5000.0f, 83.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 14500.0f,
					96.0f, -8.0f };
		case AudioReverbPreset::PaddedCell:
			prop = { 170.0f, 1.0f, 2.0f, 5000.0f, 10.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 160.0f,
					84.0f, -7.8f };
		case AudioReverbPreset::Room:
			prop = { 400.0f, 2.0f, 3.0f, 5000.0f, 83.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 6050.0f,
					88.0f, -9.4f };
		case AudioReverbPreset::BathRoom:
			prop = { 1500.0f, 7.0f, 11.0f, 5000.0f, 54.0f,
					100.0f, 60.0f, 250.0f, 0.0f, 2900.0f, 
					83.0f, 0.5f };
		case AudioReverbPreset::LivingRoom:
			prop = { 500.0f, 3.0f, 4.0f, 5000.0f, 10.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 160.0f, 
					58.0f, -19.0f };
		case AudioReverbPreset::StoneRoom:
			prop = { 2300.0f, 12.0f, 17.0f, 5000.0f, 64.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 7800.0f,
					71.0f, -8.5f };
		case AudioReverbPreset::Auditorium:
			prop = { 4300.0f, 20.0f, 30.0f, 5000.0f, 59.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 5850.0f,
					64.0f, -11.7f };
		case AudioReverbPreset::ConcertHall:
			prop = { 3900.0f, 20.0f, 29.0f, 5000.0f, 70.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 5650.0f,
					80.0f,  -9.8f };
		case AudioReverbPreset::Cave:
			prop = { 2900.0f, 15.0f, 22.0f, 5000.0f, 100.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 20000.0f, 
					59.0f, -11.3f };
		case AudioReverbPreset::Arena:
			prop = { 7200.0f, 20.0f, 30.0f, 5000.0f, 33.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 4500.0f,
					80.0f,  -9.6f };
		case AudioReverbPreset::Hangar:
			prop = { 10000.0f, 20.0f, 30.0f, 5000.0f, 23.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 3400.0f,
					72.0f, -7.4f };
		case AudioReverbPreset::CarpetteHallway:
			prop = { 300.0f, 2.0f, 30.0f, 5000.0f, 10.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 500.0f,
					56.0f, -24.0f };
		case AudioReverbPreset::Hallway:
			prop = { 1500.0f, 7.0f, 11.0f, 5000.0f, 59.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 7800.0f, 
					87.0f, -5.5f };
		case AudioReverbPreset::StoneCorridor:
			prop = { 270.0f, 13.0f, 20.0f, 5000.0f, 79.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 9000.0f, 
					86.0f, -6.0f };
		case AudioReverbPreset::Alley:
			prop = { 1500.0f, 7.0f, 11.0f, 5000.0f, 86.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 8300.0f,
					80.0f, -9.8f };
		case AudioReverbPreset::Forest:
			prop = { 1500.0f, 162.0f, 88.0f, 5000.0f, 54.0f,
					79.0f, 100.0f, 250.0f, 0.0f, 760.0f,
					94.0f, -12.3f };
		case AudioReverbPreset::City:
			prop = { 1500.0f, 7.0f, 11.0f, 5000.0f, 67.0f,
					50.0f, 100.0f, 250.0f, 0.0f, 4050.0f,
					66.0f, -26.0f };
		case AudioReverbPreset::Mountains:
			prop = { 1500.0f,  300.0f, 100.0f, 5000.0f, 21.0f,
					27.0f, 100.0f, 250, 0.0f, 1220.0f,
					82.0f, -24.0f };
		case AudioReverbPreset::Quarry:
			prop = { 1500.0f, 61.0f, 25.0f, 5000.0f, 83.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 3400.0f,
					100.0f, -5.0f };
		case AudioReverbPreset::Plain:
			prop = { 1500.0f, 179.0f, 100.0f, 5000.0f, 50.0f,
					21.0f, 100.0f, 250.0f, 0.0f, 1670.0f,
					65.0f, -28.0f };
		case AudioReverbPreset::ParkingLot:
			prop = { 1700.0f, 8.0f, 12.0f, 5000.0f,
					100.0f, 100.0f, 100.0f, 250.0f, 0.0f, 20000.0f,
					56.0f, -19.5f };
		case AudioReverbPreset::Sewerpipe:
			prop = { 2800.0f, 14.0f, 21.0f, 5000.0f, 14.0f,
					80.0f, 60.0f, 250.0f, 0.0f, 3400.0f, 
					66.0f, 1.2f };
		case AudioReverbPreset::Underwater:
			prop = { 1500.0f, 7.0f, 11.0f, 5000.0f, 10.0f,
					100.0f, 100.0f, 250.0f, 0.0f, 500.0f,
					92.0f, 7.0f };
		}
	}

	void FMODAudioReverb::setPosition(Vector3 position)
	{
		AudioReverb::setPosition(position);

		positionReverb = mPosition;
	}

	void FMODAudioReverb::setMinDistance(float distance)
	{
		AudioReverb::setMinDistance(distance);

		minDistance = mMinDistance;
	}

	void FMODAudioReverb::setMaxDistance(float distance)
	{
		AudioReverb::setMaxDistance(distance);

		maxDistance = mMaxDistance;
	}

	void FMODAudioReverb::onClipChanged()
	{
	
	}
}