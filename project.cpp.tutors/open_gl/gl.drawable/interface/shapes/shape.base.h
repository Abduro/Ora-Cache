#ifndef _GL_SHAPE_BASE_H_INCLUDED
#define _GL_SHAPE_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Jun-2026 at 13:10:47.144, UTC+4, Batumi, Sunday;
	This is OpenGL drawable shape base interface declaration file.
*/
#include "shape.trans.h"

namespace open_gl { namespace shapes {

	using namespace ::open_gl::procs::ver_1_1;
	using namespace ::open_gl::procs::matrix::ver_1_1;
	/* the query to Google AI: how to name such operations as movement, rotation and scaling in opengl?
	In OpenGL, operations that change an object's position, orientation, or size are collectively known as geometric transformations.
	Specifically, they are referred to as:
	(1) Translation: Moving an object along the x, y, and z axes;
	(2) Rotation: Turning an object around a specified axis or pivot point;
	(3) Scaling: Resizing an object by enlarging or shrinking it along the axes.
	*/
	using namespace ::open_gl::shapes::transfer;
	using CMove = CMove;

	class CBase {
	protected:
		CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete; ~CBase (void) = default;
	public:
		const
		CMove&  Move (void) const;
		CMove&  Move (void) ;
		const
		CRotate& Rotate (void) const;
		CRotate& Rotate (void) ;
		const
		CScale& Scale (void) const;
		CScale& Scale (void) ;

	protected:
		CBase& operator = (const CBase&) = delete;
		CBase& operator = (CBase&&) = delete;
		CScale  m_scale;
		CMove   m_move ;
		CRotate m_rotate;
	};

}}

#endif/*_GL_SHAPE_BASE_H_INCLUDED*/