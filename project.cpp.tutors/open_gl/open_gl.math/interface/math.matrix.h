#ifndef __MATH_MATRIX_H_INCLUDED
#define __MATH_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Dec-2025 at 18:23:09.539, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' generic data matrix interface declaration file;
*/
#include "math.defs.h"
namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	typedef ::std::array<float, 4u> t_set_4;
	typedef ::std::array<::std::array<float, 2>, 2> t_mat_2x2; // there is 2 column and 2 rows; the columns go first;

	// https://stackoverflow.com/questions/6969881/operator-overload-for-two-dimensional-array ;
	class CMat2x2 {
	public:
		CMat2x2 (void); CMat2x2 (const CMat2x2&); CMat2x2 (CMat2x2&&); ~CMat2x2 (void);
		CMat2x2& operator = (const CMat2x2&);
		CMat2x2& operator = (CMat2x2&&);

		float& cell (const uint32_t _n_col, const uint32_t _n_row); // if colomn index or row index is out of acceptable range, the reference to invalid cell is returned;

	private:
		t_mat_2x2 m_data;
	};

}}}}

#endif/*__MATH_MATRIX_H_INCLUDED*/