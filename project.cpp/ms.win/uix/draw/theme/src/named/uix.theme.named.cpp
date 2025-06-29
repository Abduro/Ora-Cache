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

namespace ex_ui { namespace theme {
// otherwise the ambiguity of the names: ex_ui::color::rgb::CNamed;
/////////////////////////////////////////////////////////////////////////////

CNamed:: CNamed (const TThemePalette _palette) : m_palette(_palette) {} CNamed:: CNamed (const CNamed& _src) : CNamed() { *this = _src; }
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

_pc_sz   CNamed::Name (void) const { return (_pc_sz) this->m_name; }
bool     CNamed::Name (_pc_sz _p_name) {
	_p_name;
	const bool b_changed = 0 != this->m_name.Compare(_p_name);
	if (b_changed)
		this->m_name = _p_name;
	return b_changed;
}

bool CNamed::Is_valid(void) const { return this->Palette() != TThemePalette::e_none; }

TThemePalette CNamed::Palette (void) const { return this->m_palette; }
const bool    CNamed::Palette (const TThemePalette _e_palette) {
	_e_palette;
	const bool b_changed = this->Palette() != _e_palette;
	if (b_changed)
		this->m_palette = _e_palette;
	return b_changed;
}

#if defined(_DEBUG)
CString  CNamed::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("csl::[%s::%s] >> {palette=%s;name=%s;desc=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("csl::[%s] >> {palette=%s;name=%s;desc=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("palette=%s;name=%s;desc=%s;valid=%s");

	CString cs_palette = TPrint::Out(this->Palette());
	CString cs_desc    = this->m_desc.IsEmpty() ? _T("#not_set") : this->Desc();
	CString cs_name    = this->m_name.IsEmpty() ? _T("#not_set") : this->Name();
	CString cs_valid   = TStringEx().Bool(this->Is_valid());

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		(_pc_sz) cs_palette, (_pc_sz) cs_name, (_pc_sz) cs_desc , (_pc_sz) cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__,
		(_pc_sz) cs_palette, (_pc_sz) cs_name, (_pc_sz) cs_desc , (_pc_sz) cs_valid);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r,
		(_pc_sz) cs_palette, (_pc_sz) cs_name, (_pc_sz) cs_desc , (_pc_sz) cs_valid);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CNamed&  CNamed::operator = (const CNamed& _src) { *this << _src.Palette() << _src.Name() >> _src.Desc(); return *this; }

CNamed&  CNamed::operator <<(_pc_sz _p_name) { this->Name(_p_name); return *this; }
CNamed&  CNamed::operator >>(_pc_sz _p_desc) { this->Desc(_p_desc); return *this; }

CNamed&  CNamed::operator <<(const TThemePalette _palette) {
	this->Palette(_palette); return *this;
}

/////////////////////////////////////////////////////////////////////////////

CNamed_Enum:: CNamed_Enum (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
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

#if defined(_DEBUG)
CString  CNamed_Enum::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {%s%s%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s%s%s}");

	CString cs_themes;
	for (size_t i_ = 0; i_ < this->Raw().size(); i_++) {
		const CNamed& named = this->Raw().at(i_);
		cs_themes += _p_sfx;
		cs_themes += _p_pfx;
		cs_themes += named.Print(e_print::e_req);
	}
	if (cs_themes.IsEmpty()) {
		cs_themes += _p_sfx;
		cs_themes += _p_pfx;
		cs_themes += _T("#empty");
	}

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format ( pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_themes, _p_sfx, _p_pfx); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format ( pc_sz_pat_n, (_pc_sz)__CLASS__  , (_pc_sz) cs_themes, _p_sfx, _p_pfx); }
	if (e_print::e_req   == _e_opt) { cs_out.Format ( pc_sz_pat_r, (_pc_sz) cs_themes , _p_sfx, _p_pfx); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

const
TRawNamed& CNamed_Enum::Raw (void) const { return this->m_themes; }
TRawNamed& CNamed_Enum::Raw (void)       { return this->m_themes; }

}}