#ifndef _GL_CONTEXT_H_INCLUDED
#define _GL_CONTEXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-Aug-2025 at 12:33:39.591, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' context base interface declaration file;
*/
#include "gl_ctx_base.h"
#include "gl_ctx_device.h"

namespace open_gl { namespace context {

	/* The main idea is composed by several steps:
		(1) creates fake window;
		(2) gets renderer context that is based on regular device context handle; *important* the rendering context must be set as current one;
		(3) querying pointers to the OpenGL functions that are required for creating real draw context of OpenGL version at least 3.0;
		(4) creates new window that is expected to be the surface of the drawing;
		(5) using new window device context for setting pixel format by using OpenGL functions been loaded on the previous step (#3);
		(6) creating the OpenGL draw rendering/graphics context and making it current;
	*/
namespace ver_1_1 {
	// this class of draw rendering is used for basic version 1.1 of OpenGL, no ARB extension is supposed to be applied;
	class CGraphics : public context::CBase { typedef context::CBase TBase;
	public:
		 CGraphics (void);  CGraphics (const CGraphics&) = delete; CGraphics (CGraphics&&) = delete;
		~CGraphics (void);

		static _pc_sz Class (void);   // returns this class name for debug purposes;

		/* for creating draw rendering/graphics context the device context is required that can be created by:
		(1) message-only aka fake window for initializing fake device context in order to receive the required/desired pixel format descriptor;
		(2) the same as above, but the device context is gotten from window of draw surface, not fake one;
		*/
		err_code  Create (void);      // it is supposed the target window is set through parent class and its HDC is already gotten;
		err_code  Create (const HDC); // the device context that is already set to required pixel format;

		err_code  MakeCurrent (const bool _yes_or_no);
		err_code  Swap (void);        // replaces graphics context by the target window device context, i.e. makes draw on the screen;

	private:
		CGraphics& operator = (const CGraphics&) = delete; CGraphics& operator = (CGraphics&&) = delete;
	};
}
namespace arb {
	// this class is used for later versions of the OpenGL that include ARB extension;
	class CGraphics : public context::CBase { typedef context::CBase TBase;
	public:
		 CGraphics (void);  CGraphics (const CGraphics&) = delete; CGraphics (CGraphics&&) = delete;
		~CGraphics (void);

		err_code  Create (void);
		err_code  Create (const HDC);

		err_code  MakeCurrent (const bool _yes_or_no);
		err_code  Swap (void);

	private:
		CGraphics& operator = (const CGraphics&) = delete; CGraphics& operator = (CGraphics&&) = delete;
	};

}}}

#endif/*_GL_CONTEXT_H_INCLUDED*/