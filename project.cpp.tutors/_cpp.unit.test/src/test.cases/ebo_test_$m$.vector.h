#ifndef _EBO_TEST_$M$_VECTOR_H_INCLUDED
#define _EBO_TEST_$M$_VECTOR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Dec-2025 at 16:33:25.764, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL math lib vector uint test interface declaration file; 
*/
#include "test_case_$m$.vec2.h"
#include "test_case_$m$.vec3.h"
#include "test_case_$m$.vec4.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {
	/* https://opengl-notes.readthedocs.io/en/latest/topics/transforms/vectors.html ;
	*/
	__class (c_vec2) {
	public:
		 c_vec2 (void) = default; c_vec2 (const c_vec2&) = delete; c_vec2 (c_vec2&&) = delete;
		~c_vec2 (void) = default;

		__method (Get_angle);
		__method (Get_dot);

	private:
		c_vec2& operator = (const c_vec2&) = delete; c_vec2& operator = (c_vec2&&) = delete;
	};

	__class (c_vec3) {
	public:
		 c_vec3 (void) = default; c_vec3 (const c_vec3&) = delete; c_vec3 (c_vec3&&) = delete;
		~c_vec3 (void) = default;
	/* (1) test case $dot:
	   (1.1) creating 2 (two) vectors along x-axis and y-axis and getting their dot product;
	         result: dot product equals to 0.0f (comparison with epsilon value is required), vectors are orthogonal;
	   (1.2) changing the end point of one of two vectors (1.1);
	         result: dot product does *not* equal to 0.0f, vectors are *not* orthogonal;
	*/
		__method (Cross);
		__method (Dot);       // The lines are perpendicular (orthogonal) if and only if their dot product is zero.
		__method (Length);
	/* (2) test case $negate:
	   (2.1) creating 2 (two) vectors: one of them with any values and signs of its elements, the second is the copy of the first vector;
	   (2.2) negating the first vector twice;
	         result: the first vector keeps the same values and signs, and equals to its copy;
	*/
		__method (Negate);
	/* (3) test case $normalize:
	   (3.1) creating 2 (two) vectors with the same values of elements for checking two different normilize methods;
	   (3.2) calling 'normalize' method on both vectors and compare elapsed time;
	         result: 'using bits level' method is slower in comparison with 'std::sqrtf()';
	   (3.3) sets one of the vectors to 0.0f (all elements) and tries to normalize it;
	         result: the vector being normalized remains the same;
	*/
		__method (Normalize);
	private:
		c_vec3& operator = (const c_vec3&) = delete; c_vec3& operator = (c_vec3&&) = delete;
	};
	/*
		Unfortunately there is no possibility to create test method with input arguments,
		it can be solved by using Google test units, or through outside storage of required input arguments without hardcode and re-compiling the test project,
		for example the usage of the system registry or ini-file;
	*/
	__class (c_vec4) {
	public:
		 c_vec4 (void) = default; c_vec4 (const c_vec4&) = delete; c_vec4 (c_vec4&&) = delete;
		~c_vec4 (void) = default;
		/* (1) test case $dot is the same as for vec_3, but only with one condition: reference to 3D vector is gotten from 4D vector;
		       https://stackoverflow.com/questions/10759206/how-to-calculate-vec4-cross-product-with-glm ;
		*/
		__method (Cross);
		__method (Dot);
		__method (Length);
		__method (Negate);
		__method (Normalize);

	private:
		c_vec4& operator = (const c_vec4&) = delete; c_vec4& operator = (c_vec4&&) = delete;
	};

}}}}}

#endif/*_EBO_TEST_$M$_VECTOR_H_INCLUDED*/