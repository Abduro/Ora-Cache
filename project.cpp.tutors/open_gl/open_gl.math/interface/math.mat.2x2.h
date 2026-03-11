#ifndef __MATH_MAT_2x2_H_INCLUDED
#define __MATH_MAT_2x2_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Mar-2026 at 21:42:17.845, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' generic data matrix 2x2 interface declaration file;
*/
#include "math.defs.h"
#include "math.vector.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	class c_mat2x2 {
	public:
		class c_cols {
		public: static const uint32_t u_count = 2;
			c_cols (c_mat2x2&); c_cols (void) = delete; c_cols (const c_cols&) = delete; c_cols (c_cols&&) = delete; ~c_cols (void) = default;

			vec_2 Get (const uint32_t _u_col) const;  // returns the vector of column values by given column index; if the column index is out of range, the empty vector is returned;

			c_mat2x2& Set (const t_seq_2& _col_0, const t_seq_2& _col_1);          // sets values to all columns; the value is x|y data sequence;
			c_mat2x2& Set (const uint32_t _u_col, const t_seq_2& _xy);             // sets values to the column by given column index; the value is x|y data sequence;
			c_mat2x2& Set (const uint32_t _u_col, const float _x, const float _y); // sets values to the column by given column index;

			c_mat2x2& Set (const uint32_t _u_col, const vec_2& _xy);    // sets the column of given index to the values provided;
			c_mat2x2& Set (const vec_2&   _col_0, const vec_2& _col_1); // sets the value to all columns by input vectors;

			const
			c_mat2x2& operator ()(void) const; // returns the reference to the matrix object whith these columns are belong to; (ro)
			c_mat2x2& operator ()(void) ;      // returns the reference to the matrix object whith these columns are belong to; (rw)
			
			c_mat2x2& operator ()(const uint32_t _u_col, const t_seq_2& _xy);
			c_mat2x2& operator ()(const uint32_t _u_col, const float _x, const float _y);
			c_mat2x2& operator ()(const uint32_t _u_col, const vec_2& _xy);

		private:
			c_cols& operator = (const c_cols&) = delete; c_cols& operator = (c_cols&&) = delete;
			c_mat2x2& m_mat_ref;
		};

		class c_rows {
		public: static const uint32_t u_count = 2;
			c_rows (c_mat2x2&); c_rows (void) = delete; c_rows (const c_rows&) = delete; c_rows (c_rows&&) = delete; ~c_rows (void) = default;

			vec_2 Get (const uint32_t _n_row) const;               // gets a copy of the row by given index; if the index out of range, empty vector is returned;
			void  Set (const uint32_t _n_row, const float _f_val); // sets the input value to all elements of the row specified by index; if the index is out of range, nothing occurs;
	
			const
			c_mat2x2& operator ()(void) const;
			c_mat2x2& operator ()(void) ;

		private:
			c_rows& operator = (const c_rows&) = delete; c_rows& operator = (c_rows&&) = delete;
			c_mat2x2& m_mat_ref;
		};
	public:
		static const uint32_t u_cols = c_cols::u_count, u_rows = c_rows::u_count, u_size = u_cols * u_rows;

		c_mat2x2 (void); c_mat2x2 (const c_mat2x2&); c_mat2x2 (c_mat2x2&&); ~c_mat2x2 (void) = default;
		c_mat2x2 (const t_seq_2x2& _arr_values);
		
		const
		float& Cell (const uint32_t _u_col, const uint32_t _u_row) const; // if column or row index is out of acceptable range, the reference to invalid cell is returned; (ro)
		float& Cell (const uint32_t _u_col, const uint32_t _u_row) ;      // if column or row index is out of acceptable range, the reference to invalid cell is returned; (rw)

		const
		c_cols& Cols (void) const;
		c_cols& Cols (void) ;

		float Get (const uint32_t _u_col, const uint32_t _u_row) const; // gets the value of the matrix entry by given column and row indices;

		c_mat2x2& Identity (void);
		vec_2& Mltply (vec_2&, const bool _b_epsilon = false) const;    // https://en.wikipedia.org/wiki/Multiplication ;

		const
		t_seq_2x2& Raw (void) const;
		t_seq_2x2& Raw (void) ;
		const
		c_rows& Rows (void) const;
		c_rows& Rows (void) ;

		c_mat2x2& Seed (const float _f_by = 0.0f);
		c_mat2x2& Transpose (void);

		c_mat2x2& operator = (const c_mat2x2&);
		c_mat2x2& operator = (c_mat2x2&&);

		const
		float& operator ()(const uint32_t _u_col, const uint32_t _u_row) const; // sets the cell/entry of this matrix by given column and row indices;
		float& operator ()(const uint32_t _u_col, const uint32_t _u_row) ;      // sets the cell/entry of this matrix by given column and row indices;

		c_mat2x2& operator << (const t_seq_2x2& _arr_values);
		c_mat2x2& operator *= (const float _f_scale);
		c_mat2x2& operator *= (const c_mat2x2&);

		vec_2& operator *= (vec_2& _v_2) const; // multiplies input vector by this matrix and returned the reference to it;

		bool operator ==(const c_mat2x2&) const;
		const
		float*    operator ()(void) const;
		float*    operator ()(void);

	protected:
	//	::std::vector<float> m_data; // u_cols x u_rows = 4 elements;
		t_seq_2x2 m_data;
		c_cols    m_cols;
		c_rows    m_rows;
	};

	c_mat2x2 operator * (const c_mat2x2& _left, const c_mat2x2& _right); // (_left * _right); https://en.wikipedia.org/wiki/Matrix_multiplication ;
	c_mat2x2 operator + (const c_mat2x2& _left, const c_mat2x2& _right); // (_left + _right); https://en.wikipedia.org/wiki/Matrix_addition ;
	c_mat2x2 operator - (const c_mat2x2& _left, const c_mat2x2& _right); // (_left - _right); https://en.wikipedia.org/wiki/Matrix_addition ; and subtraction;

	c_mat2x2 operator - (const c_mat2x2&) ; // negates the input matrix, i.e. (-1) * (input matrix); this is a form of scalar multiplication;
}}}}

typedef ex_ui::draw::open_gl::math::c_mat2x2 cmat2x2_t;

vec_2& operator * (const cmat2x2_t&, vec_2&); // returns the reference to the input vector multiplied by the matrix; no using the epsilon;

#endif/*__MATH_MAT_2x2_H_INCLUDED*/