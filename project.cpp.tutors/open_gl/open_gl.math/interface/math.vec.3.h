#ifndef __MATH_VEC_3_H_INCLUDED
#define __MATH_VEC_3_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Mar-2026 at 16:47:46.771, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' float data vector 3 interface declaration file;
*/
#include "math.defs.h"
#include "math.vec.2.h"

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
		s_vec_3& Round (const float _threshold = defs::f_epsilon); // compares elements of this vector with accuracy threshold and makes appropriate rounding if necessary;

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

}}}}

typedef ex_ui::draw::open_gl::math::s_vec_3 vec_3;

#endif/*__MATH_VEC_3_H_INCLUDED*/