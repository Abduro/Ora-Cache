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
#pragma region cls::CMove{}

CMove::CMove (void) : TBase(), m_where{0.0f}, m_cursor{0} {
	TBase::m_error >>__CLASS__;
	const t_size  sz_view = ::Get_ViewPorts().Active().Get();
	m_cursor.x = sz_view.cx / 2;
	m_cursor.y = sz_view.cy / 2;
}

f_set_3 CMove::Get (void) const { TSafe_Lock(); const f_set_3 f_where = this->m_where;
	return f_where;
}
err_code CMove::Set (const CEvent& _event) {
	_event;
	if (this->Is_accepted(_event) == false) return __s_false;

	this->Update();
	return __s_ok;
}

bool CMove::Is_accepted (const CEvent& _event) const {

	if (_event.Buttons().The_last().What() != e_button::e_left) return false;
	if (_event.Buttons().The_last().Is_pressed() == false) return false;
	if (_event.Keys().Is_ctrl()) return false;
	if (_event.Keys().Is_shift()) return false;
	return true;
}

void CMove::Update (void) {

	const t_size  sz_view = ::Get_ViewPorts().Active().Get();

	const t_point cursor  = ::Get_cursor().CurPos(); // gets current position of the cursor; this is in client window area coord system;
	const t_point pt_curr = {
		cursor.x, sz_view.cy - cursor.y // the cursor position Y-coord, must be inversed, because OpenGL origin is in left-bottom corner, but window one is at the top-left;
	};
	TSafe_Lock();
	const t_size  sz_delta = {pt_curr.x - this->m_cursor.x, pt_curr.y - this->m_cursor.y}; // calculates the difference;
#if (0)
	// optional: scale factor to adjust translation speed;
    // if the object needs to move exactly with the mouse, 1.0f is used;
	float f_scale_x = 1.0f;
	float f_scale_y = 1.0f;

	this->m_trans.at(0) += float(sz_delta.cx) * f_scale_x;
	this->m_trans.at(1) += float(sz_delta.cy) * f_scale_y;
	this->m_trans.at(2)  = -1.0f ;
#else
	this->m_cursor.x += sz_delta.cx;
	this->m_cursor.y += sz_delta.cy;

	const float f_aspect = float(sz_view.cx) / float(sz_view.cy);
	const f_set_3 f_ndc = {::Get_ViewPorts().Active().Get_X(this->m_cursor.x) * f_aspect, ::Get_ViewPorts().Active().Get_Y(this->m_cursor.y), 0.0f};
	
	this->m_where.at(0)  = f_ndc.at(0) /** f_sens*/;
	this->m_where.at(1)  = f_ndc.at(1) /** f_sens*/;
	this->m_where.at(2)  = f_ndc.at(2);
#endif
	// updates previous mouse position;
//	this->m_cursor = pt_curr;
	TBase::m_changed = true;

//	__trace_info_2(_T("translate: x = %2.2f;y = %4.2f;z = %4.2f;\n"), this->m_trans.at(0), this->m_trans.at(1), this->m_trans.at(2));
}

#pragma endregion
#pragma region cls::CRotate{}

CRotate::CRotate (void) : TBase(), m_curs_prev{0} { TBase::m_error >>__CLASS__; }

err_code CRotate::Apply (void) {
#if (0)
	if (__failed(TBase::m_opers.Rotate(this->m_angles[e_around::e_x].Rad(), {1.0f, 0.0f, 0.0f}))) { __trace_err_ex_2(TBase::m_opers.Error()); }
	if (__failed(TBase::m_opers.Rotate(this->m_angles[e_around::e_y].Rad(), {0.0f, 1.0f, 0.0f}))) { __trace_err_ex_2(TBase::m_opers.Error()); }
#else
	if (__failed(TBase::m_opers.Rotate(this->m_angles[e_around::e_z].Rad(), {0.0f, 0.0f, 1.0f}))) { __trace_err_ex_2(TBase::m_opers.Error()); }
#endif
	return __s_ok;
}

bool  CRotate::Is_accepted (const CEvent& _event) const {

	if (_event.Buttons().The_last().What() != e_button::e_left) return false;
	if (_event.Buttons().The_last().Is_pressed() == false) return false;
	if (_event.Keys().Is_ctrl() == false) return false;
	return true;
}

const
c_angle& CRotate::Get (const e_around _axis) const {
	_axis;
	if (false){}
	else if (e_around::e_x == _axis) return this->m_angles[0];
	else if (e_around::e_y == _axis) return this->m_angles[1];
	else if (e_around::e_z == _axis) return this->m_angles[2];
	else {
		TBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: axis index (%u) is unknown"), _axis);
		static c_angle inv_angle; return inv_angle;
	}
}

err_code CRotate::Set (const CEvent& _event) {
	_event;
	if (false == this->Is_accepted(_event)) return __s_false; // not handled;

	const t_point pt_delta = { _event.Coords().Get().x - this->m_curs_prev.x, _event.Coords().Get().y - this->m_curs_prev.y };
#if (0)
	this->m_angles[e_around::e_x] >> pt_delta.y * CRotate::f_sens; // the angle around X-axis is calculated from vertical mouse movement;
	this->m_angles[e_around::e_y] >> pt_delta.x * CRotate::f_sens; // the angle around Y-axis is calculated from horizontal mouse movement;
	this->m_angles[e_around::e_z] >> 0.0f; // is not considered yet; 
#else
	this->m_angles[e_around::e_x] >> 0.0f;
	this->m_angles[e_around::e_y] >> 0.0f;
	this->m_angles[e_around::e_z] >> pt_delta.y * CRotate::f_sens;
#endif
	TBase::m_changed = true;
	return __s_ok; // handled;
}

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