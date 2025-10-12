#ifndef _GL_BUFFER_H_INCLUDED
#define _GL_BUFFER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Oct-2025 at 21:58:20.910, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL data buffer wrapper interface declaration file;
*/
#include "gl_defs.h"
namespace ex_ui { namespace draw { namespace open_gl {
namespace data {}
	class CBuffer {
	public:
		CBuffer (void); CBuffer (const CBuffer&) = delete; CBuffer (CBuffer&&) = delete; ~CBuffer (void);

		err_code Create  (void);
		err_code Destroy (void);

		TError&  Error (void) const;
		uint32_t Id (void) const;
		static
		bool  Is_valid (const uint32_t _buffer_id, CError&);
		bool  Is_valid (void) const; // checks the reference of the buffer identifier to buffer object; in case of failure the error status is updated;

	private:
		CBuffer& operator = (const CBuffer&) = delete; CBuffer& operator =  (CBuffer&&) = delete;
		mutable
		CError   m_error;
		uint32_t m_buf_id;
	};
}}}
#endif/*_GL_BUFFER_H_INCLUDED*/