#ifndef _VIRT_SPACE_H_INCLUDED
#define _VIRT_SPACE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Feb-2026 at 12:49:07.329, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL 3D virtual camera space interface declaration file;
*/
#include "math.defs.h"
#include "math.matrix.h"
#include "math.mat.rotate.h"

#include "math.quat.h"
#include "math.vector.h"

namespace ex_ui { namespace draw { namespace open_gl { using namespace shared::defs; using namespace ex_ui::draw::open_gl::math;
namespace space { namespace axes {

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
	class CBase {
	protected:
		CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete; ~CBase (void) = default;
	public:
		const
		vec_3&    Angle (void) const;
		vec_3&    Angle (void);
		const
		c_mat4x4& Get_matrix (void) const;
		c_mat4x4& Get_matrix (void);
		const
		vec_3&    Pos (void) const;
		vec_3&    Pos (void);

	protected:
		vec_3     m_angle; // angle: x:pitch|y:yaw|z:roll;
		rot_4x4   m_mat;   // model|view|model-view matrix;
		vec_3     m_pos;   // model/object position;
	private:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
	};
#pragma region __refs_g
	// https://learnopengl.com/Getting-started/Coordinate-Systems ;
	// https://www.songho.ca/opengl/gl_transform.html ;
	// https://stackoverflow.com/questions/5550620/the-purpose-of-model-view-projection-matrix << https://stackoverflow.com/a/5554162/4325555 ;
#pragma endregion
	/* Local space is the coordinate space that is local to an object (model), i.e. where the object begins in.
	   the object/model coordinates are transformed to the eye/view coordinates with GL_MODELVIEW matrix;
	*/
	class CModel : public CBase {
	public:
		using CAxes = axes::CDynamic;
		CModel (void); ~CModel (void) = default;
		const
		CAxes& Axes (void) const;
		CAxes& Axes (void);
		void Update (void); // updates model matrix: transforms objects from object/local space to world space; the order: rotate-Z >> rotate-Y >> rotate-X >> translation;
	private:
		CAxes  m_axes;
	};
	/* This is the coordinate space in which all objects are located.
	*/
	class CWorld : public CBase {
	public:
		using CAxes = axes::CFixed;
		CWorld (void); ~CWorld (void) = default;
		const
		CAxes& Axes (void) const;
		CAxes& Axes (void);
		const
		CModel&   Model (void) const;
		CModel&   Model (void);
		/* https://www.songho.ca/opengl/gl_transform.html:
		   GL_MODELVIEW matrix combines viewing matrix and modeling matrix into one matrix.
		   
		*/
		const
		c_mat4x4& Get_model_view (void) const;
		c_mat4x4& Get_model_view (void);

	private:
		CAxes  m_axes;
		CModel m_model;
	};
	/* The view space is the space as seen from the camera's point of view. The world space coordinates are transfered by applying
	   translation and/or rotation to view scene; These combined transformations are generally stored inside a view matrix that transforms world coordinates to view space.
	*/
	class CView : public CBase {
	public:
		using CAxes = axes::CDynamic;
		CView (void); ~CView (void) = default;
		const
		CAxes& Axes (void) const;
		CAxes& Axes (void);
		// the translation of position values is negated, because the whole scene is moved with the inverse of camera transform;
		void Update (void); // transforms the camera (viewing matrix) from world space to eye space; the order: translation >> rotate-X >> rotate-Y >> rotate-Z;
		const
		CWorld& World (void) const;
		CWorld& World (void);

	private:
		CAxes   m_axes;
		CWorld  m_world;
	};
}
}}}

#endif/*_VIRT_SPACE_H_INCLUDED*/