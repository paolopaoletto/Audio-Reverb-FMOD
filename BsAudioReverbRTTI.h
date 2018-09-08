#include "BsCorePrerequisites.h"
#include "Reflection/BsRTTIType.h"
#include "Audio/BsAudioReverb.h"

namespace bs 
{
	/** @cond RTTI */
	/** @addtogroup RTTI-Impl-Engine
	*  @{
	*/

	class BS_CORE_EXPORT AudioReverbRTTI : public RTTIType<AudioReverb, IReflectable, AudioReverbRTTI> {
	private:
		BS_BEGIN_RTTI_MEMBERS

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