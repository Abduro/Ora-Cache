#ifndef _TEST_CASE_$M$_ROT_ARGS_H_INCLUDED
#define _TEST_CASE_$M$_ROT_ARGS_H_INCLUDED
/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 17-Mar-2026 at 09:57:30.768, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' vector rotation criteria interface declaration file;
*/
#include "ebo_test_$m$.defs.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	struct s_rot_criteria {
		float m_f_angle;          // rotation angle;
		axes_t::e_axes m_e_axis;  // the axis to rotate around;
		bool  m_b_print_cls;      // output class name flag;

		s_rot_criteria (void);
		s_rot_criteria (const float _f_angle, const axes_t::e_axes _e_axis, const bool _b_print_cls);

		static _pc_sz To_str (const float _f_angle, const axes_t::e_axes _e_axis, const bool _b_print = false);
	};

	typedef s_rot_criteria s_rot_cri_t;

	struct s_rot_cri_v2 : public s_rot_cri_t {
		vec_2 m_v_pivot;     // pivot point;
		bool  m_b_use_eps;   // using epsilon is for better result readability, not accuracy;

		s_rot_cri_v2 (void); // pivot point is set to axes origin (0,0) by default;
		s_rot_cri_v2 (const t_set_2& _v_pivot, const bool _b_use_eps);
		const
		s_rot_cri_t& operator ()(void) const;
		s_rot_cri_t& operator ()(void)      ;

		s_rot_cri_v2& operator << (const float _f_angle);
		s_rot_cri_v2& operator << (const axes_t::e_axes _e_axis);
	};

	struct s_rot_cri_v3 : public s_rot_cri_t {
	//	vec_3 m_v_pivot;   // pivot point; !attention!: no pivot point by using this type of matrix for rotation in 3d-space;
		bool  m_b_use_eps; // using epsilon is for better result readability, not accuracy;

		s_rot_cri_v3 (void);
		s_rot_cri_v3 (/*const t_set_3& _v_pivot, */const bool _b_use_eps);
		const
		s_rot_cri_t& operator ()(void) const;
		s_rot_cri_t& operator ()(void)      ;

		s_rot_cri_v3& operator << (const float _f_angle);
		s_rot_cri_v3& operator << (const axes_t::e_axes _e_axis);
	};

	struct s_rot_cri_v4 : public s_rot_cri_t { // it very looks like this structure should be inherited from s_rot_cri_v3, but it is not essential for now;
		vec_3 m_v_pivot;   // it is kept as vec_3, because 'w' component is not necessary for rotating around pivot point;
		bool  m_b_use_eps; // using epsilon is for better result readability, not accuracy;

		s_rot_cri_v4 (void);
		s_rot_cri_v4 (const t_set_3& _v_pivot, const bool _b_use_eps);
		const
		s_rot_cri_t& operator ()(void) const;
		s_rot_cri_t& operator ()(void)      ;

		s_rot_cri_v4& operator << (const float  _f_angle);
		s_rot_cri_v4& operator << (const axes_t::e_axes _e_axis);
		s_rot_cri_v4& operator << (const vec_3& _v_pivot);
	};

}}}}}

#endif/*_TEST_CASE_$M$_ROT_ARGS_H_INCLUDED*/