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
			BS_RTTI_MEMBER_PLAIN(mWetVolume, 1)
			BS_RTTI_MEMBER_PLAIN(mDryVolume, 2)
			BS_RTTI_MEMBER_PLAIN(mDecayTime, 3)
			BS_RTTI_MEMBER_PLAIN(mEarlyDelay, 4)
			BS_RTTI_MEMBER_PLAIN(mLateDelay, 5)
			BS_RTTI_MEMBER_PLAIN(mHFReference, 6)
			BS_RTTI_MEMBER_PLAIN(mHFDecayRatio, 7)
			BS_RTTI_MEMBER_PLAIN(mDiffusion, 8)
			BS_RTTI_MEMBER_PLAIN(mDensity, 9)
			BS_RTTI_MEMBER_PLAIN(mLowShelfFrequencies, 10)
			BS_RTTI_MEMBER_PLAIN(mLowShelfGain, 11)
			BS_RTTI_MEMBER_PLAIN(mHighCut, 12)
			BS_RTTI_MEMBER_PLAIN(mEarlyLateMix, 13)
			BS_RTTI_MEMBER_PLAIN(mWetLevel, 14)
			BS_RTTI_MEMBER_REFL(mSource, 15)
			BS_RTTI_MEMBER_REFL(mIr, 16)
			BS_RTTI_MEMBER_PLAIN(mPreset, 17)
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