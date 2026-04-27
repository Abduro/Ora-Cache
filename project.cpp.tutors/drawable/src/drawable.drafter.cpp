/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Apr-2026 at 17:06:23.568, UTC+4, Batumi, Sunday;
	This is Ebo Pack drawable object/drafter interface implementation file;
*/
#include "drawable.drafter.h"

using namespace shared::drawable;

#pragma region cls::CDrafter{}

CDrafter:: CDrafter (void) : TBase() {}
CDrafter:: CDrafter (const CDrafter& _src) : CDrafter() { *this = _src; }
CDrafter::~CDrafter (void) {}

err_code   CDrafter::Prepare (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	return TBase::Error();
}

CDrafter& CDrafter::operator = (const CDrafter& _src) { _src; return *this; }

#pragma endregion