/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Apr-2012 at 07:53:06pm, GMT+3, Rostov-on-Don, Sunday;
	This is Pulsepay server application generic command line interface implementation file.
	-----------------------------------------------------------------------------[oDesk.com]
	Adopted to Platinum Clocking project on 19-Mar-2014 at 8:24:43am, GMT+4, Taganrog, Wednesday;
	Adopted to BotRevolt project on 21-Aug-2014 at 6:07:39am, GMT+4, Taganrog, Thursday;
	-----------------------------------------------------------------------------[Upwork.com]
	Adopted to FG (thefileguardian.com) project on 11-Jun-2016 at 4:57:52p, GMT+7, Phuket, Rawai, Saturday;
	Adopted to sound-bin-trans project on 5-Apr-2019 at 11:55:19a, UTC+7, Phuket, Rawai, Thursday;
*/
#include "console.cmd.ln.h"

using namespace ::shared::console;

#pragma region cls::CCmdLine{}

CCmdLine:: CCmdLine (void)
{
	this->m_error >> __CLASS__ << __METHOD__<<__s_ok;
	// https://learn.microsoft.com/en-us/windows/win32/api/processenv/nf-processenv-getcommandlinea ;
	CString cs_cmd_line = ::GetCommandLine();
	CString cs_key;
	CString cs_arg;

	INT n_count = 0;
	bool bKey   = false;
	// https://learn.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-commandlinetoargvw ;
	wchar_t** pCmdArgs = ::CommandLineToArgvW(cs_cmd_line.GetString(), &n_count);
	if (!pCmdArgs || 0 == n_count) {
		if (!pCmdArgs)
			this->m_error.Last();
		else
			this->m_error << __s_false = _T("No arguments");
		goto __end_of_story__;
	}
	
	m_module_path = pCmdArgs[0];

	for (INT i_ = 1; i_ < n_count; i_+= 1) {
		CString cs_val = pCmdArgs[i_];
		bKey = (/*0 == cs_val.Find(_T("-")) // negative numbers are eaten when minus appears, quotes around value must be considered;
				||*/ 0 == cs_val.Find(_T("/")));

		if (bKey) {
			if (cs_key.IsEmpty() == false) // the previous key is not saved yet;
				m_args.insert(::std::make_pair(cs_key, cs_arg));

			cs_key = pCmdArgs[i_]; cs_key.Replace(_T("-"), _T("")); cs_key.Replace(_T("/"), _T(""));
			cs_arg = _T("");
		}
		else {
			cs_arg+= pCmdArgs[i_];
		}

		const bool bLast = (i_ == n_count - 1);
		if (bLast && cs_key.IsEmpty() == false) {
			try {
				m_args.insert(::std::make_pair(cs_key, cs_arg));
			} catch (const ::std::bad_alloc&){ this->m_error << __e_no_memory; }
		}
	}

__end_of_story__:
	if (nullptr != pCmdArgs) {
		::LocalFree(pCmdArgs); pCmdArgs = nullptr;
	}
}

CCmdLine::~CCmdLine(void) { this->Clear(); }

err_code CCmdLine::Append(_pc_sz _p_sz_name, _pc_sz _p_sz_value) {
	_p_sz_name; _p_sz_value;
	this->m_error << __METHOD__ << __s_ok;

	try {
		m_args.insert(::std::make_pair(
			CString(_p_sz_name), CString(_p_sz_value)
		));
	}
	catch (const ::std::bad_alloc&){
		this->m_error << __e_no_memory;
	}
	return this->Error();
}
err_code CCmdLine::Append(_pc_sz _p_sz_name, long _l_value) {
      return this->Append(_p_sz_name, TString().Long(_l_value));
}

CString  CCmdLine::Arg   (_pc_sz _p_sz_name) const {
	_p_sz_name;
	this->m_error << __METHOD__ << __s_ok;

	TCmdLineArgs::const_iterator it_ = m_args.find(CString(_p_sz_name));

	if (it_ == m_args.end()) {
		this->m_error << (err_code) TErrCodes::eData::eNotFound;
		return CString();
	}
	else
		return it_->second;
}

long     CCmdLine::Arg   (_pc_sz _p_sz_name, const long _def_val) const {
	_p_sz_name; _def_val;
	this->m_error << __METHOD__ << __s_ok;

	TCmdLineArgs::const_iterator it_ = m_args.find(CString(_p_sz_name));

	if (it_ == m_args.end()) {
		this->m_error << (err_code) TErrCodes::eData::eNotFound;
		return _def_val;
	}
	else
		return ::_tstol(it_->second);
}

TCmdLineArgs  CCmdLine::Args  (void) const { return m_args; }
void          CCmdLine::Clear (void)       { if (m_args.empty() == false) m_args.clear(); }
uint16_t      CCmdLine::Count (void)const  { return static_cast<uint16_t>(m_args.size()); }
bool          CCmdLine::Has   (_pc_sz pArgName) const
{
	TCmdLineArgs::const_iterator it__ = m_args.find(CString(pArgName));
	return (it__ != m_args.end());
}

