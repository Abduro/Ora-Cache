#ifndef _GL_PROCS_LIGHT_H_INCLUDED
#define _GL_PROCS_LIGHT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Jun-2026 at 12:30:32.365, UTC+4, Batumi, Friday;
	This is OpenGL lighting  wrapper interface declaration file;
*/
#include "gl_procs_basic.h"
namespace open_gl { namespace procs { namespace ver_1_1 {

	/* the query to Google AI: GL_LIGHTING is enabled by default in OprnGL 1.1 or is disabled?
	GL_LIGHTING is disabled by default in OpenGL 1.1.
	When it is disabled, OpenGL uses the current primary color set by glColor* to render primitives.
	When it is explicitly enabled by using glEnable(GL_LIGHTING), OpenGL switches to calculating vertex colors based on surface materials and active light sources.
	*/
	class CLight : public CBasic { typedef CBasic TBase;
	public:
	/* https://learn.microsoft.com/en-us/windows/win32/opengl/gllightf ; sets light source parameter(s);
	   https://learn.microsoft.com/en-us/windows/win32/opengl/glgetlightfv ' gets light source parameter(s);
	*/
		class CSource : public CBasic { typedef CBasic TBase;
		public:
			CSource (void); CSource (const CSource&) = delete; CSource (CSource&&) = delete; ~CSource (void) = default;
		private:
			CSource& operator = (const CSource&) = delete; CSource& operator = (CSource&&) = delete;
		};
	public:
		CLight (void); CLight (const CLight&) = delete; CLight (CLight&&) = delete; ~CLight (void) = default;

		err_code Get (void);                  // gets current state of lighting;
		err_code Set (const bool _on_or_off); // sets current state of lighting to 'on' or 'off';

		bool Is_on (void) const; // returns current state of the lighting, it is updated by calling this::Get();
		const
		CSource& Source (void) const;
		CSource& Source (void) ;

	private:
		CLight& operator = (const CLight&) = delete; CLight& operator = (CLight&&) = delete;
		bool    m_enabled;
		CSource m_source;
	};

	class CLtToggle {
	public:
		 CLtToggle (const bool _on_or_off); // if '_on_or_off' is 'false' the lighting is turned 'off', otherwise the light is turned 'on';
		 CLtToggle (void) = delete; CLtToggle (const CLtToggle&) = delete; CLtToggle (CLtToggle&&) = delete;
		~CLtToggle (void); // checks the current state of lighting and trigger it to opposite state;

		const
		CLight& operator ()(void) const; // gets a reference to the light object which state is being under control; (ro);
		CLight& operator ()(void) ;      // gets a reference to the light object which state is being under control; (rw);

	private:
		CLtToggle& operator = (const CLtToggle&) = delete; CLtToggle& operator = (CLtToggle&&) = delete;
		CLight m_light;
	};
}}}

#define LtToggle(on_or_off) ::open_gl::procs::ver_1_1::CLtToggle toggle(on_or_off);

#endif/*_GL_PROCS_LIGHT_H_INCLUDED*/