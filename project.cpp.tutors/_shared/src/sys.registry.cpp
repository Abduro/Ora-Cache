/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Nov-2025 at 13:32:55.600, UTC+4, Batumi, Sunday;
	This is Ebo Pack system registry storage wrapper interface implementation file;
*/
#include "sys.registry.h"
#include "shared.preproc.h"

using namespace shared::sys_core::storage;

#pragma region cls::CRegistry{}

CRegistry:: CRegistry (void) { this->m_error >> __CLASS__ << __METHOD__ << __s_ok; }
CRegistry::~CRegistry (void) {}

TError&  CRegistry::Error (void) const { return this->m_error; }

CString  CRegistry::Value (const e_element _element) const {
	_element;

	CRegKey_Ex reg_key;

	CString cs_value = reg_key.Value().GetString((_pc_sz) Get_reg_router().Theme().Path(_element), CTheme::To_str(_element));
	if (cs_value.IsEmpty())
		this->m_error = reg_key.Error();

	return  cs_value;
}

CString  CRegistry::Value (_pc_sz _p_object, const e_shaders _e_type) const {
	_p_object; _e_type;
	this->m_error <<__METHOD__<<__s_ok;

	if (e_shaders::e__undef == _e_type) {
		this->m_error <<__e_inv_arg = _T("No shader type is specified");
		return CString();
	}

	CShaders& shaders = Get_reg_router().Shaders();

	CRegKey_Ex reg_key;

	CString cs_value = reg_key.Value().GetString((_pc_sz) shaders.Path(_p_object), (_pc_sz) shaders.Name(_e_type));
	if (cs_value.IsEmpty())
		this->m_error = reg_key.Error();

	return  cs_value;
}

CString  CRegistry::Value (_pc_sz _p_key_path, _pc_sz _p_value_name) const {
	_p_key_path; _p_value_name;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _p_key_path || 0 == ::_tcslen(_p_key_path)) {
		this->m_error <<__e_inv_arg = _T("#__e_inv_arg: key path is invalid");
	}

	CRegKey_Ex reg_key;

	CString cs_value = reg_key.Value().GetString(_p_key_path, _p_value_name); if (reg_key.Error()) this->m_error = reg_key.Error();
	return  cs_value;
}

CRegistry& ::Get_registry (void) {
	static CRegistry registry;
	return registry;
}
#pragma endregion
#pragma region cls::CRegKey_Ex::CCache{}

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

#pragma endregion
#pragma region cls::CRegKey_Ex::CSubKeys{}

using CSubKeys = CRegKey_Ex::CSubKeys;

CSubKeys::CSubKeys (CKey& _the_key) : m_parent(_the_key) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

uint32_t  CSubKeys::Count (void) const { return static_cast<uint32_t>(this->Names().size()); }
TError&   CSubKeys::Error (void) const { return this->m_error; }

err_code  CSubKeys::Enum (void) {
	this->m_error <<__METHOD__<<__s_ok;
	return CSubKeys::Enum(this->m_parent(), this->m_names, this->m_error);
}

