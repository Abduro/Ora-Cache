/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Sep-2025 at 13:13:58.859, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' procedures loader wrapper interface implementation file; 
*/
#include "gl_procs.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::procs;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl_1 { void __warning_lnk_4006 (void) {}}}}}

CBase:: CBase (void) { this->m_error >>__CLASS__<<__METHOD__<< __e_not_inited; }

TError&  CBase::Error (void) const { return this->m_error; }

PROC CBase::Get (_pc_sz _p_proc_name) {
	_p_proc_name;
	if (nullptr == _p_proc_name || 0 == ::_tcslen(_p_proc_name)) {
		this->m_error <<__METHOD__<< __e_inv_arg; return nullptr;
	}
	TProcCache::const_iterator found_ = this->m_cached.find(_p_proc_name);
	if (found_ != this->m_cached.end())
		return found_->second;

	CStringA cs_ansi(_p_proc_name);
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglgetprocaddress?source=docs ;
	PROC p_proc = ::wglGetProcAddress(cs_ansi.GetString());
	if ( p_proc ) {
		try {
			this->m_cached.insert(::std::make_pair(CString(_p_proc_name), p_proc));
		}
		catch (const ::std::bad_alloc&) {
			this->m_error << __e_no_memory;
		}
	}
	// https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions#Windows ;
	else if ( 0 == p_proc || (void*)0x1 == p_proc || (void*)0x2 == p_proc || (void*)0x3 == p_proc || (void*)-1 == p_proc )
	{		// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya ;
		HMODULE h_module = ::LoadLibrary(_T("opengl32.dll"));
		if (0 ==h_module)
			this->m_error.Last();
		else {
			// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress ;
			p_proc = ::GetProcAddress(h_module, cs_ansi.GetString());
			if (0 == p_proc) {
				this->m_error.Last(); this->m_error = TString().Format(_T("Get address of '%s' failed"), _p_proc_name);
			}
		}
	}
	else {
		this->m_error << (err_code) TErrCodes::eExecute::eFunction = TString().Format(_T("the proc '%s' is not found"), _p_proc_name);
	}
	return p_proc;
}

err_code CBase::Get_all (void) { return __e_not_impl; }

CString  CBase::Print (void) const {

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

/////////////////////////////////////////////////////////////////////////////

CContext:: CContext (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

int32_t CContext::ChoosePxFormatArb (HDC _h_dc, const int* _p_atts_i, const float* _p_atts_f, uint32_t _n_max_formats, int* _p_formats, uint32_t* _p_fmt_count) {
	_h_dc; _p_atts_i; _p_atts_f; _n_max_formats; _p_formats; _p_fmt_count;
	CBase::m_error << __METHOD__ << __s_ok;

	int32_t n_result = 0;

	pfn_ChoosePxFormatArb p_fun = reinterpret_cast<pfn_ChoosePxFormatArb>(CBase::Get(_T("wglChoosePixelFormatARB")));
	if (nullptr == p_fun)
		return n_result; // needs to be figured out of what result should be returned in case of failure;

	n_result = p_fun(_h_dc, _p_atts_i, _p_atts_f, _n_max_formats, _p_formats, _p_fmt_count);
	return n_result;
}

HGLRC   CContext::CreateCtxAttsArb  (HDC _h_dc, HGLRC _h_shared_ctx, const int* p_att_lst) {
	_h_dc; _h_shared_ctx; p_att_lst;
	CBase::m_error << __METHOD__ << __s_ok;

	HGLRC h_render = nullptr;

	pfn_CreateCtxAttsArb p_fun = reinterpret_cast<pfn_CreateCtxAttsArb>(CBase::Get(_T("wglCreateContextAttribsARB")));
	if (nullptr == p_fun)
		return h_render;

	h_render = p_fun(_h_dc, _h_shared_ctx, p_att_lst);

	return h_render;
}

int32_t CContext::SwapIntervalExt   (const int _n_interval) {
	_n_interval;
	CBase::m_error << __METHOD__ << __s_ok;

	int32_t n_result = 0;

	pfn_SwapIntervalExt p_fun = reinterpret_cast<pfn_SwapIntervalExt>(CBase::Get(_T("wglSwapIntervalEXT")));
	if (nullptr == p_fun)
		return n_result; // needs to be figured out of what result should be returned in case of failure;

	n_result = p_fun(_n_interval);
	return n_result;
}

err_code CContext::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	static _pc_sz fn_names[] = {
		_T("wglChoosePixelFormatARB"), _T("wglCreateContextAttribsARB"), _T("wglSwapIntervalEXT")
	};

	for (uint32_t i_ = 0; i_ < _countof(fn_names); i_++) {
		if (nullptr == CBase::Get(fn_names[i_]))
			break;
	}

	return CBase::Error();
}