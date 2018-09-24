#include "AL/efx.h"

#define AL_GET_PROC_ADDRESS(f, ptr) ((f) = (ptr)alGetProcAddress(#f))

namespace bs 
{
	/** Effect object functions */
	static LPALGENEFFECTS alGenEffects;
	static LPALDELETEEFFECTS alDeleteEffects;
	static LPALISEFFECT alIsEffect;
	static LPALEFFECTI alEffecti;
	static LPALEFFECTIV alEffectiv;
	static LPALEFFECTF alEffectf;
	static LPALEFFECTFV alEffectfv;
	static LPALGETEFFECTI alGetEffecti;
	static LPALGETEFFECTIV alGetEffectiv;
	static LPALGETEFFECTF alGetEffectf;
	static LPALGETEFFECTFV alGetEffectfv;

	/** Auxiliary Effect Slot object functions. */
	static LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots;
	static LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots;
	static LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot;
	static LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti;
	static LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv;
	static LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf;
	static LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv;
	static LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti;
	static LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv;
	static LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf;
	static LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv;
}