err_code  CSubKeys::Enum (_pc_sz _p_key_path, TSubKeys& _names, CError& _err, const bool _b_full_path) {
	_p_key_path; _names; _err; _b_full_path;
#if (0) // reg_key.Open() tracks it itself;
	if (nullptr == _p_key_path || 0 == ::_tcslen(_p_key_path))
		return _err <<__e_inv_arg = _T("#__e_inv_arg: parent key path is invalid");
#endif
	CRegKey_Ex reg_key;
	if (__failed(reg_key.Open(_p_key_path)))
		return _err = reg_key.Error();

	if (__failed(CSubKeys::Enum(reg_key(), _names, _err)))
		return _err;
	if (_b_full_path && _names.empty() == false) {
		for (uint32_t i_ = 0; i_ < _names.size(); i_++)
			_names.at(i_) = TString().Format(_T("%s\\%s"), _p_key_path, (_pc_sz) _names.at(i_)); // replaces the name by full path to sub-key;
	}

	return _err;
}
err_code  CSubKeys::Enum (const HKEY _h_parent, TSubKeys& _names, CError& _err) {
	_h_parent; _names; _err;
	if (nullptr == _h_parent){
		return _err <<__e_inv_arg = _T("The parent key handle is invalid");
	}

	if (_names.empty() == false)
		_names.clear();
	// https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regqueryinfokeyw ;
	dword u_count = 0;
	LSTATUS n_result = ::RegQueryInfoKey(_h_parent, 0, 0, 0, &u_count, 0, 0, 0, 0, 0, 0, 0);
	if (!!n_result) {
		return _err = (dword) n_result;
	}
	// https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regenumkeyexw ;
	static const uint32_t req_sz = 256;
	dword u_length = 0;

	for (uint32_t i_ = 0; i_ < u_count; i_++) {
		u_length = req_sz;
		CString cs_name;
		n_result = ::RegEnumKeyEx(_h_parent, i_, cs_name.GetBuffer(req_sz), &u_length, 0, 0, 0, 0);
		if (!!n_result) {
			return _err = (dword) n_result;
		}
		try {
			_names.push_back(cs_name);
		} catch (const ::std::bad_alloc&) { _err << __e_no_memory; }
	}

	return _err;
}

const
TSubKeys& CSubKeys::Names (void) const { return this->m_names; }

#pragma endregion
#pragma region cls::CRegKey_Ex::CValue{}

static _pc_sz p_err_inv_path = _T("Input registry key path is invalid");
static _pc_sz p_err_inv_name = _T("Input registry value name is invalid");

static _pc_sz p_err_no_name  = _T("The value name is not set");
static _pc_sz p_err_no_path  = _T("The key path is not set");

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
	LSTATUS n_result = m_the_key().QueryDWORDValue(_p_name, d_value);
	if (!!n_result) {
		(m_the_key.m_error = dword(n_result)) <<__METHOD__ = TString().Format(_T("The value of name '%s' is not defined;"), _p_name);
		return 0u;
	}
	else
		return static_cast<uint32_t>(d_value);
}

uint32_t CRegKey_Ex::CValue::GetDword (_pc_sz _p_key_path, _pc_sz _p_name) {
	_p_key_path; _p_name;
	m_the_key[(long)0] <<__METHOD__<<__s_ok; // not readable assignment to error object;
	
	if (nullptr == m_the_key()){
		if (__failed(this->m_the_key.Open(_p_key_path))) return 0u;
	}
	else (*this)() << _p_key_path; // puts the path to the cache;

	return this->GetDword(_p_name);
}

long CRegKey_Ex::CValue::GetLong (_pc_sz _p_name) {
	_p_name;
	CString cs_value = this->GetString(_p_name);
	return ::_tstol(cs_value);
}

long CRegKey_Ex::CValue::GetLong (_pc_sz _p_key_path, _pc_sz _p_name) {
	_p_key_path; _p_name;
	CString cs_value = this->GetString(_p_key_path, _p_name);
	return ::_tstol(cs_value);
}

t_rect  CRegKey_Ex::CValue::GetRect (_pc_sz _p_key_path) {
	_p_key_path;
	this->m_the_key.m_error <<__METHOD__<<__s_ok;

	t_rect rc_result = {0};

	if (nullptr == m_the_key()){
		if (__failed(this->m_the_key.Open(_p_key_path))) return rc_result;
	}
	rc_result.left   = this->GetLong(_T("left"));
	rc_result.top    = this->GetLong(_T("top"));
	rc_result.right  = this->GetLong(_T("right"));
	rc_result.bottom = this->GetLong(_T("bottom"));

	return rc_result;
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
	this->m_the_key.m_error <<__METHOD__<<__s_ok;
	
	if (nullptr == m_the_key()){
		if (__failed(this->m_the_key.Open(_p_key_path))) return CString();
	}
	else (*this)() << _p_key_path; // puts the path to the cache;
	return this->GetString(_p_name);
}

const
CRegKey_Ex::CCache&  CRegKey_Ex::CValue::operator ()(void) const { return this->m_cache; }
CRegKey_Ex::CCache&  CRegKey_Ex::CValue::operator ()(void)       { return this->m_cache; }

