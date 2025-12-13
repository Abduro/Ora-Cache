/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Oct-2025 at 14:25:53.097, (UTC+4), Batumi, Saturday;
	This is Ebo Pack OpenGL functions' loader base interface implementation file;
*/
#include "gl_procs_base.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::procs;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl_2 { void __warning_lnk_4006 (void) {}}}}}

procs::CBase:: CBase (void) { this->m_error >>__CLASS__<<__METHOD__<< __e_not_inited; }

err_code procs::CBase::Erase (void) {

	this->m_error <<__METHOD__<<__s_ok;

	if (this->m_cached.empty() == false) {
		this->m_cached.clear();
		this->m_error <<__e_not_inited;
	}
	return __s_ok; // it is supposed the possible calling clear() function will not cause the memory related error; 
}

TError&  procs::CBase::Error (void) const { return this->m_error; }

PROC procs::CBase::Get (_pc_sz _p_proc_name) {
	_p_proc_name;
	if (nullptr == _p_proc_name || 0 == ::_tcslen(_p_proc_name)) {
		this->m_error <<__METHOD__<< __e_inv_arg; return nullptr;
	}
	if (this->m_cached.empty() == false) {
		TProcCache::const_iterator found_ = this->m_cached.find(_p_proc_name);
		if (found_ != this->m_cached.end())
			return found_->second;
	}

	CStringA cs_ansi(_p_proc_name);
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglgetprocaddress?source=docs ;
	PROC p_proc = ::wglGetProcAddress(cs_ansi.GetString());
	if ( p_proc ) {
		try {
			this->m_cached.insert(::std::make_pair(CString(_p_proc_name), p_proc));
		}
		catch (const ::std::bad_alloc&) {
			this->m_error <<__METHOD__<< __e_no_memory;
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
			}
		}
	}
	else {
		this->m_error <<__METHOD__<< (err_code) TErrCodes::eExecute::eFunction = TString().Format(_T("the proc '%s' is not found"), _p_proc_name);
	}
	return p_proc;
}

err_code procs::CBase::Get_all (void) { return __e_not_impl; }

CString  procs::CBase::Print (void) const {

	if (this->m_cached.empty()) {
		return CString(_T("#empty"));
	}
	
	CString cs_out;

	for (TProcCache::const_iterator it_ = this->m_cached.begin(); it_ != this->m_cached.end(); ++it_) {
		cs_out += _T("\t");
		cs_out += it_->first;
		cs_out += _T(";\n");
	}

	return cs_out;
}