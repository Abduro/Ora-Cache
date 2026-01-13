#ifndef _TEST_CASE_$D$_SHADER_H_INCLUDED
#define _TEST_CASE_$D$_SHADER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 15:51:44.122, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL shaders' wrapper interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$d$.defs.h"
#include "ebo_test_$d$.ctx.h"
#include "gl_defs.h"
#include "gl_shader.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {

	using namespace ex_ui::draw::open_gl;

	using CShader   = ex_ui::draw::open_gl::CShader;
	using $Fragment = ex_ui::draw::open_gl::shader::CFragment;
	using $Vertex   = ex_ui::draw::open_gl::shader::CVertex;
	// this class especially intended for shader source code file compilation check; no shared renderer components is used;
	class C$Base : public TPipe {
	public:
		C$Base (const e_object = e_object::e_grid);
		C$Base (const C$Base&) = delete; C$Base (C$Base&&) = delete; ~C$Base (void) = default;

		err_code Compile(void);        // it is supposed the object target is already set; device context must be created too;
		err_code Create (const $Type); // creates a shader of given type;
		err_code Delete (void);        // deletes a shader;

		TError&  Error  (void) const;
		const
		CShader& Ref (void) const;
		CShader& Ref (void) ;

		static err_code Compile(CShader&, const e_object, CError&); // the input shader has its type, target object is for loading appropriate source code file;
		static err_code Create (CShader&, const $Type, CError&); // device contex is created inside of this proc; such behaviour needs a review;
		static err_code Delete (CShader&, CError&); // deletes the given shader;

	protected:
		C$Base& operator = (const C$Base&) = delete; C$Base& operator = (C$Base&&) = delete;
		CError   m_error;
		CShader  m_shader; // this is isolated class from the renderer draw pipeline;
	};

	class C$Frag : public C$Base {
	public:
		C$Frag (const e_object = e_object::e_grid); ~C$Frag (void) = default;

		err_code Create (void); // creates a fragment shader;
	};

	class C$Vert : public C$Base {
	public:
		C$Vert (const e_object = e_object::e_grid); ~C$Vert (void) = default;

		err_code Create (void); // creates a vertex shader;
	};

	// the shaders' class uses program shader cache that is declared in gl_$_cache.h;
	class C$_enum : public TPipe {
	public:
		C$_enum (const e_object = e_object::e_grid);
		C$_enum (const C$_enum&) = delete; C$_enum (C$_enum&&) = delete; ~C$_enum (void) = default;

		err_code Create (void); // creates all shaders;

		const
		$Fragment& Fragment (void) const; // gets the reference to fragment shader of the program by given object type;
		$Fragment& Fragment (void) ;      // gets the reference to fragment shader of the program by given object type;

		TError&  Error  (void) const;
		const
		$Vertex& Vertex (void) const; // gets the reference to vertex shader of the program by given object type;
		$Vertex& Vertex (void)      ; // gets the reference to vertex shader of the program by given object type;
	private:
		C$_enum& operator = (const C$_enum&) = delete; C$_enum& operator = (C$_enum&&) = delete;
		CError   m_error;
	};

}}}}}

#endif/*_TEST_CASE_$D$_SHADER_H_INCLUDED*/