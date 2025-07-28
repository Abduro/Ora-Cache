/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Aug-2020 at 6:37:00a, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack shared status bar control panel interface implementation file.
*/
#include "sfx.status.ext.h"

using namespace ex_ui::controls::sfx::status;

namespace ex_ui { namespace controls { namespace sfx { namespace status { namespace _impl { void __warning_lnk_4221 (void) {}
	// the error below may appear due to not proper reference: CPane base class can be implicitly used;
	// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/compiler-error-c2440 ;
	using CPane = ex_ui::controls::sfx::status::CPane;

	CPane&  Get_fake_pane (void) {
		static CPane fk_pane;
		return fk_pane;
	}

}}}}}
using namespace ex_ui::controls::sfx::status::_impl;
/////////////////////////////////////////////////////////////////////////////

CPane:: CPane (void) {}
CPane:: CPane (const CPane& _src) : CPane() { *this = _src; } CPane:: CPane (CPane&& _victim) : CPane () { *this = (const CPane&)_victim; }
CPane::~CPane (void) {}

/////////////////////////////////////////////////////////////////////////////

_pc_sz  CPane::Text (void) const { return (_pc_sz) this->m_text; }
bool    CPane::Text (_pc_sz _p_text) {
	_p_text;
	const bool b_changed = !!this->m_text.CompareNoCase(_p_text);
	if (b_changed)
		this->m_text = _p_text;

	return b_changed;
}

CPane&  CPane::operator = (const CPane& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Text(); return *this; }

CPane&  CPane::operator <<(_pc_sz _p_text) { this->Text (_p_text); return *this; }

/////////////////////////////////////////////////////////////////////////////

CPanes:: CPanes (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CPanes::~CPanes (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code CPanes::Add (_pc_sz _p_text) {
	CPane pane;
	pane.Text(_p_text);
	return this->Add(pane);
}

err_code CPanes::Add (const CPane& _pane) {
	_pane;
	this->m_error <<__METHOD__<<__s_ok;
	try {
		this->Raw().push_back(_pane);
	}
	catch (const ::std::bad_alloc&) { m_error << E_OUTOFMEMORY; }
	return this->Error();
}

uint16_t CPanes::Count(void) const {
	return static_cast<uint16_t>(this->Raw().size());
}

TError&  CPanes::Error(void) const { return this->m_error; }
const
CPane&   CPanes::Pane (const uint16_t _ndx) const {
	_ndx;
	this->m_error <<__METHOD__<<__s_ok;
	if (_ndx >= this->Count()) {
		this->m_error << __e_index;
		return Get_fake_pane();
	}
	else
		return this->Raw().at(_ndx);
}

CPane&   CPanes::Pane (const uint16_t _ndx) {
	_ndx;
	this->m_error <<__METHOD__<<__s_ok;
	if (_ndx >= this->Count()) {
		this->m_error << __e_index;
		return Get_fake_pane();
	}
	else
		return this->Raw().at(_ndx);
}

const
TRawPanes& CPanes::Raw (void) const { return this->m_panes; }
TRawPanes& CPanes::Raw (void)       { return this->m_panes; }