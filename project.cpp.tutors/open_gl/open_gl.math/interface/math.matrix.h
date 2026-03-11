#ifndef __MATH_MATRIX_H_INCLUDED
#define __MATH_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Dec-2025 at 18:23:09.539, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' generic data matrix interface declaration file;
*/
#include "math.defs.h"
#include "math.vector.h"
#include "math.mat.2x2.h"
#include "math.mat.3x3.h"
#include "math.mat.4x4.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	typedef ::std::vector<::std::reference_wrapper<float>> t_cell_refs;
	/* the very important note from https://community.khronos.org/t/matrix-multiplication-using-2d-std-vector/106457 ;
	   regarding using SYCL (System-wide Compute Language) buffer : (cl_khr_gl_sharing  one of the extensions)
	...as the storage of a std::vector is *heap-allocated* in order to allow it to be resized, the overall structure is *non-contiguous*,
	   which is a requirement for moving data to and from a device via a SYCL buffer... the excerpt from the answer given by gordonbrown589;
	   perhaps, using fixed-sized std::array is the more preferable way in comparison with std::vector;
	*/	
}}}}

#endif/*__MATH_MATRIX_H_INCLUDED*/