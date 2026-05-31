/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-May-2026 at 17:45:24.752, UTC+4, Batumi, Saturday;
	This is OpenGL v.1.1 viewport related function set wrapper interface implementation file;
*/
#include "gl_procs_viewport.h"

namespace open_gl { namespace procs { namespace ver_1_1 {}}}

using namespace open_gl::procs;
using namespace open_gl::procs::ver_1_1;
using namespace open_gl::procs::viewport;

#pragma region cls::CParams{}

static _pc_sz p_err_param_not_init = _T("#__e_inv_state: viewport params are not inited");

CParams::CParams (void) : TBase(), m_values() { TBase::m_error >>__CLASS__<<__e_not_inited = p_err_param_not_init; }

err_code  CParams::Get (i_values& _values, CError& _error) {
	_values; _error;
	_values.fill(0);
	// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetintegerv ;
	CParam param;
	if (__failed(param.Get_ptr(GL_VIEWPORT, _values.data())))
		_error = param.Error();

	return _error;
}

err_code  CParams::Get (void) {
	this->TBase::m_error <<__METHOD__<<__s_ok; return CParams::Get(this->Value(), TBase::m_error);
}

err_code  CParams::Get (t_point& _offset, t_size_u& _size, CError& _error) {
	_offset; _size; _error;
	i_values values;
	if (__failed(CParams::Get(values, _error))) { 
		_offset = values.Offset(); _size = values.Size();
	}
	return _error;
}

err_code  CParams::Is_valid (const i_values& _values, CError& _error) {
	_values; _error;
	static _pc_sz p_err_x_offset = _T("#__e_inv_arg: Offset by x (%d) is equal or greater than width (%u)");
	static _pc_sz p_err_y_offset = _T("#__e_inv_arg: Offset by y (%d) is equal or greater than height (%u)");

	if (0 == _values.at(3)) return _error <<__e_inv_arg = _T("#__e_inv_arg: input height is 0");
	if (0 == _values.at(2)) return _error <<__e_inv_arg = _T("#__e_inv_arg: input width is 0");

	if (abs(_values.at(0)) >= _values.at(2)) return _error <<__e_inv_arg = TString().Format(p_err_x_offset, _values.at(0), _values.at(2));
	if (abs(_values.at(1)) >= _values.at(3)) return _error <<__e_inv_arg = TString().Format(p_err_y_offset, _values.at(1), _values.at(3));

	return _error << __s_ok;
}

err_code  CParams::Is_valid (void) {
	TBase::m_error <<__METHOD__<<__s_ok; return CParams::Is_valid(this->Value().Offset(), this->Value().Size(), TBase::m_error);
}

