/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-May-2026 at 00:33:57.629, UTC+4, Batumi, Tuesday;
	This is OpenGL ver.1.1 common basic interface implementation file;
*/
#include "gl_procs_basic.h"

using namespace open_gl::procs::ver_1_1;

typedef ::std::map<CString, PROC> TProcCache;  // the key is the procedure name, the value is the pointer to the address of procefure function/method;
static  TProcCache g_cached;

#pragma region cls::CBasic{}

static _pc_sz p_err_no_mem = _T("#__e_no_mem: proc name: '%s'");

CBasic::CBasic (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CBasic::Error (void) const { return this->m_error; }
PROC    CBasic::Get (_pc_sz _p_proc_name) {
	_p_proc_name;
	if (nullptr == _p_proc_name || 0 == ::_tcslen(_p_proc_name)) {
		this->m_error <<__METHOD__<< __e_inv_arg; return nullptr;
	}
	if (g_cached.empty() == false) {
		TProcCache::const_iterator found_ = g_cached.find(_p_proc_name);
		if (found_ != g_cached.end())
			return found_->second;
	}

	CStringA cs_ansi(_p_proc_name);
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglgetprocaddress?source=docs ;
	PROC p_proc = ::wglGetProcAddress(cs_ansi.GetString());
	if ( p_proc ) {
		try {
			g_cached.insert(::std::make_pair(CString(_p_proc_name), p_proc));
		}
		catch (const ::std::bad_alloc&) {
			this->m_error <<__METHOD__<< __e_no_memory = TString().Format(p_err_no_mem, _p_proc_name);
		}
	}
	// https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions#Windows ;
	else if ( 0 == p_proc || (void*)0x1 == p_proc || (void*)0x2 == p_proc || (void*)0x3 == p_proc || (void*)-1 == p_proc )
	{		// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya ;
		HMODULE h_module = ::LoadLibrary(_T("opengl32.dll"));
		if (0 ==h_module)
			(this->m_error <<__METHOD__).Last();
		else {
			// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress ;
			p_proc = ::GetProcAddress(h_module, cs_ansi.GetString());
			if (0 == p_proc) {
				this->m_error.Last(); this->m_error = TString().Format(_T("Getting the address of '%s' failed"), _p_proc_name);
			} else {
				try {
					g_cached.insert(::std::make_pair(CString(_p_proc_name), p_proc));
				}
				catch (const ::std::bad_alloc&) {
					this->m_error <<__METHOD__<< __e_no_memory = TString().Format(p_err_no_mem, _p_proc_name);
				}
			}
		}
	}
	else {
		(this->m_error <<__METHOD__ = ERROR_INVALID_FUNCTION) = TString().Format(_T("the proc '%s' is not found"), _p_proc_name);
	}
	return p_proc;
}

#pragma endregion