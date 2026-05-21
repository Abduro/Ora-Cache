/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-May-2026 at 00:33:57.629, UTC+4, Batumi, Tuesday;
	This is OpenGL ver.1.1 common basic interface implementation file;
*/
#include "gl_procs_basic.h"

using namespace open_gl::procs::ver_1_1;

#pragma region cls::CBasic{}

CBasic::CBasic (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError&  CBasic::Error (void) const { return this->m_error; }

#pragma endregion
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
#pragma region cls::CProperty{}

static _pc_sz p_err_prop_id_inv = _T("#__e_inv_arg: input '_prop_id' (%d) is not valid");
static _pc_sz p_err_prop_id_set = _T("#__s_false: '_prop_id' (%u) is already set");

CProperty::CProperty (const uint32_t _prop_id) : m_prop_id (_prop_id) { TBase::m_error >>__CLASS__; }

bool     CProperty::Is_enabled (void) const {
	return CProperty::Is_enabled(this->PropId(),this->m_error);
}

err_code CProperty::Is_enabled (const bool _yes_or_no) {
	return CProperty::Is_enabled(this->PropId(), _yes_or_no,this->m_error);
}

bool     CProperty::Is_enabled (const uint32_t _prop_id, CError& _error) {
	_prop_id; _error;
	bool b_enabled = CProperty::Is_valid(_prop_id, _error);
	if (_error)
		return b_enabled;
	// https://learn.microsoft.com/en-us/windows/win32/opengl/glisenabled ; error codes: {GL_INVALID_ENUM|GL_INVALID_OPERATION};
	b_enabled = !!::glIsEnabled (_prop_id);
	uint32_t u_err_code = CErr_ex().Get_code(); GL_TRUE;
	switch ( u_err_code ) {
	case GL_INVALID_ENUM : { _error << __e_inv_arg = TString().Format(p_err_inv_enum, _prop_id, _prop_id); }  break;
	case GL_INVALID_OPERATION : { _error << (err_code) TErrCodes::eExecute::eOperate = p_err_inv_oper; } break;
	default:
		if (!!u_err_code)
			_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	if (_error)
		b_enabled = false;

	return b_enabled;
}

err_code CProperty::Is_enabled (const uint32_t _prop_id, const bool _yes_or_no, CError& _error) {
	_prop_id; _yes_or_no; _error;
	if (false == CProperty::Is_valid(_prop_id, _error))
		return _error;

	if (_yes_or_no == CProperty::Is_enabled(_prop_id, _error) && false == _error) // there is no sense to enable/disable property state if it is already set;
		return _error;

	if (true == _yes_or_no) {
		::glEnable(_prop_id); // https://learn.microsoft.com/en-us/windows/win32/opengl/glenable ;
	} else {
		::glDisable(_prop_id); // https://learn.microsoft.com/en-us/windows/win32/opengl/gldisable ;
	}
	uint32_t u_err_code = CErr_ex().Get_code(); GL_TRUE;
	switch ( u_err_code ) {
	case GL_INVALID_ENUM : { _error << __e_inv_arg = TString().Format(p_err_inv_enum, _prop_id, _prop_id); }  break;
	case GL_INVALID_OPERATION : { _error << (err_code) TErrCodes::eExecute::eOperate = p_err_inv_oper; } break;
	default:
		if (!!u_err_code)
			_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return _error;
}

bool     CProperty::Is_valid (const uint32_t _prop_id, CError& _error) {
	_prop_id; _error;
	bool b_valid = true;
	_error <<__METHOD__<<__s_ok;
	if (1 > _prop_id) {
		_error <<__e_inv_arg = TString().Format(p_err_prop_id_inv, _prop_id);
		b_valid = false;
	}
	return b_valid;
}

uint32_t CProperty::PropId (void) const { return this->m_prop_id; }
err_code CProperty::PropId (const uint32_t _prop_id) {
	_prop_id;
	if (__failed(CProperty::Is_valid(_prop_id, TBase::m_error)))
		return TBase::Error();
	if (_prop_id == this->PropId())
		TBase::m_error <<__s_false = TString().Format(p_err_prop_id_set, _prop_id);
	return TBase::Error();
}

CProperty& CProperty::operator <<(const bool _yes_or_no)  { this->Is_enabled(_yes_or_no); return *this; }
CProperty& CProperty::operator <<(const uint32_t _prop_id) { this->PropId(_prop_id); return *this; }

const CProperty& CProperty::operator >>(bool& _yes_or_no) const { _yes_or_no = this->Is_enabled(); return *this; }  
const CProperty& CProperty::operator >>(uint32_t& _prop_id) const { _prop_id = this->PropId(); return *this; }

#pragma endregion