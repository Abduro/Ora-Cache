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
	using CData = ex_ui::draw::open_gl::buffer::CData;

	using e_bind_targets = ex_ui::draw::open_gl::procs::e_bind_targets;
	/* for test case of the getting data from vertex buffer the following prerequisites are required:
	(1) creating a shape, for example, a triangle;
	(2) set vertex data to particular values: position and color;
	(3) draw the triangle;
	(4) do *not* destroy objects related to draw operation, this requirement is mandatory;
	(5) get data from the buffer; this step is *test case*;
	(6) destroy all draw objects;
	*/
	class CVertBufData : public TPipe {
	public:
		CVertBufData (const e_object = e_object::e_none); ~CVertBufData (void) = default;
		CVertBufData (const CVertBufData&) = delete; CVertBufData (CVertBufData&&) = delete;

		TError&  Error (void) const;
		err_code Get (void);         // gets vertex buffer data copy of target shape;

	private:
		CVertBufData& operator = (const CVertBufData&) = delete; CVertBufData& operator = (CVertBufData&&) = delete;
		mutable
		CError  m_error;
	};

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