/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Sep-2022 at 10:08:55.9180723, UTC+7, Novosibirsk, Friday;
	This is MS Windows console generic definition implementation file.
	-----------------------------------------------------------------------------
	The code is based on Pulsepay WWS Server Light Console class declared on 22-Dec-2013 at 12:49:13pm, GMT+4, Saint-Petersburg, Sunday;
*/
#include "console.defs.h"

using namespace shared::console;

namespace shared { namespace console { namespace _impl { void __warning_lnk_4221 (void) {}}}}

#pragma region cls::CHandles{}

using e_index = CHandles::e_index;

CHandles:: CHandles (void) : m_handles{0} {}
CHandles::~CHandles (void) { this->On_close(); }

void* CHandles::Get (const e_index _e_ndx) const {
	_e_ndx;
	if (e_index::e_input  == _e_ndx) return this->m_handles[_e_ndx];
	if (e_index::e_output == _e_ndx) return this->m_handles[_e_ndx];
	if (e_index::e_error  == _e_ndx) return this->m_handles[_e_ndx];

	return nullptr;
}

void CHandles::On_close (void) {
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/get-osfhandl ;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fclose-fcloseall ;
#if (0)
	for (uint32_t i_ = 0; i_ < _countof(this->m_streams); i_++) {
		if (nullptr == this->m_streams[i_])
			continue;
		if (0 != ::fclose(this->m_streams[i_])) {
			CString cs_stream;

			if (0 == i_) cs_stream = _T("std_input_stream");
			if (1 == i_) cs_stream = _T("std_output_stream");
			if (2 == i_) cs_stream = _T("std_err_stream");

			this->m_error << __e_fail = TString().Format(_T("Close '%s' is failed"), (_pc_sz) cs_stream); // it saves the last error only;
		}
		else
			this->m_streams[i_] = nullptr;
	}
#endif
	// ::setvbuf() is used for setting the stream operation(s); it is not required to manage these buffers due to they are opened with _IONBF option;
}

void CHandles::Set (void) {

	// (1) sets output/read handle
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/open-osfhandle ;
	{
		this->m_handles[0] = ::GetStdHandle(STD_INPUT_HANDLE);
		const intptr_t cin_ = reinterpret_cast<intptr_t>(this->m_handles[0]);
		const INT input_ = ::_open_osfhandle(cin_, _O_TEXT );
		FILE* p_file_in = ::_fdopen(input_, "r");

		::setvbuf( p_file_in, 0, _IONBF, 0 ); // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/setvbuf ;
	}
	// (2) sets input/write handle
	{
		this->m_handles[1]  = ::GetStdHandle(STD_OUTPUT_HANDLE);
		const intptr_t out_ = reinterpret_cast<intptr_t>(this->m_handles[1]);
		const INT output_ = ::_open_osfhandle(out_, _O_TEXT );
		FILE* p_file_out = ::_fdopen(output_, "w");

		::setvbuf( p_file_out, 0, _IONBF, 0 );
	}
	// (3) sets error handle
	{
		this->m_handles[2] = ::GetStdHandle(STD_ERROR_HANDLE);
		const intptr_t err_ = reinterpret_cast<intptr_t>(this->m_handles[2]);
		const INT error_ = ::_open_osfhandle(err_, _O_TEXT );
		FILE* p_file_err = ::_fdopen(error_, "w");

		::setvbuf( p_file_err, 0, _IONBF, 0 );
	}

}

void* CHandles::Err (void) { return ::GetStdHandle(STD_ERROR_HANDLE);  }
void* CHandles::In  (void) { return ::GetStdHandle(STD_INPUT_HANDLE);  }
void* CHandles::Out (void) { return ::GetStdHandle(STD_OUTPUT_HANDLE); }

#pragma endregion