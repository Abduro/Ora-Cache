/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Apr-2012 at 07:53:06pm, GMT+3, Rostov-on-Don, Sunday;
	This is Pulsepay server application generic command line interface implementation file.
	-----------------------------------------------------------------------------
	Adopted to Platinum Clocking project on 19-Mar-2014 at 8:24:43am, GMT+4, Taganrog, Wednesday;
	Adopted to BotRevolt project on 21-Aug-2014 at 6:07:39am, GMT+4, Taganrog, Thursday;
	Adopted to FG (thefileguardian.com) project on 11-Jun-2016 at 4:57:52p, GMT+7, Phuket, Rawai, Saturday;
	Adopted to sound-bin-trans project on 5-Apr-2019 at 11:55:19a, UTC+7, Phuket, Rawai, Thursday;
*/
#include "ms.con.cmd.ln.h"

using namespace ebo::boo::test;

/////////////////////////////////////////////////////////////////////////////

CCommandLine:: CCommandLine (void)
{
	m_error >> __CLASS__ << __METHOD__;
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
			m_error.Last();
		else
			m_error << S_FALSE = _T("No arguments");
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
			} catch (const ::std::bad_alloc&){ m_error << E_OUTOFMEMORY; }
		}
	}

__end_of_story__:
	if (NULL != pCmdArgs) {
		::LocalFree(pCmdArgs); pCmdArgs = NULL;
	}
}

CCommandLine::~CCommandLine(void) { this->Clear(); }

/////////////////////////////////////////////////////////////////////////////

err_code  CCommandLine::Append(_pc_sz _p_sz_name, _pc_sz _p_sz_value) {
	_p_sz_name; _p_sz_value;
	m_error << __METHOD__ << TErrCodes::no_error;

	try {
		m_args.insert(::std::make_pair(
			CString(_p_sz_name), CString(_p_sz_value)
		));
	}
	catch (const ::std::bad_alloc&){
		m_error << E_OUTOFMEMORY;
	}
	return this->Error();
}
err_code CCommandLine::Append(_pc_sz _p_sz_name, long _l_value) {
	return this->Append(_p_sz_name, TString().Long(_l_value));
}

CString   CCommandLine::Arg   (_pc_sz _p_sz_name) const {
	_p_sz_name;
	m_error << __METHOD__ << TErrCodes::no_error;

	TCmdLineArgs::const_iterator it_ = m_args.find(CString(_p_sz_name));

	if (it_ == m_args.end()) {
		m_error << TErrCodes::eData::eNotFound;
		return CString();
	}
	else
		return it_->second;
}

LONG      CCommandLine::Arg   (_pc_sz _p_sz_name, const LONG _def_val) const {
	_p_sz_name; _def_val;
	m_error << __METHOD__ << TErrCodes::no_error;

	TCmdLineArgs::const_iterator it_ = m_args.find(CString(_p_sz_name));

	if (it_ == m_args.end()) {
		m_error << TErrCodes::eData::eNotFound;
		return _def_val;
	}
	else
		return ::_tstol(it_->second);
}

TCmdLineArgs  CCommandLine::Args  (void) const { return m_args; }
VOID          CCommandLine::Clear (void)       { if (m_args.empty() == false) m_args.clear(); }
uint16_t      CCommandLine::Count (void)const  { return static_cast<uint16_t>(m_args.size()); }
bool          CCommandLine::Has   (_pc_sz pArgName) const
{
	TCmdLineArgs::const_iterator it__ = m_args.find(CString(pArgName));
	return (it__ != m_args.end());
}

TError&   CCommandLine::Error(void) const { return this->m_error; }

CString   CCommandLine::Path (void) const { return m_module_path; }

/////////////////////////////////////////////////////////////////////////////

CString   CCommandLine::ToString(_pc_sz _lp_sz_sep) const {
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
		cs_args +=(NULL == _lp_sz_sep ? _T("; ") : _lp_sz_sep);
	}
