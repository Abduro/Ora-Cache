/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jun-2026 at 06:07:28.184, UTC+4, Batumi, Monday;
	This is OpenGL drawable shape geometry transformation related interface implementation file.
*/
#include "shape.trans.h"
#include "mouse.cache.h"
#include "view.port.h"

using namespace ::open_gl::shapes::transfer;

#pragma region cls::COper_Base{}

COper_Base::COper_Base (void) : m_changed(false) { this->m_error >>__CLASS__<<__METHOD__<<__s_false = _T("no change yet"); }

TError& COper_Base::Error (void) const { return this->m_error; }

bool COper_Base::Is_changed (void) const { TSafe_Lock(); const bool b_changed = this->m_changed; return b_changed; }
void COper_Base::Is_changed (const bool _b_state) { TSafe_Lock(); this->m_changed = _b_state; }

#pragma endregion
#pragma region cls::CScale{}

CScale::CScale (void) : TBase(),  m_factor(f_def_scale) { TBase::m_error >>__CLASS__; }

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

	TBase::m_changed = true;
	return;
}

#pragma endregion
#pragma region cls::CMove{}

CMove::CMove (void) : TBase(), m_trans{0.0f}, m_prevs{0} { TBase::m_error >>__CLASS__; }

f_set_3 CMove::Get (void) const { TSafe_Lock(); const f_set_3 f_trans = this->m_trans;
	return f_trans;
}

void CMove::Update (void) {

	const t_size  sz_view = ::Get_ViewPorts().Active().Get();

	const t_point cursor  = ::Get_cursor().CurPos(); // gets current position of the cursor; this is in client window area coord system;
	const t_point pt_curr = {
		cursor.x, sz_view.cy - cursor.y // the cursor position Y-coord, nust be inversed, because OpenGL origin is in left-bottom corner, but window one is at the top-left;
	};
	TSafe_Lock();
	const t_size  sz_delta = {pt_curr.x - this->m_prevs.x, pt_curr.y - this->m_prevs.y}; // calculates the difference;
#if (0)
	// optional: scale factor to adjust translation speed;
    // if the object needs to move exactly with the mouse, 1.0f is used;
	float f_scale_x = 1.0f;
	float f_scale_y = 1.0f;

	this->m_trans.at(0) += float(sz_delta.cx) * f_scale_x;
	this->m_trans.at(1) += float(sz_delta.cy) * f_scale_y;
	this->m_trans.at(2)  = -1.0f ;
#else
	const float f_aspect = float(sz_view.cx) / float(sz_view.cy);
	const f_set_3 f_ndc = {::Get_ViewPorts().Active().Get_X(cursor.x) * f_aspect, ::Get_ViewPorts().Active().Get_Y(cursor.y), 0.0f};
	
	float f_scale_x = 1.0f;
	float f_scale_y = 1.0f;

	this->m_trans.at(0)  = f_ndc.at(0) * f_scale_x;
	this->m_trans.at(1)  = f_ndc.at(1) * f_scale_y;
	this->m_trans.at(2)  = f_ndc.at(2);
#endif
	// updates previous mouse position;
	this->m_prevs = pt_curr;
	TBase::m_changed = true;

//	__trace_info_2(_T("translate: x = %2.2f;y = %4.2f;z = %4.2f;\n"), this->m_trans.at(0), this->m_trans.at(1), this->m_trans.at(2));
}

#pragma endregion