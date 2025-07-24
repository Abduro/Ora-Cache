/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Aug-2020 at 6:37:00a, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack shared status bar control panel interface implementation file.
*/
#include "sfx.status.ext.h"

using namespace ex_ui::controls::sfx::status;

namespace ex_ui { namespace controls { namespace sfx { namespace _impl { void __warning_lnk_4221 (void) {}}}}}

/////////////////////////////////////////////////////////////////////////////

CPane:: CPane (void) {}
CPane:: CPane (const CPane& _src) : CPane() { *this = _src; } CPane:: CPane (CPane&& _victim) : CPane () { *this = (const CPane&)_victim; }
CPane::~CPane (void) {}

/////////////////////////////////////////////////////////////////////////////

CPane&  CPane::operator = (const CPane& _src) { (TBase&)*this = (const TBase&)_src; return *this; }

/////////////////////////////////////////////////////////////////////////////

CPanes:: CPanes (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CPanes::~CPanes (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code CPanes::Add (const CPane& _pane) {
	_pane;
	this->m_error <<__METHOD__<<__s_ok;
	try {
		this->Raw().push_back(_pane);
	}
	catch (const ::std::bad_alloc&) { m_error << E_OUTOFMEMORY; }
	return this->Error();
}

TError&  CPanes::Error (void) const { return this->m_error; }

const
TRawPanes& CPanes::Raw (void) const { return this->m_panes; }
TRawPanes& CPanes::Raw (void)       { return this->m_panes; }