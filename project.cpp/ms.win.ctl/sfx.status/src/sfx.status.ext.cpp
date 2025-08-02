/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Aug-2020 at 6:37:00a, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack shared status bar control panel interface implementation file.
*/
#include "sfx.status.ext.h"
#include "sfx.status.ctrl.h"

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

namespace ex_ui { namespace controls { namespace sfx { namespace status { namespace pane {

CLayout:: CLayout (void) : TBase(), m_fixed(0) {}
CLayout:: CLayout (const CLayout& _src) : CLayout() { (TBase&)*this = (const TBase&)_src; }
CLayout:: CLayout (CLayout&& _victim) : CLayout() { (TBase&)*this = (const TBase&)_victim; }

uint32_t  CLayout::Fixed (void) const { return this->m_fixed; }
bool      CLayout::Fixed (const uint32_t _n_value) {
	_n_value;
	const bool b_changed = this->Fixed() != _n_value;
	if (b_changed)
		this->m_fixed = _n_value;
	return b_changed;
}

const
CLay_Style&  CLayout::Style (void) const { return this->m_style; }
CLay_Style&  CLayout::Style (void)       { return this->m_style; }

CLayout&  CLayout::operator = (const CLayout& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Fixed(); return *this; }
CLayout&  CLayout::operator <<(const uint32_t _n_fixed) { this->Fixed(_n_fixed); return *this; }

}}}}}

/////////////////////////////////////////////////////////////////////////////

CPane:: CPane (void) : m_pane_id(0), m_evt_sink(0) {}
CPane:: CPane (const CPane& _src) : CPane() { *this = _src; } CPane:: CPane (CPane&& _victim) : CPane () { *this = (const CPane&)_victim; }
CPane::~CPane (void) {}

/////////////////////////////////////////////////////////////////////////////

const
ex_ui::controls::pane::CFormat& CPane::Format (void) const { return this->m_format; }
ex_ui::controls::pane::CFormat& CPane::Format (void)       { return this->m_format; }

uint16_t CPane::Id (void) const { return this->m_pane_id; }
bool     CPane::Id (const uint16_t _n_id) {
	_n_id;
	const bool b_changed = this->Id() != _n_id; if (b_changed) this->m_pane_id = _n_id; return b_changed;
}

const
TPn_Lay& CPane::Layout (void) const { return this->m_layout; }
TPn_Lay& CPane::Layout (void)       { return this->m_layout; }
const
IPaneEvents* CPane::GetSink (void) const { return this->m_evt_sink; }

bool    CPane::SetSink (const IPaneEvents* _p_snk) {
	_p_snk;
	this->m_evt_sink = _p_snk; return !!_p_snk;
}

_pc_sz  CPane::Text (void) const { return (_pc_sz) this->m_text; }
bool    CPane::Text (_pc_sz _p_text) {
	_p_text;
	const bool b_changed = !!this->m_text.CompareNoCase(_p_text);
	if (b_changed) {
		this->m_text = _p_text;

		if (this->m_evt_sink)
			this->m_evt_sink->OnTextChanged(this->Id(), this->Text());

	}
	return b_changed;
}

CPane&  CPane::operator = (const CPane& _src) {
	*this << _src.Format() << _src.Layout() << _src.Text() << _src.GetSink() << _src.Id(); return *this;
}

CPane&  CPane::operator <<(_pc_sz _p_text) { this->Text (_p_text); return *this; }
CPane&  CPane::operator <<(const ex_ui::controls::pane::CFormat& _fmt) { this->Format() = _fmt; return *this; }
CPane&  CPane::operator <<(const TPn_Lay& _lay) { this->Layout() = _lay; return *this; }

CPane&  CPane::operator <<(const IPaneEvents* _p_snk) { this->SetSink(_p_snk); return *this; }
CPane&  CPane::operator <<(const uint16_t _id ) { this->Id(_id); return *this; }

/////////////////////////////////////////////////////////////////////////////

CGlyph:: CGlyph (void) : TBase() {}
CGlyph::~CGlyph (void) {}

/////////////////////////////////////////////////////////////////////////////

CPanes:: CPanes (CControl& _ctrl) : m_ctrl(_ctrl) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CPanes::~CPanes (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code CPanes::Add (_pc_sz _p_text) {
	_p_text;
	CPane pane;

	pane.Text(_p_text);
	pane.Id(this->Count());
	pane.SetSink(this);

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
const
CGlyph&  CPanes::Glyph (void) const { return this->m_glyph; }
CGlyph&  CPanes::Glyph (void)       { return this->m_glyph; }

TError&  CPanes::Error (void) const { return this->m_error; }
const
CPane&   CPanes::Pane  (const uint16_t _ndx) const {
	_ndx;
	this->m_error <<__METHOD__<<__s_ok;
	if (_ndx >= this->Count()) {
		this->m_error << __e_index;
		return Get_fake_pane();
	}
	else
		return this->Raw().at(_ndx);
}

CPane&   CPanes::Pane  (const uint16_t _ndx) {
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

void  CPanes::OnTextChanged (const int32_t _pane_id, _pc_sz _p_text) const {
	_pane_id; _p_text;
	for (size_t i_ = 0; i_ < this->Raw().size(); i_++) {
		if (this->Raw().at(i_).Id() == _pane_id) {
			if (this->m_ctrl.Window().IsWindow()) {
				// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-redrawwindow ;
				this->m_ctrl.Window().RedrawWindow(&this->Raw().at(i_).Layout().Rect(), 0, RDW_ERASE|RDW_INVALIDATE);
				break;
			}
		}
	}
}