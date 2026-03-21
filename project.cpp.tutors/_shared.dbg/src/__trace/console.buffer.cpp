/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2026 at 12:10:13.186, UTC+4, Batumi, Saturday;
	This is system console screen buffer wrapper interface implementation file;
*/
#include "console.buffer.h"
#include "shared.preproc.h"

using namespace shared::console;

#pragma region cls::CScreenBuffer{}

CScreenBuffer:: CScreenBuffer (void) : m_info{0} { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_not_inited"); }
CScreenBuffer::~CScreenBuffer (void) {}

err_code CScreenBuffer::Clear (const t_char _symbol/* = _T(' ')*/) {
	_symbol;
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Get()))
		return this->Error();

	// https://learn.microsoft.com/en-us/windows/console/fillconsoleoutputcharacter ;
	dword d_written = 0;
	if (false == !!FillConsoleOutputCharacter(__out_handle, _symbol, (*this)().dwSize.X * (*this)().dwSize.Y, {0, 0}, &d_written))
		return this->m_error.Last();

	// https://learn.microsoft.com/en-us/windows/console/setconsolecursorposition ;
	if (false == !!::SetConsoleCursorPosition(__out_handle, {0,0}))
		this->m_error.Last();

	return this->Error();
}

TError&  CScreenBuffer::Error (void) const { return this->m_error; }

err_code CScreenBuffer::Get (void) {
	this->m_error <<__METHOD__<<__s_ok;
			
	// https://learn.microsoft.com/en-us/windows/console/getconsolescreenbufferinfo ;

	if (0 == ::GetConsoleScreenBufferInfo (__out_handle, &this->m_info))
		this->m_error.Last();

	return this->Error();
}

err_code CScreenBuffer::Set (void) {

	COORD n_size =  m_info.dwSize;
	n_size.X *= 2;
			
	::SetConsoleScreenBufferSize(__out_handle, n_size);
	return this->Error();
}

CScreenBuffer::operator const TScrBufInfo& (void) const { return this->m_info; }
CScreenBuffer::operator       TScrBufInfo& (void)       { return this->m_info; }

TScrBufInfo&   CScreenBuffer::operator ()  (void) { this->Get(); return this->m_info; }

#pragma endregion
#pragma region cls::CScreenBufferEx{}

CScreenBufferEx::CScreenBufferEx (void) : m_info_ex{0} {
	this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_not_inited"); this->m_info_ex.cbSize = sizeof(TScrBufInfoEx);
}

TError&  CScreenBufferEx::Error(void) const { return this->m_error; }

err_code CScreenBufferEx::Get (void) {
	this->m_error >>__METHOD__<<__s_ok;
			
	// https://learn.microsoft.com/en-us/windows/console/getconsolescreenbufferinfoex ;
	if (0 == ::GetConsoleScreenBufferInfoEx (__out_handle, &this->m_info_ex))
		this->m_error.Last();

	return this->Error();
}

err_code CScreenBufferEx::Set (void) {
	// https://learn.microsoft.com/en-us/windows/console/setconsolescreenbufferinfoex ;
	::SetConsoleScreenBufferInfoEx(__out_handle, &m_info_ex);
	return this->Error();
}

const
TScrBufInfoEx& CScreenBufferEx::Ref (void) const { return this->m_info_ex; }
TScrBufInfoEx& CScreenBufferEx::Ref (void)       { return this->m_info_ex; }

CScreenBufferEx::operator const TScrBufInfoEx& (void) const { return this->Ref(); }
CScreenBufferEx::operator       TScrBufInfoEx& (void)       { return this->Ref(); }

TScrBufInfoEx& CScreenBufferEx::operator ()(void) { this->Get(); return this->m_info_ex; }

#pragma endregion