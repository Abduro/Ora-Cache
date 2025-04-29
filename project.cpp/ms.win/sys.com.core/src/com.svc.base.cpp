/*
	Created by Tech_dog (ebontrop@gmail.com) on 2-May-2012 at 9:07:10am, GMT+3, Rostov-on-Don, Wednesday;
	This is PulsePay project COM libraries auto-initializer interface implementation files; [one of the first projects that is gained through odesk.com]
	-----------------------------------------------------------------------------[this section shows all significant projects gained through upwork.com]
	Adopted to Platinum project on 19-Mar-2014 at 10:52:48am, GMT+4, Taganrog, Wednesday;
	Adopted to File Guardian project on 11-Jul-2018 at 10:29:17a, UTC+7, Phuket, Rawai, Wednesday;
	Adopted to FakeGPS driver project on 13-Dec-2019 at 10:18:13a, UTC+7, Novosibirsk, Friday;
	-----------------------------------------------------------------------------[this volunteer project, but it's very important]
	Adopted to Stroke Over project on 17-Aug-2024 at 07:24:38.0645698, UTC+4, Batumi, Saturday;
*/
#include "com.svc.base.h"
#include "com.sec.base.h"

using namespace shared::sys_core::com;

/////////////////////////////////////////////////////////////////////////////

CCoMode:: CCoMode (void) : m_code(0), m_alias(_T("$undef")), m_desc(_T("$not_set")) {}
CCoMode:: CCoMode (const CCoMode& _src) : CCoMode() { *this = _src; }
CCoMode:: CCoMode (CCoMode&& _victim) : CCoMode() { *this = _victim; }
CCoMode:: CCoMode (dword _code, _pc_sz _p_alias, _pc_sz _p_desc) : CCoMode() { *this >> _p_alias << _code << _p_desc; }
CCoMode::~CCoMode (void) {}

/////////////////////////////////////////////////////////////////////////////

_pc_sz CCoMode::Alias (void) const { return this->m_alias.GetString(); }
bool   CCoMode::Alias (_pc_sz _p_alias) {
	_p_alias;
	const bool b_changed = !!this->m_alias.Compare(_p_alias);
	if (b_changed)
		this->m_alias = _p_alias;

	return b_changed;
}

dword  CCoMode::Code (void) const { return this->m_code; }
bool   CCoMode::Code (const dword _code) {
	_code;
	const
	bool b_changed = this->Code() != _code ;
	if ( b_changed )
		this->m_code = _code;

	return b_changed;
}

