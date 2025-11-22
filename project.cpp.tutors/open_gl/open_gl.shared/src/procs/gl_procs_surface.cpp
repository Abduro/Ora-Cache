/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Nov-2025 at 09:22:38.084, (UTC+4) Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' draw surface class interface implementation file;
*/
#include "gl_procs_surface.h"
#include "gl_procs_prog.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

#include "program\gl_$_cache.h"
#include "shader\gl_shd_type.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::procs;

namespace ex_ui { namespace draw { namespace open_gl { namespace procs { namespace _impl {

	uint32_t _get_unk_flag_value (const uint32_t _value) {
		_value;
		using e_clear_ops = CEraser::e_clear_ops;
		uint32_t u_unk = _value;
		
		if (!!u_unk) u_unk &= ~e_clear_ops::e_color;
		if (!!u_unk) u_unk &= ~e_clear_ops::e_depth;
		if (!!u_unk) u_unk &= ~e_clear_ops::e_stencil;

		return u_unk;
	}

	CString  _primitive_to_str (const uint32_t _prim_value) {
		CString cs_out;

		using e_line = CPrimitives::e_line;
		using e_others = CPrimitives::e_others;
		using e_triangle = CPrimitives::e_triangle;
		// it would be better to extract found value from the input argument one, but it is not for this time yet;
		if ((uint32_t)e_line::e_adjacency & _prim_value) { if (cs_out.IsEmpty() == false) cs_out += _T(";"); cs_out += _T("gl_lines_adjacency"); }
		if ((uint32_t)e_line::e_lines     & _prim_value) { if (cs_out.IsEmpty() == false) cs_out += _T(";"); cs_out += _T("gl_lines"); }
		if ((uint32_t)e_line::e_loop      & _prim_value) { if (cs_out.IsEmpty() == false) cs_out += _T(";"); cs_out += _T("gl_line_loop"); }
		if ((uint32_t)e_line::e_strip     & _prim_value) { if (cs_out.IsEmpty() == false) cs_out += _T(";"); cs_out += _T("gl_line_strip"); }
		if ((uint32_t)e_line::e_strip_adj & _prim_value) { if (cs_out.IsEmpty() == false) cs_out += _T(";"); cs_out += _T("gl_line_strip_adjacency"); }

		if ((uint32_t)e_others::e_patches & _prim_value) { if (false == cs_out.IsEmpty()) cs_out += _T(";"); cs_out += _T("gl_patches"); }
		if ((uint32_t)e_others::e_points  & _prim_value) { if (false == cs_out.IsEmpty()) cs_out += _T(";"); cs_out += _T("gl_points"); }

		if ((uint32_t)e_triangle::e_adjacency & _prim_value) { if (false == cs_out.IsEmpty()) cs_out += _T(";"); cs_out += _T("gl_triangles_adjacency"); }
		if ((uint32_t)e_triangle::e_fan       & _prim_value) { if (false == cs_out.IsEmpty()) cs_out += _T(";"); cs_out += _T("gl_triangle_fan"); }
		if ((uint32_t)e_triangle::e_strip     & _prim_value) { if (false == cs_out.IsEmpty()) cs_out += _T(";"); cs_out += _T("gl_triangle_strip"); }
		if ((uint32_t)e_triangle::e_strip_adj & _prim_value) { if (false == cs_out.IsEmpty()) cs_out += _T(";"); cs_out += _T("gl_triangle_strip_adjacency"); }
		if ((uint32_t)e_triangle::e_triangles & _prim_value) { if (false == cs_out.IsEmpty()) cs_out += _T(";"); cs_out += _T("gl_triangles"); }

		if (true == cs_out.IsEmpty())
			cs_out.Format(_T("#undef value (%d)"), _prim_value);

		return  cs_out;
	}

}}}}}
using namespace _impl;

static _pc_sz erase_fun_names[] = {
	_T("glClear"), _T("glClearColor"), _T("glClearDepthf"), _T("glClearStencil")
};

enum class e_erase_fun_ndx : uint32_t {
	e_all = 0x0, e_clr = 0x1, e_depth = 0x2, e_stencil = 0x3
};

