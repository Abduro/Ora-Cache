#ifndef __MATH_MATRIX_H_INCLUDED
#define __MATH_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Dec-2025 at 18:23:09.539, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' generic data matrix interface declaration file;
*/
#include "math.defs.h"
#include "math.vector.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	typedef ::std::vector<::std::reference_wrapper<float>> t_cell_refs;
	/* the very important note from https://community.khronos.org/t/matrix-multiplication-using-2d-std-vector/106457 ;
	   regarding using SYCL (System-wide Compute Language) buffer : (cl_khr_gl_sharing  one of the extensions)
	...as the storage of a std::vector is *heap-allocated* in order to allow it to be resized, the overall structure is *non-contiguous*,
	   which is a requirement for moving data to and from a device via a SYCL buffer... the excerpt from the answer given by gordonbrown589;
	   perhaps, using fixed-sized std::array is the more preferable way in comparison with std::vector;
	*/
	/* entry positions or in other words, entry's indices:
	 cols:    #0  #1
	 rows:#0 | 0 | 2 |
	      #1 | 1 | 3 |
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
		c_rows& Rows (void) const;
		c_rows& Rows (void) ;

		c_mat2x2& operator = (const c_mat2x2&);
		c_mat2x2& operator = (c_mat2x2&&);

		const
		float& operator ()(const uint32_t _u_col, const uint32_t _u_row) const; // sets the cell/entry of this matrix by given column and row indices;
		float& operator ()(const uint32_t _u_col, const uint32_t _u_row) ;      // sets the cell/entry of this matrix by given column and row indices;

		c_mat2x2& operator <<(const t_seq_2x2& _arr_values);
		c_mat2x2& operator *=(const float _f_scale);

	protected:
		::std::vector<float> m_data; // u_cols x u_rows = 4 elements;
		c_cols m_cols;
		c_rows m_rows;
	};

	c_mat2x2 operator * (const c_mat2x2& _left, const c_mat2x2& _right); // (_left * _right); https://en.wikipedia.org/wiki/Matrix_multiplication ;
	c_mat2x2 operator + (const c_mat2x2& _left, const c_mat2x2& _right); // (_left + _right); https://en.wikipedia.org/wiki/Matrix_addition ;
	c_mat2x2 operator - (const c_mat2x2& _left, const c_mat2x2& _right); // (_left - _right); https://en.wikipedia.org/wiki/Matrix_addition ; and subtraction;

	c_mat2x2 operator - (const c_mat2x2&) ; // negates the input matrix, i.e. (-1) * (input matrix); this is a form of scalar multiplication;

	/* entry positions or in other words, entry's indices:
	 cols:    #0  #1   #2
	 rows:#0 | 0 | 3 | 6 |
	      #1 | 1 | 4 | 7 |
		  #2 | 2 | 5 | 8 |
	*/
	class c_mat3x3 {
	public:
		class c_cols {
		public: static const uint32_t u_count = 3;
			c_cols (c_mat3x3&); c_cols (void) = delete; c_cols (const c_cols&) = delete; c_cols (c_cols&&) = delete; ~c_cols (void) = default;
			c_cols (const uint32_t _u_col, const vec_3& _data);

			vec_3 Get (const uint32_t _u_col) const;  // returns the vector of column values by given column index; if the column index is out of range, the empty vector is returned;

			c_mat3x3& Set (const t_seq_3& _col_0, const t_seq_3& _col_1, const t_seq_3& _col_2); // sets values to all columns; the value is x|y|z data sequence;
			c_mat3x3& Set (const uint32_t _u_col, const t_seq_3& _xyz); // sets values to the column by given column index; the value is x|y|z data sequence;
			c_mat3x3& Set (const uint32_t _u_col, const float _x, const float _y, const float _z); // sets values to the column by given column index;

			c_mat3x3& Set (const uint32_t _u_col, const vec_3& _xyz); // sets values of the input vector to the column of the given index;
			c_mat3x3& Set (const vec_3&   _col_0, const vec_3& _col_1, const vec_3& _col_2); // sets values to all columns from the input vectors;

			const
			c_mat3x3& operator ()(void) const; // returns the reference to the matrix object whith these columns are belong to; (ro)
			c_mat3x3& operator ()(void) ;      // returns the reference to the matrix object whith these columns are belong to; (rw)

			c_mat3x3& operator ()(const uint32_t _u_col, const t_seq_3& _xyz);
			c_mat3x3& operator ()(const uint32_t _u_col, const float _x, const float _y, const float _z);
			c_mat3x3& operator ()(const uint32_t _u_col, const vec_3& _xyz);

		private:
			c_cols&   operator = (const c_cols&) = delete; c_cols& operator = (c_cols&&) = delete;
			c_mat3x3& m_mat_ref;
		};

		class c_rows {
		public: static const uint32_t u_count = 3;
			c_rows (c_mat3x3&); c_rows (void) = delete; c_rows (const c_rows&) = delete; c_rows (c_rows&&) = delete; ~c_rows (void) = default;

			vec_3 Get (const uint32_t _n_row) const;               // gets a copy of the row by given index; if the index out of range, empty vector is returned;
			void  Set (const uint32_t _n_row, const float _f_val); // sets the input value to all elements of the row specified by index; if the index is out of range, nothing occurs;

			const
			c_mat3x3& operator ()(void) const;
			c_mat3x3& operator ()(void) ;

		private:
			c_rows&   operator = (const c_rows&) = delete; c_rows& operator = (c_rows&&) = delete;
			c_mat3x3& m_mat_ref;
		};

	public:
		static const uint32_t u_cols = c_cols::u_count, u_rows = c_rows::u_count, u_size = u_cols * u_rows;

		c_mat3x3 (void); c_mat3x3 (const c_mat3x3&); c_mat3x3 (c_mat3x3&&); ~c_mat3x3 (void) = default;
		c_mat3x3 (const t_seq_3x3& _arr_values);
		c_mat3x3 (const t_seq_3& _col_0, const t_seq_3& _col_1, const t_seq_3& _col_2);

		const
		float&  Cell (const uint32_t _u_col, const uint32_t _u_row) const; // gets the reference to the value by given column and row indices;
		float&  Cell (const uint32_t _u_col, const uint32_t _u_row);       // gets the reference to the value by given column and row indices;

		const
		c_cols& Cols (void) const;
		c_cols& Cols (void) ;

		float Get (const uint32_t _u_col, const uint32_t _u_row) const; // gets the value of the matrix entry by given column and row indices;

		c_mat3x3& Identity (void);

		const
		c_rows& Rows (void) const;
		c_rows& Rows (void) ;

		const
		float&  operator ()(const uint32_t _u_col, const uint32_t _u_row) const; // gets the reference to the required matrix cell/entry;
		float&  operator ()(const uint32_t _u_col, const uint32_t _u_row) ;		 // gets the reference to the required matrix cell/entry;

		c_mat3x3& operator ()(const t_seq_3& _col_0, const t_seq_3& _col_1, const t_seq_3& _col_2);

		c_mat3x3& operator = (const c_mat3x3&);
		c_mat3x3& operator = (c_mat3x3&&);

		c_mat3x3& operator <<(const t_seq_3x3& _arr_values);
		c_mat3x3& operator *=(const float _f_scale);

	protected:
		::std::vector<float> m_data; // u_cols x u_rows = 9 elements;
		c_cols m_cols;
		c_rows m_rows;
	};
	/* entry positions or in other words, entry's indices:
	 cols:    #0  #1   #2  #3
	 rows:#0 | 0 | 4 | 8 | c |
	      #1 | 1 | 5 | 9 | d |
	      #2 | 2 | 6 | a | e |
	      #3 | 3 | 7 | b | f |
	*/
	class c_mat4x4 {
	public:
		class c_cols {
		public: static const uint32_t u_count = 4;
			c_cols (c_mat4x4&); c_cols (void) = delete; c_cols (const c_cols&) = delete; c_cols (c_cols&&) = delete; ~c_cols (void) = default;
			
			vec_4 Get (const uint32_t _u_col) const;  // returns the vector of column values by given column index; if the column index is out of range, the empty vector is returned;

			c_mat4x4& Set (const float _col_0[u_count], const float _col_1[u_count], const float _col_2[u_count], const float _col_3[u_count]); // sets all columns of the matrix;
			c_mat4x4& Set (const uint32_t _u_col, const float _values[u_count]); // sets the column of given index to the values provided: x|y|z|w;
			c_mat4x4& Set (const uint32_t _u_col, const float _x, const float _y, const float _z, const float _w = 1.0f); // sets the column of given index to the values provided;

			c_mat4x4& Set (const uint32_t _u_col, const vec_4& _xyzw); // sets the column of given index to the values provided;
			c_mat4x4& Set (const vec_4&   _col_0, const vec_4& _col_1, const vec_4& _col_2, const vec_4& _col_3);
			c_mat4x4& Set (const uint32_t _u_col, const vec_3& _xyz ); // sets the column of given index to the values provided;

			const
			c_mat4x4& operator ()(void) const;
			c_mat4x4& operator ()(void) ;

		private:
			c_cols& operator = (const c_cols&) = delete; c_cols& operator = (c_cols&&) = delete;
			c_mat4x4& m_mat_ref;
		};

		class c_rows {
		public: static const uint32_t u_count = 4;
			c_rows (c_mat4x4&); c_rows (void) = delete; c_rows (const c_rows&) = delete; c_rows (c_rows&&) = delete; ~c_rows (void) = default;

			vec_4 Get (const uint32_t _n_row) const;               // gets a copy of the row by given index; if the index out of range, empty vector is returned;
			void  Set (const uint32_t _n_row, const float _f_val); // sets the input value to all elements of the row specified by index; if the index is out of range, nothing occurs;

			const
			c_mat4x4& operator ()(void) const;
			c_mat4x4& operator ()(void) ;

		private:
			c_rows& operator = (const c_rows&) = delete; c_rows& operator = (c_rows&&) = delete;
			c_mat4x4& m_mat_ref;
		};

	public: static const uint32_t u_cols = c_cols::u_count, u_rows = c_rows::u_count, u_size = u_cols * u_rows;
		c_mat4x4 (const bool _b_identity = true); c_mat4x4 (const c_mat4x4&); c_mat4x4 (c_mat4x4&&); ~c_mat4x4 (void) = default;
		c_mat4x4 (const t_seq_4x4& _arr_values);

		const
		float& Cell (const uint32_t _u_col, const uint32_t _u_row) const; // if column or row index is out of range, the reference to invalid entry is returned; (ro)
		float& Cell (const uint32_t _u_col, const uint32_t _u_row);       // if column or row index is out of range, the reference to invalid entry is returned; (rw)

		const
		c_cols& Cols (void) const;
		c_cols& Cols (void) ;

		c_mat3x3 Exclude (const uint32_t _u_col, const uint32_t _u_row) const; // gets matrix 3x3 by excluding particular colomn and row;
		float Get (const uint32_t _u_col, const uint32_t _u_row) const; // returns the value of the matrix entry by given column and row indices;

		c_mat4x4& Identity (void);

		const
		c_rows& Rows (void) const;
		c_rows& Rows (void) ;

		c_mat4x4& Translate (const float _x, const float _y, const float _z); // view matrix converts points from world coords (global) to camera coords (local to the camera);
		c_mat4x4& Translate (const vec_3&);

		c_mat4x4& operator = (const c_mat4x4&);
		c_mat4x4& operator = (c_mat4x4&&); // https://en.cppreference.com/w/cpp/container/vector/swap ;

		c_mat4x4& operator*= (const float _f_scale);
		c_mat4x4& operator <<(const t_seq_4x4& _arr_values);

		const
		float&    operator ()(const uint32_t _u_col, const uint32_t _u_row) const;
		float&    operator ()(const uint32_t _u_col, const uint32_t _u_row) ;

	protected:
		::std::vector<float> m_data; // u_cols x u_rows = 16 elements;
		c_cols    m_cols;
		c_rows    m_rows;
	};

	// the multiplication operator cannot return reference due to the intermediate result requires buffering: neither _left nor _right is able to change;
	c_mat4x4 operator * (const c_mat4x4&, const c_mat4x4&); // https://en.wikipedia.org/wiki/Matrix_multiplication ;
	
}}}}

#endif/*__MATH_MATRIX_H_INCLUDED*/