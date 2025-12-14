#ifndef _GL_DEFS_H_INCLUDED
#define _GL_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2025 at 12:08:35.186, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL common definitions' declaration file;
*/
#include "shared.defs.h"
// https://learn.microsoft.com/en-us/windows/win32/opengl/opengl-on-windows-nt--windows-2000--and-windows-95-98 ; << old but still valid;
// https://github.com/KhronosGroup/OpenGL-Registry ;
#include <gl/gl.h> // the headers' include order is important: windows.h must go first;
#include "gl_error.h"

#pragma comment(lib, "opengl32.lib")

namespace ex_ui { namespace draw { namespace open_gl {

	using namespace shared::defs;

	using CErr_ex = CError_ex;
	using TErr_ex = const CErr_ex;

	class no_copy { // maybe it's something like boost::noncopyable;
	protected:
		 no_copy (void) = default; no_copy (const no_copy&) = delete; no_copy (no_copy&&) = delete;
		~no_copy (void) = default;

	protected:
		 no_copy& operator = (const no_copy&) = delete;
		 no_copy& operator = (no_copy&&) = delete;
	};

	class CPipeline : private no_copy {
	public:
		CPipeline (void); ~CPipeline (void);
		enum e_targets : uint32_t {
		e_none = 0x0, // due to this element the enumeration other elements cannot be used as indices for getting an item from array of open_gl wrappers;
		e_grid = 0x1,
		e_tria = 0x2,
		};
		static const uint32_t u_tgt_count = e_targets::e_tria - 1;
	public:
		using e_object = CPipeline::e_targets;

		e_object  Target (void) const;     // gets pipeline target object;
		bool      Target (const e_object); // sets pipeline target object; returns 'true' in case of target object value change;
	protected:
		e_object  m_target ;
	};
}}}

#endif/*_GL_DEFS_H_INCLUDED*/