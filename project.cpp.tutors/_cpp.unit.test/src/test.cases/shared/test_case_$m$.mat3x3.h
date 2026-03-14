#ifndef _TEST_CASE_$M$_MAT3x3_H_INCLUDED
#define _TEST_CASE_$M$_MAT3x3_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Feb-2026 at 15:10:08.201, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix 3x3 uint test interface declaration file for using in test cases' adapters;
*/
#include "ebo_test_$m$.defs.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	class c_mtx_3x3 {
	public:
		 c_mtx_3x3 (void) = default; c_mtx_3x3 (const c_mtx_3x3&) = delete; c_mtx_3x3 (c_mtx_3x3&&) = delete;
		~c_mtx_3x3 (void) = default;
		static
		_pc_sz To_str (const t_mat3x3&, const bool _b_cls); // if 'b_cls' is set to 'true', this class name is added to the log record;

	private:
		c_mtx_3x3& operator = (const c_mtx_3x3&) = delete; c_mtx_3x3& operator = (c_mtx_3x3&&) = delete;
	};

	struct s_rot_criteria {
		float m_f_angle;          // rotation angle;
		axes_t::e_axes m_e_axis;  // the axis to rotate around;
		bool  m_b_print_cls;      // output class name flag;

		s_rot_criteria (void) : m_f_angle(0.0f), m_e_axis(axes_t::e_z_axis), m_b_print_cls(true) {}
		s_rot_criteria (const float _f_angle, const axes_t::e_axes _e_axis, const bool _b_print_cls)
			: m_f_angle(_f_angle), m_e_axis(_e_axis), m_b_print_cls(_b_print_cls) {
		}
	};

	typedef s_rot_criteria s_rot_cri_t;

	struct s_rot_cri_ex : public s_rot_cri_t {
		vec_2 m_v_pivot;   // pivot point;
		bool  m_b_use_eps; // using epsilon is for better result readability, not accuracy;

		s_rot_cri_ex (void) : m_b_use_eps(true) {} // pivot point is set to axes origin (0,0) by default;
		s_rot_cri_ex (const t_set_2& _v_pivot, const bool _b_use_eps) : m_b_use_eps(_b_use_eps), m_v_pivot(_v_pivot) {}
		const
		s_rot_cri_t& operator ()(void) const { return (s_rot_cri_t&)(*this); }
		s_rot_cri_t& operator ()(void)       { return (s_rot_cri_t&)(*this); }

		s_rot_cri_ex& operator << (const float _f_angle) { s_rot_cri_t::m_f_angle = _f_angle; return *this; }
		s_rot_cri_ex& operator << (const axes_t::e_axes _e_axis) { s_rot_cri_t::m_e_axis = _e_axis; return *this; }
	};

	class c_rot_3x3 {
	public:
		 c_rot_3x3 (void) = default; c_rot_3x3 (const c_rot_3x3&) = delete; c_rot_3x3 (c_rot_3x3&&) = delete;
		~c_rot_3x3 (void) = default;

		t_rot3x3& Prepare (const s_rot_cri_t&); // returns the matrix prepared for rotation; _b_cls is for class name output;

		vec_2& Rotate (const s_rot_cri_ex&, vec_2& _to_rot); // returns vertex pos rotated in 2D space (around z-axis); pivot point is taken into account;
		vec_3& Rotate (const s_rot_cri_ex&, vec_3& _to_rot);

		const
		t_rot3x3& operator ()(void) const;
		t_rot3x3& operator ()(void);

	private:
		c_rot_3x3& operator = (const c_rot_3x3&) = delete; c_rot_3x3& operator = (c_rot_3x3&&) = delete;
		t_rot3x3 m_rot3x3;
	};
}}}}}

#endif/*_TEST_CASE_$M$_MAT3x3_H_INCLUDED*/