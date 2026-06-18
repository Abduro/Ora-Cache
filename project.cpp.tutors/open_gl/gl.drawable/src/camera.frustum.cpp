/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-May-2026 at 09:45:17.263, UTC+4, Batumi, Wednesday;
	This is OpenGL tutorials' virtual camera frustum interface implementation file;
*/
#include "camera.frustum.h"

using namespace ::open_gl::camera;
using namespace ::open_gl::camera::frustum;

namespace open_gl { namespace camera { namespace frustum { namespace _impl {

	class CValidator {
	public:
		CValidator (void) = default; CValidator (const CValidator&) = delete; CValidator (CValidator&&) = delete; ~CValidator (void) = default;

		static bool Validate (const t_size_u& _size, CError& _error) {
			_size; _error;
			const bool b_valid = !!_size.cx && !!_size.cy;
			if (false == b_valid)
				_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: given size (h=%u;w=%u) is not valid"), _size.cy, _size.cx);
			return b_valid;
		}

	private:
		CValidator& operator = (const CValidator&) = delete; CValidator& operator = (CValidator&&) = delete;
	};

}}}} using namespace _impl;

#ifndef __H
#define __H(_rect) (_rect.bottom - _rect.top)
#endif
#ifndef __W
#define __W(_rect) (_rect.right - _rect.left)
#endif
using CHorz = CFoV::CHorz;
using CVert = CFoV::CVert;

using CFar  = CPlanes::CFar;
using CNear = CPlanes::CNear;

#pragma region cls::CAspect{}

