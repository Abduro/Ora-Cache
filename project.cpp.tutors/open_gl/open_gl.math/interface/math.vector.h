#ifndef __MATH_VECTOR_H_INCLUDED
#define __MATH_VECTOR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2025 at 17:46:20.224, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' generic data vector interface declaration file;
*/
#include "math.defs.h"
#include "math.vec.2x2.h"
namespace ex_ui { namespace draw { namespace open_gl { namespace math {
	/* https://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/ ;
	   Homogeneous coordinates for vertex position as a (x,y,z) triplet or triple/trio;
	*/
	struct s_vec_3 : public s_vec_2 {
		static const uint32_t u_count = s_vec_2::u_count + 1; // the number of the fields' count;
		s_vec_3 (void);
		s_vec_3 (const float _values[u_count]);       // values are assigned in the following order: x|y|z;
		s_vec_3 (const float _x, const float _y, const float _z);
		s_vec_3 (const s_vec_2&, const float _z = 0.0f);
		// https://en.wikipedia.org/wiki/Euclidean_space ;
		// https://en.wikipedia.org/wiki/Cross_product ;
		s_vec_3 Get_cross (const s_vec_3&);           // gets cross product; https://registry.khronos.org/OpenGL-Refpages/gl4/html/cross.xhtml ;
		float   Get_dot (const s_vec_3&) const;       // gets dot product; https://registry.khronos.org/OpenGL-Refpages/gl4/html/dot.xhtml ;

		s_vec_3& Invert (const float _f_scale);       // inverts this vector in accordance with given scale factor;
		s_vec_3  Invert (const float _f_scale) const; // creates inverse vector from this one in accordance with given scale factor;

		bool  Is_unit (void) const;  // check the vector values are normalized or not, i.e. unit value in range [0.0...1/0];
		float Length (void) const;   // gets vector magnitude; https://registry.khronos.org/OpenGL-Refpages/gl4/html/length.xhtml ;

		s_vec_3& Negate (void);
		s_vec_3& Normalize (const bool _b_bits = false); // using bits level hacking is slower in comparison with ::std::sqrtf();

		s_vec_3& Set (const float values[u_count]);   // values are assigned in the following order: x|y|z; it is intended for setting data from glm::vec3;
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

		bool operator == (const s_vec_3&) const;

		float z;
	};
#if (0)
	bool operator == (const s_vec_3&, const s_vec_3&);
#endif
	/* https://en.cppreference.com/w/cpp/algorithm/transform.html ; this is not the case for vector emulation like the below class is;
	   4 elements (x,y,z,w) are quadruple or quartet, where (x,y,z) is coord triplet and the fourth element 'w' is 0 (direction) or 1 (position);
	   in mathematics, a collection of four items is often referred to as a 4-tuple or an ordered quadruple;
	   thus, v3 (x,y,z) = v4 (x/w, y/w, z/w), where w != 0.0;
	*/
	struct s_vec_4 : public s_vec_3 {
		static const uint32_t u_count = s_vec_3::u_count + 1; // the number of the fields' count;
		s_vec_4 (void);
		s_vec_4 (const float _values[u_count]);       // values are assigned in the following order: x|y|z|w;
		s_vec_4 (const float _x, const float _y, const float _z, const float _w);
		s_vec_4 (const s_vec_3&, const float _w = 0.0f);

		// https://en.wikipedia.org/wiki/Seven-dimensional_cross_product ;
		s_vec_4 Get_cross (const s_vec_3&);           // this vector is represented as the reference to parent class s_vec_3;
		s_vec_4 Get_cross (const s_vec_4&);           // this vector is represented as the reference to parent class s_vec_3;

		float   Get_dot (const s_vec_3&) const;       // this vector is represented as the reference to parent class s_vec_3;
		float   Get_dot (const s_vec_4&) const;       // this vector is represented as the reference to parent class s_vec_3;

		s_vec_4& Invert (const float _f_scale);       // inverts this vector in accordance with given scale factor;
		s_vec_4  Invert (const float _f_scale) const; // creates inverse vector from this one in accordance with given scale factor;

		bool  Is_unit (void) const;
		float Length (void) const;

		s_vec_4& Negate (void);
		s_vec_4& Normalize (const bool _b_fast = true); // https://en.wikipedia.org/wiki/Fast_inverse_square_root ;

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

typedef ex_ui::draw::open_gl::math::s_vec_3 vec_3;
typedef ex_ui::draw::open_gl::math::s_vec_4 vec_4;

#endif/*__MATH_VECTOR_H_INCLUDED*/