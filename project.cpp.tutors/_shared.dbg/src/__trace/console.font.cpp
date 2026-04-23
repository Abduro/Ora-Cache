/*
	Created by Tech_dog (ebontrop@gmail.com) on 3-Oct-2022 at 00:27:17.7595048, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack Windows system console font wrapper interface implementation file;
*/
#include "console.font.h"
#include "shared.preproc.h"

using namespace shared::console;
using CFont = shared::console::CFont;

#pragma region cls::CFont{}

CFont::CFont (void) : m_info{sizeof(ConFntInfoEx), 0}, m_size{0} { m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("font info is not inited"); }
CFont::CFont (const CFont& _src) : CFont() { *this = _src; }

const
ConFntInfoEx& CFont::Get(void) {
	m_error <<__METHOD__<<__s_ok;

	if (true == this->Is())
		return this->m_info;

	if (__e_handle == __out_handle) {
		m_error.Last();
		return this->m_info;
	}
	// https://learn.microsoft.com/en-us/windows/console/getcurrentconsolefontex
	if (false == !!::GetCurrentConsoleFontEx(__out_handle, false, &this->m_info))
		m_error.Last();

	const COORD& coord = this->m_info.dwFontSize;

	this->m_size = {
		abs(-MulDiv(coord.X, GetDeviceCaps(::GetDC(0), LOGPIXELSX), 72)), // gets the font width in pixels;
		abs(-MulDiv(coord.Y, GetDeviceCaps(::GetDC(0), LOGPIXELSY), 72))  // gets the font height in pixels;
	};

	return this->m_info;
}

err_code  CFont::Set (_pc_sz _p_face_name, const int16_t _cy) {
	_p_face_name; _cy;
	this->m_error << __METHOD__ << S_OK;

	if (nullptr == _p_face_name || 0 == ::_tcslen(_p_face_name))
		return (this->m_error << __e_inv_arg);

	if (false == this->Is())
	{
		this->Get();
		if (false == this->Is())
			return (this->Error());
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-textmetricw ;

	ConFntInfoEx info = this->Get();
	info.FontFamily   = TMPF_TRUETYPE;
	info.dwFontSize.Y = _cy;

	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strcpy-s-wcscpy-s-mbscpy-s ;
	const errno_t e_error = ::_tcscpy_s(info.FaceName, _countof(info.FaceName), _p_face_name);
	if (__s_ok != e_error)
		return (this->m_error << __e_inv_arg);

	HANDLE h_out = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE == h_out) {
		return m_error.Last();
	}
	// https://learn.microsoft.com/en-us/windows/console/setcurrentconsolefontex ;
	const bool b_result = !!::SetCurrentConsoleFontEx(h_out, false, &info);
	if (false == b_result)
		m_error.Last();
	else
		this->Raw() = info;

	return this->Error();
}

TErrorRef CFont::Error (void) const { return this->m_error; }

bool CFont::Is (void) const {

	const bool b_result = (
		this->Raw().cbSize == sizeof(ConFntInfoEx) &&
			nullptr != this->Raw().FaceName &&
				0 != ::_tcslen(this->Raw().FaceName) 
				);
	return b_result;
}

const
t_size& CFont::Size (void) const {
#if (0)
	m_error << __METHOD__ << __s_ok;
	
	// https://docs.microsoft.com/en-us/windows/console/reading-input-buffer-events ;
	// https://docs.microsoft.com/en-us/windows/console/getstdhandle ;
	HANDLE h_out = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (__e_handle == h_out) {
		m_error.Last();
		return this->m_size; // returns previously set font size, can be 0 at both fields by default;
	}

	// https://docs.microsoft.com/en-us/windows/console/getconsolefontsize ;
	CONSOLE_FONT_INFO fnt_inf = {0};
	if (false == !!::GetCurrentConsoleFont(h_out, FALSE, &fnt_inf)) {
		m_error.Last();
		return this->m_size; // returns previously set font size, can be 0 at both fields by default;
	}
	COORD coord = ::GetConsoleFontSize(h_out, fnt_inf.nFont);
	this->m_size = {
		abs(-MulDiv(coord.X, GetDeviceCaps(::GetDC(0), LOGPIXELSX), 72)), // gets the font width in pixels;
		abs(-MulDiv(coord.Y, GetDeviceCaps(::GetDC(0), LOGPIXELSY), 72))  // gets the font height in pixels;
	};
#endif
	return this->m_size; // is calculated by calling CFont::Get(void);
}

const
ConFntInfoEx& CFont::Raw (void) const { return this->m_info; }
ConFntInfoEx& CFont::Raw (void)       { return this->m_info; }

CFont&   CFont::operator = (const CFont& _ref) { this->m_error = _ref.Error(); this->Raw() = _ref.Raw(); return *this; }

CFont::operator bool (void) const { return this->Is(); }
const
ConFntInfoEx& CFont::operator ()(void) const { return this->Raw(); }
ConFntInfoEx& CFont::operator ()(void)       { return this->Raw(); }

bool CFont::operator != (const CFont& _font) {
	_font;
	bool b_equal = this->Is();

	if (false == b_equal) // no sense to compare invalid font info; the input font is not checked for validity because it's not necessary;
		return b_equal;

	// the compare order is from simple condition to more complex one;
	if (b_equal) b_equal = this->Raw().nFont != _font().nFont;
	if (b_equal) b_equal = this->Raw().FontWeight != _font().FontWeight;
	if (b_equal) b_equal = false == (this->Size().cx != _font.Size().cx || this->Size().cy != _font.Size().cy); // this is for mouse move event handling;
	if (b_equal) b_equal = 0 == CString(this->Raw().FaceName).CompareNoCase(_font().FaceName);

	return b_equal;
}

t_size CFont::To_pixels (const COORD& _coord) {
	return {
		-MulDiv(_coord.X, GetDeviceCaps(::GetDC(0), LOGPIXELSX), 72), // gets the font width in pixels;
		-MulDiv(_coord.Y, GetDeviceCaps(::GetDC(0), LOGPIXELSY), 72)  // gets the font height in pixels;
	};
}

#pragma endregion