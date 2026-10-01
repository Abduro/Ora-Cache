/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Apr-2017 at 11:05:46p, GMT+7, Phuket, Rawai, Saturday;
	This is Ebo Pack shared UIX Web Browser library common definition implementation file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 28-May-2018 at 9:27:08p, UTC+7, Phuket, Rawai, Monday;
*/
#include "shared.web.defs.h"

using namespace ex_ui::web;

#include "shared.gen.app.obj.h"
#include "shared.reg.hive.h"

using namespace shared::user32;
using namespace shared::registry;

#include "shared.fs.defs.h"

using namespace shared::ntfs;

/////////////////////////////////////////////////////////////////////////////

CUrlLocateType:: CUrlLocateType(LPCWSTR _lp_sz_pat) : m_type(CUrlLocateType::eHostExecutable) { m_error >> __CLASS__ << __METHOD__;
	this->Type(_lp_sz_pat);
}
CUrlLocateType:: CUrlLocateType(const _e _type) : m_type(_type) { m_error >> __CLASS__ << __METHOD__; }
CUrlLocateType::~CUrlLocateType(void) {}

/////////////////////////////////////////////////////////////////////////////

TErrorRef   CUrlLocateType::Error(void) const  { return m_error; }
const bool  CUrlLocateType::IsCmd(void) const  { return (_e::eInterCommand ==  this->Type()); }
const bool  CUrlLocateType::IsExt(void) const  { return (_e::eExternalLink ==  this->Type()); }
const bool  CUrlLocateType::IsOut(void) const  { return (_e::eOuterBrowser ==  this->Type()); }
const CUrlLocateType::_e
            CUrlLocateType::Type (void) const  { return m_type ; }
VOID        CUrlLocateType::Type (const _e _v) { m_type = _v   ; }
HRESULT     CUrlLocateType::Type (LPCWSTR _lp_sz_pat) {
	m_error << __METHOD__ << S_OK;

	CStringW cs_pat(_lp_sz_pat);

	if (cs_pat.IsEmpty()) return (m_error << E_INVALIDARG);
	if (cs_pat.GetLength() < CUrlLocateType::MinLen()) return (m_error = (DWORD)ERROR_INVALID_DATA);

	m_type = CUrlLocateType::ToType(_lp_sz_pat);

	return m_error;
}

/////////////////////////////////////////////////////////////////////////////

CUrlLocateType& CUrlLocateType::operator << (LPCWSTR _lp_sz_pat) { this->Type(_lp_sz_pat); return *this; }
CUrlLocateType& CUrlLocateType::operator << (const _e _type)     { this->Type(_type); return *this; }

CUrlLocateType::operator TErrorRef  (void)   const { return this->Error(); }
CUrlLocateType::operator const _e   (void)   const { return this->Type (); }
CUrlLocateType::operator const bool (void)   const { return this->Error() == false; }

/////////////////////////////////////////////////////////////////////////////

const  INT CUrlLocateType::MinLen(void) {
	static const INT n_min_len = 7; // equals to length of possible prefix plus one character for URL itself;
	return n_min_len;
}

CStringW CUrlLocateType::Prefix(const _e _type) {
	CStringW cs_pfx;
	switch (_type) {
	case CUrlLocateType::eExternalLink  : {} break;
	case CUrlLocateType::eHostExecutable: { cs_pfx = _T("res://" ); } break;
	case CUrlLocateType::eOuterBrowser  : { cs_pfx = _T("outer::"); } break;
	case CUrlLocateType::eInterCommand  : { cs_pfx = _T("inter::"); } break;
	}
	return cs_pfx;
}

