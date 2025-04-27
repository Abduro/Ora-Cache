/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Apr-2025 at 02:21:55.972, UTC+4, Batumi, Sunday;
	This is Ebo Pack desktop window manager wrapper interface implementation file.
*/
#include "ebo.sha.dwm.wrap.h"

using namespace ebo::sha::theme;

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace sha { namespace theme { namespace _impl {

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

}}}}

using namespace ebo::sha::theme::_impl;
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