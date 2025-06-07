/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Apr-2025 at 02:21:55.972, UTC+4, Batumi, Sunday;
	This is Ebo Pack desktop window manager wrapper interface implementation file.
*/
#include "sys.shell.dwm.h"

using namespace shared::sys_core::shell;

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace sys_core { namespace shell { namespace _impl {

	class CReg_router {
	public:
		 CReg_router (void) {} CReg_router (const CReg_router&) = delete; CReg_router (CReg_router&&);
		~CReg_router (void) {}

	public:
		static _pc_sz GetPersonalize (void) {
			static CString cs_pers;
			if (cs_pers.IsEmpty()) {
				cs_pers.Format(_T("%s\\Personalize"), CReg_router::GetThemes());
			}
			return  (_pc_sz)cs_pers;
		}

		static _pc_sz GetThemes (void) {
			static _pc_sz pc_sz_root = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Themes");
			return  pc_sz_root;
		}

	private:
		CReg_router& operator = (const CReg_router&) = delete;
		CReg_router& operator = (CReg_router&&) = delete;
	};
	#define ThemeRoot HKEY_CURRENT_USER
	class CReg_storage {
	public:
		 CReg_storage (void) : m_hRoot (ThemeRoot){ this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
		 CReg_storage (const CReg_storage&) = delete; CReg_storage (CReg_storage&&) = delete;
		~CReg_storage (void) {}

	public:
		TError& Error (void) const { return this->m_error; }

		err_code Get (_pc_sz _p_path, _pc_sz _p_key, dword& _value) {
			_p_path; _p_key; _value = 0;
			this->m_error << __METHOD__ << __s_ok;

			CRegKey key;

			LSTATUS n_result = key.Create(m_hRoot, _p_path);
			if (__failed(n_result))
				return this->m_error.Last();

			n_result = key.QueryDWORDValue(_p_key, _value);
			if (__failed(n_result))
				this->m_error.Last();

			return this->Error();
		}

	private:
		CReg_storage&  operator = (const CReg_storage&) = delete;
		CReg_storage&  operator = (CReg_storage&&) = delete;

	private:
		CError  m_error;
		HKEY    m_hRoot;
	};
	
	// https://learn.microsoft.com/en-us/windows/win32/sysinfo/operating-system-version ; for Win.11 build no. >= 22000;
	// https://stackoverflow.com/questions/69373447/is-there-an-official-way-to-detect-windows-11 ;
	typedef OSVERSIONINFOEX TOsVerInfoEx; // for getting OS build no. it is not required or can be not used;
	typedef OSVERSIONINFO   TOsVerInfo  ;

	class COS_Version {
	public:
		 COS_Version (void) : m_info{0} { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
		~COS_Version (void) {}
		 COS_Version (const COS_Version&) = delete; COS_Version (COS_Version&&) = delete;

	public:
		TError&   Error (void) const { return this->m_error; }
		const
		TOsVerInfo& Get (void) const { return this->m_info; }

		bool Is_10 (void) const { return this->Get().dwBuildNumber < 22000; }
		bool Is_11 (void) const { return false == this->Is_10(); }
		// https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getversionexa ;
		err_code    Set (void) {
			this->m_error << __METHOD__ << __s_ok;
			this->m_info.dwOSVersionInfoSize = sizeof(TOsVerInfo);
			#pragma warning(disable:4996)
			if (false == !!::GetVersionEx(&this->m_info))
				this->m_error.Last();
			#pragma warning(default:4996)
			return this->Error();
		}

	private:
		COS_Version&  operator = (const COS_Version&) = delete;
		COS_Version&  operator = (COS_Version&&) = delete;
	private:
		CError  m_error;
		TOsVerInfo m_info;
	};
}}}}

using namespace shared::sys_core::shell::_impl;
/////////////////////////////////////////////////////////////////////////////

CDwmAtt:: CDwmAtt (const HWND _target) : m_target( _target) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CDwmAtt::~CDwmAtt (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&   CDwmAtt::Error (void) const { return this->m_error; }
bool      CDwmAtt::Get (const uint32_t _n_att) const {
	_n_att;
	this->m_error << __METHOD__ << __s_ok;
	bool b_result = false;

	if (CDwmAtt::Is_valid(this->Target()) == false) {
		this->m_error << __e_hwnd;
		return b_result;
	}

	switch (_n_att) {
	case ToWin_10::e_nc_render:
	case ToWin_10::e_transit  :
	case ToWin_10::e_nc_paint : {
		// https://learn.microsoft.com/en-us/windows/win32/api/dwmapi/nf-dwmapi-dwmgetwindowattribute ;
		int32_t n_result = 0;
		this->m_error << ::DwmGetWindowAttribute(this->Target(), _n_att, &n_result, sizeof(int32_t));
		if (this->Error() == false)
			b_result = !!n_result;
		break;
	}
	default:
		this->m_error << __e_inv_arg = TStringEx().Format(_T("The attr=(%d) returns other data type;"), _n_att);
	}

	return b_result;
}

err_code  CDwmAtt::Set (const uint32_t _n_att, const bool _b_value) {
	_n_att; _b_value;
	this->m_error << __METHOD__ << __s_ok;

	if (CDwmAtt::Is_valid(this->Target()) == false)
		return this->m_error << __e_hwnd;

	switch (_n_att) {
	case ToWin_10::e_nc_render:
	case ToWin_10::e_transit  :
	case ToWin_10::e_nc_paint : {
		// https://learn.microsoft.com/en-us/windows/win32/api/dwmapi/nf-dwmapi-dwmsetwindowattribute ;
		int32_t n_result = _b_value;
		this->m_error << ::DwmSetWindowAttribute(this->Target(), _n_att, &n_result, sizeof(int32_t));
		break;
	}
	default:
		this->m_error << __e_inv_arg = TStringEx().Format(_T("The attr=(%d) requires other input data type;"), _n_att);
	}

	return this->Error();
}

const
HWND      CDwmAtt::Target (void) const { return this->m_target; }
err_code  CDwmAtt::Target (const HWND _h_target) {
	_h_target;
	this->m_error << __METHOD__ << __s_ok;

	if (CDwmAtt::Is_valid(_h_target) == false)
		return this->m_error << __e_hwnd;

	this->m_target = _h_target;

	return this->Error();
}

bool CDwmAtt::Is_valid (const HWND _h_target) {
	return (nullptr != _h_target && true == !!::IsWindow(_h_target));
}

/////////////////////////////////////////////////////////////////////////////

CDwmAtt& CDwmAtt::operator <<(const HWND _h_target) { this->Target(_h_target); return *this; }

/////////////////////////////////////////////////////////////////////////////

CDwmSettings:: CDwmSettings (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////

TError& CDwmSettings::Error (void) const { return this->m_error; }

bool    CDwmSettings::EnableTransparency (void) const {
	this->m_error << __METHOD__ << __s_ok;

	bool b_use = false;

	CReg_storage reg_stg;
	dword n_value = 0;
	this->m_error << reg_stg.Get(CReg_router::GetPersonalize(), _T("EnableTransparency"), n_value);

	if (this->Error())
		this->m_error = reg_stg.Error();
	else
		b_use = !!n_value;

	return b_use;
}

bool    CDwmSettings::SystemUsesLightTheme (void) const {
	this->m_error << __METHOD__ << __s_ok;

	bool b_use = false;

	CReg_storage reg_stg;
	dword n_value = 0;
	this->m_error << reg_stg.Get(CReg_router::GetPersonalize(), _T("SystemUsesLightTheme"), n_value);

	if (this->Error())
		this->m_error = reg_stg.Error();
	else
		b_use = !!n_value;

	return b_use;
}