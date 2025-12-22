#ifndef __MATH_MATRIX_H_INCLUDED
#define __MATH_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Dec-2025 at 18:23:09.539, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' generic data matrix interface declaration file;
*/
#include "math.defs.h"
#include "math.vector.h"

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

	class c_mat4x4 {
	public: static const uint32_t u_cols = 4, u_rows = 4, u_size = u_cols * u_rows;
	public:
		class c_rows {
		public:
			c_rows (c_mat4x4&); c_rows (void) = delete; c_rows (const c_rows&) = delete; c_rows (c_rows&&) = delete; ~c_rows (void) = default;

			void Set (const uint32_t _n_row, const float _f_val); // sets the input value to all elements of the row specified by index; if the index is out of range, nothing occurs;

		private:
			c_rows& operator = (const c_rows&) = delete; c_rows& operator = (c_rows&&) = delete;
			c_mat4x4& m_mat_ref;
		};
	public:
		c_mat4x4 (void); c_mat4x4 (const c_mat4x4&); c_mat4x4 (c_mat4x4&&) = delete; ~c_mat4x4 (void) = default;
		c_mat4x4& operator = (const c_mat4x4&);
		c_mat4x4& operator = (c_mat4x4&&) = delete; // not required yet;

		const
		float& Cell (const uint32_t _u_col, const uint32_t _u_row) const; // if column or row index is out of range, the reference to invalid cell is returned; (ro)
		float& Cell (const uint32_t _u_col, const uint32_t _u_row);       // if column or row index is out of range, the reference to invalid cell is returned; (rw)

		c_mat4x4& Identity (void);

		const
		c_rows& Rows (void) const;
		c_rows& Rows (void) ;

		c_mat4x4& Translate (const float _x, const float _y, const float _z); // view matrix converts points from world coords (global) to camera coords (local to the camera);
		c_mat4x4& Translate (const vec_3&);

	protected:
		::std::vector<float> m_data; // u_cols x u_rows = 16 elements;
		c_rows m_rows;
	};

}}}}

#endif/*__MATH_MATRIX_H_INCLUDED*/