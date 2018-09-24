#include "BsCorePrerequisites.h"
#include "Reflection/BsRTTIType.h"
#include "Audio/BsAudioReverb.h"

namespace bs 
{
	/** @cond RTTI */
	/** @addtogroup RTTI-Impl-Engine
	*  @{
	*/

	class BS_CORE_EXPORT AudioReverbRTTI : public RTTIType<AudioReverb, IReflectable, AudioReverbRTTI> 
	{
	private:
		BS_BEGIN_RTTI_MEMBERS
			BS_RTTI_MEMBER_PLAIN(mWetVolume, 0)
			BS_RTTI_MEMBER_PLAIN(mDryVolume, 1)
			BS_RTTI_MEMBER_PLAIN(mDecayTime, 2)
			BS_RTTI_MEMBER_PLAIN(mEarlyDelay, 3)
			BS_RTTI_MEMBER_PLAIN(mLateDelay, 4)
			BS_RTTI_MEMBER_PLAIN(mHFReference, 5)
			BS_RTTI_MEMBER_PLAIN(mHFDecayRatio, 6)
			BS_RTTI_MEMBER_PLAIN(mDiffusion, 7)
			BS_RTTI_MEMBER_PLAIN(mDensity, 8)
			BS_RTTI_MEMBER_PLAIN(mLowShelfFrequencies, 9)
			BS_RTTI_MEMBER_PLAIN(mLowShelfGain, 10)
			BS_RTTI_MEMBER_PLAIN(mHighCut, 11)
			BS_RTTI_MEMBER_PLAIN(mEarlyLateMix, 12)
			BS_RTTI_MEMBER_PLAIN(mWetLevel, 13)
			BS_RTTI_MEMBER_REFL(mSource, 14)
			BS_RTTI_MEMBER_REFL(mIr, 14)
			BS_RTTI_MEMBER_PLAIN(mPreset, 15)
			BS_RTTI_MEMBER_PLAIN(mIsReverbIR, 16)
			BS_RTTI_MEMBER_PLAIN(mPosition, 17)
			BS_RTTI_MEMBER_PLAIN(mMinDistance, 18)
			BS_RTTI_MEMBER_PLAIN(mMaxDistance, 19)
		BS_END_RTTI_MEMBERS
	public:
		const String& getRTTIName() override {
			static String name = "AudioReverb";
			return name;
		}

		UINT32 getRTTIId() override {
			return TID_AudioReverb;
		}

		SPtr<IReflectable> newRTTIObject() override {
			return AudioReverb::create();
		}
	};

	/** @} */
	/** @endcond */
}