_pc_sz CCoMode::Desc (void) const { return this->m_desc.GetString(); }
bool   CCoMode::Desc (_pc_sz _p_desc) {
	_p_desc;
	const bool b_changed = !!this->m_desc.Compare(_p_desc);
	if (b_changed)
		this->m_desc = _p_desc;

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

void    CCoMode::Clear(void) { *this >> _T("$undef") << (dword)0 << _T("$not_set"); }
#if defined(_DEBUG)
CString CCoMode::Print(const e_print e_opt) const {
	static _pc_sz p_sz_pat_a = _T("cls::[%s]>>{%s:code=%d(0x%x);desc='%s'}");
	static _pc_sz p_sz_pat_r = _T("{%s=%d(0x%x):%s}");

	CString cs_desc = this->Desc();
	if (cs_desc.IsEmpty())
		cs_desc = _T("$not_set");

	CString cs_out;
	if (e_print::e_all == e_opt) cs_out.Format(p_sz_pat_a, (_pc_sz)__CLASS__, 
	                                                       this->Alias(), this->Code(), this->Code(), (_pc_sz)cs_desc);
	if (e_print::e_req == e_opt) cs_out.Format(p_sz_pat_r, this->Alias(), this->Code(), this->Code(), (_pc_sz)cs_desc);
	return  cs_out;
}
#endif
void    CCoMode::Set  (dword _code, _pc_sz _p_alias, _pc_sz _p_desc) { *this >> _p_alias << _code << _p_desc; }

/////////////////////////////////////////////////////////////////////////////

CCoMode& CCoMode::operator = (const CCoMode& _src) { *this >> _src.Alias() << _src.Code() << _src.Desc(); return *this;}
CCoMode& CCoMode::operator = (CCoMode&& _victim) { *this = _victim; _victim.Clear(); return *this; }
CCoMode& CCoMode::operator >>(_pc_sz _p_alias) { this->Alias(_p_alias); return *this; }
CCoMode& CCoMode::operator <<(dword _code)     { this->Code(_code); return *this; }
CCoMode& CCoMode::operator <<(_pc_sz _p_desc)  { this->Desc(_p_desc); return *this; }

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace sys_core { namespace com { namespace _impl {

	struct raw_mode {
		dword  _code ;
		_pc_sz _alias;
		_pc_sz _desc ;
	};
	static
	raw_mode modes[] = {
		{ TModeAccept::e_apart   , _T("#APART" ), _T("Apartment-threaded object concurrency;") }, // #0;
		{ TModeAccept::e_default , _T("#THREAD"), _T("Multithreaded object concurrency;")      }, // #1;
		{ TModeAccept::e_threaded, _T("#THREAD"), _T("Multithreaded object concurrency;")      }, // #2;
		{ TModeAccept::e_ole_1   , _T("#OLE_1" ), _T("Disabling of DDE for OLE1 support;")     }, // #3;
		{ TModeAccept::e_speed   , _T("#SPEED" ), _T("Increasing memory usage for fast performance;")}, // #4;
		{ TModeAccept::e_the_fake, _T("#FAKE"  ), _T("Fake concurrent mode<%u>") }, // #5;
	};

}}}}
using namespace shared::sys_core::com::_impl;
/////////////////////////////////////////////////////////////////////////////

CCoMode_enum:: CCoMode_enum (void) { this->Set(); }
CCoMode_enum::~CCoMode_enum (void) {}

/////////////////////////////////////////////////////////////////////////////

bool     CCoMode_enum::Has  (dword _code) const { return (this->Get().end() != this->Get().find(_code)); }
const
TCoMode& CCoMode_enum::Find (dword _code) const {
	_code;
	TRawModes::const_iterator it_found = this->Get().find(_code);

	if (this->Get().end() == it_found) {
		static CCoMode fake_;

		fake_ >> _T("#FAKE") << TString().Format(_T("Fake concurrent mode<%u>"), _code) << _code;

		return fake_;
	}
	else
		return it_found->second;
}

const
TRawModes& CCoMode_enum::Get (void) const { return this->m_modes; }
err_code   CCoMode_enum::Set (void) {

	err_code n_result = TErrCodes::no_error;

	if (this->m_modes.empty() == false)
		this->m_modes.clear();
	// https://learn.microsoft.com/en-us/windows/win32/api/objbase/ne-objbase-coinit ;
	try {
		this->m_modes.insert(::std::make_pair(modes[0]._code, CCoMode(modes[0]._code, modes[0]._alias, modes[0]._desc)));
		this->m_modes.insert(::std::make_pair(modes[1]._code, CCoMode(modes[1]._code, modes[1]._alias, modes[1]._desc)));
		this->m_modes.insert(::std::make_pair(modes[3]._code, CCoMode(modes[3]._code, modes[3]._alias, modes[3]._desc)));
		this->m_modes.insert(::std::make_pair(modes[4]._code, CCoMode(modes[4]._code, modes[4]._alias, modes[4]._desc)));
	}
	catch (const ::std::bad_alloc&) {
		n_result = __e_no_memory;
	}

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
CString   CCoMode_enum::Print (_pc_sz _pfx, _pc_sz _sfx) const {
	_pfx;_sfx;

	static _pc_sz p_sz_pat = _T("cls::[%s]%s%s");

	CString cs_out;
	CString cs_modes;

	for (TRawModes::const_iterator it_ = this->Get().begin(); it_ != this->Get().end(); ++it_) {

		cs_modes += _pfx;
		cs_modes += it_->second.Print(e_print::e_req);
		cs_modes += _sfx;

	}

	cs_out.Format(p_sz_pat, (_pc_sz)__CLASS__, _sfx, (_pc_sz)cs_modes);

	return  cs_out;
} 
#endif

/////////////////////////////////////////////////////////////////////////////
CCoMode_enum& CCoMode_enum::Ref (void) {
	static CCoMode_enum the_fake;
	return the_fake;
}
/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace sys_core { namespace com { namespace _impl {

	static _pc_sz _cfg_to_str(TCo_Cfg _e_cfg) {
			_e_cfg;
			static CString cs_cfg;
			
			if (TCoModelCfg::e_fast == _e_cfg) { cs_cfg = _T("$e_fast"); }
			if (TCoModelCfg::e_gui  == _e_cfg) { cs_cfg = _T("$e_gui "); }
			if (TCoModelCfg::e_none == _e_cfg) { cs_cfg = _T("$e_none"); }
			if (TCoModelCfg::e_task == _e_cfg) { cs_cfg = _T("$e_task"); }

			return (_pc_sz)cs_cfg;
	}

}}}}
using namespace shared::sys_core::com::_impl;
/////////////////////////////////////////////////////////////////////////////