err_code  CParams::Is_valid (const t_point& _offset, const t_size_u& _size, CError& _error) {
	_offset; _size; _error;
	i_values values; values << _offset << _size;
	return CParams::Is_valid(values, _error);
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/glviewport ;
err_code  CParams::Set (const i_values& _values, CError& _error) {
	_values; _error;
	if (__failed(CParams::Is_valid(_values, _error))) return _error;
	/* possible error codes:
	GL_INVALID_OPERATION : the function was called between a call to glBegin and the corresponding call to glEnd;
	GL_INVALID_VALUE     : either width or height was negative;
	*/
	::glViewport(_values.at(0), _values.at(1), _values.at(2), _values.at(3));
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ) {
	case GL_INVALID_OPERATION : { _error << (err_code) TErrCodes::eExecute::eOperate = p_err_inv_oper; } break;
	case GL_INVALID_VALUE :
		_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: either width (%d) or height (%d) was negative"),  _values.at(2), _values.at(3)); break;
	default:
		if (!!u_err_code)
			_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return _error;
}

err_code  CParams::Set (const i_values& _values) {
	_values;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (__succeeded(CParams::Set(_values, TBase::m_error)))
		this->Value() = _values;
	return TBase::Error();
}

err_code  CParams::Set (const t_point& _offset, const t_size_u& _size, CError& _error) {
	_offset; _size; _error;
	return CParams::Set(i_values(_offset, _size), _error);
}

err_code  CParams::Set (void) {
	return CParams::Set(this->Value(), TBase::m_error);
}

const
i_values& CParams::Value (void) const { return this->m_values; }
i_values& CParams::Value (void)       { return this->m_values; }

_pc_sz    CParams::To_str (const i_values& _values) {
	_values;
	static  _pc_sz  p_values_pat = _T("Offset >> {x = %04d; y = %04d}; dims >> {w = %04d; h = %04d}");
	static  CString cs_out; cs_out.Format(p_values_pat, _values.at(0), _values.at(1), _values.at(2), _values.at(3));
	return (_pc_sz) cs_out;
}

_pc_sz    CParams::To_str (const t_point& _offset, const t_size_u& _size) { return CParams::To_str(i_values(_offset, _size)); }

#pragma endregion
#pragma region cls::CViewport{}

CViewport::CViewport (const uint32_t _u_width, const uint32_t _u_height) : m_size{_u_width, _u_height}, m_offset{0} { TBase::m_error >>__CLASS__; }
const
t_size_u& CViewport::Get (void) const { return this->m_size; }

float   CViewport::Get_X (const int32_t _n_x) const {
	_n_x;
	if (0 == this->Get().cx) // the division by zero is not defined;
		return 0.0f;
	// https://en.wikipedia.org/wiki/Division_(mathematics) ; >> Dividend / Divisor = Quotient; (Remainder) : left amount;
#if (1)
	const float f_divisor = (float)this->Get().cx;
	return 2.0f * (float)_n_x/f_divisor - 1.0f;
#else
	return 2.0f * ((float)_n_x + 0.5f)/(float)(this->Get().cx / 2) - 1.0f
#endif
}

float   CViewport::Get_Y (const int32_t _n_y) const {
	_n_y;
	if (0 == this->Get().cy) // the division by zero is not defined;
		return 0.0f;
#if (1)
	return 1.0f - 2.0f * (float)_n_y/(float)this->Get().cy;
#else
	return 1.0f - ((float)_n_y + 0.5f)/(float)(this->Get().cy / 2);
#endif
}

// https://stackoverflow.com/questions/8491247/c-opengl-convert-world-coords-to-screen2d-coords#comment43751183_8493759 ;
// https://learn.microsoft.com/en-us/windows/win32/opengl/glviewport#remarks ;
int32_t CViewport::Get_X (const float _f_x) const {
	_f_x;
	const int32_t n_x = int32_t((_f_x + 1.0f) / 2.0f) * this->Get().cx + this->m_offset.x;
	return n_x;
}

int32_t CViewport::Get_Y (const float _f_y) const {
	_f_y;
	const int32_t n_y = int32_t((1.0f - _f_y) / 2.0f) * this->Get().cy + this->m_offset.y;
	return n_y;
}

bool CViewport::Is_valid (void) const {
	return CViewport::Is_valid(this->m_size, TBase::m_error);
}
bool CViewport::Is_valid (const t_size_u& _u_size, CError& _err) {
	_u_size; _err;
	if (0 == _u_size.cx || 0 == _u_size.cy) {
		_err <<__METHOD__<<__e_inv_arg = TString().Format(_T("#__e_inv_size: cx=0x%04x, cy=0x%04x"), _u_size.cx, _u_size.cy);
		return false;
	}
	else return true;
}

const
CParams&  CViewport::Params (void) const { return this->m_params; }
CParams&  CViewport::Params (void)       { return this->m_params; }

err_code  CViewport::To_pos (const t_size_u& _u_size, const uint32_t _in_x, const uint32_t _in_y, f_set_3& _pos_out, CError& _err) {
	_u_size; _in_x; _in_y; _pos_out; _err;
	if (CViewport::Is_valid(_u_size, _err) == false)
		return _err;
	// ToDo: this requires testing to find out which expression works faster;
#if (1)
	// https://discourse.glfw.org/t/converting-between-screen-coordinates-and-pixels/1841/2 ; thanks @dougbinks for good answer;
	_pos_out[0] = 2.0f * (float)_in_x/(float)_u_size.cx - 1.0f; // x;
	_pos_out[1] = 1.0f - 2.0f * (float)_in_y/(float)_u_size.cy; // y;
	_pos_out[2] = 0.0f; // z;
#else
	// https://stackoverflow.com/questions/40068191/opengl-screen-to-world-coordinates-conversion ;
	_pos_out = {2.0f * ((float)_in_x + 0.5f)/(float)(_u_size.cx / 2) - 1.0f, 1.0f - ((float)_in_y + 0.5f)/(float)(_u_size.cy / 2), 0.0f};
#endif
	return _err;
}

#pragma endregion