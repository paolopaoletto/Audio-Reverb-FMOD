#pragma once

#include "BsCorePrerequisites.h"
#include "Reflection/BsRTTIType.h"
#include "Components/BsCAudioReverb.h"
#include "Private/RTTI/BsGameObjectRTTI.h"

namespace bs
{
	/** @cond RTTI */
	/** @addtogroup RTTI-Impl-Core
	 *  @{
	 */

	class BS_CORE_EXPORT CAudioReverbRTTI : public RTTIType<CAudioReverb, Component, CAudioReverbRTTI>
	{
		BS_BEGIN_RTTI_MEMBERS
			//BS_RTTI_MEMBER_REFLPTR(mInternal, 0)
			BS_RTTI_MEMBER_PLAIN(mWetVolume, 0)
			BS_RTTI_MEMBER_PLAIN(mDryVolume, 1)
			BS_RTTI_MEMBER_PLAIN(mDiffusion, 2)
			BS_RTTI_MEMBER_PLAIN(mDensity, 3)
			BS_RTTI_MEMBER_PLAIN(mGain, 4)
			BS_RTTI_MEMBER_PLAIN(mGainHF, 5)
			BS_RTTI_MEMBER_PLAIN(mGainLF, 6)
			BS_RTTI_MEMBER_PLAIN(mDecayTime, 7)
			BS_RTTI_MEMBER_PLAIN(mDecayHFRatio, 8)
			BS_RTTI_MEMBER_PLAIN(mDecayLFRatio, 9)
			BS_RTTI_MEMBER_PLAIN(mReflectionGain, 10)
			BS_RTTI_MEMBER_PLAIN(mReflectionDelay, 11)
			BS_RTTI_MEMBER_PLAIN(mReflectionPan, 12)
			BS_RTTI_MEMBER_PLAIN(mLateReverbGain, 13)
			BS_RTTI_MEMBER_PLAIN(mLateReverbDelay, 14)
			BS_RTTI_MEMBER_PLAIN(mLateReverbPan, 15)
			BS_RTTI_MEMBER_PLAIN(mEchoTime, 16)
			BS_RTTI_MEMBER_PLAIN(mEchoDepth, 17)
			BS_RTTI_MEMBER_PLAIN(mModulationTime, 18)
			BS_RTTI_MEMBER_PLAIN(mModulationDepth, 19)
			BS_RTTI_MEMBER_PLAIN(mHFReference, 20)
			BS_RTTI_MEMBER_PLAIN(mLFReference, 21)
			BS_RTTI_MEMBER_PLAIN(mHighCut, 22)
			BS_RTTI_MEMBER_PLAIN(mEarlyLateMix, 23)
			BS_RTTI_MEMBER_PLAIN(mWetLevel, 24)
			BS_RTTI_MEMBER_PLAIN(mRoomRolloffFactor, 25)
			BS_RTTI_MEMBER_PLAIN(mAirAbsorptionGainHF, 26)
			BS_RTTI_MEMBER_PLAIN(mDecayHFLimit, 27)
			BS_RTTI_MEMBER_PLAIN(mPosition, 28)
			BS_RTTI_MEMBER_PLAIN(mMinDistance, 29)
			BS_RTTI_MEMBER_PLAIN(mMaxDistance, 30)
		BS_END_RTTI_MEMBERS
	public:
		const String& getRTTIName() override
		{
			static String name = "CAudioReverb";
			return name;
		}

		UINT32 getRTTIId() override
		{
			return TID_CAudioReverb;
		}

		SPtr<IReflectable> newRTTIObject() override
		{
			return GameObjectRTTI::createGameObject<CAudioReverb>();
		}
	};

	/** @} */
	/** @endcond */
}