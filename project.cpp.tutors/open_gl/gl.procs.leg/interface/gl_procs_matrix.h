#ifndef _GL_PROCS_MATRIX_H_INCLUDED
#define _GL_PROCS_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-May-2026 at 16:13:11.611, UTC+4, Batumi, Wednesday;
	This is OpenGL v.1.1 matrix related function set wrapper interface declaration file;
*/
#include "gl_procs_basic.h"
#include "matrix\gl_procs_mtx.mode.h"
/*
	These procedure wrappers are espacially intended for OpenGL vers 1.1 API (aka legacy);
*/
namespace open_gl { namespace procs {
namespace ver_1_1 {

	// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetfloatv ;
	enum e_mat_type : uint32_t {
	/* alias    | value    | OpenGL symbolic defs(gl.h)| brief description ;
	------------+----------+---------------------------+-------------------*/
	e_modelview = GL_MODELVIEW_MATRIX , // the modelview matrix on the top of the modelview matrix stack;
	e_project   = GL_PROJECTION_MATRIX, // the projection matrix on the top of the projection matrix stack;
	e_texture   = GL_TEXTURE_MATRIX   , // the texture matrix on the top of the texture matrix stack;
	};

	struct s_print_params {
	CString m_pfx, m_sfx, m_pfx_hf;
		s_print_params (void) {
			this->m_pfx    = _T("\t\t");   // the indentation at the start of the line;
			this->m_sfx    = _T("\n");     // new line only;
			this->m_pfx_hf = _T("\t");     // the half of indentation at the start of the line;
		}
		_pc_sz _pfx (void) const { return (_pc_sz)this->m_pfx; } _pc_sz _pfx_hf (void) const { return (_pc_sz)this->m_pfx_hf; }
		_pc_sz _sfx (void) const { return (_pc_sz)this->m_sfx; }
	};
	static s_print_params _prn_params;

	class CMatrix : public CBasic { typedef CBasic TBase;
	public:
		CMatrix (void); CMatrix (const CMatrix&) = delete; CMatrix (CMatrix&&) = delete; ~CMatrix (void) = default;

		const
		f_seq_4x4& Cached (void) const;  // gets the reference to matrix data that is cached by getting matrix from the stack;

		err_code Get (const e_mat_type); // gets current matrix from the matrix stack to internal matrix data cache;
		err_code Get (const e_mat_type, f_seq_4x4&); // gets current matrix from the matrix stack;
		err_code To_self (void);  // loads matrix identity to stack;

		static f_seq_4x4& To_self (f_seq_4x4&); // sets input matrix to identity form, no calls to OpenGL API;
		static CString To_str (const f_seq_4x4&, const bool _b_col_major = true);
		static _pc_sz  To_str (const e_mat_type);

	private:
		CMatrix& operator = (const CMatrix&) = delete; CMatrix& operator = (CMatrix&&) = delete;
		f_seq_4x4 m_cached;
	};

}}}

#endif/*_GL_PROCS_MATRIX_H_INCLUDED*/