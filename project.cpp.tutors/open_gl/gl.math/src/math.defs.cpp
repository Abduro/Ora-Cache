/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2025 at 03:14:40.600, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' geometry generic elements' interface implementation file;
*/
#include "math.defs.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::math;

namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	static _pc_sz pc_sz_err_angle = _T("#__e_inv_arg: the rotate angle %.7f is less than epsilon;\n");

	bool __chk_angle (const float _f_angle) {
		if (defs::f_epsilon > abs(_f_angle)) {
			__trace_warn_2(pc_sz_err_angle, _f_angle); return false;
		}
		else return true;
	}

	_pc_sz _format (const float _f_value, _pc_sz _p_format/* = _T("%.7f")*/) {
		_f_value; _p_format;
		static CString  cs_val; cs_val = TString().Float(_f_value, _p_format);
		static CString  cs_out; cs_out.Empty(); if (_T('-') == cs_val.Left(1)) {} else { cs_out += _T(" "); } cs_out += cs_val;
		return (_pc_sz) cs_out;
	}

	float _pow_2 (const float& _base) { return _base * _base; }
	float _pow_3 (const float& _base) { return _base * _base * _base; }

	float _pow_n (const uint32_t _index, const float _base) {
		_index; _base;
		if (false) {}
		else if (0 == _index) return 1.0f;
		else if (1 == _index) return _base;
		float f_result = _base;
		for (uint32_t i_ = 0; i_ < _index; i_++)
			f_result *= _base;
		return f_result;
	}

	float _rsqrt (const float _f_value) {
		_f_value;
		static const float f_half_3 = 1.5f;
		static const float f_half = 0.5f;

		float f_half_of_val = _f_value * f_half;
		float f_result = _f_value;
		long 
		bits_ = *(long*)&f_result;         // evil floating point bit level hacking;
		bits_ = 0x5f3759df - (bits_ >> 1); // what the fuck?

		f_result = *(float*) &bits_;
		f_result = f_result * ( f_half_3 - (f_half_of_val * f_result * f_result));   // the 1st iteration;
	//	f_result = f_result * ( f_half_3 - (f_half_of_val * f_result * f_result));   // the 2nd iteration;
		return f_result;
	}
	// https://stackoverflow.com/questions/1343890/how-do-i-round-a-number-to-2-decimal-places-in-c << https://stackoverflow.com/a/54197024/4325555 ;
	float _round (const float _f_value, const uint32_t _u_dec_places/* = 5*/) {
		_f_value; _u_dec_places;
		return static_cast<float>(::std::floor(_f_value * ::std::pow(10, _u_dec_places) + .5) / ::std::pow(10, _u_dec_places));
	}
}}}}

#if (0) // not used;
_2d::CPoint:: CPoint (void) : m_x(0.0f), m_y(0.0f) {}
_2d::CPoint:: CPoint (const float _x, const float _y) : CPoint() { *this << _x >> _y; }
_2d::CPoint:: CPoint (const CPoint& _src) : CPoint() { *this = _src; }
_2d::CPoint:: CPoint (CPoint&& _victim) : CPoint() { *this = _victim; }
_2d::CPoint::~CPoint (void) {}

const
float  _2d::CPoint::x (void) const { return this->m_x; }
float& _2d::CPoint::x (void)       { return this->m_x; }
void   _2d::CPoint::x (const float _x) { this->m_x = _x; }
const
float  _2d::CPoint::y (void) const { return this->m_y; }
float& _2d::CPoint::y (void)       { return this->m_y; }
void   _2d::CPoint::y (const float _y) { this->m_y = _y; }

void   _2d::CPoint::Set (const float _x, const float _y) {
	this->x() = _x; this->y() = _y;
}

_2d::CPoint& _2d::CPoint::operator = (const _2d::CPoint& _src) { *this >> _src.y() << _src.x(); return *this; }
_2d::CPoint& _2d::CPoint::operator = (_2d::CPoint&& _victim) { *this = (const _2d::CPoint&)_victim;  return *this; }

_2d::CPoint& _2d::CPoint::operator <<(const float _x) { this->x(_x); return *this; }
_2d::CPoint& _2d::CPoint::operator >>(const float _y) { this->y(_y); return *this; }

float& _2d::CPoint::operator [] (const _2d::e_index _ndx) {
	return _2d::e_index::_0 == _ndx ? this->x() : this->y();
}

/////////////////////////////////////////////////////////////////////////////

_3d::CPoint:: CPoint (void) : TBase(), m_z(0.0f) {}
_3d::CPoint:: CPoint (const float _x, const float _y, const float _z) : CPoint() { *this << _x >> _y; this->z() = _z; }
_3d::CPoint:: CPoint (const CPoint& _src) : CPoint() { *this = _src; }
_3d::CPoint:: CPoint (CPoint&& _victim) : CPoint() { *this = _victim; }
_3d::CPoint::~CPoint (void) {}

const
float  _3d::CPoint::z (void) const { return this->m_z; }
float& _3d::CPoint::z (void)       { return this->m_z; }
void   _3d::CPoint::z (const float _z) { this->m_z = _z; }

_3d::CPoint&  _3d::CPoint::operator = (const _3d::CPoint& _src) { (TBase&)*this = (const TBase&)_src; this->z() = _src.z(); return *this; }
_3d::CPoint&  _3d::CPoint::operator = (_3d::CPoint&& _victim) { *this = (const _3d::CPoint&)_victim; return *this; }
_3d::CPoint&  _3d::CPoint::operator ^ (const float _z) { this->z() = _z; return *this; }

#endif