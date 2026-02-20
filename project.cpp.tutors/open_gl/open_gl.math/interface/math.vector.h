#ifndef __MATH_VECTOR_H_INCLUDED
#define __MATH_VECTOR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2025 at 17:46:20.224, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' generic data vector interface declaration file;
*/
#include "math.defs.h"
namespace ex_ui { namespace draw { namespace open_gl { namespace math {
	/* https://learnopengl.com/Getting-started/Transformations ;
	   In its most basic definition, vectors are directions and nothing more. A vector has a direction and a magnitude (also known as its strength or length).
	   2 elements: double / pair / couple;
	*/
	struct s_vec_2 {
		static const uint32_t u_count = 2; // the number of the fields' count;
		s_vec_2 (void);
		s_vec_2 (const float _values[u_count]);       // values are assigned in the following order: x|y;
		s_vec_2 (const float _x, const float _y);

		s_vec_2& Invert (const float _f_scale);       // inverts this vector in accordance with given scale factor;
		s_vec_2  Invert (const float _f_scale) const; // creates inverse vector from this one in accordance with given scale factor;

		float Length (void) const;

		s_vec_2& Set (const float values[u_count]);   // values are assigned in the following order: x|y|z|w;
		s_vec_2& Set (const float _x, const float _y);

		s_vec_2& Negate (void);
		float Sum (const uint32_t _u_exp = 1) const;  // gets the sum of the elements of this vector; each element can be in power of given exponent;

		CString  To_str (_pc_sz _p_format = _T("%.7f")) const;

		s_vec_2  operator - (void) const;             // unary operator (negate) returns new vector with reversed direction;
		s_vec_2& operator - (void) ;                  // changes sign to opposite of all elements of this vector;
		s_vec_2& operator  =(const s_vec_2&);
		s_vec_2& operator *=(const s_vec_2&); // multiplies this vector by input one;

		s_vec_2& operator +=(const float _f_scalar);      // adds scalar value to this vector;
		s_vec_2& operator -=(const float _f_scalar);      // substracts scalar value from this vector;
		s_vec_2& operator /=(const float _f_scale) ;      // makes inversion of this vector in accordance with given scale factor;
		s_vec_2  operator / (const float _f_scale) const; // makes inversion of this vector in accordance with given scale factor;

		float x, y;
	};
	/* https://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/ ;
	   Homogeneous coordinates for vertex position as a (x,y,z) triplet or triple/trio;
	*/
	struct s_vec_3 : public s_vec_2 {
		static const uint32_t u_count = s_vec_2::u_count + 1; // the number of the fields' count;
		s_vec_3 (void);
		s_vec_3 (const float _values[u_count]);       // values are assigned in the following order: x|y|z;
		s_vec_3 (const float _x, const float _y, const float _z);
		s_vec_3 (const s_vec_2&, const float _z = 0.0f);

		s_vec_3 Get_cross (const s_vec_3&);           // gets cross product;
		float   Get_dot (const s_vec_3&);             // gets dot product;

		s_vec_3& Invert (const float _f_scale);       // inverts this vector in accordance with given scale factor;
		s_vec_3  Invert (const float _f_scale) const; // creates inverse vector from this one in accordance with given scale factor;

		float Length (void) const;

		s_vec_3& Negate (void);
		s_vec_3& Normalize (const bool _b_fast = true); // https://en.wikipedia.org/wiki/Fast_inverse_square_root ;

		s_vec_3& Set (const float values[u_count]);   // values are assigned in the following order: x|y|z;
		s_vec_3& Set (const float _x, const float _y, const float _z);
		s_vec_3& Set (const s_vec_2&, const float _z = 0.0f);

		float Sum (const uint32_t _u_exp = 1) const;  // gets the sum of the elements of this vector; each element can be in power of given exponent;

		CString  To_str (_pc_sz _p_format = _T("%.7f")) const;

		s_vec_3  operator - (void) const;             // unary operator (negate) returns new vector with reversed direction;
		s_vec_3& operator - (void) ;                  // changes sign to opposite of all elements of this vector;

