/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Jun-2026 at 11:32:21.897, UTC+4, Batumi, Friday;
	This is OpenGL utility perspective function wrapper interface implementation file;
*/
#include "gl_procs_perspect.h"

using namespace ::open_gl::procs::utils::ver_1_1;

#pragma region cls::c_converter{}

c_converter::c_converter (void) : m_data(0.0) {}
c_converter::c_converter (const float _f_value) : c_converter() { *this << _f_value; }
c_converter::c_converter (const double _d_value) : c_converter() { *this << _d_value; }
c_converter::c_converter (const c_converter& _src) : c_converter() { *this = _src; }

float c_converter::Float (void) const { return static_cast<float>(this->m_data); }
double c_converter::Double (void) const { return this->m_data; }

c_converter& c_converter::operator = (const c_converter& _src) { *this << _src.Double(); return *this; }

double c_converter::operator <<(const float _f_value) { return (this->m_data = static_cast<double>(_f_value)); }
float  c_converter::operator <<(const double _d_value) { return static_cast<float>(this->m_data = _d_value); }

c_converter::operator float (void) const { return static_cast<float>(this->m_data); }
c_converter::operator double (void) const { return this->m_data; }

#pragma endregion
#pragma region str::s_pers_args{}

s_pers_args::s_pers_args (void) : _fov_y(0.0f), _aspect(0.0f), _near(0.0f), _far(0.0f) {}
s_pers_args::s_pers_args (const float _f_fov_y, const float _f_aspect, const float _f_near, const float _f_far)
			: _fov_y(_f_fov_y), _aspect(_f_aspect), _near(_f_near), _far(_f_far) {
}

CString s_pers_args::To_str (void) const {
	static _pc_sz pc_sz_pat = _T("vert fov = %.2f (deg); aspect = %.7f; near = %.7f; far = %.7f;");
	CString cs_out; cs_out.Format(pc_sz_pat, this->_fov_y, this->_aspect, this->_near, this->_far);
	return  cs_out;
}

#pragma endregion
#pragma region cls::CPerspect{}

CPerspect::CPerspect (void) : TBase(), m_data{0.0f} {
	TBase::m_error >>__CLASS__;
}

#define gl_project_mat GL_PROJECTION_MATRIX
static _pc_sz p_err_inv_enum_el = _T("#__e_inv_arg: enum element (%04u) is not accepted");
static _pc_sz p_err_proj_mode = _T("#__e_state: matrix stack is not in projection mode");
const
f_mat_4x4& CPerspect::Ref (void) const {
	return this->m_data;
}

err_code  CPerspect::Get (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	CMatrix matrix;
	if (__failed(matrix.Get(e_mat_type::e_project, this->m_data)))
		TBase::m_error = matrix.Error();

	return TBase::Error();
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/gluperspective ;
err_code  CPerspect::Set (const float _fov_y, const float _f_aspect, const float _f_near, const float _f_far) {
	_fov_y; _f_aspect; _f_near; _f_far;
	TBase::m_error <<__METHOD__<<__s_ok;
	/* query: what result is expected when gluPerspective is called but GL_PROJECTION mode is not set in opengl (to Google AI);
	when gluPerspective is called while GL_MODELVIEW (or another mode) is active instead of GL_PROJECTION,
	the perspective matrix is multiplied onto the active model-view stack instead. This causes several unintended visual issues:
	(1) Distorted, inverted, or Offset geometry: 3D models will undergo camera-like transformations while they are being modeled, severely warping their scale and position;
	(2) Camera tracking issues: any subsequent operations (like glTranslate or glRotate) will treat the perspective matrix as if it were a regular model transformation,
	    breaking the standard rendering pipeline.
	*/
	CMode mode;
	if (__failed(mode.Get()))
		return TBase::m_error = mode.Error();
	if (false == mode.Is_project())
		return TBase::m_error <<(err_code)TErrCodes::eExecute::eState = p_err_proj_mode;

	CMatrix matrix;
	if (__failed(matrix.To_self())) // resets any previous projections;
		return TBase::m_error = matrix.Error();

	::gluPerspective(var(_f_aspect), var(_f_aspect), var(_f_near), var(_f_far));
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	if (u_err_code) {
		TBase::m_error = TString(gluErrorStringWIN(u_err_code));
	}

	return TBase::Error();
}

err_code  CPerspect::Set (const s_pers_args& _args) {
	return this->Set(_args._fov_y, _args._aspect, _args._near, _args._far);
}
const
f_mat_4x4& CPerspect::operator <<(const s_pers_args& _args) {
	_args;
	if (__succeeded(this->Set(_args)))
		this->Get();

	return this->Ref();
}

#pragma endregion
#pragma region cls::CProject{}

CProject::CProject (void) : TBase() { TBase::m_error >>__CLASS__; }

#pragma endregion