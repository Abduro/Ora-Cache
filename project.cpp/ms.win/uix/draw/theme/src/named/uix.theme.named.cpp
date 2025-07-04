/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Jun-2025 at 12:59:02.491, UTC+4, Batumi, Saturday;
	This is Ebo Pack generic custom color theme named interface implementation file.
*/
#include "uix.theme.named.h"
#include "uix.theme.reg.h"

// hiding this reference to MSXML from consumers of custom theme, otherwise, it will introduce not necessary references;
#include "msxml.doc.h"
#include "msxml.ntfs.h"
#include "msxml.root.h"

using namespace ex_ui::theme;

using namespace shared::xml::ms;
using namespace shared::xml::ms::ntfs;

using CDataLocator = shared::xml::ms::ntfs::CLocator;
using CDataProvider = shared::xml::ms::ntfs::CProvider;
using CXmlDoc = shared::xml::ms::CDocument;

/////////////////////////////////////////////////////////////////////////////

CBase:: CBase (void) : m_valid(false) {}
CBase:: CBase (_pc_sz _p_name, const bool _b_valid) : CBase() { *this << _p_name << _b_valid; }
CBase:: CBase (const CBase& _src) : CBase() { *this = _src; }
CBase:: CBase (CBase&& _victim) : CBase() { *this = _victim; }
CBase::~CBase (void) {}

/////////////////////////////////////////////////////////////////////////////

bool   CBase::Is_valid (void) const { return this->m_valid; /*0 == ex_ui::color::rgb::get_a_value(this->Color());*/ }
void   CBase::Is_valid (const bool _b_valid) { this->m_valid = _b_valid; }

_pc_sz CBase::Name (void) const { return (_pc_sz) this->m_name; }
bool   CBase::Name (_pc_sz _p_name) {
	_p_name;

	if (nullptr == _p_name || 0 == ::_tcslen(_p_name))
		return false;

	const bool b_changed = !!this->m_name.CompareNoCase(_p_name); // non sensitive case comparison due to for registry key name the case is not important;
	if (b_changed)
		this->m_name = _p_name;

	return b_changed;
}

#if defined(_DEBUG)
CString  CBase::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {name=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {name=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{name=%s;valid=%s}");

	CString cs_name  = this->m_name.IsEmpty() ? _T("#not_set") : this->Name();
	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_name, (_pc_sz) cs_valid); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_name, (_pc_sz) cs_valid); }
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r, (_pc_sz) cs_name, (_pc_sz) cs_valid); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