CCoModel:: CCoModel (_cfg_4 _cfg) : m_cfg(_cfg) {
	_cfg;
	err_code n_result = TErrCodes::no_error;
	TRawModes& accept = this->Accepted();
	// https://learn.microsoft.com/en-us/windows/win32/api/objbase/ne-objbase-coinit ;
	try {

		if (_cfg_4::e_fast == _cfg) {
			accept.insert(::std::make_pair(modes[1]._code, CCoMode(modes[1]._code, modes[1]._alias, modes[1]._desc)));
			accept.insert(::std::make_pair(modes[3]._code, CCoMode(modes[3]._code, modes[3]._alias, modes[3]._desc)));
			accept.insert(::std::make_pair(modes[4]._code, CCoMode(modes[4]._code, modes[4]._alias, modes[4]._desc)));
		}
		if (_cfg_4::e_gui  == _cfg) { accept.insert(::std::make_pair(modes[0]._code, CCoMode(modes[0]._code, modes[0]._alias, modes[0]._desc))); }
		if (_cfg_4::e_none == _cfg) { accept.insert(::std::make_pair(modes[1]._code, CCoMode(modes[1]._code, modes[1]._alias, modes[1]._desc))); }
		if (_cfg_4::e_task == _cfg) {
			accept.insert(
				::std::make_pair(modes[1]._code, CCoMode(modes[1]._code, modes[1]._alias, modes[1]._desc))
			);
		}
	}
	catch (const ::std::bad_alloc&) {
		n_result = __e_no_memory;  // it is very impossible to get exception from above piece of code, but for the sake of stability it must be catched ;
	}
}
CCoModel:: CCoModel (const CCoModel& _src) : CCoModel() { *this = _src; }
CCoModel::~CCoModel (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TRawModes& CCoModel::Accepted(void) const { return this->m_accepted; }
TRawModes& CCoModel::Accepted(void)       { return this->m_accepted; }
dword      CCoModel::CoInit  (void) const {
	dword n_init = 0;
	for (TRawModes::const_iterator it_ = this->Accepted().begin(); it_ != this->Accepted().end(); it_++)
		n_init |= it_->second.Code();
	return n_init;
}

TCo_Cfg    CCoModel::Cfg (void) const { return this->m_cfg; }

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString    CCoModel::Print (void) const {

	static _pc_sz p_sz_pat_def = _T("cls::[%s]>>{default-mode:%s}");
	static _pc_sz p_sz_pat_yes = _T("cls::[%s]>>{cfg=%u(%s);co-init-flag=%02u(0x04%x);modes:%s}");

	CString cs_out;
	CString cs_accepted;

	for (TRawModes::const_iterator it_ = this->Accepted().begin(); it_ != this->Accepted().end(); ++it_) {

		if (cs_accepted.IsEmpty() == false)
			cs_accepted += _T("|");
		cs_accepted += it_->second.Alias();

	}
	if (this->Accepted().empty()) { // this means no element is in the map of modes, i.e. default mode is applied (code = 0);
		cs_out.Format(p_sz_pat_def, (_pc_sz)__CLASS__, (_pc_sz)CCoMode_enum::Ref().Find(TModeAccept::e_default).Print(::e_print::e_all));
	}
	else {
		const dword co_init = this->CoInit();
		cs_out.Format(p_sz_pat_yes, (_pc_sz)__CLASS__, this->Cfg(), _cfg_to_str(this->Cfg()), co_init, co_init, (_pc_sz)cs_accepted);
	}
	
	return  cs_out;
} 
#endif
/////////////////////////////////////////////////////////////////////////////

CCoModel&  CCoModel::operator = (const CCoModel& _src) { this->Accepted() = _src.Accepted(); return *this; }

CCoModel::operator dword (void) const { return this->CoInit(); }

/////////////////////////////////////////////////////////////////////////////

CCoGuard:: CCoGuard (bool _b_dbg) : m_auto(!_b_dbg), m_model(TCo_Cfg::e_none) {
	m_error >> __CLASS__ << __METHOD__ << OLE_E_BLANK;
	m_error = _T("The object in debug mode: no auto init invoked;");
}
CCoGuard:: CCoGuard (TCo_Cfg _e_cfg) : m_auto(true), m_model(_e_cfg) { m_error >> __CLASS__ << __METHOD__ << OLE_E_BLANK; this->OnCreate(); }
CCoGuard::~CCoGuard (void) { if (this->m_auto) this->OnDestroy(); }

/////////////////////////////////////////////////////////////////////////////

TError&   CCoGuard::Error (void) const { return ( this->m_error); }
bool      CCoGuard::Is    (void) const { return (!this->m_error); }
const
TCoModel& CCoGuard::Model (void) const { return this->m_model; }

#if defined(_DEBUG)
CString   CCoGuard::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz p_sz_pat_all = _T("cls::[%s]>>{model=%s;err=%s;valid=%s}"); // the pattern for e_all option;
	static _pc_sz p_sz_pat_req = _T("cls::[%s]>>{model=%s;valid=%s}");                 // the pattern for e_req option; e_req == e_required;

	CString cs_out;

	if (e_print::e_all == e_opt) {
		cs_out.Format(p_sz_pat_all, (_pc_sz)__CLASS__, (_pc_sz)this->Model().Print(), (_pc_sz)this->Error().Print(), (_pc_sz)TString(this->Is()));
	}
	if (e_print::e_req == e_opt) {
		cs_out.Format(p_sz_pat_req, (_pc_sz)__CLASS__, (_pc_sz)this->Model().Print(), (_pc_sz)TString(this->Is()));
	}

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

err_code CCoGuard::OnCreate (void) {

	if (this->Is())
		return TErrCodes::eObject::eInited;

	this->m_error << __METHOD__ << TErrCodes::no_error;

	// https://learn.microsoft.com/en-us/windows/win32/api/objbase/nf-objbase-coinitialize ;
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-coinitializeex ;
	// https://learn.microsoft.com/en-us/windows/win32/com/processes--threads--and-apartments ;
	this->m_error = ::CoInitializeEx(0, this->Model().CoInit());
	return this->Error();
}

err_code CCoGuard::OnDestroy(void) {

	if (this->Is() == false)
		return OLE_E_BLANK;

	this->m_error << __METHOD__ << TErrCodes::no_error;
	
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-couninitialize ;
	::CoUninitialize(); // nobody cares about the result returned by invocation of this method;

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CCoGuard::operator const bool (void) const { return this->Is(); }