const CUrlLocateType::_e
         CUrlLocateType::ToType(LPCWSTR _lp_sz_pat) {
	CUrlLocateType::_e type_ = CUrlLocateType::eExternalLink;
	CStringW cs_pat(_lp_sz_pat);

	if (cs_pat.IsEmpty()) return type_;
	if (cs_pat.GetLength() < CUrlLocateType::MinLen()) return type_;

	if (0 == cs_pat.Find(CUrlLocateType::Prefix(CUrlLocateType::eHostExecutable))) type_ = CUrlLocateType::eHostExecutable;
	if (0 == cs_pat.Find(CUrlLocateType::Prefix(CUrlLocateType::eOuterBrowser))) type_ = CUrlLocateType::eOuterBrowser;
	if (0 == cs_pat.Find(CUrlLocateType::Prefix(CUrlLocateType::eInterCommand))) type_ = CUrlLocateType::eInterCommand;

	return type_;
}

/////////////////////////////////////////////////////////////////////////////

CUrlLocator:: CUrlLocator(const CUrlLocateType::_e _type) : m_type(_type), m_data((LONG)0) { m_error >> __CLASS__ << __METHOD__; }
CUrlLocator:: CUrlLocator(LPCWSTR _lp_sz_pat) : m_type(_lp_sz_pat), m_data((LONG)0) { m_error >> __CLASS__ << __METHOD__; this->URL(_lp_sz_pat); }
CUrlLocator::~CUrlLocator(void) {}

/////////////////////////////////////////////////////////////////////////////

bool          CUrlLocator::Accept(LPCWSTR _lp_sz_pat) const {
	m_error << __METHOD__ << S_OK;
	bool b_accept = false;

	CUrlLocateType type_(_lp_sz_pat); // this object is just for pattern type test, otherwise, this method cannot be const;
	if (type_ == false)
		return (m_error = type_);

	switch (type_.Type()) {
	case CUrlLocateType::eHostExecutable: {
			CStringW cs_pat(_lp_sz_pat);
			const INT n_pos = cs_pat.Find(_T("%s"));
			b_accept = (n_pos != -1);
		} break;
	case CUrlLocateType::eInterCommand  :
	case CUrlLocateType::eOuterBrowser  : {
			b_accept = true;
		} break;
	}

	return b_accept;
}

const
_variant_t&   CUrlLocator::Data  (void) const { return m_data; }
DWORD         CUrlLocator::DataAsCommand(void) const { if (VT_I4 != m_data.vt) return 0; else return m_data.lVal; }

TErrorRef     CUrlLocator::Error (void) const { return m_error; }
const
CUrlLocateType& CUrlLocator::Type(void) const { return m_type ; }
CUrlLocateType& CUrlLocator::Type(void)       { return m_type ; }
LPCWSTR       CUrlLocator::URL   (void) const { return m_url.GetString(); }
LPCWSTR       CUrlLocator::URL   (LPCWSTR lpszPattern) { this->URL(lpszPattern, m_url);  return this->URL(); }
HRESULT       CUrlLocator::URL   (LPCWSTR lpszPattern, CStringW& _result) {
	m_error << __METHOD__ << S_OK;

	m_type << lpszPattern;
	if (m_type == false)
		return (m_error = m_type);

	switch (m_type.Type()) {
	case CUrlLocateType::eHostExecutable:
		{
			CStringW cs_path;
			CApplication& the_app = GetAppObjectRef();

			HRESULT hr_ = the_app.GetPath(cs_path);
			if (FAILED(hr_))
				return (m_error = the_app.GetLastResult());

			CGenericPath path_(cs_path.GetString());
			const bool bResult  = path_.Normalize(CObjectType::eFolder);
			if (false == bResult)
				return (m_error = (DWORD)ERROR_BAD_PATHNAME);

			CStringW cs_file  = the_app.GetFileName(false);
			cs_path.Format(
				_T("%s%s"), (LPCWSTR)path_, cs_file.GetString()
			);

			_result.Format(
					lpszPattern, cs_path.GetString()
				);
		} break;
	case CUrlLocateType::eExternalLink: { _result = lpszPattern; } break;
	case CUrlLocateType::eOuterBrowser: {

			CStringW cs_pat(lpszPattern);
			CStringW cs_pfx = CUrlLocateType::Prefix(m_type);

			if (0 == cs_pat.Find(cs_pfx)) {
				_result = cs_pat.Right(cs_pat.GetLength() - cs_pfx.GetLength());
			}
			else
				m_error.State().Set((DWORD)ERROR_INVALID_DATA, _T("Provided URL pattern cannot be parsed."));

		} break;
	case CUrlLocateType::eInterCommand: {

		CStringW cs_pat(lpszPattern);
		CStringW cs_pfx = CUrlLocateType::Prefix(m_type);

			if (0 == cs_pat.Find(cs_pfx)) {
				_result = cs_pat.Right(cs_pat.GetLength() - cs_pfx.GetLength());
				m_data = ::_tstol(_result.GetString());
			}
			else
				m_error.State().Set((DWORD)ERROR_INVALID_DATA, _T("Provided URL pattern does not provide internal command ID."));

		} break;

	default:
		m_error = DISP_E_TYPEMISMATCH;
	}

	return m_error;
}

