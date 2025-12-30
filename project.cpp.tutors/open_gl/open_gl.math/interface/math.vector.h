#ifndef __MATH_VECTOR_H_INCLUDED
#define __MATH_VECTOR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2025 at 17:46:20.224, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' generic data vector interface declaration file;
*/
#include "math.defs.h"
namespace ex_ui { namespace draw { namespace open_gl { namespace math {
	// it is not right approach to call every data sets (fixed or dynamic size) to be a vector;
	struct s_vec_2 {
		static const uint32_t u_count = 2; // the number of the fields' count;
		s_vec_2 (void);
		s_vec_2 (const float _values[u_count]);        // values are assigned in the following order: x|y;
		s_vec_2 (const float _x, const float _y);

		s_vec_2& Inverse (const float _f_scale);       // inverses this vector in accordance with given scale factor;
		s_vec_2  Inverse (const float _f_scale) const; // creates inverse vector from this one in accordance with given scale factor;

		s_vec_2& Set (const float values[u_count]);    // values are assigned in the following order: x|y|z|w;
		s_vec_2& Set (const float _x, const float _y);

		float Sum (void) const; // gets the sum of the elements of this vector;

		s_vec_2& operator  = (const s_vec_2&);
		s_vec_2& operator *= (const s_vec_2&); // multiplies this vector by input one;

		s_vec_2& operator /= (const float _f_scale) ;      // makes inversion of this vector in accordance with given scale factor;
		s_vec_2  operator /  (const float _f_scale) const; // makes inversion of this vector in accordance with given scale factor;

		float x, y;
	};

	struct s_vec_3 : public s_vec_2 {
		static const uint32_t u_count = s_vec_2::u_count + 1; // the number of the fields' count;
		s_vec_3 (void);
		s_vec_3 (const float _values[u_count]);     // values are assigned in the following order: x|y|z;
		s_vec_3 (const float _x, const float _y, const float _z);

		s_vec_3& Inverse (const float _f_scale);       // inverses this vector in accordance with given scale factor;
		s_vec_3  Inverse (const float _f_scale) const; // creates inverse vector from this one in accordance with given scale factor;

		s_vec_3& Set (const float values[u_count]); // values are assigned in the following order: x|y|z;
		s_vec_3& Set (const float _x, const float _y, const float _z);

		float Sum (void) const; // gets the sum of the elements of this vector;

		s_vec_3& operator  = (const s_vec_3&);
		s_vec_3& operator *= (const s_vec_3&); // multiplies this vector by input one;

		s_vec_3& operator /= (const float _f_scale) ;      // makes inversion of this vector in accordance with given scale factor;
		s_vec_3  operator /  (const float _f_scale) const; // makes inversion of this vector in accordance with given scale factor;

		const
		s_vec_2& operator ()(void) const;     // gets the reference to the parent structure object; (ro)
		s_vec_2& operator ()(void) ;          // gets the reference to the parent structure object; (rw)

		float z;
	};

	// https://en.cppreference.com/w/cpp/algorithm/transform.html ; this is not the case for vector emulation like the below class is;
	struct s_vec_4 : public s_vec_3 {
		static const uint32_t u_count = s_vec_3::u_count + 1; // the number of the fields' count;
		s_vec_4 (void);
		s_vec_4 (const float _values[u_count]);     // values are assigned in the following order: x|y|z|w;
		s_vec_4 (const float _x, const float _y, const float _z, const float _w);

		s_vec_4& Inverse (const float _f_scale);       // inverses this vector in accordance with given scale factor;
		s_vec_4  Inverse (const float _f_scale) const; // creates inverse vector from this one in accordance with given scale factor;

		s_vec_4& Set (const float values[u_count]); // values are assigned in the following order: x|y|z|w;
		s_vec_4& Set (const float _x, const float _y, const float _z, const float _w);

		float Sum (void) const; // gets the sum of the elements of this vector;

		s_vec_4& operator  = (const s_vec_4&);
		s_vec_4& operator *= (const s_vec_4&); // multiplies this vector by input one;

		s_vec_4& operator /= (const float _f_scale) ;      // makes inversion of this vector in accordance with given scale factor;
		s_vec_4  operator /  (const float _f_scale) const; // makes inversion of this vector in accordance with given scale factor;

		const
		s_vec_3& operator ()(void) const;     // gets the reference to the parent structure object; (ro)
		s_vec_3& operator ()(void) ;          // gets the reference to the parent structure object; (rw)

		float w;
	};

	s_vec_4 operator * (const s_vec_4&, const s_vec_4&);

}}}}

typedef ex_ui::draw::open_gl::math::s_vec_2 vec_2;
typedef ex_ui::draw::open_gl::math::s_vec_3 vec_3;
typedef ex_ui::draw::open_gl::math::s_vec_4 vec_4;

#endif/*__MATH_VECTOR_H_INCLUDED*/