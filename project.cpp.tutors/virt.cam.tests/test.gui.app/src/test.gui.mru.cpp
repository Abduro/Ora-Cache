/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Nov-2026 at 10:38:59.675, UTC+4, Batumi, Tuesday;
	This is virtual camera test application MRU class interface implementation file;
*/
#include "test.gui.mru.h"

using namespace ::test::app::storage;

namespace test { namespace app { namespace storage { namespace _impl {
}}}}

#pragma region cls::CMruItem{}

CMruItem::CMruItem (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CMruItem::CMruItem (const CMruItem& _src) { *this = _src; }
CMruItem::CMruItem (CMruItem&& _victim) { *this = _victim; }

TError&   CMruItem::Error (void) const { return this->m_error; }

static _pc_sz p_err_path_empty = _T("__e_inv_arg: Input path to HTML file is not set");
static _pc_sz p_err_path_invalid = _T("__e_inv_arg: Input path to HTML file does not exist");

bool      CMruItem::Is_valid (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->m_path.IsEmpty())
		return (this->m_error << __e_inv_arg = p_err_path_empty).Is() == false;
	if (false == this->Timestamp().Is_valid()) {
		this->m_error <<__e_inv_arg =_T("__e_inv_arg: Timestamp is invalid");
	}

	return this->Error() == false;
}

_pc_sz    CMruItem::Path (void) const { return (_pc_sz) this->m_path; }
err_code  CMruItem::Path (_pc_sz _path) {
	this->m_error <<__METHOD__<<__s_ok;

	CString cs_path(_path); cs_path.Trim();
	if (cs_path.IsEmpty())
		return this->m_error <<__e_inv_arg = p_err_path_empty;
	// https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathfileexistsw) ;
	if (false == !!::PathFileExists((_pc_sz) cs_path))
		this->m_error.Last();
	else
		this->m_path = cs_path;
	return this->Error();
}

const
CTimestamp& CMruItem::Timestamp (void) const { return this->m_stamp; }
CTimestamp& CMruItem::Timestamp (void)       { return this->m_stamp; }

CMruItem& CMruItem::operator = (const CMruItem& _src) { *this << _src.Path() << _src.Timestamp(); return *this; }
CMruItem& CMruItem::operator = (CMruItem&& _victim) { *this = (const CMruItem&)_victim; return *this; } // clearing of input argument is ignored;
CMruItem& CMruItem::operator <<(_pc_sz _p_path) { this->Path(_p_path); return *this; }
CMruItem& CMruItem::operator <<(const CTimestamp& _stamp) { this->Timestamp() = _stamp; return *this; }

#pragma endregion
#pragma region cls::CMruList{}

CMruList:: CMruList (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("__e_not_inited: MRU list is empty"); }
CMruList::~CMruList (void) {}

err_code CMruList::Add (_pc_sz _p_html_path) {
	_p_html_path;
	this->m_error <<__METHOD__<<__s_ok;
	return this->Error();
}

TError&  CMruList::Error (void) const { return this->m_error; }
const
TMruItems& CMruList::Items (void) const { return this->m_items; }
TMruItems& CMruList::Items (void)       { return this->m_items; }

err_code CMruList::Load (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Items().empty() == false)
		this->Items().clear();

	using TSubKeys = ::shared::sys_core::storage::TSubKeys;
	TSubKeys sub_keys;
	if (__failed(TRegKeyEx::CSubKeys::Enum(Get_reg_router().Mru().Root(), sub_keys, this->m_error, false))) // full path of registry key is turned off;
		return this->Error();

	TRegKeyEx the_key;
	CString sub_key_path;
	CString html_path;

	for (uint32_t i_ = 0; i_ < sub_keys.size(); i_++) {

		CTimestamp stamp((_pc_sz) sub_keys.at(i_)); // the name of sub-key is actually a timestamp as a string value;
		if (false == stamp.Is_valid())
			continue;

		sub_key_path = TString().Format(_T("%s\\%s"), Get_reg_router().Mru().Root(), (_pc_sz) sub_keys.at(i_));

		html_path = the_key.Value().GetString((_pc_sz) sub_key_path, Get_reg_router().Mru().Name());
		if (the_key.Error()) // the error is intentionally ignored;
			continue;

		CMruItem mru_item; mru_item << stamp << html_path;
		if (false == mru_item.Is_valid())
			continue;

		try {
			this->m_items.insert(::std::make_pair(mru_item.Timestamp().Get(), mru_item));
		}
		catch (const ::std::bad_alloc&) { this->m_error <<__e_no_memory; break; }

		the_key.Close();
	}

	return this->Error();
}

