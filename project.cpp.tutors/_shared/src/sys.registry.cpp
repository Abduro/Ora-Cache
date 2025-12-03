/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Nov-2025 at 13:32:55.600, UTC+4, Batumi, Sunday;
	This is Ebo Pack system registry storage wrapper interface implementation file;
*/
#include "sys.registry.h"
#include "shared.preproc.h"

using namespace shared::sys_core::storage;

#define TutorialRootKey HKEY_CURRENT_USER

/////////////////////////////////////////////////////////////////////////////

using e_element  = CReg_router::CTheme::e_element;
using e_renderer = CReg_router::CRoot::e_renderer;
using e_shaders  = CReg_router::CShaders::e_types;

namespace shared { namespace sys_core { namespace storage { namespace _impl {

	static e_renderer e_current = e_renderer::e_open_gl;
	static CString cs_$_root;
	static CString cs_theme;

}}}}

CReg_router::CRoot::CRoot (void) {}
const
HKEY    CReg_router::CRoot::Key  (void) const { static HKEY h_key = TutorialRootKey; return h_key; }
_pc_sz  CReg_router::CRoot::Path (void) const { static _pc_sz p_path = _T("Software\\ebo::pack\\tutorials"); return p_path; }

CString CReg_router::CRoot::Path (const e_renderer _renderer) const {
	_renderer;
	CString cs_path;

	if (e_renderer::e_direct_x == _renderer) cs_path.Format(_T("%s\\direct_x"), CReg_router::CRoot::Path());
	if (e_renderer::e_open_gl  == _renderer) cs_path.Format(_T("%s\\open_gl"), CReg_router::CRoot::Path());

	return  cs_path;
}

