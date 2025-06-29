/*
	Created by Tech_dog (ebontrop@gmail.con) on 29-Jun-2025 at 07:41:53.2300, UTC+4, Batumi, Sunday;
	This is Ebo Pack custom theme registry storage base interface implementation file;
*/
#include "uix.theme.reg.h"

using namespace ex_ui::theme::storage;

using CRegKey = ::ATL::CRegKey;
/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace theme { namespace storage { namespace _impl {
	#define ThemeRoot HKEY_CURRENT_USER
	class CReg_router {
	public:
		class CCategory {
		public:
			 CCategory (void) {} CCategory (const CCategory&) = delete; CCategory (CCategory&&) = delete;
			~CCategory (void) {}

		public:
			CString  Dark (void) const { CString cs_key(CReg_router::Themes()); cs_key += _T("Dark"); return cs_key; }
			CString  Light (void) const { CString cs_key(CReg_router::Themes()); cs_key += _T("Light"); return cs_key; }

		private:
			CCategory& operator = (const CCategory&) = delete;
			CCategory& operator = (CCategory&&) = delete;
		};
	public:
		 CReg_router (void) : m_root(ThemeRoot) {} CReg_router (const CReg_router&) = delete; CReg_router (CReg_router&&);
		~CReg_router (void) {}

	public:
		const
		HKEY&   Root (void) const { return this->m_root; }

		static _pc_sz Themes (void) {
			static _pc_sz pc_sz_root = _T("Software\\ebo::boo::renderer\\Themes");
			return  pc_sz_root;
		}

	private:
		CReg_router& operator = (const CReg_router&) = delete;
		CReg_router& operator = (CReg_router&&) = delete;
	private:
		HKEY m_root;
	};

	CReg_router&  Get_rooter (void) {
		static CReg_router rooter;
		return rooter;
	}

	class CTheme_enum {
	public:
		 CTheme_enum (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
		 CTheme_enum (const CTheme_enum&) = delete; CTheme_enum (CTheme_enum&&) = delete;
		~CTheme_enum (void) {}

	public:
		TError&  Error (void) const { return this->m_error; }
		err_code Get (const HKEY _parent, const TThemePalette _palette, TRawNamed& _raw) {
			_parent; _raw;
			this->m_error << __METHOD__ << __s_ok;

			dword d_count = 0;
			CRegKey counter; counter.Attach(_parent);
			
			LSTATUS n_result = counter.QueryDWORDValue(_T("Count"), d_count);

			if (!!n_result)
				return this->m_error = dword(n_result);

			if (0 == d_count)
				return this->Error(); // there is not such category theme;

			t_char  sz_buffer[512] = {0}; unsigned long u_count = _countof(sz_buffer); u_count;
			CString cs_theme;
			for (dword i_ = 0; i_ < d_count; i_++) {

				cs_theme.Format(_T("Theme#%u"), i_);
				CRegKey  theme_;
				// https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regopenkeyexa ;
				n_result = theme_.Open(counter, (_pc_sz) cs_theme);
				if (!!n_result) {
					this->m_error = dword(n_result); break;
				}
				CNamed named(_palette);

				unsigned long n_chars = u_count;
				n_result = theme_.QueryStringValue(_T("Name"), sz_buffer, &n_chars);
				if (!!n_result) {
					this->m_error = dword(n_result); break;
				}
				else
					named.Name(sz_buffer);

				n_chars = u_count; // the buffer size requires to be restored, otherwise above call resets it to '0';

				// https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regqueryvalueexa ;
				n_result = theme_.QueryStringValue(_T("Description"), sz_buffer, &n_chars);
				if (!!n_result) {
					this->m_error = dword(n_result); break;
				}
				else
					named.Desc(sz_buffer);

				try {
					_raw.push_back(named);
				}
				catch (const ::std::bad_alloc&) { this->m_error << __e_no_memory;  break; }
			}
			counter.Detach();
			return this->Error();
		}

	private:
		CTheme_enum& operator = (const CTheme_enum&) = delete;
		CTheme_enum& operator = (CTheme_enum&&) = delete;
	private:
		CError m_error;
	};

}}}}

using namespace ex_ui::theme::storage::_impl;

/////////////////////////////////////////////////////////////////////////////

CRegistry:: CRegistry (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CRegistry::~CRegistry (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&  CRegistry::Error (void) const { return this->m_error; }

err_code  CRegistry::Load (ex_ui::theme::CNamed_Enum& _enum) {
	_enum;
	this->m_error << __METHOD__ << __s_ok;
	// *attention*: registry does not return hresult, in case of success a key function returns '0', i.e. error_success;
	CRegKey themes;
	LSTATUS n_result = themes.Open(Get_rooter().Root(), Get_rooter().Themes());
	if (!!n_result)
		return this->m_error = dword(n_result);

	CTheme_enum theme_enum; TRawNamed& raw_themes = _enum.Raw();

	CRegKey cat_dark;
	n_result = cat_dark.Open(themes, _T("Dark"));
	if (__s_ok == n_result) {
		if (__failed(theme_enum.Get(cat_dark, TThemePalette::e_dark, raw_themes))) {
			this->m_error = theme_enum.Error();
		}
	}

	CRegKey cat_light;
	n_result = cat_light.Open(themes, _T("Light"));
	if (__s_ok == n_result) {
		if (__failed(theme_enum.Get(cat_light, TThemePalette::e_light, raw_themes))) {
			this->m_error = theme_enum.Error();
		}
	}

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

