/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Oct-2025 at 16:12:30.810, (UTC+4), Batumi, Saturday;
	This is Ebo Pack OpenGL viewport functions' loader interface implementation file;
*/
#include "gl_procs_view.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::procs;

static _pc_sz depth_fun_names[] = {
	_T("glDepthFunc"), _T("glDepthRange"), _T("glDepthRangef"),
};

enum class e_depth_fun_ndx : uint32_t {
	e_depth_fun = 0x0, e_range_d = 0x1, e_range_f = 0x2,
};

CDepth::CDepth (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDepthFunc.xhtml ;
// https://learn.microsoft.com/en-us/windows/win32/opengl/gldepthfunc ;
err_code CDepth::SetCompareRule (const uint32_t _u_rule) {
	_u_rule;
	/* Possible error codes:
	GL_INVALID_ENUM : '_u_rule' is not an acceptable value;
	GL_INVALID_OPERATION : this function was called between a call to glBegin and the corresponding call to glEnd;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Compare p_fun = reinterpret_cast<pfn_Compare>(CBase::Get(depth_fun_names[(uint32_t)e_depth_fun_ndx::e_depth_fun]));
	if (nullptr == p_fun)
		return CBase::Error();

	switch (CErr_ex().Get_last(false)) {
	case GL_INVALID_ENUM: { CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_enum: comparison rule (%u) is not acceptable"), _u_rule); } break;
	case GL_INVALID_OPERATION: { CBase::m_error << (err_code)TErrCodes::eExecute::eState = _T("#__e_inv_oper: inapplicable state for execution"); } break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDepthRange.xhtml ;
// https://learn.microsoft.com/en-us/windows/win32/opengl/gldepthrange ;
err_code CDepth::SetRange_D (const double _d_near, const double _d_far) {
	_d_near; _d_far;
	/* Possible error codes:
	GL_INVALID_OPERATION : this function was called between a call to glBegin and the corresponding call to glEnd;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Range_D p_fun = reinterpret_cast<pfn_Range_D>(CBase::Get(depth_fun_names[(uint32_t)e_depth_fun_ndx::e_range_d]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_d_near, _d_far);
	// https://softwareengineering.stackexchange.com/questions/219351/state-or-status-when-should-a-variable-name-contain-the-word-state-and-w ;
	switch (CErr_ex().Get_last(false)) {
	case GL_INVALID_OPERATION: {
			CBase::m_error << (err_code)TErrCodes::eExecute::eState = _T("#__e_inv_oper: inapplicable state for execution");
		} break;
	default:;
	}

	return CBase::Error();
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/gldepthrange ;
err_code CDepth::SetRange_F (const float _d_near, const float _d_far) {
	_d_near; _d_far;
	/* Possible error codes:
	GL_INVALID_OPERATION : this function was called between a call to glBegin and the corresponding call to glEnd;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Range_F p_fun = reinterpret_cast<pfn_Range_F>(CBase::Get(depth_fun_names[(uint32_t)e_depth_fun_ndx::e_range_f]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_d_near, _d_far);
	// https://softwareengineering.stackexchange.com/questions/219351/state-or-status-when-should-a-variable-name-contain-the-word-state-and-w ;
	switch (CErr_ex().Get_last(false)) {
	case GL_INVALID_OPERATION: {
			CBase::m_error << (err_code)TErrCodes::eExecute::eState = _T("#__e_inv_oper: inapplicable state for execution");
		} break;
	default:;
	}

	return CBase::Error();
}

err_code CDepth::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(depth_fun_names); i_++) {
		if (nullptr == CBase::Get(depth_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

TDepthProcs&  ::__get_depth_procs (void) {
	static TDepthProcs procs;
	static bool b_loaded = false;
	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
		    __trace_err_2(_T("%s\n;"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
		    b_loaded = true;
	}
	return procs;
}

/////////////////////////////////////////////////////////////////////////////

static _pc_sz view_fun_names[] = {
	_T("glPolygonOffset"), _T("glViewport")
};

enum class e_view_fun_ndx : uint32_t {
	e_offset = 0x0, e_set = 0x1, 
};

CViewport:: CViewport (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glPolygonOffset.xhtml ;
// https://learn.microsoft.com/en-us/windows/win32/opengl/glpolygonoffset ;
err_code CViewport::Offset (const float _f_factor, const float _f_unit) {
	_f_factor; _f_unit;

	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Offset p_fun = reinterpret_cast<pfn_Offset>(CBase::Get(view_fun_names[(uint32_t)e_view_fun_ndx::e_offset]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_f_factor, _f_unit);

	return CBase::Error();
}

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glViewport.xhtml ;
err_code CViewport::Set (const int32_t _x, const int32_t _y, const uint32_t _u_width, const uint32_t _u_height) {
	_x; _y; _u_width; _u_height;
	/* Possible error code(s):
	GL_INVALID_VALUE : either '_u_width' or '_u_height' is negative;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Set p_fun = reinterpret_cast<pfn_Set>(CBase::Get(view_fun_names[(uint32_t)e_view_fun_ndx::e_set]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_x, _y, _u_width, _u_height);

	switch (CErr_ex().Get_last(false)) {
	case GL_INVALID_VALUE: {
			if (0 == _u_height) CBase::m_error << __e_inv_arg = _T("#__e_inv_val: '_u_height' is 0 (zero)");
			if (0 == _u_width ) CBase::m_error << __e_inv_arg = _T("#__e_inv_val: '_u_width' is 0 (zero)");
		} break;
	default:;
	}
	
	return CBase::Error();
}

err_code CViewport::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(view_fun_names); i_++) {
		if (nullptr == CBase::Get(view_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

TViewProcs&  ::__get_view_procs (void) {
	static TViewProcs procs;
	static bool b_loaded = false;
	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
		    __trace_err_2(_T("%s\n;"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
		    b_loaded = true;
	}
	return procs;
}