bool   CBase::Set (_pc_sz _p_name, const bool _b_valid) {
	_p_name; _b_valid;
	bool b_changed = false;

	if (this->Name(_p_name)) b_changed = true;
	if (this->Is_valid() != _b_valid) { this->Is_valid(_b_valid); b_changed = true; }

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CBase& CBase::operator = (const CBase& _src) { *this << _src.Name() << _src.Is_valid(); return *this; }
CBase& CBase::operator = (CBase&& _victim) { *this = (const CBase&)_victim; return *this; }
CBase& CBase::operator <<(_pc_sz _p_name) { this->Name(_p_name); return *this; }
CBase& CBase::operator <<(const bool _b_valid) { this->Is_valid(_b_valid); return *this; }

/////////////////////////////////////////////////////////////////////////////

CCurrent:: CCurrent (void) : TBase(), m_theme_ndx(0) { this->Default(); }
CCurrent:: CCurrent (const CCurrent& _src) : CCurrent() { *this = _src; }
CCurrent:: CCurrent (CCurrent&& _victim) : CCurrent() { *this = _victim; }
CCurrent::~CCurrent (void) {}

void       CCurrent::Default (void) {
	(TBase&)*this << TThemePalette::e_dark;
	(TBase&)*this << TThemePart::e_form;
	(TBase&)*this << TThemeElement::e_back;
	(TBase&)*this << TThemeState::e_normal;

	this->ThemeIndex(0);
}
const
CPart&     CCurrent::Form (void) const {

	const TRawParts&  parts = this->Theme().Parts();

	for (size_t i_ = 0; i_ < parts.size(); i_++)
		if (parts.at(i_).Id() == TThemePart::e_form)
			return parts.at(i_);

	static CPart inv_form;
	return inv_form;
}
CPart&     CCurrent::Form (void) {

	TRawParts&  parts = this->Theme().Parts();

	for (size_t i_ = 0; i_ < parts.size(); i_++)
		if (parts.at(i_).Id() == TThemePart::e_form)
			return parts.at(i_);

	static CPart inv_form;
	return inv_form;
}

err_code   CCurrent::Load (void) {

	using ex_ui::theme::storage::CRegistry;

	CRegistry storage;
	err_code n_result = storage.Load(*this);
	return n_result;
}

const
ex_ui::theme::CPalette&  CCurrent::Palette (void) const { return this->m_palette; }
ex_ui::theme::CPalette&  CCurrent::Palette (void)       { return this->m_palette; }

static ex_ui::theme::CNamed inv_theme;

const
ex_ui::theme::CNamed&  CCurrent::Theme (void) const {
	if (this->ThemeIndex() >= this->Palette().Themes().size())
		return inv_theme;
	else
		return this->Palette().Themes().at(this->ThemeIndex());
}
ex_ui::theme::CNamed&  CCurrent::Theme (void) {
	if (this->ThemeIndex() >= this->Palette().Themes().size())
		return inv_theme;
	else
		return this->Palette().Themes().at(this->ThemeIndex());
}

uint32_t   CCurrent::ThemeIndex (void) const { return this->m_theme_ndx; }
bool       CCurrent::ThemeIndex (const uint32_t _ndx) {

	const bool b_changed = _ndx != this->ThemeIndex();
	if (b_changed)
		this->m_theme_ndx = _ndx;

	return b_changed;
}

CCurrent&  CCurrent::operator = (const CCurrent& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.ThemeIndex(); return *this; }
CCurrent&  CCurrent::operator = (CCurrent&& _victim) { *this = (const CCurrent&)_victim; return *this; }

CCurrent&  CCurrent::operator <<(const uint32_t _ndx) {
	this->ThemeIndex(_ndx); return *this;
}

/////////////////////////////////////////////////////////////////////////////

CElement:: CElement (const TThemeElement _id) : m_el_id(_id) {
	this->m_name = TPrint::Out(_id);
	for (size_t i_ = 0; i_ < this->States().Raw().size(); i_++) {
		CState& state = this->States().Raw().at(i_);
		state.Id((TThemeState)i_, true);
	}
}
CElement:: CElement (const CElement& _src) : CElement() { *this = _src; }
CElement:: CElement (CElement&& _victim) : CElement() { *this = _victim; }
CElement::~CElement (void) {}

/////////////////////////////////////////////////////////////////////////////

const bool CElement::Clear (void) {
	bool b_changed = false;

	if (TBase::Is_valid()) { TBase::Is_valid(false); b_changed = true; }
	for (size_t i_ = 0; i_ < this->States().Raw().size(); i_++) // clears all states;
			if (this->States().Raw().at(i_).Clear())
				b_changed = true;

	return b_changed;
}

TThemeElement CElement::Id (void) const { return this->m_el_id; }
const bool    CElement::Id (const TThemeElement _e_id, const bool b_update_name) {
	_e_id; b_update_name;
	bool b_changed = this->Id() != _e_id;

	if (b_changed) {
		this->m_el_id = _e_id;
		if (b_update_name)
			this->m_name = TPrint::Out(_e_id);
		this->Clear();
	}
	return b_changed;
}

#if defined(_DEBUG)
CString CElement::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {name=%s;id=%u;valid=%s;%s%sstates:%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {name=%s;id=%u;valid=%s;%s%sstates:%s}");
	static _pc_sz pc_sz_pat_r = _T("name=%s;id=%u;valid=%s;%s%sstates:%s");

	CString cs_name  = TBase::m_name.IsEmpty() ? _T("#not_set") : TBase::Name();
	CString cs_valid = TStringEx().Bool(TBase::Is_valid());

	CString cs_states;
	for (size_t i_ = 0; i_ < this->States().Raw().size(); i_++) {
		const CState& state = this->States().Raw().at(i_);
		cs_states += _p_sfx;
		cs_states += _p_pfx;
		cs_states += state.Print(e_print::e_req);
	}
	if (cs_states.IsEmpty()) {
		cs_states += _p_sfx;
		cs_states += _p_pfx;
		cs_states += _T("#empty");
	}

	CString cs_out;

	if (e_print::e_all == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		(_pc_sz) cs_name, this->Id(), (_pc_sz) cs_valid, _p_sfx, _p_pfx, (_pc_sz) cs_states);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__,
		(_pc_sz) cs_name, this->Id(), (_pc_sz) cs_valid, _p_sfx, _p_pfx, (_pc_sz) cs_states);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format (pc_sz_pat_r,
		(_pc_sz) cs_name, this->Id(), (_pc_sz) cs_valid, _p_sfx, _p_pfx, (_pc_sz) cs_states);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif
const
CStates&  CElement::States (void) const { return this->m_states; }
CStates&  CElement::States (void)       { return this->m_states; }

/////////////////////////////////////////////////////////////////////////////

CElement& CElement::operator = (const CElement& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Id() << _src.States(); return *this; }
CElement& CElement::operator = (CElement&& _victim) { *this = (const CElement&)_victim; return *this; }

CElement& CElement::operator <<(const CStates& _states) { this->States() = _states; return *this; }

CElement& CElement::operator <<(const TThemeElement& _e_id) {
	this->Id(_e_id, true); return *this;
}

/////////////////////////////////////////////////////////////////////////////
namespace ex_ui { namespace theme {

CPalette:: CPalette (const TThemePalette _e_id) : m_pal_id(_e_id) {
	this->m_name = TPrint::Out(_e_id);
}
CPalette:: CPalette (const CPalette& _src) : CPalette() { *this = _src; }
CPalette:: CPalette (CPalette&& _victim) : CPalette() { *this = _victim; }
CPalette::~CPalette (void) {}

/////////////////////////////////////////////////////////////////////////////

const bool CPalette::Clear (void) {
	bool b_changed = false;

	if (TBase::Is_valid()) { TBase::Is_valid(false); b_changed = true; }
	if (this->Themes().empty() == false) {
		this->Themes().clear();

		b_changed = true;
	}
	return b_changed;
}

TThemePalette CPalette::Id (void) const { return this->m_pal_id;}
const bool    CPalette::Id (const TThemePalette _e_id, const bool b_update_name) {
	_e_id; b_update_name;
	bool b_changed = this->Id() != _e_id;

	if (b_changed) {
		this->m_pal_id = _e_id;
		if (b_update_name)
			this->m_name = TPrint::Out(_e_id);
		this->Clear();
	}
	return b_changed;
}

#if defined(_DEBUG)
CString    CPalette::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {name=%s;id=%u;valid=%s;parts=%s%s%s\t}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {name=%s;id=%u;valid=%s;parts=%s%s%s\t}");
	static _pc_sz pc_sz_pat_r = _T("name=%s;id=%u;valid=%s;parts=%s%s%s");

	CString cs_name  = TBase::m_name.IsEmpty() ? _T("#not_set") : TBase::Name();
	CString cs_valid = TStringEx().Bool(TBase::Is_valid());
	CString cs_parts;

	for (size_t i_ = 0; i_ < this->Themes().size(); i_++) {
		const CNamed& theme = this->Themes().at(i_);
		cs_parts += _p_sfx;
		cs_parts += _p_pfx;
		cs_parts += TStringEx().Format(_T("Theme #%u: "), i_);
		cs_parts += theme.Print(e_print::e_req);
		cs_parts += _p_sfx;
	}
	if (cs_parts.IsEmpty()) {
		cs_parts += _p_sfx;
		cs_parts += _p_pfx;
		cs_parts += _T("#empty");
		cs_parts += _p_sfx;
	}
	CString cs_out;

	if (e_print::e_all == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		(_pc_sz) cs_name, this->Id(), (_pc_sz) cs_valid, _p_sfx, _p_pfx, (_pc_sz) cs_parts);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__,
		(_pc_sz) cs_name, this->Id(), (_pc_sz) cs_valid, _p_sfx, _p_pfx, (_pc_sz) cs_parts);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format (pc_sz_pat_r,
		(_pc_sz) cs_name, this->Id(), (_pc_sz) cs_valid, _p_sfx, _p_pfx, (_pc_sz) cs_parts);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

const
TRawNamed& CPalette::Themes (void) const { return this->m_themes; }
TRawNamed& CPalette::Themes (void)       { return this->m_themes; }

/////////////////////////////////////////////////////////////////////////////

CPalette&  CPalette::operator = (const CPalette& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Id() << _src.Themes(); return *this; }
CPalette&  CPalette::operator = (CPalette&& _victim) { *this = (const CPalette&)_victim; return *this; }

CPalette&  CPalette::operator <<(const TRawNamed& _named) { this->Themes() = _named; return *this; }
CPalette&  CPalette::operator <<(const TThemePalette _e_id) { this->Id(_e_id, true); return *this; }

}}
/////////////////////////////////////////////////////////////////////////////

