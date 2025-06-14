/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Jun-2025 at 22:35:55.633, UTC+4, Batumi, Friday;
	This is Ebo Pack system font collection generic wrapper interface implementation file;
*/
#include "sys.shell.font.h"

using namespace shared::sys_core::shell;
#if (0)
CFontStub:: CFontStub (void) : m_log{0} {}
CFontStub:: CFontStub (const CFontStub& _src) : CFontStub() { *this = _src; }
CFontStub:: CFontStub (CFontStub&& _victim) : CFontStub() { *this = _victim; }
CFontStub::~CFontStub (void) {}

/////////////////////////////////////////////////////////////////////////////
const
LOGFONT&    CFontStub::Raw (void) const { return this->m_log; }
LOGFONT&    CFontStub::Raw (void)       { return this->m_log; }

/////////////////////////////////////////////////////////////////////////////

CFontStub&  CFontStub::operator = (const CFontStub& _src) { *this << _src.Raw(); return *this; }
CFontStub&  CFontStub::operator = (CFontStub&& _victim) { *this = (const CFontStub&)_victim; return *this; }
CFontStub&  CFontStub::operator <<(const LOGFONT& _log) {  this->Raw() = _log; return *this; }

CFontStub::operator const LOGFONT& (void) const { return this->Raw(); }
CFontStub::operator       LOGFONT& (void)       { return this->Raw(); }
#endif
/////////////////////////////////////////////////////////////////////////////

CFonts:: CFonts (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CFonts::~CFonts (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&  CFonts::Error (void) const { return this->m_error; }

err_code CFonts::GetInstalled (void) {

	this->m_error << __METHOD__ << __s_ok;

	if (this->m_installed.empty() == false)
		this->m_installed.clear();

#if (0)
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-enumfontfamiliesexa ;
#else
	// https://stackoverflow.com/questions/11253827/too-many-fonts-when-enumerating-with-enumfontfamiliesex-function ;
#if (0)
	LPITEMIDLIST  pFontList = nullptr;
#else
	CCoItemIdList pFontList;
#endif
	// https://learn.microsoft.com/en-us/windows/win32/shell/knownfolderid ; >> FOLDERID_Fonts is used below;
	this->m_error << ::SHGetKnownFolderIDList(FOLDERID_Fonts, 0, nullptr, pFontList);
	if (this->Error().Is())
		return this->Error();

	::ATL::CComPtr<IShellFolder> pFolder = nullptr;

	if (__succeeded(::SHBindToObject(nullptr, pFontList, nullptr, IID_IShellFolder, reinterpret_cast<void**>(&pFolder)))) {

		::ATL::CComPtr<IEnumIDList> pEnum = nullptr;

		const uint32_t u_flags = SHCONTF_FOLDERS | SHCONTF_NONFOLDERS | SHCONTF_INCLUDEHIDDEN | SHCONTF_INIT_ON_FIRST_NEXT;
		// https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-ishellfolder-enumobjects ;
		if (__succeeded(pFolder->EnumObjects(nullptr, u_flags, &pEnum))) {

			ULONG uFetched = 0;
			STRRET s_result = {0};
			t_char t_buffer[_MAX_PATH] = {0};
#if (0)
			LPITEMIDLIST  pFile = nullptr;
			while (__s_ok == pEnum->Next(1, pFile, &uFetched)) {

				// https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/ne-shobjidl_core-_shgdnf ;
				// https://learn.microsoft.com/en-us/windows/win32/shell/folder-info ;

				if (__succeeded(pFolder->GetDisplayNameOf(pFile, SHGDN_NORMAL, &s_result))) {
					if (__succeeded(::StrRetToBuf(&s_result, pFontList, t_buffer, sizeof(t_buffer)))) {

						try {
							this->m_installed.push_back(CString(t_buffer));
						} catch (const ::std::bad_alloc&) { this->m_error << __e_no_memory; }
					}
				}
				::CoTaskMemFree(pFile);
			}
#else
			do {
				CCoItemIdList pFile;
				this->m_error << pEnum->Next(1, pFile, &uFetched);
				if (true == this->Error() || false == pFile.Is_valid()) // in case when the next item does not exist must be handled also;
					break;

				this->m_error << pFolder->GetDisplayNameOf(pFile, SHGDN_NORMAL, &s_result);
				if (true == this->Error())
					break;

				this->m_error << ::StrRetToBuf(&s_result, pFontList, t_buffer, sizeof(t_buffer));
				if (true == this->Error())
					break;

				try {
					this->m_installed.push_back(CString(t_buffer));
				} catch (const ::std::bad_alloc&) { this->m_error << __e_no_memory; }
			
			} while (false == this->Error());
#endif
		}
	}
#if (0)
	::CoTaskMemFree(pFontList);
#endif
	if (1 < this->List().size()) {
		::std::sort(this->m_installed.begin(), this->m_installed.end());
	}
#endif
	return this->Error();
}

bool     CFonts::Has  (_pc_sz _p_name) const {
	_p_name;
	CString cs_name(_p_name); cs_name.Trim();

	if (cs_name.IsEmpty())
		return false;

	if (this->List().empty())
		return false;

	bool b_found = false;

	for (uint16_t i_ = 0; i_ < this->List().size(); i_++) {
		b_found = -1 != this->List().at(i_).Find((_pc_sz) cs_name);
		if (b_found)
			break;
	}

	return b_found;
}

const
TFntList CFonts::List (void) const { return this->m_installed; }

#if defined(_DEBUG)
CString  CFonts::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{%s%s%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s%s%s%s%s}");

	CString cs_fonts;

	for (uint32_t i_ = 0; i_ < this->List().size();		i_++) {
	
		cs_fonts += _p_sfx;
		cs_fonts += _p_pfx;
		cs_fonts += this->List().at(i_);
	}
	if (cs_fonts.IsEmpty()) {
		cs_fonts += _p_sfx;
		cs_fonts += _p_pfx;
		cs_fonts += _T("#empty");
	}
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_fonts, _p_sfx, _p_pfx); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_fonts, _p_sfx, _p_pfx); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_fonts, _p_sfx, _p_pfx); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif