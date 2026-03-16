#ifndef _VIRT_SPACE_H_INCLUDED
#define _VIRT_SPACE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Feb-2026 at 12:49:07.329, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL 3D virtual camera space interface declaration file;
*/
#include "math.defs.h"
#include "math.vector.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace space { namespace axes { using namespace shared::defs; using namespace ex_ui::draw::open_gl::math;
#pragma region __refs_g
	// https://learnopengl.com/Getting-started/Coordinate-Systems ;
	// https://www.songho.ca/opengl/gl_transform.html ;
	// https://stackoverflow.com/questions/5550620/the-purpose-of-model-view-projection-matrix << https://stackoverflow.com/a/5554162/4325555 ;
#pragma endregion
	class CBase {
	public: static const uint32_t u_count = 3;
	protected:
		CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete; ~CBase (void) = default;
	protected:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
		vec_3  m_v_axes[CBase::u_count];
	};

	class CFixed : public CBase {
	public: enum e_axes : uint32_t { e_x_axis = 0x0, e_y_axis, e_z_axis };
		
		CFixed (void); ~CFixed (void) = default;

		const
		vec_3& Get (const e_axes) const;
		vec_3& Get (const e_axes);
		static
		_pc_sz To_str (const CFixed::e_axes);

		const vec_3& X (void) const; vec_3& X (void);
		const vec_3& Y (void) const; vec_3& Y (void);
		const vec_3& Z (void) const; vec_3& Z (void);
	};

	class CDynamic : public CBase {
	public: enum e_axes : uint32_t { e_fwd = CFixed::e_z_axis, e_left = CFixed::e_x_axis, e_up = CFixed::e_y_axis };

		CDynamic (void); ~CDynamic (void) = default;

		const
		vec_3& Get (const e_axes) const;
		vec_3& Get (const e_axes);

		const vec_3& Fwd (void) const; vec_3& Fwd (void);
		const vec_3& Left (void) const; vec_3& Left (void);
		const vec_3& Up (void) const; vec_3& Up (void);
	};
}	
}}}}

typedef ex_ui::draw::open_gl::space::axes::CFixed axes_t;

#endif/*_VIRT_SPACE_H_INCLUDED*/