err_code CRegKey_Ex::CValue::Set (_pc_sz _p_value) {
	_p_value;
	m_the_key.m_error <<__METHOD__<<__s_ok;

	if (false == (*this)().Is()) return m_the_key.m_error << __e_inv_arg = p_err_no_path;
	if (nullptr == (*this)().Name()) return m_the_key.m_error << __e_inv_arg = p_err_no_name;

	return this->Set((*this)().Path(), (*this)().Name(), _p_value);
}

err_code CRegKey_Ex::CValue::Set (_pc_sz _p_key_path, _pc_sz _p_name, _pc_sz _p_value) {
	_p_key_path; _p_name; _p_value;
	m_the_key.m_error <<__METHOD__<<__s_ok;
	if (nullptr == _p_key_path || 0 == ::_tcslen(_p_key_path)) { return m_the_key.m_error << __e_inv_arg = p_err_inv_path; }

	LSTATUS n_result = __s_ok;
	if (nullptr == m_the_key()){ // the key is not open yet;
		if (__failed(this->m_the_key.Open(_p_key_path))) return this->m_the_key.Error();
	}
	n_result = m_the_key().SetStringValue(_p_name, _p_value);
	if (!!n_result) {
		(m_the_key.m_error = dword(n_result)) = TString().Format(_T("Set value '%s' to '%s' is failed"), _p_name, _p_value);
	}

	return m_the_key.Error();
}

err_code CRegKey_Ex::CValue::SetLong (const long _u_value) {
	_u_value;
	m_the_key.m_error <<__METHOD__<<__s_ok;

	if (false == (*this)().Is()) return m_the_key.m_error << __e_inv_arg = p_err_no_path;
	if (nullptr == (*this)().Name()) return m_the_key.m_error << __e_inv_arg = p_err_no_name;

	return this->Set((*this)().Path(), (*this)().Name(), _u_value);
}

err_code CRegKey_Ex::CValue::SetLong (_pc_sz _p_key_path, _pc_sz _p_name, const long _u_value) {
	_p_key_path; _p_name; _u_value;
	return this->Set(_p_key_path, _p_name, TString().Long(_u_value));
}

err_code CRegKey_Ex::CValue::Set (const uint32_t _u_value) {
	_u_value;
	m_the_key.m_error <<__METHOD__<<__s_ok;

	if (false == (*this)().Is()) return m_the_key.m_error << __e_inv_arg = p_err_no_path;
	if (nullptr == (*this)().Name()) return m_the_key.m_error << __e_inv_arg = p_err_no_name;

	return this->Set((*this)().Path(), (*this)().Name(), _u_value);
}

err_code CRegKey_Ex::CValue::Set (_pc_sz _p_key_path, _pc_sz _p_name, const uint32_t _u_value) {
	_p_key_path; _p_name; _u_value;
	m_the_key.m_error <<__METHOD__<<__s_ok;
	if (nullptr == _p_key_path || 0 == ::_tcslen(_p_key_path)) { return m_the_key.m_error << __e_inv_arg = p_err_inv_path; }
	if (nullptr == _p_name || 0 == ::_tcslen(_p_name)) { return m_the_key.m_error << __e_inv_arg = p_err_inv_name; }

	LSTATUS n_result = __s_ok;
	if (nullptr == m_the_key()){ // the key is not open yet;
		if (__failed(this->m_the_key.Open(_p_key_path))) return this->m_the_key.Error();
	}
	// https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regsetvalueexw ;
	n_result = m_the_key().SetDWORDValue(_p_name, _u_value);
	if (!!n_result) {
		(m_the_key.m_error = dword(n_result)) = TString().Format(_T("Set value '%s' to (%d) is failed"), _p_name, _u_value);
	}

	return m_the_key.Error();
}