		s_vec_3& operator  =(const s_vec_3&);
		s_vec_3& operator *=(const s_vec_3&);         // multiplies this vector by input one;

		s_vec_3& operator /=(const float _f_scale) ;      // makes inversion of this vector in accordance with given scale factor;
		s_vec_3  operator / (const float _f_scale) const; // makes inversion of this vector in accordance with given scale factor;
		s_vec_3  operator + (const s_vec_3&) const;
		s_vec_3& operator +=(const float _f_scalar);      // adds scalar value to this vector;
		s_vec_3& operator -=(const float _f_scalar);      // substracts scalar value from this vector;

		const
		s_vec_2& operator ()(void) const;     // gets the reference to the parent structure object; (ro)
		s_vec_2& operator ()(void) ;          // gets the reference to the parent structure object; (rw)

		float z;
	};

	bool operator == (const s_vec_3&, const s_vec_3&);

	/* https://en.cppreference.com/w/cpp/algorithm/transform.html ; this is not the case for vector emulation like the below class is;
	   4 elements (x,y,z,w) are quadruple or quartet, where (x,y,z) is coord triplet and the fourth element 'w' is 0 (direction) or 1 (position);
	   in mathematics, a collection of four items is often referred to as a 4-tuple or an ordered quadruple;
	*/
	struct s_vec_4 : public s_vec_3 {
		static const uint32_t u_count = s_vec_3::u_count + 1; // the number of the fields' count;
		s_vec_4 (void);
		s_vec_4 (const float _values[u_count]);       // values are assigned in the following order: x|y|z|w;
		s_vec_4 (const float _x, const float _y, const float _z, const float _w);
		s_vec_4 (const s_vec_3&, const float _w = 0.0f);

		s_vec_4& Invert (const float _f_scale);       // inverts this vector in accordance with given scale factor;
		s_vec_4  Invert (const float _f_scale) const; // creates inverse vector from this one in accordance with given scale factor;

		s_vec_4& Set (const float values[u_count]);   // values are assigned in the following order: x|y|z|w;
		s_vec_4& Set (const float _x, const float _y, const float _z, const float _w);
		s_vec_4& Set (const s_vec_3&, const float _w = 0.0f);

		float Sum (const uint32_t _u_exp = 1) const;  // gets the sum of the elements of this vector; each element can be in power of given exponent;
		CString  To_str (_pc_sz _p_format = _T("%.7f")) const;

		s_vec_4  operator - (void) const;             // unary operator (negate) returns new vector with reversed direction;
		s_vec_4& operator - (void) ;                  // changes sign to opposite of all elements of this vector;

		s_vec_4& operator  =(const s_vec_4&);
		s_vec_4& operator *=(const s_vec_4&);         // multiplies this vector by input one;
		s_vec_4& operator +=(const float _f_scalar);  // adds scalar value to this vector;
		s_vec_4& operator -=(const float _f_scalar);  // substracts scalar value from this vector;

		s_vec_4& operator /=(const float _f_scale) ;      // makes inversion of this vector in accordance with given scale factor;
		s_vec_4  operator / (const float _f_scale) const; // makes inversion of this vector in accordance with given scale factor;

		const
		s_vec_3& operator ()(void) const;     // gets the reference to the parent structure object; (ro)
		s_vec_3& operator ()(void) ;          // gets the reference to the parent structure object; (rw)

		float w;
	};

	s_vec_3 operator * (const float, const s_vec_3&);
	s_vec_4 operator * (const s_vec_4&, const s_vec_4&);
	// what is about five elements: quintuple or quintet;
}}}}

typedef ex_ui::draw::open_gl::math::s_vec_2 vec_2;
typedef ex_ui::draw::open_gl::math::s_vec_3 vec_3;
typedef ex_ui::draw::open_gl::math::s_vec_4 vec_4;

#endif/*__MATH_VECTOR_H_INCLUDED*/