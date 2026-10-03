/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Apr-2017 at 11:05:46p, GMT+7, Phuket, Rawai, Saturday;
	This is Ebo Pack shared UIX Web Browser library common definition implementation file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 28-May-2018 at 9:27:08p, UTC+7, Phuket, Rawai, Monday;
*/
#include "web.ie.defs.h"

using namespace ex_ui::web::IE::defs;

#if (0)

#include "shared.gen.app.obj.h"
#include "shared.reg.hive.h"

using namespace shared::user32;
using namespace shared::registry;

#include "shared.fs.defs.h"

using namespace shared::ntfs;


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

#endif