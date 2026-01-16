/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jan-2026 at 00:40:14.892, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL data types' enumeration interface implementation file;
*/
#include "gl_types.h"

using namespace ex_ui::draw::open_gl::procs;

#pragma region cls::CType{}

CType::CType (uint32_t _type) : m_data(_type) {}
CType::CType (const CType& _src) : CType() { *this = _src; }
CType::CType (CType&& _victim) : CType() { *this = _victim; }

bool  CType::Is_float (const uint32_t _u_type) {
	_u_type;
	return (_i_to_f(e_att_val_float::e_double) == _u_type || _i_to_f(e_att_val_float::e_float) == _u_type ||
	        _i_to_f(e_att_val_float::e_float_16bits) == _u_type);
}
bool  CType::Is_int (const uint32_t _u_type) {
	_u_type;
	return (_i_to_u(e_att_val_int::e_byte) == _u_type || _i_to_u(e_att_val_int::e_u_byte) == _u_type || _i_to_u(e_att_val_int::e_short) == _u_type ||
	        _i_to_u(e_att_val_int::e_u_short) == _u_type || _i_to_u(e_att_val_int::e_int) == _u_type || _i_to_u(e_att_val_int::e_u_int) == _u_type ||
	        _i_to_u(e_att_val_int::e_fixed) == _u_type);
}
bool  CType::Is_vec (const uint32_t _u_type) {
	_u_type;
	return (0x8B50 <= _u_type && _u_type <= 0x8B55) /*vector float & int 2|3|4*/
	    || (0x8B57 <= _u_type && _u_type <= 0x8B59) /*vector bool 2|3|4*/
	    || (0x8DC6 <= _u_type && _u_type <= 0x8DC8) /*vector uint 2|3|4*/
	    || (0x8FFC <= _u_type && _u_type <= 0x8FFE) /*vector double 2|3|4*/;
}

uint32_t CType::Get (void) const { return this->m_data; }  
bool     CType::Set (const uint32_t _type) {
	_type;
	const bool b_changed = this->Get() != _type; if (b_changed) this->m_data = _type; return b_changed;
}

const
uint32_t& CType::Ref (void) const { return this->m_data; }
uint32_t& CType::Ref (void)       { return this->m_data; }

CString CType::To_str (void) const {

	if (0 == this->Get()) return CString(_T("#undef"));

	CString cs_out;
	if (CType::Is_float(this->Get())) cs_out = CType::To_str((e_att_val_float)this->Get());
	if (CType::Is_int(this->Get())) cs_out = CType::To_str((e_att_val_int)this->Get());
	if (CType::Is_vec(this->Get())) cs_out = CType::To_str((e_att_val_vec)this->Get());

	if (cs_out.IsEmpty()) cs_out = _T("#undef");

	return  cs_out;
}

CString CType::To_str (const e_att_val_float _type) {
	_type;
	CString cs_out;
	switch (_type) {
	case e_att_val_float::e_double: cs_out = _T("#e_double"); break;
	case e_att_val_float::e_float : cs_out = _T("#e_float"); break;
	case e_att_val_float::e_float_16bits: cs_out = _T("#e_float_16bits"); break;
	}
	return  cs_out;
}

CString CType::To_str (const e_att_val_int _type) {
	_type;
	CString cs_out;
	switch (_type) {
	case e_att_val_int::e_byte   : cs_out = _T("#e_byte"); break;
	case e_att_val_int::e_fixed  : cs_out = _T("#e_fixed"); break;
	case e_att_val_int::e_int    : cs_out = _T("#e_int"); break;
	case e_att_val_int::e_int_2_10_10_10: cs_out = _T("#e_int_2_10_10_10"); break;
	case e_att_val_int::e_short  : cs_out = _T("#e_short"); break;
	case e_att_val_int::e_u_byte : cs_out = _T("#e_u_byte"); break;
	case e_att_val_int::e_u_int  : cs_out = _T("#e_u_int"); break;
	case e_att_val_int::e_u_short: cs_out = _T("#e_u_short"); break;
	case e_att_val_int::e_uint_2_10_10_10: cs_out = _T("#e_uint_2_10_10_10"); break;
	case e_att_val_int::e_uint_10_11_11: cs_out = _T("#e_uint_10_11_11"); break;
	}
	return  cs_out;
}