/////////////////////////////////////////////////////////////////////////////

CUrlLocator& CUrlLocator::operator<<  (const CUrlLocateType&  _rhv)  { this->Type() = _rhv   ; return *this; }
CUrlLocator& CUrlLocator::operator<<  (const CUrlLocateType::_e _v)  { this->Type() = _v     ; return *this; }
CUrlLocator& CUrlLocator::operator<<  (LPCWSTR _lp_sz_pat)           { this->URL (_lp_sz_pat); return *this; }
CUrlLocator::operator DWORD    (void)  const { return this->DataAsCommand(); }
CUrlLocator::operator LPCWSTR  (void)  const { return this->URL();   }
CUrlLocator::operator TErrorRef(void)  const { return this->Error(); }
bool  CUrlLocator::operator==  (LPCWSTR _lp_sz_ref) const {
	bool b_res = false;
	if (NULL == _lp_sz_ref || !::_tcslen(_lp_sz_ref))
		return b_res;

	const INT n_pos = m_url.Find(_lp_sz_ref);
	b_res = ( n_pos!= -1);
	return b_res;
}

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace details
{
	class CBrowserEmulateRegistry
	{
	private:
		mutable
		CRegistryStg m_stg;
		CStringW     m_named_value;
	public:
		CBrowserEmulateRegistry(LPCWSTR lpszNamedValue) :
			m_stg(
				HKEY_CURRENT_USER, CRegOptions::eDoNotModifyPath
			),
			m_named_value(lpszNamedValue){}
	public:
		HRESULT   Emulation(eBrowserEmulationVersion::_e& _mode)
		{
			LONG lValue = 0;
			HRESULT hr_ = m_stg.Load(
					this->_EmulateRegFolder(), m_named_value, lValue, static_cast<DWORD>(eBrowserEmulationVersion::eDefault)
				);
			if (FAILED(hr_))
				return hr_;

			_mode = static_cast<eBrowserEmulationVersion::_e>(lValue);

			return hr_;
		}

		HRESULT   Emulation(const eBrowserEmulationVersion::_e& _mode)
		{
			HRESULT hr_ = m_stg.Save(
					this->_EmulateRegFolder(), m_named_value, static_cast<DWORD>(_mode)
				);
			return  hr_;
		}

		HRESULT   Version(LONG& _major)
		{
			CStringW cs_version;
			HRESULT hr_ = m_stg.Load(
					this->_VersionRegFolder(), this->_VersionRegValue_New(), cs_version
				);
			if (cs_version.IsEmpty())
				hr_ = m_stg.Load(
					this->_VersionRegFolder(), this->_VersionRegValue_Old(), cs_version
				);
			if (SUCCEEDED(hr_))
				_major = ::_tstol(cs_version);
			return hr_;
		}
	private:
		LPCWSTR  _EmulateRegFolder(void) const
		{
			static CStringW cs_folder;
			if (cs_folder.IsEmpty()){
				cs_folder += this->_VersionRegFolder();
				cs_folder +=_T("\\Main\\FeatureControl\\FEATURE_BROWSER_EMULATION");
			}
			return cs_folder;
		}

		LPCWSTR  _VersionRegFolder(void) const
		{
			static CStringW cs_folder(_T("SOFTWARE\\Microsoft\\Internet Explorer"));
			return cs_folder;
		}

		LPCWSTR  _VersionRegValue_New(void)const
		{
			static CStringW cs_ver(_T("svcVersion"));
			return cs_ver;
		}

		LPCWSTR  _VersionRegValue_Old(void)const
		{
			static CStringW cs_ver(_T("Version"));
			return cs_ver;
		}
	};
}}

