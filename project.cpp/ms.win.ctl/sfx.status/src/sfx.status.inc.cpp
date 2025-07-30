/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Jul-2025 at 03:49:05.262, UTC+4, Batumi, Wednesday;
	This is Ebo Pack status bar user control include header(s) implementation file;
*/
#include "sfx.status.inc.h"

using namespace ex_ui::controls::sfx;
using namespace ex_ui::controls::sfx::status::layout;

/////////////////////////////////////////////////////////////////////////////

CStyle::CStick:: CStick (const e_side _side/* = e_side::e_left*/) : m_side(_side) {}
CStyle::CStick:: CStick (const CStick& _src) : CStick() { *this = _src; }
CStyle::CStick::~CStick (void) {}

CStyle::CStick::e_side  CStyle::CStick::Get (void) const { return this->m_side; }
bool CStyle::CStick::Set (const e_side _side) {
	_side;
	const bool b_changed = this->Get() != _side;
	if (b_changed)
		this->m_side = _side;
	return b_changed;
}

CStyle::CStick&  CStyle::CStick::operator = (const CStick& _src) { *this << _src.Get(); return *this; }
CStyle::CStick&  CStyle::CStick::operator <<(const e_side _side) {  this->Set(_side); return *this; }

/////////////////////////////////////////////////////////////////////////////

CStyle::CWidth:: CWidth (const e_mode _mode/*= e_mode::e_fixed*/) : m_mode(_mode) {}
CStyle::CWidth:: CWidth (const CWidth& _src) : CWidth() { *this = _src; }
CStyle::CWidth::~CWidth (void) {}

CStyle::CWidth::e_mode  CStyle::CWidth::Get (void) const { return this->m_mode; }
bool CStyle::CWidth::Set (const e_mode _mode) {
	_mode;
	const bool b_changed = this->Get() != _mode;
	if (b_changed)
		this->m_mode = _mode;
	return b_changed;
}

CStyle::CWidth&  CStyle::CWidth::operator = (const CWidth& _src) { *this << _src.Get(); return *this; }
CStyle::CWidth&  CStyle::CWidth::operator <<(const e_mode _mode) {  this->Set(_mode); return *this; }

/////////////////////////////////////////////////////////////////////////////

CStyle:: CStyle (void) {}
CStyle:: CStyle (const CStyle& _src) : CStyle() { *this = _src; }
CStyle::~CStyle (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CStyle::CStick& CStyle::Stick (void) const { return m_stick; }
CStyle::CStick& CStyle::Stick (void)       { return m_stick; }
const
CStyle::CWidth& CStyle::Width (void) const { return m_width; }
CStyle::CWidth& CStyle::Width (void)       { return m_width; }

bool CStyle::Set (const CStick::e_side _side, const CWidth::e_mode _mode) {
	_side; _mode;
	bool b_changed = false;

	if (this->Stick().Set(_side)) b_changed = true;
	if (this->Width().Set(_mode)) b_changed = true;

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CStyle&   CStyle::operator = (const CStyle& _src  ) { *this << _src.Stick() << _src.Width(); return *this; }
CStyle&   CStyle::operator <<(const CStick& _stick) {  this->Stick() = _stick; return *this; }
CStyle&   CStyle::operator <<(const CWidth& _width) {  this->Width() = _width; return *this; }