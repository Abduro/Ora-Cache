#ifndef _VIRT_VIEW_H_INCLUDED
#define _VIRT_VIEW_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Mar-2026 at 10:48:51.066, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL 3D virtual camera view interface declaration file;
*/
#include "math.defs.h"
#include "math.matrix.h"
#include "math.mat.rotate.h"
#include "virt_space.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace views { using namespace ex_ui::draw::open_gl::math;

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
		rot_4x4_t m_mat;   // model|view|model-view matrix;
		vec_3     m_pos;   // model/object position;
	private:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
	};
	/* Local space is the coordinate space that is local to an object (model), i.e. where the object begins in.
	   the object/model coordinates are transformed to the eye/view coordinates with GL_MODELVIEW matrix;
	*/
	class CModel : public CBase {
	public:
		using CAxes = space::axes::CDynamic;
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
		using CAxes = space::axes::CFixed;
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
		using CAxes = space::axes::CDynamic;
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
}}}}

#endif/*_VIRT_VIEW_H_INCLUDED*/