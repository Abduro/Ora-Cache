#ifndef _TEST_CASE_$D$_SHAPE_2D_H_INCLUDED
#define _TEST_CASE_$D$_SHAPE_2D_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Jan-2026 at 13:36:52.511, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL 2D shape wrapper interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$d$.ctx.h"
#include "shapes\gl_shape.2d.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {

	using namespace ex_ui::draw::open_gl;
#if (1) // the triangle from shape cache is used as the shape for drawing by renderer;
	    // this class is for creating the triangle shape directly, without using the renderer scene;
	using CTriangle = shapes::CTriangle;

	CTriangle&  __tria_accessor (void);

	class C3angle : public TPipe {
	public:
		C3angle (void); C3angle (const C3angle&) = delete; C3angle (C3angle&&) = delete; ~C3angle (void) = default;

		err_code Create (void); // creates a simple triangle and related to the triangle objects, such as vertex array object and vertex buffer object;
		err_code Delete (void); // deletes this shape: the associated program and vertex array object;

		err_code Draw (void);   // calls 'draw' method of the triangle; the 'draw' method is used by the renderer;

		TError&  Error (void) const;

		const
		TPipe& operator ()(void) const;
		TPipe& operator ()(void) ;

	private:
		C3angle& operator = (const C3angle&) = delete; C3angle& operator = (C3angle&&) = delete;
		CError  m_error;
		CCtx_auto m_ctx; // this object is required for shareing the contexts between 'Create' and 'Delete' methods, otherwise each of them creats its own context objects;
	};
#endif
}}}}}

#endif/*_TEST_CASE_$D$_SHAPE_2D_H_INCLUDED*/