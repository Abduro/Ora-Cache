/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jun-2026 at 06:07:28.184, UTC+4, Batumi, Monday;
	This is OpenGL drawable shape geometry transformation related interface implementation file.
*/
#include "shape.trans.h"

using namespace ::open_gl::shapes::transfer;

#pragma region cls::COper_Base{}

COper_Base::COper_Base (void) : m_changed(false) { this->m_error >>__CLASS__<<__METHOD__<<__s_false = _T("no change yet"); }

TError& COper_Base::Error (void) const { return this->m_error; }

bool COper_Base::Is_changed (void) const { TSafe_Lock(); const bool b_changed = this->m_changed; return b_changed; }
void COper_Base::Is_changed (const bool _b_state) { TSafe_Lock(); this->m_changed = _b_state; }

#pragma endregion
#pragma region cls::CScale{}

CScale::CScale (void) : TBase(),  m_factor(f_def_scale) {}

float CScale::Get (void) const { TSafe_Lock(); const float f_value = this->m_factor;  return f_value; }
void  CScale::Set (const int32_t _n_factor) {
	_n_factor;
	static float f_factor_prev = f_def_scale;

	using namespace ex_ui::draw::open_gl::math::defs;

	TSafe_Lock();
	if (false) {}
	else if (_n_factor > 0) { this->m_factor += float(_n_factor) * f_delta; }
	else if (_n_factor < 0) { this->m_factor += float(_n_factor) * f_delta; if (this->m_factor < f_epsilon) this->m_factor = 0.0f; }
	else { return; }

	if (f_epsilon > abs(this->m_factor - f_factor_prev))
		return;
	else
		f_factor_prev = this->m_factor;

	__trace_warn_2(_T("scale factor: %2.2f;\n"), this->m_factor);

	this->m_changed = true;
	return;
}

#pragma endregion