/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2025 at 03:14:40.600, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' geometry generic elements' interface implementation file;
*/
#include "math.defs.h"

using namespace ex_ui::draw::open_gl::math;

namespace ex_ui { namespace draw { namespace open_gl { namespace math { namespace _impl { void __warning_lnk_4221 (void) {}}}}}}

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