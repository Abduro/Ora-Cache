#ifndef _GL_SHD_STATUS_H_INCLUDED
#define _GL_SHD_STATUS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Sep-2025 at 08:09:23.032, UTC+4, Batumi, Tuesday;
	This Ebo Pack OpenGL shader status wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "gl_shd_id.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace shader {

	class CStatus : private no_copy  {
	public:
		CStatus (const uint32_t _shader_id = 0); ~CStatus (void);

		TError&  Error (void) const;
		static
		bool     Get (const uint32_t _param_id, const uint32_t _shader_id, CError&);
		bool     Get (const uint32_t _param_id) const;
		static
		bool  Is_compiled (const uint32_t _shader_id, CError&);
		bool  Is_compiled (void) const;       // if result is 'false' the details can be received by calling the log info function;
		const
		CShaderId& ShaderId (void) const;
		CShaderId& ShaderId (void) ;

		CStatus& operator <<(const uint32_t _shader_id);

	private:
		mutable
		CError     m_error ;
		CShaderId  m_shd_id;		
	};

}}}}

#endif/*_GL_SHD_STATUS_H_INCLUDED*/