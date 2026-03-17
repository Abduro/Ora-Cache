/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 09:10:27.386, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib common definitions' uint test interface implementation file; 
*/
#include "ebo_test_$m$.defs.h"

using namespace ebo::boo::test::open_gl::math;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl_3 { void __warning_lnk_4006 (void) {}}}}}

#pragma region cls::c_ada_4x4{}

static t_mat3x3 cached_3x3;
static t_mat4x4 cached_4x4;

c_adapter::c_adapter (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& c_adapter::Error (void) const { return this->m_error; }

t_mat3x3& c_adapter::operator << (const ::glm::mat3x3& _mat3x3) {
	_mat3x3;
	this->m_error <<__METHOD__<<__s_ok;
	t_mat3x3::Set(::cached_3x3, static_cast<const float*>(::glm::value_ptr(_mat3x3)), this->m_error);
	return ::cached_3x3;
}

t_mat4x4& c_adapter::operator << (const ::glm::mat4x4& _mat4x4) {
	this->m_error <<__METHOD__<<__s_ok;
	t_mat4x4::Set(::cached_4x4, static_cast<const float*>(::glm::value_ptr(_mat4x4)), this->m_error);
	return ::cached_4x4;
}

::glm::mat3x3& c_adapter::operator >> (::glm::mat3x3& _mat3x3) const {
	_mat3x3;
	this->m_error <<__METHOD__<<__s_ok;
	::cached_3x3.Set(static_cast<float*>(::glm::value_ptr(_mat3x3)), this->m_error);
	return _mat3x3;
}

::glm::mat4x4& c_adapter::operator >> (::glm::mat4x4& _mat4x4) const {
	_mat4x4;
	this->m_error <<__METHOD__<<__s_ok;
	::cached_4x4.Set(static_cast<float*>(::glm::value_ptr(_mat4x4)), this->m_error);
	return _mat4x4;
}

c_adapter& c_adapter::operator << (const t_mat3x3& _mat_3x3) {::cached_3x3 = _mat_3x3; return *this; }
c_adapter& c_adapter::operator << (const t_mat4x4& _mat_4x4) {::cached_4x4 = _mat_4x4; return *this; }

const c_adapter& c_adapter::operator >> (t_mat3x3& _out_3x3) const { _out_3x3 = ::cached_3x3; return *this; }
const c_adapter& c_adapter::operator >> (t_mat4x4& _out_4x4) const { _out_4x4 = ::cached_4x4; return *this; }

#pragma endregion
#pragma region cls::c_axes{}

::glm::vec3 c_axes::Get_axis (const axes_t::e_axes _e_axis) {
	_e_axis;
	switch (_e_axis) {
	case axes_t::e_x_axis: return ::glm::vec3(1.0f, 0.0f, 0.0f);
	case axes_t::e_y_axis: return ::glm::vec3(0.0f, 1.0f, 0.0f);
	case axes_t::e_z_axis: return ::glm::vec3(0.0f, 0.0f, 1.0f);
	default: return ::glm::vec3(0.0f, 0.0f, 0.0f);
	}
}
#pragma endregion
#pragma region cls::c_mtx_base

c_mtx_base::c_mtx_base (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& c_mtx_base::Error (void) const { return this->m_error; }

#pragma endregion