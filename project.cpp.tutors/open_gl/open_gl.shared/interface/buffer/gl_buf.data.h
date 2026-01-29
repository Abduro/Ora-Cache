#ifndef _Gl_BUF_DATA_H_INCLUDED
#define _Gl_BUF_DATA_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Jan-2026 at 17:48:32.622, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL vertex buffer data wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "gl_buf.bind.h"
#include "buffer\gl_procs_buffer.h"
#include "buffer\gl_procs_buf.mem.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace buffer {

	using e_bnd_tgts = ex_ui::draw::open_gl::procs::e_bnd_tgts;
	using e_data_access = ex_ui::draw::open_gl::procs::buffer::e_data_access;

	/*
	the preferable way is to use the buffer identifier for getting the buffer data,
	but for comparison the old way is kept: getting by target type the buffer is bound to;
	*/
	class CData : public TPipe {
	public:
		CData (const e_object = e_object::e_none); CData (const CData&) = delete; CData (CData&&) = delete; ~CData (void) = default;
		const
		CTarget& BoundTo (void) const;      // gets the reference to target object the buffer is bound to; (ro)
		CTarget& BoundTo (void);            // gets the reference to target object the buffer is bound to; (rw)

		uint32_t BufferId (void) const;     // gets buffer identifier value;
		bool     BufferId (const uint32_t); // sets buffer identifier value; no check for input value validity; returns 'true' in case of value change;
		const
		TRawData& Get (void) const;
		TError& Error (void) const;

		bool Is_valid (void) const; // checks for assigning the target type and buffer identifier;

		err_code Query (void); // retrieves data copy of the buffer object;

		CData& operator <<(e_bnd_tgts); // sets the target type the buffer is bound to;
		CData& operator <<(const uint32_t _buf_id);

	private:
		CData& operator = (const CData&) = delete; CData& operator = (CData&&) = delete;
		CError   m_error;
		CTarget  m_bound_to;  // target type which the buffer is bound to;
		uint32_t m_buf_id;
		TRawData m_data;
	};
}}}}

#endif/*_Gl_BUF_DATA_H_INCLUDED*/