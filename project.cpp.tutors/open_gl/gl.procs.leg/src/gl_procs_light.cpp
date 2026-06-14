/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Jun-2026 at 12:31:47.182, UTC+4, Batumi, Friday;
	This is OpenGL lighting  wrapper interface implementation file;
*/
#include "gl_procs_light.h"

using namespace ::open_gl::procs::ver_1_1;
using CSource = CLight::CSource;

#pragma region cls::CLight{}

CLight::CLight (void) : TBase(), m_enabled(false) { TBase::m_error >>__CLASS__; }

err_code CLight::Get (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	const bool b_enabled = CProperty::Is_enabled(GL_LIGHTING, TBase::m_error);
	if (TBase::Error())
		return TBase::Error();

	this->m_enabled = b_enabled; // updates current state in case of above call success;

	return TBase::Error();
}

err_code CLight::Set (const bool _on_or_off) {
	TBase::m_error <<__METHOD__<<__s_ok;

	CProperty::Is_enabled(GL_LIGHTING, _on_or_off, TBase::m_error);
	if (TBase::Error() == false)
		this->m_enabled = _on_or_off;

	return TBase::Error();
}

bool CLight::Is_on (void) const { return this->m_enabled; }

const
CSource& CLight::Source (void) const { return this->m_source; }
CSource& CLight::Source (void)       { return this->m_source; }

#pragma endregion
#pragma region cls::CSource{}

CSource::CSource (void) : TBase() { TBase::m_error >>__CLASS__; }

#pragma endregion
#pragma region cls::CLtToggle{}

CLtToggle:: CLtToggle (const bool _on_or_off) { (*this)().Set(_on_or_off); }
CLtToggle::~CLtToggle (void) {
	(*this)().Set( ! (*this)().Is_on());
}

const
CLight& CLtToggle::operator ()(void) const { return this->m_light; }
CLight& CLtToggle::operator ()(void)       { return this->m_light; }     

#pragma endregion