/////////////////////////////////////////////////////////////////////////////

CBrowserEmulateMan::CBrowserEmulateMan(LPCWSTR lpszHost) {
	m_error << __METHOD__ << S_OK;

	m_host_name = lpszHost;

	if (m_host_name.IsEmpty())
	{
		const CApplication& the_app = GetAppObjectRef();
		m_host_name = the_app.GetFileName();
	}
	if (m_host_name.IsEmpty())
		m_error.State().Set(
				E_FAIL,
				_T("Cannot evaluate executable file name.")
			);
	else
		m_error = S_OK;
}

/////////////////////////////////////////////////////////////////////////////

HRESULT      CBrowserEmulateMan::ApplyLatestVersion(void) {
	m_error << __METHOD__ << S_OK;

	eBrowserEmulationVersion::_e the_latest = this->LatestAvailableVersion();
	this->Mode(the_latest);

	return m_error;
}

TErrorRef    CBrowserEmulateMan::Error(void) const { return m_error; }

bool         CBrowserEmulateMan::IsEnabled(const eBrowserEmulationVersion::_e _mode)const
{
	const eBrowserEmulationVersion::_e eMode = this->Mode();
	return (_mode <= eMode);
}

eBrowserEmulationVersion::_e
             CBrowserEmulateMan::LatestAvailableVersion(void)const
{
	eBrowserEmulationVersion::_e the_latest = eBrowserEmulationVersion::eVersion11;
	return the_latest;
#if(0)
	details::CBrowserEmulateRegistry reg_(m_host_name);
	LONG major_ = 0;
	HRESULT hr_ = reg_.Version(major_);
	if (FAILED(hr_))
		return the_latest;

	if (major_ > 11)
		major_ = 11;
	switch (major_)
	{
	case 11: the_latest = eBrowserEmulationVersion::eVersion11; break;
	case 10: the_latest = eBrowserEmulationVersion::eVersion10; break;
	case  9: the_latest = eBrowserEmulationVersion::eVersion9;  break;
	case  8: the_latest = eBrowserEmulationVersion::eVersion8;  break;
	}
	return the_latest;
#endif
}

eBrowserEmulationVersion::_e 
             CBrowserEmulateMan::Mode(void) const {
	m_error << __METHOD__ << S_OK;

	eBrowserEmulationVersion::_e eMode = eBrowserEmulationVersion::eDefault;
	details::CBrowserEmulateRegistry reg_(m_host_name);

	HRESULT hr_ = reg_.Emulation(eMode);
	if (FAILED(hr_)) {
		eMode = eBrowserEmulationVersion::eDefault;
		m_error = hr_;
	}
	return eMode;
}

HRESULT      CBrowserEmulateMan::Mode(const eBrowserEmulationVersion::_e _mode) {
	m_error << __METHOD__ << S_OK;

	details::CBrowserEmulateRegistry reg_(m_host_name);
	HRESULT hr_ = reg_.Emulation(_mode);
	if (FAILED(hr_))
		m_error = hr_;

	return m_error;
}