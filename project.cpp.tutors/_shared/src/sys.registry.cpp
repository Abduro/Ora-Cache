/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Nov-2025 at 13:32:55.600, UTC+4, Batumi, Sunday;
	This is Ebo Pack system registry storage wrapper interface implementation file;
*/
#include "sys.registry.h"
#include "shared.preproc.h"

using namespace shared::sys_core::storage;

HKEY CReg_router::Root (void) const { return this->m_root; }

CReg_router&  Get_router (void) {
	static CReg_router router;
	return router;
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
		m_the_key.m_error << __e_inv_arg = _T("Input registry key path/name is invalid"); return CString();
	}
	else
		(*this)() << _p_key_path; // puts the path to the cache;

	LSTATUS n_result = __s_ok;
	if (nullptr == m_the_key()){
		n_result = m_the_key().Open(Get_router().Root(), (_pc_sz) _p_key_path);
		if (!!n_result) {
			m_the_key.m_error = dword(n_result); return CString();
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