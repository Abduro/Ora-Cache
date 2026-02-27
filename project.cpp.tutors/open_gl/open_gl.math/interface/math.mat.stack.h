#ifndef _MATH_MAT_STACK_H_INCLUDED
#define _MATH_MAT_STACK_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Feb-2026 at 22:39:59.517, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL matrix stack wrapper interface declaration file;
*/
#include "math.matrix.h"
#include "matrix\gl_procs_mtx.mode.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {
namespace matrix {
	using e_mat_type = ex_ui::draw::open_gl::procs::matrix::e_mat_type;
	class CTarget {
	public:
		CTarget (void); CTarget (const CTarget&) = delete; CTarget (CTarget&&) = delete; ~CTarget (void);
		TError& Error (void) const;

		e_mat_type Get (void) const;       // gets currently set matrix mode;
		err_code   Set (const e_mat_type); // sets matrix mode;

		const
		CTarget& operator >>(e_mat_type&) const;
		CTarget& operator <<(const e_mat_type);

		e_mat_type operator ()(void) const;

	private:
		CTarget& operator = (const CTarget&) = delete; CTarget& operator = (CTarget&&) = delete;
		mutable CError m_error;
		mutable e_mat_type m_type;
	};

	class CStack {
	public:
		CStack (const bool _b_auto = false); ~CStack (void); CStack (const CStack&) = delete; CStack (CStack&&) = delete;
		const
		CTarget& Current (void) const;
		CTarget& Current (void);

		TError& Error (void) const;
		bool Is_pushed (void) const;

		err_code Pop  (void);
		err_code Push (void);
		err_code Push (const c_mat4x4&, const e_mat_type);

	private:
		CStack& operator = (const CStack&) = delete; CStack& operator = (CStack&&) = delete;
		CError  m_error;
		bool    m_auto;
		bool    m_pushed;
		CTarget m_target;
	};
}}}}}

#endif/*_MATH_MAT_STACK_H_INCLUDED*/