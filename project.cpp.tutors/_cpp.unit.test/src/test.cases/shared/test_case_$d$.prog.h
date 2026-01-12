#ifndef _TEST_CASE_$D$_PROG_H_INCLUDED
#define _TEST_CASE_$D$_PROG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 15:36:34.036, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL shader program wrapper interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$d$.defs.h"
#include "ebo_test_$d$.shader.h"
#include "gl_program.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {

	using namespace ex_ui::draw::open_gl;

	using CProgram  = ex_ui::draw::open_gl::CProgram;

	// the pipeline helps to identify the target draw object; this program class uses global renderer components, shaders for example;
	class CProg : public TPipe {
	public:
		class COpts {
			enum e_opts : uint32_t {
				e_link  = 0x0, // 'link' program option flag index;
				e_use_$ = 0x1, // 'use shaders' flag index;
			};
			static const uint32_t u_opt_count = e_opts::e_use_$ + 1u;
		public:
			COpts (void) ; ~COpts (void) = default; COpts (const COpts&) = delete; COpts (COpts&&) = delete;

			bool Link (void) const;       // if this option is 'true'; the program will be linked after its creation; it is assumed the shaders are used also;
			bool Link (const bool);       // sets the 'link' option value, returns 'true' in case of option value change;

			bool UseShaders (void) const; // if this option is 'true'; the program creates shaders when it is create itself;
			bool UseShaders (const bool); // sets the 'shader use' option value, returns 'true' in case of option value change;

		private:
			COpts& operator = (const COpts&) = delete; COpts& operator = (COpts&&) = delete;
			bool  m_b_opts[u_opt_count];
		};
	public:
		CProg (const e_object = e_object::e_grid); // creates grid program by default for testing matrices throug shaders;
		CProg (const CProg&) = delete; CProg (CProg&&) = delete; ~CProg (void) = default;

		err_code Attach (const CShader&); // for this program link management;
		err_code Detach (const CShader&); // for this program link management;

		err_code Create (void);
		err_code Delete (void);
		TError&  Error  (void) const;

		err_code Link (void); // links this program;

		const
		COpts&   Opts (void) const;
		COpts&   Opts (void) ;

	private:
		CProg& operator = (const CProg&) = delete; CProg& operator = (CProg&&) = delete;
		CError   m_error;
		COpts    m_opts ;
	};

}}}}}

#endif/*_TEST_CASE_$D$_PROG_H_INCLUDED*/