CEraser:: CEraser (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}
// https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glClear.xml ;
err_code CEraser::All (const uint32_t _u_mask) {
	_u_mask;
	/* Possible error code(s):
	GL_INVALID_VALUE : '_u_mask' contains a bit that is not pre-defined one;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfnAll p_fun = reinterpret_cast<pfnAll>(CBase::Get(erase_fun_names[(uint32_t)e_erase_fun_ndx::e_all]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_mask);

	const uint32_t u_result = CErr_ex().Get_code();

	switch(u_result) {
	case GL_INVALID_VALUE : {
		const uint32_t u_unk = _get_unk_flag_value(_u_mask);
		CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_u_mask' has unknown flag value (%u)"), u_unk); } break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glClearColor.xml ;
// https://learn.microsoft.com/en-us/windows/win32/opengl/glclearcolor ;
err_code CEraser::Clr (const float _r, const float _g, const float _b, const float _a) {
	_r; _g; _b; _a;
	CBase::m_error << __METHOD__ << __s_ok;

	pfnClr p_fun = reinterpret_cast<pfnClr>(CBase::Get(erase_fun_names[(uint32_t)e_erase_fun_ndx::e_clr]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_r, _g, _b, _a);

	const uint32_t u_err_code = CErr_ex().Get_code();

	if (!!u_err_code) {
		CString cs_rgba; cs_rgba.Format(_T("rgba:{%s|%s|%s|%s}"),
			TString().Float(_r, t_fmt_spec::e_decimal, _T("%.2f")),
			TString().Float(_g, t_fmt_spec::e_decimal, _T("%.2f")),
			TString().Float(_b, t_fmt_spec::e_decimal, _T("%.2f")),
			TString().Float(_a, t_fmt_spec::e_decimal, _T("%.2f"))
		);
		CBase::m_error << (err_code) TErrCodes::eExecute::eInternal = TString().Format(_T("__e_int: err_code = %u; clr = %s"), u_err_code, (_pc_sz) cs_rgba);
	}
	return CBase::Error();
}

err_code CEraser::Depth (const float _f_z) {
	_f_z;
	CBase::m_error << __METHOD__ << __s_ok;

	pfnDepth p_fun = reinterpret_cast<pfnDepth>(CBase::Get(erase_fun_names[(uint32_t)e_erase_fun_ndx::e_depth]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_f_z);

	const uint32_t u_err_code = CErr_ex().Get_code();

	if (!!u_err_code)
		CBase::m_error << (err_code) TErrCodes::eExecute::eInternal = TString().Format(_T("__e_int: err_code = %u; z_value = %s"), u_err_code, TString().Float(_f_z));

	return CBase::Error();
}

err_code CEraser::Stencil (const uint32_t _u_bits) {
	_u_bits;
	CBase::m_error << __METHOD__ << __s_ok;

	pfnStencil p_fun = reinterpret_cast<pfnStencil>(CBase::Get(erase_fun_names[(uint32_t)e_erase_fun_ndx::e_stencil]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_bits);

	const uint32_t u_err_code = CErr_ex().Get_code();

	if (!!u_err_code)
		CBase::m_error << (err_code) TErrCodes::eExecute::eInternal = TString().Format(_T("__e_int: err_code = %u; '_u_bits' = %u"), u_err_code, _u_bits);

	return CBase::Error();
}

err_code CEraser::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(erase_fun_names); i_++) {
		if (nullptr == CBase::Get(erase_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

TEraserProcs&  ::__get_eraser_procs (void) {
	static TEraserProcs procs;
	static bool b_loaded = false;

	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
			__trace_err_2(_T("%s;\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
			b_loaded = true;
	}
	return procs;
}

/////////////////////////////////////////////////////////////////////////////

CString CPrimitives::To_str (const uint32_t _prom_id) { return _primitive_to_str(_prom_id);}

/////////////////////////////////////////////////////////////////////////////

static _pc_sz render_fun_names[] = {
	_T("glDrawArrays")
};

enum class e_render_fun_ndx : uint32_t {
	e_arrays = 0x0
};

CRenderer:: CRenderer (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

err_code CRenderer::DrawArrays (const uint32_t _prog_id, const uint32_t _u_mode, const uint32_t _u_start_ndx, const uint32_t _u_count) {
	_u_mode; _u_start_ndx; _u_count;
	/* Possible error codes:
	GL_INVALID_ENUM      : '_u_mode' has value that is not an accepted for the mode;
	GL_INVALID_OPERATION : a non-zero buffer object name is bound to an enabled array and the buffer object's data store is currently mapped;
	GL_INVALID_OPERATION : a geometry shader is active and mode is incompatible with the input primitive type of the geometry shader in the currently installed program object;
	GL_INVALID_VALUE     : '_u_count' has negative value;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	if (0 == _prog_id)
		return CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: '_prog_id' (%u) is invalid"), _prog_id);

	pfnDrawArrays p_fun = reinterpret_cast<pfnDrawArrays>(CBase::Get(render_fun_names[(uint32_t)e_render_fun_ndx::e_arrays]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_mode, _u_start_ndx, _u_count);
	const
	uint32_t u_err_code = CErr_ex().Get_code();

	switch (u_err_code) {
	case GL_INVALID_ENUM : CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_enum: %s (%d)"), (_pc_sz) _primitive_to_str(_u_mode), _u_mode); break;
	case GL_INVALID_OPERATION : {
		bool b_geo_shader = false;
		::std::vector<$Type> $_types;
		if (__failed(T$Cache::Attached(_prog_id, $_types, CBase::m_error))) {}
		else if ($_types.empty() == false) {
			for (size_t i_ = 0; i_ < $_types.size(); i_++) {
				b_geo_shader = $Type::e_geometry == $_types[i_];
				if (b_geo_shader)
					break;
			}
			if (b_geo_shader)
			     CBase::m_error << (err_code)TErrCodes::eExecute::eState = TString().Format(_T("#__e_inv_mode: %s (%d) is not accepted when geometry shader is active"), (_pc_sz) _primitive_to_str(_u_mode), _u_mode);
			else CBase::m_error << (err_code)TErrCodes::eExecute::eState = TString().Format(_T("#__e_inv_oper: vertex buffer is mapped")); // this error should be more accurate;
		}
		else {} // this condition can cannot occur;
	} break;
	case GL_INVALID_VALUE :
		if (static_cast<int32_t>(_u_count) < 0) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: '_u_count' (%d) is invalid"), _u_count); break;
	default:
		if (!!u_err_code) // this is the good idea to check error code anyway, otherwise the error may throw the error code that is not specified in docs;
			CBase::m_error <<__e_fail = TString().Format(_T("#__e_undef: error code (%d)"),  u_err_code);
	}

	return CBase::Error();
}

err_code CRenderer::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(render_fun_names); i_++) {
		if (nullptr == CBase::Get(render_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

TRenderProcs&  ::__get_render_procs (void) {
	static TRenderProcs procs;
	static bool b_loaded = false;

	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
			__trace_err_2(_T("%s;\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
			b_loaded = true;
	}
	return procs;
}