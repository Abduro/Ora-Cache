#ifndef _TEST_CASE_$D$_BUFFER_H_INCLUDED
#define _TEST_CASE_$D$_BUFFER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jan-2026 at 12:54:59.091, UTC+4, Batumi, Ssturday;
	This is Ebo Pack OpenGL vertex buffer object wrapper interface declaration file for using in test cases adapters;
*/
#include "test_case_$d$.ctx.h"
#include "gl_buffer.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ex_ui::draw::open_gl;
	using CBuffer = ex_ui::draw::open_gl::vertex::CBuffer;

	using e_bind_targets = ex_ui::draw::open_gl::procs::e_bind_targets;

	class CVertBuffer : public TPipe {
	public:
		CVertBuffer (const e_object = e_object::e_none); ~CVertBuffer (void) = default;
		CVertBuffer (const CVertBuffer&) = delete; CVertBuffer (CVertBuffer&&) = delete;

		TError&  Error (void) const;
		static
		uint32_t Size  (const e_bind_targets, CError&);
		uint32_t Size  (void) const;
		const
		CBuffer& operator ()(void) const;
		CBuffer& operator ()(void);

	private:
		CVertBuffer& operator = (const CVertBuffer&) = delete; CVertBuffer& operator = (CVertBuffer&&) = delete;
		mutable
		CError  m_error;
		CBuffer m_buffer;
	};
}}}}}

#endif/*_TEST_CASE_$D$_BUFFER_H_INCLUDED*/