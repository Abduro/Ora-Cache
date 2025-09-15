/*
	Created by Tech_dog (ebontrop@gmail.com) on 3-Oct-2022 at 00:27:17.7595048, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack Windows system console font wrapper interface implementation file;
*/
#include "console.font.h"
#include "shared.preproc.h"

using namespace shared::console;

namespace shared { namespace console {

/////////////////////////////////////////////////////////////////////////////

CFont:: CFont (void) : m_info{sizeof(ConFntInfoEx), 0} { m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CFont:: CFont (const CFont& _ref) : CFont() { *this = _ref; }
CFont::~CFont (void) {}

/////////////////////////////////////////////////////////////////////////////
const
ConFntInfoEx& CFont::Get(void) const
{
	m_error <<__METHOD__<<__s_ok;

	if (true == this->Is())
		return this->m_info;

	HANDLE h_out = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE == h_out) {
		m_error = __LastErrToHresult();
		return this->m_info;
	}
	// https://learn.microsoft.com/en-us/windows/console/getcurrentconsolefontex
	if (false == !!::GetCurrentConsoleFontEx(h_out, false, &this->m_info))
		m_error = __LastErrToHresult();	

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

/////////////////////////////////////////////////////////////////////////////

TErrorRef CFont::Error (void) const { return this->m_error; }

bool CFont::Is (void) const {

	const bool b_result = (
		this->Raw().cbSize == sizeof(ConFntInfoEx) &&
			nullptr != this->Raw().FaceName &&
				0 != ::_tcslen(this->Raw().FaceName) 
				);
	return b_result;
}

UINT CFont::Size (void) const {

	m_error << __METHOD__ << S_OK;

	// https://docs.microsoft.com/en-us/windows/console/reading-input-buffer-events ;
	// https://docs.microsoft.com/en-us/windows/console/getstdhandle ;
	HANDLE h_out = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE == h_out) {
		m_error.Last();
		return (0);
	}

	// https://docs.microsoft.com/en-us/windows/console/getconsolefontsize ;
	CONSOLE_FONT_INFO fnt_inf = {0};
	if (FALSE == ::GetCurrentConsoleFont(h_out, FALSE, &fnt_inf)) {
		m_error.Last();
		return (0);
	}
	COORD coord = ::GetConsoleFontSize(h_out, fnt_inf.nFont);
	return coord.Y;
}

const
ConFntInfoEx& CFont::Raw (void) const { return this->m_info; }
ConFntInfoEx& CFont::Raw (void)       { return this->m_info; }

/////////////////////////////////////////////////////////////////////////////

CFont&   CFont::operator = (const CFont& _ref) { this->m_error = _ref.Error(); this->Raw() = _ref.Raw(); return *this; }

/////////////////////////////////////////////////////////////////////////////

CFont::operator bool (void) const { return this->Is(); }
CFont::operator const ConFntInfoEx& (void) const { return this->Raw(); }
CFont::operator       ConFntInfoEx& (void)       { return this->Raw(); }

}}