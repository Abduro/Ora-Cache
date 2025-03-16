/*
	Created by Tech_dog (ebontrop@gmail.com) on 3-Oct-2022 at 00:27:17.7595048, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack Windows system console font wrapper interface implementation file;
*/
#include "console.font.h"

using namespace shared::console;

/////////////////////////////////////////////////////////////////////////////

CFont:: CFont (void) : m_info{sizeof(ConFntInfoEx), 0} { m_error >> __CLASS__ << __METHOD__; }
CFont:: CFont (const CFont& _ref) : CFont() { *this = _ref; }
CFont:: CFont (_pc_sz _lp_sz_face_name) : CFont() { *this << _lp_sz_face_name; }
CFont::~CFont (void) {}

/////////////////////////////////////////////////////////////////////////////
const
ConFntInfoEx& CFont::Get(void) const
{
	m_error << __METHOD__ << S_OK;

	if (true == this->Is())
		return this->m_info;

	HANDLE h_out = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE == h_out) {
		m_error = __LastErrToHresult();
		return this->m_info;
	}
	// https://learn.microsoft.com/en-us/windows/console/getcurrentconsolefontex
	if (FALSE == ::GetCurrentConsoleFontEx(h_out, false, &this->m_info))
		m_error = __LastErrToHresult();	

	return this->m_info;
}

HRESULT   CFont::Set (LPCTSTR _lp_sz_face_name)
{
	m_error << __METHOD__ << S_OK;

	if (nullptr == _lp_sz_face_name || 0 == ::_tcslen(_lp_sz_face_name))
		return (m_error << E_INVALIDARG);

	if (false == this->Is())
	{
		this->Get();
		if (false == this->Is())
			return (this->Error());
	}

//	const DWORD dw_length = 32;
	ConFntInfoEx info = this->Get();
	info.FontFamily   = TMPF_TRUETYPE; // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-textmetricw ;
//	https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strcpy-s-wcscpy-s-mbscpy-s ;
	const errno_t e_error = ::_tcscpy_s(info.FaceName, _countof(info.FaceName), _lp_sz_face_name/*, ::_tcslen(_lp_sz_face_name)/sizeof(t_char)*/);
	if (S_OK != e_error)
		return (this->m_error << E_INVALIDARG);

	HANDLE h_out = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE == h_out) {
		m_error << __LastErrToHresult();
		return (m_error);
	}
	// https://learn.microsoft.com/en-us/windows/console/setcurrentconsolefontex
	const BOOL b_result = ::SetCurrentConsoleFontEx(h_out, false, &info);
	if (FALSE == b_result)
		m_error << __LastErrToHresult();
	else
		this->Raw() = info;

	return  m_error;
}

/////////////////////////////////////////////////////////////////////////////

TErrorRef CFont::Error (void) const { return m_error; }

bool      CFont::Is    (void) const {

	const bool b_result = (
		this->Raw().cbSize == sizeof(ConFntInfoEx) &&
			nullptr != this->Raw().FaceName &&
				0 != ::_tcslen(this->Raw().FaceName) 
				);
	return b_result;
}

UINT      CFont::Size  (void) const {
	m_error << __METHOD__ << __s_ok;
	// https://docs.microsoft.com/en-us/windows/console/reading-input-buffer-events
	// https://docs.microsoft.com/en-us/windows/console/getstdhandle
	HANDLE h_out = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE == h_out) {
		m_error  = __LastErrToHresult();
		return (0);
	}
	// https://docs.microsoft.com/en-us/windows/console/getconsolefontsize
	CONSOLE_FONT_INFO fnt_inf = {0};
	if (FALSE == ::GetCurrentConsoleFont(h_out, FALSE, &fnt_inf)) {
		m_error  = __LastErrToHresult();
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
CFont&   CFont::operator <<(LPCTSTR _lp_sz_face_name) { this->Set(_lp_sz_face_name); return *this; }

/////////////////////////////////////////////////////////////////////////////

CFont::operator bool (void) const { return this->Is(); }
CFont::operator const ConFntInfoEx& (void) const { return this->Raw(); }
CFont::operator       ConFntInfoEx& (void)       { return this->Raw(); }