e_renderer CReg_router::CRoot::Renderer (void) const { return _impl::e_current; }
const bool CReg_router::CRoot::Renderer (const e_renderer _e_curr) {
	_e_curr;
	const bool b_changed = this->Renderer() != _e_curr;
	if (b_changed) {
		_impl::e_current = _e_curr;
		_impl::cs_$_root = _T("");  // must be set by shaders' class itself;
	}
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CReg_router::CShaders::CShaders (void) {}

CString CReg_router::CShaders::Path (const e_shaders _shader) const {
	_shader;
	CString cs_path;

	if (e_shaders::e_fragment == _shader) cs_path.Format(_T("%s\\$_fragment"), this->Root());
	if (e_shaders::e_vertex   == _shader) cs_path.Format(_T("%s\\$_vertex"), this->Root());

	return  cs_path;
}

_pc_sz  CReg_router::CShaders::Root (void) const {

	if (_impl::cs_$_root.IsEmpty()) {
		_impl::cs_$_root.Format(_T("%s\\shaders"), (_pc_sz) Get_reg_router().Root().Path(Get_reg_router().Root().Renderer()));
	}
	return (_pc_sz)_impl::cs_$_root;
}

/////////////////////////////////////////////////////////////////////////////

CReg_router::CTheme::CTheme (void) {}

CString CReg_router::CTheme::Path (const e_element _element) const {
	_element;
	CString cs_path;

	if (e_element::e_bkgnd  == _element) cs_path.Format(_T("%s"), this->Root());
	if (e_element::e_border == _element) cs_path.Format(_T("%s"), this->Root());

	return  cs_path;
}

_pc_sz  CReg_router::CTheme::Root (void) const {

	if (_impl::cs_theme.IsEmpty()) {
		_impl::cs_theme.Format(_T("%s\\theme"), (_pc_sz) Get_reg_router().Root().Path(Get_reg_router().Root().Renderer()));
	}
	return (_pc_sz)_impl::cs_theme;
}

_pc_sz  CReg_router::CTheme::To_str (const e_element _element) {
	static CString cs_out;

	if (e_element::e_bkgnd == _element) cs_out = _T("bkgnd");
	if (e_element::e_border == _element) cs_out = _T("border");

	return (_pc_sz) cs_out; // if it is empty, then the '(default)' value is meant;
}

/////////////////////////////////////////////////////////////////////////////

using CCell = CReg_router::CViewport::CViewport::CGrid::CCell;
using CGrid = CReg_router::CViewport::CViewport::CGrid;
using CViewport = CReg_router::CViewport;

CCell::CCell (void) {}

_pc_sz CCell::Root (void) const {

	static CString cs_cell;

	if (cs_cell.IsEmpty()) {
		cs_cell.Format(_T("%s\\cell"), (_pc_sz) Get_reg_router().Viewport().Grid().Root());
	}
	return (_pc_sz)cs_cell;
}

CString CCell::Value (const e_values _e_value) const {
	_e_value;
	if (e_values::e_height == _e_value) return CString(_T("height"));
	if (e_values::e_width == _e_value) return CString(_T("width"));

	return CString(_T("")); // this is '(default)' value name;
}

CGrid::CGrid (void) {}
const
CCell& CGrid::Cell (void) const { return m_cell; }
CCell& CGrid::Cell (void)       { return m_cell; }

_pc_sz CGrid::Clr_name (void) const { static _pc_sz p_clr_name = _T("color"); return p_clr_name; }

_pc_sz CGrid::Root (void) const {

	static CString cs_grid;

	if (cs_grid.IsEmpty()) {
		cs_grid.Format(_T("%s\\grid"), (_pc_sz) Get_reg_router().Viewport().Root());
	}
	return (_pc_sz)cs_grid;
}

CViewport::CViewport (void) {}
const
CGrid& CViewport::Grid (void) const { return this->m_grid; }
CGrid& CViewport::Grid (void)       { return this->m_grid; }

_pc_sz CViewport::Root (void) const {

	static CString cs_viewport;

	if (cs_viewport.IsEmpty()) {
		cs_viewport.Format(_T("%s\\viewport"), (_pc_sz) Get_reg_router().Root().Path(Get_reg_router().Root().Renderer()));
	}
	return (_pc_sz) cs_viewport;
}

/////////////////////////////////////////////////////////////////////////////

CReg_router:: CReg_router (void) {}
CReg_router::~CReg_router (void) {}
const
CReg_router::CRoot&  CReg_router::Root (void) const { return this->m_root; }
CReg_router::CRoot&  CReg_router::Root (void)       { return this->m_root; }
const
CReg_router::CShaders& CReg_router::Shaders (void) const { return this->m_shaders; }
CReg_router::CShaders& CReg_router::Shaders (void)       { return this->m_shaders; }
const
CReg_router::CTheme&  CReg_router::Theme (void) const { return this->m_theme; }
CReg_router::CTheme&  CReg_router::Theme (void)       { return this->m_theme; }
const
CReg_router::CViewport& CReg_router::Viewport (void) const { return this->m_v_port; }
CReg_router::CViewport& CReg_router::Viewport (void)       { return this->m_v_port; }

CReg_router& ::Get_reg_router (void) {
	static CReg_router router;
	return router;
}

/////////////////////////////////////////////////////////////////////////////

CRegistry:: CRegistry (void) { this->m_error >> __CLASS__ << __METHOD__ << __s_ok; }
CRegistry::~CRegistry (void) {}

TError&  CRegistry::Error (void) const { return this->m_error; }

CString  CRegistry::Value (const e_element& _element) const {
	_element;

	CRegKey_Ex reg_key;

	CString cs_value = reg_key.Value().GetString((_pc_sz) Get_reg_router().Theme().Path(_element), CReg_router::CTheme::To_str(_element));
	if (cs_value.IsEmpty())
		this->m_error = reg_key.Error();

	return  cs_value;
}

CString  CRegistry::Value (const e_shaders _e_shader, _pc_sz _p_name) const {
	_e_shader; _p_name;
	this->m_error <<__METHOD__<<__s_ok;

	if (e_shaders::e__undef == _e_shader) {
		this->m_error <<__e_inv_arg = _T("No shader type is specified");
		return CString();
	}

	CRegKey_Ex reg_key;

	CString cs_value = reg_key.Value().GetString((_pc_sz) Get_reg_router().Shaders().Path(_e_shader), _p_name);
	if (cs_value.IsEmpty())
		this->m_error = reg_key.Error();

	return  cs_value;
}

CRegistry& ::Get_registry (void) {
	static CRegistry registry;
	return registry;
}

/////////////////////////////////////////////////////////////////////////////

CRegKey_Ex::CCache:: CCache (_pc_sz _p_path, _pc_sz _p_name) { *this << _p_path >> _p_name; }

bool   CRegKey_Ex::CCache::Is (void) const { return this->m_path.IsEmpty() == false; }

_pc_sz CRegKey_Ex::CCache::Name (void) const { return (_pc_sz) this->m_name; }
_pc_sz CRegKey_Ex::CCache::Path (void) const { return (_pc_sz) this->m_path; }

bool   CRegKey_Ex::CCache::Name (_pc_sz _p_name) {
	_p_name;
//	if (nullptr == _p_name || 0 == ::_tcslen(_p_name)) {} it is not necessary to check the input name due to it may be empty for (default) value;
	CString cs_name(_p_name); cs_name.Trim();

	const bool b_changed = !!this->m_name.CompareNoCase((_pc_sz) cs_name);
	if (b_changed)
		this->m_name = cs_name;
	return b_changed;
}

bool   CRegKey_Ex::CCache::Path (_pc_sz _p_path) {
	_p_path;
	if (nullptr == _p_path || 0 == ::_tcslen(_p_path))
		return false;
	CString cs_path(_p_path); cs_path.Trim();

	const bool b_changed = !!this->m_path.CompareNoCase((_pc_sz) cs_path);
	if (b_changed)
		this->m_path = cs_path;
	return b_changed;
}

bool   CRegKey_Ex::CCache::Set (_pc_sz _p_path, _pc_sz _p_name) {
	_p_path; _p_name;
	bool b_changed = false;

	if (this->Name(_p_name)) b_changed = true;
	if (this->Path(_p_path)) b_changed = true;

	return b_changed;
}

CRegKey_Ex::CCache& CRegKey_Ex::CCache::operator << (_pc_sz _p_path) { this->Path(_p_path); return *this; }
CRegKey_Ex::CCache& CRegKey_Ex::CCache::operator >> (_pc_sz _p_name) { this->Name(_p_name); return *this; }

/////////////////////////////////////////////////////////////////////////////

CRegKey_Ex::CValue:: CValue (CRegKey_Ex& _the_key) : m_the_key(_the_key) {}

const
CRegKey_Ex::CCache& CRegKey_Ex::CValue::Cache (void) const { return this->m_cache; }
CRegKey_Ex::CCache& CRegKey_Ex::CValue::Cache (void)       { return this->m_cache; }

uint32_t CRegKey_Ex::CValue::GetDword (_pc_sz _p_name) {
	_p_name;
	if (nullptr == m_the_key()){
		m_the_key.m_error <<__METHOD__<< __e_not_inited; return 0u;
	}
	else
		(*this)() >> _p_name;  // puts the name to the cache;

	dword d_value  = 0;
	LSTATUS n_result = m_the_key().QueryDWORDValue((_pc_sz) _p_name, d_value);
	if (!!n_result) {
		(m_the_key.m_error = dword(n_result)) <<__METHOD__ = TString().Format(_T("The value of name '%s' is not defined;"), _p_name);
		return 0u;
	}
	else
		return static_cast<uint32_t>(d_value);
}

uint32_t CRegKey_Ex::CValue::GetDword (_pc_sz _p_key_path, _pc_sz _p_name) {
	_p_key_path; _p_name;
	m_the_key[(long)0] <<__METHOD__<<__s_ok;
	if (nullptr == _p_key_path || 0 == ::_tcslen(_p_key_path)) {
		m_the_key.m_error << __e_inv_arg = _T("Input registry key path is invalid"); return 0u;
	}
	else
		(*this)() << _p_key_path; // puts the path to the cache;

	LSTATUS n_result = __s_ok;
	if (nullptr == m_the_key()){
		n_result = m_the_key().Open(Get_reg_router().Root().Key(), (_pc_sz) _p_key_path);
		if (!!n_result) {
			(m_the_key.m_error = dword(n_result)) = TString().Format(_T("The key path '%s' does not exist"), (_pc_sz)_p_key_path); return 0u;
		}
	}
	return this->GetDword(_p_name);
}

CString CRegKey_Ex::CValue::GetString (_pc_sz _p_name) {
	_p_name;
	if (nullptr == m_the_key()){
		m_the_key.m_error <<__METHOD__<< __e_not_inited; return CString();
	}
	else
		(*this)() >> _p_name;  // puts the name to the cache;

	t_char  sz_buffer[512] = {0}; unsigned long u_count = _countof(sz_buffer);

	unsigned long n_chars = u_count;

	LSTATUS n_result = m_the_key().QueryStringValue((_pc_sz) _p_name, sz_buffer, &n_chars);
	if (!!n_result) {
		(m_the_key.m_error = dword(n_result)) <<__METHOD__ = TString().Format(_T("The value of name '%s' is not defined;"), _p_name);
		return CString();
	}
	else
		return CString(sz_buffer);
}

CString CRegKey_Ex::CValue::GetString (_pc_sz _p_key_path, _pc_sz _p_name) {
	_p_key_path; _p_name;

	m_the_key[(long)0] <<__METHOD__<<__s_ok; // not readable assignment to error object;
	if (nullptr == _p_key_path || 0 == ::_tcslen(_p_key_path)) {
		m_the_key.m_error << __e_inv_arg = _T("Input registry key path is invalid"); return CString();
	}
	else
		(*this)() << _p_key_path; // puts the path to the cache;

	LSTATUS n_result = __s_ok;
	if (nullptr == m_the_key()){
		n_result = m_the_key().Open(Get_reg_router().Root().Key(), (_pc_sz) _p_key_path);
		if (!!n_result) {
			(m_the_key.m_error = dword(n_result)) = TString().Format(_T("The key path '%s' does not exist"), (_pc_sz)_p_key_path); return CString();
		}
	}
	return this->GetString(_p_name);
}

const
CRegKey_Ex::CCache&  CRegKey_Ex::CValue::operator ()(void) const { return this->m_cache; }
CRegKey_Ex::CCache&  CRegKey_Ex::CValue::operator ()(void)       { return this->m_cache; }

CRegKey_Ex::CValue::operator _pc_sz (void) /*const*/ { return this->GetString((*this)().Path(), (*this)().Name()); }

/////////////////////////////////////////////////////////////////////////////

CRegKey_Ex:: CRegKey_Ex (void) : m_value(*this) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CRegKey_Ex::~CRegKey_Ex (void) {}

/////////////////////////////////////////////////////////////////////////////

TError& CRegKey_Ex::Error (void) const { return this->m_error; }
const
CRegKey_Ex::CValue& CRegKey_Ex::Value (void) const { return this->m_value; }
CRegKey_Ex::CValue& CRegKey_Ex::Value (void)       { return this->m_value; }

TError&  CRegKey_Ex::operator [](const long _not_used) const { _not_used; return this->m_error; }
CError&  CRegKey_Ex::operator [](const long _not_used)       { _not_used; return this->m_error; }

CRegKey& CRegKey_Ex::operator ()(void) { return this->m_key; }
const
CRegKey_Ex::CValue&  CRegKey_Ex::operator [](_pc_sz _not_used) const { _not_used; return this->Value(); }
CRegKey_Ex::CValue&  CRegKey_Ex::operator [](_pc_sz _not_used)       { _not_used; return this->Value(); }