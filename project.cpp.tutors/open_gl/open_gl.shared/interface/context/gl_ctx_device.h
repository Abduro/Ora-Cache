#ifndef _GL_CTX_DEVICE_H_INCLUDED
#define _GL_CTX_DEVICE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Apr-2026 at 22:19:59.284, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' graphics device interface (GDI) and device context (DC) wrappers' interface declaration file;
*/
#include "context\gl_ctx_base.h"
#include "gl_format.h"
#include "shared.wnd.fake.h" // for getting fake message-only window interface that is used for creating device context renderer of the OpenGL;

namespace ex_ui { namespace draw { namespace open_gl { namespace context {

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getgraphicsmode ;
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setgraphicsmode ;

	class CMode {
	public:
		enum e_mode : uint32_t {
		    e__undef     = 0,             // the error mode;
		    e_advanced   = GM_ADVANCED  , // the mode for the possibility to apply world transformations;
		    e_compatible = GM_COMPATIBLE, // the mode for the compatibility with 16-bit operating system; (default);
		};
	public:
		 CMode (void); CMode (const HDC&); CMode(const CMode&) = delete; CMode (CMode&&) = delete;
		~CMode (void);

		uint32_t Current (void) const;       // returns currently saved value of the mode without querying the device object;
		TError&  Error (void) const;

		uint32_t Get (void) const;           // gets the current graphics' mode which the input device context is in;
		err_code Set (const e_mode);         // sets the new graphics' mode which the input device context is in;

		bool IsAdvanced (void) const;
		bool Is_valid (void) const;

		static
		CString To_str (const uint32_t _u_mode);
		CString To_str (void) const;

		CMode& operator <<(const HDC&);      // sets the target device context handle for manupulating by its graphical mode;
		CMode& operator <<(const e_mode);    // sets the the mode value; no query to device context;
		const
		CMode& operator >>(uint32_t&) const; // gets the current value;  no query to device context;

	private:
		CMode& operator = (const CMode&) = delete; CMode& operator = (CMode&&) = delete;
		mutable
		uint32_t m_value;
		mutable
		CError   m_error;
		HDC      m_hdc; // this is the context device handle which the graphics mode is received from and can be set to;
	};

	/*
	   https://learn.microsoft.com/en-us/windows/win32/gdi/windows-gdi ;
	   https://en.wikipedia.org/wiki/Graphics_Device_Interface ;
	   https://learn.microsoft.com/en-us/windows/win32/gdi/about-device-contexts ;
	   https://learn.microsoft.com/en-us/windows/win32/gdi/device-contexts;
	*/
	/* https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglcreatecontext ;
	   excerpt: ...creates a new OpenGL rendering context, which is suitable for drawing on the device referenced by hdc... ;
	   this is the class declartion of the context compatible with regular GDI context (HDC);
	*/
	class CDevice : public CBase {
	public:
		 CDevice (void); CDevice (const HWND _h_target); // the mode of the HDC will be set automatically to advanced mode if input window handle is valid;
		~CDevice (void);

		err_code Create (const HWND _h_target); // creates the rendering context that is compatible with input window device context;
		const
		CFormat& Format (void) const; // gets the reference to the pixel format object; (ro)
		CFormat& Format (void) ;      // gets the reference to the pixel format object; (rw)
		const
		CMode&   Mode (void) const;
		CMode&   Mode (void) ;

		CDevice& operator <<(const HWND _h_target); // invokes this::Create(...); if the renderer context is already created, it will be destroyed first;

		operator const HDC (void) const;

		static bool Is_DC (const HDC);     // returns true if an input handle has proper data type such as: OBJ_DC|OBJ_MEMDC;
		static bool Is_DC_mem (const HDC); // returns true if an input handle has proper data type is OBJ_MEMDC;

	private:
		CFormat m_format;
		CMode   m_mode;
	};

	class CSelector {
	public:
		 CSelector (void); CSelector (const CSelector&) = delete; CSelector (CSelector&&) = delete;
		 CSelector (const HDC& _to_set);
		~CSelector (void);

		TError&  Error (void) const;
		bool  Is_used  (void) const;    // returns 'true' in case this selector is already used: draw renderer context is created and is selected;

		err_code Set (const HDC _h_dc); // creates the draw renderer context from the input device one and makes it current;
		err_code Unset (void);          // sets the current context to nothing;

	private:
		CSelector& operator = (const CSelector&) = delete; CSelector& operator = (CSelector&&) = delete;
		CError m_error;
		HGLRC  m_renderer; 
	};
}
	class CFake_Ctx { using CDevice = ex_ui::draw::open_gl::context::CDevice;
	public:
		 CFake_Ctx (const CFake_Ctx&) = delete; CFake_Ctx (CFake_Ctx&&) = delete;
		 CFake_Ctx (void); // creates fake device;
		~CFake_Ctx (void); // destroys fake device;

		err_code Create (void);
		err_code Destroy (void);

		TError&  Error (void) const;

		const
		CDevice& operator ()(void) const;

	private:
		CFake_Ctx& operator = (const CFake_Ctx&) = delete; CFake_Ctx& operator = (CFake_Ctx&&) = delete;
		CError   m_error ;
		TFakeWnd m_fk_wnd;  // it is created automatically in its constructor;
		CDevice  m_device;  // a fake window GDI object;
	};
}}}

#endif/*_GL_CTX_DEVICE_H_INCLUDED*/