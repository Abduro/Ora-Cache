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
		static const uint32_t u_cols = 2, u_rows = 2, u_size = u_cols * u_rows;

		c_mat2x2 (void); c_mat2x2 (const c_mat2x2&); c_mat2x2 (c_mat2x2&&) = delete; ~c_mat2x2 (void) = default;
		c_mat2x2& operator = (const c_mat2x2&);
		c_mat2x2& operator = (c_mat2x2&&) = delete; // not required yet;

		float& Cell (const uint32_t _u_col, const uint32_t _u_row); // if column or row index is out of acceptable range, the reference to invalid cell is returned;

	protected:
		::std::vector<float> m_data; // u_cols x u_rows = 4 elements;
	};

	class c_mat3x3 {
	public:
		class c_cols {
		public: static const uint32_t u_count = 3;
			c_cols (c_mat3x3&); c_cols (void) = delete; c_cols (const c_cols&) = delete; c_cols (c_cols&&) = delete; ~c_cols (void) = default;

			c_mat3x3& Set (const float _col_0[3], const float _col_1[3], const float _col_2[3]);
			c_mat3x3& Set (const uint32_t _u_col, const float _xyz[3]);
			c_mat3x3& Set (const uint32_t _u_col, const float _x, const float _y, const float _z);

			c_mat3x3& Set (const uint32_t _u_col, const vec_3& _xyz);
			c_mat3x3& Set (const vec_3&   _col_0, const vec_3& _col_1, const vec_3& _col_2);

		private:
			c_cols& operator = (const c_cols&) = delete; c_cols& operator = (c_cols&&) = delete;
			c_mat3x3& m_mat_ref;
		};
	public:
		static const uint32_t u_cols = c_cols::u_count, u_rows = 3, u_size = u_cols * u_rows;

		c_mat3x3 (void); c_mat3x3 (const c_mat3x3&); c_mat3x3 (c_mat3x3&&) = delete; ~c_mat3x3 (void) = default;
		c_mat3x3& operator = (const c_mat3x3&);
		c_mat3x3& operator = (c_mat3x3&&) = delete; // not required yet;
		const
		float&  Cell (const uint32_t _u_col, const uint32_t _u_row) const;
		float&  Cell (const uint32_t _u_col, const uint32_t _u_row);
		const
		c_cols& Cols (void) const;
		c_cols& Cols (void) ;
		const
		float&  operator ()(const uint32_t _u_col, const uint32_t _u_row) const;
		float&  operator ()(const uint32_t _u_col, const uint32_t _u_row) ;

	protected:
		::std::vector<float> m_data; // u_cols x u_rows = 9 elements;
		c_cols m_cols;
	};

	class c_mat4x4 {
	public:
		class c_cols {
		public: static const uint32_t u_count = 4;
			c_cols (c_mat4x4&); c_cols (void) = delete; c_cols (const c_cols&) = delete; c_cols (c_cols&&) = delete; ~c_cols (void) = default;

			c_mat4x4& Set (const uint32_t _u_col, const float _values[4]);
			c_mat4x4& Set (const uint32_t _u_col, const float _x, const float _y, const float _z, const float _w = 1.0f);

			c_mat4x4& Set (const uint32_t _u_col, const vec_3& _xyz);
			c_mat4x4& Set (const vec_3&   _col_0, const vec_3& _col_1, const vec_3& _col_2);

		private:
			c_cols& operator = (const c_cols&) = delete; c_cols& operator = (c_cols&&) = delete;
			c_mat4x4& m_mat_ref;
		};
		class c_rows {
		public: static const uint32_t u_count = 4;
			c_rows (c_mat4x4&); c_rows (void) = delete; c_rows (const c_rows&) = delete; c_rows (c_rows&&) = delete; ~c_rows (void) = default;

			void Set (const uint32_t _n_row, const float _f_val); // sets the input value to all elements of the row specified by index; if the index is out of range, nothing occurs;

		private:
			c_rows& operator = (const c_rows&) = delete; c_rows& operator = (c_rows&&) = delete;
			c_mat4x4& m_mat_ref;
		};
	public: static const uint32_t u_cols = c_cols::u_count, u_rows = c_rows::u_count, u_size = u_cols * u_rows;
		c_mat4x4 (void); c_mat4x4 (const c_mat4x4&); c_mat4x4 (c_mat4x4&&) = delete; ~c_mat4x4 (void) = default;

		const
		float& Cell (const uint32_t _u_col, const uint32_t _u_row) const; // if column or row index is out of range, the reference to invalid cell is returned; (ro)
		float& Cell (const uint32_t _u_col, const uint32_t _u_row);       // if column or row index is out of range, the reference to invalid cell is returned; (rw)

		c_mat4x4& Identity (void);

		const
		c_rows& Rows (void) const;
		c_rows& Rows (void) ;

		c_mat4x4& Translate (const float _x, const float _y, const float _z); // view matrix converts points from world coords (global) to camera coords (local to the camera);
		c_mat4x4& Translate (const vec_3&);

		c_mat4x4& operator = (const c_mat4x4&);
		c_mat4x4& operator = (c_mat4x4&&) = delete; // not required yet;

		const
		float&    operator ()(const uint32_t _u_col, const uint32_t _u_row) const;
		float&    operator ()(const uint32_t _u_col, const uint32_t _u_row) ;

	protected:
		::std::vector<float> m_data; // u_cols x u_rows = 16 elements;
		c_rows    m_rows;
	};

	class c_rotate_3x3 : public c_mat3x3 {
	public:
		c_rotate_3x3 (void); c_rotate_3x3 (const c_rotate_3x3&) = delete; c_rotate_3x3 (c_rotate_3x3&&) = delete; ~c_rotate_3x3 (void) = default;
		c_rotate_3x3 (const float _f_angle, const float _x, const float _y, const float _z);

		c_mat3x3& Do (const float _f_angle, const float _x, const float _y, const float _z);  // rotates by a given angle about an axis specified;
		c_mat3x3& Do (const float _f_angle, const vec_3& _axis);

		c_mat3x3& operator ()(const float _f_angle, const float _x, const float _y, const float _z);

		const
		c_mat3x3& operator ()(void) const;
		c_mat3x3& operator ()(void);

	private:
		c_rotate_3x3& operator = (const c_rotate_3x3&) = delete; c_rotate_3x3& operator = (c_rotate_3x3&&) = delete;
	}; 

	class c_rotate_4x4 : public c_mat4x4 {
	public:
		c_rotate_4x4 (void); c_rotate_4x4 (const c_rotate_4x4&) = delete; c_rotate_4x4 (c_rotate_4x4&&) = delete; ~c_rotate_4x4 (void) = default;

		c_mat4x4& Do (const float _f_angle, const float _x, const float _y, const float _z); //  rotates angle(degree) along the given axix;
		c_mat4x4& Do (const float _f_angle, const vec_3&);

		c_mat4x4& On_x (const float _f_angle); // rotates on X-axis, the angle is in degrees;
		c_mat4x4& On_y (const float _f_angle); // rotates on Y-axis, the angle is in degrees;
		c_mat4x4& On_z (const float _f_angle); // rotates on Z-axis, the angle is in degrees;

		const
		c_mat4x4& operator ()(void) const;
		c_mat4x4& operator ()(void) ;

	private:
		c_rotate_4x4& operator = (const c_rotate_4x4&) = delete; c_rotate_4x4& operator = (c_rotate_4x4&&) = delete;
	};

}}}}

#endif/*__MATH_MATRIX_H_INCLUDED*/