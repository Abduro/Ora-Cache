#ifndef _GL_PROG_ID_H_INCLUDED
#define _GL_PROG_ID_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Sep-2025 at 19:53:21.623, UTC+4, Batumi, Monday;
	This Ebo Pack OpenGL program identifier (aka symbolic name) interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace program {

	class CProgId : private no_copy {
	public:
		CProgId (uint32_t _u_value = 0); ~CProgId (void);

		TError&  Error (void) const;

		uint32_t Get (void) const;
		err_code Set (const uint32_t);
		static
		bool Is_valid (const uint32_t _prog_id, CError&);
		bool Is_valid (void) const;

		void Reset (void); // just sets the value of the prog id to 0 (zero);

		CProgId& operator <<(const uint32_t _prog_id);

		operator uint32_t (void) const;

	private:
		mutable
		CError   m_error;
		uint32_t m_value;
	};

}}}}

#endif/*_GL_PROG_ID_H_INCLUDED*/