CString CType::To_str (const e_att_val_vec _type) {
	_type;
	CString cs_out;
	switch (_type) {
	case e_att_val_vec::e_bool_vec2: cs_out = _T("#e_bool_vec2"); break; case e_att_val_vec::e_dbl_vec2: cs_out = _T("#e_dbl_vec2"); break; case e_att_val_vec::e_float_vec2: cs_out = _T("#e_float_vec2"); break; case e_att_val_vec::e_int_vec2: cs_out = _T("#e_int_vec2"); break; case e_att_val_vec::e_uint_vec2: cs_out = _T("#e_uint_vec2"); break;
	case e_att_val_vec::e_bool_vec3: cs_out = _T("#e_bool_vec3"); break; case e_att_val_vec::e_dbl_vec3: cs_out = _T("#e_dbl_vec3"); break; case e_att_val_vec::e_float_vec3: cs_out = _T("#e_float_vec3"); break; case e_att_val_vec::e_int_vec3: cs_out = _T("#e_int_vec3"); break; case e_att_val_vec::e_uint_vec3: cs_out = _T("#e_uint_vec3"); break;
	case e_att_val_vec::e_bool_vec4: cs_out = _T("#e_bool_vec4"); break; case e_att_val_vec::e_dbl_vec4: cs_out = _T("#e_dbl_vec4"); break; case e_att_val_vec::e_float_vec4: cs_out = _T("#e_float_vec4"); break; case e_att_val_vec::e_int_vec4: cs_out = _T("#e_int_vec4"); break; case e_att_val_vec::e_uint_vec4: cs_out = _T("#e_uint_vec4"); break;
	}
	return  cs_out;
}

CString CType::To_str (const e_att_val_mtx _type) {
	CString cs_out;
	switch (_type) {
	case e_att_val_mtx::e_dbl_mtx2  : cs_out = _T("#e_dbl_mtx2"); break;   case e_att_val_mtx::e_float_mtx2: cs_out = _T("#e_float_mtx2"); break; case e_att_val_mtx::e_float_mtx2x3: cs_out = _T("#e_float_mtx2x3"); break; case e_att_val_mtx::e_float_mtx3x4: cs_out = _T("#e_float_mtx3x4"); break;
	case e_att_val_mtx::e_dbl_mtx3  : cs_out = _T("#e_dbl_mtx3"); break;   case e_att_val_mtx::e_float_mtx3: cs_out = _T("#e_float_mtx3"); break; case e_att_val_mtx::e_float_mtx2x4: cs_out = _T("#e_float_mtx2x4"); break; case e_att_val_mtx::e_float_mtx4x2: cs_out = _T("#e_float_mtx4x2"); break;
	case e_att_val_mtx::e_dbl_mtx4  : cs_out = _T("#e_dbl_mtx4"); break;   case e_att_val_mtx::e_float_mtx4: cs_out = _T("#e_float_mtx4"); break; case e_att_val_mtx::e_float_mtx3x2: cs_out = _T("#e_float_mtx3x2"); break; case e_att_val_mtx::e_float_mtx4x4: cs_out = _T("#e_float_mtx4x4"); break;
	case e_att_val_mtx::e_dbl_mtx2x3: cs_out = _T("#e_dbl_mtx2x3"); break; case e_att_val_mtx::e_dbl_mtx3x2: cs_out = _T("#e_dbl_mtx3x2"); break;   case e_att_val_mtx::e_dbl_mtx4x2: cs_out = _T("e_dbl_mtx4x2"); break;
	case e_att_val_mtx::e_dbl_mtx2x4: cs_out = _T("#e_dbl_mtx2x4"); break; case e_att_val_mtx::e_dbl_mtx3x4: cs_out = _T("#e_dbl_mtx3x4"); break;   case e_att_val_mtx::e_dbl_mtx4x3: cs_out = _T("e_dbl_mtx4x3"); break;
	}
	return  cs_out;
}

CType&  CType::operator <<(const uint32_t _type) { this->Set(_type); return *this; }
CType&  CType::operator = (const CType& _src) { *this << _src.Get(); return *this; }
CType&  CType::operator = (CType&& _victim) { *this = (const CType&)_victim; return *this; }

#pragma endregion