TError&  CCmdLine::Error(void) const { return this->m_error; }

CString  CCmdLine::Path (void) const { return m_module_path; }

CString  CCmdLine::ToString(_pc_sz _lp_sz_sep) const {
	_lp_sz_sep;

	static _pc_sz lp_sz_pat = _T("{%s=%s}");

	CString cs_pat ;
	CString cs_args;

	if (m_args.empty())
		return (cs_args = _T("#no_args;"));
#if (0)
	for (TCmdLineArgs::const_iterator it_ = m_args.begin(); it_ != m_args.end(); ++it_)
	{
		cs_pat.Format(
				lp_sz_pat, (_pc_sz)it_->first, (_pc_sz)it_->second
			);
		cs_args += cs_pat;
		cs_args +=(nullptr == _lp_sz_sep ? _T("; ") : _lp_sz_sep);
	}
#else
	size_t n_count = this->m_args.size();
	for (TCmdLineArgs::const_iterator it_ = m_args.begin(); it_ != m_args.end(); ++it_) {

		cs_pat.Format(
			lp_sz_pat, (_pc_sz)it_->first, (_pc_sz)it_->second
		);
		cs_args += cs_pat;

		if (--n_count) {
			cs_args +=(nullptr == _lp_sz_sep ? _T("; ") : _lp_sz_sep);
		}
	}
#endif
	return cs_args;
}

#if defined (_DEBUG) || defined(TRUE)

CString  CCmdLine::Print (void) const {

	static _pc_sz lp_sz_pat = _T("cls::[%s]>>{args=%s;count=%u}");

	CString cs_out;
	cs_out.Format(lp_sz_pat, (_pc_sz)__CLASS__, (_pc_sz)this->ToString(), this->Count());
	return  cs_out;
}
#endif

CCmdLine::operator _pc_sz (void) const { return this->ToString(); }

bool CCmdLine::operator==(_pc_sz pszArgName) const { return this->Has(pszArgName); }

#pragma endregion
#pragma region cls::CArg

CArg:: CArg (void) : m_type(0) {}
CArg:: CArg (const CArg& _arg) : CArg() { *this = _arg; }
CArg:: CArg (const _word _w_res_name, const _word _w_res_verb, const dword _dw_type) : CArg() {
	this->Name(_w_res_name); 
	this->Verb(_w_res_verb);
	this->Type(_dw_type);
}
CArg:: CArg (_pc_sz _lp_sz_name, _pc_sz _lp_sz_verb, const dword _dw_type) : m_name(_lp_sz_name), m_verb(_lp_sz_verb), m_type(_dw_type) {}
CArg::~CArg (void) {}

bool     CArg::Is (void) const { return (m_name.IsEmpty() == false); }

_pc_sz   CArg::Name (void) const { return  m_name.GetString(); }
err_code CArg::Name (const _word _w_res_id) {
	if (0 == _w_res_id)
		return __e_inv_arg;

	m_name.LoadStringW(_w_res_id);
	return (m_name.IsEmpty() ? TErrCodes::eResource::eNotPresent : __s_ok);
}

err_code CArg::Name (_pc_sz _lp_sz_name) {
	_lp_sz_name;
	if (nullptr == _lp_sz_name || 0 == ::_tcslen(_lp_sz_name))
		return __e_inv_arg;

	m_name = _lp_sz_name;
	return __s_ok;
}

dword    CArg::Type (void) const { return m_type; }
bool     CArg::Type (const dword _type) { const bool b_changed = m_type != _type; m_type = _type; return b_changed; }

_pc_sz   CArg::Verb (void) const { return m_verb.GetString(); }
err_code CArg::Verb (const _word _w_res_id) {
	if (0 == _w_res_id)
		return __e_inv_arg;

	m_verb.LoadStringW(_w_res_id);
	return (m_verb.IsEmpty() ? TErrCodes::eResource::eNotPresent : __s_ok);
}

err_code CArg::Verb (_pc_sz _lp_sz_desc ) {
	_lp_sz_desc;
	if (nullptr == _lp_sz_desc || 0 == ::_tcslen(_lp_sz_desc))
		return __e_inv_arg;

	m_verb = _lp_sz_desc;
	return __s_ok;
}

CArg& CArg::operator = (const CArg& _ref) {
	this->Name(_ref.Name());
	this->Verb(_ref.Verb());
	this->Type(_ref.Type());
	return *this;
}

bool CArg::operator == (const CArg& _ref) const { return (this->Type() == _ref.Type()); }
bool CArg::operator == (_pc_sz _lp_sz_name) const {
	if (nullptr == _lp_sz_name || 0 == ::_tcslen(_lp_sz_name))
		return false;
	else
		return (0 == m_name.CompareNoCase(_lp_sz_name));
}

#pragma endregion