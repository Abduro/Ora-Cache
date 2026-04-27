/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Apr-2026 at 17:06:23.568, UTC+4, Batumi, Sunday;
	This is Ebo Pack drawable object/drafter interface implementation file;
*/
#include "drawable.drafter.h"

using namespace shared::drawable;

#pragma region cls::CDrafter{}

CDrafter:: CDrafter (void) : TBase() { TBase::m_error >>__CLASS__; }
//CDrafter:: CDrafter (const CDrafter& _src) : CDrafter() { *this = _src; }
CDrafter::~CDrafter (void) {}

err_code   CDrafter::OnCreate (const HWND _h_surface) {
	_h_surface;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (__failed(this->View().Create(_h_surface))) {
		__trace_err_ex_2(TBase::m_error = this->View().Error()); return TBase::Error();
	} else {}

	return TBase::Error();
}

err_code   CDrafter::OnDestroy (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (__failed(this->View().Destroy())) {
		__trace_err_ex_2(TBase::m_error = this->View().Error()); return TBase::Error();
	} else {}

	return TBase::Error();
}

void CDrafter::Run (void) {
	TBase::Run();
}

const
CModel& CDrafter::Model (void) const { return this->m_model; }
CModel& CDrafter::Model (void)       { return this->m_model; }
const
CView&  CDrafter::View (void) const { return this->m_view; }
CView&  CDrafter::View (void)       { return this->m_view; }

//CDrafter& CDrafter::operator = (const CDrafter& _src) { _src; return *this; }

#pragma endregion