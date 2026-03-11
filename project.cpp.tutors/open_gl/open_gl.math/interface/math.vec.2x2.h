#ifndef __MATH_VEC_2x2_H_INCLUDED
#define __MATH_VEC_2x2_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Mar-2026 at 12:05:50.139, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' generic data vector 2 interface declaration file;
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

		float Get_angle (const bool b_round, CError&) const; // gets angle of this vector in 2D coord system, it is assumed the vector is normalized;

		s_vec_2& Invert (const float _f_scale);       // inverts this vector in accordance with given scale factor;
		s_vec_2  Invert (const float _f_scale) const; // creates inverse vector from this one in accordance with given scale factor;

		bool  Is_unit (void) const;                   // checks this vector for unit length;
		float Length (void) const;                    // gets this vector magnitude;

		s_vec_2& Negate (void);
		s_vec_2& Normalize (void);                    // if this vector length is less than defs::f_epsilon, no normalizing occurs;
		s_vec_2& Round (void);     // compares elements of this vector with ::defs::f_epsilon and make appropriate rounding if necessary;

		s_vec_2& Set (const float values[u_count]);   // values are assigned in the following order: x|y|z|w;
		s_vec_2& Set (const float _x, const float _y);

		float Sum (const uint32_t _u_exp = 1) const;  // gets the sum of the elements of this vector; each element can be in power of given exponent;

		CString  To_str (_pc_sz _p_format = _T("%.7f")) const;

		s_vec_2  operator - (void) const;             // unary operator (negate) returns new vector with reversed direction;
		s_vec_2& operator - (void) ;                  // changes sign to opposite of all elements of this vector;
		s_vec_2& operator  =(const s_vec_2&);
		s_vec_2& operator *=(const s_vec_2&); // multiplies this vector by input one;
		s_vec_2& operator +=(const s_vec_2&);
		s_vec_2& operator +=(const float _f_scalar);      // adds scalar value to this vector;
		s_vec_2& operator -=(const float _f_scalar);      // substracts scalar value from this vector;
		s_vec_2& operator /=(const float _f_scale) ;      // makes inversion of this vector in accordance with given scale factor;
		s_vec_2  operator / (const float _f_scale) const; // makes inversion of this vector in accordance with given scale factor;

		bool operator == (const s_vec_2&) const;

		s_vec_2  operator - (const s_vec_2&) const;

		float x, y;
	};
}}}}

typedef ex_ui::draw::open_gl::math::s_vec_2 vec_2;
/* https://www.cuemath.com/numbers/subtraction/
   in a subtraction operation a - b = c, the members of expression are named: (from left to right)
     minuend   : the total amount or the number from which another number is subtracted;
     subtrahend: the number that is to be subtracted or taken away;
     difference: the result or value remaining after the subtraction is performed;
*/
// this operator cannot be used inside of matrix function, because the matrix class has unary subtract operator too:
// C2678: binary '-': no operator found which takes a left-hand operand of type 'const vec_2';
vec_2 operator - (const vec_2& _v_from, const vec_2& _v_what);

#endif/*__MATH_VEC_2x2_H_INCLUDED*/