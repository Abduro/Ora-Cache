#ifndef _TEST_CASE_$D$_SHADER_H_INCLUDED
#define _TEST_CASE_$D$_SHADER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 15:51:44.122, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL shaders' wrapper interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$d$.defs.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {

	using namespace ex_ui::draw::open_gl;

	using $Fragment = ex_ui::draw::open_gl::shader::CFragment;
	using $Vertex   = ex_ui::draw::open_gl::shader::CVertex;

	// the shaders class uses program shader cache that is declared in gl_$_cache.h;
	class CShaders : public CPipeline { typedef CPipeline TBase;
	public:
		CShaders (const e_object = e_object::e_grid);
		CShaders (const CShaders&) = delete; CShaders (CShaders&&) = delete; ~CShaders (void) = default;

		err_code Create (void); // creates all shaders;

		const
		$Fragment& Fragment (void) const; // gets the reference to fragment shader of the program by given object type;
		$Fragment& Fragment (void) ;      // gets the reference to fragment shader of the program by given object type;

		TError&  Error  (void) const;
		const
		$Vertex& Vertex (void) const; // gets the reference to vertex shader of the program by given object type;
		$Vertex& Vertex (void)      ; // gets the reference to vertex shader of the program by given object type;
	private:
		CShaders& operator = (const CShaders&) = delete; CShaders& operator = (CShaders&&) = delete;
		CError   m_error;
	};

}}}}}

#endif/*_TEST_CASE_$D$_SHADER_H_INCLUDED*/