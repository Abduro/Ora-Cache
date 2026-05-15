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
using CNear = CPlanes::CNear;

#pragma region cls::c_angle{}

c_angle::c_angle (const float _f_degrees) : m_degrees(0.0f), m_radians(0.0f) { *this << _f_degrees; }
c_angle::c_angle (const c_angle& _src) : c_angle() { *this = _src; }

float c_angle::Degrees (void) const  { return this->m_degrees; } 
float c_angle::Degrees (const float _f_degrees) { this->m_degrees = _f_degrees; return this->m_radians = (this->m_degrees * deg_2_rad); }

float c_angle::Radians (void) const  { return this->m_radians; } 
float c_angle::Radians (const float _f_radians) { this->m_radians = _f_radians; return this->m_degrees = (this->m_radians * rad_2_deg); }

float c_angle::operator << (const float _f_degrees) { return this->Degrees(_f_degrees); }
float c_angle::operator >> (const float _f_radians) { return this->Radians(_f_radians); }

#pragma endregion
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
#pragma region cls::CBase{}

using CBase = CFoV::CBase;

CBase::CBase (void) : m_angle(0.0f) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CBase::Error (void) const { return this->m_error; }

float    CBase::Get (void) const { return this->m_angle; }
err_code CBase::Set (const e_angle _e_value) {
	_e_value;
	this->m_error <<__METHOD__<<__s_ok;

	const float f_angle = float(_e_value);
	if (false == CFoV::Is_valid(f_angle, this->m_error)) {
		__trace_err_ex_2(this->Error()); return this->Error();
	}

	this->m_angle = float(_e_value);

	return this->Error();
}

bool  CBase::Is_valid (void) const { return CFoV::Is_valid(this->Get(), this->m_error); }

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

	CBase::m_angle = 2.0f * ::std::atanf(::std::tanf( _fov_y / 2.0f ) * _aspect);

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

	CBase::m_angle  = 2.0f * ::std::atanf(float(_u_obj_height) / 2.0f * _f_dist);
	CBase::m_angle *= rad_2_deg;

	return CBase::Error();
}

#pragma endregion
#pragma region cls::CCfg{}

CCfg::CCfg (void) : m_fov_y(float(e_angle::e_std_max)), m_fov_x(0.0f) {}

float CCfg::Get_fov_x (void) const { return this->m_fov_x; }
bool  CCfg::Set_fov_x (const uint32_t _u_height, const uint32_t _u_width) {
	_u_height; _u_width;
	/* query: how to calculate a horizontal field of view manually in opengl (to GoogleAI);
	To calculate the horizontal field of view (FOV_{h}) manually in OpenGL, you typically derive it from the vertical field of view (FOV_{v}) and the window's aspect ratio (AR).
	*/
	CAspect aspect(_u_height, _u_width);
	if (aspect.Error())
		return false;  // the error is traced;

	CError error(__CLASS__, __METHOD__,__s_ok);

	if (f_epsilon > this->Get_fov_y()) { __trace_err_ex_2(error <<__e_inv_arg = _T("#__e_inv_arg: fovy value is invalid")); return false; }

	const float f_radians = deg_2_rad * this->Get_fov_y(); // step#0: converts the fov_y angle to radians;
	const float f_tangent = ::std::tanf(f_radians/2.0f);   // step#1: calculates the half-angle tangent;
//	const float f_aspect  = _u_width / float(_u_height);   // step#2: gets aspect ratio (AR);
	const float f_height  = f_tangent * aspect;            // step#3: applies the aspect ratio;
	const float f_angle_h = 2.0f * ::std::atanf(f_height); // step#4: finds the horizontal angle in radians;

	this->m_fov_x = rad_2_deg * f_angle_h;
	return true;
}

float CCfg::Get_fov_y (void) const { return this->m_fov_y; }
void  CCfg::Set_fov_y (const e_angle _e_value) { this->m_fov_y = float(_e_value); }

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

err_code  CFrustum::Update  (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Aspect().Is_valid()) {
		__trace_err_ex_2(this->m_error = this->Aspect().Error()); return this->Error();
	}

	return this->Error();
}

#pragma endregion
#pragma region cls::CPlanes{}

CPlanes::CPlanes (void) : m_far(100.0f), m_near(1.0f) {}

float CPlanes::Far (void) const { return this->m_far; }
void  CPlanes::Far (const float _f_value) { this->m_far = _f_value; }
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
#pragma region cls::CNear{}

CNear::CNear (const float _f_dist) : m_dist(1.0f), m_height(0.0f), m_width(0.0f) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; *this << _f_dist; }
CNear::CNear (const CNear& _src) : CNear() { *this = _src; }

TError& CNear::Error (void) const { return this->m_error; }

float    CNear::Get_dist (void) const { return this->m_dist; }
err_code CNear::Set_dist (const float _f_dist) {
	_f_dist;
	this->m_error <<__METHOD__<<__s_ok;

	if (false == CPlanes::Is_valid(_f_dist, this->m_error)) {
		__trace_err_ex_2(this->Error()); return this->Error();
	}
	this->m_dist = _f_dist;
	if (0.0002f > this->m_dist) {
		__trace_warn_2(_T("the near plane is very close (%.7f);\n"), this->m_dist);
	}
	return this->Error();
}

static _pc_sz p_err_plane_h = _T("#__e_size: plane height is invalid");
static _pc_sz p_err_plane_w = _T("#__e_size: plane width is invalid"); 

float CNear::Height (void) const { return this->m_height; }
err_code CNear::Height (const float _fov_y) {
	_fov_y;
	this->m_error <<__METHOD__<<__s_ok;
	this->m_error <<__METHOD__<<__s_ok;
	/* query: how do I calculate near plane height opengl; (to Google AI);
	Input data:
	(1) virtical angle (top-down) value field of view in radians;
	(2) near plane distance from the camera;
	*/
	if (false == CFoV::Is_valid(_fov_y, this->m_error)) return this->Error();
	if (false == this->Is_valid()) return this->Error();

	this->m_height = 2 * ::std::tanf(_fov_y/2.0f) * this->Get_dist();

	return this->Error();
}

bool  CNear::Is_valid (void) const {
	bool b_valid = CPlanes::Is_valid(this->m_dist, this->m_error);
	if ( b_valid ) { b_valid = f_epsilon < this->m_height; if (false == b_valid) this->m_error <<__e_inv_arg = p_err_plane_h; }
	if ( b_valid ) { b_valid = f_epsilon < this->m_width ; if (false == b_valid) this->m_error <<__e_inv_arg = p_err_plane_w; }
	return b_valid;
}

float CNear::Width (void) const { return this->m_width; }
err_code CNear::Width (const CAspect& _aspect) {
	_aspect;
	this->m_error <<__METHOD__<<__s_ok;

	if (f_epsilon > this->Height()) return this->m_error <<__e_inv_arg = p_err_plane_h;
	if (false == _aspect.Is_valid()) return this->m_error = _aspect.Error();

	this->m_width = this->Height() * _aspect;

	return this->Error();
}

CNear& CNear::operator = (const CNear& _src) { this->m_dist = _src.m_dist; this->m_error = _src.Error(); return *this; }
CNear& CNear::operator <<(const float _f_dist) { this->Set_dist(_f_dist); return *this; }

#pragma endregion