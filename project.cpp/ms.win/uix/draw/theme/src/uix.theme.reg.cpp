/*
	Created by Tech_dog (ebontrop@gmail.con) on 29-Jun-2025 at 07:41:53.2300, UTC+4, Batumi, Sunday;
	This is Ebo Pack custom theme registry storage base interface implementation file;
*/
#include "uix.theme.reg.h"

using namespace ex_ui::theme::storage;

using CRegKey = ::ATL::CRegKey;

#define ThemeRoot HKEY_CURRENT_USER
/////////////////////////////////////////////////////////////////////////////

CReg_router:: CReg_router (void) : m_root(ThemeRoot) {}
CReg_router::~CReg_router (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CCurrent&     CReg_router::CurrentTheme (void) const { return this->m_current; }
CCurrent&     CReg_router::CurrentTheme (void)       { return this->m_current; }

_pc_sz CReg_router::Element (void) const {
	return this->Element(this->CurrentTheme().Palette(), this->CurrentTheme().Part(), this->CurrentTheme().Element());
}

_pc_sz CReg_router::Element (const TThemePalette _palette, const TThemePart _part, const TThemeElement _element) const {
	_palette; _part; _element;
	static CString cs_out;
	cs_out.Format(_T("%s\\%s"), this->Part(_palette, _part), (_pc_sz) TPrint::Out(_element));

	return cs_out.GetString();
}

_pc_sz CReg_router::Marker (const TColorMarker& _marker) const {
	_marker;
	static CString cs_out;

	cs_out.Format(_T("%s\\%s\\%s\\%s"),
		this->Theme(_marker.Palette()),
		(_pc_sz) TPrint::Out(_marker.Part()),
		(_pc_sz) TPrint::Out(_marker.Element()),
		(_pc_sz) TPrint::Out(_marker.State())
	);

	return cs_out.GetString();
}

_pc_sz CReg_router::Palette (void) const {
	return this->Palette(this->CurrentTheme().Palette());
}

_pc_sz CReg_router::Palette (const TThemePalette _palette) const {
	_palette;
	static CString cs_out;
	cs_out.Format(_T("%s\\%s"), this->Themes(), (_pc_sz) TPrint::Out(_palette));

	return cs_out.GetString();
}

_pc_sz CReg_router::Part (void) const {
	return this->Part(this->CurrentTheme().Palette(), this->CurrentTheme().Part());
}

_pc_sz CReg_router::Part (const TThemePalette _palette, const TThemePart _part) const {
	_palette; _part;
	static CString cs_out;
	cs_out.Format(_T("%s\\Parts\\%s"), this->Theme(_palette), (_pc_sz) TPrint::Out(_part));

	return cs_out.GetString();
}

HKEY   CReg_router::Root (void) const { return this->m_root; }

_pc_sz CReg_router::State (void) {
	return this->State(this->CurrentTheme().Palette(), this->CurrentTheme().Part(), this->CurrentTheme().Element(), this->CurrentTheme().State());
}

_pc_sz CReg_router::State (const TThemePalette _palette, const TThemePart _part, const TThemeElement _element, const TThemeState _state) const {
	_palette; _part; _element; _state;
	static CString cs_out;
	cs_out.Format(_T("%s\\%s"), this->Element(_palette, _part, _element), (_pc_sz) TPrint::Out(_state));

	return cs_out.GetString();
}

_pc_sz CReg_router::Theme (const TThemePalette _palette) const {
	return this->Theme(_palette, this->CurrentTheme().ThemeIndex());
}

_pc_sz CReg_router::Theme (const TThemePalette _palette, const uint32_t _ndx) const {
	_ndx;
	static CString cs_out; cs_out.Format(_T("%s\\Theme#%u"), (_pc_sz) this->Palette(_palette), _ndx);
	return cs_out.GetString();
}

_pc_sz CReg_router::Themes (void) const {
	static _pc_sz pc_sz_root = _T("Software\\ebo::boo::renderer\\Themes");
	return  pc_sz_root;
}

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace theme { namespace storage { 
	
	CReg_router&  Get_router (void) {
		static CReg_router router;
		return router;
	}

namespace _impl {

	class CTheme_enum {
	public:
		 CTheme_enum (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
		 CTheme_enum (const CTheme_enum&) = delete; CTheme_enum (CTheme_enum&&) = delete;
		~CTheme_enum (void) {}

	public:
		TError&  Error (void) const { return this->m_error; }
		err_code Get (const HKEY _plt_key, const TThemePalette _palette, TRawNamed& _raw) {
			_plt_key; _raw;
			this->m_error << __METHOD__ << __s_ok;

			dword d_count = 0;
			CRegKey plt_key_; plt_key_.Attach(_plt_key);
			
			LSTATUS n_result = plt_key_.QueryDWORDValue(_T("Count"), d_count);

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
				n_result = theme_.Open(plt_key_, (_pc_sz) cs_theme);
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
			plt_key_.Detach();
			return this->Error();
		}

	private:
		CTheme_enum& operator = (const CTheme_enum&) = delete;
		CTheme_enum& operator = (CTheme_enum&&) = delete;
	private:
		CError m_error;
	};

	class CTheme_parts {
	public:
		 CTheme_parts (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
		 CTheme_parts (const CTheme_parts&) = delete; CTheme_parts (CTheme_parts&&) = delete;
		~CTheme_parts (void) {}

	public:
		TError&  Error (void) const { return this->m_error; }
		err_code Get (const HKEY _theme, TRawParts& _raw_parts) {
			_theme; _raw_parts;
			this->m_error << __METHOD__ << __s_ok;

			CRegKey theme_; theme_.Attach(_theme);

			CRegKey parts_;


			theme_.Detach();
			return this->Error();
		}

	private:
		CTheme_parts&  operator = (const CTheme_parts&) = delete;
		CTheme_parts&  operator = (CTheme_parts&&) = delete;
	private:
		CError m_error;
	};

	class CTheme_state {
	public:
		 CTheme_state (void) {} CTheme_state (const CTheme_state&) = delete; CTheme_state (CTheme_state&&) = delete;
		~CTheme_state (void) {}

	public:
		err_code Get (const HKEY _h_key, TRawStates& _states) {
			_h_key; _states;
			err_code n_result = __s_ok;
			CRegKey  key_state; key_state.Attach(_h_key);

			t_char  sz_buffer[512] = {0}; unsigned long u_count = _countof(sz_buffer);
			for (size_t i_ = 0; i_ < _states.size(); i_++) {
#if (0)
			//	https://stackoverflow.com/questions/20264530/c-warning-c4930-prototyped-function-not-called-was-a-variable-definition-i ;
			//	https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4930 ;
			//	warning C4930: 'ex_ui::theme::CState state(TThemeState)': prototyped function not called (was a variable definition intended?) ;

			//	CState state((TThemeState(i_));
				CState state_((TThemeState)i_);
#else
				CState& state_ = _states.at(i_);
				state_.Id ((TThemeState)i_, true);
#endif
				unsigned long n_chars = u_count;
				n_result = key_state.QueryStringValue(state_.Name(), sz_buffer, &n_chars);
				if (!!n_result) // there is no value with such name;
					continue;
				state_.Hex().Set(sz_buffer);
			}

			key_state.Detach();
			return n_result;		
		}
	private:
		CTheme_state& operator = (const CTheme_state&) = delete;
		CTheme_state& operator = (CTheme_state&&) = delete;
	};
}}}}

using namespace ex_ui::theme::storage::_impl;

/////////////////////////////////////////////////////////////////////////////

CRegistry:: CRegistry (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CRegistry::~CRegistry (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&  CRegistry::Error (void) const { return this->m_error; }

err_code CRegistry::Node  (_pc_sz _p_path, CElement& _element) {
	_p_path; _element;
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_path || 0 == ::_tcslen(_p_path))
		return this->m_error << __e_inv_arg;

	CRegKey k_element;
	LSTATUS n_result = k_element.Open(Get_router().Root(), _p_path);

	if (!!n_result)
		return this->m_error = dword(n_result);
	else
		_element.Is_valid(true);
#if (1)
	n_result = this->Value (_element.States());
#else
	for (size_t i_ = 0; i_ < _element.States().size(); i_++ ){

		CState& state_ = _element.States().at(i_); // the particular state has already proper identifier and name that is set by its owner;

		CCurrent& theme = Get_router().CurrentTheme();
		theme.State() = state_.Id();

		CString cs_path = Get_router().State();

		n_result = this->Value((_pc_sz) cs_path, state_); // the error is ignored due to the fact the state is not saved in the registry;
	}
#endif
	return this->Error();
}

err_code CRegistry::Node  (_pc_sz _p_path, ex_ui::theme::CPalette& _palette) {
	_p_path; _palette;
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_path || 0 == ::_tcslen(_p_path))
		return this->m_error << __e_inv_arg;

	CRegKey k_palette;
	LSTATUS n_result = k_palette																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																					.Open(Get_router().Root(), _p_path);

	if (!!n_result)
		return this->m_error = dword(n_result);
	else
		_palette.Is_valid(true);

	this->Node(_palette.Parts());

	return this->Error();
}

err_code CRegistry::Node  (_pc_sz _p_path, CPart& _part) {
	_p_path; _part;
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_path || 0 == ::_tcslen(_p_path))
		return this->m_error << __e_inv_arg;

	CRegKey k_part;
	LSTATUS n_result = k_part.Open(Get_router().Root(), _p_path);

	if (!!n_result)
		return this->m_error = dword(n_result);
	else
		_part.Is_valid(true);

	this->Node(_part.Elements());

	return this->Error();
}

err_code CRegistry::Node  (TRawElements& _elements) {
	_elements;
	this->m_error << __METHOD__ << __s_ok;

	CString cs_path ;
	bool b_at_least = false;                // is set to 'true' in case when at least one element is loaded from the regestry;

	for (size_t i_ = 0; i_ < _elements.size(); i_++) {
		CElement& element = _elements.at(i_);

		Get_router().CurrentTheme().Element() = element.Id();
		cs_path = Get_router().Element();   // currently selected theme is used for composing the path required;

		if (__failed(this->Node((_pc_sz) cs_path, element))) {
			continue; // ignores the error returned;
		}
		else
			b_at_least = true;
	}
	if (b_at_least)
		this->m_error << __s_ok;

	return this->Error();
}

err_code CRegistry::Node  (TRawParts& _parts) {
	_parts;
	this->m_error << __METHOD__ << __s_ok;

	CString cs_path ;
	bool b_at_least = false;                // is set to 'true' in case when at least one part is loaded from the regestry;

	for (size_t i_ = 0; i_ < _parts.size(); i_++) {
		CPart& part = _parts.at(i_);

		Get_router().CurrentTheme().Part() = part.Id();
		cs_path = Get_router().Part();      // currently selected theme is used for composing the path required;

		if (__failed(this->Node((_pc_sz) cs_path, part))) {
			continue; // ignores the error returned;
		}
		else
			b_at_least = true;
	}

	if (b_at_least)
		this->m_error << __s_ok;

	return this->Error();
}

err_code CRegistry::Value (TRawStates& _states) {
	_states;
	err_code n_result = __s_ok;
	CString cs_path = Get_router().Element();

	bool b_at_least = false; // this is intermediate result that indicates at least one state is loaded;

	for (size_t i_ = 0; i_ < _states.size(); i_++) {
		CState& state = _states.at(i_);
		n_result = this->Value((_pc_sz) cs_path, state); // result code is ignored;
		if (n_result == __s_ok)
			b_at_least = true;
	}
	if (b_at_least)
		this->m_error << __s_ok; // restores the no error state if at least one state has been loaded;

	return n_result;
}

err_code CRegistry::Value (_pc_sz _p_path, CState& _state) {
	return this->Value (_p_path, _state.Id(), _state);
}

err_code CRegistry::Value (_pc_sz _p_path, const TThemeState _e_state, CState& _state) {
	_p_path; _state;
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_path || 0 == ::_tcslen(_p_path))
		return this->m_error << __e_inv_arg;

	CRegKey k_state;
	LSTATUS n_result = k_state.Open(Get_router().Root(), _p_path);

	if (!!n_result)
		return this->m_error = dword(n_result);

	t_char  sz_buffer[512] = {0}; unsigned long u_count = _countof(sz_buffer);

	unsigned long n_chars = u_count;

	CString cs_value = TThemeState::e_default == _e_state ? _T("") : (_pc_sz) TPrint::Out(_e_state);

	n_result = k_state.QueryStringValue((_pc_sz) cs_value, sz_buffer, &n_chars);
	if (!!n_result) // there is no value with such name;
		(this->m_error = dword(n_result)) = TStringEx().Format(_T("%s such state is not defined;"), (_pc_sz) TPrint::Out(_e_state));
	else {
		_state.Hex().Set(sz_buffer);
		_state.Is_valid(true);
	}
	return this->Error();
}

err_code CRegistry::Load (ex_ui::theme::CNamed_Enum& _enum) {
	_enum;
	this->m_error << __METHOD__ << __s_ok;
	// *attention*: registry does not return hresult, in case of success a key function returns '0', i.e. error_success;
	CRegKey themes;
	LSTATUS n_result = themes.Open(Get_router().Root(), Get_router().Themes());
	if (!!n_result)
		return this->m_error = dword(n_result);

	CTheme_enum theme_enum; TRawNamed& raw_themes = _enum.Raw();

	CRegKey plt_dark;
	n_result = plt_dark.Open(themes, _T("Dark"));
	if (__s_ok == n_result) {
		if (__failed(theme_enum.Get(plt_dark, TThemePalette::e_dark, raw_themes))) {
			this->m_error = theme_enum.Error();
		}
	}

	CRegKey plt_light;
	n_result = plt_light.Open(themes, _T("Light"));
	if (__s_ok == n_result) {
		if (__failed(theme_enum.Get(plt_light, TThemePalette::e_light, raw_themes))) {
			this->m_error = theme_enum.Error();
		}
	}

	return this->Error();
}