#else
	size_t n_count = this->m_args.size();
	for (TCmdLineArgs::const_iterator it_ = m_args.begin(); it_ != m_args.end(); ++it_) {

		cs_pat.Format(
			lp_sz_pat, (_pc_sz)it_->first, (_pc_sz)it_->second
		);
		cs_args += cs_pat;

		if (--n_count) {
			cs_args +=(NULL == _lp_sz_sep ? _T("; ") : _lp_sz_sep);
		}
	}
#endif
	return cs_args;
}
#if defined (_DEBUG)
CString   CCommandLine::Print (void) const {

	static _pc_sz lp_sz_pat = _T("cls::[%s]>>{args=%s;count=%u}");

	CString cs_out;
	cs_out.Format(lp_sz_pat, (_pc_sz)__CLASS__, (_pc_sz)this->ToString(), this->Count());
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CCommandLine::operator _pc_sz (void) const { return this->ToString(); }

/////////////////////////////////////////////////////////////////////////////

bool CCommandLine::operator==(_pc_sz pszArgName) const { return this->Has(pszArgName); }

/////////////////////////////////////////////////////////////////////////////
#if (0)
CArgument:: CArgument (void) : m_type(0) {}
CArgument:: CArgument (const CArgument& _arg) : CArgument() { *this = _arg; }
CArgument:: CArgument (const WORD _w_res_name, const WORD _w_res_verb, const DWORD _dw_type) : CArgument() {
	this->Name(_w_res_name); 
	this->Verb(_w_res_verb);
	this->Type(_dw_type);
}
CArgument:: CArgument (LPCWSTR _lp_sz_name, LPCWSTR _lp_sz_verb, const DWORD _dw_type) : m_name(_lp_sz_name), m_verb(_lp_sz_verb), m_type(_dw_type) {}
CArgument::~CArgument (void) {}

/////////////////////////////////////////////////////////////////////////////

bool      CArgument::Is  (void) const { return (m_name.IsEmpty() == false); }
LPCWSTR   CArgument::Name(void) const { return  m_name.GetString(); }
HRESULT   CArgument::Name(const WORD _w_res_id) {
	if (0 == _w_res_id)
		return E_INVALIDARG;

	m_name.LoadStringW(_w_res_id);
	return (m_name.IsEmpty() ? __DwordToHresult(ERROR_RESOURCE_NOT_PRESENT) : S_OK);
}
HRESULT   CArgument::Name(LPCWSTR _lp_sz_name ) {
	if (NULL == _lp_sz_name || 0 == ::wcslen(_lp_sz_name))
		return E_INVALIDARG;

	m_name = _lp_sz_name;
	return S_OK;
}
DWORD     CArgument::Type(void) const { return m_type; }
bool      CArgument::Type(const DWORD _type) { const bool b_changed = m_type != _type; m_type = _type; return b_changed; }
LPCWSTR   CArgument::Verb(void) const { return m_verb.GetString(); }
HRESULT   CArgument::Verb(const WORD _w_res_id) {
	if (0 == _w_res_id)
		return E_INVALIDARG;

	m_verb.LoadStringW(_w_res_id);
	return (m_verb.IsEmpty() ? __DwordToHresult(ERROR_RESOURCE_NOT_PRESENT) : S_OK);
}
HRESULT   CArgument::Verb(LPCWSTR _lp_sz_desc ) {
	if (NULL == _lp_sz_desc || 0 == ::wcslen(_lp_sz_desc))
		return E_INVALIDARG;

	m_verb = _lp_sz_desc;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////

CArgument& CArgument::operator = (const CArgument& _ref) {
	this->Name(_ref.Name());
	this->Verb(_ref.Verb());
	this->Type(_ref.Type());
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

bool CArgument::operator == (const CArgument& _ref) const { return (this->Type() == _ref.Type()); }
bool CArgument::operator == (LPCWSTR _lp_sz_name) const {
	if (NULL == _lp_sz_name || 0 == ::_tcslen(_lp_sz_name))
		return false;
	else
		return (0 == m_name.CompareNoCase(_lp_sz_name));
}
#endif