err_code CMruList::Save (void) {
	this->m_error <<__METHOD__<<__s_ok;


	return this->Error();
}

#pragma endregion
#pragma region cls::CTimestamp{}

CTimestamp::CTimestamp (const qword_t _q_value) : m_value(_q_value) {}
CTimestamp::CTimestamp (const CTimestamp& _src) : CTimestamp() { *this = _src; }
CTimestamp::CTimestamp (CTimestamp&& _victim) : CTimestamp() { *this = _victim; }
CTimestamp::CTimestamp (_pc_sz _p_value) : CTimestamp() { *this << _p_value; }

qword_t CTimestamp::Current (void) {

	FILETIME ft = {0};
#if (0)
	::GetSystemTimeAsFileTime(&ft);        // https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemtimeasfiletime ;
#else
	::GetSystemTimePreciseAsFileTime(&ft); // https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemtimepreciseasfiletime ;
#endif
	ULARGE_INTEGER uli = {0};
	uli.LowPart   = ft.dwLowDateTime;
	uli.HighPart  = ft.dwHighDateTime;
	this->m_value = uli.QuadPart;
	return this->Get();
}

qword_t CTimestamp::Get (void) const { return this->m_value; }
bool    CTimestamp::Set (const qword_t _q_value) {
	const bool b_changed = _q_value != this->Get(); if (b_changed) this->m_value = _q_value; return b_changed;
}

bool    CTimestamp::Is_hex (_pc_sz _p_value) {
	CString cs_value(_p_value);
	cs_value.Trim();
	cs_value.MakeLower();
	return _T("0x") == cs_value.Left(2);
}

bool    CTimestamp::Is_valid (_pc_sz _p_value) {
	CString cs_value(_p_value);
	cs_value.Trim();
	cs_value.MakeLower();
	const uint32_t u_req_len = CTimestamp::Is_hex((_pc_sz) cs_value) ? 18 : 16;
	return u_req_len == static_cast<uint32_t>(cs_value.GetLength());
}
bool    CTimestamp::Is_valid (void) const { return CTimestamp::Is_valid(this->Get()); }
bool    CTimestamp::Is_valid (const qword_t _q_value) {
	return _q_value != 0 && 0x7FFFFFFFFFFFFFFFULL < _q_value;
}

CString CTimestamp::To_str (const bool _b_hex) const { return CTimestamp::To_str(this->Get(), _b_hex); }
CString CTimestamp::To_str (const qword_t _q_value, const bool _b_hex) {
	_q_value; _b_hex;
	CString cs_out = TString().Format(_b_hex ? _T("%016llX") : _T("%ULL"), _q_value);
	cs_out.MakeLower();

	if (cs_out.IsEmpty() == false && _T("0x") == cs_out.Left(2))
		cs_out.Delete(2);

	return cs_out;
}

bool    CTimestamp::To_qword (_pc_sz _in_value) {
	return CTimestamp::To_qword(_in_value, this->m_value);
}

bool    CTimestamp::To_qword (const _pc_sz _in_value, qword_t& _out_value) {
	_in_value; _out_value;

	CString cs_in(_in_value);
	if (cs_in.IsEmpty())
		return false;
	cs_in.MakeLower();
	if (_T("0x") == cs_in.Left(2))
		cs_in.Delete(2);

	errno = 0;
    wchar_t* endPtr = nullptr;
    _out_value = ::_wcstoui64((_pc_sz) cs_in, &endPtr, 0xf);

	return (errno != ERANGE && *endPtr == _T('\0'));
}

CTimestamp& CTimestamp::operator = (const CTimestamp& _src) { *this << _src.Get(); return *this; }
CTimestamp& CTimestamp::operator = (CTimestamp&& _victim) { *this = (const CTimestamp&)_victim; _victim.m_value = 0ULL; return *this; }
CTimestamp& CTimestamp::operator <<(const qword_t _q_value) { this->Set(_q_value); return *this; }
CTimestamp& CTimestamp::operator <<(_pc_sz _p_value) { this->To_qword(_p_value); return *this; }

CTimestamp::operator const qword_t (void) const { return this->Get(); }

#pragma endregion