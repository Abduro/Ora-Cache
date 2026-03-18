/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Dec-2025 at 18:25:16.417, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' generic data matrix interface implementation file;
*/
#include "math.matrix.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math { namespace _impl4 { void __warning_lnk_4221 (void) {}}}}}}

using namespace ex_ui::draw::open_gl::math;

#pragma region cls::c_comparator{}

c_comparator::c_comparator (const float _f_threshold/* = defs::f_epsilon*/) : m_threshold(_f_threshold) {}

bool  c_comparator::Do_it (const c_mat3x3& _lhs, const c_mat3x3& _rhs, const float _f_threshold/* = defs::f_epsilon*/) {
	_lhs; _rhs; _f_threshold;
	static CString cs_diff;
	for (uint32_t i_ = 0; i_ < _lhs.Data().size() && i_ < _rhs.Data().size(); i_++) {
		const float f_diff = ::abs(::abs(_lhs.Data().at(i_)) - ::abs(_rhs.Data().at(i_)));

		if (::abs(_f_threshold) < f_diff) {
			cs_diff.Format(_T("%9.7f"), f_diff); // for debug purposes, it's better to see decimal representation of float in comparison with exponential;
			return false;
		}
	}
	return true;
}

bool  c_comparator::Do_it (const c_mat4x4& _lhs, const c_mat4x4& _rhs, const float _f_threshold/* = defs::f_epsilon*/) {
	_lhs; _rhs; _f_threshold;
	static CString cs_diff;
	for (uint32_t i_ = 0; i_ < _lhs.Data().size() && i_ < _rhs.Data().size(); i_++) {
		const float f_diff = ::abs(::abs(_lhs.Data().at(i_)) - ::abs(_rhs.Data().at(i_)));

		if (::abs(_f_threshold) < f_diff) {
			cs_diff.Format(_T("%9.7f"), f_diff); // for debug purposes, it's better to see decimal representation of float in comparison with exponential;
			return false;
		}
	}
	return true;
}

bool  c_comparator::Do_it (const s_vec_3& _lhs, const s_vec_3& _rhs, const float _f_threshold/* = defs::f_epsilon*/) {
	_lhs; _rhs; _f_threshold;
	static CString cs_diff;
	static float f_diff = 0.0f;

	if (::abs(_f_threshold) < ::abs((f_diff = _lhs.x - _rhs.x))) { cs_diff.Format(_T("%9.7f"), f_diff); return false; }
	if (::abs(_f_threshold) < ::abs((f_diff = _lhs.y - _rhs.y))) { cs_diff.Format(_T("%9.7f"), f_diff); return false; }
	if (::abs(_f_threshold) < ::abs((f_diff = _lhs.z - _rhs.z))) { cs_diff.Format(_T("%9.7f"), f_diff); return false; }
	return true;
}

bool  c_comparator::Do_it (const s_vec_4& _lhs, const s_vec_4& _rhs, const float _f_threshold/* = defs::f_epsilon*/) {
	_lhs; _rhs; _f_threshold;
	static CString cs_diff;
	static float f_diff = 0.0f;

	if (::abs(_f_threshold) < ::abs((f_diff = _lhs.w - _rhs.w))) { cs_diff.Format(_T("%9.7f"), f_diff); return false; }

	return c_comparator::Do_it(_lhs(), _rhs(), _f_threshold);
}

float c_comparator::Threshold (void) const { return this->m_threshold; }
void  c_comparator::Threshold (const float _f_value) { this->m_threshold = _f_value; }

bool c_comparator::operator ()(const c_mat3x3& _lhs, const c_mat3x3& _rhs, const float _f_threshold) { return c_comparator::Do_it(_lhs, _rhs, _f_threshold); }
bool c_comparator::operator ()(const c_mat4x4& _lhs, const c_mat4x4& _rhs, const float _f_threshold) { return c_comparator::Do_it(_lhs, _rhs, _f_threshold); }

bool c_comparator::operator ()(const s_vec_3& _lhs, const s_vec_3& _rhs, const float _f_threshold) { return c_comparator::Do_it(_lhs, _rhs, _f_threshold); }
bool c_comparator::operator ()(const s_vec_4& _lhs, const s_vec_4& _rhs, const float _f_threshold) { return c_comparator::Do_it(_lhs, _rhs, _f_threshold); }

#pragma endregion