err_code CRegKey_Ex::CValue::Set (_pc_sz _p_key_path, const t_rect& _rect) {
	_p_key_path; _rect;
	m_the_key.m_error <<__METHOD__<<__s_ok;

	if (nullptr == _p_key_path || 0 == ::_tcslen(_p_key_path)) { return m_the_key.m_error << __e_inv_arg = p_err_inv_path; }

	if (__failed(this->SetLong(_p_key_path, _T("left"), _rect.left))) return m_the_key.Error();
	if (__failed(this->SetLong(_p_key_path, _T("top"), _rect.top))) return m_the_key.Error();
	if (__failed(this->SetLong(_p_key_path, _T("right"), _rect.right))) return m_the_key.Error();
	if (__failed(this->SetLong(_p_key_path, _T("bottom"), _rect.bottom))) return m_the_key.Error();

	return m_the_key.Error();
}

CRegKey_Ex::CValue::operator _pc_sz (void) /*const*/ { return this->GetString((*this)().Path(), (*this)().Name()); }

#pragma endregion
#pragma region cls::CRegKey_Ex{}

CRegKey_Ex:: CRegKey_Ex (void) : m_value(*this), m_sub_keys(*this) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CRegKey_Ex:: CRegKey_Ex (_pc_sz _p_key_path) : CRegKey_Ex() { this->Open(_p_key_path); }
CRegKey_Ex::~CRegKey_Ex (void) {}

err_code CRegKey_Ex::Close (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_open()) {
		if (!!this->m_key.Close()) // https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regclosekey ;
			this->m_error.Last();
	}
	return this->Error();
}

TError&  CRegKey_Ex::Error (void) const { return this->m_error; }

bool CRegKey_Ex::Is_exist (_pc_sz _p_key_path) const {
	_p_key_path;
	this->m_error <<__METHOD__<<__s_ok;

	bool b_result = false;
	if (nullptr == _p_key_path || 0 == ::_tcslen(_p_key_path)) {
		this->m_error <<__e_inv_arg = _T("#__e_inv_key: '_p_key_path' is invalid"); return b_result;
	}
	b_result = 0 == CRegKey().Open(Get_reg_router().Root().Key(), _p_key_path); // cannot use m_key field due to this is the 'const' method;
	return b_result;
}

bool  CRegKey_Ex::Is_open (void) const { return nullptr != this->m_key; }

err_code CRegKey_Ex::Open (_pc_sz _p_key_path) {
	_p_key_path;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr != (*this)())
		return this->m_error <<(err_code)TErrCodes::eExecute::eState = _T("#__inv_state: the key is open");

	if (nullptr == _p_key_path || 0 == ::_tcslen(_p_key_path)) {
		CString cs_err = nullptr == _p_key_path ? _T("(nullptr)") : _T("(empty)");
		this->m_error << __e_inv_arg = TString().Format(_T("Input registry key path '%s' is invalid"), (_pc_sz) cs_err); return this->Error();
	}
	// checks the existance of the registry key first;
	if (this->Is_exist(_p_key_path) == false) {
		if (0 != CRegKey().Create(::Get_reg_router().Root().Key(), _p_key_path))
			return this->m_error << __e_fail = TString().Format(_T("#__e_failure: cannot create '%s' key"), _p_key_path);
	}

	const
	LSTATUS n_result = (*this)().Open(Get_reg_router().Root().Key(), _p_key_path);
	if (!!n_result) {
		(this->m_error = dword(n_result)) = TString().Format(_T("The key path '%s' does not exist"), _p_key_path);
	}

	return this->Error();
}
const
CSubKeys& CRegKey_Ex::SubKeys (void) const { return this->m_sub_keys; }
CSubKeys& CRegKey_Ex::SubKeys (void)       { return this->m_sub_keys; }

const
CRegKey_Ex::CValue& CRegKey_Ex::Value (void) const { return this->m_value; }
CRegKey_Ex::CValue& CRegKey_Ex::Value (void)       { return this->m_value; }

TError&  CRegKey_Ex::operator [](const long _not_used) const { _not_used; return this->m_error; }
CError&  CRegKey_Ex::operator [](const long _not_used)       { _not_used; return this->m_error; }

CRegKey& CRegKey_Ex::operator ()(void) { return this->m_key; }
const
CRegKey_Ex::CValue&  CRegKey_Ex::operator [](_pc_sz _not_used) const { _not_used; return this->Value(); }
CRegKey_Ex::CValue&  CRegKey_Ex::operator [](_pc_sz _not_used)       { _not_used; return this->Value(); }

#pragma endregion