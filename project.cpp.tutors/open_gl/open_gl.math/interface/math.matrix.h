#ifndef __MATH_MATRIX_H_INCLUDED
#define __MATH_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Dec-2025 at 18:23:09.539, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' generic data matrix interface declaration file;
*/
#include "math.defs.h"
namespace ex_ui { namespace draw { namespace open_gl { namespace math {
#if (0)
	// https://stackoverflow.com/questions/6969881/operator-overload-for-two-dimensional-array ;
	typedef ::std::array<float, 4u> t_set_4;
	typedef ::std::array<::std::array<float, 2>, 2> t_mat_2x2; // there is 2 column and 2 rows; the columns go first;
#endif
	typedef ::std::vector<::std::reference_wrapper<float>> t_cell_refs;

	class c_mat2x2 {
	public:
		static const uint32_t u_cols = 2, u_rows = 2;

		c_mat2x2 (void); c_mat2x2 (const c_mat2x2&); c_mat2x2 (c_mat2x2&&) = delete; ~c_mat2x2 (void) = default;
		c_mat2x2& operator = (const c_mat2x2&);
		c_mat2x2& operator = (c_mat2x2&&) = delete; // not required yet;

		float& cell (const uint32_t _u_col, const uint32_t _u_row); // if column or row index is out of acceptable range, the reference to invalid cell is returned;

	protected:
		::std::vector<float> m_data; // u_cols x u_rows = 4 elements;
	};

}}}}

#endif/*__MATH_MATRIX_H_INCLUDED*/