#ifndef _GL_SHD_ID_H_INCLUDED
#define _GL_SHD_ID_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Sep-2025 at 08:58:22.875, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL shader identifier wrapper interface declaration file.
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace shader {

	class CShaderId : private no_copy {
	public:
		CShaderId (uint32_t _u_value = 0); ~CShaderId (void);

		TError&  Error (void) const;

		uint32_t Get (void) const;
		err_code Set (const uint32_t);
		static
		bool Is_valid (const uint32_t _shader_id, CError&);
		bool Is_valid (void) const;

		CShaderId& operator <<(const uint32_t _shader_id);

		operator uint32_t (void) const;

	private:
		mutable
		CError   m_error;
		uint32_t m_value;
	};

}}}}
#endif/*_GL_SHD_ID_H_INCLUDED*/