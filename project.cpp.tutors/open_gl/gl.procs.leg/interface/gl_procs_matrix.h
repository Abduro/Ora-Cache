#ifndef _GL_PROCS_MATRIX_H_INCLUDED
#define _GL_PROCS_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-May-2026 at 16:13:11.611, UTC+4, Batumi, Wednesday;
	This is OpenGL v.1.1 matrix related function set wrapper interface declaration file;
*/
#include "matrix\gl_procs_mtx.defs.h"
/*These procedure wrappers are espacially intended for OpenGL vers 1.1 API (aka legacy);
*/
namespace open_gl { namespace procs { namespace matrix {
namespace ver_1_1 { using namespace ::open_gl::procs::ver_1_1;

}}}}
namespace open_gl { namespace procs {
namespace ver_1_1 {

	// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetfloatv ;

	using e_mat_type = open_gl::procs::matrix::ver_1_1::e_mat_type;

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

	/* note:
	   It is assumed the Set() and Get() operations are made afterwards the required matrix stack is selected by applying appropriate mode;
	   https://learn.microsoft.com/en-us/windows/win32/opengl/glloadmatrixf ;
	*/
	class CMatrix : public CBasic { typedef CBasic TBase;
	public:
		CMatrix (void); CMatrix (const CMatrix&) = delete; CMatrix (CMatrix&&) = delete; ~CMatrix (void) = default;

		const
		f_mat_4x4& Data (void) const;    // gets the reference to matrix data that is cached by getting matrix from the stack;
		f_mat_4x4& Data (void) ;         // gets the reference to matrix data for read-write operations;

		err_code Get (const e_mat_type); // gets current matrix from the matrix stack to internal matrix data cache; in case of error they data is not changed;
		err_code Get (const e_mat_type, f_mat_4x4&); // gets current matrix from the matrix stack;

		static
		err_code Set (const f_mat_4x4&, CError&);
		err_code Set (void);             // loads internal matrix data to the current matrix stack; it is assumed the appropriate matrix mode is already set;
		err_code Set (const f_mat_4x4&); // loads given matrix data to the current matrix stack;

		err_code To_self (void);         // loads matrix identity to stack;

		static f_mat_4x4& To_self (f_mat_4x4&); // sets input matrix to identity form, no calls to OpenGL API;
		static CString To_str (const f_mat_4x4&, const bool _b_col_major = true);

		const
		f_mat_4x4& operator ()(void) const;
		f_mat_4x4& operator ()(void) ;

		err_code   operator <<(const f_mat_4x4&);

	private:
		CMatrix& operator = (const CMatrix&) = delete; CMatrix& operator = (CMatrix&&) = delete;
		f_mat_4x4 m_data;
	};

}}}

#endif/*_GL_PROCS_MATRIX_H_INCLUDED*/