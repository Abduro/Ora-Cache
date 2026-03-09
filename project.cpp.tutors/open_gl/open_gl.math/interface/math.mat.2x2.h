#ifndef __MATH_MAT_2x2_H_INCLUDED
#define __MATH_MAT_2x2_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Mar-2026 at 21:42:17.845, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' generic data matrix 2x2 interface declaration file;
*/
#include "math.defs.h"
#include "math.vector.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	/* (google AI)
	In a standard rotation matrix:
	the 1st column represents the transformed x-axis (the image of the unit vector),
	the 2nd column represents the transformed y-axis (the image of the unit vector).

	The Rotation Matrix:
	for a counterclockwise rotation by an angle 'A', the transformation matrix is defined as:
	cosl:      #0      #1
	rows: #0 [ cos(A) -sin(A) ]
	      #1 [ sin(A)  cos(A) ]
	where,
	the x-basis (col #0): [ cos(A) ] represents the new position of the point (1,0); how origin x-coord contributes to the new x and y values;
	                      [ sin(A) ]
	the y-baaia (col #1): [-sin(A) ] represents the new position of the point (0,1).
	                      [ cos(A) ]
	Coordinate Transformation:
	  when multiplying a vector [x] 
	                            [y] by this matrix, the resulting coordinates are:
	  x' = x * cos(A) - y * sin(A);
	  y' = x * sin(A) + y * cos(A);
	Key Consideration:
	  The first column is always the "destination" of the X unit vector, and the second column is the "destination" of the Y unit vector.
	  This is a fundamental property of all linear transformation matrices.
	*/
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

		c_mat2x2& operator <<(const t_seq_2x2& _arr_values);
		c_mat2x2& operator *=(const float _f_scale);
		c_mat2x2& operator *=(const c_mat2x2&);

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

#endif/*__MATH_MAT_2x2_H_INCLUDED*/