CAspect::CAspect (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_not_init: the size is not set"); }
CAspect::CAspect (const HWND _h_surface) : CAspect() { *this << _h_surface; }
CAspect::CAspect (const uint32_t _u_height, const uint32_t _u_width) : CAspect() { this->Set(_u_height, _u_width); }
CAspect::CAspect (const CAspect& _src) : CAspect() { *this = _src; }

TError&  CAspect::Error (void) const { return this->m_error; }

float    CAspect::Ratio (void) const {
	this->m_error <<__METHOD__<<__s_ok;
	if (false == this->Is_valid()) {
		__trace_err_ex_2(this->m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: the size (w=%u;h=%u) is not valid"), this->m_size.cx, this->m_size.cy));
		return 0.0f;
	}
	return float(this->m_size.cx) / float(this->m_size.cy);
}
bool  CAspect::Is_valid (void) const { return CAspect::Is_valid(this->m_size, this->m_error); }
bool  CAspect::Is_valid (const t_size_u& _size, CError& _error) {
	return CValidator::Validate(_size, _error);
}

err_code CAspect::Set (const HWND _h_surface) {
	this->m_error <<__METHOD__<<__s_ok;
	if (nullptr == _h_surface || false == !!::IsWindow(_h_surface)) {
		__trace_err_ex_2(this->m_error <<__e_hwnd = _T("#__e_hwnd: input window handle is invaled")); return this->Error();
	}
	t_rect cli_rect = {0};
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclientrect ;
	if (0 == ::GetClientRect(_h_surface, &cli_rect)) {
		this->m_error.Last();
		__trace_err_ex_2(this->m_error); return this->Error();
	}

	this->m_size = {(uint32_t)__W(cli_rect), (uint32_t)__H(cli_rect)};
	return this->Error();
}

err_code CAspect::Set (const uint32_t _u_height, const uint32_t _u_width) {
	this->m_error <<__METHOD__<<__s_ok;
	if (0 == _u_height) { __trace_err_ex_2(this->m_error <<__e_inv_arg = _T("#__e_inv_arg: input height value is invalid")); return this->Error(); }
	if (0 == _u_width) { __trace_err_ex_2(this->m_error <<__e_inv_arg = _T("#__e_inv_arg: input width value is invalid")); return this->Error(); }

	this->m_size = {_u_width, _u_height};
	return this->Error();
}

CAspect& CAspect::operator = (const CAspect& _src) { this->m_size = _src.m_size; return *this; }
const
t_size_u& CAspect::operator <<(const HWND _h_surface) { this->Set(_h_surface); return this->m_size; }

CAspect::operator float (void) const { return this->Ratio(); }

#pragma endregion
#pragma region cls::CFoV::CBase{}

CFoV::CBase::CBase (void) : m_angle(0.0f) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError&  CFoV::CBase::Error (void) const { return this->m_error; }
const
c_angle& CFoV::CBase::Get (void) const { return this->m_angle; }
err_code CFoV::CBase::Set (const e_angle _e_value) {
	_e_value;
	this->m_error <<__METHOD__<<__s_ok;

	const float f_angle = float(_e_value);
	if (false == CFoV::Is_valid(f_angle, this->m_error)) {
		__trace_err_ex_2(this->Error()); return this->Error();
	}

	this->m_angle << float(_e_value);

	return this->Error();
}

bool  CFoV::CBase::Is_valid (void) const { return CFoV::Is_valid(this->Get().Deg(), this->m_error); }

#pragma endregion
#pragma region cls::CFoV{}

CFoV::CFoV (void) {}

_pc_sz CFoV::Class (void) { static CString cs_cls; if (cs_cls.IsEmpty()) cs_cls = __CLASS__; return (_pc_sz) cs_cls; }

bool   CFoV::Is_valid (const float _f_angle, CError& _error) {
	_f_angle; _error;
	const bool b_valid = float(e_angle::e_narrow_min) <= _f_angle && _f_angle <= float(e_angle::e_wide_max);
	if (false == b_valid)
		_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: input angle (%.7f) is invalid"), _f_angle);

	return b_valid;
}
const
CHorz& CFoV::Horz (void) const { return this->m_horz; }
CHorz& CFoV::Horz (void)       { return this->m_horz; }
const
CVert& CFoV::Vert (void) const { return this->m_vert; }
CVert& CFoV::Vert (void)       { return this->m_vert; }

#pragma endregion
#pragma region cls::CHorz{}

// otherwise compiler error C2371: 'CY': redefinition; different basic types note: see declaration of 'tagCY'; wtypes.h(670);

CHorz::CHorz (void) : CBase() { CBase::m_error >> TString().Format(_T("%s::%s"), CFoV::Class(), (_pc_sz) __CLASS__); }

err_code CHorz::Set (const float _fov_y, const CAspect& _aspect) {
	_fov_y; _aspect;
	CBase::m_error <<__METHOD__<<__s_ok;
	/* query: how to calculate horizontal field of view opengl; (to Google AI)
	use the relationship between the vertical field of view (vFOV) and the window's aspect ratio (AR);
	*/
	if (false == CFoV::Is_valid(_fov_y, CBase::m_error)) return CBase::Error();
	if (false == _aspect.Is_valid()) return CBase::m_error = _aspect.Error();

	CBase::m_angle >> 2.0f * ::std::atanf(::std::tanf( c_angle(_fov_y).Rad() / 2.0f ) * _aspect); // the operator of assigning radians to angle is not readable :(

	return CBase::Error();
}

#pragma endregion
#pragma region cls::CVert{}

CVert::CVert (void) : CBase() { CBase::m_error >> TString().Format(_T("%s::%s"), CFoV::Class(), (_pc_sz) __CLASS__); }

err_code CVert::Set (const float _f_dist, const uint32_t _u_obj_height) {
	_f_dist; _u_obj_height;
	CBase::m_error <<__METHOD__<<__s_ok;
	/* query: how to calculate vertical field of view opengl; (to Google AI)
	(1) calculation from object dimensions: fovy = 2 * atan( _u_obj_height / 2 * _f_dist);
	*/
	if (false == CPlanes::Is_valid(_f_dist, CBase::m_error)) return CBase::Error();

	CBase::m_angle >> 2.0f * ::std::atanf((float(_u_obj_height) / 2.0f ) / _f_dist);

	return CBase::Error();
}

err_code CVert::Set (const float _f_horz, const CAspect& _aspect) {
	_f_horz; _aspect;
	CBase::m_error <<__METHOD__<<__s_ok;

	return CBase::Error();
}

err_code CVert::Set (const e_angle _angle) {
	_angle;
	CBase::m_error <<__METHOD__<<__s_ok;
	CBase::m_angle << float(_angle); // it is not necessary to check for error in case of setting pre-defined angle value;
	return CBase::Error();
}

#pragma endregion
#pragma region cls::CCfg{}

CCfg::CCfg (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CCfg::Default (void) {
	this->m_error <<__METHOD__<<__s_ok;
	// for drawing a view grid 10.0f is enough for far plane;
	CFoV& fov = this->FoV();
	if (__failed(fov.Vert().Set(CFoV::e_angle::e_std_max))) { return this->m_error = fov.Vert().Error(); }
	if (__failed(this->Planes().Far() << 10.0f)) { return this->m_error = this->Planes().Far().Error(); }
	if (__failed(this->Planes().Near() << 1.0f)) { return this->m_error = this->Planes().Near().Error(); }

	return this->Error();
}

TError& CCfg::Error (void) const { return this->m_error; }

const
CFoV& CCfg::FoV (void) const { return this->m_fov; }
CFoV& CCfg::FoV (void)       { return this->m_fov; }
const
CPlanes& CCfg::Planes (void) const { return this->m_planes; }
CPlanes& CCfg::Planes (void)       { return this->m_planes; }

#pragma endregion
#pragma region cls::CFrustum{}

CFrustum::CFrustum (void) : m_proj(true) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_not__inited: frustum is not set");}
const
CAspect&  CFrustum::Aspect (void) const { return this->m_aspect; }
CAspect&  CFrustum::Aspect (void)       { return this->m_aspect; }
const
CCfg&     CFrustum::Cfg (void) const { return this->m_cfg; }
CCfg&     CFrustum::Cfg (void)       { return this->m_cfg; }

TError&   CFrustum::Error (void) const { return this->m_error; }

const
c_mat4x4& CFrustum::Project (void) const { return this->m_proj; }
c_mat4x4& CFrustum::Project (void)       { return this->m_proj; }

#include <array>

err_code  CFrustum::Update  (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Aspect().Is_valid()) {
		__trace_err_ex_2(this->m_error = this->Aspect().Error()); return this->Error();
	}
	const
	CFoV::CVert& fov_y = this->Cfg().FoV().Vert();
	CNear& hither = this->Cfg().Planes().Near(); //'near' is defined as the macro in minwindef.h line 95;

	// the step #1: the near plane distance is set by default to 1.0f, but for test purpose only it is set again here;
	if (__failed(hither.Dist(1.0f)))
		return this->m_error = hither.Error();
	// the step #2: calculating the near plane height by appliying specific vertical field of view;
	if (__failed(hither.Height(fov_y.Get().Deg())))
		return this->m_error = hither.Error();
	if (__failed(hither.Width(this->Aspect())))
		return this->m_error = hither.Error();
	// the step #3: setting the projective matrix;
	// sets left, right, top and bottom values from the near plane size;
	const float r_ = hither.Half().width();  const float l_ = -r_;
	const float t_ = hither.Half().height(); const float b_ = -t_;
	const float n_ = hither.Dist();
	const float f_ = this->Cfg().Planes().Far().Dist();
	/* cols: #0       #1       #2           #3
	rows #0  2n/(r-l) 0        (r+l)/(r-l)  0
	     #1  0        2n/(t-b) (t+b)/(t-b)  0
	     #2  0        0       -(f+n)/(f-n) -(2fn)/(f-n)
	     #3  0        0       -1            0
	*/
#if (0)
	ex_ui::draw::open_gl::math::t_seq_4x4 mat = {{
		2.0f * n_/(r_ - l_), 0.0f, 0.0f, 0.0f,   // the col #0;
		0.0f, 2.0f * n_/(t_ - b_), 0.0f, 0.0f,   // the col #1;
		(r_ + l_)/(r_ - l_), (t_ + b_)/(t_ - b_), -(f_ + n_)/(f_ - n_), -1.0f, // the col #2;
		0.0f, 0.0f, -(2.0f * f_ * n_)/(f_ - n_)  // the col #3;
	}};
	this->m_proj << mat;
#else
	// to-do: checking for possible division by zero is required;
	c_mat4x4& m_4 = this->m_proj;
	m_4(0, 0) = 2.0f * n_/(r_ - l_);
	m_4(1, 1) = 2.0f * n_/(t_ - b_);
	m_4(2, 0) = (r_ + l_)/(r_ - l_); m_4(2, 1) = (t_ + b_)/(t_ - b_); m_4(2, 2) = -(f_ + n_)/(f_ - n_); m_4(2, 3) = -1.0f;
	m_4(3, 2) =-(2.0f * f_ * n_)/(f_ - n_); m_4(3, 3) = 0.0f;
#endif
	return this->Error();
}

#pragma endregion
#pragma region cls::CFar{}

CFar::CFar (void) : CPlane() { CPlane::m_error >> TString().Format(_T("CPlanes::%s"), (_pc_sz)__CLASS__); }
CFar::CFar (const float _f_dist) : CFar() {  *this << _f_dist; }
CFar& CFar::operator = (const CFar& _src)  { (CPlane&)*this = (const CPlane&)_src; return *this; } 

#pragma endregion
#pragma region cls::CNear{}

CNear::CNear (void) : CPlane() { CPlane::m_error >> TString().Format(_T("CPlanes::%s"), (_pc_sz)__CLASS__); }
CNear::CNear (const float _f_dist) : CNear() { *this << _f_dist; }
CNear::CNear (const CNear& _src) : CNear() { *this = _src; }

CNear& CNear::operator = (const CNear& _src) { CPlane::m_dist = _src.m_dist; this->m_error = _src.Error(); return *this; }

#pragma endregion

#pragma region cls::CPlane{}

static _pc_sz p_err_plane_h = _T("#__e_size: plane height is invalid");
static _pc_sz p_err_plane_w = _T("#__e_size: plane width is invalid"); 

CPlane::CPlane (void) : m_dist(0.0f) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CPlane::CPlane (const CPlane& _src) : CPlane() { *this = _src; }

float    CPlane::Dist (void) const { return this->m_dist; }
err_code CPlane::Dist (const float _f_dist) {
	_f_dist;
	this->m_error <<__METHOD__<<__s_ok;

	if (false == CPlanes::Is_valid(_f_dist, this->m_error)) {
		__trace_err_ex_2(this->Error()); return this->Error();
	}
	this->m_dist = _f_dist;

	return this->Error();
}

TError&  CPlane::Error (void) const { return this->m_error; }

const s_size& CPlane::Half (void) const { return this->m_half; }
const s_size& CPlane::Size (void) const { return this->m_size; }

float    CPlane::Height (void) const { return this->m_size.height(); }
err_code CPlane::Height (const float _fov_y) {
	_fov_y;
	this->m_error <<__METHOD__<<__s_ok;
	/* query: how do I calculate near plane height opengl; (to Google AI);
	Input data:
	(1) virtical angle (top-down) value field of view in radians;
	(2) near plane distance from the camera;
	*/
	if (false == CFoV::Is_valid(_fov_y, this->m_error)) return this->Error();
	if (false == CPlanes::Is_valid(this->Dist(), this->m_error)) return this->Error();

	this->m_half.height() = ::std::tanf((c_angle() << _fov_y)/2.0f) * this->Dist();
	this->m_size.height() = 2.0f * this->m_half.height();

	return CPlane::Error();
}

bool  CPlane::Is_valid (void) const {
	bool b_valid = CPlanes::Is_valid(this->m_dist, this->m_error);
	if ( b_valid ) { b_valid = f_epsilon < this->m_size.height(); if (false == b_valid) this->m_error <<__e_inv_arg = p_err_plane_h; }
	if ( b_valid ) { b_valid = f_epsilon < this->m_size.width() ; if (false == b_valid) this->m_error <<__e_inv_arg = p_err_plane_w; }
	return b_valid;
}

float    CPlane::Width (void) const { return this->m_size.width(); }
err_code CPlane::Width (const CAspect& _aspect) {
	_aspect;
	this->m_error <<__METHOD__<<__s_ok;

	if (f_epsilon > this->Height()) return this->m_error <<__e_inv_arg = p_err_plane_h;
	if (false == _aspect.Is_valid()) return this->m_error = _aspect.Error();

	this->m_half.width() = this->Half().height() * _aspect;
	this->m_size.width() = this->Height() * _aspect;

	return this->Error();
}

CPlane&  CPlane::operator = (const CPlane& _src) {
	this->m_dist = _src.m_dist; this->m_size = _src.m_size; this->m_error = _src.Error(); return *this;
}
err_code CPlane::operator <<(const float _f_dist) { return this->Dist(_f_dist); }

CPlane::operator float (void) const { return this->Dist(); }

#pragma endregion
#pragma region cls::CPlanes{}

CPlanes::CPlanes (void)/* : m_far(100.0f), m_near(1.0f)*/ {}
const
CFar& CPlanes::Far (void) const { return this->m_far; }
CFar& CPlanes::Far (void)       { return this->m_far; }
const
CNear& CPlanes::Near (void) const { return this->m_near; }
CNear& CPlanes::Near (void)       { return this->m_near; }

static _pc_sz p_err_dist_small = _T("#__e_inv_arg: distance value (%.7f) to small or negative");
static _pc_sz p_err_dist_out = _T("#__e_inv_arg: distance value (%.7f) is out of range");

bool CPlanes::Is_valid (const float _f_dist, CError& _error) {
	_f_dist; _error;
	if (f_epsilon > _f_dist) { _error <<__e_inv_arg = TString().Format(p_err_dist_small, _f_dist); return false; }
	if (CPlanes::f_dist_min > _f_dist || _f_dist > CPlanes::f_dist_max) { _error <<__e_inv_arg = TString().Format(p_err_dist_out, _f_dist); return false; }
	return true;
}

bool CPlanes::Is_valid (const t_size_u& _size, CError& _error) {
	return CValidator::Validate(_size, _error);
}

#pragma endregion