CPart:: CPart (const TThemePart _part) : m_part_id(_part) {
	this->m_name = TPrint::Out(_part);
	for (size_t i_ = 0; i_ < this->Elements().size(); i_++) {
		if (false){}
		else if (0 == i_) this->Elements().at(i_).Id(TThemeElement::e_back, true);
		else if (1 == i_) this->Elements().at(i_).Id(TThemeElement::e_fore, true);
		else if (2 == i_) this->Elements().at(i_).Id(TThemeElement::e_border, true);
		else
			break;
	}
}
CPart:: CPart (const CPart& _src) : CPart() { *this = _src; }
CPart:: CPart (CPart&& _victim ) : CPart() { *this = _victim; }
CPart::~CPart (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CElement&   CPart::Bkgnd (void) const { return this->Get (TThemeElement::e_back); }
CElement&   CPart::Bkgnd (void)       { return this->Get (TThemeElement::e_back); }
const
CElement&   CPart::Border(void) const { return this->Get (TThemeElement::e_border); }
CElement&   CPart::Border(void)       { return this->Get (TThemeElement::e_border); }

const bool  CPart::Clear (void) {
	bool b_changed = false;

	if (TBase::Is_valid()) { TBase::Is_valid(false); b_changed = true; }
	for (size_t i_ = 0; i_ < this->Elements().size(); i_++) // clears all elements;
			if (this->Elements().at(i_).Clear())
				b_changed = true;

	return b_changed;
}
const
TRawElements& CPart::Elements (void) const { return this->m_elements; }
TRawElements& CPart::Elements (void)       { return this->m_elements; }
const
CElement&   CPart::Get (const TThemeElement _e_id) const {

	for (size_t i_ = 0; i_ < this->Elements().size(); i_++)
		if (_e_id == this->Elements().at(i_).Id())
			return this->Elements().at(i_);

	static CElement inv_el;
	return inv_el;
}
CElement&   CPart::Get (const TThemeElement _e_id) {

	for (size_t i_ = 0; i_ < this->Elements().size(); i_++)
		if (_e_id == this->Elements().at(i_).Id())
			return this->Elements().at(i_);

	static CElement inv_el;
	return inv_el;
}

TThemePart  CPart::Id (void) const { return this->m_part_id; }
const bool  CPart::Id (const TThemePart _part, const bool b_update_name) {
	_part;
	const bool b_changed = this->Id() != _part;

	if (b_changed) {
		this->m_part_id = _part;
		if (b_update_name)
			this->m_name = TPrint::Out(_part);
		this->Clear();
	}
	return b_changed;
}

#if defined(_DEBUG)
CString CPart::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {name=%s;id=%u;valid=%s;%s%selements:%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {name=%s;id=%u;valid=%s;%s%selements:%s}");
	static _pc_sz pc_sz_pat_r = _T("name=%s;id=%u;valid=%s;%s%selements:%s");

	CString cs_name  = TBase::m_name.IsEmpty() ? _T("#not_set") : TBase::Name();
	CString cs_valid = TStringEx().Bool(TBase::Is_valid());

	CString cs_elements;
	for (size_t i_ = 0; i_ < this->Elements().size(); i_++) {
		const CElement& element = this->Elements().at(i_);
		cs_elements += _p_sfx;
		cs_elements += _p_pfx;
		cs_elements += TStringEx().Format(_T("el #%u: "), i_ + 1);
		cs_elements += element.Print(e_print::e_req);
		cs_elements += _p_sfx;
	}
	if (cs_elements.IsEmpty()) {
		cs_elements += _p_sfx;
		cs_elements += _p_pfx;
		cs_elements += _T("#empty");
		cs_elements += _p_sfx;
	}

	CString cs_out;

	if (e_print::e_all == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		(_pc_sz) cs_name, this->Id(), (_pc_sz) cs_valid, _p_sfx, _p_pfx, (_pc_sz) cs_elements);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__,
		(_pc_sz) cs_name, this->Id(), (_pc_sz) cs_valid, _p_sfx, _p_pfx, (_pc_sz) cs_elements);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format (pc_sz_pat_r,
		(_pc_sz) cs_name, this->Id(), (_pc_sz) cs_valid, _p_sfx, _p_pfx, (_pc_sz) cs_elements);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CPart& CPart::operator = (const CPart& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Id() << _src.Elements(); return *this; }
CPart& CPart::operator = (CPart&& _victim) { *this = (const CPart&)_victim; return *this; }

CPart& CPart::operator <<(const TThemePart _e_id) { this->Id(_e_id, true); return *this; }
CPart& CPart::operator <<(const TRawElements& _elements) { this->Elements() = _elements; return *this; }

/////////////////////////////////////////////////////////////////////////////

CState:: CState (const TThemeState _id) : TBase(), m_state_id (_id) { TBase::m_name = TPrint::Out(_id); }
CState:: CState (const CState& _src) : CState() { *this = _src; }
CState:: CState (CState&& _victim) : CState() { *this = _victim; }
CState::~CState (void) {}

/////////////////////////////////////////////////////////////////////////////

bool      CState::Clear (void) {
	bool b_changed = false;
	if (TBase::Is_valid()) { TBase::Is_valid(false); b_changed = true; }
	if (this->Color() != 0) { this->Color(0); b_changed = true; }

	return b_changed;
}

rgb_color CState::Color (void) const { return this->m_color.Color().ToRgb(); }
bool      CState::Color (const rgb_color _color) {
	_color;
	const bool b_changed = _color != this->Color();
	if (b_changed)
		this->m_color.Color() = _color;

	return b_changed;
}

TThemeState  CState::Id (void) const { return this->m_state_id; }
const bool   CState::Id (const TThemeState _id, const bool b_update_name) {
	_id; b_update_name;
	const bool b_changed = _id != this->Id();
	if (b_changed) {
		this->m_state_id = _id;
		if (b_update_name)
			this->m_name = TPrint::Out(_id);
	}
	return b_changed;
}

const
CHex&  CState::Hex  (void) const { return this->m_color; }
CHex&  CState::Hex  (void)       { return this->m_color; }

#if defined(_DEBUG)
CString CState::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {name=%s;color=%s;id=%u;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {name=%s;color=%s;id=%u;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{name=%s;color=%s;id=%u;valid=%s}");

	CString cs_name  = this->m_name.IsEmpty() ? _T("#not_set") : this->Name();
	CString cs_color = CHex::Print(this->Color());
	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;

	if (e_print::e_all == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		(_pc_sz) cs_name, (_pc_sz) cs_color, this->Id(), (_pc_sz) cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__,
		(_pc_sz) cs_name, (_pc_sz) cs_color, this->Id(), (_pc_sz) cs_valid);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format (pc_sz_pat_r,
		(_pc_sz) cs_name, (_pc_sz) cs_color, this->Id(), (_pc_sz) cs_valid);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CState& CState::operator = (const CState& _src) { (TBase)*this = (const TBase&) _src; *this << _src.Id() << _src.Color(); return *this; }
CState& CState::operator = (CState&& _victim)   { *this = (const CState&)_victim; return *this; }

CState& CState::operator <<(const TThemeState _e_id) { this->Id(_e_id, false); return *this; }
CState& CState::operator <<(const rgb_color  _color) { this->Color(_color); return *this; }

/////////////////////////////////////////////////////////////////////////////

CStates:: CStates (void) {}
CStates:: CStates (const CStates&_src) : CStates() { *this = _src; }
CStates:: CStates (CStates&& _victim) : CStates() { *this = _victim; }
CStates::~CStates (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CState&   CStates::Disabled(void) const { return this->Get(TThemeState::e_disabled); }
CState&   CStates::Disabled(void)       { return this->Get(TThemeState::e_disabled); }

const
CState&   CStates::Get (const TThemeState e_state_id) const {
	e_state_id;
	for (size_t i_ = 0; i_ < this->Raw().size(); i_++)
		if (e_state_id == this->Raw().at(i_).Id())
			return this->Raw().at(i_);

	static CState inv_state; return inv_state;
}
CState&   CStates::Get (const TThemeState e_state_id){
	e_state_id;
	for (size_t i_ = 0; i_ < this->Raw().size(); i_++)
		if (e_state_id == this->Raw().at(i_).Id())
			return this->Raw().at(i_);

	static CState inv_state; return inv_state;
}

const
CState&   CStates::Normal(void) const { return this->Get(TThemeState::e_normal); }
CState&   CStates::Normal(void)       { return this->Get(TThemeState::e_normal); }

const
TRawStates& CStates::Raw (void) const { return this->m_states; }
TRawStates& CStates::Raw (void)       { return this->m_states; }

const
CState&   CStates::Selected (void) const { return this->Get(TThemeState::e_selected); }
CState&   CStates::Selected (void)       { return this->Get(TThemeState::e_selected); }

/////////////////////////////////////////////////////////////////////////////

CStates& CStates::operator = (const CStates& _src) { *this << _src.Raw(); return *this; }
CStates& CStates::operator = (CStates&& _victim) { *this = (const CStates&)_victim; return *this; }

CStates& CStates::operator <<(const TRawStates& _raw) { this->Raw() = _raw; return *this; }

CStates::operator const TRawStates& (void) const { return this->Raw(); }
CStates::operator       TRawStates& (void) { return this->Raw(); }

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace theme {
// otherwise the ambiguity of the names: ex_ui::color::rgb::CNamed;
/////////////////////////////////////////////////////////////////////////////

CNamed:: CNamed (void) {
	for (size_t i_ = 0; i_ < this->Parts().size(); i_++) {
		if (false){}
		else if (0 == i_) this->Parts().at(i_).Id(TThemePart::e_form   , true);
		else if (1 == i_) this->Parts().at(i_).Id(TThemePart::e_panel  , true);
		else if (2 == i_) this->Parts().at(i_).Id(TThemePart::e_edit   , true);
		else if (3 == i_) this->Parts().at(i_).Id(TThemePart::e_label  , true);
		else if (4 == i_) this->Parts().at(i_).Id(TThemePart::e_caption, true);
		else if (5 == i_) this->Parts().at(i_).Id(TThemePart::e_button , true);
	}
}
CNamed:: CNamed (const CNamed& _src) : CNamed() { *this = _src; }
CNamed:: CNamed (CNamed&& _victim) : CNamed() { *this = (const CNamed&)_victim; } // does not care about move or swap operation;
CNamed::~CNamed (void) {}

/////////////////////////////////////////////////////////////////////////////

_pc_sz   CNamed::Desc (void) const { return (_pc_sz) this->m_desc; }
bool     CNamed::Desc (_pc_sz _p_desc) {
	_p_desc;
	const bool b_changed = 0 != this->m_desc.Compare(_p_desc);
	if (b_changed)
		this->m_desc = _p_desc;
	return b_changed;
}

bool     CNamed::Is_valid (void) const {

	if (TBase::Is_valid() == false)
		return false;

	for (size_t i_ = 0; i_ < this->Parts().size(); i_++) {
		if (this->Parts().at(i_).Is_valid())
			return true;
	}
	return false;
}

bool     CNamed::Is_valid (const bool _b_valid) {
	const bool b_changed = TBase::Is_valid() != _b_valid;

	if (b_changed)
		TBase::Is_valid(_b_valid);

	return b_changed;
}

#if defined(_DEBUG)
CString  CNamed::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("csl::[%s::%s] >> {%s%sname=%s;desc=%s;valid=%s;parts=%s%s%s\t}");
	static _pc_sz pc_sz_pat_n = _T("csl::[%s] >> {%s%sname=%s;desc=%s;valid=%s;parts=%s%s%s\t}");
	static _pc_sz pc_sz_pat_r = _T("%s%sname=%s;desc=%s;valid=%s;parts=%s%s%s\t");

	CString cs_desc    = this->m_desc.IsEmpty() ? _T("#not_set") : this->Desc();
	CString cs_name    = this->m_name.IsEmpty() ? _T("#not_set") : this->Name();
	CString cs_valid   = TStringEx().Bool(this->Is_valid());

	CString cs_parts;

	for (size_t i_ = 0; i_ < this->Parts().size(); i_++) {
		const CPart& part  = this->Parts().at(i_);
		cs_parts += _p_sfx;
		cs_parts += _p_pfx;
		cs_parts += TStringEx().Format(_T("part #%u: "), i_ + 1);
		cs_parts += part.Print(e_print::e_req);
		cs_parts += _p_sfx;
	}
	if (cs_parts.IsEmpty()) {
		cs_parts += _p_sfx;
		cs_parts += _p_pfx;
		cs_parts += _T("#empty");
		cs_parts += _p_sfx;
	}

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_name, (_pc_sz) cs_desc, (_pc_sz) cs_valid , _p_sfx, _p_pfx, (_pc_sz) cs_parts);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_name, (_pc_sz) cs_desc, (_pc_sz) cs_valid , _p_sfx, _p_pfx, (_pc_sz) cs_parts);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r,
		_p_sfx, _p_pfx, (_pc_sz) cs_name, (_pc_sz) cs_desc, (_pc_sz) cs_valid , _p_sfx, _p_pfx, (_pc_sz) cs_parts);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif
const
TRawParts&  CNamed::Parts (void) const { return this->m_parts; }
TRawParts&  CNamed::Parts (void)       { return this->m_parts; }

/////////////////////////////////////////////////////////////////////////////

CNamed&  CNamed::operator = (const CNamed& _src) { (TBase&)*this = (const TBase&)_src; *this >> _src.Desc() << _src.Parts(); return *this; }

CNamed&  CNamed::operator <<(_pc_sz _p_name) { TBase::Name(_p_name); return *this; }
CNamed&  CNamed::operator >>(_pc_sz _p_desc) { this->Desc(_p_desc); return *this; }

CNamed&  CNamed::operator <<(const TRawParts& _parts) {
	this->Parts() = _parts; return *this;
}

/////////////////////////////////////////////////////////////////////////////

CNamed_Enum:: CNamed_Enum (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited;
	for (size_t i_ = 0; i_ < this->Palettes().size(); i_++) {
		if (false){}
		else if (0 == i_) this->Palettes().at(i_).Id(TThemePalette::e_dark, true);
		else if (1 == i_) this->Palettes().at(i_).Id(TThemePalette::e_light, true);
	}
}
CNamed_Enum::~CNamed_Enum (void) {}

TError&  CNamed_Enum::Error(void) const { return this->m_error; }

err_code CNamed_Enum::Load(void) {
	this->m_error <<__METHOD__<<__s_ok;
#if (0)
	CDataLocator locator;
	CDataProvider provider;

	err_code n_result = locator.Refresh();
	if (__failed(n_result))
		return this->m_error = locator.Error();

	n_result = provider.Load((_pc_sz)locator.Get_full_path());
	if (__failed(n_result))
		return this->m_error = provider.Error();

	const CXmlDoc& doc_ = provider.Doc();
	const CNode& root_ = doc_.Root();

	const CNode_Enum* p_kids = root_.Children();
	if (p_kids) {
		const TNodes& nodes =  p_kids->Raw();
		for (uint32_t i_ = 0; i_ < nodes.size(); i_++) {

		}
	}
#else
	storage::CRegistry storage;

	if (__failed(storage.Load(*this)))
		this->m_error = storage.Error();

#endif
	return this->Error();
}

err_code CNamed_Enum::Load (const TThemePalette _palette_id) {
	_palette_id;
	this->m_error <<__METHOD__<<__s_ok;

	storage::CRegistry storage;

	if (__failed(storage.Load(_palette_id, *this)))
		this->m_error = storage.Error();

	return this->Error();
}

#if defined(_DEBUG)
CString  CNamed_Enum::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {%s%s%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s%s%s}");

	CString cs_palettes;
	for (size_t i_ = 0; i_ < this->Palettes().size(); i_++) {
		const CPalette& palette = this->Palettes().at(i_);
		cs_palettes += _p_sfx;
		cs_palettes += _p_pfx;
		cs_palettes += palette.Print(e_print::e_req);
	}
	if (cs_palettes.IsEmpty()) {
		cs_palettes += _p_sfx;
		cs_palettes += _p_pfx;
		cs_palettes += _T("#empty");
	}

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format ( pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_palettes, _p_sfx, _p_pfx); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format ( pc_sz_pat_n, (_pc_sz)__CLASS__  , (_pc_sz) cs_palettes, _p_sfx, _p_pfx); }
	if (e_print::e_req   == _e_opt) { cs_out.Format ( pc_sz_pat_r, (_pc_sz) cs_palettes , _p_sfx, _p_pfx); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

const
TRawPalettes& CNamed_Enum::Palettes (void) const { return this->m_palettes; }
TRawPalettes& CNamed_Enum::Palettes (void)       { return this->m_palettes; }

const
CPalette&     CNamed_Enum::PaletteOf (const TThemePalette _plt_id) const {

	for (size_t i_ = 0; i_ < this->Palettes().size(); i_++)
		if (_plt_id == this->Palettes().at(i_).Id())
			return this->Palettes().at(i_);

	static CPalette inv_palette;
	if (nullptr  == inv_palette.Name()) {
		inv_palette.Name(_T("#inv_palette"));
		inv_palette.Is_valid(false);
	}
	return inv_palette;
}


CCurrent&  Get_current (void) {
	using namespace ex_ui::theme::storage;
	return Get_router().CurrentTheme();
}

}}