#ifndef _GL_CONTEXT_H_INCLUDED
#define _GL_CONTEXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-Aug-2025 at 12:33:39.591, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' context base interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace context {

	class CTarget {
	public:
		 CTarget (void);  CTarget (const HWND); CTarget (const CTarget&) = delete; CTarget (CTarget&&) = delete;
		~CTarget (void);

		TError& Error (void) const; // this is the system error wrapper; that is the base for OpenGL error wrapper;
		err_code Free (void) ;      // releases the device context and sets error to '__e_not_inited', otherwise the error state of the failure;
		bool Is_valid (void) const; // validates device context handle;

		const HDC Get (void) const; // gets target window device context handle;
		err_code  Set (const HWND); // sets target window device context handle;
		// it would be better to name the following property as 'Caller' instead of 'Source';
		_pc_sz Source (void) const; // returns the window class name that is creator of the device context, i.e. the source;
		bool   Source (_pc_sz _p_cls_name); // sets the source class name; returns 'true' in case of source class name change;

		CTarget& operator <<(const HWND);   // invokes this::Set(...); if the device context is already obtained, it will be released first;

		operator const HWND (void) const;

	protected:
		mutable
		CError  m_error;
		CString m_cls_src;
		HDC  m_dc_src ; // this is the source device context from which the device renderer is created; it is auto-released on destroying this class instance;
		HWND m_target ; // the target window handle, it owns the source device context; this window handle is saved for releasing the HDC;
	};

	class CBase {
	public:
		 CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete;
		~CBase (void);

		 TError&  Error  (void) const;   // this is the OpenGL error wrapper;
		 err_code Destroy(void) ;

		 bool   Is_valid (void) const;   // returns 'true' in case if device renderer context is not nullptr; no target object check;
		 HGLRC  Renderer (void) const;

		 err_code Set (const HWND _h_target);   // assines the target window handle, does*not* create the target, and checks the renderer handle first;

		 const
		 CTarget& Target (void) const;
		 CTarget& Target (void) ;        // releasing device context directly in target object will lead to errors on operations with the renderer;

		 CBase& operator <<(const HWND); // invokes this::Set(...); if the renderer context is already created, it will be destroyed first;

	private:
		 CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
	protected:
		 mutable // for updating the error state in 'const' methods/properties;
		 CError   m_error ;
		 CTarget  m_target;  // this is the object containing the target window handle and its device context one;
		 HGLRC    m_drw_ctx; // rendering context that is compatible with regular GDI;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglcreatecontext ;
	// excerpt: ...creates a new OpenGL rendering context, which is suitable for drawing on the device referenced by hdc... ;
	// this is the class declartion of the context compatible with regular GDI context (HDC);
	class CDevice : public CBase {
	public:
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
	public:
		 CDevice (void); CDevice (const HWND _h_target); // the mode of the HDC will be set automatically to advanced mode if input window handle is valid;
		~CDevice (void);

		err_code Create (const HWND _h_target); // creates the rendering context that is compatible with input window device context;
		const
		CMode&   Mode (void) const;
		CMode&   Mode (void);

		CDevice& operator <<(const HWND _h_target); // invokes this::Create(...); if the renderer context is already created, it will be destroyed first;

		static bool Is_DC (const HDC);     // returns true if an input handle has proper data type such as: OBJ_DC|OBJ_MEMDC;
		static bool Is_DC_mem (const HDC); // returns true if an input handle has proper data type is OBJ_MEMDC;

	private: CMode m_mode;
	};
}
	/* The main idea is composed by several steps:
		(1) creates fake window;
		(2) gets renderer context that is based on regular device context handle; *important* the rendering context must be set as current one;
		(3) querying pointers to the OpenGL functions that are required for creating real draw context of OpenGL version at least 3.0;
		(4) creates new window that is expected to be the surface of the drawing;
		(5) using new window device context for setting pixel format by using OpenGL functions been loaded on the previous step (#3);
		(6) creating the OpenGL draw rendering/graphics context and making it current;
	*/

	class CGraphics : public context::CBase { typedef context::CBase TBase;
	public:
		class CVersion { // for setting the version attributes that may be different by value in comparison with OpenGL installed on the OS;
		public:
			CVersion (void) ; CVersion (const CVersion&) = delete; CVersion (CVersion&&) = delete; ~CVersion (void) = default;

			TError&  Error (void) const;
			/*the version info is loaded from the system registry;*/
			uint32_t Major (void) const;
			uint32_t Minor (void) const;
			bool  Use_core (void) const;

			err_code Load  (void);  // reads all values related to context version from the system registry;

		private:
			CVersion& operator = (const CVersion&) = delete;
			CVersion& operator = (CVersion&&) = delete;
			CError    m_error;
			uint32_t  m_major, m_minor;
			bool      m_use_core;
		};
	public:
		 CGraphics (void);  CGraphics (const CGraphics&) = delete; CGraphics (CGraphics&&) = delete;
		~CGraphics (void);

		 err_code  Create (const uint32_t _u_gl_major_ver, const uint32_t _u_gl_minor_ver); // it is supposed the target window is set and its HDC is already gotten;

		 const
		 CVersion& Version (void) const;

	private:
		 CGraphics& operator = (const CGraphics&) = delete; CGraphics& operator = (CGraphics&&) = delete;
		 CVersion  m_ver;
	};
}}}

#endif/*_GL_CONTEXT_H_INCLUDED*/