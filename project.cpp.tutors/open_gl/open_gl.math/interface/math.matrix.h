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
	   regarding using SYCL (System-wide Compute Language) buffer : (cl_khr_gl_sharing one of the extensions)
	...as the storage of a std::vector is *heap-allocated* in order to allow it to be resized, the overall structure is *non-contiguous*,
	   which is a requirement for moving data to and from a device via a SYCL buffer... the excerpt from the answer given by gordonbrown589;
	   perhaps, using fixed-sized std::array is the more preferable way in comparison with std::vector;
	*/
	/* to follow the above note using std::array data storage is good due to its fixed size at compile time, thus the array can be used on stack;
	   the pitfall is matrix2x2 cannot be inherited by matrix3x3 and the same is for matrix4x4,
	   in order to support inheritance dynamic size data storage can help only, like std::vector;
	*/
	// the following approach can be used: (1) each matrix defines fixed array of entries; (2) matrix of entry indices is used;
/* all matrix entries are represented by their indices;
      mat_2x2   mat_3x3     mat_4x4
cols:    #0 #1  #0  #1  #2  #0  #1  #2  #3
rows: #0  0  2  m2  m2   6  m3  m3  m3  0xc
      #1  1  3  m2  m2   7  m3  m3  m3  0xd
      #2         4   5   8  m3  m3  m3  0xe
      #3                     9  0xa 0xb 0xf

      index sets for each matrix cols and rows:
      mat_2x2:                            mat_3x3:                                  mat_4x4
      col_#0 -> {0, 1}; row_#0 -> {0, 2}; col_#0 -> {0, 1, 4}; row_#0 -> {0, 2, 6}; col_#0 -> {0x0, 0x1, 0x4, 0x9}; row_#0 -> {0x0, 0x2, 0x6, 0xc};
      col_#1 -> {2, 3}; row_#1 -> {1, 3}; col_#1 -> {2, 3, 5}; row_#1 -> {1, 3, 7}; col_#1 -> {0x2, 0x3, 0x5, 0xa}; row_#1 -> {0x1, 0x3, 0x7, 0xd};
                                          col_#2 -> {6, 7, 8}; row_#2 -> {4, 5, 8}; col_#2 -> {0x6, 0x7, 0x8, 0xb}; row_#2 -> {0x4, 0x5, 0x8, 0xe};
                                                                                    col_#3 -> {0xc, 0xd, 0xe, 0xf}; row_#3 -> {0x9, 0xa, 0xb, 0xf};
      using index set inheritance:
      mat_2x2:                            mat_3x3:                                            mat_4x4
      col_#0 -> {0, 1}; row_#0 -> {0, 2}; col_#0 -> {{m2x2.c0}, 4}; row_#0 -> {{m2x2.r0}, 6}; col_#0 -> {{m3x3.c0}, 0x9}; row_#0 -> {{m3x3.r0}, 0xc};
      col_#1 -> {2, 3}; row_#1 -> {1, 3}; col_#1 -> {{m2x2.c1}, 5}; row_#0 -> {{m2x2.r1}, 7}; col_#1 -> {{m3x3.c1}, 0xa}; row_#1 -> {{m3x3.r1}, 0xd};
                                          col_#2 -> no inheritance;                           col_#2 -> {{m3x3.c2}, 0xb}; row_#2 -> {{m3x3.r2}, 0xe};
                                                                                            col_#3 -> no inheritance;
      instead of matrix cols' and rows' indices sets the matrix of indices can be used:
      mat_2x2:  mat_3x3:    mat_4x4:
cols:    #0 #1  #0  #1  #2  #0  #1  #2  #3
rows: #0  0  2   0   2   6   0   2   6 0xc
      #1  1  3   1   3   7   1   3   7 0xd
      #2         4   5   8   4   5   8 0xe
      #3                     9 0xa 0xb 0xf; these matrices can be defined as static volatile;
*/
	class c_comparator {
	public:
		 c_comparator (const float _f_threshold = defs::f_epsilon); c_comparator (const c_comparator&) = delete; c_comparator (c_comparator&&) = delete;
		~c_comparator (void) = default;

		static bool Do_it (const c_mat3x3& _lhs, const c_mat3x3& _rhs, const float _f_threshold = defs::f_epsilon);
		static bool Do_it (const s_vec_3& _lhs, const s_vec_3& _rhs, const float _f_threshold = defs::f_epsilon);

		float Threshold (void) const;
		void  Threshold (const float);

	private:
		c_comparator& operator = (const c_comparator&) = delete; c_comparator& operator = (c_comparator&&) = delete;
		float m_threshold;
	};
}}}}

#endif/*__MATH_MATRIX_H_INCLUDED*/